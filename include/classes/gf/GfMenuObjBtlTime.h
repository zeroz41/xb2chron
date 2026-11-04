#ifndef CLASSES_GF_TUNK_B60928_H
#define CLASSES_GF_TUNK_B60928_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf {
// table 0x7100B60928: the menu object of gf_menu_obj_btl_time.cpp (new in 3.0.1; nothing names the class yet). It
// shows the battle challenge's time, ether and score (LAY_time, LAY_ether, LAY_score), attached as object 0x87
class GfMenuObjBtlTime : public ::gf::GfMenuObject {
public:
    class TimeListener;
    class EtherListener;
    class ScoreListener;

    GfMenuObjBtlTime(unsigned int handle);
    virtual ~GfMenuObjBtlTime();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 2.0.0's symbols name them. Static members: their code is in this unit among the class's functions and takes no
    // instance; they reach the object through attached object 0x87. reset sends event 0x103 to LAY_time, and to
    // LAY_ether and LAY_score when GfMenuObjUtil::isValidExpansion(1) holds (initialize calls it last; the battle
    // challenge manager calls it when it resets).
    static void reset();
    // fn_71003B4AD8 sends the open event (0x21, first parameter `param`) to part `part` (0 LAY_time, 1 LAY_ether,
    // 2 LAY_score: fn_71003B4B7C), for parts other than 0 only when isValidExpansion(1) holds and isValidExpansion(3) does
    // not; fn_71003B4C24 sends that part the close event (0x22).
    static void fn_71003B4AD8(int part, unsigned int param);
    // fn_71003B4B7C: the handle of part `part` under `handle` (LAY_time, LAY_ether, LAY_score), 0 for any other
    // part; LAY_ether and LAY_score only when `always` or GfGameManager::isBattleArenaActive() holds
    static unsigned int fn_71003B4B7C(unsigned int handle, int part, bool always);
    static void fn_71003B4C24(int part);
    // openFromChallengeBattle opens parts 0 and 1 and, by the short at 6 of GfGameManager::getBattleArenaMenuInfo()'s record, opens
    // LAY_score with 0 (1), with 1 (3) or closes it (other values), all only when isValidExpansion(1) holds;
    // closeAll closes parts 0, 1 and 2 (1 and 2 only when isValidExpansion(1) holds)
    static void openFromChallengeBattle();
    static void closeAll();
    // noticeNewRecord / noticeTimeLimit send LAY_time event 0x100 / 0x101 (its listener queues the new record
    // display / starts LAY_time_info's control)
    static void noticeNewRecord();
    static void noticeTimeLimit();

    // 2.0.0's symbols name them. The jobs m_seq and m_seq2 call on this object (Delegate<bool
    // ()>::memberFuncInvoker<GfMenuObjBtlTime>), queued by this class's listeners and by each other. LAY_time's new
    // record (m_seq): seqNewRecordFadeIn shows LAY_time_new_record, fades TXT_time_new_record in (cmn_fade_motion_lr
    // fade_in_l), starts IMG_time_new_record_eff's "start", then waits 5 frames, runs seqNewRecordSE (sound 0x22) and
    // seqNewRecordWait (until IMG_time_new_record_eff's animation stops), which queues seqNewRecordFadeOut (fades
    // TXT_time_new_record out, fade_out_r), seqNewRecordFadeWait (until that control ends) and seqNewRecordEnd (hides
    // LAY_time_new_record, sends LAY_time event 0x102). LAY_ether's box (m_seq2): seqGetBoxStart fades
    // TXT_ether_box_get in, seqGetBoxWait waits for that control, then 60 frames, then seqGetBoxEnd fades it out
    // (fade_out_r). All return true once done.
    bool seqNewRecordFadeIn();
    bool seqGetBoxStart();
    bool seqNewRecordSE();
    bool seqNewRecordWait();
    bool seqNewRecordFadeOut();
    bool seqNewRecordFadeWait();
    bool seqNewRecordEnd();
    bool seqGetBoxWait();
    bool seqGetBoxEnd();

    unsigned char pad_24[4];
    GfMenuSequence<GfMenuObjBtlTime, 8> m_seq;   // LAY_time's jobs (the name is not the original's)
    GfMenuSequence<GfMenuObjBtlTime, 8> m_seq2;  // LAY_ether's jobs (the name is not the original's)
    int m_etherBox;  // the ether box LAY_ether's listener got last (event 0xD), 0 when reset (the name is not the original's)
};
}  // namespace gf

#endif
