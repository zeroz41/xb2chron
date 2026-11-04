#ifndef CLASSES_GF_TUNK_B535D0_H
#define CLASSES_GF_TUNK_B535D0_H

#include "classes/fw/MessageObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "ai/Fsm.h"
#include "mm/mtl/FixedVector.h"
#include "MicroUpdater.h"
#include "gf/MsgUnk_1000034.h"
#include "classes/gf/GfGameManager.h"
#include "fw/UpdateInfo.h"

namespace fw { class SoundResource; class SoundPack; }

namespace gf {
class GfArenaBattle;
class GfArenaParty;
class GfArenaReward;
class GfArenaJingle;
class GfSetupParam;

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: it fills the arena's
// m_ids (its code is in GfDataBlade_71002906D0's unit range, called only by the arena's setup). What it does: clears
// the vector, then pushes every ID from GfBdatBtl::getBTL_ChBtlStart() up to (not including) GfBdatBtl::getBTL_ChBtlEnd().
void fn_71002906D0(::mm::mtl::FixedVector<unsigned short, 128>& ids);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: its code is in
// GfDataBlade_710029064C's range and GfGameArena::fn_7100290D40 tail-calls it with message type 0x13's pad_40
// (no object).
// What it does: finds the GfBdatBtl challenge whose condition (type 0xD) resolves to the value and, unless its row's
// m_flag3E is set, sets it and shows SCOM_POPUP::createChBtlNewChallenge.
void fn_7100290BAC(unsigned int value);
// table 0x7100B535D0 (the fw::MessageObject base's at +0x38, offset 8); the base at 0 is
// mm::mtl::PtrSingleton<GfGameArena> (its table 0x7100B53628). No RTTI or 1.0.0 symbol names it: the arena manager
// of gf_game_arena's unit (its constructor GfGameArena installs both tables; the arena play commands send it
// MsgUnk_1000034). Only what gf_play_command uses is declared so far (size 0x18E0, layout not recovered).
class GfGameArena : public ::mm::mtl::PtrSingleton<GfGameArena>, public ::fw::MessageObject {
public:
    // 2.0.0's symbols name them. Members: their code is in
    // gf_game_arena's unit and the play commands call them on PtrSingleton<GfGameArena>'s instance. What they do:
    // read the state object the pointer at +0x30 holds and answer whether its word at +8 is 9
    // (GfPlayComMapjumpForLeaveArena::update waits for it), 3 (GfPlayComWaitArenaStateField::update; also
    // fn_710028C9CC) or 8 (GfPlayComStartChallengeBattle::update).
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
    // handle to m_partySetup's fn_710028E5BC.
    unsigned int getWeaponDamage(GF_OBJ_HANDLE* handle) const;
    // 2.0.0's symbols name it. A member: its code is in gf_game_arena's unit
    // and GfGameScene::updateControlFreeEvent calls it with PtrSingleton<GfGameArena>'s instance in x0 (after testing
    // it for null), though the body reads no this. What it does: answers whether
    // PtrSingleton<GfPlayComStartChallengeBattle>'s instance exists.
    bool isBusy() const;

    // one row of the challenge rules (the arena keeps 48, SDataGame another 48 at 0x11A8CC; fn_7100291E40 copies
    // m_rules[mode] of row id into a record, setupGame sets the flags; the names are not the original's)
    struct RuleRow {
        RuleRow() : m_flag3C(false), m_isChecked(false), m_flag3E(false) {}
        GfGameManager::BattleChallengeRecord::Rule m_rules[5];
        bool m_flag3C;  // setupGame: !GfBdatBtl::isBTL_ChBtlFlagHide(id) the first time
        bool m_isChecked;  // setupGame sets it once it has set m_flag3C
        bool m_flag3E;
    };
    struct RuleTable {
        // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in title_main's
        // unit range; SDataGame's constructor and GfGameArena's call it on their tables. What it does: clears each
        // row's five rules (copies of a zeroed array) and flags.
        RuleTable() { fn_71001528A0(); }
        void fn_71001528A0();
        // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code in the neighbour
        // range: unit_710028EBB0's). A member: GfGameArena::setupGame calls it on SDataGame's table with the arena's m_ids.
        void fn_7100290510(const ::mm::mtl::FixedVector<unsigned short, 128>& ids);
        // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code in unit_710028EBB0's range). A
        // member: StateArenaField's (StateArenaField) onEnter calls it on SDataGame's table with the arena's m_ids. What it
        // does: for each id's row, sets m_flag3E once GfGameCond::isGameCond(GfBdatBtl::getBTL_ChBtlCondition(id)) holds; a
        // row without m_flag3C gets m_flag3C and m_flag3E then and the id goes to createChBtlNewChallenge.
        void fn_7100290598(const ::mm::mtl::FixedVector<unsigned short, 128>& ids);
        // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (code in unit_7100290CC4's range and,
        // fn_710029078C, GfDataBlade_710029064C's). Members: GfGameArena::fn_7100290D40 calls them on SDataGame's
        // table (0x11A8CC) with the message's id. What they do: fn_7100290CE0 answers bit 1 of byte 10 of row id
        // (0 for id 0), fn_7100290CC4 sets that bit (not for id 0), fn_710029078C stores 2 in the row's m_flag3C.
        bool fn_7100290CE0(unsigned int id);
        void fn_7100290CC4(unsigned int id);
        void fn_710029078C(unsigned int id);
        RuleRow m_rows[48];
    };

