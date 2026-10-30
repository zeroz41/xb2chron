#ifndef CLASSES_GF_TUNK_B60928_H
#define CLASSES_GF_TUNK_B60928_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf {
// table 0x7100B60928: the menu object of gf_menu_obj_btl_time.cpp (new in 3.0.1; nothing names the class yet). It
// shows the battle challenge's time, ether and score (LAY_time, LAY_ether, LAY_score), attached as object 0x87
class TUnk_B60928 : public ::gf::GfMenuObject {
public:
    class TUnk_B60970;
    class TUnk_B60998;
    class TUnk_B609C0;

    TUnk_B60928(unsigned int handle);
    virtual ~TUnk_B60928();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Static members: their code is in this
    // unit among the class's functions and takes no instance; they reach the object through attached object 0x87.
    // fn_71003B48B8 sends event 0x103 to LAY_time, and to LAY_ether and LAY_score when GfMenuObjUtil::fn_710048FD30(1)
    // holds (initialize calls it last; the battle challenge manager calls it when it resets).
    static void fn_71003B48B8();
    // fn_71003B4AD8 sends the open event (0x21, first parameter `param`) to part `part` (0 LAY_time, 1 LAY_ether,
    // 2 LAY_score: fn_71003B4B7C), for parts other than 0 only when fn_710048FD30(1) holds and fn_710048FD30(3) does
    // not; fn_71003B4C24 sends that part the close event (0x22).
    static void fn_71003B4AD8(int part, unsigned int param);
    // fn_71003B4B7C: the handle of part `part` under `handle` (LAY_time, LAY_ether, LAY_score), 0 for any other
    // part; LAY_ether and LAY_score only when `always` or GfGameManager::fn_71002AC580() holds
    static unsigned int fn_71003B4B7C(unsigned int handle, int part, bool always);
    static void fn_71003B4C24(int part);
    // fn_71003B4CC0 opens parts 0 and 1 and, by the short at 6 of GfGameManager::fn_71002AC5D8()'s record, opens
    // LAY_score with 0 (1), with 1 (3) or closes it (other values), all only when fn_710048FD30(1) holds;
    // fn_71003B4D3C closes parts 0, 1 and 2 (1 and 2 only when fn_710048FD30(1) holds)
    static void fn_71003B4CC0();
    static void fn_71003B4D3C();
    // fn_71003B4D80 / fn_71003B4E18 send LAY_time event 0x100 / 0x101 (its listener queues the new record
    // display / starts LAY_time_info's control)
    static void fn_71003B4D80();
    static void fn_71003B4E18();

    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: the jobs m_seq and m_seq2 call
    // on this object (Delegate<bool ()>::memberFuncInvoker<TUnk_B60928>), queued by this class's listeners and by
    // each other. LAY_time's new record (m_seq): fn_71003B52DC shows LAY_time_new_record, fades TXT_time_new_record
    // in (cmn_fade_motion_lr fade_in_l), starts IMG_time_new_record_eff's "start", then waits 5 frames, runs
    // fn_71003B5E54 (sound 0x22) and fn_71003B5E70 (until IMG_time_new_record_eff's animation stops), which queues
    // fn_71003B5F20 (fades TXT_time_new_record out, fade_out_r), fn_71003B6028 (until that control ends) and
    // fn_71003B60DC (hides LAY_time_new_record, sends LAY_time event 0x102). LAY_ether's box (m_seq2): fn_71003B5B28
    // fades TXT_ether_box_get in, fn_71003B6170 waits for that control, then 60 frames, then fn_71003B62C4 fades it
    // out (fade_out_r). All return true once done.
    bool fn_71003B52DC();
    bool fn_71003B5B28();
    bool fn_71003B5E54();
    bool fn_71003B5E70();
    bool fn_71003B5F20();
    bool fn_71003B6028();
    bool fn_71003B60DC();
    bool fn_71003B6170();
    bool fn_71003B62C4();

    unsigned char pad_24[4];
    GfMenuSequence<TUnk_B60928, 8> m_seq;   // LAY_time's jobs (the name is not the original's)
    GfMenuSequence<TUnk_B60928, 8> m_seq2;  // LAY_ether's jobs (the name is not the original's)
    int m_etherBox;  // the ether box LAY_ether's listener got last (event 0xD), 0 when reset (the name is not the original's)
};
}  // namespace gf

#endif
