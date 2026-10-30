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
class TUnk_B607D8 : public ::gf::GfMenuObject {
public:
    TUnk_B607D8(unsigned int handle);
    virtual ~TUnk_B607D8();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they are its sequence's
    // jobs (m_seq calls them on this object; the functions that queue them are this class's too).
    // fn_71003B1DA4 waits for m_animHandle's animation; fn_71003B219C sends LAY_main the close event (0x22);
    // fn_71003B2558 waits for m_ctrl's control; fn_71003B259C and fn_71003B26B4 do nothing (true at once).
    bool fn_71003B1DA4();
    bool fn_71003B219C();
    bool fn_71003B2558();
    bool fn_71003B259C();
    bool fn_71003B26B4();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they are its sequence's
    // jobs too (TUnk_B60820::reciveEvent and the other jobs queue them on this object). What they do: each shows a
    // telop part, plays its animation on its base image (into m_animHandle) and starts a control (into m_ctrl):
    // fn_71003B12E8 the start (LAY_start, "start_battlechallenge", SE dlc_se_btl_chbtl001 unless
    // TUnk_B60848::fn_71003B2B30), then fn_71003B1E08 (LAY_start_bch, "start_start"), then fn_71003B1FEC ("end",
    // fades LAY_start_bch out); fn_71003B14B8 the wave (LAY_wave, "start", SE dlc_se_btl_chbtl002) and
    // fn_71003B1688 the timed wave ("start_time"), ended by fn_71003B21F0 ("end") and fn_71003B23A4 ("end_time");
    // fn_71003B1858 the result's success (LAY_success_title, "start_success") with fn_71003B25A4 ("end_success");
    // fn_71003B1B2C its failure or time-up (m_result 1: LAY_failed_title, 2: LAY_timeup_title, "start_failed") with
    // fn_71003B26BC ("end_failed"). All return true.
    bool fn_71003B12E8();
    bool fn_71003B14B8();
    bool fn_71003B1688();
    bool fn_71003B1858();
    bool fn_71003B1B2C();
    bool fn_71003B1E08();
    bool fn_71003B1FEC();
    bool fn_71003B21F0();
    bool fn_71003B23A4();
    bool fn_71003B25A4();
    bool fn_71003B26BC();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because TUnk_B60820::reciveEvent
    // calls it on its owner before each open and on close. What it does: clears m_seq, stops m_ctrl's control and
    // m_animHandle's animation, and hides LAY_start, LAY_start_title, LAY_start_bch, LAY_wave, LAY_wave_title,
    // LAY_result, LAY_success_title, LAY_failed_title, LAY_timeup_title and LAY_result_info.
    void fn_71003B0E58();
    // what fn_71003B0CE4 sends with its open event (0x21); the names are not the original's
    struct OpenParam {
        int m_type;   // the event's first parameter
        int m_value;  // its second, for types 1, 2 and 3 only
    };
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its unit holds only this
    // class's functions. What it does: when GfMenuObjUtil::fn_710048FD30(1), GfGameManager::fn_71002AC580 and
    // checkCCStart(context) hold and attached object 0x88 lives, sends it the open event (0x21) with param and
    // starts the context on it (true); otherwise aborts the context (false). TUnk_B60848::fn_71003B3EF4 calls it.
    static bool fn_71003B0CE4(GfMenuCallContext* context, const OpenParam& param);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member as fn_71003B0CE4, its
    // opening counterpart. What it does: when GfMenuObjUtil::fn_710048FD30(1) and GfGameManager::fn_71002AC580 hold
    // and attached object 0x88 lives, sends it the close event (0x22). fn_71003B34D0, fn_7100007D0C and
    // fn_7100488958 call it.
    static void fn_71003B0DE0();
    unsigned char pad_24[4];
    GfMenuSequence<TUnk_B607D8, 8> m_seq;
    int m_ctrl;  // a control slot update and fn_71003B2558 wait for, -1 for none (the name is not the original's)
    unsigned int m_animHandle;  // the object fn_71003B1DA4 waits for (the name is not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_number;  // the reference adapters' number (the name is not the original's)
    unsigned char pad_2C8[4];
    // the result fn_71003B1B2C and fn_71003B26BC show: 1 failed, 2 time up (OpenParam::m_value of an open of type
    // 3; the name is not the original's)
    unsigned int m_result;
};

// table 0x7100B60820: TUnk_B607D8's listener (nothing names the class yet)
class TUnk_B60820 : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    TUnk_B60820(TUnk_B607D8* owner) : m_open(), pad_10(), m_owner(owner) {}
    virtual ~TUnk_B60820() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_open;  // 1 while a telop runs: set by the open event (0x21), cleared by close (0x22) and 1 (the name is not the original's)
    unsigned char pad_10[0xC];
    TUnk_B607D8* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
