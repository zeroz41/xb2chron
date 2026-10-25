#ifndef CLASSES_GF_PC_STATEFIELDONGROUND_H
#define CLASSES_GF_PC_STATEFIELDONGROUND_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B684E8
class StateFieldOnGround : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldOnGround; }
    virtual ~StateFieldOnGround() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    // the names are not the original's: update sets m_keepAccess before the moves to other ground states (leave
    // then keeps the access flag and foot steps on) and m_keepLure before the move to state 0x38 (leave keeps the
    // lure on); enter clears both
    bool m_keepAccess;
    bool m_keepLure;
    unsigned char pad_1a[0x6];
};
}}  // namespace gf::pc

#endif
