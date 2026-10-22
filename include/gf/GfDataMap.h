#ifndef GF_GFDATAMAP_H
#define GF_GFDATAMAP_H

namespace gf { enum WEATYPE : int; }
namespace gf { enum WEATHERID : int; }

namespace gf {
// the map data's helpers (functions, by their symbols)
class GfDataMap {
public:
    static const char* getWeatherEffName(WEATYPE type);  // the weather's effect, null or empty for none
    static const char* getWeatherSndName(WEATYPE type);  // the weather's loop sound, null or empty for none
    static const char* getWeatherSndBeginName(WEATYPE type);  // the sound it starts with, null or empty for none
    // the times of day (GfFieldTime::getTimeRangeBits's bits) a map's weather may come in
    static unsigned int getWeatherTimeBonus(unsigned int mapId, WEATHERID id);
};
}  // namespace gf

#endif
