#ifndef CLASSES_GF_TUNK_28D7B8_H
#define CLASSES_GF_TUNK_28D7B8_H

#include "classes/gf/GfGameManager.h"
#include "gf/GfReqParam.h"

namespace gf { class TUnk_B535D0; }

namespace gf {
// a class with no table (so no table address to name it by: named after its constructor 0x710028D7B8): the
// 0xCF0-byte object TUnk_B535D0's setup fn_7100291100 makes (gf_game_arena.cpp line 109) and keeps at +0xB8. Its
// constructor keeps the arena at +0 and builds a gf::RQ_SETUP_PARTY at +0x10 (a party setup helper, by that member);
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

    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (code at 0x710028DA24 / 0x710028DAB4,
    // GfAppendWire's unit range). Members: the arena states call them on the arena's +0xB8 object (StateArenaField's
    // onEnter fn_710028DA24; StateArenaWait's onEnter and TUnk_B53690's enter fn_710028DAB4). What they do: walk
    // this object's party entries; fn_710028DAB4 ends with fn_71002EC268(0, 1).
    void fn_710028DA24();
    void fn_710028DAB4();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code at 0x710028E4E8, GfAppendWire's unit
    // range). A member: TUnk_B53720's step calls it on the arena's +0xB8 object with the +0xC0 object's m_key and
    // goes to state 5 when it answers true, else to 3.
    bool fn_710028E4E8(const GfGameManager::BattleChallengeRecord::Key& key);

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code at 0x710028E15C, GfAppendWire's unit
    // range). A member: TUnk_B52C38::fn_710028D584 calls it on its arena's +0xB8 object (GEV 4, the map jump).
    void fn_710028E15C();
    TUnk_B535D0* m_owner;  // (the name is not the original's)
    unsigned char pad_8[0x8];
    RQ_SETUP_PARTY m_party;  // the constructor builds it (the name is not the original's)
    unsigned char pad_250[0xA0];
    // cleared by the constructor; the destructor clears it when set (what it holds is unknown)
    void* pad_2F0;
    unsigned char pad_2F8[0x9E8];
    void* pad_CE0;  // as pad_2F0
    unsigned char pad_CE8[0x8];
};
}  // namespace gf

#endif
