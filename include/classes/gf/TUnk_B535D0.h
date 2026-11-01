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
class TUnk_B52C38;
class TUnk_28D7B8;
class TUnk_28E618;
class TUnk_28D5BC;
class GfSetupParam;

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: it fills the arena's
// m_ids (its code is in GfDataBlade_71002906D0's unit range, called only by the arena's setup). What it does: clears
// the vector, then pushes every ID from GfBdatBtl::fn_71001E9534() up to (not including) GfBdatBtl::fn_71001E9540().
void fn_71002906D0(::mm::mtl::FixedVector<unsigned short, 128>& ids);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: its code is in gf_game_arena's
// unit and uses no argument (GfGameScene::updateControlFreeEvent calls it). What it does: answers whether
// PtrSingleton<GfPlayComStartChallengeBattle>'s instance exists.
bool fn_71002920F0();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: its code is in
// GfDataBlade_710029064C's range and TUnk_B535D0::fn_7100290D40 tail-calls it with message type 0x13's pad_40
// (no object).
// What it does: finds the GfBdatBtl challenge whose condition (type 0xD) resolves to the value and, unless its row's
// m_flag3E is set, sets it and shows SCOM_POPUP::fn_710056A3FC.
void fn_7100290BAC(unsigned int value);
// table 0x7100B535D0 (the fw::MessageObject base's at +0x38, offset 8); the base at 0 is
// mm::mtl::PtrSingleton<TUnk_B535D0> (its table 0x7100B53628). No RTTI or 1.0.0 symbol names it: the arena manager
// of gf_game_arena's unit (its constructor fn_7100290FA0 installs both tables; the arena play commands send it
// MsgUnk_1000034). Only what gf_play_command uses is declared so far (size 0x18E0, layout not recovered).
class TUnk_B535D0 : public ::mm::mtl::PtrSingleton<TUnk_B535D0>, public ::fw::MessageObject {
public:
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: their code is in
    // gf_game_arena's unit and the play commands call them on PtrSingleton<TUnk_B535D0>'s instance. What they do:
    // read the state object the pointer at +0x30 holds and answer whether its word at +8 is 9
    // (GfPlayComMapjumpForLeaveArena::update waits for it), 3 (GfPlayComWaitArenaStateField::update; also
    // fn_710028C9CC) or 8 (GfPlayComStartChallengeBattle::update).
    bool fn_7100291CAC();
    bool fn_7100291DA0();
    bool fn_7100291E00();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: their code is in
    // gf_game_arena's unit and the arena states (unit_710028EBB0) call them on the state machine's owner or on
    // PtrSingleton<TUnk_B535D0>'s instance. What they do: fn_7100291D68 answers isDestroyNow() || the bool at
    // +0xB4; fn_7100291DB4 answers GfGameFlag::getLocal(1, 0xDC0D) != 0.
    bool fn_7100291D68();
    bool fn_7100291DB4();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: their code is in gf_game_arena's
    // unit; GfGameManager (isChangeNormalHomuraForce, fn_71002AC930) calls fn_7100291D54 on PtrSingleton<TUnk_B535D0>'s
    // instance, GfPlayFactory::createStartTutorial calls fn_7100291DD8, TUnk_B52C38's code calls fn_7100291E2C on the
    // arena it keeps at +0x18. What they do: fn_7100291D54 answers whether the current state's ID is 5;
    // fn_7100291DD8 answers m_msgObj's flag at +0xAD || the current state's ID is 7; fn_7100291E2C sleeps the
    // calling micro thread for the given frames (MicroThread::sleep(frames, true)).
    bool fn_7100291D54();
    bool fn_7100291DD8();
    void fn_7100291E2C(unsigned int frames);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: fn_71002EC674 calls it on
    // PtrSingleton<TUnk_B535D0>'s instance while fn_7100291D54 holds. What it does: passes m_msgObj's key and the
    // handle to m_partySetup's fn_710028E5BC.
    unsigned int fn_7100291E14(GF_OBJ_HANDLE* handle);

