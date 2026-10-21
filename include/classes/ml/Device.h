#ifndef CLASSES_ML_DEVICE_H
#define CLASSES_ML_DEVICE_H

#include "classes/ml/WorkObj.h"

namespace ml {
// a base of ml::Device no evidence names yet
class TUnk_B75A80 {
public:
    virtual ~TUnk_B75A80();
};
// table 0x7100B759D8; base at 0x1A8 unknown (TUnk_B75A80)
class Device : public ::ml::WorkObj, public TUnk_B75A80 {
public:
    virtual ~Device();  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
    virtual void createDevice() = 0;  // slot 17
    virtual void createDevicePort(char const*) = 0;  // slot 18
};
}  // namespace ml

#endif
