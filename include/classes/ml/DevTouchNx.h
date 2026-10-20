#ifndef CLASSES_ML_DEVTOUCHNX_H
#define CLASSES_ML_DEVTOUCHNX_H

#include "classes/ml/DevTouch.h"

namespace ml {
// table 0x7100B768A8
class DevTouchNx : public ::ml::DevTouch {
public:
    virtual ~DevTouchNx();  // slot 0
    virtual void updateDevice();  // slot 20
    virtual void createDevice();  // slot 21
    virtual void releaseDevice();  // slot 22
};
}  // namespace ml

#endif
