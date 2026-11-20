#ifndef CLASSES_ML_DEVPADNX_H
#define CLASSES_ML_DEVPADNX_H

#include <stddef.h>
#include <string.h>

#include "classes/ml/DevPad.h"
#include "ml/WorkUtil.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/UniquePtr.h"
#include "nn/hid.h"

namespace ml { class PadVibrationInfo; }

namespace ml {
// table 0x7100B76678
class DevPadNx : public ::ml::DevPad {
public:
    // the Nx pad state the getters read (named by the symbols; layout from DevPadNx's getters, field names are not
    // the original's)
    class Impl {
    public:
        // 0x71006AD2AC, inline (the original keeps only its base-object copy, the one DevPadNx's constructor calls)
        Impl();
        // one vibration device of a pad (initializeVibration fills it; the names are not the original's): the SDK's
        // handle and info, a value reset to 0, the resting vibration value
        struct VibDevice {
            nn::hid::VibrationDeviceHandle m_handle;  // 0x00
            nn::hid::VibrationDeviceInfo m_info;      // 0x04
            int pad_c;                                // 0x0C (initializeVibration clears it)
            nn::hid::VibrationValue m_value;          // 0x10
        };
        // one pad's state (0x180 bytes; FixedArray<PadData, 4> names it)
        struct PadData {
            unsigned int m_btn;        // 0x0 (getLocalBtn)
            float m_alx;               // 0x4 (getLocalALX)
            float m_aly;               // 0x8 (getLocalALY)
            float m_arx;               // 0xC (getLocalARX)
            float m_ary;               // 0x10 (getLocalARY)
            bool m_connect;            // 0x14 (isLocalConnect)
            unsigned char pad_15[3];
            int m_style;               // 0x18 (getLocalStyle)
            // the vibration devices initializeVibration found (GetVibrationDeviceHandles' count; the names are not
            // the original's)
            int m_vibDeviceCount;      // 0x1C
            VibDevice m_vibDevices[2];  // 0x20
            // 0x60.. the vibration stopLocalVibration stops and resets (the names are not the original's): the
            // player id (1..63, an index into m_players), a state (3 once stopped), four scales (1.0 once stopped),
            // a value (0 once stopped), two flags (playing, devices set up: initializeVibration sets it once)
            unsigned int m_vibId;      // 0x60
            int m_vibState;            // 0x64
            float m_vibScale0;         // 0x68
            float m_vibScale1;         // 0x6C
            float m_vibScale2;         // 0x70
            float m_vibScale3;         // 0x74
            int m_vibValue;            // 0x78
            bool m_vibOn;              // 0x7C
            bool m_vibInit;            // 0x7D
            unsigned char pad_7e[2];
            // the two vibration targets the connections link (DevPadNx's destructor destroys them; the names are
            // not the original's)
            nn::hid::VibrationTarget m_vibTarget0;  // 0x80
            nn::hid::VibrationTarget m_vibTarget1;  // 0xC8
            nn::hid::VibrationNodeConnection m_vibConnect0;  // 0x110
            nn::hid::VibrationNodeConnection m_vibConnect1;  // 0x148
        };
        // a loaded vibration file (FixedArray<VibPlayerData, 64> names the type; the fields' names are not the
        // original's): loadLocalVibration copies the file into m_data and loads m_player from it
        struct VibPlayerData {
            void* m_data;               // 0x00
            unsigned long m_size;       // 0x08
            unsigned int m_id;          // 0x10
            unsigned char pad_14[4];
            nn::hid::VibrationPlayer m_player;  // 0x18
        };

