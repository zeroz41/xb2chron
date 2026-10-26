#ifndef CLASSES_GF_MOB_STATESQUADMEMBER_H
#define CLASSES_GF_MOB_STATESQUADMEMBER_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }
namespace gf { class GfComBehaviorMob; }

namespace gf { namespace mob {
// table 0x7100B66678
class StateSquadMember : public ::gf::GfStateBase {
public:
    // a step of the state: the sequence the update runs, none when null
    typedef void (StateSquadMember::*Seq)(GfComBehaviorMob& owner, const fw::UpdateInfo& info);
    StateSquadMember() : pad_18(0.5f), m_seq(nullptr), pad_68(false) {}
    // what GfComBehaviorMob::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateSquadMember; }
    virtual ~StateSquadMember() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateSquadMember"; }  // slot 2
    // the slots hand the owner to the state's own functions
    virtual void onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorMob*>(owner), prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { leave(static_cast<GfComBehaviorMob*>(owner), next); }  // slot 4
    virtual void onStep(void* owner, const void* arg) {  // slot 5
        update(static_cast<GfComBehaviorMob*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
    }
    void enter(GfComBehaviorMob* owner, ai::State* prev);
    void leave(GfComBehaviorMob* owner, ai::State* next);
    void update(GfComBehaviorMob* owner, const fw::UpdateInfo& info);
    float pad_18;
    TFieldExecCmd<GfComAsm> m_execCmd;
    // whether the state may run: the owner is a squad member
    static bool isCondMatch(const GfComBehaviorMob& owner);
    Seq m_seq;
    bool pad_68;
};
}}  // namespace gf::mob

#endif
