#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfBdatCond.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/gf/GfGameFlag.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataUtil.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100D6CBB0). The condition tables
// (GfBdatCond's object), kept by initialize and cleared by finalize.
static GfBdatCond* s_bdatCond;

inline GfGameCond::GfGameCond(const GfSetupParam& param) {
    initialize(param);
}

inline void GfGameCond::initialize(const GfSetupParam& param) {
    s_bdatCond = GfBdatCond::get();
}

GfGameCond::~GfGameCond() {}

void GfGameCond::build(const GfSetupParam& param) {
#line 87
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameCond(param);
}

void GfGameCond::destroy() {
    GfGameCond* cond = get();
    cond->finalize();
    delete cond;
}

inline void GfGameCond::finalize() {
    s_bdatCond = nullptr;
}

bool GfGameCond::isScenario(unsigned int condition) {
    unsigned short scenario = GfDataUtil::getScenarioFlag();
    unsigned short min = s_bdatCond->getConditionScenarioScenarioMin(condition);
    unsigned short max = s_bdatCond->getConditionScenarioScenarioMax(condition);
    if (max != 0 && (min > scenario || scenario > max)) {
        return false;
    }
    unsigned short notMin = s_bdatCond->getConditionScenarioNotScenarioMin(condition);
    unsigned short notMax = s_bdatCond->getConditionScenarioNotScenarioMax(condition);
    if (notMax != 0 && notMin <= scenario && scenario <= notMax) {
        return false;
    }
    return min != 0 || max != 0 || notMin != 0 || notMax != 0;
}

inline bool GfGameCond::isGameEnv(unsigned int condition, unsigned int timeBits, unsigned int weatherBits,
                                  CLOUD_SEA cloudSea) {
    unsigned int timeRange = s_bdatCond->getConditionEnvTimeRange(condition);
    if (timeRange != 0 && (timeRange & timeBits) == 0) {
        return false;
    }
    unsigned int weather = s_bdatCond->getConditionEnvWeather(condition);
    if (weather != 0 && (weather & weatherBits) == 0) {
        return false;
    }
    unsigned int cloudHeight = s_bdatCond->getConditionEnvCloudHeight(condition);
    if (cloudHeight != 0) {
        if (cloudSea != 0 && cloudHeight == 1) {
            return false;
        }
        if (cloudSea != 1 && cloudHeight == 2) {
            return false;
        }
    }
    return true;
}

bool GfGameCond::isGameEnv(unsigned int condition, unsigned int map) {
    GfFieldTime* time = GfFieldTime::get();
    unsigned int timeBits = time != nullptr ? time->getTimeRangeBits() : 0;
    unsigned int weatherBits = GfFieldWeather::getCurrentMapWeatherBit(false);
    CLOUD_SEA cloudSea = GfFieldWeather::getCloudSea(map);
    return isGameEnv(condition, timeBits, weatherBits, cloudSea);
}

bool GfGameCond::isFlag(unsigned int condition, bool* overMin, bool* underMax) {
    unsigned int flagType = s_bdatCond->getConditionFlagFlagType(condition);
    unsigned int id = s_bdatCond->getConditionFlagFlagID(condition);
    unsigned int min = s_bdatCond->getConditionFlagFlagMin(condition);
    unsigned int max = s_bdatCond->getConditionFlagFlagMax(condition);
    unsigned int value;
    switch (flagType) {
    case 1:
        value = GfGameFlag::getLocal(1, id);
        break;
    case 2:
        value = GfGameFlag::getLocal(2, id);
        break;
    case 4:
        value = GfGameFlag::getLocal(4, id);
        break;
    case 8:
        value = GfGameFlag::getLocal(8, id);
        break;
    case 16:
        value = GfGameFlag::getLocal(16, id);
        break;
    case 32:
        value = GfGameFlag::getLocal(32, id);
        break;
    default:
        return false;
    }
    bool over = min <= value;
    bool under = max >= value;
    if (overMin != nullptr) {
        *overMin = over;
    }
    if (underMax != nullptr) {
        *underMax = under;
    }
    return over && under;
}

bool GfGameCond::isGameCondWithoutEnv(unsigned int condition) {
    CondQuery query(condition);
    query.m_withoutEnv = true;
    return fn_71002A48D4(query);
}

bool GfGameCond::isGameCond(unsigned int condition) {
    CondQuery query(condition);
    return fn_71002A48D4(query);
}

bool GfGameCond::isGameCondWithMap(unsigned int condition, unsigned int map) {
    CondQuery query(condition);
    query.m_map = map;
    return fn_71002A48D4(query);
}

bool GfGameCond::isGameCondWithBlade(unsigned int condition, unsigned int blade) {
    CondQuery query(condition);
    query.m_blade = blade;
    return fn_71002A48D4(query);
}

}  // namespace gf