    // one row of the challenge rules (the arena keeps 48, SDataGame another 48 at 0x11A8CC; fn_7100291E40 copies
    // m_rules[mode] of row id into a record, fn_7100291CC0 sets the flags; the names are not the original's)
    struct RuleRow {
        RuleRow() : m_flag3C(false), m_isChecked(false), m_flag3E(false) {}
        GfGameManager::BattleChallengeRecord::Rule m_rules[5];
        bool m_flag3C;  // fn_7100291CC0: !GfBdatBtl::fn_71001E9F94(id) the first time
        bool m_isChecked;  // fn_7100291CC0 sets it once it has set m_flag3C
        bool m_flag3E;
    };
    struct RuleTable {
        // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in title_main's
        // unit range; SDataGame's constructor and TUnk_B535D0's call it on their tables. What it does: clears each
        // row's five rules (copies of a zeroed array) and flags.
        RuleTable() { fn_71001528A0(); }
        void fn_71001528A0();
        // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code in the neighbour
        // range: unit_710028EBB0's). A member: TUnk_B535D0::fn_7100291CC0 calls it on SDataGame's table with the arena's m_ids.
        void fn_7100290510(const ::mm::mtl::FixedVector<unsigned short, 128>& ids);
        // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code in unit_710028EBB0's range). A
        // member: StateArenaField's (TUnk_B52EC0) onEnter calls it on SDataGame's table with the arena's m_ids. What it
        // does: for each id's row, sets m_flag3E once GfGameCond::isGameCond(GfBdatBtl::fn_71001E9CEC(id)) holds; a
        // row without m_flag3C gets m_flag3C and m_flag3E then and the id goes to fn_710056A3FC.
        void fn_7100290598(const ::mm::mtl::FixedVector<unsigned short, 128>& ids);
        // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (code in unit_7100290CC4's range and,
        // fn_710029078C, GfDataBlade_710029064C's). Members: TUnk_B535D0::fn_7100290D40 calls them on SDataGame's
        // table (0x11A8CC) with the message's id. What they do: fn_7100290CE0 answers bit 1 of byte 10 of row id
        // (0 for id 0), fn_7100290CC4 sets that bit (not for id 0), fn_710029078C stores 2 in the row's m_flag3C.
        bool fn_7100290CE0(unsigned int id);
        void fn_7100290CC4(unsigned int id);
        void fn_710029078C(unsigned int id);
        RuleRow m_rows[48];
    };

    // what fn_7100290D40 (message type 2) and TUnk_B52C38::fn_710028D4A4 pass to fn_71003217A0 (the name is not the
    // original's): fn_71003217A0 copies m_mapjumpId into the first word of the GfMapjumpInfo it builds
    struct MapjumpParam {
        // fn_7100290D00 (out of line: TUnk_B52C38::fn_710028D4A4 calls it; fn_7100290D40 inlines it)
        MapjumpParam();
        unsigned int m_mapjumpId;  // 0xE1 (the name is not the original's)
        unsigned char pad_4[4];
    };

