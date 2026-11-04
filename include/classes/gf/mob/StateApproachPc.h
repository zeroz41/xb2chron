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
    // a step of the state: the sequence the update runs, none when null
    typedef void (StateApproachPc::*Seq)(GfComBehaviorMob& owner, const fw::UpdateInfo& info);
    StateApproachPc() : m_seq(nullptr) {}
    // what GfComBehaviorMob::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateApproachPc; }
    virtual ~StateApproachPc() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateApproachPc"; }  // slot 2
    // the slots hand the owner to the state's own functions
    virtual void onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorMob*>(owner), prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { leave(static_cast<GfComBehaviorMob*>(owner), next); }  // slot 4
    virtual void onStep(void* owner, const void* arg) {  // slot 5
        update(static_cast<GfComBehaviorMob*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
    }
    // 2.0.0's symbols name it. What it does: the state's enter (its code lies at the head of the text split as
    // gf_com_model).
    void enter(GfComBehaviorMob* owner, ai::State* prev);
    // 2.0.0's symbols name it. What it does: the state's leave (its code lies at the head of the text split as
    // gf_com_model).
    void leave(GfComBehaviorMob* owner, ai::State* next);
    // 2.0.0's symbols name it. What it does: the state's update (its code lies at the head of the text split as
    // gf_com_model).
    void update(GfComBehaviorMob* owner, const fw::UpdateInfo& info);
    TFieldExecCmd<GfComAsm> m_execCmd;
    // 2.0.0's symbols name it. What it does: once the player exists, turns the owner to the player's position and moves
    // on to seqWaitTurnEnd.
    void seqTurnPc(GfComBehaviorMob& owner, const fw::UpdateInfo& info);
    // 2.0.0's symbols name it. What it does: when the owner's flag at 0x2bc is set, starts the command "C_move" on the
    // owner's object and moves on to seqApproachPc.
    void seqWaitTurnEnd(GfComBehaviorMob& owner, const fw::UpdateInfo& info);
    // 2.0.0's symbols name it. What it does: true when the player exists, the owner's value at 0xa4 is above 0, its
    // value at 0x53d4 is at most 4 and its 0xa4 at least its 0x53d0.
    static bool isCondMatch(const GfComBehaviorMob& owner);
    // 2.0.0's symbols name it. What it does: runs the "C_move" command started by seqWaitTurnEnd and moves on to
    // seqApproachPcIdle (see its body).
    void seqApproachPc(GfComBehaviorMob& owner, const fw::UpdateInfo& info);
    // 2.0.0's symbols name it. What it does: re-inits the owner once the command ran (m_execCmd.m_executed); when
    // isCondMatch's test fails, clears the owner's pad_53d9 and requests state 1.
    void seqApproachPcIdle(GfComBehaviorMob& owner, const fw::UpdateInfo& info);
    Seq m_seq;
};
}}  // namespace gf::mob

#endif
