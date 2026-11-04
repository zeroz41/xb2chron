#ifndef CLASSES_GF_GFFIELDWEATHER_H
#define CLASSES_GF_GFFIELDWEATHER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedQueue.h"
#include "gf/MapjumpCallbackInfo.h"

namespace gf { class GfFieldWeather; enum WEATYPE : int; enum WEATHERID : int; }
namespace gf { class GfSetupParam; class MapjumpCallbackInfo; class GF_OBJ_HANDLE; enum GEV : int; enum RELOAD_BDAT : int; enum CLOUD_SEA : int; enum CLOUD_SEA_HANDLE : int; }
namespace fw { class UpdateInfo; }
namespace gf { struct WeatherParam; }

namespace gf {
// table 0x7100B526C0
class GfFieldWeather : public ::mm::mtl::PtrSingleton< ::gf::GfFieldWeather> {
public:
    // GfPlayComEventWeather::start passes its weather and no name
    static void setWeatherForEvent(WEATYPE type, const char* name);
    virtual ~GfFieldWeather();  // slot 0
    static unsigned int getCurrentWtrType(bool);
    static int getCurrentCloudSea();
    // the current map's weather (event::EnvManager::login passes false)
    static WEATHERID getCurrentMapWeatherID(bool);
    // GfGameEvent::setMapWeather and resetWeaType hand it the weather to go back to
    static void setMapWeatherID(WEATHERID id);
    static void setCloudSea(unsigned int map, CLOUD_SEA cloudSea);  // GfGameUtilCloudSea::getCloudSea forwards here
    // GfFieldManager's forwards (its initialize, finalize, clear, setupGame and gev* functions call them)
    static void build(const GfSetupParam& param);
    static void setWeather(WEATYPE type, bool flag);  // the fld script plugin's setWeather (name from the symbols)
    static void destroy();
    static void clear();
    // 1.0.0's GfFieldManager::setupGame calls setupGame() where 3.0.1's calls this, and the bodies make the same calls
    static void setupGame();
    static void gevMapjump(GEV gev, const MapjumpCallbackInfo& info);
    static void gevGameMapModel(GF_OBJ_HANDLE* handle, bool flag);
    static void gevPause(unsigned int flags0, unsigned int flags1);
    static void update(const fw::UpdateInfo& info);
    static void setDispWeather(bool disp);
    // 1 << (getCurrentMapWeatherID(prev) - 1): the current weather as a bit (WeatherCond::isMatch tests it)
    static unsigned int getCurrentMapWeatherBit(bool prev);
    // the cloud sea of a map (its record in the game data), the current one for map 0 (1.0.0's
    // GfGameCond::isGameEnv and GfPlayComPlayerDead::update call it)
    static CLOUD_SEA getCloudSea(unsigned int map);
    void updateCloudSea(const fw::UpdateInfo& info);
    // a weather for the map (setMapWeatherID passes the current map and 4.0 as the fade time)
    void createWeather(unsigned int map, WEATHERID id, float fadeTime);
    void createWeather(const WeatherParam& param, float fadeTime);
    // a weather forced by type (setWeatherForEvent passes 4.0 as the fade time and its effect name)
    void createWeatherForce(WEATYPE type, float fadeTime, const char* name);
    void applyNowMapWeather(unsigned int prevMap, unsigned int map);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in this class's
    // unit between setCloudSea and setMapWeatherID and only setMapWeatherID calls it (no this: its map in w0).
    // What it does: saves the newest weather on the list (its type, id, time and length) into the map's record
    // (GfDataMap::getWeatherParam), with a new length (10800 for weather id 5, else GfDataMap::getWeatherTimeEnd
    // times 300, plus up to as much again by ml::mtRandf1).
    static void fn_7100280F84(unsigned int map);
    // 2.0.0's symbols name it. It lives in this class's unit among its functions and applyNowMapWeather hands it
    // this. What it does: brings the weather list to the map's record (0x6E0 bytes, not written yet). Caller:
    // applyNowMapWeather with the new map's record.
    void execChangeWeather(const WeatherParam& data);
    void updateEvent(const fw::UpdateInfo& info);
    void updateWeather(const fw::UpdateInfo& info);
    static bool isDispWeather();  // whether the weather shows (WeatherEff and WeatherSnd play only then)  // the weather now (GfMenuBdat::getIconIDFromWeatherType takes it)

    GfFieldWeather()
        : m_built(false), pad_9(false), pad_a(false), m_mapjumpInfo(), pad_74(0), m_cloudSea(), m_cloudSeaRequest(0),
          m_innCloudSea(), m_dispWeather(true) {}

    // the field names are not the original's
    bool m_built;  // 0x8: build sets it, destroy clears it
    bool pad_9;
    bool pad_a;
    ::mm::mtl::FixedQueue<GEV, 16> m_gevQueue;  // 0x10: gevMapjump's events
    MapjumpCallbackInfo m_mapjumpInfo;  // 0x60: gevMapjump's last info
    int pad_74;
    CLOUD_SEA_HANDLE m_cloudSea;  // 0x78: build's GfGameEnv cloud sea (type 0, priority 0)
    // 0x7C: the cloud sea to set: 0 none, 1 off, 2 on (setCloudSea, setupGame; updateCloudSea applies and clears it)
    int m_cloudSeaRequest;
    CLOUD_SEA_HANDLE m_innCloudSea;  // 0x80: updateCloudSea's cloud sea while its game condition holds
    bool m_dispWeather;  // 0x84: setDispWeather's flag
};
}  // namespace gf

#endif
