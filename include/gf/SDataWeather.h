#ifndef GF_SDATAWEATHER_H
#define GF_SDATAWEATHER_H

namespace gf { enum WEATYPE : int; enum WEATHERID : int; }

namespace gf {

// a map's record in the game data (0x20 bytes; GfDataBlade's fn_710024E1C8 finds it by m_mapId; GfFieldWeather keeps
// each map's weather in it). The type name is 1.0.0's: GfFieldWeather::updateEvent hands fn_710024E1C8's record to
// createWeather(const WeatherParam&, float). The field names are not the original's. Its constructor clears the
// name's first byte and the rest (GfDataBlade's static initialiser and function-static records).
struct WeatherParam {
    WeatherParam() : m_type(), m_id(), m_time(0.0f), m_timeMax(0.0f), m_mapId(0), m_cloudSea(0) {
        m_resource[0] = '\0';
    }
    char m_resource[8];  // GfBdatMaplist::getMaplistresource's name (GfFieldWeather::setupGame copies it in)
    WEATYPE m_type;  // the map's weather, its id, time and length (GfFieldWeather's fn_7100280F84 saves them)
    WEATHERID m_id;
    float m_time;
    float m_timeMax;
    unsigned int m_mapId;
    unsigned int m_cloudSea;  // fn_710024E8F4 stores (cloudSea != 0); GfFieldWeather::getCloudSea reads it
};

// the maps' weather records (0x800 bytes; the class and clear() are the symbols'): SDataGame keeps one at 0x10A53C
// (SDataGame::SDataGame calls clear()), GfDataBlade's unit a file-static one that its static initialiser constructs.
// m_params and find() are not the original's names.
class SDataWeather {
public:
    SDataWeather() { clear(); }
    void clear();
    // the index of the first record whose m_mapId is map, else -1 (inlined in GfDataBlade's fn_710024E0D0 and
    // fn_710024E1C8: the name is not the original's)
    int find(unsigned int map) const {
        for (int i = 0; i < 64; i++) {
            if (m_params[i].m_mapId == map) {
                return i;
            }
        }
        return -1;
    }

    WeatherParam m_params[64];
};

}  // namespace gf

#endif
