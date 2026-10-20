#ifndef CLASSES_ML_DEVPADNX_H
#define CLASSES_ML_DEVPADNX_H

#include "classes/ml/DevPad.h"

namespace ml { class PadVibrationInfo; }

namespace ml {
// table 0x7100B76678
class DevPadNx : public ::ml::DevPad {
public:
    virtual ~DevPadNx();  // slot 0
    virtual void isLocalConnect(int) const;  // slot 17
    virtual void getLocalStyle(int) const;  // slot 18
    virtual void getLocalUserSelectPadID() const;  // slot 19
    virtual void getLocalBtn(int) const;  // slot 20
    virtual void getLocalALX(int) const;  // slot 21
    virtual void getLocalALY(int) const;  // slot 22
    virtual void getLocalARX(int) const;  // slot 23
    virtual void getLocalARY(int) const;  // slot 24
    virtual void updateDevice(float);  // slot 25
    virtual void createDevice();  // slot 26
    virtual void releaseDevice();  // slot 27
    virtual void playLocalVibration(int, ml::PadVibrationInfo const&);  // slot 31
    virtual void stopLocalVibration(int);  // slot 32
    virtual void loadLocalVibration(unsigned int, void*, unsigned long);  // slot 33
};
}  // namespace ml

#endif