    // what fn_7100290D40 (message type 2) and GfArenaBattle::mapjumpForReturnField pass to createMapJumpForReturnBattle (the name is not the
    // original's): createMapJumpForReturnBattle copies m_mapjumpId into the first word of the GfMapjumpInfo it builds
    struct MapjumpParam {
        // GfGameArena::MapjumpParam::MapjumpParam (out of line: GfArenaBattle::mapjumpForReturnField calls it; fn_7100290D40 inlines it)
        MapjumpParam();
        unsigned int m_mapjumpId;  // 0xE1 (the name is not the original's)
        unsigned char pad_4[4];
    };

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
    // 2.0.0's symbols name them. setupMenuInfoForChBtl and fn_7100290BAC call getSaveInfo
    // on PtrSingleton<GfGameArena>'s instance, GfArenaBattle::execAfterBattle calls fn_7100291D14 on its arena. What
    // they do: getSaveInfo returns SDataGame's rule table, fn_7100291D14 the rule for mode of its row id (neither
    // reads the arena).
    RuleTable* getSaveInfo() const;
    GfGameManager::BattleChallengeRecord::Rule* fn_7100291D14(unsigned int id, unsigned int mode);
    unsigned int update(const ::fw::UpdateInfo& info);
    // 2.0.0's symbols name them. The arena states call them. createMapSound loads the sound resource "dlc_se_btl_chbtl"
    // and finds its pack; destroyMapSound releases both.
    void createMapSound();
    void destroyMapSound();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: GfGameManager::fn_71002AC60C calls
    // it. What it does: fills the record for the challenge id and mode (setupMenuInfoForChBtl, the rule from SDataGame's
    // table, the lists through fn_71002907A0 / fn_71002908DC) and sets its m_flagAEC from m_msgObj's m_result.
    void fn_7100291E40(GfGameManager::BattleChallengeRecord* record, unsigned int id, unsigned int mode);

    virtual ~GfGameArena();
    // the arena's messages (MsgUnk_1000034) go to fn_7100290D40
    virtual bool recieveMessage(::fw::MessageObject* sender, ::fw::Message& msg);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: recieveMessage calls it with its
    // arguments for MsgUnk_1000034. What it does: unless GfManager::isExecModeThater, passes the message to m_msgObj,
    // then switches on its m_type (2..0x15).
    void fn_7100290D40(::fw::MessageObject* sender, MsgUnk_1000034& msg);

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
    // the record GfGameManager::getBattleArenaMenuInfo returns (its address) and fn_7100291E40 fills (the name is not the original's)
    GfGameManager::BattleChallengeRecord m_record;
    RuleTable m_ruleTable;  // (the name is not the original's)
    // the IDs fn_71002906D0 fills from GfBdatBtl (the name is not the original's)
    ::mm::mtl::FixedVector<unsigned short, 128> m_ids;
    // createMapSound's (the names are not the original's)
    ::fw::SoundResource* m_soundResource;
    ::fw::SoundPack* m_soundPack;
};

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: its code is in
// unit_71003214F4 (sequential play); GfGameArena::fn_7100290D40 and GfArenaBattle::mapjumpForReturnField call it with a
// MapjumpParam (no object). What it does: builds a GfMapjumpInfo from param's m_mapjumpId and the defaults.
void createMapJumpForReturnBattle(const GfGameArena::MapjumpParam& param);
}  // namespace gf

#endif
