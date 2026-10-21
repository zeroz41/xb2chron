#ifndef CLASSES_ML_WORKOBJ_H
#define CLASSES_ML_WORKOBJ_H

#include "classes/ml/IWorkEvent.h"

namespace ml {
// table 0x7100B78CB8
class WorkObj : public ::ml::IWorkEvent {
public:
    virtual ~WorkObj();  // slot 0
    virtual void wkStandby();  // slot 8
    virtual void wkUpdate() {}  // slot 9
    virtual void wkRender() {}  // slot 10
    virtual void wkRenderAfter() {}  // slot 11
    virtual void wkTail() {}  // slot 12
    virtual void wkFrameEnd() {}  // slot 13
    virtual bool wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
    virtual void wkStandbyExceptionRetry(unsigned int);  // slot 16
    unsigned char pad_8[0x1A0];  // fields: size from its derived classes
};
}  // namespace ml

#endif
