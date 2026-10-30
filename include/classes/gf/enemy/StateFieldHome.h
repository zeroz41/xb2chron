#ifndef CLASSES_GF_ENEMY_STATEFIELDHOME_H
#define CLASSES_GF_ENEMY_STATEFIELDHOME_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include "fw/UpdateInfo.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorEnemy; }
namespace gf { class GfComAsm; }

namespace gf { namespace enemy {
// table 0x7100B65C38
class StateFieldHome : public ::gf::GfStateBase {
public:
    // a step of the state: the sequence update runs, none when null
    typedef void (StateFieldHome::*Seq)(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    StateFieldHome();  // out of line (StateFieldWalk's unit): create calls it
    // what GfComBehaviorEnemy::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldHome; }
    virtual ~StateFieldHome();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    void enter(GfComBehaviorEnemy* owner, ai::State* prev);
    void update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info);
    void seqWaitIdle(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqInitHomePos(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqWaitTurnEnd(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqMoveToHomePos(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    // whether the enemy may take this state (GfComBehaviorEnemy asks before requesting it)
    static bool isCondMatch(const GfComBehaviorEnemy& owner);
    // what its constructor sets (0x71004B7C28 / 0x71004B8B54; the pads' use is not known)
    TFieldExecCmd<GfComAsm> m_execCmd;
    Seq m_seq;
    bool pad_60;
    float pad_64;  // update counts the time in the state: past 10 it destroys the enemy (pad_60 set once it did)
};
}}  // namespace gf::enemy

#endif
