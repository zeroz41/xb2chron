#ifndef GF_GFDATAMAP_H
#define GF_GFDATAMAP_H

namespace gf { enum WEATYPE : int; }
namespace gf { enum WEATHERID : int; }
namespace gf { enum CLOUD_SEA : int; struct WeatherParam; }

namespace gf {
// the map data's helpers (functions, by their symbols)
class GfDataMap {
public:
    static unsigned int getZoneIdForGameMap(unsigned int map);
    static unsigned int getFieldZoneId(unsigned int id);  // SCOM_ADD_DEVELOP::createGmk passes its first argument
    static unsigned int getDevelopMapId(unsigned int zone);
    static const char* getWeatherName(WEATYPE type);  // "Default" for none, "" when it has no name
    static const char* getWeatherEffName(WEATYPE type);  // the weather's effect, null or empty for none
    static const char* getWeatherSndName(WEATYPE type);  // the weather's loop sound, null or empty for none
    static const char* getWeatherSndBeginName(WEATYPE type);  // the sound it starts with, null or empty for none
    // the times of day (GfFieldTime::getTimeRangeBits's bits) a map's weather may come in
    static unsigned int getWeatherTimeBonus(unsigned int mapId, WEATHERID id);
    // a map's resource name, null or empty for none (GfFieldZoneScript::execScript runs fld_<it>)
    static const char* getMapResourceName(unsigned int mapId);
    static const char* getMapResourceNameByMapID(unsigned int mapId);
    static unsigned int getWeatherForceConditionOn(unsigned int mapId, WEATHERID weather);
    static unsigned int getWeatherForceConditionOff(unsigned int mapId, WEATHERID weather);
    static unsigned int getWeatherTimeEnd(unsigned int mapId, WEATHERID weather);
    static unsigned int getWeatherPopRate(unsigned int mapId, WEATHERID weather);
    static bool isMapCompleteFlag(unsigned int mapId);
    // the FLD_maplist id of a map jump (GfFieldManager passes GfGameManager::getMapJumpID and
    // MapjumpCallbackInfo::m_mapJumpId), 0 for none
    static unsigned int getMapID(unsigned int mapJumpId);
    // the first FLD_maplist row (BDAT 182) whose MapList byte is mapId, 0 for none
    static unsigned int getMapJumpID(unsigned int mapId);
    static void setMapCompleteFlag(unsigned int mapId);
    static unsigned int getZoneIdForDevelopPoint(unsigned int point);
    static int getWeatherType(unsigned int mapId, WEATHERID id);
    // the weather id (1 to 4) whose type is type on the map, 5 when none is
    static unsigned int getWeatherIdByWeaType(unsigned int mapId, WEATYPE type);
    // the time range's name in FLD_TimeInfo's msg (GfFieldTime::getTimeRangeName passes its range); false for none
    static bool getTimeRangeName(unsigned char*& bdat, unsigned int& id, unsigned int range);
    // 2.0.0's symbols name it. What it does: a game data map record whose m_mapId is 0 (a free one);
    // GfFieldWeather::setupGame copies a map's resource name into it and sets its m_mapId.
    static WeatherParam* getEmptyWeatherParam();
    // 2.0.0's symbols name it. What it does: the game data's record for the map (two 64-record arrays searched by
    // m_mapId, the first in GfDataManager::getDataGame() + 0x10A53C, each only when
    // GfBdatMaplist::getMaplistresource(map) is set), else a zeroed function-static record. Callers: GfFieldWeather
    // (getCloudSea, setupGame, createWeather, updateEvent, updateWeather, applyNowMapWeather), GfDataMap::setCloudType,
    // GfDataStore::initGameData.
    static WeatherParam* getWeatherParam(unsigned int map);
    // 2.0.0's symbols name it. What it does: whether the map's record (GfDataMap::getWeatherParam) has its cloud sea on
    // (m_cloudSea != 0). Caller: GfFieldWeather::applyNowMapWeather, which hands it on as the cloud sea to set (it
    // tests the whole word).
    static CLOUD_SEA getCloudType(unsigned int map);
    // 2.0.0's symbols name it. What it does: stores (cloudSea != 0) at 0x1C of the record GfDataMap::getWeatherParam
    // returns for the map; GfGameUtilCloudSea::setInnCloudSea passes (GfGameManager::getMapID(), its cloud sea),
    // GfPlayComPlayerDead::update calls it too.
    static void setCloudType(unsigned int map, CLOUD_SEA cloudSea);
    // 2.0.0's symbols name it. What it does: whether GfDataUtil::getScenarioFlag (local flag 1, type 16) is above
    // 0x1F64.
    static bool isArcadiaDestroy();
    // 2.0.0's symbols name it. What it does: whether local flag 0xD862 (type 1) is set (GfGameFlag::getLocal(1,
    // 0xD862)); GfDataMap::setIraLastMapCloud2 sets it.
    static bool isIraLastMapCloud2();
    // 2.0.0's symbols name it. What it does: sets local flag 0xD862 (type 1) to flag.
    static void setIraLastMapCloud2(bool flag);
    // 2.0.0's symbols name it. What it does: whether local flag 0xD863 (type 1) is set;
    // GfDataMap::setIraOutoAttackCloud sets it.
    static bool isIraOutoAttackCloud();
    // 2.0.0's symbols name it. What it does: sets local flag 0xD863 (type 1) to flag.
    static void setIraOutoAttackCloud(bool flag);
    // 2.0.0's symbols name it. What it does: looks up the FLD_MapGimmick table (result unused) and counts the set local
    // flags (type 1) 0xABFA and 0xAC00-0xAC08.
    static unsigned int getErasedEthCloudNum();
};
}  // namespace gf

#endif
