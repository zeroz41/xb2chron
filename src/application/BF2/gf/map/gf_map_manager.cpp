#include "gf/MapEff.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfBdatMaplist.h"
#include "classes/fw/EffectManager.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "classes/gf/GfMapManager.h"
#include "classes/gf/GfMapManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/gf/GfBdatMaplist.h"
#include "classes/gf/GfEvent.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "classes/gf/GfAllocatorManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfBdatMsg.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupMap.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/fw/DynamicWindResource.h"
#include "classes/fw/EffectLodManager.h"
#include "classes/fw/WindManager.h"
#include "fw/RenderParam.h"
#include "fw/UpdateInfo.h"
#include "fw/WindFactory.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/MapjumpCallbackInfo.h"
#include "idcoli/IDColiAccMan.h"
#include "ml/TimeCount.h"
#include "mm/Math.h"

namespace gf {

GfMapManager::GfMapManager(const GfSetupParam& param)
    : m_initialized(false), m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_mapJumpID(0), m_mapID(0),
      m_assetHandle(reinterpret_cast<GF_ASSET_HANDLE*>(-1)) {
    initialize(param);
    GfObjManager::addListener(this, static_cast<IGfObjListener::OBJEVT>(0));
}

void GfMapManager::initialize(const GfSetupParam& param) {
    GfEvent::addEventCallback(this);
    m_initialized = true;
}

GfMapManager::~GfMapManager() {
    GfObjManager::removeListener(this);
}

void GfMapManager::build(const GfSetupParam& param) {
#line 74
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMapManager(param);
}

void GfMapManager::destroy() {
    GfMapManager* manager = get();
    manager->finalize();
    delete manager;
}

void GfMapManager::finalize() {
    GfObjUtil::destroy(m_handle);
    while (m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        GfSleep(1);
    }
    GfEvent::removeEventCallback(this);
    m_initialized = false;
}

void GfMapManager::listenerGfObj(IGfObjListener::OBJEVT evt, GF_OBJ_HANDLE* handle, unsigned int flag) {
    if (flag != 1) {
        return;
    }
    switch (evt) {
    case 1:
        if (mm::mtl::rttiCast<GfObjSetupMap>(GfObjManager::getObjInfo(handle)->m_setup)->pad_75) {
            m_handle = handle;
        }
        break;
    case 2:
        buildMapData(handle);
        break;
    case 3:
        destroyMapData(handle);
        break;
    case 4:
        if (mm::mtl::rttiCast<GfObjSetupMap>(GfObjManager::getObjInfo(handle)->m_setup)->pad_75) {
            m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        }
        break;
    }
}

void GfMapManager::buildMapData(GF_OBJ_HANDLE* handle) {
    GfMapManager* manager = get();
    if (!mm::mtl::rttiCast<GfObjSetupMap>(GfObjManager::getObjInfo(handle)->m_setup)->pad_75) {
        return;
    }
    manager->m_assetHandle = GfObjUtil::getAssetHandle(manager->m_handle);
    manager->m_coli.create(manager->m_assetHandle);
    if (fw::EffectManager* effect = fw::EffectManager::get()) {
        effect->setDisableCollision(false);
    }
    manager->m_navi.create(manager->m_assetHandle);
    manager->m_eff.create(manager->m_assetHandle, getModelObject());
    manager->m_gibl.create(manager->m_assetHandle);
    manager->m_libl.create(manager->m_assetHandle);
    manager->createWind();
}

void GfMapManager::destroyMapData(GF_OBJ_HANDLE* handle) {
    if (!mm::mtl::rttiCast<GfObjSetupMap>(GfObjManager::getObjInfo(handle)->m_setup)->pad_75) {
        return;
    }
    GfEvent::callGameMapModel(handle, false);
    m_mapJumpID = 0;
    m_mapID = 0;
    m_assetHandle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
    if (fw::WindManager* wind = fw::WindManager::get()) {
        wind->destroyWorld();
    }
    m_wind = nullptr;
    m_libl.destroy();
    m_gibl.destroy();
    m_eff.destroy();
    m_navi.destroy();
    if (fw::EffectManager* effect = fw::EffectManager::get()) {
        effect->setDisableCollision(true);
        ml::TimeCount time;
        while (time.getSecLap() < GfInfo::m_fSecPerFrame) {
        }
    }
    m_coli.destroy();
}

fw::ModelObject* GfMapManager::getModelObject() {
    if (GfObj* obj = GfObjUtil::getObj(get()->m_handle)) {
        if (GfComModel* model = obj->getComponent<GfComModel>(1)) {
            return model->m_model;
        }
    }
    return nullptr;
}

GF_OBJ_HANDLE* GfMapManager::getGfObjHandle() {
    return get()->m_handle;
}

void GfMapManager::destroyObj() {
    GF_OBJ_HANDLE* handle = get()->m_handle;
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        GfObjUtil::destroy(handle);
    }
}

