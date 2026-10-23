#ifndef CLASSES_GF_PC_STATEFIELDWATERDEADIDLE_H
#define CLASSES_GF_PC_STATEFIELDWATERDEADIDLE_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B68E48
class StateFieldWaterDeadIdle : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWaterDeadIdle; }
    virtual ~StateFieldWaterDeadIdle() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because StateFieldWaterDeadIdle::onStep, the
    // slot that hands the state its update, tail-calls it with the owner and the step argument.
    void fn_7100507984(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
};
}}  // namespace gf::pc

#endif
