#include "classes/gf/GfFieldTime.h"
#include "gf/SDataGame.h"
#include "gf/GfDataMap.h"
#include "classes/gf/GfEvent.h"
#include "ml/TimeUtil.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfGameSpeed.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfPause.h"
#include "classes/gf/GfEvent.h"
#include "gf/GfDataMap.h"
#include "gf/SDataGame.h"
#include "ml/TimeUtil.h"
#include <math.h>

namespace gf {

namespace {
// a time of day range: from start hour:min to end hour:min (the names are not the original's)
struct TimeRange {
    unsigned short startHour;
    unsigned short startMin;
    unsigned short endHour;
    unsigned short endMin;

    bool isIn(unsigned int hour, unsigned int min) const {
        return startHour <= hour && hour <= endHour && startMin <= min && min <= endMin;
    }
};
}  // namespace

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B52658)
static TimeRange s_timeRanges[6] = {
    {7, 0, 11, 59}, {12, 0, 15, 59}, {16, 0, 18, 59}, {19, 0, 23, 59}, {0, 0, 4, 59}, {5, 0, 6, 59},
};

GfFieldTime::~GfFieldTime() {}

int GfFieldTime::getTimeRange(unsigned int hour, unsigned int min) const {
    for (int i = 0; i < 6; i++) {
        if (s_timeRanges[i].isIn(hour, min)) {
            return i;
        }
    }
    return 0;
}

int GfFieldTime::getTimeRangeDN() const {
    return m_timeRange < 3 ? 6 : 7;
}

void GfFieldTime::getRealTime(RealTime& time) const {
    ml::TimeInfo info = {};
    ml::TimeUtil::getTime(info);
    time.year = info.year;
    time.month = info.month;
    time.yday = info.yday;
    time.day = info.day;
    time.hour = info.hour;
    time.minute = info.min;
    time.sec = info.sec;
    time.msec = info.msec;
}

void GfFieldTime::setTime(unsigned int hour, unsigned int min) {
    float fhour = hour;
    float fmin = min;
    float time = fhour * 1800.0f + fmin * 30.0f;
    pad_38 = 0.0f;
    m_gameTime.hour = hour;
    m_gameTime.min = min;
    m_gameTime.sec = 0;
    m_time = m_prevTime = time;
    m_timeRange = getTimeRange(hour, min);
    m_timeRangeDN = getTimeRangeDN();
    saveRealTime();
}

const GameTime& GfFieldTime::getGameTime() const {
    return m_gameTime;
}

void GfFieldTime::setElapseTime(const ElapseTime& time) {
    m_startPlayTime = time;
    m_playTime = time;
    getRealTime(m_startRealTime);
}

void GfFieldTime::setGameTime(const GameTime& time) {
    float hour = fmodf(time.hour, 24.0f);
    float min = fmodf(time.min, 60.0f);
    m_time = m_prevTime = hour * 1800.0f + min * 30.0f;
    m_gameTime = time;
    m_timeRange = getTimeRange(time.hour, time.min);
    m_timeRangeDN = getTimeRangeDN();
    saveRealTime();
}

void GfFieldTime::setTimeStop(bool stop) {
    m_flags.set(0, stop);
}

void GfFieldTime::gevReloadBdat(RELOAD_BDAT type, unsigned int id) {}

void GfFieldTime::build(const GfSetupParam& param) {
#line 108
    GfFieldTime* time = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldTime();
    time->clear();
    time->m_initialized = true;
}

void GfFieldTime::destroy() {
    GfFieldTime* time = get();
    time->finalize();
    delete time;
}

bool GfFieldTime::isTimeStop() const {
    return m_flags.test(0) || m_flags.test(1);
}

int GfFieldTime::getTimeRange() const {
    return m_timeRange;
}

bool GfFieldTime::getTimeRangeName(unsigned char*& bdat, unsigned int& id) const {
    return GfDataMap::getTimeRangeName(bdat, id, m_timeRange);
}

int GfFieldTime::getHour() const {
    return m_gameTime.hour;
}

int GfFieldTime::getMin() const {
    return m_gameTime.min;
}

const ElapseTime& GfFieldTime::getElapseTime() const {
    return m_playTime;
}

void GfFieldTime::saveSuspendRealTime() {}

unsigned int GfFieldTime::getTime(unsigned int& hour, unsigned int& min) const {
    float time = m_time;
    hour = fmodf(time / 1800.0f, 24.0f);
    min = fmodf(time / 30.0f, 60.0f);
    return fmodf(time, 43200.0f) * 2.0f;
}

void GfFieldTime::setFieldScriptTimeStop(bool stop) {
    m_flags.set(1, stop);
}

ElapseTime operator-(const ElapseTime& a, const ElapseTime& b) {
    int hour = a.hour - b.hour;
    int min = a.min - b.min;
    int sec = a.sec - b.sec;
    if (sec < 0) {
        sec += 60;
        min--;
    }
    if (min < 0) {
        min += 60;
        hour--;
    }
    ElapseTime time;
    time.sec = sec;
    time.hour = hour;
    time.min = min;
    if (hour < 0) {
        time = ElapseTime();
    }
    return time;
}

}  // namespace gf
