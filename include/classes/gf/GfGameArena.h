#ifndef CLASSES_GF_TUNK_B535D0_H
#define CLASSES_GF_TUNK_B535D0_H

#include "classes/fw/MessageObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "ai/Fsm.h"
#include "mm/mtl/FixedVector.h"
#include "MicroUpdater.h"
#include "gf/MsgGameBtlArena.h"
#include "gf/ArenaMenuInfo.h"
#include "gf/ChBtlInfo.h"
#include "gf/SaveChBtl.h"
#include "gf/MapJumpForReturnBattle.h"
#include "gf/GfArenaUtil.h"
#include "classes/gf/GfGameManager.h"
#include "fw/UpdateInfo.h"

namespace fw { class SoundResource; class SoundPack; }

namespace gf {
class GfArenaBattle;
class GfArenaParty;
class GfArenaReward;
class GfArenaJingle;
class GfSetupParam;

enum GFDIFF : int;

// table 0x7100B535D0 (the fw::MessageObject base's at +0x38, offset 8); the base at 0 is
// mm::mtl::PtrSingleton<GfGameArena> (its table 0x7100B53628). No RTTI or 1.0.0 symbol names it: the arena manager
// of gf_game_arena's unit (its constructor GfGameArena installs both tables; the arena play commands send it
// MsgGameBtlArena). Only what gf_play_command uses is declared so far (size 0x18E0, layout not recovered).
class GfGameArena : public ::mm::mtl::PtrSingleton<GfGameArena>, public ::fw::MessageObject {
public:
    // 2.0.0's symbols name them. Members: their code is in
    // gf_game_arena's unit and the play commands call them on PtrSingleton<GfGameArena>'s instance. What they do:
    // read the state object the pointer at +0x30 holds and answer whether its word at +8 is 9
    // (GfPlayComMapjumpForLeaveArena::update waits for it), 3 (GfPlayComWaitArenaStateField::update; also
    // GfArenaBattle::procMsgGameBtlArena) or 8 (GfPlayComStartChallengeBattle::update).
    bool isStateDestroy() const;
    bool isEnableStartBattle() const;
    bool isPlayEvent() const;
    // 2.0.0's symbols name them. Members: their code is in
    // gf_game_arena's unit and the arena states (unit_710028EBB0) call them on the state machine's owner or on
    // PtrSingleton<GfGameArena>'s instance. What they do: isDestroyNow answers isDestroyNow() || the bool at
    // +0xB4; isActiveArena answers GfGameFlag::getLocal(1, 0xDC0D) != 0.
    bool isDestroyNow() const;
    bool isActiveArena() const;
    // 2.0.0's symbols name them. Their code is in gf_game_arena's unit; GfGameManager
    // (isChangeNormalHomuraForce, isDisableFieldDamage) calls isBattleNow on PtrSingleton<GfGameArena>'s instance,
    // GfPlayFactory::createStartTutorial calls isInvalidTutorial, GfArenaBattle's code calls sleep on the arena it keeps at
    // +0x18. What they do: isBattleNow answers whether the current state's ID is 5; isInvalidTutorial answers m_msgObj's
    // flag at +0xAD || the current state's ID is 7; sleep sleeps the calling micro thread for the given frames
    // (MicroThread::sleep(frames, true)).
    bool isBattleNow() const;
    bool isInvalidTutorial() const;
    void sleep(unsigned int frames);
    // 2.0.0's symbols name it. A member: GfGameUtil::getWpnDamage calls it on
    // PtrSingleton<GfGameArena>'s instance while isBattleNow holds. What it does: passes m_msgObj's key and the
    // handle to m_partySetup's getWeaponDamage.
    unsigned int getWeaponDamage(GF_OBJ_HANDLE* handle) const;
    // 2.0.0's symbols name it. A member: its code is in gf_game_arena's unit
    // and GfGameScene::updateControlFreeEvent calls it with PtrSingleton<GfGameArena>'s instance in x0 (after testing
    // it for null), though the body reads no this. What it does: answers whether
    // PtrSingleton<GfPlayComStartChallengeBattle>'s instance exists.
    bool isBusy() const;

