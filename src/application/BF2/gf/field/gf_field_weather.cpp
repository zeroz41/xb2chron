#include "gf/FileStaticVec3.h"
#include "gf/MapjumpCallbackInfo.h"
#include "classes/gf/GfFieldWeather.h"
#include "gf/GfDataBlade.h"
#include "gf/MapjumpCallbackInfo.h"
#include "mm/mtl/FixedList.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/gf/GfGameEnv.h"
#include "gf/WeatherInfo.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfBdatMaplist.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfGameUtilCloudSea.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfManager.h"
#include "gf/GfDataMap.h"
#include "gf/SDataGame.h"
#include "classes/gf/GfMapManager.h"
#include <string.h>

namespace gf {

namespace _gffwt {

mm::mtl::FixedList<WeatherInfo*, 16> s_list;

void destroyList() {
    for (mm::mtl::FixedList<WeatherInfo*, 16>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
        if (*it != nullptr) {
            delete *it;
            *it = nullptr;
        }
    }
    s_list.clear();
}

// the weathers that fade out: every one but the newest
void destroyFadeWeather() {
    // a signed count: the original tests it with b.lt
    while (static_cast<int>(s_list.size()) > 1) {
        if (s_list.front() != nullptr) {
            delete s_list.front();
        }
        s_list.pop_front();
    }
}

// the cloud sea for updateCloudSea to set, when the weather is built (the name is not the original's)
inline void requestCloudSea(CLOUD_SEA cloudSea) {
    if (GfFieldWeather::get() != nullptr) {
        GfFieldWeather::get()->m_cloudSeaRequest = cloudSea != 0 ? 2 : 1;
    }
}

}  // namespace _gffwt

GfFieldWeather::~GfFieldWeather() {}

void GfFieldWeather::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    GfFieldWeather* weather = get();
    weather->m_gevQueue.push_back(gev);
    weather->m_mapjumpInfo = info;
}

void GfFieldWeather::gevGameMapModel(GF_OBJ_HANDLE* handle, bool flag) {}

void GfFieldWeather::gevPause(unsigned int flags0, unsigned int flags1) {
    if (flags1 & 1) {
        for (mm::mtl::FixedList<WeatherInfo*, 16>::iterator it = _gffwt::s_list.begin(); it != _gffwt::s_list.end(); ++it) {
            (*it)->setPause(true);
        }
    }
    if (flags0 & 1) {
        for (mm::mtl::FixedList<WeatherInfo*, 16>::iterator it = _gffwt::s_list.begin(); it != _gffwt::s_list.end(); ++it) {
            (*it)->setPause(false);
        }
    }
}

void GfFieldWeather::setCloudSea(unsigned int map, CLOUD_SEA cloudSea) {
    GfFieldWeather* weather = get();
    weather->m_cloudSeaRequest = cloudSea != 0 ? 2 : 1;
}

void GfFieldWeather::updateCloudSea(const fw::UpdateInfo& info) {
    unsigned int map = GfGameManager::getMapID();
    if (GfGameCond::isGameCond(GfBdatMaplist::get()->getMaplistebb_ON_cndID(map))) {
        if (m_innCloudSea == 0) {
            m_innCloudSea = GfGameEnv::createCloudSea(CLOUD_SEA(1), CLOUD_SEA_PRIO(1));
            GfGameUtilCloudSea::setInnCloudSea(CLOUD_SEA(1));
        }
    } else {
        if (m_innCloudSea != 0) {
            GfGameEnv::destroyCloudSea(m_innCloudSea);
            m_innCloudSea = CLOUD_SEA_HANDLE(0);
            GfGameUtilCloudSea::setInnCloudSea(CLOUD_SEA(0));
        }
        if (m_cloudSeaRequest != 0) {
            GfGameEnv::setCloudSea(m_cloudSea, CLOUD_SEA(m_cloudSeaRequest != 1));
            m_cloudSeaRequest = 0;
        }
    }
}

