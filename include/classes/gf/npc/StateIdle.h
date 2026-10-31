#ifndef CLASSES_GF_NPC_STATEIDLE_H
#define CLASSES_GF_NPC_STATEIDLE_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }
namespace gf { class GfComBehaviorNpc; }

namespace gf { namespace npc {
// table 0x7100B66900
class StateIdle : public ::gf::GfStateBase {
public:
    // a step of the state: the sequence update runs, none when null
    typedef void (StateIdle::*Seq)(GfComBehaviorNpc& owner, const fw::UpdateInfo& info);

    StateIdle() : m_endSchedule(false), m_seq(nullptr) {}
    // what GfComBehaviorNpc::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateIdle; }
    virtual ~StateIdle() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateIdle"; }  // slot 2
    // the slots hand the owner to the state's own functions
    virtual void onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorNpc*>(owner), prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { leave(static_cast<GfComBehaviorNpc*>(owner), next); }  // slot 4
    virtual void onStep(void* owner, const void* arg) {  // slot 5
        update(static_cast<GfComBehaviorNpc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
    }
    // whether leaving for (or coming back from) state ends the npc's schedule (1.0.0's symbol; 3.0.1 inlines it):
    // false without a state and for a talk (state 6) with a gimmick whose bdat row's NpcTurn (u8) is 3, else true
    inline bool isExecEndScheduleCondMatched(GfComBehaviorNpc& owner, ai::State* state) const;
    void enter(GfComBehaviorNpc* owner, ai::State* prev);
    void leave(GfComBehaviorNpc* owner, ai::State* next);
    void update(GfComBehaviorNpc* owner, const fw::UpdateInfo& info);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's enter inlined its code). A member
    // because enter and the sequences call it with the state. What it does: starts the npc's schedule command, the
    // asm state S_schedule_<n> as a C_ command (GfComAsm's state name, else the npc setup's schedule name), ending
    // the schedule first when m_endSchedule is set.
    void fn_71004E0660(GfComBehaviorNpc& owner);
    // Placeholder name: new in 3.0.1. A sequence (enter stores it in m_seq, as fn_71004E09E0 does). What it does:
    // runs the schedule command until it ran, then requests the state getNexStateId gives.
    void fn_71004E0948(GfComBehaviorNpc& owner, const fw::UpdateInfo& info);
    // Placeholder name: new in 3.0.1. A sequence (enter's first one). What it does: waits for the npc's turn to end,
    // then starts the schedule command and moves on to fn_71004E0948.
    void fn_71004E09E0(GfComBehaviorNpc& owner, const fw::UpdateInfo& info);
    TFieldExecCmd<GfComAsm> m_execCmd;
    // whether starting the schedule command ends the schedule first: enter stores isExecEndScheduleCondMatched of
    // the previous state (the name is not the original's)
    bool m_endSchedule;
    Seq m_seq;
};
}}  // namespace gf::npc

#endif
