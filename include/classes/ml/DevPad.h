#ifndef CLASSES_ML_DEVPAD_H
#define CLASSES_ML_DEVPAD_H

#include "classes/ml/DevGraphCB.h"
#include "classes/ml/WorkObj.h"

namespace ml { class PadVibrationInfo; }

namespace ml {
// a base of ml::DevPad no evidence names yet
class TUnk_B75F70 {
public:
    virtual ~TUnk_B75F70();
};
// table 0x7100B75E48; base at 0x1A8 unknown (TUnk_B75F70)
class DevPad : public ::ml::WorkObj, public TUnk_B75F70, public ::ml::DevGraphCB {
public:
    virtual ~DevPad();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual void wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
    virtual void isLocalConnect(int) const = 0;  // slot 17
    virtual void getLocalStyle(int) const = 0;  // slot 18
    virtual void getLocalUserSelectPadID() const = 0;  // slot 19
    virtual void getLocalBtn(int) const = 0;  // slot 20
    virtual void getLocalALX(int) const = 0;  // slot 21
    virtual void getLocalALY(int) const = 0;  // slot 22
    virtual void getLocalARX(int) const = 0;  // slot 23
    virtual void getLocalARY(int) const = 0;  // slot 24
    virtual void updateDevice(float) = 0;  // slot 25
    virtual void createDevice() = 0;  // slot 26
    virtual void releaseDevice() = 0;  // slot 27
    virtual void setCaptureName(char const*);  // slot 28
    virtual void setCapture(bool);  // slot 29
    virtual void isCapture() const;  // slot 30
    virtual void playLocalVibration(int, ml::PadVibrationInfo const&);  // slot 31
    virtual void stopLocalVibration(int);  // slot 32
    virtual void loadLocalVibration(unsigned int, void*, unsigned long);  // slot 33
    virtual void viBeginFrame();  // slot 34
};
}  // namespace ml

#endif
