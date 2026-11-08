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
#include "ml/MtRand.h"

namespace gmk {

GmkAntiBladeAreaManager::~GmkAntiBladeAreaManager() {
    dispose();
}

}  // namespace gmk

namespace gf {

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

void GfFieldGimmick::listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) {}

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

// GfMobSlotManager::update (not written yet) adds slots
template mm::mtl::Map<gf::GF_SLOT_HANDLE*, float>::node* mm::mtl::Map<gf::GF_SLOT_HANDLE*, float>::tree_type::insert(const mm::mtl::Map<gf::GF_SLOT_HANDLE*, float>::tree_type::value_type&);
