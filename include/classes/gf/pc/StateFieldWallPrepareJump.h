#ifndef CLASSES_GF_PC_STATEFIELDWALLPREPAREJUMP_H
#define CLASSES_GF_PC_STATEFIELDWALLPREPAREJUMP_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class MsgPcFieldNotifyWallJump; }

namespace gf { namespace pc {
// table 0x7100B682B8
class StateFieldWallPrepareJump : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWallPrepareJump; }
    virtual ~StateFieldWallPrepareJump() {}  // slot 0: inline (the deleting destructor only frees the state)
    // inline: recieveMessage is the key function (the unit emits the table and these slots' weak copies)
    virtual inline const char* getName() const;  // slot 2
    virtual inline void onEnter(void*, ai::State*);  // slot 3
    virtual inline void onLeave(void*, ai::State*);  // slot 4
    virtual inline void onStep(void*, void const*);  // slot 5
    virtual bool recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    // the message recieveMessage hands on (1.0.0's symbol; 3.0.1 inlines it, its linker dropped the copy)
    void procMsgPcFieldNotifyWallJump(GfComBehaviorPc* behavior, fw::MessageObject* from, MsgPcFieldNotifyWallJump& msg);
    // set once a wall jump notice came (procMsgPcFieldNotifyWallJump; the name is not the original's)
    bool m_notified;
    unsigned char pad_19[0x7];
};
}}  // namespace gf::pc

#endif
