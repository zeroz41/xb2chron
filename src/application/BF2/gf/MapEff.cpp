#include "gf/MapEff.h"
#include "gf/GfSetupParam.h"
#include "classes/fw/EffectPack.h"
#include "classes/fw/EffectLodManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/ColiObject.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfManager.h"
#include "classes/ml/Scn.h"
#include "classes/fw/NaviManager.h"
#include "classes/gf/GfAssetResource.h"
#include "classes/ml/ScnObjIBL.h"
#include "fw/UpdateInfo.h"
#include "math.h"

namespace gf {

MapEff::~MapEff() {}

void MapEff::create(GF_ASSET_HANDLE* handle, fw::ModelObject* model) {
    if (handle == reinterpret_cast<GF_ASSET_HANDLE*>(-1)) {
        return;
    }
    GfAssetResource* resource = GfAssetManager::getResource(handle, GfFileIdx(6), GfAssetType(0));
    if (resource != nullptr && m_pack == nullptr) {
        m_pack = fw::EffectPack::createFromMemory(resource->getAssetData(), resource->getAssetSize(),
                                                  resource->getAssetName(), false);
    }
    if (!m_lodInit) {
        fw::EffectLodManager::get()->init(model, m_pack);
        m_lodInit = true;
    }
}

void MapEff::destroy() {
    if (m_lodInit) {
        fw::EffectLodManager::get()->term();
        m_lodInit = false;
    }
    if (m_pack != nullptr) {
        m_pack->release();
        m_pack = nullptr;
    }
}

void MapEff::destroyEffefct() {
    if (m_lodInit) {
        fw::EffectLodManager::get()->term();
        m_lodInit = false;
    }
}

void MapEff::update(const fw::UpdateInfo& info) {
    if (m_lodInit) {
        fw::EffectLodManager::get()->update(info);
    }
    fw::EffectManager* manager = fw::EffectManager::get();
    manager->m_categorySpeed[1] = fmaxf(info.m_speed, 1e-5f);
}

MapNavi::~MapNavi() {}

void MapNavi::create(GF_ASSET_HANDLE* handle) {
    if (m_created) {
        return;
    }
    if (GfAssetResource* resource = GfAssetManager::getResource(handle, GfFileIdx(2), GfAssetType(0))) {
        m_created = fw::NaviManager::get()->createNaviMesh(resource->getAssetData(), resource->getAssetName());
    }
}

void MapNavi::destroy() {
    if (m_created) {
        fw::NaviManager::get()->releaseNaviMesh();
        m_created = false;
    }
}

MapColi::~MapColi() {}

void MapColi::create(GF_ASSET_HANDLE* handle) {
    if (m_coli != nullptr) {
        return;
    }
    if (GfAssetResource* resource = GfAssetManager::getResource(handle, GfFileIdx(1), GfAssetType(0))) {
        m_coli = fw::ColiObject::createColiGrand(resource->getAssetData());
    }
}

void MapColi::destroy() {
    if (m_coli != nullptr) {
        m_coli->release();
        m_coli = nullptr;
    }
}

MapGIBL::~MapGIBL() {}

void MapGIBL::create(GF_ASSET_HANDLE* handle) {
    if (m_ibl != nullptr) {
        return;
    }
    if (GfAssetResource* resource = GfAssetManager::getResource(handle, GfFileIdx(7), GfAssetType(0))) {
        m_ibl = GfManager::getSetupParam().m_scn->createIBL(resource->getAssetData(), 0);
    }
}

void MapGIBL::destroy() {
    if (m_ibl != nullptr) {
        GfManager::getSetupParam().m_scn->releaseItem(m_ibl);
        m_ibl = nullptr;
    }
}

void MapGIBL::setReferencePos(const mm::Vec3& pos) {
    if (m_ibl != nullptr) {
        m_ibl->setReferencePos(pos);
    }
}

MapLIBL::~MapLIBL() {}

void MapLIBL::create(GF_ASSET_HANDLE* handle) {
    if (m_lgt != nullptr) {
        return;
    }
    if (GfAssetResource* resource = GfAssetManager::getResource(handle, GfFileIdx(8), GfAssetType(0))) {
        m_lgt = GfManager::getSetupParam().m_scn->createLgt(resource->getAssetData(), 0);
    }
}

void MapLIBL::destroy() {
    if (m_lgt != nullptr) {
        GfManager::getSetupParam().m_scn->releaseItem(m_lgt);
        m_lgt = nullptr;
    }
}

}  // namespace gf
