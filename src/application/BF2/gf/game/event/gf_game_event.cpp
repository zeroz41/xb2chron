#include "classes/gf/GfGameEvent.h"
#include "classes/event/Manager.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfSound.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfGameEnv.h"
#include "classes/gf/GfLayerPause.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/event/Manager.h"
#include "classes/gf/GfEvtBgm.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfSound.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfGameEnv.h"
#include "classes/gf/GfLayerPause.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfSetupParam.h"
#include "ml/MlMem.h"
#include "mtl/MemManager.h"

#include "classes/fw/EffectManager.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/gf/GfEvtModel.h"
#include "classes/gf/GfInitParamWeapon.h"
#include "classes/gf/GfInitParamNpc.h"
#include "classes/gf/GfInitParamEventObj.h"
#include "classes/gf/GfEvtModelNpc.h"
#include "classes/gf/GfEvtModelWeapon.h"
#include "classes/gf/GfEvtModelEvent.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfBdatChrBl.h"
#include "classes/gf/GfInitParamDriver.h"
#include "classes/gf/GfInitParamBlade.h"
#include "classes/gf/GfInitParamEnemy.h"
#include "classes/gf/GfEvtModelDriver.h"
#include "classes/gf/GfEvtModelBlade.h"
#include "classes/gf/GfEvtModelEnemy.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfPause.h"
#include "gf/GfDataEvent.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfGameFlag.h"
#include "gf/GfPlayFactory.h"
#include "classes/gf/GfMapManager.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfEvtModelSalvage.h"
#include "plugin/Bdat.h"
#include <math.h>

