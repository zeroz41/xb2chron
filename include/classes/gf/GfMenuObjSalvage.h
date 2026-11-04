#ifndef CLASSES_GF_GFMENUOBJSALVAGE_H
#define CLASSES_GF_GFMENUOBJSALVAGE_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class GfMenuCallContext; }
namespace gf { class GfMenuReferenceNumber; }

namespace gf {
// table 0x7100B645F8
class GfMenuObjSalvage : public ::gf::GfMenuObject {
public:
    class ResultListener;
    class RecordListener;
    GfMenuObjSalvage(unsigned int handle);
    virtual ~GfMenuObjSalvage();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // what openResult shows (the name of the field is not the original's: StateSalvageResultUi gives 1 to 3 by the
    // raffle's rank)
    struct ResultParam {
        ResultParam() : m_rank(0), m_unk2(0) {}
        unsigned short m_rank;  // the rating animation: s_rankAnims[m_rank] ("rank_1".."rank_4")
        // 0 shows LAY_result_index_normal, 1 LAY_result_index_bch (battle challenge; then rank 1)
        unsigned short m_unk2;
    };
    static void openResult(GfMenuCallContext* context, const ResultParam& param);

    // 2.0.0's symbols name it. What it does: when GfMenuObjUtil::isValidExpansion(1) and
    // GfGameManager::isBattleArenaActive() hold and the context starts, sends event 0x21 to LAY_record and starts the
    // context on it; otherwise requests event 2 on the context's object (+0x14) or sets the context's +0x40 flag.
    static void openBtlchRecord(GfMenuCallContext* context);
    // 2.0.0's symbols name it. What it does: with GfMenuObjUtil::isValidExpansion(1), stores its argument in that flag.
    static void setBtlchNewRecord(bool flag);
    // set by setBtlchNewRecord, read and cleared by seqRecordInfoOpen: with it, a new record marks the time too (bit 0 of
    // m_newRecords). The code reaches it through the GOT: not file-local. 2.0.0's symbols name it.
    static bool s_BtlchNewRecord;

    bool seqResultAppear();
    bool seqResultLeave();
    bool seqResultEnd();
    // 2.0.0's symbols name them. What they do: seqRecordInfoOpen lays out LAY_record from
    // GfGameManager::getBattleArenaMenuInfo()'s record and queues the jobs below; seqCtrlWait waits for the control
    // m_ctrlSlot; seqNewRecordSE plays "dlc_se_btl_chbtl004"; seqRecordStartConfirm enables LAY_record's input and
    // opens the operation guide; seqRecordWaitConfirm waits for m_inputClosed.
    bool seqRecordInfoOpen();
    bool seqCtrlWait();
    bool seqNewRecordFadeIn();
    bool seqNewRecordSE();
    bool seqNewRecordWait();
    bool seqRecordStartConfirm();
    bool seqRecordWaitConfirm();
    bool seqRecordBoxOpen();
    bool seqRecordFadeout();
    bool seqRecordEnd();

    ResultParam m_param;  // 0x24: the open event's parameters (the name is not the original's)
    GfMenuSequence<GfMenuObjSalvage, 12> m_seq;  // 0x28
    bool m_appeared;  // 0x3E8: seqResultAppear has started the rating animation (the name is not the original's)
    int m_ctrlSlot;  // 0x3EC: LAY_record's control slot, -1 when done (the name is not the original's)
    unsigned char pad_3F0[4];
    // 0x3F4: LAY_record's listener got event 8 with 1 (input closed); seqRecordWaitConfirm waits for it (the name is not the
    // original's)
    bool m_inputClosed;
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_time;  // 0x3F8: TXT_time's number (the name is not the original's)
    // 0x400: the records seqRecordInfoOpen found new: bit 0 time, 1 ether, 2 score (s_recordKinds) (the name is not the
    // original's)
    unsigned int m_newRecords;
};
}  // namespace gf

#endif
