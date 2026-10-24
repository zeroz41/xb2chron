#ifndef CLASSES_GF_PC_STATEFIELDDEAD_H
#define CLASSES_GF_PC_STATEFIELDDEAD_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class MsgObjectNotifyHealHp; }

namespace gf { namespace pc {
// table 0x7100B681C8
class StateFieldDead : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldDead; }
    virtual ~StateFieldDead() {}  // slot 0: inline (the deleting destructor only frees the state)
    // inline: its slot is emitted with the class's table (the key function is recieveMessage)
    virtual inline const char* getName() const;  // slot 2
    virtual inline void onEnter(void*, ai::State*);  // slot 3
    virtual inline void onLeave(void*, ai::State*);  // slot 4
    // inline: the original's slot holds the state's own code (waits for the dead motion's end)
    virtual inline void onStep(void*, void const*);  // slot 5
    virtual bool recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void procMsgObjectNotifyHealHp(GfComBehaviorPc* behavior, fw::MessageObject* from, gf::MsgObjectNotifyHealHp& msg);
    // set while the state waits for the animation layer 0's end; onStep clears it once command 0x20 ran (the name
    // is not the original's)
    bool m_waitAnimEnd;
    unsigned char pad_19[0x7];
};
}}  // namespace gf::pc

#endif
