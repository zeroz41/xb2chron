#ifndef CLASSES_GF_TUNK_B52C38_H
#define CLASSES_GF_TUNK_B52C38_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/GfGameManager.h"

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

    unsigned char pad_18[0x8];
    // the challenge TUnk_B535D0::fn_7100291E14 passes on and fn_710028D330 looks up a rule for (the name is not
    // the original's)
    GfGameManager::BattleChallengeRecord::Key m_key;
    // 5 sends TUnk_B53118 to arena state 3, anything else to 6 (the name is not the original's)
    int m_result;
    unsigned char pad_30[0x7D];
    bool m_isDone;  // TUnk_B535D0::fn_7100291DD8 answers true while it is set (the name is not the original's)
    unsigned char pad_AE[0x4A];  // sizeof 0xF8 (the arena's setup allocates it)
};
}  // namespace gf

#endif
