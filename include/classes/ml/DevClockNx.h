// not proven yet: its table differs from the original's (word 10: _ZN2ml8DevClock9wkStandbyEv where the original has _ZN2ml7WorkObj9wkStandbyEv)
#ifndef CLASSES_ML_DEVCLOCKNX_H
#define CLASSES_ML_DEVCLOCKNX_H

#include "classes/ml/DevClock.h"

namespace ml {
// a base of ml::DevClockNx no evidence names yet
class TUnk_B764A0 {
public:
    virtual ~TUnk_B764A0();
};
// table 0x7100B763E0; base at 0x1B0 unknown (TUnk_B764A0)
class DevClockNx : public ::ml::DevClock, public TUnk_B764A0 {
public:
    virtual ~DevClockNx();  // slot 0
    virtual void wkStandbyExceptionRetry(unsigned int);  // slot 16
    virtual void getPowerOnTimeSys() const;  // slot 17
    virtual void getClockNowSys(long&) const;  // slot 18
    virtual void getSec2ClockSys(long&, float) const;  // slot 19
    virtual void getSecNowSys(long const&) const;  // slot 20
    virtual void getClock2SecSys(long const&) const;  // slot 21
};
}  // namespace ml

#endif
