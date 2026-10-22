#ifndef CLASSES_GF_GFFIELDTIME_H
#define CLASSES_GF_GFFIELDTIME_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldTime; }

namespace gf {
// a play time in 32 bits (GfMenuGameAdapter::update_GamePlayTime shows at most 999:59:59)
struct ElapseTime {
    unsigned int sec : 6;
    unsigned int min : 6;
    unsigned int hour : 20;
};

// the console's date and time in 64 bits, as GfMenuGameAdapter's update_RealYear and update_RealTime read them
struct RealTime {
    unsigned long long pad_0 : 22;
    unsigned long long minute : 6;
    unsigned long long hour : 5;
    unsigned long long day : 5;
    unsigned long long pad_38 : 9;
    unsigned long long month : 4;
    unsigned long long year : 13;
};

// table 0x7100B52638
class GfFieldTime : public ::mm::mtl::PtrSingleton< ::gf::GfFieldTime> {
public:
    virtual ~GfFieldTime();  // slot 0
    const ElapseTime& getElapseTime() const;  // the play time
    int getHour() const;
    int getMin() const;
    int getTimeRange() const;  // the time of day's range (an icon index)
    bool getTimeRangeName(unsigned char*& bdat, unsigned int& id) const;  // its name in a message table
    void getRealTime(RealTime& time) const;
    unsigned int getTimeRangeBits() const;  // the time of day's range as a bit (WeatherInfo::isTimeRangeOK tests it)
};
}  // namespace gf

#endif
