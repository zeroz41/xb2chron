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
    static void setMapCompleteFlag(unsigned int mapId);
};
}  // namespace gf

#endif
