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
    virtual void wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
    unsigned char pad_8[0x1A8];  // fields: size from its derived classes
};
}  // namespace ml

#endif
