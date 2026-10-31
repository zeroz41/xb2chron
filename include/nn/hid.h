#ifndef NN_HID_H
#define NN_HID_H

#include "nn/result.h"

namespace nn { namespace hid {

// the SDK's touch screen setup (ml::DevTouchNx::createDevice calls it)
void InitializeTouchScreen();

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