CLOUD_SEA GfFieldWeather::getCloudSea(unsigned int map) {
    if (map != 0) {
        return CLOUD_SEA(GfDataMap::getWeatherParam(map)->m_cloudSea != 0);
    }
    return GfGameEnv::getCurrentCloudSea();
}

void GfFieldWeather::applyNowMapWeather(unsigned int prevMap, unsigned int map) {
    if (GfGameManager::isStartGame()) {
        return;
    }
    setupGame();
    execChangeWeather(*GfDataMap::getWeatherParam(map));
    _gffwt::requestCloudSea(GfDataMap::getCloudType(map));
    if (map != prevMap) {
        unsigned char play = !GfManager::isExecModeThater();
        if (_gffwt::s_list.size() == 1 && play) {
            WeatherInfo* info = _gffwt::s_list.front();
            info->m_time = info->m_timeMax;
        }
    }
}

void GfFieldWeather::setupGame() {
    GfDataManager::getDataGame();
    GfBdatMaplist* maplist = GfBdatMaplist::get();
    for (unsigned int map = maplist->getMaplistStart(); map < maplist->getMaplistEnd(); map++) {
        WeatherParam* data = GfDataMap::getWeatherParam(map);
        if (data->m_mapId == 0) {
            data = GfDataMap::getEmptyWeatherParam();
            strcpy(data->m_resource, maplist->getMaplistresource(map));
            data->m_mapId = map;
        }
    }
    WeatherParam* data = GfDataMap::getWeatherParam(GfDataMap::getMapID(GfDataManager::getDataGame()->m_skipTravelID));
    _gffwt::requestCloudSea(CLOUD_SEA(data->m_cloudSea));
}

int GfFieldWeather::getCurrentCloudSea() {
    return GfGameEnv::getCurrentCloudSea();
}

void GfFieldWeather::setDispWeather(bool disp) {
    if (get() != nullptr) {
        get()->m_dispWeather = disp;
    }
}

bool GfFieldWeather::isDispWeather() {
    if (get() != nullptr) {
        return get()->m_dispWeather;
    }
    return false;
}

void GfFieldWeather::clear() {
    GfFieldWeather* weather = get();
    _gffwt::destroyList();
    GfMapManager::setEnvWeather(0, 4.0f);
    if (weather->m_innCloudSea != 0) {
        GfGameEnv::destroyCloudSea(weather->m_innCloudSea);
        weather->m_innCloudSea = CLOUD_SEA_HANDLE(0);
    }
}

void GfFieldWeather::build(const GfSetupParam& param) {
#line 1362
    GfFieldWeather* weather = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldWeather();
    _gffwt::destroyList();
    if (weather->m_cloudSea != 0) {
        GfGameEnv::destroyCloudSea(weather->m_cloudSea);
        weather->m_cloudSea = CLOUD_SEA_HANDLE(0);
    }
    weather->m_cloudSea = GfGameEnv::createCloudSea(CLOUD_SEA(0), CLOUD_SEA_PRIO(0));
    weather->m_built = true;
}

void GfFieldWeather::destroy() {
    GfFieldWeather* weather = get();
    if (weather->m_cloudSea != 0) {
        GfGameEnv::destroyCloudSea(weather->m_cloudSea);
        weather->m_cloudSea = CLOUD_SEA_HANDLE(0);
    }
    if (weather->m_innCloudSea != 0) {
        GfGameEnv::destroyCloudSea(weather->m_innCloudSea);
        weather->m_innCloudSea = CLOUD_SEA_HANDLE(0);
    }
    _gffwt::destroyList();
    weather->m_built = false;
    delete weather;
}

void GfFieldWeather::update(const fw::UpdateInfo& info) {
    GfFieldWeather* weather = get();
    weather->updateEvent(info);
    weather->updateWeather(info);
    weather->updateCloudSea(info);
}

}  // namespace gf
