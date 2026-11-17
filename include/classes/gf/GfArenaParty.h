#ifndef CLASSES_GF_TUNK_28D7B8_H
#define CLASSES_GF_TUNK_28D7B8_H

#include "classes/gf/GfGameManager.h"
#include "gf/GfReqParam.h"
#include "gf/ArenaBattleStart.h"
#include "gf/ArenaChanged.h"

namespace gf { class GfGameArena; }

namespace gf {
// a class with no table (so no table address to name it by: named after its constructor 0x710028D7B8): the
// 0xCF0-byte object GfGameArena's setup initialize makes (gf_game_arena.cpp line 109) and keeps at +0xB8. Its
// constructor keeps the arena at +0 and builds a gf::RQ_SETUP_PARTY at +0x10 (a party setup helper, by that member);
// layout not recovered.
class GfArenaParty {
public:
    // 2.0.0's symbols name it.
    explicit GfArenaParty(GfGameArena* owner);
    // fn_710028DA08 (placeholder code address; GfGameArena::finalize runs it before freeing the object)
    ~GfArenaParty();
    // 2.0.0's symbols name it (code at 0x710028E5BC, its own unit). GfGameArena::getWeaponDamage calls it on the
    // arena's +0xB8 object. What it does: answers GfArenaUtil::getWeaponDamage for the start and the blade of the
    // handle (DataParamAcc(handle).getBlade(-1, false)); it reads nothing of this.
    unsigned int getWeaponDamage(const ArenaBattleStart& start, GF_OBJ_HANDLE* handle) const;

    // 2.0.0's symbols name them. The arena states call them on the arena's +0xB8 object (StateArenaField's onEnter
    // addFieldBlade; StateArenaWait's onEnter and StateArenaLeave's enter removeFieldBlade). What they do: walk this
    // object's party entries; removeFieldBlade ends with GfGameUtil::execPartyBladeFollow(0, 1).
    void addFieldBlade();
    void removeFieldBlade();
    // 2.0.0's symbols name it (code at 0x710028E4E8, GfAppendWire's unit range). StateArenaStartBattle's step calls
    // it on the arena's +0xB8 object with the +0xC0 object's m_key and goes to state 5 when it answers true, else to 3.
    bool setupParty(const ArenaBattleStart& start);

    // 2.0.0's symbols name it. GfArenaBattle::mapjumpForReturnFieldForObjCleanup calls it on its arena's +0xB8 object
    // (GEV 4, the map jump).
    void setupLevelForBattleEnd();
    // 2.0.0's symbols name them. setupParty calls them on this object with its start (code next to it). checkDriver
    // (this not used) answers whether the challenge's party can be set up: true for a mode-3 challenge, else
    // GfBdatBtl's getBTL_ChBtlDriver drivers 0..2 must be in the party (0 and 7 and 9 always count).
    // setupLevelForBattleStart fills m_lists.m_list38 (GfArenaUtil::setupLevelForBattleStart), sets each driver's
    // level to the challenge's and copies the list to the arena's record; setupWeaponParamForBattleStart the same for
    // m_listE0 (GfArenaUtil::setupRankForBattleStart, no levels).
    bool checkDriver(const ArenaBattleStart& start);
    // changePartyForStartBattle: fades out, keeps the party (GfGameParty::getCurrentPartyInfo into m_party) and, when
    // one of the challenge's drivers 0..2 is driver 12, changes the party to driver 12 alone with its default blade
    // (GfReqCommand::reqChangeParty) and unselects the kept party's blades. It answers true (the code ends with
    // mov w0, #1 on both paths).
    bool changePartyForStartBattle(const ArenaBattleStart& start);
    void setupLevelForBattleStart(const ArenaBattleStart& start);
    void setupWeaponParamForBattleStart(const ArenaBattleStart& start);
    GfGameArena* m_owner;  // (the name is not the original's)
    unsigned char pad_8[0x8];
    RQ_SETUP_PARTY m_party;  // the constructor builds it (the name is not the original's)
    // the lists setupLevelForBattleStart / setupWeaponParamForBattleStart fill and copy to the arena's record;
    // setupLevelForBattleEnd empties them and copies them there whole (ArenaChanged::operator=, 0x710028E234) (the name
    // is not the original's)
    ArenaChanged m_lists;
    unsigned char pad_CE8[0x8];
};
}  // namespace gf

#endif
