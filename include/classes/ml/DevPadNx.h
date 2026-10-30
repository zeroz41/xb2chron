#ifndef CLASSES_ML_DEVPADNX_H
#define CLASSES_ML_DEVPADNX_H

#include "classes/ml/DevPad.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/UniquePtr.h"

namespace ml { class PadVibrationInfo; }

namespace ml {
// table 0x7100B76678
class DevPadNx : public ::ml::DevPad {
public:
    // the Nx pad state the getters read (named by the symbols; layout from DevPadNx's getters, field names are not
    // the original's)
    class Impl {
    public:
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
            unsigned char pad_1c[0x164];
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

        // named by the symbols: the state functions m_state runs (stateInitialize stores stateUpdate), the npad update
        // stateUpdate runs, the release releaseDevice forwards to
        void stateUpdate(float);
        void updateNpad();
        void release();
        // named by the symbols: starts a vibration on a pad's state (playLocalVibration forwards to it)
        void playVibration(PadData&, const PadVibrationInfo&);

        mm::mtl::Delegate<void(float)> m_state;   // 0x0 (updateDevice calls it; the name is not the original's)
        int m_stateId;                              // 0x20 (stateUpdate updates the npads in state 2)
        unsigned int m_npadId[4];                   // 0x24 (setUserSelectControllerID matches against these)
        unsigned char pad_34[0x3604];
        mm::mtl::FixedArray<PadData, 4> m_pads;     // 0x3638
        unsigned char pad_3c38[0x600];
        PadData m_selectPad;                        // 0x4238
        PadData m_emptyPad;                         // 0x43B8
        unsigned char pad_4538[8];
        int m_userSelect;                           // 0x4540
        int m_userSelectController;                 // 0x4544 (setUserSelectControllerID stores the matching index)
        int m_selectPadId;                          // 0x4548
    };

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

    unsigned char pad_544[4];
    mm::mtl::UniquePtr<Impl> m_impl;  // 0x548 (the name is not the original's)
};
}  // namespace ml

#endif
