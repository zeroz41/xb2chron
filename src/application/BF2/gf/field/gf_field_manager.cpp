#include "classes/gf/GfFieldManager.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/gf/GfFieldSound.h"
#include "classes/gf/GfFieldZone.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfFieldCollect.h"
#include "classes/gf/GfFieldMapGimmick.h"
#include "classes/gf/GfFieldGrave.h"
#include "classes/gf/GfFieldJump.h"
#include "classes/gf/GfFieldWarp.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfMapManager.h"
#include "classes/gf/GfBdatMaplist.h"
#include "gf/GfDataMap.h"
#include "gf/SDataGame.h"
#include "gf/MapjumpCallbackInfo.h"
#include "classes/gmk/GmkLandmarkManager.h"
#include "classes/gmk/GmkLandmark.h"
#include "classes/gf/GfFieldTbox.h"
#include "classes/gf/GfFieldGmkTutorial.h"
#include "classes/gf/GfFieldDmgManager.h"
#include "classes/gf/GfFobjManager.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfPause.h"
#include "classes/gf/GfFieldZoneScript.h"
#include "classes/gf/SCOM_SCRIPT.h"
#include "classes/fw/WindManager.h"
#include "fw/RenderParam.h"
#include "fw/UpdateInfo.h"
#include "mm/Vec3.h"

namespace gf {

GfFieldManager::~GfFieldManager() {
    GfObjManager::removeListener(this);
}

void GfFieldManager::build(const GfSetupParam& param) {
#line 70
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldManager(param);
}

void GfFieldManager::destroy() {
    GfFieldManager* manager = get();
    manager->finalize();
    delete manager;
}

void GfFieldManager::finalize() {
    if (!GfGameManager::isGameObjEmpty()) {
        GfSleep(1);
    }
    GfFieldDmgManager::destroy();
    GfFobjManager::destroy();
    GfFieldLod::destroy();
    GfFieldGmkTutorial::destroy();
    GfFieldWarp::get()->dispose();
    delete GfFieldWarp::get();
    GfFieldJump::get()->dispose();
    delete GfFieldJump::get();
    GfFieldGrave::get()->dispose();
    delete GfFieldGrave::get();
    GfFieldMapGimmick::get()->dispose();
    delete GfFieldMapGimmick::get();
    GfFieldTbox::destroy();
    GfFieldCollect::destroy();
    GfFieldGimmick::destroy();
    GfFieldZone::destroy();
    GfFieldSound::destroy();
    GfFieldWeather::destroy();
    GfFieldTime::destroy();
    GfEvent::removeEventCallback(this);
    m_initialized = false;
}

void GfFieldManager::clear() {
    if (GfFieldTime::get() != nullptr) {
        GfFieldTime::get()->clear();
    }
    GfFieldWeather::clear();
    if (GfFieldSound::get() != nullptr) {
        GfFieldSound::get()->clear();
    }
    GfFieldLod::validateByInitData();
}

void GfFieldManager::setupGame() {
    if (GfFieldTime::get() != nullptr) {
        GfFieldTime::get()->setupGame();
    }
    GfFieldWeather::setupGame();
    SCOM_SCRIPT::create(0, GfGameManager::fn_71002A9E68() ? "aoc_field" : "field", false);
}

void GfFieldManager::fn_7100277784() {
    if (GfFobjManager::get() != nullptr) {
        GfFobjManager::get()->fn_7100289668();
    }
}

void GfFieldManager::setSuspendGame(bool suspend) {
    if (GfFieldTime::get() != nullptr && !suspend) {
        GfFieldTime::get()->saveSuspendRealTime();
    }
}

void GfFieldManager::listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) {}

bool GfFieldManager::isExistObj() {
    return GfFobjManager::isExistObj();
}

void GfFieldManager::destroyObj() {
    GfFobjManager::destroyObj();
}

fw::EffectPack* GfFieldManager::getEffectPack() {
    return GfMapManager::getEffectPack();
}

void GfFieldManager::gevReloadBdat(RELOAD_BDAT type, unsigned int id) {
    unsigned int mapId = GfDataMap::getMapID(GfGameManager::getMapJumpID());
    if (mapId != 0) {
        m_enemyBaloonRadius = GfBdatMaplist::get()->getMapliste_balloondisp_r(mapId);
    }
    if (GfFieldTime::get() != nullptr) {
        GfFieldTime::get()->gevReloadBdat(type, id);
    }
}

bool GfFieldManager::execMapScript(const char* name) {
    return GfFieldZoneScript::execScript(name);
}

void GfFieldManager::destroyMapScript() {
    GfFieldZoneScript::destroyScript();
}

bool GfFieldManager::isExecMapScriptBusy() {
    return GfFieldZoneScript::isExecScriptBusy();
}

bool GfFieldManager::isDestroyMapScriptBusy() {
    return GfFieldZoneScript::isDestroyScriptBusy();
}

float GfFieldManager::getEnemyBaloonRadius() {
    return get()->m_enemyBaloonRadius;
}

const char* GfFieldManager::getMapName() {
    return GfMapManager::getMapName();
}

bool GfFieldManager::getLandmarkNameId(unsigned char*& bdat, int& id) {
    gmk::GmkLandmark* landmark = gmk::GmkLandmarkManager::get()->m_currentLandmark;
    if (landmark == nullptr) {
        return false;
    }
    bdat = GfDataBdat::getFP(0x1B3);
    id = landmark->getBdatInfo()->m_nameId;
    return true;
}

