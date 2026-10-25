#ifndef CLASSES_GF_PC_STATEFIELDACCESS_H
#define CLASSES_GF_PC_STATEFIELDACCESS_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf { namespace pc {
// table 0x7100B683A8
class StateFieldAccess : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldAccess; }
    virtual ~StateFieldAccess() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    // the object accessed: leave notifies it (MsgPcFieldNotifyAction 1) (the name is not the original's)
    GF_OBJ_HANDLE* m_target;
};
}}  // namespace gf::pc

#endif