        // the state a getter reads for a pad: the user-selected pad's own entry for its id, pad 4 the selected
        // entry, an unknown pad the empty one (the name is not the original's)
        const PadData& getPadData(int pad) const {
            if (m_selectPadId == pad) {
                return m_selectPad;
            }
            if (pad == 4) {
                return getPad(m_userSelect, m_userSelect >= 0);
            }
            return getPad(pad, pad < 4);
        }
        PadData& getPadData(int pad) {
            if (m_selectPadId == pad) {
                return m_selectPad;
            }
            if (pad == 4) {
                return getPad(m_userSelect, m_userSelect >= 0);
            }
            return getPad(pad, pad < 4);
        }
        PadData& getPad(int index, bool valid) {
            return valid ? m_pads[index] : m_emptyPad;
        }
        // the entry at index when valid, else the empty one (the original computes both before choosing; the name
        // is not the original's)
        const PadData& getPad(int index, bool valid) const {
            return valid ? m_pads[index] : m_emptyPad;
        }
        // getLocalUserSelectPadID's value: 4 when the selected controller is the selected entry (the name is not
        // the original's)
        int getUserSelectPadID() const {
            int id = m_userSelectController;
            return id == m_userSelect ? 4 : id;
        }
        // setUserSelectControllerID's work: the index of the controller with this id, -1 for none (the name is not
        // the original's)
        void setUserSelectController(unsigned int id) {
            m_userSelectController = -1;
            for (int i = 0; i < 4; ++i) {
                if (m_npadId[i] == id) {
                    m_userSelectController = i;
                    break;
                }
            }
        }

        // named by the symbols: the pad setup stateInitialize runs first
        void initPad();
        // named by the symbols: the state functions m_state runs (stateInitialize stores stateUpdate), the npad update
        // stateUpdate runs, the release releaseDevice forwards to
        void stateInitialize(float);
        void stateUpdate(float);
        void stateFinalize(float);
        void updateNpad();
        void release();
        // named by the symbols: starts a vibration on a pad's state (playLocalVibration forwards to it)
        void playVibration(PadData&, const PadVibrationInfo&);
        // stops a connected full-key or joy-dual pad's playing vibration and resets its state (stopLocalVibration's
        // and stateFinalize's inline work; the name is not the original's)
        void stopVibration(PadData& pad) {
            if (pad.m_connect && pad.m_vibOn && (pad.m_style == 1 || pad.m_style == 3)) {
                unsigned int id = pad.m_vibId;
                if (id != 0) {
                    bool valid = id - 1 < 63;
                    nn::hid::VibrationPlayer& player = m_players[id].m_player;
                    if (valid && player.IsLoaded()) {
                        player.Stop();
                        pad.m_vibConnect0.Disconnect();
                        pad.m_vibConnect1.Disconnect();
                        pad.m_vibId = 0;
                        pad.m_vibState = 3;
                        pad.m_vibScale0 = 1.0f;
                        pad.m_vibScale2 = 1.0f;
                        pad.m_vibScale1 = 1.0f;
                        pad.m_vibScale3 = 1.0f;
                        pad.m_vibValue = 0;
                        pad.m_vibOn = false;
                        pad.m_vibInit = false;
                    }
                }
            }
        }
        // a connected pad whose style changed or that went away, once stopVibration ran: resets the vibration and
        // clears the input up to the connect flag (updateNpad's inline work; the name is not the original's)
        void resetPad(PadData& pad) {
            pad.m_vibId = 0;
            pad.m_vibState = 3;
            pad.m_vibScale0 = 1.0f;
            pad.m_vibScale2 = 1.0f;
            pad.m_vibScale1 = 1.0f;
            pad.m_vibScale3 = 1.0f;
            pad.m_vibValue = 0;
            pad.m_vibOn = false;
            pad.m_vibInit = false;
            pad.m_style = 0;
            memset(&pad, 0, offsetof(PadData, m_connect) + sizeof(pad.m_connect));
        }

        // the pad styles initializeVibration sets up (named by its instantiations; their members are not the
        // original's): how many vibration devices it asks for, and the style it asks them for
        struct PadFullKeyState {
            static const int VibrationDeviceCount = 2;
            typedef nn::hid::NpadStyleFullKey Style;
        };
        struct PadHandheldState {
            static const int VibrationDeviceCount = 2;
            typedef nn::hid::NpadStyleHandheld Style;
        };
        struct PadJoyDualState {
            static const int VibrationDeviceCount = 1;
            typedef nn::hid::NpadStyleJoyDual Style;
        };
        // named by the symbols: sets up a pad's vibration devices once (updateNpad calls it for a new or changed pad)
        template <typename T>
        void initializeVibration(unsigned int id, PadData& pad);
        // named by the symbols: reads a pad's input from its npad state (0x71006AC804, 0x71006ACB08, 0x71006ACE0C)
        template <typename T>
        void updateTpad(PadData& pad, const T& state);

