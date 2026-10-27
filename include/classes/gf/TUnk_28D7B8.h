#ifndef CLASSES_GF_TUNK_28D7B8_H
#define CLASSES_GF_TUNK_28D7B8_H

#include "classes/gf/GfGameManager.h"

namespace gf { class TUnk_B535D0; }

namespace gf {
// a class with no table (so no table address to name it by: named after its constructor 0x710028D7B8): the
// 0xCF0-byte object TUnk_B535D0's setup fn_7100291100 makes (gf_game_arena.cpp line 109) and keeps at +0xB8. Its
// constructor keeps the arena at +0 and builds a gf::RQ_SETUP_PARTY at +8 (a party setup helper, by that member);
// layout not recovered.
class TUnk_28D7B8 {
public:
    // Placeholder name (constructor): new in 3.0.1, nothing in 1.0.0's place names it; its code (fn_710028D7B8) is in
    // GfAppendWire's unit range.
    explicit TUnk_28D7B8(TUnk_B535D0* owner);
    // fn_710028DA08 (placeholder code address; TUnk_B535D0::fn_7100291B64 runs it before freeing the object)
    ~TUnk_28D7B8();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code at 0x710028E5BC, its own unit). A
    // member: TUnk_B535D0::fn_7100291E14 calls it on the arena's +0xB8 object. What it does: answers the key's
    // fn_7100290AE4 for the blade of the handle (DataParamAcc(handle).getBlade(-1, false)); it reads nothing of this.
    unsigned int fn_710028E5BC(const GfGameManager::BattleChallengeRecord::Key& key, GF_OBJ_HANDLE* handle);

    TUnk_B535D0* m_owner;  // (the name is not the original's)
    unsigned char pad_8[0xCE8];
};
}  // namespace gf

#endif
