#ifndef CLASSES_ML_DEVCLOCK_H
#define CLASSES_ML_DEVCLOCK_H

#include "classes/ml/DevBase.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {
// table none (its derived classes'); its singleton at 0x1B0 (WorkUtil::createWork<DevClockNx> stores
// PtrSingleton<ml::DevClock>'s table there and asserts get()==0)
class DevClock : public ::ml::DevBase, public ::mm::mtl::PtrSingleton<DevClock> {
public:
    DevClock(const char* name, WorkObj* parent) : DevBase(name, parent) {}
    virtual ~DevClock() {}  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    virtual float getPowerOnTimeSys() const = 0;  // slot 17
    virtual void getClockNowSys(long& clock) const = 0;  // slot 18
    virtual void getSec2ClockSys(long& clock, float sec) const = 0;  // slot 19
    virtual float getSecNowSys(const long& clock) const = 0;  // slot 20
    virtual float getClock2SecSys(const long& clock) const = 0;  // slot 21
    // the clock now, and the seconds from a clock to now (static: the states of the salvage game time themselves);
    // false while the device is not logged in
    static bool getClockNow(long& clock);
    static bool getTimeNow(float& time, const long& clock);
    static float getClock2Sec(const long& clock);
};
}  // namespace ml

#endif