    // GfGameArena (GfGameManager::initialize builds it through build; the parameter is not used)
    explicit GfGameArena(const GfSetupParam& param);
    // 2.0.0's symbols name them. Static members: GfGameManager::initialize calls build (after GfGameSalvage::build) and
    // GfGameManager::finalize destroy. What they do: build makes the instance; destroy runs finalize on it, then
    // deletes it.
    static void build(const GfSetupParam& param);
    static void destroy();
    // 2.0.0's symbols name it. What it does: sleeps until the current state's ID is 9, deletes the updater, cleans up
    // the state machine, deletes the four owned objects, clears m_isSetUp.
    void finalize();
    // 2.0.0's symbols name them. GfGameManager::setupGame calls setupGame, GfGameManager::update update. What they do:
    // setupGame marks each of m_ids' rows of SDataGame's rule table once; update keeps the frame's update info, runs
    // the updater and m_sound, and returns GfGameFlag::getLocal(1, 0xDC0D).
    void setupGame();
    // 2.0.0's symbols name them. GfArenaUtil::setupMenuInfoForChBtl and createPopupForKillEnemy call getSaveInfo() on
    // PtrSingleton<GfGameArena>'s instance, GfArenaBattle::execAfterBattle calls getSaveInfo(id, diff) on its arena.
    // What they do: getSaveInfo() returns SDataGame's SaveChBtl, getSaveInfo(id, diff) the ChBtlDiff for diff of its
    // row id (neither reads the arena).
    SaveChBtl* getSaveInfo() const;
    ChBtlInfo::ChBtlDiff* getSaveInfo(unsigned int id, GFDIFF diff) const;
    unsigned int update(const ::fw::UpdateInfo& info);
    // 2.0.0's symbols name them. The arena states call them. createMapSound loads the sound resource "dlc_se_btl_chbtl"
    // and finds its pack; destroyMapSound releases both.
    void createMapSound();
    void destroyMapSound();
    // 2.0.0's symbols name it. GfGameManager::getBattleArenaMenuInfo calls it. What it does: fills the record for the
    // challenge id and difficulty (GfArenaUtil::setupMenuInfoForChBtl, the ChBtlDiff from SDataGame's table, the lists
    // through GfArenaUtil::setupLevelForBattleStart / setupRankForBattleStart) and sets its m_flagAEC from m_msgObj's
    // m_result.
    void getMenuInfo(ArenaMenuInfo& info, unsigned int id, GFDIFF diff) const;

    virtual ~GfGameArena();
    // the arena's messages (MsgGameBtlArena) go to procMsgGameBtlArena
    virtual bool recieveMessage(::fw::MessageObject* sender, ::fw::Message& msg);
    // 2.0.0's symbols name it. A member: recieveMessage calls it with its arguments for MsgGameBtlArena. What it does:
    // unless GfManager::isExecModeThater, passes the message to m_msgObj, then switches on its m_type (2..0x15).
    void procMsgGameBtlArena(::fw::MessageObject* sender, MsgGameBtlArena& msg);

    // 2.0.0's symbols name it. What it does: makes the four owned objects, registers the ten arena states (IDs 0..9),
    // starts the state machine at 0 on a MicroUpdater thread, fills m_ids, clears the local flag 0xDC0D, sets
    // m_isSetUp.
    void initialize(const GfSetupParam& param);  // (the parameter is not used)
    // 2.0.0's symbols name it. The MicroUpdater thread's function (static: the updater calls it with the arena): steps
    // the state machine with m_stepInfo, then sleeps a frame, forever.
    static void fnUpdate(GfGameArena* self);

    bool m_isSetUp;  // initialize sets it last (the name is not the original's)
    unsigned char pad_21[7];
    ::ai::Fsm m_fsm;  // the arena states (IDs 0..9)
    MicroUpdater<GfGameArena>* m_updater;  // runs fnUpdate
    ::fw::UpdateInfo m_updateInfo;  // update keeps it; each step passes it to the states (the name is not the original's)
    bool m_isEnd;  // isDestroyNow answers it (the name is not the original's)
    unsigned char pad_B5[3];
    // the objects initialize makes (the names are not the original's): 0xCF0 bytes (a party setup helper),
    // 0xF8 (table 0x7100B52C38), 0x58, 0x20 (holds a SoundHandle)
    GfArenaParty* m_partySetup;
    GfArenaBattle* m_msgObj;
    GfArenaReward* m_helper;
    GfArenaJingle* m_sound;
    // the record GfGameManager::getBattleArenaMenuInfo returns (its address) and getMenuInfo fills (the name is not the original's)
    ArenaMenuInfo m_record;
    SaveChBtl m_ruleTable;  // (the name is not the original's)
    // the IDs GfArenaUtil::setupChBtlList fills from GfBdatBtl (the name is not the original's)
    ::mm::mtl::FixedVector<unsigned short, 128> m_ids;
    // createMapSound's (the names are not the original's)
    ::fw::SoundResource* m_soundResource;
    ::fw::SoundPack* m_soundPack;
};

}  // namespace gf

#endif
