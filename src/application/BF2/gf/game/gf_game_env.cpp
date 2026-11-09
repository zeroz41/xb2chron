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
#include "classes/gf/GfEvent.h"
#include "classes/gf/IGfEvent.h"
#include "classes/gf/GfObj.h"
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
#include "classes/gf/GfDataAoc.h"
#include "classes/gf/GfBdatShop.h"
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

void GfLayerPause::gevPause(unsigned int prev, unsigned int next) {
    GfLayerPause* self = get();
    if (prev & 1) {
        destroyLayerPause(self->m_eventPause4);
        destroyLayerPause(self->m_eventPause0);
        destroyLayerPause(self->m_eventPause1);
        destroyLayerPause(self->m_eventPause7);
    } else if (next & 1) {
        self->m_eventPause4 = setLayerPause(4);
        self->m_eventPause0 = setLayerPause(0);
        self->m_eventPause1 = setLayerPause(1);
        self->m_eventPause7 = setLayerPause(7);
    }
    if (prev & 0x200) {
        destroyLayerPause(self->m_eventPause10);
    } else if (next & 0x200) {
        self->m_eventPause10 = setLayerPause(10);
    }
}

inline void GfEvent::callLayerPause(unsigned int layer, bool pause) {
    GfEvent* event = get();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevLayerPause(layer, pause);
    }
}

void GfLayerPause::destroyLayerPause(GF_LP_HANDLE*& handle) {
    if (handle == reinterpret_cast<GF_LP_HANDLE*>(-1)) {
        return;
    }
    unsigned long value = reinterpret_cast<unsigned long>(handle);
    unsigned int bit = static_cast<unsigned int>(value) >> 8;
    unsigned int layer = value & 0xFF;
    GfLayerPause* self = get();
    unsigned int* pauses = nullptr;
    switch (layer) {
    case 0:
        pauses = &self->m_layer0Pauses;
        break;
    case 1:
        pauses = &self->m_layer1Pauses;
        break;
    case 4:
        pauses = &self->m_layer4Pauses;
        break;
    case 7:
        pauses = &self->m_layer7Pauses;
        break;
    case 10:
        pauses = &self->m_layer10Pauses;
        break;
    }
    *pauses &= ~(1 << bit);
    if (*pauses == 0) {
        // the layer's group runs again once its last handle is gone
        auto resume = [](unsigned int index) {
            if (fw::Framework::isLayerPause(index)) {
                fw::Framework::setLayerPause(index, false);
                GfObjLayerSpeed::reqApplyModelLayerSpeed(index, 1.0f);
                GfEvent::callLayerPause(index, false);
            }
        };
        resume(layer);
        if (layer != 0) {
            resume(layer + 1);
            resume(layer + 2);
        }
    }
    handle = reinterpret_cast<GF_LP_HANDLE*>(-1);
}

GF_LP_HANDLE* GfLayerPause::setLayerPause(unsigned int layer) {
    GfLayerPause* self = get();
    unsigned int* pauses = nullptr;
    switch (layer) {
    case 0:
        pauses = &self->m_layer0Pauses;
        break;
    case 1:
        pauses = &self->m_layer1Pauses;
        break;
    case 4:
        pauses = &self->m_layer4Pauses;
        break;
    case 7:
        pauses = &self->m_layer7Pauses;
        break;
    case 10:
        pauses = &self->m_layer10Pauses;
        break;
    }
    auto pause = [](unsigned int index) {
        if (!fw::Framework::isLayerPause(index)) {
            fw::Framework::setLayerPause(index, true);
            GfObjLayerSpeed::reqApplyModelLayerSpeed(index, 0.0f);
            GfEvent::callLayerPause(index, true);
        }
    };
    // the first free bit of the group is the handle's
    unsigned int mask = 1;
    for (unsigned int bit = 0; bit < 32; ++bit, mask <<= 1) {
        if ((*pauses & mask) == 0) {
            *pauses |= mask;
            if (layer != 0) {
                pause(layer + 1);
                pause(layer + 2);
            }
            pause(layer);
            return reinterpret_cast<GF_LP_HANDLE*>(static_cast<unsigned long>(layer | (bit << 8)));
        }
    }
    return reinterpret_cast<GF_LP_HANDLE*>(-1);
}

bool GfLayerPause::isLayerPause(unsigned int layer) {
    return fw::Framework::isLayerPause(layer);
}

