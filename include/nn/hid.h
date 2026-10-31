#ifndef NN_HID_H
#define NN_HID_H

#include "nn/result.h"

namespace nn { namespace hid {

// the SDK's touch screen setup (ml::DevTouchNx::createDevice calls it)
void InitializeTouchScreen();
// the SDK's vibration file player (ml::DevPadNx::loadLocalVibration loads one per id; the size is the room
// DevPadNx::Impl's player entries leave it, its fields are not known)
class VibrationPlayer {
public:
    void Load(const void* data, unsigned long size);
    void SetLoop(bool loop);
    bool IsLoaded() const;
    void Stop();
    unsigned char pad_0[0xC0];
};
// the SDK's link between two vibration nodes (ml::DevPadNx::stopLocalVibration disconnects a pad's two; the size is
// the room DevPadNx::Impl::PadData leaves it, its fields are not known)
class VibrationNodeConnection {
public:
    void Disconnect();
    unsigned char pad_0[0x38];
};
// the SDK's mouse and keyboard setup (ml::DeviceNx::initializeSDK calls them)
void InitializeMouse();
void InitializeKeyboard();

// the SDK's controller support applet arguments (0x21C bytes; ml::ControllerApplet::showApplet fills it)
struct ControllerSupportArg {
    void SetDefault() {
        playerCountMin = 0;
        playerCountMax = 4;
        enableTakeOverConnection = true;
        enableLeftJustify = true;
        enablePermitJoyDual = true;
        enableSingleMode = false;
        enableIdentificationColor = false;
        enableExplainText = false;
    }

    signed char playerCountMin;              // 0x00
    signed char playerCountMax;              // 0x01
    bool enableTakeOverConnection;           // 0x02
    bool enableLeftJustify;                  // 0x03
    bool enablePermitJoyDual;                // 0x04
    bool enableSingleMode;                   // 0x05
    bool enableIdentificationColor;          // 0x06
    unsigned char identificationColor[4][4]; // 0x07 (nn::util::Color4u8Type)
    bool enableExplainText;                  // 0x17
    char explainText[4][0x81];               // 0x18
};
struct ControllerSupportResultInfo {
    signed char playerCount;  // 0x00
    unsigned int selectedId;  // 0x04 (an NpadIdType)
};
Result ShowControllerSupport(ControllerSupportResultInfo* info, const ControllerSupportArg& arg);

}}  // namespace nn::hid

#endif
