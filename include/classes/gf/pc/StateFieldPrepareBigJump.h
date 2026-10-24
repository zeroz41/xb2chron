#ifndef CLASSES_GF_PC_STATEFIELDPREPAREBIGJUMP_H
#define CLASSES_GF_PC_STATEFIELDPREPAREBIGJUMP_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class MsgPcFieldNotifyBigJump; }

namespace gf { namespace pc {
// table 0x7100B68128
class StateFieldPrepareBigJump : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldPrepareBigJump; }
    virtual ~StateFieldPrepareBigJump() {}  // slot 0: inline (the deleting destructor only frees the state)
    // inline: its slot is emitted with the class's table (the key function is recieveMessage)
    virtual inline const char* getName() const;  // slot 2
    virtual inline void onEnter(void*, ai::State*);  // slot 3
    virtual inline void onLeave(void*, ai::State*);  // slot 4
    virtual inline void onStep(void*, void const*);  // slot 5
    virtual bool recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    void procMsgPcFieldNotifyBigJump(GfComBehaviorPc* behavior, fw::MessageObject* from, gf::MsgPcFieldNotifyBigJump& msg);
};
}}  // namespace gf::pc

#endif