namespace gf {

namespace _gfgev {
// gives a memory back and clears its handle (finalize's two; inlined, so it has no symbol: the name is not the
// original's). Through a reference the two handles load one at a time
inline void eraseMem(mtl::ALLOC_HANDLE& mem) {
    if (mem.m_handle != 0) {
        mtl::MemManager::erase(mem);
        mem = mtl::ALLOC_HANDLE();
    }
}
}  // namespace _gfgev

void GfGameEvent::initialize(const GfSetupParam& param) {
    m_eventMem = mtl::MemManager::create(ml::MlMem::getProductMem(), 0x2300000, "GfTalk", false, mtl::AllocatorType(1),
                                         0x10, "no name", 0);
    if (event::Manager::get() == nullptr) {
        event::Manager::create(param.m_scn);
    }
    for (int i = 0; i < 27; i++) {
        m_disp[i] = true;
    }
    if (GfSound* sound = GfSound::get()) {
        m_categoryHandle = sound->createCategoryHandle();
        m_csCategoryHandle = sound->createCategoryHandle();
    }
    GfEvtBgm::build(param);
    m_fadeInSec = 0.5f;
    m_fadeInWaitSec = 0.0f;
    m_initialized = true;
}

void GfGameEvent::build(const GfSetupParam& param) {
#line 110
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameEvent(param);
}

void GfGameEvent::destroy() {
    GfGameEvent* self = get();
    if (self != nullptr) {
        self->finalize();
        delete self;
    }
}

void GfGameEvent::finalize() {
    m_se.cleanup();
    GfEvtBgm::destroy();
    if (GfSound* sound = GfSound::get()) {
        sound->releaseCategoryHandle(m_categoryHandle);
        sound->releaseCategoryHandle(m_csCategoryHandle);
    }
    if (m_colorFilter != 0) {
        GfGameEnv::destroyColorFilter(m_colorFilter);
        m_colorFilter = CFILTER_HANDLE(0);
    }
    if (event::Manager::get() != nullptr) {
        event::Manager::destroy();
    }
    _gfgev::eraseMem(m_eventMem);
    _gfgev::eraseMem(m_eventMem2);
    m_initialized = false;
}

void GfGameEvent::clear() {
    GfGameEvent* self = get();
    if (self != nullptr) {
        self->m_afterEventStartID = 0;
        self->m_mapjumped = 0;
        GfLayerPause::destroyLayerPause(self->m_layerPause);
        for (int i = 0; i < 27; i++) {
            self->m_disp[i] = true;
        }
        self->m_dispObjects.clear();
    }
}

void GfGameEvent::update(const fw::UpdateInfo& info) {
    if (get() == nullptr || !get()->m_initialized) {
        return;
    }
    event::Manager* manager = event::Manager::get();
    if (manager != nullptr) {
        manager->update();
        manager->tail();
        manager->render();
    }
    mm::mtl::FixedList<GfEvtModel*, 128>& models = get()->m_models;
    for (mm::mtl::FixedList<GfEvtModel*, 128>::iterator it = models.begin(); it != models.end(); ++it) {
        (*it)->update(info);
    }
    if (GfEvtBgm::get() != nullptr) {
        GfEvtBgm::get()->update(info);
    }
    if (get() != nullptr) {
        get()->updateCsEventCategoryVolume();
    }
}

void GfGameEvent::play(unsigned int id, unsigned int mode, unsigned int bladeId, const mm::Vec3& pos, float time) {
    GfGameEvent* self = get();
    event::Manager* manager = event::Manager::get();
    if (self == nullptr || manager == nullptr) {
        return;
    }
    self->m_stop = false;
    unsigned char* list = Bdat::getFP("EVT_listList");
    unsigned int top = Bdat::getIdTop(list);
    unsigned int end = top + Bdat::getIdCount(list);
    for (unsigned int i = top; i < end; i++) {
        unsigned char* fp = Bdat::getFP(reinterpret_cast<const char*>(Bdat::getVal(list, "listSeat", i)));
        unsigned int evtTop = Bdat::getIdTop(fp);
        unsigned int evtEnd = evtTop + Bdat::getIdCount(fp);
        if (evtTop <= id && id < evtEnd) {
            mm::mtl::FixStr<64> name(reinterpret_cast<const char*>(Bdat::getVal(fp, "evtName", id)));
            if (name.m_str[0] == '\0') {
                return;
            }
            if (!manager->isDebugPlayOnetime() && static_cast<unsigned short>(Bdat::getVal(fp, "linkID", id)) != 0) {
                name += "_link";
            }
            Bdat::getVal(fp, "category", id);
            self->m_playEventId = id;
            self->m_playBladeId = bladeId;
            manager->play(name.m_str, reinterpret_cast<GF_OBJ_HANDLE*>(-1), 0, 0, mode, bladeId, pos, time);
            return;
        }
    }
}

void GfGameEvent::postUpdate(const fw::UpdateInfo& info) {
    GfGameEvent* self = get();
    if (self != nullptr && self->m_initialized) {
        event::Manager* manager = event::Manager::get();
        if (manager != nullptr) {
            manager->post();
        }
    }
}

mtl::ALLOC_HANDLE GfGameEvent::getEventMem() {
    if (get() != nullptr) {
        return get()->m_eventMem;
    }
    return mtl::ALLOC_HANDLE();
}

void GfGameEvent::stop() {
    event::Manager* manager = event::Manager::get();
    if (manager != nullptr) {
        manager->stop();
    }
    if (get() != nullptr) {
        get()->m_stop = true;
    }
}

bool GfGameEvent::isPlaying() {
    event::Manager* manager = event::Manager::get();
    if (manager != nullptr) {
        return manager->isPlaying();
    }
    return false;
}

bool GfGameEvent::isStop() {
    if (get() != nullptr) {
        return get()->m_stop;
    }
    return false;
}

int GfGameEvent::getPlayEventId() {
    if (get() != nullptr) {
        return get()->m_playEventId;
    }
    return 0;
}

int GfGameEvent::getPlayBladeId() {
    if (get() != nullptr) {
        return get()->m_playBladeId;
    }
    return 0;
}

void GfGameEvent::setFadeInSec(float waitSec, float sec) {
    if (get() != nullptr) {
        get()->m_fadeInWaitSec = waitSec;
        get()->m_fadeInSec = sec;
    }
}

float GfGameEvent::getFadeInWaitSec() {
    if (get() != nullptr) {
        return get()->m_fadeInWaitSec;
    }
    return 0.0f;
}

float GfGameEvent::getFadeInSec() {
    if (get() != nullptr) {
        return get()->m_fadeInSec;
    }
    return 0.0f;
}

int GfGameEvent::getAfterEventStartID() {
    if (get() != nullptr) {
        return get()->m_afterEventStartID;
    }
    return 0;
}

void GfGameEvent::setAfterEventStartID(int id) {
    if (get() != nullptr) {
        get()->m_afterEventStartID = id;
    }
}

void GfGameEvent::setDisp(EVTDISP disp, bool flag) {
    if (get() != nullptr) {
        get()->m_disp[disp] = flag;
        applySetDisp(disp);
    }
}

void GfGameEvent::applySetDisp(EVTDISP disp) {
    // the gimmick type each display kind 16..26 shows (65 for the kinds below 16, which are object lists); the
    // name is not the original's
    static const unsigned char s_gmkType[27] = {65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65,
                                                65, 65, 28, 31, 34, 9,  13, 15, 37, 38, 50, 51, 35};
    if (disp == 1) {
        applySetDispObject(GfMapManager::getGfObjHandle());
        return;
    }
    if (disp >= 16) {
        unsigned long index = disp;
        if (index - 16 < 11) {
            GfGameUtil::setDispByGmkType(gmk::GmkType(s_gmkType[index]), get() != nullptr ? get()->m_disp[index] : true);
        }
    } else {
        mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>& list = *GfGameObj::getList(disp);
        for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>::iterator it = list.begin(); it != list.end(); ++it) {
            applySetDispObject(*it);
        }
    }
}