void GfFieldManager::setLandmarkPoint(unsigned int point, const mm::Vec3& pos, float rotY) {
    SDataGame* data = GfDataManager::getDataGame();
    if (GfDataMap::getMapID(point) != 0x3A) {
        data->m_landmarkPoint = point;
        data->m_landmarkPos = pos;
        data->m_landmarkRotY = rotY;
    }
}

unsigned int GfFieldManager::getLandmarkPoint() {
    unsigned int point = GfDataManager::getDataGame()->m_landmarkPoint;
    if (point == 0) {
        return GfGameManager::getMapJumpID();
    }
    return point;
}

const mm::Vec3& GfFieldManager::getLandmarkPos() {
    SDataGame* data = GfDataManager::getDataGame();
    if (data->m_landmarkPoint == 0) {
        return mm::Vec3::zero;
    }
    return data->m_landmarkPos;
}

float GfFieldManager::getLandmarkRotY() {
    SDataGame* data = GfDataManager::getDataGame();
    if (data->m_landmarkPoint == 0) {
        return 0.0f;
    }
    return data->m_landmarkRotY;
}

void GfFieldManager::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    if (gev == 5) {
        unsigned int mapId = GfDataMap::getMapID(info.m_mapJumpId);
        if (mapId != 0) {
            m_enemyBaloonRadius = GfBdatMaplist::get()->getMapliste_balloondisp_r(mapId);
        }
    }
    GfFieldZone::get()->gevMapjump(gev, info);
    GfFieldLod::get()->gevMapjump(gev, info);
    GfFieldMapGimmick::get()->gevMapjump(gev, info);
    GfFieldGrave::get()->gevMapjump(gev, info);
    GfFieldJump::get()->gevMapjump(gev, info);
    GfFieldWarp::get()->gevMapjump(gev, info);
    GfFieldGmkTutorial::get()->gevMapjump(gev, info);
    GfFieldTbox::get()->gevMapjump(gev, info);
    GfFieldCollect::get()->gevMapjump(gev, info);
    GfFieldWeather::gevMapjump(gev, info);
    if (GfFieldSound::get() != nullptr) {
        GfFieldSound::get()->gevMapjump(gev, info);
    }
}

void GfFieldManager::gevGameMapModel(GF_OBJ_HANDLE* handle, bool flag) {
    GfFieldWeather::gevGameMapModel(handle, flag);
    if (GfFieldSound::get() != nullptr) {
        GfFieldSound::get()->gevGameMapModel(handle, flag);
    }
}

void GfFieldManager::gevBattleStart() {}

void GfFieldManager::gevBattleEnd() {
    if (GfFieldSound::get() != nullptr) {
        GfFieldSound::get()->gevBattleEnd();
    }
}

void GfFieldManager::gevPause(unsigned int flags0, unsigned int flags1) {
    GfFieldWeather::gevPause(flags0, flags1);
    if (GfFieldSound::get() != nullptr) {
        GfFieldSound::get()->gevPause(flags0, flags1);
    }
}

void GfFieldManager::gevPlayEvent(GEV gev, unsigned int eventId) {
    if (GfFieldSound::get() != nullptr) {
        GfFieldSound::get()->gevPlayEvent(gev, eventId);
    }
    if (GfFieldLod::get() != nullptr) {
        GfFieldLod::get()->gevPlayEvent(gev, eventId);
    }
}

void GfFieldManager::postUpdate(const fw::UpdateInfo& info) {
    if (GfFieldSound::get() != nullptr) {
        GfFieldSound::get()->postUpdate(info);
    }
    GfFieldGimmick::fn_710026B74C(info);
}

void GfFieldManager::update(const fw::UpdateInfo& info) {
    if (GfObjManager::get() != nullptr && GfObjManager::get()->hasReloadObjForDebug()) {
        return;
    }
    if (GfFieldTime::get() != nullptr) {
        GfFieldTime::get()->update(info);
    }
    GfFieldZone::update(info);
    if (GfFieldSound::get() != nullptr) {
        GfFieldSound::get()->update(info);
    }
    GfFieldWeather::update(info);
    if (!GfPause::isPause(1)) {
        GfFobjManager::update(info);
        GfFieldGimmick::update(info);
        GfFieldCollect::update(info);
        GfFieldTbox::update(info);
        if (GfFieldMapGimmick::get() != nullptr) {
            GfFieldMapGimmick::get()->update(info.m_deltaTime);
        }
        if (GfFieldGrave::get() != nullptr) {
            GfFieldGrave::get()->update(info.m_deltaTime);
        }
        if (GfFieldJump::get() != nullptr) {
            GfFieldJump::get()->update(info.m_deltaTime);
        }
        if (GfFieldWarp::get() != nullptr) {
            GfFieldWarp::get()->update(info.m_deltaTime);
        }
        GfFieldLod::update(info);
    }
    GfFieldTime* time = GfFieldTime::get();
    if (time != nullptr) {
        GfMapManager::setEnvTime(time->getHour(), time->getMin());
    }
    fw::RenderParam::setGlobalWindPower(fw::WindManager::getGlobalWindPower(), fw::CAMERA_TYPE(0));
}

}  // namespace gf
