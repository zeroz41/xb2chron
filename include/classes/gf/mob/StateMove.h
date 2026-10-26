#ifndef CLASSES_GF_MOB_STATEMOVE_H
#define CLASSES_GF_MOB_STATEMOVE_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }
namespace gf { class GfComBehaviorMob; }

namespace gf { namespace mob {
// table 0x7100B665D8
class StateMove : public ::gf::GfStateBase {
public:
    // a step of the state: the sequence the update runs, none when null
    typedef void (StateMove::*Seq)(GfComBehaviorMob& owner, const fw::UpdateInfo& info);
    StateMove() : m_seq(nullptr), pad_60(0) {}
    // what GfComBehaviorMob::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateMove; }
    virtual ~StateMove() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateMove"; }  // slot 2
    // the slots hand the owner to the state's own functions
    virtual void onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorMob*>(owner), prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { leave(static_cast<GfComBehaviorMob*>(owner), next); }  // slot 4
    virtual void onStep(void* owner, const void* arg) {  // slot 5
        update(static_cast<GfComBehaviorMob*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
    }
    void enter(GfComBehaviorMob* owner, ai::State* prev);
    void leave(GfComBehaviorMob* owner, ai::State* next);
    void update(GfComBehaviorMob* owner, const fw::UpdateInfo& info);
    TFieldExecCmd<GfComAsm> m_execCmd;
    // whether the state may run: the owner has its object at 0xb8
    static bool isCondMatch(const GfComBehaviorMob& owner);
    Seq m_seq;
    unsigned int pad_60;
};
}}  // namespace gf::mob

#endif
