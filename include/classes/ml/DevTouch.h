#ifndef CLASSES_ML_DEVTOUCH_H
#define CLASSES_ML_DEVTOUCH_H

#include "classes/ml/WorkObj.h"

namespace ml {
// a base of ml::DevTouch no evidence names yet
class TUnk_B760A0 {
public:
    virtual ~TUnk_B760A0();
    virtual void itDown(unsigned int, float, float) = 0;
    virtual void itUp(unsigned int, float, float) = 0;
    virtual void itMove(unsigned int, float, float) = 0;
};
// a base of ml::DevTouch no evidence names yet
class TUnk_B760D8 {
public:
    virtual ~TUnk_B760D8();
};
// table 0x7100B75FD8; base at 0x1A8 unknown (TUnk_B760A0), base at 0x1B0 unknown (TUnk_B760D8)
class DevTouch : public ::ml::WorkObj, public TUnk_B760A0, public TUnk_B760D8 {
public:
    virtual ~DevTouch();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual bool wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
    virtual void itDown(unsigned int, float, float);  // slot 17
    virtual void itUp(unsigned int, float, float);  // slot 18
    virtual void itMove(unsigned int, float, float);  // slot 19
    virtual void updateDevice();  // slot 20
    virtual void createDevice() = 0;  // slot 21
    virtual void releaseDevice() = 0;  // slot 22
};
}  // namespace ml

#endif
