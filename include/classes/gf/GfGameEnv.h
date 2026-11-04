#ifndef CLASSES_GF_GFGAMEENV_H
#define CLASSES_GF_GFGAMEENV_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedQueue.h"

namespace mm { class Vec3; }
namespace fw { class UpdateInfo; }

namespace gf { class GfGameEnv; }
namespace gf {
// the handles GfGameEnv's create functions return (GfGameEvent keeps them, 0 for none)
enum CFILTER_HANDLE : int;
enum CLOUD_SEA_HANDLE : int;
enum CLOUD_SEA : int;
enum CLOUD_SEA_PRIO : int;
enum WEATHERID : int;
enum WEATHER_PRIO : int;
enum WEATHER_HANDLE : int;
// the game type GfGameAoc::setupGame takes (1: the mode GfGameManager::isGameTypeIra tests); 2.0.0's symbols name it
enum GAME_TYPE : int {};
// an encoded add-on item GfGameAoc::isExistGameAoc answers for (kind = bits 16-19, needed count = bits 8-15); 2.0.0's
// symbols name it
enum GAMEAOC : unsigned int {};
class GfSetupParam;

// a color filter request: createColorFilter's argument and GfGameEnv's queue entry, highest m_prio first; update
// hands the last one to fw::RenderParam::setColorFilter (the field names are not the original's)
struct ColorFilter {
    int m_num;
    int m_farNum;
    float m_time;
    CFILTER_HANDLE m_handle;  // createColorFilter sets it: (count + 1) | (serial << 8)
    int m_prio;
};
// a cloud sea request (createCloudSea's queue entry; the field names are not the original's)
struct CloudSea {
    CLOUD_SEA m_type;
    CLOUD_SEA_PRIO m_prio;
    CLOUD_SEA_HANDLE m_handle;  // (count + 1) | (serial << 8)
};
// a temporary weather request (createTempWeather's queue entry; the field names are not the original's)
struct WeatherSet {
    WEATHERID m_weather;
    WEATHER_PRIO m_prio;
    WEATHER_HANDLE m_handle;  // (count + 1) | (serial << 8)
};
}
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// table 0x7100B54838
class GfGameEnv : public ::mm::mtl::PtrSingleton< ::gf::GfGameEnv> {
public:
    GfGameEnv() {}
    virtual ~GfGameEnv();  // slot 0
    static void clear();
    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isMapjump();
    static bool isMapjumpWithSaveData();
    static unsigned int getMapJumpID();
    static int getMapID();
    static void setMapID(unsigned int jumpID, unsigned int mapID);
    static CFILTER_HANDLE createColorFilter(const ColorFilter& filter);
    static void destroyColorFilter(CFILTER_HANDLE handle);  // GfGameEvent::finalize's
    static CLOUD_SEA_HANDLE createCloudSea(CLOUD_SEA type, CLOUD_SEA_PRIO prio);
    static void destroyCloudSea(CLOUD_SEA_HANDLE handle);
    static void setCloudSea(CLOUD_SEA_HANDLE handle, CLOUD_SEA type);
    static CLOUD_SEA getCurrentCloudSea();  // 0 without a request
    static void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);
    static void gevPlayEvent(gf::GEV gev, unsigned int id);
    static void gevGameState(GF_STATE prev, GF_STATE next);
    static void update(const fw::UpdateInfo& info);
    static bool isRoom();
    static void sendPlayerPositionToRender(const mm::Vec3& pos);
    static WEATHER_HANDLE createTempWeather(WEATHERID weather, WEATHER_PRIO prio);
    static void destroyTempWeather(WEATHER_HANDLE handle);
    static WEATHERID getTempWeather();  // 0 without a request

    // the field names are not the original's
    bool m_mapjump;              // 0x8: gevMapjump's GEV 1 sets it, GEV 6 clears it
    bool m_mapjumpEnd;           // 0x9: gevMapjump's GEV 2 sets it; update keeps the room count while it is set
    bool m_mapjumpWithSaveData;  // 0xA: MapjumpCallbackInfo's flag at 0xC on GEV 1
    int m_mapID;                 // 0xC
    unsigned int m_mapJumpID;    // 0x10
    float m_fadeTimer;           // 0x14: gevMapjump's GEV 5 sets 0 or 3; update counts it down outside a map jump
    mm::mtl::FixedQueue<ColorFilter, 16> m_colorFilters;  // 0x18
    unsigned long m_colorFilterSerial;                     // 0x168: clear sets 1
    mm::mtl::FixedQueue<CloudSea, 16> m_cloudSeas;         // 0x170
    unsigned long m_cloudSeaSerial;                        // 0x240: clear sets 1
    mm::mtl::FixedQueue<WeatherSet, 16> m_weathers;        // 0x248
    unsigned long m_weatherSerial;                         // 0x318: clear sets 1
    int m_room;  // 0x320: frames counted in (> 0) or out of (< 0) a room by update, -99..99; isRoom: above -3
    unsigned char m_screenShotWait;  // 0x324: frames until update enables screenshots again (GEV 6 sets 180)
};
}  // namespace gf

