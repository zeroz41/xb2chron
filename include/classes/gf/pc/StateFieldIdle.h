#ifndef CLASSES_GF_PC_STATEFIELDIDLE_H
#define CLASSES_GF_PC_STATEFIELDIDLE_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw { class UpdateInfo; }
namespace gf { class MsgPcFieldHighJump; }
namespace gf { class MsgPcFieldTestEnableUniqueMotion; }
namespace gf { class MsgPcFieldSetUniqueMotion; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B68218
class StateFieldIdle : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldIdle; }
    virtual ~StateFieldIdle() {}  // slot 0: inline (the deleting destructor only frees the state)
    // inline: recieveMessage is the key function (the unit emits the table and these slots' weak copies)
    virtual inline const char* getName() const;  // slot 2
    // inline: the original's slot holds the state's own code (not written yet)
    virtual inline void onEnter(void*, ai::State*);  // slot 3
    // inline: the original's slot holds leave's code (inlined)
    virtual inline void onLeave(void*, ai::State*);  // slot 4
    virtual inline void onStep(void*, void const*);  // slot 5
    virtual bool recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    // the state's own functions; the slots above hand them the owner
    // 1.0.0's symbols (3.0.1 inlines them into onEnter/onLeave; its linker dropped their out-of-line copies)
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    // whether the PC has room for a unique idle motion: a capsule test from its collision values (never uses `this`)
    bool checkSpace(GfComBehaviorPc* behavior) const;
    // the messages recieveMessage hands on (1.0.0's symbols; 3.0.1 inlines the first two, its linker dropped their
    // out-of-line copies)
    void procMsgPcFieldHighJump(GfComBehaviorPc* behavior, fw::MessageObject* from, MsgPcFieldHighJump& msg);
    void procMsgPcFieldTestEnableUniqueMotion(GfComBehaviorPc* behavior, fw::MessageObject* from,
                                              MsgPcFieldTestEnableUniqueMotion& msg);
    void procMsgPcFieldSetUniqueMotion(GfComBehaviorPc* behavior, fw::MessageObject* from,
                                       MsgPcFieldSetUniqueMotion& msg);
};
}}  // namespace gf::pc

#endif
