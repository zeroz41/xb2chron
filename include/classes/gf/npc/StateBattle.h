#ifndef CLASSES_GF_NPC_STATEBATTLE_H
#define CLASSES_GF_NPC_STATEBATTLE_H

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
class StateBattle : public ::gf::GfStateBase {
public:
    // a step of the state: the sequence onStep runs, none when null
    typedef void (StateBattle::*Seq)(T& owner, const fw::UpdateInfo& info);

    StateBattle() : m_seq(nullptr), pad_60(0) {}
    // what the owner's createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateBattle; }
    virtual ~StateBattle() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateBattle"; }  // slot 2
    virtual void onEnter(void* owner, ai::State* prev);  // slot 3
    virtual void onLeave(void* owner, ai::State* next) {}  // slot 4
    virtual void onStep(void* owner, const void* arg) {  // slot 5
        const fw::UpdateInfo& info = *static_cast<const fw::UpdateInfo*>(arg);
        m_execCmd.update(info.m_deltaTime);
        if (m_seq) {
            (this->*m_seq)(*static_cast<T*>(owner), info);
        }
    }
    static bool isCondMatch(const T& owner);
    void seqApplyBattleMot(T& owner, const fw::UpdateInfo& info);
    void seqTurnPc(T& owner, const fw::UpdateInfo& info);
    void seqUpdateBattleMot(T& owner, const fw::UpdateInfo& info);
    void seqWaitTurnEnd(T& owner, const fw::UpdateInfo& info);
    void seqUpdateMove(T& owner, const fw::UpdateInfo& info);
    TFieldExecCmd<GfComAsm> m_execCmd;
    Seq m_seq;
    unsigned int pad_60;
};
}}  // namespace gf::npc

#endif