namespace gf {
// 2.0.0's symbols name it (its tables are lbl_7100B54858 and its PtrSingleton base's lbl_7100B54878, its instance
// lbl_7100C23300). 1.0.0 has no such object.
// gf_game_env.cpp's build creates it (0x10 bytes, line 1258) from GfGameManager::initialize. What it does:
// keeps the add-on content state: its functions refresh the local flags 0xD781-0xD787 from GfDataAoc's counts
// (GfDataAoc::getContentVersion(1..3)), answer whether an encoded add-on item is owned (isExistGameAoc) and hold the mode int that
// GfGameManager::isGameTypeIra tests for 1.
class GfGameAoc : public ::mm::mtl::PtrSingleton< ::gf::GfGameAoc> {
public:
    virtual ~GfGameAoc() {}  // slot 0 (its table's D2 slot holds the base's)
    // 2.0.0's symbols name it. A member: GfGameManager::resetGameType
    // passes the instance. What it does: sets GfDataGame's bit 0 of 0xFD6D0 to (mode == 1), stores mode at 0x8 and
    // refreshes the add-on flags 0xD781-0xD787 (as refreshAocFlag).
    void setupGame(GAME_TYPE mode);
    // 2.0.0's symbols name it. A member: GfGameManager::isInstalledBattleArenaContents
    // passes the instance. What it does: decodes id (kind = bits 16-19, needed count = bits 8-15), true when
    // GfDataAoc's count of that kind reaches it; kind 4 (0x401xx/0x402xx) also asks GfBdatShop::getMNU_DlcGiftgetflag.
    bool isExistGameAoc(GAMEAOC id) const;
    // 2.0.0's symbols name it. What it does: for id >= 35353 refreshes the add-on flags (refreshAocFlag).
    void gevChangeAocFlag(unsigned int id);
    // 2.0.0's symbols name it. What it does: sets local flags 0xD781-0xD784 (type 1) to whether GfDataAoc's count 1
    // (GfDataAoc::getContentVersion(1)) is above 0..3, 0xD785 to count 3 > 0, 0xD786 to 1 and 0xD787 to count 2 > 0.
    void refreshAocFlag();
    // 2.0.0's symbols name it. It builds the instance (0x10 bytes, gf_game_env.cpp line 1258, m_mode 0) as build does
    // for the other singletons of the file.
    static void build(const GfSetupParam& param);
    // 2.0.0's symbols name it. It deletes the instance when there is one, as destroy does for the other singletons of
    // the file.
    static void destroy();
    GfGameAoc() : m_mode(0) {}

    int m_mode;  // 0x8 (the name is not the original's) 1 in the mode GfGameManager::isGameTypeIra tests
};
}  // namespace gf

#endif
