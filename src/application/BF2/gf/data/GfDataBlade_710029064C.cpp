#include "gf/GfArenaUtil.h"
#include "classes/gf/GfBdatBtl.h"
#include "gf/GfDataMap.h"
#include "gf/GfDataBlade.h"

namespace gf {

void GfArenaUtil::setupBattleMapWeather(unsigned int id) {
    GfBdatBtl* btl = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
    if (unsigned int map = btl->getBTL_ChBtlMapJump(id)) {
        unsigned int mapId = GfDataMap::getMapID(map);
        unsigned int weather = btl->getBTL_ChBtlWeather(id);
        WeatherParam* env = GfDataMap::getWeatherParam(mapId);
        if (env->m_mapId == mapId) {
            env->m_id = static_cast<WEATHERID>(weather < 4 ? weather + 1 : 5);
            env->m_time = 0.0f;
            env->m_timeMax = 100.0f;
        }
    }
}

}  // namespace gf
