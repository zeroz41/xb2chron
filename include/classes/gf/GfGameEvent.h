#ifndef CLASSES_GF_GFGAMEEVENT_H
#define CLASSES_GF_GFGAMEEVENT_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfEvtSe.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/FixedVector.h"
#include "mtl/AllocHandle.h"

namespace gf { class GfGameEvent; }
namespace mm { class Vec3; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { class GfSetupParam; class GfEvtModel; class EventBgmSetup; class GF_OBJ_HANDLE; class GF_SE_CATEGORY_HANDLE; }
namespace gf { enum WEATHERID : int; enum WEATYPE : int; enum CFILTER_HANDLE : int; enum CLOUD_SEA_HANDLE : int; enum WEATHER_HANDLE : int; class GF_LP_HANDLE; }
namespace gmk { enum GmkType : int; }
namespace fw { enum SoundCategory : int; }

namespace fw { class UpdateInfo; }
namespace gf {
// what an event shows: GfGameEvent::setDisp(EVTDISP, bool) keeps one flag per kind (27 of them, initialize sets
// them all); the enumerators are not known
enum EVTDISP : unsigned int {};

// table 0x7100B54448
class GfGameEvent : public ::mm::mtl::PtrSingleton< ::gf::GfGameEvent> {
public:
    static void postUpdate(const fw::UpdateInfo& info);
    static void finishNewGameWait();
    static void stop();
    // shows the object as the running events' display settings ask (GfGameObj::addInObj, listenerGfObj)
    static void applySetDispObject(GF_OBJ_HANDLE* handle);
    // 2.0.0's symbols name it. A static member: its unit is gf_game_event and it reads GfGameEvent's and
    // event::Manager's instances. What it does: finds the event id in EVT_listList's sheets, builds its evtName
    // (+ "_link" when linkID is set and debug one-time play is off), stores the id and third argument at
    // GfGameEvent+0x190C/0x1910 and starts the event; GfPlayComEvent::start passes its three ids, m_pos and m_time
    // (in s0).
    static void play(unsigned int id, unsigned int, unsigned int, const mm::Vec3& pos, float time);
    static void gevPause(unsigned int, unsigned int);
    // 2.0.0's symbols name it. What it does: returns the int at +0x1914 (pad_1914), 0 without an instance (the same
    // shape as getPlayBladeId one field later); gf::GfGameUtil::getDriverModel, GfGameUtil::getAcceDriverModel and GfGameUtil::dispSinMask call it.
    static int getStartEventId();
    // 2.0.0's symbols name it. What it does: GfFieldLod::findBdatIdByLodId(lodId), then (when found)
    // GfFieldLod::setLodSwitchId(bdatId, switchId); event::LodManager::OnEventProc calls it.
    static void setMapLodSwitch(unsigned int lodId, unsigned int switchId);
    // 2.0.0's symbols name it. What it does: GfFieldLod::findBdatIdByLodId(lodId), then (when found) returns
    // GfFieldLod::getLodSwitchId(bdatId) (the model's switch id), else -1; event::LodManager::playAnm calls it.
    static int getMapLodSwitch(unsigned int lodId);
    // 2.0.0's symbols name it. What it does: GfEvtBgm::get()->clear() when the instance exists;
    // GfPlayComEventFade::update calls it.
    static void destroyPlayingBgm();
    static float getPlayBgmTime();
    static float getPlayBgmTotalTime();
    // an event's color filter request (priority 2) to GfGameEnv; false drops it
    static void setColorFilter(bool on, int num, int farNum, float time);
    static class GfEvtModelDriver* createDriver(class GfInitParamDriver& param);
    static class GfEvtModelBlade* createBlade(class GfInitParamBlade& param);
    static class GfEvtModelNpc* createNpc(class GfInitParamNpc& param);
    static class GfEvtModelEnemy* createEnemy(class GfInitParamEnemy& param);
    // 2.0.0's symbols name it. What it does: GfEvtModelWeapon::create(param), first giving blade 1011 (param+0x12c) its
    // GfBdatChrBl::getChrBlDefWeapon(1011) as m_objId while event 10345 (m_playEventId) plays.
    static class GfEvtModelWeapon* createWeapon(class GfInitParamWeapon& param);
    static class GfEvtModelEvent* createEventObj(class GfInitParamEventObj& param);
    static void setMapWeather(WEATHERID weather);
    static void setWeaType(WEATYPE type);
    static void resetWeaType();
    virtual ~GfGameEvent();  // slot 0
    static void setCancelFlag(bool flag);
    static bool isCancelFlag();
    static void setAfterEventStartID(int id);
    static int getAfterEventStartID();
    static mtl::ALLOC_HANDLE getEventMem();
    static bool isPlaying();
    static bool isStop();
    // GfEvtModel::destroy hands it the model first
    // the event playing now (GfEvtModelBlade::create asks)
    static int getPlayEventId();
    static int getPlayBladeId();
    // the event's fade-in: the wait before it and its length, in seconds
    static void setFadeInSec(float waitSec, float sec);
    static float getFadeInWaitSec();
    static float getFadeInSec();
    static void setDisp(EVTDISP disp, bool flag);
    static void applySetDisp(EVTDISP disp);
    static void setGmkIdDisp(gmk::GmkType type, unsigned int id, bool flag);
    static void setGmkBdatDisp(gmk::GmkType type, unsigned int id, bool flag);
    static void setMapLodDisp(unsigned int lodId, bool flag);
    static bool isMapLodDisp(unsigned int lodId);
    static void setMapLodAnim(unsigned int lodId, bool flag0, bool flag1);
    static bool isMapLodAnimReverse(unsigned int lodId);
    static void playBgm(const EventBgmSetup& setup);
    static void stopBgm(const EventBgmSetup& setup);
    static void cancelOverTime();
    static void changeVolume(const EventBgmSetup& setup);
    static bool isPlayBgm();
    static float getPlayBgmVolume();
    static void setCategoryVolume(fw::SoundCategory category, float volume, float time);
    static float getCategoryVolume(fw::SoundCategory category);
    static void createSe(const char* name);
    static void destroySe();
    static bool isLoadedSe();
    static void setCloudSea(bool on, bool type);
    static bool isMapWeatherEnable();
    static bool isLeaderCharaNG(unsigned int chara);
    static void build(const GfSetupParam& param);
    static void destroy();
    void initialize(const GfSetupParam& param);
    void finalize();
    static void destroyEvtModel(class GfEvtModel* model);
    // a new salvage model (GfGameSalvage::createModel keeps it)
    static class GfEvtModelSalvage* createSalvage();
    static void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);
    static void clear();
    void gevPlayEvent(gf::GEV gev, unsigned int id);

