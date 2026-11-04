#ifndef CLASSES_GF_TUNK_B52C38_H
#define CLASSES_GF_TUNK_B52C38_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "gf/MsgUnk_1000034.h"

namespace gf { class GfGameArena; }
namespace fw { class UpdateInfo; }

namespace gf {
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: no this, only the BTL_ChBtl row
// id; GfArenaBattle::mapjumpForBattleStart calls it (code in GfDataBlade_710029064C). What it does: when GfBdatBtl's
// getBTL_ChBtlMapJump gives the row's map, sets that map's WeatherParam weather id from getBTL_ChBtlWeather (+1, at most 5),
// time 0, length 100.
void fn_710029064C(unsigned int id);

// table 0x7100B52C38 (no RTTI; a fw::MessageObject secondary table, slots 0x710028C998/CE38/CEB8): the 0xF8-byte
// object GfGameArena's setup initialize makes with fn_710028CDC0 and keeps at +0xC0. Only what the arena
// states use is declared; its bases and the rest of its layout are not recovered.
class GfArenaBattle : public ::fw::MessageObject {
public:
    // what StateArenaResultBattle's steps pass to GfArenaReward's placeholders fn_710028E7DC / fn_710028E69C / fn_710028E878 /
    // fn_710028EF70 / fn_710028F0A4 (the names are not the original's): m_id is a BTL_ChBtl row (GfBdatBtl's
    // getBTL_ChBtlTresureNeed / getBTL_ChBtlClearReward take it), m_value is compared with that row's TresureNeed1..3 values. 16 bytes:
    // execBattleSequence copies it whole (two 8-byte moves) into m_resultScore.
    struct Score {
        unsigned int m_id;
        unsigned int pad_4;
        unsigned int m_value;
        unsigned int pad_C;
    };
    // slots 1/2: fn_710028CE38 / fn_710028CEB8 (GfGameArena::finalize deletes the object through slot 2)
    virtual ~GfArenaBattle();
    // 2.0.0's symbols name it.
    explicit GfArenaBattle(GfGameArena* owner);
    // 2.0.0's symbols name them. The arena states call them on GfGameArena's +0xC0 object (code in GfAppendWire's unit
    // range, next to its constructor fn_710028CDC0). mapjumpForReturnField: StateArenaReturnBattle::onStep calls it
    // each step before GfMenuManager::unloadBchUI; mapjumpForReturnFieldForObjCleanup:
    // StateArenaReturnBattle::gevMapjump calls it for GEV 4.
    void mapjumpForReturnField();
    void mapjumpForReturnFieldForObjCleanup();
    // mapjumpForBattleStart: StateArenaStartBattle's step calls it when m_partySetup's fn_710028E4E8 accepts m_key, before asking for
    // state 5; execBattleSequence: StateArenaExecBattle's step calls it with its step's fw::UpdateInfo, before asking for state 7.
    void mapjumpForBattleStart();
    void execBattleSequence(fw::UpdateInfo const& info);
    // 2.0.0's symbols name it. A member: execBattleSequence calls it on this
    // object (code next to it); it works on m_isDone, pad_A8 and m_context. What it does: waits out the fade, then
    // opens GfMenuObjBtlchTelop's menu (open, type 0) on m_context and sleeps the arena until the context ends.
    void execBattleStart(fw::UpdateInfo const& info);
    // 2.0.0's symbols name them. execBattleSequence calls them on this object in
    // a loop, until execAfterBattle answers false (code next to them). execBattle runs the battle: hands m_key's id
    // to gmk::GmkBattleChallenge::sm_targetGmkBdatId and waits until pad_7C is set, showing GfMenuObjBtlchTelop's wave menu as
    // sm_battleStatus's wave changes; execAfterBattle keeps the best values for pad_7C 3 or m_result 2, retries for 5.
    void execBattle(fw::UpdateInfo const& info);
    bool execAfterBattle();

    // slot 3: the arena's messages (fn_710028C998): MsgUnk_1000034 goes to fn_710028C9CC
    virtual bool recieveMessage(::fw::MessageObject* sender, ::fw::Message& msg);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: recieveMessage calls it with its
    // arguments for MsgUnk_1000034 (code next to it).
    void fn_710028C9CC(::fw::MessageObject* sender, MsgUnk_1000034& msg);

    GfGameArena* m_owner;  // the constructor's (the name is not the original's)
    // the challenge GfGameArena::getWeaponDamage passes on and execAfterBattle looks up a rule for (the name is not
    // the original's)
    GfGameManager::BattleChallengeRecord::Key m_key;
    // 5 sends StateArenaReturnBattle to arena state 3, anything else to 6 (the name is not the original's)
    int m_result;
    // execBattleSequence copies m_score here when the challenge is cleared (m_result 2) and zeroes it otherwise (the name
    // is not the original's)
    Score m_resultScore;
    unsigned char pad_40[0x3C];
    unsigned int pad_7C;
    // set before the waits that sleep the arena a frame at a time until it is cleared (the name is not the original's)
    bool m_isWaiting;
    unsigned char pad_81[0x3];
    Score m_score;
    unsigned int pad_94;  // the constructor's and mapjumpForBattleStart's 1
    bool pad_98;
    unsigned char pad_99[0x7];
    // execBattleStart creates it (GfMenuCallContext::create) and opens GfMenuObjBtlchTelop's menu with it; released and
    // cleared by the destructor (the name is not the original's)
    GfMenuCallContext* m_context;
    unsigned int pad_A8;
    bool pad_AC;
    bool m_isDone;  // GfGameArena::isInvalidTutorial answers true while it is set (the name is not the original's)
    unsigned char pad_AE[0x2];
    // fn_710028C9CC's best values, kept with setupMenuInfoForCube / fn_71002904DC / fn_71002904F4 (the constructor zeroes it
    // as Rule() does; the name is not the original's)
    GfGameManager::BattleChallengeRecord::Rule m_best;
    // 0x3C bytes mapjumpForReturnFieldForObjCleanup / execBattleSequence copy into the option data (fn_71002EE8C4's; the name is not the
    // original's); sizeof 0xF8 (the arena's setup allocates it)
    unsigned char m_option[0x3C];
};
}  // namespace gf

#endif
