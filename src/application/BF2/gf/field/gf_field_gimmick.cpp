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

namespace gmk {

GmkAntiBladeAreaManager::~GmkAntiBladeAreaManager() {
    dispose();
}

}  // namespace gmk

namespace gf {

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
    if (gimmick->m_eventFade) {
        float dt = info.m_deltaTime;
        if (!gimmick->m_fadeGmkUpdated) {
            gimmick->m_fadeGmkUpdated = gmk::GmkManager::get()->updateImmediate();
        } else {
            gimmick->m_fadeViewReady = gmk::GmkManager::get()->isValidView();
        }
        gimmick->m_fadeTime += dt;
        if (gimmick->m_fadeTime > 10.0f) {
            gimmick->m_fadeViewReady = true;
        }
    }
    gimmick->m_mobSlotMgr.update();
    if (gmk::isPlayerExist()) {
        gimmick->m_enableOpenMainMenu = GfGameUtil::isPointSavable(gmk::getPlayerPos());
    }
}

void GfFieldGimmick::fn_710026B74C(const fw::UpdateInfo& info) {}

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

}  // namespace gf

namespace gmk {

GmkCtrlVolSeManager::~GmkCtrlVolSeManager() {}

}  // namespace gmk