bool GfMapManager::isMapReady() {
    GfMapManager* manager = get();
    if (manager == nullptr || GfReqSmallCom::isExistCommand(SCOM_TYPE(0x1A))) {
        return false;
    }
    if (manager->m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return manager->m_mapJumpID == 0 || manager->m_mapJumpID == 0xFFFFFFFF;
    }
    if (manager->m_coli.m_coli == nullptr) {
        return false;
    }
    return manager->m_eff.m_lodInit;
}

bool GfMapManager::isExistObj() {
    GfMapManager* manager = get();
    if (manager == nullptr) {
        return false;
    }
    if (manager->m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return true;
    }
    ml::ScnRenderDrSysParmAcc acc;
    return acc.fn_710070A0DC();
}

unsigned int GfMapManager::getMapJumpID() {
    return get()->m_mapJumpID;
}

unsigned int GfMapManager::getMapID() {
    return get()->m_mapID;
}

fw::EffectPack* GfMapManager::getEffectPack() {
    return get()->m_eff.m_pack;
}

void GfMapManager::setEnvTime(unsigned int hour, unsigned int min) {
    fw::RenderParam::setTime(hour, min, fw::CAMERA_TYPE(0));
}

void GfMapManager::setEnvWeather(unsigned int weather) {
    if (weather > 20) {
        weather = 0;
    }
    fw::RenderParam::setWeather(weather, fw::CAMERA_TYPE(0));
}

void GfMapManager::setGlobalIBLReferencePos(const mm::Vec3& pos) {
    if (GfMapManager* manager = get()) {
        manager->m_gibl.setReferencePos(pos);
    }
}

void GfMapManager::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    if (gev == GEV(4)) {
        m_mapJumpID = info.m_mapJumpId;
        m_mapID = info.m_mapId;
    } else if (gev == GEV(2)) {
        if (m_mapID != info.m_mapId) {
            m_eff.destroyEffefct();
        }
    }
}

const char* GfMapManager::getMapName() {
    unsigned int mapID = get()->m_mapID;
    if (mapID != 0) {
        unsigned int nameID = GfBdatMaplist::get()->getMaplistnameID(mapID);
        if (nameID != 0) {
            return GfBdatMsg::getNameMapInfo(nameID);
        }
    }
    return "";
}

void GfMapManager::createWind() {
    mm::Vec3 max;
    mm::Vec3 min;
    idcoli::IDColiAccMan acc;
    if (acc.getGrandAABB(max, min)) {
        m_wind = fw::WindFactory::createWindResource(min, max);
    } else {
        m_wind = fw::WindFactory::createWindResource(mm::Vec3(-10000.0f, -10000.0f, -10000.0f),
                                                     mm::Vec3(10000.0f, 10000.0f, 10000.0f));
    }
    if (fw::WindManager* wind = fw::WindManager::get()) {
        wind->buildWorld(&m_wind->m_resWind);
        wind->setGlobalWind(0);
    }
}

fw::ColiObject* GfMapManager::getColiObject() {
    if (GfMapManager* manager = get()) {
        return manager->m_coli.m_coli;
    }
    return nullptr;
}

void GfMapManager::postUpdate(const fw::UpdateInfo& info) {
    fw::UpdateInfo fieldInfo = info;
    fieldInfo.m_deltaTime = fieldInfo.m_frameTime * GfGameManager::getFieldSpeed(info);
    fieldInfo.m_speed = GfGameManager::getFieldSpeed(info);
    m_eff.update(fieldInfo);
}

void GfMapManager::update(const fw::UpdateInfo& info) {
    float speed = GfGameManager::getFieldSpeed(info);
    GfObjAcc(m_handle).setFrameSpeed(speed);
}

}  // namespace gf
