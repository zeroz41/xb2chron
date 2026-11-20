#ifndef NN_HID_H
#define NN_HID_H

#include "nn/result.h"
#include "nn/os.h"
#include "nn/util.h"

namespace nn { namespace hid {

// the SDK's controllers (ml::DevPadNx::Impl::updateNpad reads each pad's style set and state): an id, the style
// bits (the SDK's FullKey 0, Handheld 1, JoyDual 2)
typedef unsigned int NpadIdType;
struct NpadStyleTag;
typedef util::BitFlagSet<32, NpadStyleTag> NpadStyleSet;
typedef NpadStyleSet::Flag<0> NpadStyleFullKey;
typedef NpadStyleSet::Flag<1> NpadStyleHandheld;
typedef NpadStyleSet::Flag<2> NpadStyleJoyDual;
NpadStyleSet GetNpadStyleSet(const NpadIdType& id);

// the SDK's npad buttons, the flags of an NpadButtonSet (ml::DevPadNx::Impl::updateTpad maps them to its pad bits)
struct NpadButton {
    typedef util::BitFlagSet<64, NpadButton>::Flag<0> A;
    typedef util::BitFlagSet<64, NpadButton>::Flag<1> B;
    typedef util::BitFlagSet<64, NpadButton>::Flag<2> X;
    typedef util::BitFlagSet<64, NpadButton>::Flag<3> Y;
    typedef util::BitFlagSet<64, NpadButton>::Flag<4> StickL;
    typedef util::BitFlagSet<64, NpadButton>::Flag<5> StickR;
    typedef util::BitFlagSet<64, NpadButton>::Flag<6> L;
    typedef util::BitFlagSet<64, NpadButton>::Flag<7> R;
    typedef util::BitFlagSet<64, NpadButton>::Flag<8> ZL;
    typedef util::BitFlagSet<64, NpadButton>::Flag<9> ZR;
    typedef util::BitFlagSet<64, NpadButton>::Flag<10> Plus;
    typedef util::BitFlagSet<64, NpadButton>::Flag<11> Minus;
    typedef util::BitFlagSet<64, NpadButton>::Flag<12> Left;
    typedef util::BitFlagSet<64, NpadButton>::Flag<13> Up;
    typedef util::BitFlagSet<64, NpadButton>::Flag<14> Right;
    typedef util::BitFlagSet<64, NpadButton>::Flag<15> Down;
    typedef util::BitFlagSet<64, NpadButton>::Flag<16> StickLLeft;
    typedef util::BitFlagSet<64, NpadButton>::Flag<17> StickLUp;
    typedef util::BitFlagSet<64, NpadButton>::Flag<18> StickLRight;
    typedef util::BitFlagSet<64, NpadButton>::Flag<19> StickLDown;
    typedef util::BitFlagSet<64, NpadButton>::Flag<20> StickRLeft;
    typedef util::BitFlagSet<64, NpadButton>::Flag<21> StickRUp;
    typedef util::BitFlagSet<64, NpadButton>::Flag<22> StickRRight;
    typedef util::BitFlagSet<64, NpadButton>::Flag<23> StickRDown;
    typedef util::BitFlagSet<64, NpadButton>::Flag<24> LeftSL;
    typedef util::BitFlagSet<64, NpadButton>::Flag<25> LeftSR;
    typedef util::BitFlagSet<64, NpadButton>::Flag<26> RightSL;
    typedef util::BitFlagSet<64, NpadButton>::Flag<27> RightSR;
};
typedef util::BitFlagSet<64, NpadButton> NpadButtonSet;

struct AnalogStickState {
    int x;
    int y;
};
// the per-style states GetNpadState fills (0x28 bytes, the room updateNpad's buffer leaves; the SDK's fields)
struct NpadFullKeyState {
    long samplingNumber;
    NpadButtonSet buttons;
    AnalogStickState analogStickL;
    AnalogStickState analogStickR;
    unsigned int attributes;  // an NpadAttributesSet
};
struct NpadHandheldState {
    long samplingNumber;
    NpadButtonSet buttons;
    AnalogStickState analogStickL;
    AnalogStickState analogStickR;
    unsigned int attributes;
};
struct NpadJoyDualState {
    long samplingNumber;
    NpadButtonSet buttons;
    AnalogStickState analogStickL;
    AnalogStickState analogStickR;
    unsigned int attributes;
};
void GetNpadState(NpadFullKeyState* pOutValue, const NpadIdType& id);
void GetNpadState(NpadHandheldState* pOutValue, const NpadIdType& id);
void GetNpadState(NpadJoyDualState* pOutValue, const NpadIdType& id);

// the SDK's vibration devices (ml::DevPadNx::Impl::initializeVibration sets up a pad's): a handle, its kind and side,
// and a vibration value (Make gives the SDK's resting value, 160 and 320 Hz)
struct VibrationDeviceHandle {
    unsigned int _storage;
};
enum VibrationDeviceType {
    VibrationDeviceType_Unknown,
    VibrationDeviceType_LinearResonantActuator,
};
enum VibrationDevicePosition {
    VibrationDevicePosition_None,
    VibrationDevicePosition_Left,
    VibrationDevicePosition_Right,
};
struct VibrationDeviceInfo {
    VibrationDeviceType deviceType;
    VibrationDevicePosition position;
};
struct VibrationValue {
    static VibrationValue Make() {
        VibrationValue value = {0.0f, 160.0f, 0.0f, 320.0f};
        return value;
    }

    float amplitudeLow;
    float frequencyLow;
    float amplitudeHigh;
    float frequencyHigh;
};
int GetVibrationDeviceHandles(VibrationDeviceHandle* pOutValues, int count, const NpadIdType& id,
                              NpadStyleSet style);
void InitializeVibrationDevice(const VibrationDeviceHandle& handle);
void GetVibrationDeviceInfo(VibrationDeviceInfo* pOutValue, const VibrationDeviceHandle& handle);

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
    // out of line in the SDK (FixedArray<DevPadNx::Impl::VibPlayerData, 64>'s destructor calls it per entry)
    ~VibrationPlayer();
    unsigned char pad_0[0xC0];
};
// the SDK's link between two vibration nodes (ml::DevPadNx::stopLocalVibration disconnects a pad's two; the size is
// the room DevPadNx::Impl::PadData leaves it, its fields are not known)
class VibrationNodeConnection {
public:
    void Disconnect();
    // out of line in the SDK (DevPadNx::Impl::PadData's destructor calls it for both connections)
    ~VibrationNodeConnection();
    unsigned char pad_0[0x38];
};
// the SDK's vibration output node (DevPadNx::Impl::PadData holds two at 0x80 and 0xC8, its destructor calls this
// destructor for both; the size is the room between them, its fields are not known)
class VibrationTarget {
public:
    void SetVibrationDeviceHandle(const VibrationDeviceHandle& handle);
    ~VibrationTarget();
    unsigned char pad_0[0x48];
};
// the SDK's controller setup (ml::DevPadNx::Impl::stateInitialize calls it)
void InitializeNpad();
// the SDK's vibration node graph: Update runs it one sample on (ml::pad_detail::VibrationNodeThreadFunction calls it
// once per DefaultVibrationSampleInterval, the period its timer event runs at)
class VibrationNode {
public:
    static void Update();
    static const TimeSpan DefaultVibrationSampleInterval;
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
