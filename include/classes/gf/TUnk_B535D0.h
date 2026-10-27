#ifndef CLASSES_GF_TUNK_B535D0_H
#define CLASSES_GF_TUNK_B535D0_H

#include "classes/fw/MessageObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "ai/Fsm.h"
#include "mm/mtl/FixedVector.h"
#include "MicroUpdater.h"
#include "gf/MsgUnk_1000034.h"

namespace gf {
class TUnk_B52C38;
class TUnk_28D7B8;
class TUnk_28E618;
class TUnk_28D5BC;

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: it fills the arena's
// m_ids (its code is in GfDataBlade_71002906D0's unit range, called only by the arena's setup). What it does: clears
// the vector, then pushes every ID from GfBdatBtl::fn_71001E9534() up to (not including) GfBdatBtl::fn_71001E9540().
void fn_71002906D0(::mm::mtl::FixedVector<unsigned short, 128>& ids);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: its code is in gf_game_arena's
// unit and uses no argument (GfGameScene::updateControlFreeEvent calls it). What it does: answers whether
// PtrSingleton<GfPlayComStartChallengeBattle>'s instance exists.
bool fn_71002920F0();
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
    void fn_7100291100();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. The MicroUpdater thread's function (static:
    // the updater calls it with the arena): steps the state machine with m_stepInfo, then sleeps a frame, forever.
    static void fn_7100291C6C(TUnk_B535D0* self);

    bool m_isSetUp;  // fn_7100291100 sets it last (the name is not the original's)
    unsigned char pad_21[7];
    ::ai::Fsm m_fsm;  // the arena states (IDs 0..9)
    MicroUpdater<TUnk_B535D0>* m_updater;  // runs fn_7100291C6C
    unsigned char m_stepInfo[0xC];  // what each step passes the states (layout not recovered; the name is not the original's)
    bool m_isEnd;  // fn_7100291D68 answers it (the name is not the original's)
    unsigned char pad_B5[3];
    // the objects fn_7100291100 makes (the names are not the original's): 0xCF0 bytes (a party setup helper),
    // 0xF8 (table 0x7100B52C38), 0x58, 0x20 (holds a SoundHandle)
    TUnk_28D7B8* m_partySetup;
    TUnk_B52C38* m_msgObj;
    TUnk_28E618* m_helper;
    TUnk_28D5BC* m_sound;
    unsigned char pad_D8[0x16F0];
    // the IDs fn_71002906D0 fills from GfBdatBtl (the name is not the original's)
    ::mm::mtl::FixedVector<unsigned short, 128> m_ids;
    unsigned char pad_18D0[0x10];
};
}  // namespace gf

#endif
