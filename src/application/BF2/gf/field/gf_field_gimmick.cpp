#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkAccManager.h"
#include "classes/gmk/GmkDoorPhantomManager.h"
#include "classes/gmk/GmkDmgPhantomManager.h"
#include "classes/gmk/GmkCtrlVolSeManager.h"
#include "gf/GfGameUtil.h"
#include "classes/gmk/GmkAntiBladeArea.h"
#include "classes/gmk/GmkAntiBladeAreaManager.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfManager.h"
#include "classes/gmk/GmkCtrlVolSeManager.h"
#include "mm/Math.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfGmkBladeTraverser.h"
#include "classes/gmk/GmkBlade.h"
#include "classes/gmk/GmkNpc.h"
#include "classes/gmk/GmkCtrlVolSe.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gmk/IGmkList.h"
#include "gf/GfDataEvent.h"
#include "classes/gf/GfUnpopBladeIds.h"
#include "classes/gf/GfGmkLocatorAtlas.h"
#include "gf/GfDataBlade.h"
#include "ml/MTRand.h"
#include "classes/gmk/GmkEffect.h"
#include "classes/gmk/GmkEvent.h"
#include "classes/gmk/TGmkList.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfObjUtil.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjInfo.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjSetupMob.h"
#include "classes/gmk/GmkMob.h"
#include "classes/gmk/GmkRoutedMob.h"
#include "mm/mtl/FixedList.h"

namespace gmk {

GmkAntiBladeAreaManager::~GmkAntiBladeAreaManager() {
    dispose();
}

}  // namespace gmk

namespace gf {

namespace {
// disposes a mob's game object after the objects bound to it (update and createMobInfos inline it; the name is not
// the original's)
inline void disposeMob(const GfMobSlotManager::MobInfo& info) {
    if (GfObjManager* manager = GfObjManager::get()) {
        if (const mm::mtl::FixedList<GF_OBJ_HANDLE*, 32>* list = manager->getMultiBindList(info.m_handle)) {
            for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 32>::const_iterator it = list->begin(); it != list->end(); ++it) {
                gmk::disposeGobInst(*it, 1.0f);
            }
        }
    }
    gmk::disposeGobInst(info.m_handle, 1.0f);
}
}  // namespace

bool GfMobSlotManager::addFailedPopDistSq(float distSq) {
    if (m_failedPopDistSqs.size() == m_failedPopDistSqs.capacity()) {
        return false;
    }
    for (float* it = m_failedPopDistSqs.begin(); it != m_failedPopDistSqs.end(); ++it) {
        if (*it < distSq) {
            continue;
        }
        m_failedPopDistSqs.insert(it, distSq);
        return true;
    }
    m_failedPopDistSqs.push_back(distSq);
    return true;
}

