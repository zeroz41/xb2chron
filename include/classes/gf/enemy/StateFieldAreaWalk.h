#ifndef CLASSES_GF_ENEMY_STATEFIELDAREAWALK_H
#define CLASSES_GF_ENEMY_STATEFIELDAREAWALK_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }
namespace gf { class GfComBehaviorEnemy; }

namespace gf { namespace enemy {
// table 0x7100B65FE0
class StateFieldAreaWalk : public ::gf::GfStateBase {
public:
    // a step of the state: the sequence update runs, none when null
    typedef void (StateFieldAreaWalk::*Seq)(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    StateFieldAreaWalk() : pad_18(0), pad_1c(false), m_seq(nullptr), pad_68(0) {}
    // what GfComBehaviorEnemy::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldAreaWalk; }
    virtual ~StateFieldAreaWalk() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateFieldAreaWalk"; }  // slot 2
    // the slots hand the owner to the state's own functions
    virtual void onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorEnemy*>(owner), prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { leave(static_cast<GfComBehaviorEnemy*>(owner), next); }  // slot 4
    virtual void onStep(void* owner, const void* arg) {  // slot 5
        update(static_cast<GfComBehaviorEnemy*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
    }
    void enter(GfComBehaviorEnemy* owner, ai::State* prev);
    void leave(GfComBehaviorEnemy* owner, ai::State* next);
    void update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info);
    void seqInitGoalPos(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqWaitTurnEnd(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqMoveToGoal(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqWaitMoveEnd(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqChangeState(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    // whether the enemy may take this state (GfComBehaviorEnemy asks before requesting it)
    static bool isCondMatch(const GfComBehaviorEnemy& owner);
    unsigned int pad_18;
    bool pad_1c;
    TFieldExecCmd<GfComAsm> m_execCmd;
    Seq m_seq;
    unsigned int pad_68;
};
}}  // namespace gf::enemy

#endif
