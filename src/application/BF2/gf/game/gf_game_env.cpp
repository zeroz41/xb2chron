#include "classes/gf/GfLayerPause.h"
#include "classes/gf/GfGameSpeed.h"
#include "classes/gf/GfGameEnv.h"
#include "gf/GfSetupParam.h"
#include "gf/GfDataBlade.h"
#include "gf/MapjumpCallbackInfo.h"
#include "nn/oe.h"
#include "classes/fw/CameraLayer.h"
#include "classes/fw/CameraManager.h"
#include "classes/fw/Framework.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfLayerPause.h"
#include "classes/gf/GfGameSpeed.h"
#include "classes/gf/GfGameEnv.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfMapManager.h"
#include "fw/RenderParam.h"
#include "fw/UpdateInfo.h"
#include "gf/GfDataBlade.h"
#include "gf/GfSetupParam.h"
#include "gf/MapjumpCallbackInfo.h"
#include "gf/SDataGame.h"
#include "gf/gf_data_aoc.h"
#include "nn/oe.h"
#include "gf/GfDataUtil.h"

namespace gf {

GfLayerPause::~GfLayerPause() {}

GfGameSpeed::~GfGameSpeed() {}

GfGameEnv::~GfGameEnv() {}

void GfLayerPause::build(const GfSetupParam& param) {
#line 116
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfLayerPause();
}

void GfLayerPause::destroy() {
    GfLayerPause* pause = get();
    pause->m_valid = false;
    delete pause;
}

bool GfLayerPause::isLayerPause(unsigned int layer) {
    return fw::Framework::isLayerPause(layer);
}

GfGameSpeed::GfGameSpeed(const GfSetupParam& param) : m_timedSpeed(1.0f), m_timer(0.0f) {
    m_valid = true;
}

void GfGameSpeed::setGlobalSpeed(float speed) {
    get()->m_speeds[SPEED_GLOBAL].set(speed);
}

void GfGameSpeed::destroy() {
    GfGameSpeed* speed = get();
    speed->m_valid = false;
    delete speed;
}

void GfGameSpeed::update(const fw::UpdateInfo& info) {
    if (get()) {
        get()->updateFrameSpeed(info);
    }
}

void GfGameSpeed::clear() {
    if (get()) {
        get()->m_timedSpeed = 1.0f;
        get()->m_timer = 0.0f;
    }
}

void GfGameSpeed::setPlaySpeed(float speed) {
    get()->m_speeds[SPEED_PLAY].set(speed);
}

float GfGameSpeed::getPlaySpeed() {
    if (get()) {
        return get()->m_speeds[SPEED_PLAY].m_applied;
    }
    return 0.0f;
}

void GfGameSpeed::setSalvageSpeed(float speed) {
    GfGameSpeed* self = get();
    self->m_speeds[SPEED_SALVAGE].m_speed = speed;
    self->m_speeds[SPEED_LAYER4].m_dirty = true;
    self->m_speeds[SPEED_SALVAGE_CHARA].m_speed = speed;
    self->m_speeds[SPEED_LAYER7].m_dirty = true;
}

void GfGameSpeed::setSalvageCharacterSpeed(float speed) {
    GfGameSpeed* self = get();
    self->m_speeds[SPEED_SALVAGE_CHARA].m_speed = speed;
    self->m_speeds[SPEED_LAYER7].m_dirty = true;
}

void GfGameEnv::clear() {
    GfGameEnv* env = get();
    env->m_mapjump = false;
    env->m_mapjumpEnd = false;
    env->m_mapjumpWithSaveData = false;
    env->m_mapID = 0;
    env->m_mapJumpID = 0;
    env->m_fadeTimer = 0.0f;
    env->m_colorFilterSerial = 1;
    env->m_cloudSeaSerial = 1;
    env->m_weatherSerial = 1;
    env->m_room = 0;
    env->m_screenShotWait = 0;
    nn::oe::EnableScreenShot();
}

void GfGameEnv::build(const GfSetupParam& param) {
#line 732
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameEnv();
    clear();
}

void GfGameEnv::destroy() {
    if (get()) {
        delete get();
    }
}

bool GfGameEnv::isMapjump() {
    return get()->m_mapjump;
}

bool GfGameEnv::isMapjumpWithSaveData() {
    if (get()) {
        return get()->m_mapjumpWithSaveData;
    }
    return false;
}

unsigned int GfGameEnv::getMapJumpID() {
    return get()->m_mapJumpID;
}

int GfGameEnv::getMapID() {
    return get()->m_mapID;
}

void GfGameEnv::setMapID(unsigned int jumpID, unsigned int mapID) {
    GfGameEnv* env = get();
    env->m_mapID = mapID;
    env->m_mapJumpID = jumpID;
}

CFILTER_HANDLE GfGameEnv::createColorFilter(const ColorFilter& filter) {
    GfGameEnv* env = get();
    ColorFilter entry = filter;
    CFILTER_HANDLE handle = CFILTER_HANDLE((env->m_colorFilters.size() + 1) | (env->m_colorFilterSerial << 8));
    ++env->m_colorFilterSerial;
    entry.m_handle = handle;
    for (mm::mtl::FixedQueue<ColorFilter, 16>::iterator it = env->m_colorFilters.begin(); it != env->m_colorFilters.end(); ++it) {
        if ((*it).m_prio <= entry.m_prio) {
            env->m_colorFilters.insert(it, entry);
            goto found;
        }
    }
    env->m_colorFilters.push_front(entry);
found:
    fw::RenderParam::setColorFilter(env->m_colorFilters.first().m_num, env->m_colorFilters.first().m_farNum,
                                    env->m_colorFilters.first().m_time, fw::CAMERA_TYPE(0));
    return entry.m_handle;
}

void GfGameEnv::destroyColorFilter(CFILTER_HANDLE handle) {
    GfGameEnv* env = get();
    mm::mtl::FixedQueue<ColorFilter, 16>::iterator it =
        mm::mtl::find_if(env->m_colorFilters.begin(), env->m_colorFilters.end(),
                         [handle](const ColorFilter& filter) { return filter.m_handle == handle; });
    if (it == env->m_colorFilters.end()) {
        return;
    }
    if ((*it).m_handle == env->m_colorFilters.first().m_handle) {
        env->m_colorFilters.pop();
        if (!env->m_colorFilters.empty()) {
            fw::RenderParam::setColorFilter(env->m_colorFilters.front().m_num, env->m_colorFilters.front().m_farNum,
                                            env->m_colorFilters.front().m_time, fw::CAMERA_TYPE(0));
        } else {
            fw::RenderParam::resetColorFilter(1.0f, fw::CAMERA_TYPE(0));
        }
    } else {
        env->m_colorFilters.erase(it);
    }
}

CLOUD_SEA_HANDLE GfGameEnv::createCloudSea(CLOUD_SEA type, CLOUD_SEA_PRIO prio) {
    GfGameEnv* env = get();
    CloudSea sea;
    sea.m_type = type;
    sea.m_prio = prio;
    CLOUD_SEA_HANDLE handle = CLOUD_SEA_HANDLE((env->m_cloudSeas.size() + 1) | (env->m_cloudSeaSerial << 8));
    ++env->m_cloudSeaSerial;
    sea.m_handle = handle;
    for (mm::mtl::FixedQueue<CloudSea, 16>::iterator it = env->m_cloudSeas.begin(); it != env->m_cloudSeas.end(); ++it) {
        if ((*it).m_prio <= prio) {
            env->m_cloudSeas.insert(it, sea);
            goto found;
        }
    }
    env->m_cloudSeas.push_front(sea);
found:
    fw::RenderParam::setCloudSea(type);
    return sea.m_handle;
}

void GfGameEnv::destroyCloudSea(CLOUD_SEA_HANDLE handle) {
    GfGameEnv* env = get();
    mm::mtl::FixedQueue<CloudSea, 16>::iterator it =
        mm::mtl::find_if(env->m_cloudSeas.begin(), env->m_cloudSeas.end(),
                         [handle](const CloudSea& sea) { return sea.m_handle == handle; });
    if (it == env->m_cloudSeas.end()) {
        return;
    }
    if ((*it).m_handle == env->m_cloudSeas.first().m_handle) {
        env->m_cloudSeas.pop();
        fw::RenderParam::setCloudSea(env->m_cloudSeas.empty() ? CLOUD_SEA(0) : env->m_cloudSeas.front().m_type);
    } else {
        env->m_cloudSeas.erase(it);
    }
}

CLOUD_SEA GfGameEnv::getCurrentCloudSea() {
    GfGameEnv* env = get();
    if (!env->m_cloudSeas.empty()) {
        return env->m_cloudSeas.front().m_type;
    }
    return CLOUD_SEA(0);
}

void GfGameEnv::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    GfGameEnv* env = get();
    switch (gev) {
    case GEV(1):
        env->m_mapjump = true;
        env->m_mapjumpWithSaveData = info.m_withSaveData;
        break;
    case GEV(2):
        env->m_mapjumpEnd = true;
        break;
    case GEV(5):
        env->m_fadeTimer = info.m_jumpKind == 1 ? 0.0f : 3.0f;
        break;
    case GEV(6):
        env->m_mapjump = false;
        env->m_mapjumpEnd = false;
        env->m_mapjumpWithSaveData = false;
        if (!GfGameManager::isEvent(false)) {
            nn::oe::DisableScreenShot();
            env->m_screenShotWait = 180;
        }
        break;
    default:
        break;
    }
}