void GfMobSlotManager::update() {
    if (GfGameManager::isMapjump()) {
        return;
    }
    if (mm::mtl::PtrSingleton<GfFieldGimmick>::get()->m_eventFade.m_active) {
        return;
    }
    m_slotDistSqs.clear();
    if (!gmk::isInterestPosExist()) {
        return;
    }
    createMobInfos();
    float minEmptyDistSq = 1.0e12f;
    bool hasEmpty = false;
    for (MobInfo& info : m_mobInfos) {
        GF_OBJ_HANDLE* handle = info.m_handle;
        if (GfObjUtil::isSearchEmptyResource(handle)) {
            minEmptyDistSq = info.m_distSq < minEmptyDistSq ? info.m_distSq : minEmptyDistSq;
            hasEmpty = true;
            continue;
        }
        mm::mtl::FixedVector<GF_SLOT_HANDLE*, 88> slots;
        GfObjUtil::getMobSlotHandle(slots, handle);
        GF_SLOT_HANDLE* slot = reinterpret_cast<GF_SLOT_HANDLE*>(-1);
        if (!slots.empty()) {
            slot = slots[0];
        }
        if (slot != reinterpret_cast<GF_SLOT_HANDLE*>(-1)) {
            if (m_slotDistSqs.lookup(slot).m_node == nullptr || info.m_distSq < m_slotDistSqs[slot]) {
                m_slotDistSqs[slot] = info.m_distSq;
            }
        }
    }
    if (!hasEmpty || m_slotDistSqs.m_tree.m_size == 0) {
        return;
    }
    float maxDistSq = 0.0f;
    GF_SLOT_HANDLE* maxSlot = reinterpret_cast<GF_SLOT_HANDLE*>(-1);
    typedef mm::mtl::Map<GF_SLOT_HANDLE*, float>::node SlotNode;
    for (SlotNode* n = m_slotDistSqs.m_tree.first(); n != nullptr; n = m_slotDistSqs.m_tree.next(n)) {
        if (maxDistSq < n->value.second) {
            maxSlot = n->value.first;
            maxDistSq = n->value.second;
        }
    }
    if (!(minEmptyDistSq < maxDistSq)) {
        return;
    }
    for (MobInfo& info : m_mobInfos) {
        mm::mtl::FixedVector<GF_SLOT_HANDLE*, 88> slots;
        GfObjUtil::getMobSlotHandle(slots, info.m_handle);
        GF_SLOT_HANDLE* slot = slots.size() != 0 ? *slots.begin() : reinterpret_cast<GF_SLOT_HANDLE*>(-1);
        if (maxSlot == slot) {
            disposeMob(info);
        }
    }
}

void GfMobSlotManager::createMobInfos() {
    disposeMobInfos();
    if (!gmk::isInterestPosExist()) {
        return;
    }
    const mm::Vec3& pos = gmk::getInterestPos();
    // each kind's mobs, with their squared distance from the interest position (a lambda: the name is not the original's)
    auto addGmkMob = [this, pos](const gmk::AGmkBase& base) {
        const gmk::GmkMob& gmk = static_cast<const gmk::GmkMob&>(base);
        if (!gmk.isValid()) {
            return;
        }
        unsigned int num = gmk.getGobInstNum();
        for (unsigned int i = 0; i < num; ++i) {
            GF_OBJ_HANDLE* handle = gmk.getGobInst(i);
            // the distance in each branch: x and y of the captured position stay integer copies (`ldp w; fmov`)
            float distSq;
            GfObjAcc acc(handle);
            if (acc.isValidTransform()) {
                mm::Vec3 d = pos - acc.getWorldTransform().position;
                distSq = d.x * d.x + d.y * d.y + d.z * d.z;
            } else {
                mm::Vec3 d = pos - mm::mtl::rttiCast<GfObjSetupMob>(GfObjManager::getObjInfo(handle)->m_setup)->m_initialPos;
                distSq = d.x * d.x + d.y * d.y + d.z * d.z;
            }
            MobInfo info = {handle, distSq};
            m_mobInfos.push_back(info);
        }
    };
    gmk::GmkManager::get()->traverseGmkInst(gmk::GmkMob::TYPE, addGmkMob);
    if (!m_failedPopDistSqs.empty()) {
        m_popDistSqLimit = m_failedPopDistSqs.back();
    } else if (GfObjManager::getGfObjCapacity(7) < static_cast<int>(m_mobInfos.size())) {
        m_popDistSqLimit = 0.0f;
    }
    MobInfo* farthest = nullptr;
    float limit = m_popDistSqLimit;
    for (MobInfo& info : m_mobInfos) {
        if (limit < info.m_distSq) {
            limit = info.m_distSq;
            farthest = &info;
        }
    }
    if (farthest != nullptr) {
        // the farthest mob's position is looked up and left unused (the original keeps the calls)
        {
            GfObjAcc acc(farthest->m_handle);
            mm::Vec3 farthestPos;
            if (acc.isValidTransform()) {
                farthestPos = acc.getWorldTransform().position;
            } else {
                GFOBJ_INFO* info = GfObjManager::getObjInfo(farthest->m_handle);
                if (info != nullptr && info->m_setup != nullptr && info->m_setup->m_type == info->m_obj->m_type &&
                    info->m_obj->m_type == 7) {
                    if (GfObjSetupMob* setup = mm::mtl::rttiCast<GfObjSetupMob>(info->m_setup)) {
                        farthestPos = setup->m_initialPos;
                    }
                }
            }
        }
        disposeMob(*farthest);
        m_mobInfos.erase(farthest);
        if (!m_failedPopDistSqs.empty()) {
            m_failedPopDistSqs.pop_back();
        }
    }
    // each kind's mobs, with their squared distance from the interest position (a lambda: the name is not the original's)
    auto addGmkRoutedMob = [this, pos](const gmk::AGmkBase& base) {
        const gmk::GmkRoutedMob& gmk = static_cast<const gmk::GmkRoutedMob&>(base);
        if (!gmk.isValid()) {
            return;
        }
        unsigned int num = gmk.getGobInstNum();
        for (unsigned int i = 0; i < num; ++i) {
            GF_OBJ_HANDLE* handle = gmk.getGobInst(i);
            // the distance in each branch: x and y of the captured position stay integer copies (`ldp w; fmov`)
            float distSq;
            GfObjAcc acc(handle);
            if (acc.isValidTransform()) {
                mm::Vec3 d = pos - acc.getWorldTransform().position;
                distSq = d.x * d.x + d.y * d.y + d.z * d.z;
            } else {
                mm::Vec3 d = pos - mm::mtl::rttiCast<GfObjSetupMob>(GfObjManager::getObjInfo(handle)->m_setup)->m_initialPos;
                distSq = d.x * d.x + d.y * d.y + d.z * d.z;
            }
            MobInfo info = {handle, distSq};
            m_mobInfos.push_back(info);
        }
    };
    gmk::GmkManager::get()->traverseGmkInst(gmk::GmkRoutedMob::TYPE, addGmkRoutedMob);
}

