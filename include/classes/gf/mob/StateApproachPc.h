#ifndef CLASSES_GF_MOB_STATEAPPROACHPC_H
#define CLASSES_GF_MOB_STATEAPPROACHPC_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }
namespace gf { class GfComBehaviorMob; }

namespace gf { namespace mob {
// table 0x7100B66768
class StateApproachPc : public ::gf::GfStateBase {
public:
    StateApproachPc() : pad_50(nullptr), pad_58(nullptr) {}
    // what GfComBehaviorMob::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateApproachPc; }
    virtual ~StateApproachPc() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateApproachPc"; }  // slot 2
    // the slots hand the owner to the state's own functions
    virtual void onEnter(void* owner, ai::State* prev) { fn_71004D70EC(static_cast<GfComBehaviorMob*>(owner), prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { fn_71004D714C(static_cast<GfComBehaviorMob*>(owner), next); }  // slot 4
    virtual void onStep(void* owner, const void* arg) {  // slot 5
        fn_71004D7154(static_cast<GfComBehaviorMob*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
    }
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because the state's
    // onEnter slot tail-calls it with the state and the owner. What it does: the state's enter (its code
    // lies at the head of the text split as gf_com_model).
    void fn_71004D70EC(GfComBehaviorMob* owner, ai::State* prev);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because the state's
    // onLeave slot tail-calls it with the state and the owner. What it does: the state's leave (its code
    // lies at the head of the text split as gf_com_model).
    void fn_71004D714C(GfComBehaviorMob* owner, ai::State* next);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because the state's
    // onStep slot tail-calls it with the state and the owner. What it does: the state's update (its code
    // lies at the head of the text split as gf_com_model).
    void fn_71004D7154(GfComBehaviorMob* owner, const fw::UpdateInfo& info);
    TFieldExecCmd<GfComAsm> m_execCmd;
    void* pad_50;
    void* pad_58;
};
}}  // namespace gf::mob

#endif
