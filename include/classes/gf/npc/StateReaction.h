#ifndef CLASSES_GF_NPC_STATEREACTION_H
#define CLASSES_GF_NPC_STATEREACTION_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include "mm/Quat.h"
#include "fw/UpdateInfo.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }

namespace gf { namespace npc {
// a template on its owner (GfComBehaviorMob, GfComBehaviorNpc): 2 instances in the module
template <typename T>
class StateReaction : public ::gf::GfStateBase {
public:
    // a step of the state: the sequence onStep runs, none when null
    typedef void (StateReaction::*Seq)(T& owner, const fw::UpdateInfo& info);

    StateReaction() : m_seq(nullptr), pad_60(mm::Quat::identity), pad_70(0) {}
    // what the owner's createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateReaction; }
    virtual ~StateReaction() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateReaction"; }  // slot 2
    virtual void onEnter(void* owner, ai::State* prev) {
        pad_70 = 0;
        m_seq = &StateReaction::seqTurnToPc;
    }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { static_cast<T*>(owner)->m_reactionRot = pad_60; }  // slot 4
    virtual void onStep(void* owner, const void* arg) {  // slot 5
        const fw::UpdateInfo& info = *static_cast<const fw::UpdateInfo*>(arg);
        m_execCmd.update(info.m_deltaTime);
        if (m_seq) {
            (this->*m_seq)(*static_cast<T*>(owner), info);
        }
    }
    void seqTurnToPc(T& owner, const fw::UpdateInfo& info);
    void seqWaitTurnToPcEnd(T& owner, const fw::UpdateInfo& info);
    void beginReaction(const T& owner);
    void seqUpdateMove(T& owner, const fw::UpdateInfo& info);
    void endReaction(const T& owner);
    void seqTurnToPrev(T& owner, const fw::UpdateInfo& info);
    void seqWaitTurnToPrevEnd(T& owner, const fw::UpdateInfo& info);
    TFieldExecCmd<GfComAsm> m_execCmd;
    Seq m_seq;
    mm::Quat pad_60;  // onLeave hands it back to the owner
    unsigned int pad_70;
};
}}  // namespace gf::npc

#endif
