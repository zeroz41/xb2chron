#ifndef CLASSES_GF_TUNK_B52C38_H
#define CLASSES_GF_TUNK_B52C38_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "gf/MsgGameBtlArena.h"
#include "gf/ArenaBattleStart.h"
#include "gf/ArenaBattleInfo.h"
#include "gf/ChBtlInfo.h"

namespace gf { class GfGameArena; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B52C38 (no RTTI; a fw::MessageObject secondary table, slots 0x710028C998/CE38/CEB8): the 0xF8-byte
// object GfGameArena's setup initialize makes with GfArenaBattle and keeps at +0xC0. Only what the arena
// states use is declared; its bases and the rest of its layout are not recovered.
class GfArenaBattle : public ::fw::MessageObject {
public:
    // slots 1/2: ~GfArenaBattle / ~GfArenaBattle (GfGameArena::finalize deletes the object through slot 2)
    virtual ~GfArenaBattle();
    // 2.0.0's symbols name it.
    explicit GfArenaBattle(GfGameArena* owner);
    // 2.0.0's symbols name them. The arena states call them on GfGameArena's +0xC0 object (code in GfAppendWire's unit
    // range, next to its constructor GfArenaBattle). mapjumpForReturnField: StateArenaReturnBattle::onStep calls it
    // each step before GfMenuManager::unloadBchUI; mapjumpForReturnFieldForObjCleanup:
    // StateArenaReturnBattle::gevMapjump calls it for GEV 4.
    void mapjumpForReturnField();
    void mapjumpForReturnFieldForObjCleanup();
    // mapjumpForBattleStart: StateArenaStartBattle's step calls it when m_partySetup's setupParty accepts m_key, before asking for
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

    // slot 3: the arena's messages (recieveMessage): MsgGameBtlArena goes to procMsgGameBtlArena
    virtual bool recieveMessage(::fw::MessageObject* sender, ::fw::Message& msg);
    // 2.0.0's symbols name it. A member: recieveMessage calls it with its arguments for MsgGameBtlArena (code next to
    // it).
    void procMsgGameBtlArena(::fw::MessageObject* sender, MsgGameBtlArena& msg);

    GfGameArena* m_owner;  // the constructor's (the name is not the original's)
    // the challenge GfGameArena::getWeaponDamage passes on and execAfterBattle looks up a rule for (the name is not
    // the original's)
    ArenaBattleStart m_key;
    // 5 sends StateArenaReturnBattle to arena state 3, anything else to 6 (the name is not the original's)
    int m_result;
    // execBattleSequence copies m_score here when the challenge is cleared (m_result 2) and zeroes it otherwise (the name
    // is not the original's)
    ArenaBattleInfo m_resultScore;
    unsigned char pad_40[0x3C];
    unsigned int pad_7C;
    // set before the waits that sleep the arena a frame at a time until it is cleared (the name is not the original's)
    bool m_isWaiting;
    unsigned char pad_81[0x3];
    ArenaBattleInfo m_score;
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
    // procMsgGameBtlArena's best values, kept with GfArenaUtil::setupMenuInfoForCube / setupMenuInfoForScore /
    // setupMenuInfoForClearTime (the constructor zeroes it as ChBtlDiff() does; the name is not the original's)
    ChBtlInfo::ChBtlDiff m_best;
    // 0x3C bytes mapjumpForReturnFieldForObjCleanup / execBattleSequence copy into the option data (GfGameUtilDiff::getUseSoundUiOption's; the name is not the
    // original's); sizeof 0xF8 (the arena's setup allocates it)
    unsigned char m_option[0x3C];
};
}  // namespace gf

#endif
