#ifndef CLASSES_ML_DEVBASE_H
#define CLASSES_ML_DEVBASE_H

#include "classes/ml/WorkObj.h"

namespace ml {
// table 0x7100B77470
class DevBase : public ::ml::WorkObj {
public:
    // WorkUtil::createWork<DevClockNx> inlines it: the work, then 0 at 0x1A8
    DevBase(const char* name, WorkObj* parent) : WorkObj(name, parent, 0), m_devState(0) {}
    virtual ~DevBase() {}  // slot 0
    int m_devState;  // 0x1A8 the constructor clears it (the name is not the original's)
    unsigned char pad_1ac[0x4];
};
}  // namespace ml

#endif
