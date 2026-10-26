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
    class TUnk_B646A0;
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

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits between openResult
    // and initialize and opens this class's attached object (0x53). What it does: when GfMenuObjUtil::fn_710048FD30(1)
    // and GfGameManager::fn_71002AC580() hold and the context starts, sends event 0x21 to LAY_record and starts the
    // context on it; otherwise requests event 2 on the context's object (+0x14) or sets the context's +0x40 flag.
    static void fn_710046F628(GfMenuCallContext* context);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits next to
    // fn_710046F628 and sets the unit's file-static flag that fn_7100470314 reads. What it does: with
    // GfMenuObjUtil::fn_710048FD30(1), stores its argument in that flag.
    static void fn_710046F6F4(bool flag);
    // set by fn_710046F6F4, read and cleared by fn_7100470314: with it, a new record marks the time too (bit 0 of
    // m_newRecords). The code reaches it through the GOT: not file-local. (the name is not the original's)
    static bool s_recordFlag;

    bool seqResultAppear();
    bool seqResultLeave();
    bool seqResultEnd();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they are the m_seq jobs
    // the LAY_record listener (TUnk_B646A0, event 0x21) and fn_7100470314 queue. What they do:
    // fn_7100470314 lays out LAY_record from GfGameManager::fn_71002AC5D8()'s record and queues the jobs below;
    // fn_7100470BBC waits for the control m_ctrlSlot; fn_7100470D98 plays "dlc_se_btl_chbtl004";
    // fn_7100470ED8 enables LAY_record's input and opens the operation guide; fn_7100470F34 waits for m_inputClosed.
    bool fn_7100470314();
    bool fn_7100470BBC();
    bool fn_7100470C00();
    bool fn_7100470D98();
    bool fn_7100470DB8();
    bool fn_7100470ED8();
    bool fn_7100470F34();
    bool fn_7100470F3C();
    bool fn_71004710CC();
    bool fn_710047122C();

    ResultParam m_param;  // 0x24: the open event's parameters (the name is not the original's)
    GfMenuSequence<GfMenuObjSalvage, 12> m_seq;  // 0x28
    bool m_appeared;  // 0x3E8: seqResultAppear has started the rating animation (the name is not the original's)
    int m_ctrlSlot;  // 0x3EC: LAY_record's control slot, -1 when done (the name is not the original's)
    unsigned char pad_3F0[4];
    // 0x3F4: LAY_record's listener got event 8 with 1 (input closed); fn_7100470F34 waits for it (the name is not the
    // original's)
    bool m_inputClosed;
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_time;  // 0x3F8: TXT_time's number (the name is not the original's)
    // 0x400: the records fn_7100470314 found new: bit 0 time, 1 ether, 2 score (s_recordKinds) (the name is not the
    // original's)
    unsigned int m_newRecords;
};
}  // namespace gf

#endif