inline void GfFieldGimmick::initialize(const GfSetupParam& param) {
    gmk::GmkManager::CreateInfo info;
    info.m_handle = getAllocator(ALLOCATOR(9))->getMemHandle();
    info.m_bdatPath = "bdat/common_gmk.bdat";
    info.m_tableName = "RSC_GmkSetList";
    info.m_param = 1;
    m_gmkMgr.create(info);
    m_initialized = true;
    GfObjManager::addListener(this, IGfObjListener::OBJEVT(0));
}

GfFieldGimmick::GfFieldGimmick(const GfSetupParam& param)
    : m_initialized(false),
      m_locatorAtlas(nullptr),
      m_unknownFlag1(false),
      m_enableOpenMainMenu(true),
      m_unknownFlag2(true),
      m_unknownFlag3(true) {
    initialize(param);
}

GfFieldGimmick::~GfFieldGimmick() {
    GfObjManager::removeListener(this);
}

GfGmkLocatorAtlas::~GfGmkLocatorAtlas() {
    dispose();
}

void GfFieldGimmick::listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) {}

void GfFieldGimmick::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    switch (static_cast<int>(gev)) {
    case 1:
        if (info.m_withSaveData) {
            m_unknownFlag1 = true;
        }
        break;
    case 2:
        // the effects are created again from what they were created with
        for (gmk::GmkSet** it = m_gmkMgr.m_gmkSets.begin(); it != m_gmkMgr.m_gmkSets.end(); ++it) {
            gmk::TGmkList<gmk::GmkEffect, gmk::GmkEffect::BdatInfo, 1413695045u, 8u, gmk::GmkEffectGobCustom>* list =
                static_cast<gmk::TGmkList<gmk::GmkEffect, gmk::GmkEffect::BdatInfo, 1413695045u, 8u, gmk::GmkEffectGobCustom>*>(
                    (*it)->getGmkList(gmk::GmkEffect::TYPE));
            if (list != nullptr && list->isValid()) {
                unsigned int num = list->getInstNum();
                for (unsigned int i = 0; i < num; ++i) {
                    gmk::GmkEffect& effect = list->m_gmks[i];
                    gmk::AGmkBase::CreateInfo createInfo = effect.m_createInfo;
                    if (createInfo.m_data != nullptr) {
                        effect.create(createInfo);
                    }
                }
            }
        }
        for (gmk::GmkSet** it = m_gmkMgr.m_gmkSets.begin(); it != m_gmkMgr.m_gmkSets.end(); ++it) {
            gmk::IGmkList* list = (*it)->getGmkList(gmk::GmkEvent::TYPE);
            if (list != nullptr) {
                unsigned int num = list->getInstNum();
                for (unsigned int i = 0; i < num; ++i) {
                    static_cast<gmk::GmkEvent*>(list->getInst(i))->pad_f2 = false;
                }
            }
        }
        break;
    case 6: {
        // activates every blade not popped yet, in a random order (a rare one first three times in four)
        GfUnpopBladeIds ids;
        if (ids.m_ids.empty()) {
            break;
        }
        // a do-while: a while loop here has its latch duplicated into erase's paths, which the original does not
        do {
            unsigned short* it = &ids.m_ids[ml::mtRand(ids.m_ids.size())];
            if (!GfDataBlade::isRareBlade(*it) && ml::mtRandf1() < 0.75f) {
                for (unsigned short* rare = ids.m_ids.begin(); rare != ids.m_ids.end(); ++rare) {
                    if (GfDataBlade::isRareBlade(*rare)) {
                        it = rare;
                        break;
                    }
                }
            }
            gevBladeActivate(*it, ActivateType(0), ActivateType(1));
            ids.m_ids.erase(it);
        } while (!ids.m_ids.empty());
        break;
    }
    case 7:
        m_unknownFlag1 = false;
        break;
    }
}

