#ifndef CLASSES_FW_PADMANAGER_H
#define CLASSES_FW_PADMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/fw/PadResEventManager.h"
#include "classes/ml/DevGraphCB.h"
#include "classes/fw/PadFilterStd.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "ml/PadVibrationInfo.h"
#include "fw/PadData.h"
#include "mm/mtl/Bitflag.h"
#include "mm/mtl/FixedArray.h"

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B42678; its base at 0x10 is its singleton (the destructor stores PtrSingleton<fw::PadManager>'s table
// there and clears its instance), the one at 0x18 ml::DevGraphCB
class PadManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::PadManager>,
                   public ::ml::DevGraphCB {
public:
    PadManager();  // out of line (Framework::createManager calls it)
    virtual ~PadManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    // inline: emitted with the table, after initVibData (0x7100196AF8)
    virtual const char* getName() const { return "PadManager"; }  // slot 5
    virtual bool isInitialized() const;  // slot 6
    virtual void debugDraw(int, int);  // slot 8
    virtual void update(fw::UpdateInfo const&);  // slot 9
    virtual void viBeginFrame();  // slot 10

    // one button's hold timers for a pad (12 bytes; updatePadData keeps 32 per pad). The names are not the
    // original's
    struct PadWork {
        float m_repeatTime;  // time held since the last repeat (cleared on release)
        float m_holdTime;    // time held (cleared on release; a short hold makes a tap, a long one a long press)
        int m_isRepeating;   // set after the first repeat: later repeats wait m_repeatInterval
    };
    // a pad's key assignment (0x54 bytes; the constructor maps every id to itself). The name is not the original's
    struct KeyAssign {
        int pad_0;
        int m_keys[16];  // for button id i + 1 the button id read from the raw pad (0: none)
        // for the stick axes lx, ly, rx, ry the raw axis id 17..20 (lx..ry) read, negated when negative (0: none)
        int m_axes[4];
    };

    // the named members (the symbols); what the comments say they do is read from their code
    // reads pad padNo from ml::DevPad through its filter into m_rawPads, then remaps it (replacePadData)
    void makePadData(int padNo);
    // the button bits the sticks give, the repeats, taps and long presses of data from the previous buttons prevBtn
    void updatePadData(int padNo, PadData& data, unsigned int prevBtn,
                       mm::mtl::FixedArray<mm::mtl::FixedArray<PadWork, 32>, 12>& works, float dt);
    // which pad becomes control pad slot (the user-selected one, the first with a full controller, or the applet's)
    void updateControlPadNo(int slot);
    // m_pads[padNo] from m_rawPads[padNo] through the pad's key assignment
    void replacePadData(int padNo);
    static void initVibData();  // static: Framework::initializeManager calls it with no object
    static void playVibration(const ml::PadVibrationInfo& info);
    // the control pad's data of pad padNo for this frame (m_nullPad's without a manager)
    static const PadData& getControlPadData(int padNo);

    // what getControlPadData returns without a manager (0x7100B42630)
    static PadData m_nullPad;
    // a stick counts as tilted past this (0.6f; minigame::tora::minigame::update_pad compares the squared length)
    static const float ANALOG_TRIGGER_THRESHOLD;

    // the field names below are not the original's
    TUnk_B42870* m_filters[12];  // 0x20 each pad's filter (makePadData)
    PadData m_rawPads[12];       // 0x80 each pad as read (makePadData)
    PadData m_pads[12];          // 0x3E0 each pad through its key assignment (replacePadData)
    mm::mtl::FixedArray<mm::mtl::FixedArray<PadWork, 32>, 12> m_rawWorks;  // 0x740 m_rawPads' timers
    mm::mtl::FixedArray<mm::mtl::FixedArray<PadWork, 32>, 12> m_works;     // 0x1940 m_pads' timers
    // the control pads' data for this frame (getControlPadData); the first one's pad gets the vibrations
    PadData m_controlPads[12];
    PadData m_rawControlPads[12];  // 0x2EA0 the same from m_rawPads (update)
    KeyAssign m_keyAssigns[12];    // 0x3200
    int m_controlPadNos[12];       // 0x35F0 the pad of each control pad slot (-1: none)
    int m_rawControlPadNos[12];    // 0x3620 the same for m_rawControlPads
    mm::mtl::Bitflag<32> m_activePads;  // 0x3650 the pads update reads
    unsigned char pad_3654[0x4];
    long m_clock;  // 0x3658 the ml::DevClock clock of the last viBeginFrame
    float m_repeatInterval;  // 0x3660 the hold time between repeats after the first
    float m_repeatDelay;     // 0x3664 the hold time before the first repeat
    float m_tapMinTime;      // 0x3668 a release after a hold longer than this ...
    float m_longPressTime;   // 0x366C ... and shorter than this is a tap; longer is a long press
    int m_userSelectPadNo;   // 0x3670 the pad ml::DevPad's user selection picked last (-1: none)
    int m_connectPadCount;   // 0x3674 the local connected pad count seen last (-1: unknown)
    int m_operationMode;     // 0x3678 the ml::DevPerf operation mode seen last (-1: none yet)
    unsigned char pad_367C[0x4];
    // 0x3680 a FixedQueue<T*, 16> of objects viBeginFrame calls slot 0 of (count 0x3700, first 0x3708); nothing
    // names T yet
    unsigned char pad_3680[0x90];
    // its destructor runs from ~PadManager (the name is not the original's)
    PadResEventManager m_padResEventManager;
};
}  // namespace fw

#endif
