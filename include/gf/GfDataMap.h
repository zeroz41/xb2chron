#ifndef GF_GFDATAMAP_H
#define GF_GFDATAMAP_H

namespace gf { enum WEATYPE : int; }
namespace gf { enum WEATHERID : int; }

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
};
}  // namespace gf

#endif