inline void GfFieldGimmick::finalize() {
    m_gmkMgr.dispose();
    m_initialized = false;
}

void GfFieldGimmick::build(const GfSetupParam& param) {
#line 773
    GfFieldGimmick* gimmick = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldGimmick(param);
    GfEvent::addEventCallback(gimmick);
}

void GfFieldGimmick::destroy() {
    GfFieldGimmick* gimmick = get();
    GfEvent::removeEventCallback(gimmick);
    gimmick->finalize();
    delete gimmick;
}

void GfFieldGimmick::update(const fw::UpdateInfo& info) {
    if (GfManager::isDestroyNow()) {
        return;
    }
    GfFieldGimmick* gimmick = get();
    gimmick->m_gmkMgr.update(info.m_deltaTime);
    gimmick->m_accMgr.update();
    gimmick->m_doorPhantomMgr.update(info.m_deltaTime);
    gimmick->m_dmgPhantomMgr.update(info.m_deltaTime);
    gimmick->m_ctrlVolSeMgr.update(info.m_deltaTime);
    if (gimmick->m_eventFade.m_active) {
        float dt = info.m_deltaTime;
        if (!gimmick->m_eventFade.m_gmkUpdated) {
            gimmick->m_eventFade.m_gmkUpdated = gmk::GmkManager::get()->updateImmediate();
        } else {
            gimmick->m_eventFade.m_viewReady = gmk::GmkManager::get()->isValidView();
        }
        gimmick->m_eventFade.m_time += dt;
        if (gimmick->m_eventFade.m_time > 10.0f) {
            gimmick->m_eventFade.m_viewReady = true;
        }
    }
    gimmick->m_mobSlotMgr.update();
    if (gmk::isPlayerExist()) {
        gimmick->m_enableOpenMainMenu = GfGameUtil::isPointSavable(gmk::getPlayerPos());
    }
}

}  // namespace gf

