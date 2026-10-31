#ifndef CLASSES_GF_NPC_STATEWALK_H
#define CLASSES_GF_NPC_STATEWALK_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }
namespace gf { class GfComBehaviorNpc; }

namespace gf { namespace npc {
// table 0x7100B66950
class StateWalk : public ::gf::GfStateBase {
public:
    // a step of the state: the sequence update runs (enter starts seqWaitTurnEnd)
    typedef void (StateWalk::*Seq)(GfComBehaviorNpc& owner, const fw::UpdateInfo& info);

    StateWalk() : m_seq(nullptr), pad_60(0) {}
    // what GfComBehaviorNpc::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateWalk; }
    virtual ~StateWalk() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateWalk"; }  // slot 2
    // the slots hand the owner to the state's own functions
    virtual void onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorNpc*>(owner), prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { leave(static_cast<GfComBehaviorNpc*>(owner), next); }  // slot 4
    virtual void onStep(void* owner, const void* arg) {  // slot 5
        update(static_cast<GfComBehaviorNpc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
    }
    void enter(GfComBehaviorNpc* owner, ai::State* prev);
    void leave(GfComBehaviorNpc* owner, ai::State* next);
    void update(GfComBehaviorNpc* owner, const fw::UpdateInfo& info);
    void updateGoalPos(GfComBehaviorNpc& owner);
    void seqWaitTurnEnd(GfComBehaviorNpc& owner, const fw::UpdateInfo& info);
    TFieldExecCmd<GfComAsm> m_execCmd;
    Seq m_seq;
    unsigned int pad_60;
};
}}  // namespace gf::npc

#endif
