#ifndef CLASSES_GF_PC_STATEFIELDIDLE_H
#define CLASSES_GF_PC_STATEFIELDIDLE_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B68218
class StateFieldIdle : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldIdle; }
    virtual ~StateFieldIdle() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    // inline: the original's slot holds the state's own code (not written yet)
    virtual inline void onEnter(void*, ai::State*);  // slot 3
    // inline: the original's slot holds the state's own code (not written yet)
    virtual inline void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    virtual bool recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    // the state's own functions; the slots above hand them the owner
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
};
}}  // namespace gf::pc

#endif