void GfGameEvent::setGmkIdDisp(gmk::GmkType type, unsigned int id, bool flag) {
    GfGameUtil::setDispByGmkTypeAndGmkIdx(type, id, flag);
}

void GfGameEvent::setGmkBdatDisp(gmk::GmkType type, unsigned int id, bool flag) {
    GfGameUtil::setDispByGmkTypeAndBdatId(type, id, flag);
}

void GfGameEvent::setMapLodDisp(unsigned int lodId, bool flag) {
    int bdatId = GfFieldLod::get()->findBdatIdByLodId(lodId);
    if (bdatId != 0) {
        GfFieldLod::get()->setFade(bdatId, flag, true);
    }
}

bool GfGameEvent::isMapLodDisp(unsigned int lodId) {
    int bdatId = GfFieldLod::get()->findBdatIdByLodId(lodId);
    if (bdatId != 0) {
        return !GfFieldLod::get()->isFadeOut(bdatId);
    }
    return bdatId;
}

void GfGameEvent::setMapLodAnim(unsigned int lodId, bool flag0, bool flag1) {
    int bdatId = GfFieldLod::get()->findBdatIdByLodId(lodId);
    if (bdatId != 0) {
        GfFieldLod::get()->setAnimReverse(bdatId, flag0, flag1);
    }
}

bool GfGameEvent::isMapLodAnimReverse(unsigned int lodId) {
    int bdatId = GfFieldLod::get()->findBdatIdByLodId(lodId);
    if (bdatId != 0) {
        return GfFieldLod::get()->isAnimReverse(bdatId);
    }
    return false;
}

bool GfGameEvent::isCancelFlag() {
    if (get() != nullptr) {
        return get()->m_flags & 1;
    }
    return false;
}

void GfGameEvent::setCancelFlag(bool flag) {
    if (get() != nullptr) {
        if (flag) {
            get()->m_flags |= 1;
        } else {
            get()->m_flags &= ~1;
        }
    }
}

void GfGameEvent::finishNewGameWait() {
    event::Manager* manager = event::Manager::get();
    if (manager != nullptr) {
        manager->finishNewGameWait();
    }
}

void GfGameEvent::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    if (gev == GEV(6)) {
        event::Manager* manager = event::Manager::get();
        if (manager != nullptr && manager->isPlaying()) {
            get()->m_mapjumped = 1;
        }
    }
}

