#ifndef CLASSES_GF_GFMENUOBJBUTTONCHALLENGE2_H
#define CLASSES_GF_GFMENUOBJBUTTONCHALLENGE2_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UICtrlSimple.h"
#include "classes/ui/UICtrlSimpleUpdater.h"
#include "gf/GfMenuSequence.h"
#include "mm/Pnt.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfMenuCallContext; }

namespace gf {
// table 0x7100B609E8
// Field names are not the original's unless they spell a BDAT column (importOpenParam reads "Speed", "Wait",
// "Type", "BtnType%d", "Point%d", "Start%d", "Hit%d", "End%d", "InputType", "PushRange", "PushSweetRange",
// "PushSweetFrame", "MashingCount", "MashingTime").
class GfMenuObjButtonChallenge2 : public ::gf::GfMenuObject {
public:
    class MainListener;
    class RingListener;
    // how a challenge opens: the last 8 bytes of OpenParam (StateSalvageDiveStart gives a speed of 0.16;
    // openSequence's two flags are m_flag0 and m_flag1)
    struct OptionParam {
        OptionParam() {
            m_unk2 = false;
            m_flag0 = false;
            m_flag1 = false;
            m_speed = 0.16f;
        }
        OptionParam(bool flag0, bool flag1, bool unk2, float speed)
            : m_flag0(flag0), m_flag1(flag1), m_unk2(unk2), m_speed(speed) {}
        bool m_flag0;
        bool m_flag1;
        bool m_unk2;
        float m_speed;
    };
    // one button of a challenge (0x14 bytes)
    struct Button {
        unsigned char m_btnType;    // 1-5
        unsigned char m_inputType;  // 1 push, 2 mashing
        unsigned char m_point;      // the points of all buttons add up to 100
        unsigned short m_pushRange;
        unsigned short m_pushSweetRange;
        unsigned char m_mashingCount;
        unsigned short m_mashingTime;
        unsigned short m_start;
        unsigned short m_hit;
        unsigned short m_end;
        unsigned short m_pushSweetFrame;
    };
    // one button's ring: its scale control and the updater running it (0x48 bytes; seqRunningV2 reads the
    // control's value as setRingScaleV2's scale; the name is not the original's)
    struct Ring {
        ui::UICtrlSimple<1> m_ctrl;
        ui::UICtrlSimpleUpdater<ui::UICtrlSimple<1> > m_updater;
    };
    struct OpenParam {
        OpenParam() : m_speed(0), m_wait(0), m_type(0), m_buttons(), m_option(false, true, false, 0.25f) {}
        unsigned short m_speed;
        unsigned short m_wait;
        unsigned char m_type;
        mm::mtl::FixedVector<Button, 3> m_buttons;
        OptionParam m_option;
    };

    GfMenuObjButtonChallenge2(unsigned int handle);
    virtual ~GfMenuObjButtonChallenge2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    static void open(GfMenuCallContext* context, const OpenParam& param, unsigned int id);
    static void open(GfMenuCallContext* context, unsigned int id, bool flag0, bool flag1);
    static void importOpenParam(OpenParam& param, unsigned int id);
    static void open(GfMenuCallContext* context, unsigned int id, const OptionParam& param);
    static void openSequence(GfMenuCallContext* context, unsigned int id, bool flag0, bool flag1);
    static void close(GfMenuCallContext* context);
    static void resume(GfMenuCallContext* context);
    static void setSpeedFactor(GfMenuCallContext* context, float factor);
    // 2.0.0's symbols name it: LAY_main's display priority (initialize keeps it; open gives it back to the opened
    // object's parent outside battle)
    static unsigned int s_DefRootPrio;

    void setup(const OpenParam& param, unsigned int index, bool flag);
    bool seqStart();
    void setupV2(const OpenParam& param);
    bool seqRunningV2();
    bool seqClose();
    bool seqEnd();
    void pushChallengeButtonV2(unsigned char button);
    void pushChallengeButton(unsigned char button);
    void setRingScaleV2(unsigned int index, float scale);
    void nextChallenge();
    bool seqCheckSequence();
    bool seqAppearCursor();
    bool seqMovePush();
    bool seqMoveMashing();
    bool seqSuccess();
    bool seqFailed();
    bool seqWaitMashing();
    bool seqWaitRestartV2();
    bool seqResultStart();
    bool seqResultWait();
    bool seqWaitMashingV2();

    OpenParam m_param;               // 0x28
    unsigned int m_index;            // 0x80: the button being challenged
    unsigned int pad_84;
    unsigned int pad_88;
    unsigned int pad_8C;
    unsigned int pad_90;
    unsigned int pad_94;
    unsigned int m_score;            // 0x98: what nextChallenge reports
    float m_speedFactor;             // 0x9C
    GfMenuSequence<GfMenuObjButtonChallenge2, 8> m_seq;  // 0xA0
    mm::mtl::FixedVector<unsigned int, 4> pad_330;
    mm::mtl::FixedVector<float, 1> pad_348;  // 0x348: seqMoveMashing keeps m_ctrl0's latest value in it
    bool pad_358;
    bool m_resultSent;               // 0x359: nextChallenge sent the result
    unsigned short pad_35A;
    unsigned short m_resultWait;     // 0x35C: frames seqResultWait waits before it fades the result out
    unsigned short pad_35E;
    mm::Pnt<short> m_guidePos;       // 0x360: LAY_guide_contents' center
    ui::UICtrlSimple<1> m_ctrl0;     // 0x368
    ui::UICtrlSimpleUpdater<ui::UICtrlSimple<1> > m_updater0;  // 0x390
    short m_hitSize;                 // 0x3B0: POL_challenge_hit_a@01's size
    short m_ringSize;                // 0x3B2: POL_ring_v2@01's size
    Ring m_rings[3];                 // 0x3B8: LAY_challenge_v2@01-03 (seqRunningV2 indexes them by button)
    unsigned int pad_490;            // 0x490: seqWaitMashingV2 counts frames in it up to pad_498
    float pad_494;
    unsigned int pad_498;
    unsigned int pad_49C;
    bool pad_4A0;
};
}  // namespace gf

#endif