namespace gmk {

// inline: the original's caller (GfFieldGimmick::update) still passes `this`, which it ignores (it works on the
// singleton); a strong definition lets the optimizer drop that argument at the call
inline void GmkCtrlVolSeManager::update(float dt) {
    get()->m_updating = true;
    for (GmkCtrlVolSe& se : get()->m_list) {
        se.update(dt);
    }
    get()->m_updating = false;
    for (mm::mtl::IntrusiveList<GmkCtrlVolSe>::iterator it = get()->m_list.begin(); it != get()->m_list.end(); ++it) {
        if (it->isPlayEnd()) {
            it = get()->m_list.erase(it);
            --it;
        }
    }
}

}  // namespace gmk

namespace gf {

void GfFieldGimmick::postUpdate(const fw::UpdateInfo& info) {}

bool GfFieldGimmick::createGmkSet(int mapId) {
    if (!get()->m_gmkMgr.isValid()) {
        return false;
    }
    mtl::ALLOC_HANDLE handle = getAllocator(ALLOCATOR(8))->getMemHandle();
    int gmkSetId = getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(mapId);
    get()->m_gmkMgr.createGmkSet(handle, gmkSetId, mm::Vec3::zero, 0.0f);
    return true;
}

int GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(int mapId) {
    if (!get()->m_gmkMgr.isValid()) {
        return -1;
    }
    return get()->m_gmkMgr.findFirstBdatId_RSC_GmkSetList(mapId);
}

void GfFieldGimmick::disposeGmkSet(int mapId) {
    if (!get()->m_gmkMgr.isValid()) {
        return;
    }
    int gmkSetId = getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(mapId);
    get()->m_gmkMgr.disposeGmkSet(gmkSetId);
}

bool GfFieldGimmick::isGmkSetReady() {
    if (GfManager::isDestroyNow()) {
        return true;
    }
    return get()->m_gmkMgr.isGmkSetsReady();
}

int GfFieldGimmick::getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(int gmkSetId) {
    if (!get()->m_gmkMgr.isValid()) {
        return -1;
    }
    return get()->m_gmkMgr.getMapBdatId(gmkSetId);
}

int GfFieldGimmick::getBdatIdOfActiveGmkAntiBladeArea() {
    if (get() == nullptr) {
        return 0;
    }
    gmk::GmkAntiBladeAreaManager* manager = gmk::GmkAntiBladeAreaManager::get();
    if (manager == nullptr) {
        return 0;
    }
    const gmk::GmkAntiBladeArea* area = manager->m_active;
    if (area == nullptr) {
        return 0;
    }
    return area->getBdatInfo()->m_bdatId;
}

GfUnpopBladeIds::GfUnpopBladeIds() {
    GfDataBlade::getListReserver(m_ids);
    for (unsigned short* it = m_ids.begin(); it != m_ids.end(); ++it) {
        if (!GfGameUtil::isBladeInVillage(*it)) {
            it = m_ids.erase(it);
            --it;
        }
    }
    gmk::GmkManager::get()->traverseGmkInst(gmk::GmkBlade::TYPE, *this);
}

void GfFieldGimmick::gevBladeActivate(unsigned int bladeId, gf::ActivateType, gf::ActivateType type) {
    // gives the blade gimmick its id and marks whether it changed (inline; the field at 0x54 is unnamed)
    auto setBladeId = [](const gmk::AGmkBase* gmk, int id) {
        gmk::GmkBlade* blade = const_cast<gmk::GmkBlade*>(static_cast<const gmk::GmkBlade*>(gmk));
        bool changed = blade->m_bladeId != id;
        blade->m_bladeId = id;
        blade->pad_54 = changed;
    };
    if (bladeId == 1003) {
        return;
    }
    switch (type) {
    case 1: {
        if (!GfGameUtil::isBladeInVillage(bladeId)) {
            return;
        }
        {
            GfGmkBladeTraverser f(0, bladeId);
            gmk::GmkManager::get()->traverseGmkInst(gmk::GmkBlade::TYPE, f);
            if (f.m_result != nullptr) {
                return;
            }
        }
        GfGmkBladeTraverser f(GfDataBlade::getSize(bladeId), 0);
        gmk::GmkManager::get()->traverseGmkInst(gmk::GmkBlade::TYPE, f);
        if (f.m_result != nullptr) {
            setBladeId(f.m_result, bladeId);
        }
        break;
    }
    case 0:
    case 2:
    case 3: {
        GfGmkBladeTraverser f(0, bladeId);
        gmk::GmkManager::get()->traverseGmkInst(gmk::GmkBlade::TYPE, f);
        if (f.m_result == nullptr) {
            return;
        }
        setBladeId(f.m_result, 0);
        GfUnpopBladeIds ids;
        if (ids.m_ids.empty()) {
            return;
        }
        int id = *ids.m_ids.begin();
        if (!GfDataBlade::isRareBlade(id) && ml::mtRandf1() < 0.75f) {
            for (unsigned short blade : ids.m_ids) {
                if (GfDataBlade::isRareBlade(blade)) {
                    id = blade;
                    break;
                }
            }
        }
        setBladeId(f.m_result, id);
        break;
    }
    }
}

void GfFieldGimmick::gevPlayEvent(GEV gev, unsigned int eventId) {
    switch (gev) {
    case GEV(10):
    case GEV(14):
        m_unknownFlag2 = GfDataEvent::getEventType(eventId) < 2;
        m_unknownFlag3 = GfDataEvent::getEventType(eventId) < 2;
        break;
    case GEV(11):
        m_unknownFlag2 = true;
        m_unknownFlag3 = true;
        break;
    default:
        return;
    }
    for (gmk::GmkSet** it = m_gmkMgr.m_gmkSets.begin(); it != m_gmkMgr.m_gmkSets.end(); ++it) {
        gmk::IGmkList* list = (*it)->getGmkList(gmk::GmkNpc::TYPE);
        if (list == nullptr) {
            continue;
        }
        for (unsigned int i = 0; i < list->getInstNum(); ++i) {
            static_cast<const gmk::GmkNpc*>(list->getInst(i))->setDispSpecified(m_unknownFlag2);
        }
    }
    GfGameUtil::setDispByGmkType(gmk::GmkType(0x3c), m_unknownFlag3);
}

void GfGmkBladeTraverser::onTraverse(const gmk::AGmkBase& base) {
    const gmk::GmkBlade& blade = static_cast<const gmk::GmkBlade&>(base);
    bool found;
    if (m_bladeId == 0) {
        found = static_cast<const gmk::GmkBlade::BdatInfo*>(blade.m_createInfo.m_bdatInfo)->m_kind == m_kind && blade.m_bladeId == 0;
    } else if (m_rareOnly) {
        found = blade.m_bladeId == 1001 || blade.m_bladeId == 1002;
    } else {
        found = blade.m_bladeId == m_bladeId;
    }
    if (found) {
        m_result = &blade;
    }
}

}  // namespace gf

namespace gmk {

GmkCtrlVolSeManager::~GmkCtrlVolSeManager() {}

}  // namespace gmk

// Explicit instantiation: as a linkonce_odr copy the inliner defers ~GfGmkLocators (cost 265) out of destruct_n,
// because destruct_n (cost 55) is still inlinable into Vector::clear, and inlines destruct_n into
// ~GfGmkLocatorAtlas; the original keeps this out-of-line copy with ~GfGmkLocators inlined into it, which a
// non-linkonce definition gives (the destructor above calls it)
template void mm::mtl::destruct_n<gf::GfGmkLocators>(gf::GfGmkLocators*, size_t);