void GfGameEvent::gevPlayEvent(GEV gev, unsigned int id) {
    switch (gev) {
    case 8:
        if (m_tempWeather != 0) {
            WEATHERID current = GfGameEnv::getTempWeather();
            int mapId = m_tempWeatherMapId;
            GfGameEnv::destroyTempWeather(m_tempWeather);
            m_tempWeather = WEATHER_HANDLE(0);
            m_tempWeatherMapId = 0;
            if (mapId == GfGameManager::getMapID()) {
                GfFieldWeather::setMapWeatherID(current);
            }
        }
        break;
    case 9:
        pad_1914 = id;
        break;
    case 10:
        m_eventPhase = 2;
        if (GfDataEvent::getEventType(id) != 1 && m_mapjumped == 0) {
            m_mapjumped = 1;
        }
        m_playEventId = id;
        pad_1908 = id;
        break;
    case 11: {
        GfDataEvent::getEventType(id);
        if (m_mapjumped == 1) {
            m_mapjumped = 0;
        }
        if (GfManager::isExecModeThater()) {
            break;
        }
        int flag = GfDataEvent::getEventPlayFlag(id);
        if (flag >= 0) {
            GfGameFlag::setLocal(1, flag, 1);
        }
        GfPlayFactory::createEventAfterScript(id);
        break;
    }
    case 12:
        m_eventPhase = 1;
        m_playEventId = id;
        break;
    case 13:
        m_playEventId = 0;
        pad_1914 = 0;
        m_eventPhase = 0;
        m_fadeInWaitSec = 0.0f;
        m_fadeInSec = 0.5f;
        if (m_tempWeather != 0) {
            WEATHERID current = GfGameEnv::getTempWeather();
            int mapId = m_tempWeatherMapId;
            GfGameEnv::destroyTempWeather(m_tempWeather);
            m_tempWeather = WEATHER_HANDLE(0);
            m_tempWeatherMapId = 0;
            if (mapId == GfGameManager::getMapID()) {
                GfFieldWeather::setMapWeatherID(current);
            }
        }
        break;
    default:
        break;
    }
}

void GfGameEvent::playBgm(const EventBgmSetup& setup) {
    EventBgmSetup bgm = setup;
    if (GfPause::isPause(0x40)) {
        bgm.m_noBgm = false;
    }
    if (GfEvtBgm::get() != nullptr) {
        GfEvtBgm::get()->playBgm(bgm);
    }
}

void GfGameEvent::stopBgm(const EventBgmSetup& setup) {
    if (GfEvtBgm::get() != nullptr) {
        GfEvtBgm::get()->stopBgm(setup);
    }
}

void GfGameEvent::cancelOverTime() {
    if (GfEvtBgm::get() != nullptr) {
        GfEvtBgm::get()->cancelOverTime();
    }
}

void GfGameEvent::changeVolume(const EventBgmSetup& setup) {
    if (GfEvtBgm::get() != nullptr) {
        GfEvtBgm::get()->changeBgmVolume(setup);
    }
}

float GfGameEvent::getPlayBgmVolume() {
    float volume = 0.0f;
    GfEvtBgm* bgm = GfEvtBgm::get();
    if (bgm != nullptr && bgm->isPlayBgm()) {
        volume = bgm->m_setup.m_volume;
    }
    return volume;
}

bool GfGameEvent::isPlayBgm() {
    if (GfEvtBgm::get() != nullptr) {
        return GfEvtBgm::get()->isPlayBgm();
    }
    return false;
}

void GfGameEvent::setCategoryVolume(fw::SoundCategory category, float volume, float time) {
    if (get() != nullptr && GfSound::get() != nullptr) {
        GfSound::get()->setCategoryVolume(get()->m_categoryHandle, category, volume, time);
    }
}

float GfGameEvent::getCategoryVolume(fw::SoundCategory category) {
    if (get() != nullptr && GfSound::get() != nullptr) {
        return GfSound::get()->getCategoryVolume(get()->m_categoryHandle, category);
    }
    return 1.0f;
}

void GfGameEvent::createSe(const char* name) {
    if (get() != nullptr) {
        get()->m_se.createSe(name);
    }
}

void GfGameEvent::destroySe() {
    if (get() != nullptr) {
        get()->m_se.destroySe();
    }
}

bool GfGameEvent::isLoadedSe() {
    if (get() != nullptr) {
        return get()->m_se.isLoadedSe();
    }
    return true;
}