        mm::mtl::Delegate<void(float)> m_state;   // 0x0 (updateDevice calls it; the name is not the original's)
        int m_stateId;                              // 0x20 (stateUpdate updates the npads in state 2)
        unsigned int m_npadId[4];                   // 0x24 (setUserSelectControllerID matches against these)
        unsigned char pad_34[4];
        mm::mtl::FixedArray<VibPlayerData, 64> m_players;  // 0x38 (the name is not the original's)
        mm::mtl::FixedArray<PadData, 4> m_pads;     // 0x3638
        // a second set of pad states (DevPadNx's destructor destroys it with the same FixedArray<PadData, 4>
        // destructor as m_pads; its use is not known)
        mm::mtl::FixedArray<PadData, 4> pad_3c38;  // 0x3C38
        PadData m_selectPad;                        // 0x4238
        PadData m_emptyPad;                         // 0x43B8
        unsigned char pad_4538[4];
        int m_padCount;                             // 0x453C (stateFinalize stops the first m_padCount pads; the name is not the original's)
        int m_userSelect;                           // 0x4540
        int m_userSelectController;                 // 0x4544 (setUserSelectControllerID stores the matching index)
        int m_selectPadId;                          // 0x4548
        int m_connectPadCount;                      // 0x454C (getLocalConnectPadCount returns it; the name is not the original's)
        unsigned char pad_4550[0x8];                // DeviceNx::createDevice allocates 0x4558 bytes
    };

    // the key function: its body is empty, the Impl (m_impl) and the bases are destroyed inline
    // inline: ml::DeviceNx::createDevice builds it (the original has no out-of-line copy)
    DevPadNx(const char* name, WorkObj* parent)
        : DevPad(name, parent), m_impl(new (WorkUtil::getWorkMem(), nullptr, 0, 8, false) Impl()) {}
    virtual ~DevPadNx();  // slot 0
    virtual bool isLocalConnect(int) const;  // slot 17
    virtual int getLocalStyle(int) const;  // slot 18
    virtual int getLocalUserSelectPadID() const;  // slot 19
    virtual unsigned int getLocalBtn(int) const;  // slot 20
    virtual float getLocalALX(int) const;  // slot 21
    virtual float getLocalALY(int) const;  // slot 22
    virtual float getLocalARX(int) const;  // slot 23
    virtual float getLocalARY(int) const;  // slot 24
    virtual void updateDevice(float);  // slot 25
    virtual bool createDevice();  // slot 26
    virtual void releaseDevice();  // slot 27
    virtual void playLocalVibration(int, ml::PadVibrationInfo const&);  // slot 31
    virtual void stopLocalVibration(int);  // slot 32
    virtual void loadLocalVibration(unsigned int, void*, unsigned long);  // slot 33

    // named by the symbols: makes the controller with this id the user-selected one (index into Impl's ids)
    static void setUserSelectControllerID(unsigned int);
    // named by the symbols: the number of connected local pads (0 without the device)
    static int getLocalConnectPadCount();

    unsigned char pad_544[4];
    mm::mtl::UniquePtr<Impl> m_impl;  // 0x548 (the name is not the original's)
};

// the vibration node thread (named by the symbols): DevPadNx::Impl::stateInitialize starts it and the periodic timer
// event it waits on, stateFinalize sets the quit flag and waits for it
namespace pad_detail {
extern bool g_IsQuitRequired;
extern nn::os::ThreadType g_thread;
extern nn::os::TimerEventType g_TimerEvent;
extern unsigned char g_ThreadStack1[0x2000];
void VibrationNodeThreadFunction(void*);
}  // namespace pad_detail
}  // namespace ml

#endif