    // fn_7100290FA0 (GfGameManager::initialize builds it through fn_7100291AD8; the parameter is not used)
    explicit TUnk_B535D0(const GfSetupParam& param);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Static members: GfGameManager::initialize
    // calls fn_7100291AD8 (after GfGameSalvage::build) and GfGameManager::finalize fn_7100291B1C. What they do:
    // fn_7100291AD8 makes the instance; fn_7100291B1C runs fn_7100291B64 on it, then deletes it.
    static void fn_7100291AD8(const GfSetupParam& param);
    static void fn_7100291B1C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: fn_7100291B1C calls it. What it
    // does: sleeps until the current state's ID is 9, deletes the updater, cleans up the state machine, deletes the
    // four owned objects, clears m_isSetUp.
    void fn_7100291B64();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: GfGameManager::setupGame calls
    // fn_7100291CC0, GfGameManager::update fn_7100292060. What they do: fn_7100291CC0 marks each of m_ids' rows of
    // SDataGame's rule table once; fn_7100292060 keeps the frame's update info, runs the updater and m_sound, and
    // returns GfGameFlag::getLocal(1, 0xDC0D).
    void fn_7100291CC0();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (the symbols' GfDataMap::getSDataMap /
    // setCloudType are wrong donor matches: the callers pass the arena as this). Members: fn_7100290130 and
    // fn_7100290BAC call fn_7100291CF4 on PtrSingleton<TUnk_B535D0>'s instance, TUnk_B52C38::fn_710028D330 calls
    // fn_7100291D14 on its arena. What they do: fn_7100291CF4 returns SDataGame's rule table, fn_7100291D14 the
    // rule for mode of its row id (neither reads the arena).
    RuleTable* fn_7100291CF4();
    GfGameManager::BattleChallengeRecord::Rule* fn_7100291D14(unsigned int id, unsigned int mode);
    unsigned int fn_7100292060(const ::fw::UpdateInfo& info);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: the arena states call them.
    // fn_7100291F2C loads the sound resource "dlc_se_btl_chbtl" and finds its pack; fn_7100291FF0 releases both.
    void fn_7100291F2C();
    void fn_7100291FF0();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: GfGameManager::fn_71002AC60C calls
    // it. What it does: fills the record for the challenge id and mode (fn_7100290130, the rule from SDataGame's
    // table, the lists through fn_71002907A0 / fn_71002908DC) and sets its m_flagAEC from m_msgObj's m_result.
    void fn_7100291E40(GfGameManager::BattleChallengeRecord* record, unsigned int id, unsigned int mode);

    virtual ~TUnk_B535D0();
    // the arena's messages (MsgUnk_1000034) go to fn_7100290D40
    virtual bool recieveMessage(::fw::MessageObject* sender, ::fw::Message& msg);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: recieveMessage calls it with its
    // arguments for MsgUnk_1000034. What it does: unless GfManager::isExecModeThater, passes the message to m_msgObj,
    // then switches on its m_type (2..0x15).
    void fn_7100290D40(::fw::MessageObject* sender, MsgUnk_1000034& msg);

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: the constructor fn_7100290FA0
    // calls it on itself. What it does: makes the four owned objects, registers the ten arena states (IDs 0..9),
    // starts the state machine at 0 on a MicroUpdater thread, fills m_ids, clears the local flag 0xDC0D, sets m_isSetUp.
    void fn_7100291100(const GfSetupParam& param);  // (the parameter is not used)
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. The MicroUpdater thread's function (static:
    // the updater calls it with the arena): steps the state machine with m_stepInfo, then sleeps a frame, forever.
    static void fn_7100291C6C(TUnk_B535D0* self);

    bool m_isSetUp;  // fn_7100291100 sets it last (the name is not the original's)
    unsigned char pad_21[7];
    ::ai::Fsm m_fsm;  // the arena states (IDs 0..9)
    MicroUpdater<TUnk_B535D0>* m_updater;  // runs fn_7100291C6C
    ::fw::UpdateInfo m_updateInfo;  // fn_7100292060 keeps it; each step passes it to the states (the name is not the original's)
    bool m_isEnd;  // fn_7100291D68 answers it (the name is not the original's)
    unsigned char pad_B5[3];
    // the objects fn_7100291100 makes (the names are not the original's): 0xCF0 bytes (a party setup helper),
    // 0xF8 (table 0x7100B52C38), 0x58, 0x20 (holds a SoundHandle)
    TUnk_28D7B8* m_partySetup;
    TUnk_B52C38* m_msgObj;
    TUnk_28E618* m_helper;
    TUnk_28D5BC* m_sound;
    // the record GfGameManager::fn_71002AC5D8 returns (its address) and fn_7100291E40 fills (the name is not the original's)
    GfGameManager::BattleChallengeRecord m_record;
    RuleTable m_ruleTable;  // (the name is not the original's)
    // the IDs fn_71002906D0 fills from GfBdatBtl (the name is not the original's)
    ::mm::mtl::FixedVector<unsigned short, 128> m_ids;
    // fn_7100291F2C's (the names are not the original's)
    ::fw::SoundResource* m_soundResource;
    ::fw::SoundPack* m_soundPack;
};

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: its code is in
// unit_71003214F4 (sequential play); TUnk_B535D0::fn_7100290D40 and TUnk_B52C38::fn_710028D4A4 call it with a
// MapjumpParam (no object). What it does: builds a GfMapjumpInfo from param's m_mapjumpId and the defaults.
void fn_71003217A0(const TUnk_B535D0::MapjumpParam& param);
}  // namespace gf

#endif
