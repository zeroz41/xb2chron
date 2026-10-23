#ifndef CLASSES_ML_DEVCLOCKNX_H
#define CLASSES_ML_DEVCLOCKNX_H

#include "classes/ml/DevClock.h"
#include "nn/os.h"

namespace ml {
// table 0x7100B763E0
class DevClockNx : public ::ml::DevClock {
public:
    DevClockNx(const char* name, WorkObj* parent)
        : DevClock(name, parent), m_powerOnClock(nn::os::GetSystemTick().GetInt64Value()) {}
    virtual ~DevClockNx() {}  // slot 0
    virtual void wkStandbyExceptionRetry(unsigned int);  // slot 16
    virtual float getPowerOnTimeSys() const;  // slot 17
    virtual void getClockNowSys(long& clock) const;  // slot 18
    virtual void getSec2ClockSys(long& clock, float sec) const;  // slot 19
    virtual float getSecNowSys(const long& clock) const;  // slot 20
    virtual float getClock2SecSys(const long& clock) const;  // slot 21
    unsigned char pad_1b8[0x8];
    long m_powerOnClock;  // 0x1C0 the system tick at construction: getPowerOnTimeSys counts from it
};
}  // namespace ml

#endif
