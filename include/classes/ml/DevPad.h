#ifndef CLASSES_ML_DEVPAD_H
#define CLASSES_ML_DEVPAD_H

#include "classes/ml/DevGraphCB.h"
#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class PadVibrationInfo; }

namespace ml {
// table 0x7100B75E48; its base at 0x1A8 is its singleton (the inline destructor stores PtrSingleton<ml::DevPad>'s
// table there and clears its instance)
class DevPad : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton<DevPad>, public ::ml::DevGraphCB {
public:
    virtual ~DevPad();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    virtual bool isLocalConnect(int pad) const = 0;  // slot 17
    virtual int getLocalStyle(int pad) const = 0;  // slot 18
    virtual int getLocalUserSelectPadID() const = 0;  // slot 19
    virtual unsigned int getLocalBtn(int pad) const = 0;  // slot 20
    virtual float getLocalALX(int pad) const = 0;  // slot 21
    virtual float getLocalALY(int pad) const = 0;  // slot 22
    virtual float getLocalARX(int pad) const = 0;  // slot 23
    virtual float getLocalARY(int pad) const = 0;  // slot 24
    virtual void updateDevice(float) = 0;  // slot 25
    virtual void createDevice() = 0;  // slot 26
    virtual void releaseDevice() = 0;  // slot 27
    virtual void setCaptureName(char const*) {}  // slot 28
    virtual void setCapture(bool) {}  // slot 29
    virtual bool isCapture() const { return false; }  // slot 30
    virtual void playLocalVibration(int, ml::PadVibrationInfo const&) {}  // slot 31
    virtual void stopLocalVibration(int) {}  // slot 32
    virtual void loadLocalVibration(unsigned int, void*, unsigned long) {}  // slot 33
    virtual void viBeginFrame();  // slot 34

    // whether the pad device is set up (fw::PadManager::isInitialized requires it)
    static bool isInitialized();
    static int getPadMax();
    static bool isConnectPad(int pad);
    static int getStylePad(int pad);
    static int getUserSelectPadID();
    static unsigned int getBtn(int pad);
    static unsigned int getDown(int pad);
    static unsigned int getUp(int pad);
    static unsigned int getDbl(int pad);
    static float getALX(int pad, bool deadZone);
    static float getALY(int pad, bool deadZone);
    static float getARX(int pad, bool deadZone);
    static float getARY(int pad, bool deadZone);
    static void playVibration(int pad, const PadVibrationInfo& info);
    static void stopVibration(int pad);
    static void loadVibration(unsigned int id, void* data, unsigned long size);

    unsigned char pad_1b8[0x34];
    // the per-pad button words getDown/getUp/getBtn/getDbl return, one per pad of getPadMax()
    // (the names are not the original's)
    unsigned int m_down[11];  // 0x1EC
    unsigned int m_up[11];    // 0x218
    unsigned int m_btn[11];   // 0x244
    unsigned int m_dbl[11];   // 0x270
    unsigned char pad_29c[0x2A4];
    // getALX..getARY return 0 for a stick value inside (-m_deadZone, m_deadZone) when asked to
    // (the name is not the original's)
    float m_deadZone;  // 0x540
};
}  // namespace ml

#endif
