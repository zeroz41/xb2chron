#ifndef CLASSES_GF_TUNK_B52C38_H
#define CLASSES_GF_TUNK_B52C38_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/GfGameManager.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "gf/MsgUnk_1000034.h"

namespace gf { class TUnk_B535D0; }

namespace gf {
// table 0x7100B52C38 (no RTTI; a fw::MessageObject secondary table, slots 0x710028C998/CE38/CEB8): the 0xF8-byte
// object TUnk_B535D0's setup fn_7100291100 makes with fn_710028CDC0 and keeps at +0xC0. Only what the arena
// states use is declared; its bases and the rest of its layout are not recovered.
class TUnk_B52C38 : public ::fw::MessageObject {
public:
    // slots 1/2: fn_710028CE38 / fn_710028CEB8 (TUnk_B535D0::fn_7100291B64 deletes the object through slot 2)
    virtual ~TUnk_B52C38();
    // Placeholder name (constructor): new in 3.0.1, nothing in 1.0.0's place names it (fn_710028CDC0, in GfAppendWire's
    // unit range); the arena's setup passes itself.
    explicit TUnk_B52C38(TUnk_B535D0* owner);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: the arena states call them
    // on TUnk_B535D0's +0xC0 object (code in GfAppendWire's unit range, next to its constructor fn_710028CDC0).
    // fn_710028D4A4: TUnk_B53118::onStep calls it each step before GfMenuManager::fn_710035CE3C;
    // fn_710028D584: TUnk_B53118::gevMapjump calls it for GEV 4.
    void fn_710028D4A4();
    void fn_710028D584();
    // fn_710028CF40: TUnk_B53720's step calls it when m_partySetup's fn_710028E4E8 accepts m_key, before asking for
    // state 5; fn_710028CFF8: TUnk_B53768's step calls it with its step argument, before asking for state 7.
    void fn_710028CF40();
    void fn_710028CFF8(void const* arg);

    // slot 3: the arena's messages (fn_710028C998): MsgUnk_1000034 goes to fn_710028C9CC
    virtual bool recieveMessage(::fw::MessageObject* sender, ::fw::Message& msg);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: recieveMessage calls it with its
    // arguments for MsgUnk_1000034 (code next to it).
    void fn_710028C9CC(::fw::MessageObject* sender, MsgUnk_1000034& msg);

    TUnk_B535D0* m_owner;  // the constructor's (the name is not the original's)
    // the challenge TUnk_B535D0::fn_7100291E14 passes on and fn_710028D330 looks up a rule for (the name is not
    // the original's)
    GfGameManager::BattleChallengeRecord::Key m_key;
    // 5 sends TUnk_B53118 to arena state 3, anything else to 6 (the name is not the original's)
    int m_result;
    unsigned int pad_30;
    unsigned int pad_34;
    unsigned int pad_38;
    unsigned int pad_3C;
    unsigned char pad_40[0x3C];
    unsigned int pad_7C;
    // set before the waits that sleep the arena a frame at a time until it is cleared (the name is not the original's)
    bool m_isWaiting;
    unsigned char pad_81[0x3];
    // what TUnk_B537B0's steps pass to TUnk_28E618's placeholders fn_710028E7DC / fn_710028E69C / fn_710028E878 /
    // fn_710028EF70 / fn_710028F0A4 (the names are not the original's): m_id is a BTL_ChBtl row (GfBdatBtl's
    // fn_71001EA2E8 / fn_71001EA1C4 take it), m_value is compared with that row's TresureNeed1..3 values
    struct Score {
        unsigned int m_id;
        unsigned int pad_4;
        unsigned int m_value;
    };
    Score m_score;
    unsigned int pad_90;
    unsigned int pad_94;  // the constructor's and fn_710028CF40's 1
    bool pad_98;
    unsigned char pad_99[0x7];
    // released and cleared by the destructor (reference_object.h's `m_RefCount > 0`); what it holds is unknown
    ::mm::mtl::ReferenceObject* m_ref;
    unsigned int pad_A8;
    bool pad_AC;
    bool m_isDone;  // TUnk_B535D0::fn_7100291DD8 answers true while it is set (the name is not the original's)
    unsigned char pad_AE[0x2];
    unsigned int pad_B0;
    unsigned int pad_B4;
    unsigned short pad_B8;
    unsigned char pad_BA;
    unsigned char pad_BB;
    // 0x3C bytes fn_710028D584 / fn_710028CFF8 copy into the option data (fn_71002EE8C4's; the name is not the
    // original's); sizeof 0xF8 (the arena's setup allocates it)
    unsigned char m_option[0x3C];
};
}  // namespace gf

#endif
