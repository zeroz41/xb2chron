#ifndef CLASSES_GF_NPC_STATEAREAMOVE_H
#define CLASSES_GF_NPC_STATEAREAMOVE_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"

#include "fw/UpdateInfo.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }

namespace gf { namespace npc {
// a template on its owner (GfComBehaviorMob, GfComBehaviorNpc): 2 instances in the module
template <typename T>
class StateAreaMove : public ::gf::GfStateBase {
public:
    // a step of the state: the sequence onStep runs, none when null
    typedef void (StateAreaMove::*Seq)(T& owner, const fw::UpdateInfo& info);

    StateAreaMove() : m_seq(nullptr), pad_60(0.0f), pad_64(0.0f) {}
    // what the owner's createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateAreaMove; }
    virtual ~StateAreaMove() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateAreaMove"; }  // slot 2
    virtual void onEnter(void* owner, ai::State* prev);  // slot 3
    virtual void onLeave(void* owner, ai::State* next) {}  // slot 4
    virtual void onStep(void* owner, const void* arg) {
        if (m_seq) {
            (this->*m_seq)(*static_cast<T*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
        }
    }  // slot 5
    void seqInitGoalPos(T& owner, const fw::UpdateInfo& info);
    void seqWaitTurnEnd(T& owner, const fw::UpdateInfo& info);
    void seqMoveToGoal(T& owner, const fw::UpdateInfo& info);
    void seqWaitMoveEnd(T& owner, const fw::UpdateInfo& info);
    void seqIdle(T& owner, const fw::UpdateInfo& info);
    TFieldExecCmd<GfComAsm> m_execCmd;
    Seq m_seq;
    float pad_60;
    float pad_64;  // the time seqIdle waits (it adds the step time until pad_60)
};
}}  // namespace gf::npc

#endif