void GfGameEvent::setCloudSea(bool on, bool type) {
    GfGameEvent* self = get();
    if (self->m_cloudSea != 0) {
        GfGameEnv::destroyCloudSea(self->m_cloudSea);
        self->m_cloudSea = CLOUD_SEA_HANDLE(0);
    }
    if (on) {
        self->m_cloudSea = GfGameEnv::createCloudSea(CLOUD_SEA(type), CLOUD_SEA_PRIO(2));
    }
}

bool GfGameEvent::isMapWeatherEnable() {
    return get()->m_tempWeather != 0;
}

bool GfGameEvent::isLeaderCharaNG(unsigned int chara) {
    switch (chara) {
    case 0:
    case 5:
    case 7:
    case 8:
    case 9:
        return true;
    default:
        return false;
    }
}

GfGameEvent::~GfGameEvent() {}

int GfGameEvent::getStartEventId() {
    if (get() != nullptr) {
        return get()->pad_1914;
    }
    return 0;
}

void GfGameEvent::setMapLodSwitch(unsigned int lodId, unsigned int switchId) {
    int bdatId = GfFieldLod::get()->findBdatIdByLodId(lodId);
    if (bdatId != 0) {
        GfFieldLod::get()->setLodSwitchId(bdatId, switchId);
    }
}

int GfGameEvent::getMapLodSwitch(unsigned int lodId) {
    int bdatId = GfFieldLod::get()->findBdatIdByLodId(lodId);
    if (bdatId != 0) {
        return GfFieldLod::get()->getLodSwitchId(bdatId);
    }
    return -1;
}

// the parameter names are not the original's: bit 7 of each is the pause flag
void GfGameEvent::gevPause(unsigned int prev, unsigned int now) {
    bool isPaused = (now & 0x80) != 0;
    bool wasPaused = (prev & 0x80) != 0;
    if (!isPaused && !wasPaused) {
        return;
    }
    bool pause = isPaused & !wasPaused;
    fw::EffectManager* manager = fw::EffectManager::get();
    manager->m_categorySpeed[3] = fmaxf(pause ? 0.0f : 1.0f, 1e-5f);
    manager->setMasterPause(pause);
}

void GfGameEvent::destroyPlayingBgm() {
    if (GfEvtBgm* bgm = GfEvtBgm::get()) {
        bgm->clear();
    }
}

float GfGameEvent::getPlayBgmTime() {
    GfEvtBgm* bgm = GfEvtBgm::get();
    if (bgm != nullptr && bgm->isPlayBgm()) {
        return bgm->getPlayBgmTime();
    }
    return 0.0f;
}

float GfGameEvent::getPlayBgmTotalTime() {
    GfEvtBgm* bgm = GfEvtBgm::get();
    if (bgm != nullptr && bgm->isPlayBgm()) {
        return bgm->getTotalBgmTime();
    }
    return 0.0f;
}

void GfGameEvent::setMapWeather(WEATHERID weather) {
    GfGameEvent* self = get();
    if (self->m_tempWeather != 0) {
        WEATHERID current = GfGameEnv::getTempWeather();
        int mapId = self->m_tempWeatherMapId;
        GfGameEnv::destroyTempWeather(self->m_tempWeather);
        self->m_tempWeather = WEATHER_HANDLE(0);
        self->m_tempWeatherMapId = 0;
        if (mapId == GfGameManager::getMapID()) {
            GfFieldWeather::setMapWeatherID(current);
        }
    }
    self->m_tempWeather = GfGameEnv::createTempWeather(weather, WEATHER_PRIO(1));
    self->m_tempWeatherMapId = GfGameManager::getMapID();
}

void GfGameEvent::setWeaType(WEATYPE type) {
    GfGameEvent* self = get();
    if (self != nullptr) {
        self->m_weaType = type;
        self->m_weaTypeWeather = GfFieldWeather::getCurrentMapWeatherID(false);
        if (type != 0) {
            GfFieldWeather::setWeatherForEvent(type, nullptr);
        }
    }
}

