#ifndef CLASSES_GF_TUNK_B607D8_H
#define CLASSES_GF_TUNK_B607D8_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/ui/UIObjectListener.h"

namespace gf { class GfMenuCallContext; }
namespace gf { class GfMenuReferenceNumber; }
namespace ui { struct EventData; }

namespace gf {
// table 0x7100B607D8: the menu object of gf_menu_obj_btlch_telop.cpp (new in 3.0.1; nothing names the class yet). It
// shows the battle challenge's telops (LAY_start, TXT_wave_title, ...)
class GfMenuObjBtlchTelop : public ::gf::GfMenuObject {
public:
    GfMenuObjBtlchTelop(unsigned int handle);
    virtual ~GfMenuObjBtlchTelop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name them. seqAnimWait waits for m_animHandle's animation; seqEnd sends LAY_main the close event
    // (0x22); seqCtrlWait waits for m_ctrl's control; seqResultOpenSuccessSE and seqResultOpenFailedSE do nothing (true
    // at once).
    bool seqAnimWait();
    bool seqEnd();
    bool seqCtrlWait();
    bool seqResultOpenSuccessSE();
    bool seqResultOpenFailedSE();
    // 2.0.0's symbols name them. What they do: each shows a telop part, plays its animation on its base image (into
    // m_animHandle) and starts a control (into m_ctrl): seqStartTitleOpen the start (LAY_start,
    // "start_battlechallenge", SE dlc_se_btl_chbtl001 unless GfMenuObjBtlchTutorial::isOpen), then seqStartOpen
    // (LAY_start_bch, "start_start"), then seqStartFadeout ("end", fades LAY_start_bch out); seqWaveOpen the wave
    // (LAY_wave, "start", SE dlc_se_btl_chbtl002) and seqWaveOpen2 the timed wave ("start_time"), ended by
    // seqWaveFadeout ("end") and seqWaveFadeout2 ("end_time"); seqResultOpenSuccess the result's success
    // (LAY_success_title, "start_success") with seqResultFadeoutSuccess ("end_success"); seqResultOpenFailed its
    // failure or time-up (m_result 1: LAY_failed_title, 2: LAY_timeup_title, "start_failed") with
    // seqResultFadeoutFailed ("end_failed"). All return true.
    bool seqStartTitleOpen();
    bool seqWaveOpen();
    bool seqWaveOpen2();
    bool seqResultOpenSuccess();
    bool seqResultOpenFailed();
    bool seqStartOpen();
    bool seqStartFadeout();
    bool seqWaveFadeout();
    bool seqWaveFadeout2();
    bool seqResultFadeoutSuccess();
    bool seqResultFadeoutFailed();
    // 2.0.0's symbols name it. What it does: clears m_seq, stops m_ctrl's control and m_animHandle's animation, and
    // hides LAY_start, LAY_start_title, LAY_start_bch, LAY_wave, LAY_wave_title, LAY_result, LAY_success_title,
    // LAY_failed_title, LAY_timeup_title and LAY_result_info.
    void reset();
    // what open sends with its open event (0x21); the names are not the original's
    struct OpenParam {
        int m_type;   // the event's first parameter
        int m_value;  // its second, for types 1, 2 and 3 only
    };
    // 2.0.0's symbols name it. What it does: when GfMenuObjUtil::isValidExpansion(1),
    // GfGameManager::isBattleArenaActive and checkCCStart(context) hold and attached object 0x88 lives, sends it the
    // open event (0x21) with param and starts the context on it (true); otherwise aborts the context (false).
    // GfMenuObjBtlchTutorial::seqStartTelop calls it.
    static bool open(GfMenuCallContext* context, const OpenParam& param);
    // 2.0.0's symbols name it. What it does: when GfMenuObjUtil::isValidExpansion(1) and
    // GfGameManager::isBattleArenaActive hold and attached object 0x88 lives, sends it the close event (0x22).
    // GfMenuObjBtlchTutorial::TutorialListener::reciveEvent, UpdateFutureView and GfMenuObjTips::TutorialListener::reciveEvent call it.
    static void forceClose();
    unsigned char pad_24[4];
    GfMenuSequence<GfMenuObjBtlchTelop, 8> m_seq;
    int m_ctrl;  // a control slot update and seqCtrlWait wait for, -1 for none (the name is not the original's)
    unsigned int m_animHandle;  // the object seqAnimWait waits for (the name is not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_number;  // the reference adapters' number (the name is not the original's)
    unsigned char pad_2C8[4];
    // the result seqResultOpenFailed and seqResultFadeoutFailed show: 1 failed, 2 time up (OpenParam::m_value of an open of type
    // 3; the name is not the original's)
    unsigned int m_result;
};

// table 0x7100B60820: GfMenuObjBtlchTelop's listener (nothing names the class yet)
class TUnk_B60820 : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    TUnk_B60820(GfMenuObjBtlchTelop* owner) : m_open(), pad_10(), m_owner(owner) {}
    virtual ~TUnk_B60820() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_open;  // 1 while a telop runs: set by the open event (0x21), cleared by close (0x22) and 1 (the name is not the original's)
    unsigned char pad_10[0xC];
    GfMenuObjBtlchTelop* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