void GfGameEnv::gevPlayEvent(GEV gev, unsigned int id) {}

void GfGameEnv::gevGameState(GF_STATE prev, GF_STATE next) {
    switch (next) {
    case GF_STATE(2):
        fw::RenderParam::setMotionBlur(false, fw::CAMERA_TYPE(0));
        break;
    case GF_STATE(3):
        if (!GfManager::isExecModeAdvertize()) {
            fw::RenderParam::setMotionBlur(true, fw::CAMERA_TYPE(0));
        }
        break;
    default:
        break;
    }
}

void GfGameEnv::update(const fw::UpdateInfo& info) {
    GfGameEnv* env = get();
    if (!env->m_mapjump && env->m_fadeTimer > 0.0f) {
        env->m_fadeTimer -= info.m_deltaTime;
        if (env->m_fadeTimer < 0.0f) {
            env->m_fadeTimer = 0.0f;
        }
    }
    {
        mm::Vec3 pos = fw::CameraManager::get()->m_layers[0].getCameraPosition();
        if (!get()->m_mapjumpEnd) {
            if (fw::RenderParam::isRoom(pos, fw::CAMERA_TYPE(0))) {
                if (env->m_room <= 0) {
                    env->m_room = 1;
                } else if (env->m_room < 99) {
                    env->m_room++;
                }
            } else {
                if (env->m_room >= 0) {
                    env->m_room = -1;
                } else if (env->m_room > -99) {
                    env->m_room--;
                }
            }
        }
    }
    if (fw::CameraManager::get()) {
        GfMapManager::setGlobalIBLReferencePos(fw::CameraManager::get()->m_layers[0].getCameraPosition());
    }
    if (!env->m_colorFilters.empty()) {
        ColorFilter& filter = env->m_colorFilters.back();
        fw::RenderParam::setColorFilter(filter.m_num, filter.m_farNum, filter.m_time, fw::CAMERA_TYPE(0));
    }
    if (env->m_screenShotWait != 0 && --env->m_screenShotWait == 0) {
        nn::oe::EnableScreenShot();
    }
}