void GfGameEvent::resetWeaType() {
    GfGameEvent* self = get();
    if (self != nullptr && self->m_weaType != 0) {
        self->m_weaType = WEATYPE(0);
        GfFieldWeather::setMapWeatherID(self->m_weaTypeWeather);
    }
}

void GfGameEvent::setColorFilter(bool on, int num, int farNum, float time) {
    GfGameEvent* self = get();
    if (self->m_colorFilter != 0) {
        GfGameEnv::destroyColorFilter(self->m_colorFilter);
        self->m_colorFilter = CFILTER_HANDLE(0);
    }
    if (on) {
        ColorFilter filter = {};
        filter.m_num = num;
        filter.m_farNum = farNum;
        filter.m_time = time;
        filter.m_prio = 2;
        self->m_colorFilter = GfGameEnv::createColorFilter(filter);
    }
}

GfEvtModelDriver* GfGameEvent::createDriver(GfInitParamDriver& param) {
    if (!param.pad_1a2 && !GfGameManager::isInMetJIJI()) {
        param.pad_1a2 = true;
    }
    GfEvtModelDriver* model = GfEvtModelDriver::create(param);
    get()->m_models.push_back(model);
    return model;
}

GfEvtModelBlade* GfGameEvent::createBlade(GfInitParamBlade& param) {
    if (param.getBladeID() == 1003 && GfDataBlade::isHomuriNameHikari()) {
        param.m_objId = 1074;
    }
    GfEvtModelBlade* model = GfEvtModelBlade::create(param);
    get()->m_models.push_back(model);
    return model;
}


GfEvtModelNpc* GfGameEvent::createNpc(GfInitParamNpc& param) {
    unsigned char* fp = GfDataBdat::getFP(0xA8);
    if (param.pad_18 == nullptr) {
        param.pad_18 = &fp;
    }
    return GfEvtModelNpc::create(param);
}


GfEvtModelEnemy* GfGameEvent::createEnemy(GfInitParamEnemy& param) {
    unsigned char* fp = GfDataBdat::getFP(0xA5);
    if (param.pad_18 == nullptr) {
        param.pad_18 = &fp;
    }
    GfEvtModelEnemy* model = GfEvtModelEnemy::create(param);
    get()->m_models.push_back(model);
    return model;
}

GfEvtModelWeapon* GfGameEvent::createWeapon(GfInitParamWeapon& param) {
    if (param.pad_12c == 1011 && get() != nullptr && get()->m_playEventId == 10345) {
        param.m_objId = GfBdatChrBl::get()->getChrBlDefWeapon(1011);
    }
    return GfEvtModelWeapon::create(param);
}

GfEvtModelEvent* GfGameEvent::createEventObj(GfInitParamEventObj& param) {
    if (GfGameManager::isFullScreenMenu()) {
        param.pad_40 = GfEvtModel::changeLayerUI(param.pad_40);
    }
    return GfEvtModelEvent::create(param);
}

void GfGameEvent::destroyEvtModel(GfEvtModel* model) {
    GfGameEvent* self = get();
    mm::mtl::FixedList<GfEvtModel*, 128>::iterator it = self->m_models.find(model);
    if (it != self->m_models.end()) {
        self->m_models.erase(it);
    }
}


GfEvtModelSalvage* GfGameEvent::createSalvage() {
    GfInitParamDriver param;
    param.m_createType = 9;
    param.m_objId = 1;
    param.pad_40 = 8;
    return GfEvtModelSalvage::create(param);
}


void GfGameEvent::replaceEquipModel(mm::mtl::FixStr<128>& model) {
    if (get() != nullptr && (get()->m_playEventId == 10498 || get()->m_playEventId == 10494)) {
        if (strstr(model.m_str, "pc000101") != nullptr) {
            const char* driverModel = GfGameUtil::getDriverModel(1, true, true);
            if (driverModel != nullptr && strstr(driverModel, "pc000103") == nullptr) {
                model = "model/";
                model += driverModel;
            }
        }
    }
    if (strstr(model.m_str, "bl000401") != nullptr) {
        model = "model/";
        model += GfGameUtil::getBladeModel(1011, false);
    }
}

}  // namespace gf
