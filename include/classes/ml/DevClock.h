#ifndef CLASSES_ML_DEVCLOCK_H
#define CLASSES_ML_DEVCLOCK_H

#include "classes/ml/IWorkEvent.h"

namespace ml {
// table none (its derived classes')
class DevClock : public ::ml::IWorkEvent {
public:
    virtual ~DevClock();  // slot 0
    virtual void wkStandby();  // slot 8
    virtual void wkUpdate();  // slot 9
    virtual void wkRender();  // slot 10
    virtual void wkRenderAfter();  // slot 11
    virtual void wkTail();  // slot 12
    virtual void wkFrameEnd();  // slot 13
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    // the clock now, and the seconds from a clock to now (static: the states of the salvage game time themselves)
    static void getClockNow(long& clock);
    static void getTimeNow(float& time, const long& clock);

    unsigned char pad_8[0x1A8];  // fields: size from its derived classes
};
}  // namespace ml

#endif