void GfLayerPause::destroyLayerPause() {
    GfLayerPause* self = get();
    destroyLayerPause(self->m_eventPause4);
    destroyLayerPause(self->m_eventPause0);
    destroyLayerPause(self->m_eventPause1);
    destroyLayerPause(self->m_eventPause7);
    destroyLayerPause(self->m_eventPause10);
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

void GfGameSpeed::updateFrameSpeed(const fw::UpdateInfo& info) {
    bool timed;
    if (m_timer > 0.0f) {
        m_timer -= info.m_deltaTime;
        if (m_timer <= 0.0f) {
            m_timedSpeed = m_speeds[SPEED_LAYER4].m_speed;
            m_timer = 0.0f;
        }
        timed = true;
    } else {
        timed = false;
    }
    if (m_speeds[SPEED_LAYER1].m_dirty || m_speeds[SPEED_LAYER4].m_dirty || m_speeds[SPEED_PLAY].m_dirty || timed) {
        m_speeds[SPEED_LAYER1].m_dirty = false;
        m_speeds[SPEED_LAYER4].m_dirty = false;
        m_speeds[SPEED_PLAY].m_dirty = false;
        m_speeds[SPEED_PLAY].m_applied = m_speeds[SPEED_PLAY].m_speed;
        const float& base0 = timed ? m_timedSpeed : m_speeds[SPEED_LAYER4].m_speed;
        float speed0 = base0 * m_speeds[SPEED_SALVAGE].m_speed * m_speeds[SPEED_PLAY].m_speed;
        if (speed0 <= 0.0f) {
            speed0 = 0.000001f;
        }
        const float& base1 = timed ? m_timedSpeed : m_speeds[SPEED_LAYER1].m_speed;
        float speed1 = base1 * m_speeds[SPEED_FACTOR1B].m_speed * m_speeds[SPEED_FACTOR1].m_speed;
        if (speed1 <= 0.0f) {
            speed1 = 0.000001f;
        }
        fw::Framework::setLayerUpdateSpeed(0, speed0);
        m_speeds[SPEED_LAYER0].m_applied = speed0;
        fw::Framework::setLayerUpdateSpeed(4, speed0);
        m_speeds[SPEED_LAYER4].m_applied = speed0;
        fw::Framework::setLayerUpdateSpeed(5, speed0);
        fw::Framework::setLayerUpdateSpeed(6, speed0);
        fw::Framework::setLayerUpdateSpeed(1, speed1);
        m_speeds[SPEED_LAYER1].m_applied = speed0;  // as the original: layer 1's group runs at speed1
        fw::Framework::setLayerUpdateSpeed(2, speed1);
        fw::Framework::setLayerUpdateSpeed(3, speed1);
    }
    if (m_speeds[SPEED_LAYER7].m_dirty) {
        float speed = m_speeds[SPEED_LAYER7].m_speed * m_speeds[SPEED_SALVAGE_CHARA].m_speed;
        m_speeds[SPEED_LAYER7].m_dirty = false;
        fw::Framework::setLayerUpdateSpeed(7, speed);
        m_speeds[SPEED_LAYER7].m_applied = speed;
        fw::Framework::setLayerUpdateSpeed(8, speed);
        fw::Framework::setLayerUpdateSpeed(9, speed);
    }
    if (m_speeds[SPEED_LAYER10].m_dirty) {
        float speed = m_speeds[SPEED_LAYER10].m_speed * m_speeds[SPEED_FACTOR10].m_speed;
        if (speed <= 0.0f) {
            speed = 0.000001f;
        }
        m_speeds[SPEED_LAYER10].m_dirty = false;
        fw::Framework::setLayerUpdateSpeed(10, speed);
        m_speeds[SPEED_LAYER10].m_applied = speed;
        fw::Framework::setLayerUpdateSpeed(11, speed);
        fw::Framework::setLayerUpdateSpeed(12, speed);
    }
    if (m_speeds[SPEED_LAYER0].m_dirty) {
        float speed =
            m_speeds[SPEED_LAYER0].m_speed * m_speeds[SPEED_FACTOR0].m_speed * m_speeds[SPEED_PLAY].m_speed;
        if (speed <= 0.0f) {
            speed = 0.000001f;
        }
        m_speeds[SPEED_LAYER0].m_dirty = false;
        fw::Framework::setLayerUpdateSpeed(0, speed);
        m_speeds[SPEED_LAYER0].m_applied = speed;
    }
    if (m_speeds[SPEED_GLOBAL].m_dirty) {
        m_speeds[SPEED_GLOBAL].m_applied = m_speeds[SPEED_GLOBAL].m_speed;
        m_speeds[SPEED_GLOBAL].m_dirty = false;
        float speed = m_speeds[SPEED_GLOBAL].m_speed;
        if (speed <= 0.0f) {
            speed = 0.000001f;
        }
        fw::Framework::setUpdateSpeed(speed);
    }
}

void GfGameSpeed::clear() {
    if (get()) {
        get()->m_timedSpeed = 1.0f;
        get()->m_timer = 0.0f;
    }
}

void GfGameSpeed::setLayerSpeed(unsigned int layer, float speed) {
    GfGameSpeed* self = get();
    switch (layer) {  // case 0 last: the original lays its block out to end at the shared return
    case 1:
        self->m_speeds[SPEED_LAYER1].set(speed);
        break;
    case 4:
        self->m_speeds[SPEED_LAYER4].set(speed);
        break;
    case 7:
        self->m_speeds[SPEED_LAYER7].set(speed);
        break;
    case 10:
        self->m_speeds[SPEED_LAYER10].set(speed);
        break;
    case 0:
        self->m_speeds[SPEED_LAYER0].set(speed);
        break;
    }
}

float GfGameSpeed::getLayerSpeed(unsigned int layer) {
    float speed = 1.0f;
    GfGameSpeed* self = get();
    switch (layer) {  // case 0 last: the original lays its block out to end at the shared return
    case 1:
        speed = self->m_speeds[SPEED_LAYER1].m_applied;
        break;
    case 4:
        speed = self->m_speeds[SPEED_LAYER4].m_applied;
        break;
    case 7:
        speed = self->m_speeds[SPEED_LAYER7].m_applied;
        break;
    case 10:
        speed = self->m_speeds[SPEED_LAYER10].m_applied;
        break;
    case 0:
        speed = self->m_speeds[SPEED_LAYER0].m_applied;
        break;
    }
    return speed;
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

void GfGameEnv::setCloudSea(CLOUD_SEA_HANDLE handle, CLOUD_SEA type) {
    GfGameEnv* env = get();
    mm::mtl::FixedQueue<CloudSea, 16>::iterator it =
        mm::mtl::find_if(env->m_cloudSeas.begin(), env->m_cloudSeas.end(),
                         [handle](const CloudSea& sea) { return sea.m_handle == handle; });
    if (it == env->m_cloudSeas.end()) {
        return;
    }
    (*it).m_type = type;
    fw::RenderParam::setCloudSea(env->m_cloudSeas.first().m_type);
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

void GfGameAoc::refreshAocFlag() {
    GfGameFlag::setLocal(1, 0xD781, isExistGameAoc(GAMEAOC(0x10100)));
    GfGameFlag::setLocal(1, 0xD782, isExistGameAoc(GAMEAOC(0x10200)));
    GfGameFlag::setLocal(1, 0xD783, isExistGameAoc(GAMEAOC(0x10300)));
    GfGameFlag::setLocal(1, 0xD784, isExistGameAoc(GAMEAOC(0x10400)));
    GfGameFlag::setLocal(1, 0xD785, isExistGameAoc(GAMEAOC(0x30100)));
    GfGameFlag::setLocal(1, 0xD786, 1);
    GfGameFlag::setLocal(1, 0xD787, isExistGameAoc(GAMEAOC(0x20100)));
}

// the add-on gift items isExistGameAoc knows, in GfBdatShop::getMNU_DlcGiftgetflag's row order (row 0 is none; the
// name is not the original's)
static const unsigned int s_aocGifts[] = {0, 0x40101, 0x40102, 0x40103, 0x40104, 0x40201, 0x40202, 0x40203, 0x40204};

bool GfGameAoc::isExistGameAoc(GAMEAOC id) const {
    AOC_TYPE type = AOC_TYPE((id >> 16) & 0xF);
    int version = GfDataAoc::getContentVersion(type);
    if (version < 0) {
        return false;
    }
    int need = (id >> 8) & 0xFF;
    if (need > version) {
        return false;
    }
    switch (type) {
    case 0:
        return version >= need;
    case 1:
        return version >= need;
    case 2:
        return version >= need;
    case 3:
        return version >= need;
    case 4:
        for (unsigned int i = 0; i < 9; ++i) {
            if (s_aocGifts[i] == id) {
                if (i == 0) {
                    return false;
                }
                unsigned int flag = GfBdatShop::get()->getMNU_DlcGiftgetflag(i);
                if (flag == 0) {
                    return false;
                }
                return GfGameFlag::getLocal(GfDataManager::getDataGame()->m_gameFlag, 1, flag) != 0;
            }
        }
        return false;
    default:
        return false;
    }
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