bool GfGameEnv::isRoom() {
    return get()->m_room > -3;
}

void GfGameEnv::sendPlayerPositionToRender(const mm::Vec3& pos) {
    fw::RenderParam::setPlayerPosition(pos, fw::CAMERA_TYPE(0));
}

WEATHER_HANDLE GfGameEnv::createTempWeather(WEATHERID weather, WEATHER_PRIO prio) {
    GfGameEnv* env = get();
    WeatherSet set;
    set.m_weather = weather;
    set.m_prio = prio;
    WEATHER_HANDLE handle = WEATHER_HANDLE((env->m_weathers.size() + 1) | (env->m_weatherSerial << 8));
    ++env->m_weatherSerial;
    set.m_handle = handle;
    for (mm::mtl::FixedQueue<WeatherSet, 16>::iterator it = env->m_weathers.begin(); it != env->m_weathers.end(); ++it) {
        if ((*it).m_prio <= prio) {
            env->m_weathers.insert(it, set);
            return set.m_handle;
        }
    }
    env->m_weathers.push_front(set);
    return set.m_handle;
}

void GfGameEnv::destroyTempWeather(WEATHER_HANDLE handle) {
    GfGameEnv* env = get();
    mm::mtl::FixedQueue<WeatherSet, 16>::iterator it =
        mm::mtl::find_if(env->m_weathers.begin(), env->m_weathers.end(),
                         [handle](const WeatherSet& set) { return set.m_handle == handle; });
    if (it != env->m_weathers.end()) {
        env->m_weathers.erase(it);
    }
}

WEATHERID GfGameEnv::getTempWeather() {
    GfGameEnv* env = get();
    if (!env->m_weathers.empty()) {
        return env->m_weathers.front().m_weather;
    }
    return WEATHERID(0);
}

void GfGameAoc::setupGame(GAME_TYPE mode) {
    GfDataUtil::setIra(*GfDataManager::getDataGame(), mode == 1);
    m_mode = mode;
    refreshAocFlag();
}

void GfGameAoc::build(const GfSetupParam& param) {
#line 1258
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameAoc();
}

void GfGameAoc::destroy() {
    delete get();
}

void GfGameAoc::gevChangeAocFlag(unsigned int id) {
    if (id < 35353) {
        return;
    }
    refreshAocFlag();
}

}  // namespace gf
