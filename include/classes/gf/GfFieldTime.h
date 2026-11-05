#ifndef CLASSES_GF_GFFIELDTIME_H
#define CLASSES_GF_GFFIELDTIME_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Bitflag.h"

namespace gf { class GfFieldTime; }
namespace gf { class GfSetupParam; class MapjumpCallbackInfo; class GF_OBJ_HANDLE; enum GEV : int; enum RELOAD_BDAT : int; }
namespace fw { class UpdateInfo; }

namespace gf {
// a play time in 32 bits (GfMenuGameAdapter::update_GamePlayTime shows at most 999:59:59)
struct ElapseTime {
    unsigned int sec : 6;
    unsigned int min : 6;
    unsigned int hour : 20;
};
// the time from b to a, zero when b is later (gf_field_time.cpp)
ElapseTime operator-(const ElapseTime& a, const ElapseTime& b);

// the console's date and time in 64 bits, as GfMenuGameAdapter's update_RealYear and update_RealTime read them
struct RealTime {
    unsigned long long pad_0 : 6;
    unsigned long long msec : 10;  // ml::TimeInfo's milliseconds, cut to 10 bits
    unsigned long long sec : 6;
    unsigned long long minute : 6;
    unsigned long long hour : 5;
    unsigned long long day : 5;
    unsigned long long yday : 9;  // ml::TimeInfo's day of the year
    unsigned long long month : 4;
    unsigned long long year : 13;
};

// the time of day in 32 bits, as GfMenuObjSkipTime reads and sets it
struct GameTime {
    unsigned int sec : 6;
    unsigned int min : 6;
    unsigned int hour : 5;
    // the days (1.0.0's GfFieldTime::nextDay adds one; update carries the hours into it and stops at 0x7FFF)
    unsigned int day : 15;
};

// table 0x7100B52638
class GfFieldTime : public ::mm::mtl::PtrSingleton< ::gf::GfFieldTime> {
public:
    int getTimeRangeDN() const;
    virtual ~GfFieldTime();  // slot 0
    const ElapseTime& getElapseTime() const;  // the play time
    int getHour() const;
    // the time of day as hour and minute (event::EnvManager::login keeps them)
    // returns the second of the day (0 to 86399)
    unsigned int getTime(unsigned int& hour, unsigned int& min) const;
    // the fld script plugin's setTime and stopTime (names from the symbols)
    void setTime(unsigned int hour, unsigned int min);
    void setFieldScriptTimeStop(bool stop);
    int getMin() const;
    void setHour(unsigned int hour);
    void setMin(unsigned int min);
    int getTimeRange() const;  // the time of day's range (an icon index)
    int getTimeRange(unsigned int hour, unsigned int min) const;  // the same for that time
    const GameTime& getGameTime() const;
    void setGameTime(const GameTime& time);
    bool getTimeRangeName(unsigned char*& bdat, unsigned int& id) const;  // its name in a message table
    void getRealTime(RealTime& time) const;
    unsigned int getTimeRangeBits() const;  // the time of day's range as a bit (WeatherInfo::isTimeRangeOK tests it)
    // GfFieldManager's forwards (its initialize, finalize, clear, setupGame, gevReloadBdat, update call them)
    static void build(const GfSetupParam& param);
    static void destroy();
    void clear();
    void setupGame();
    void gevReloadBdat(RELOAD_BDAT type, unsigned int id);
    void update(const fw::UpdateInfo& info);
    // 1.0.0's GfFieldManager::setSuspendGame calls saveSuspendRealTime() where 3.0.1's calls this (same instance, no
    // other argument); 3.0.1's body is empty
    void saveSuspendRealTime();
    void setElapseTime(const ElapseTime& time);
    void setTimeStop(bool stop);
    bool isTimeStop() const;  // stopped by setTimeStop or the fld script plugin

private:
    // GfFieldTime::build's object: setupGame and clear set it all (the names are not the original's unless noted)
    GfFieldTime()
        : m_initialized(false), m_flags(), m_startPlayTime(), m_playTime(), m_realTime(), m_startRealTime(),
          m_gameTime(), m_stop(false) {}
    // 1.0.0's GfFieldTime::finalize (destroy inlines it)
    void finalize() { m_initialized = false; }
    // 1.0.0's GfFieldTime::saveRealTime (the console's date and time now; every caller inlines it)
    void saveRealTime() { getRealTime(m_realTime); }

    bool m_initialized;  // 0x8: build sets it after clear, finalize clears it
    mm::mtl::Bitflag<32> m_flags;  // 0xC: 0 setTimeStop, 1 setFieldScriptTimeStop (the size is not known)
    ElapseTime m_startPlayTime;  // 0x10: the play time setupGame and setElapseTime start from
    ElapseTime m_playTime;  // 0x14: the play time, counted up a second at a time by update
    RealTime m_realTime;  // 0x18: the console's date and time, saved every update
    RealTime m_startRealTime;  // 0x20: the date and time setupGame and setElapseTime saw
    unsigned int pad_28;  // clear sets it to 0
    GameTime m_gameTime;  // 0x2C: the time of day
    float m_time;  // 0x30: the time of day in 30ths of a minute (hour * 1800 + min * 30), getTime reads it
    float m_prevTime;  // 0x34: m_time before the last update
    float pad_38;  // set to 0 with every new time of day
    float pad_3C;  // clear sets it to 1
    unsigned int m_timeRange;  // 0x40: getTimeRange()
    unsigned int m_prevTimeRange;  // 0x44: GfEvent::callChangeTimeRange runs when m_timeRange leaves it
    int m_timeRangeDN;  // 0x48: getTimeRangeDN() when the range was set
    unsigned int pad_4C;  // clear sets it to 0
    float m_playSec;  // 0x50: seconds toward the next play time second
    float m_gameSec;  // 0x54: seconds toward the next minute of the time of day
    bool m_stop;  // 0x58: update stops the time of day while it is set
};
}  // namespace gf

#endif