    // build constructs it (no constructor of its own in the symbols)
    GfGameEvent(const GfSetupParam& param)
        : m_flags(0), m_initialized(false), m_eventMem(), m_eventMem2(), m_afterEventStartID(0), m_mapjumped(0),
          m_layerPause(reinterpret_cast<GF_LP_HANDLE*>(-1)), m_colorFilter(CFILTER_HANDLE(0)), m_cloudSea(CLOUD_SEA_HANDLE(0)),
          m_tempWeather(WEATHER_HANDLE(0)), m_tempWeatherMapId(0), m_weaType(WEATYPE(0)), m_weaTypeWeather(WEATHERID(5)), pad_1908(0), m_playEventId(0),
          m_playBladeId(0), pad_1914(0), m_eventPhase(0), m_categoryHandle(reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(-1)),
          m_csCategoryHandle(reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(-1)), m_csEventMute(false), m_stop(false),
          m_fadeInWaitSec(0.0f), m_fadeInSec(0.0f) {
        initialize(param);
    }

    // the names are not the original's unless a function above says so
    unsigned int m_flags;  // bit 0: setCancelFlag's
    bool m_initialized;  // initialize sets it, finalize clears it
    mtl::ALLOC_HANDLE m_eventMem;  // initialize's "GfTalk" memory (getEventMem returns it)
    mtl::ALLOC_HANDLE m_eventMem2;  // finalize erases it too
    int m_afterEventStartID;  // setAfterEventStartID's
    int m_mapjumped;  // gevMapjump sets it for GEV 6 while an event plays
    GF_LP_HANDLE* m_layerPause;  // clear hands it to GfLayerPause::destroyLayerPause
    bool m_disp[27];  // setDisp(EVTDISP)'s flags
    unsigned char pad_43[5];
    mm::mtl::FixedVector<unsigned int, 1024> m_dispObjects;  // clear empties it
    mm::mtl::FixedList<GfEvtModel*, 128> m_models;  // update runs each model
    CFILTER_HANDLE m_colorFilter;  // setColorFilter's GfGameEnv filter
    CLOUD_SEA_HANDLE m_cloudSea;  // setCloudSea's GfGameEnv cloud sea
    WEATHER_HANDLE m_tempWeather;  // setMapWeather's GfGameEnv weather
    int m_tempWeatherMapId;  // the map setMapWeather set it on
    WEATYPE m_weaType;  // setWeaType's
    WEATHERID m_weaTypeWeather;  // the map weather setWeaType found (resetWeaType goes back to it)
    int pad_1908;
    int m_playEventId;  // getPlayEventId's
    int m_playBladeId;  // getPlayBladeId's
    int pad_1914;
    // the name is not the original's: SCOM_QUEST_REACH::exec waits (in GF_STATE 20) until it is 2 or more
    // (1.0.0 read it at 0x1914)
    int m_eventPhase;
    GF_SE_CATEGORY_HANDLE* m_categoryHandle;  // setCategoryVolume's GfSound category handle
    GF_SE_CATEGORY_HANDLE* m_csCategoryHandle;  // updateCsEventCategoryVolume's
    bool m_csEventMute;  // updateCsEventCategoryVolume mutes category 13 while it is set
    bool m_stop;  // stop sets it, isStop returns it
    GfEvtSe m_se;  // createSe, destroySe and isLoadedSe forward to it
    float m_fadeInWaitSec;  // setFadeInSec's first
    float m_fadeInSec;  // setFadeInSec's second
};
}  // namespace gf

#endif
