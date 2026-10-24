#ifndef CLASSES_GF_PC_STATEFIELDRIDEON_H
#define CLASSES_GF_PC_STATEFIELDRIDEON_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class MsgPcFieldNotifyRiderEvent; }

namespace gf { namespace pc {
// table 0x7100B68178
class StateFieldRideOn : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldRideOn; }
    virtual ~StateFieldRideOn() {}  // slot 0: inline (the deleting destructor only frees the state)
    // inline: its slot is emitted with the class's table (the key function is recieveMessage)
    virtual inline const char* getName() const;  // slot 2
    // inline: the original's slot holds the state's own code (sets the property's riding flag)
    virtual inline void onEnter(void*, ai::State*);  // slot 3
    // inline: the original's slot holds the state's own code (clears it)
    virtual inline void onLeave(void*, ai::State*);  // slot 4
    virtual inline void onStep(void*, void const*);  // slot 5
    virtual bool recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    // the state's own functions; the slots above hand them the owner
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    void procMsgPcFieldNotifyRiderEvent(GfComBehaviorPc* behavior, fw::MessageObject* from, gf::MsgPcFieldNotifyRiderEvent& msg);
    unsigned char pad_18[0x120];
    unsigned long pad_138[2] = {};
};
}}  // namespace gf::pc

#endif
