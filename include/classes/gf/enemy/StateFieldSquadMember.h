#ifndef CLASSES_GF_ENEMY_STATEFIELDSQUADMEMBER_H
#define CLASSES_GF_ENEMY_STATEFIELDSQUADMEMBER_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include "fw/UpdateInfo.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorEnemy; }
namespace gf { class GfComAsm; }

namespace gf { namespace enemy {
// table 0x7100B65D28
class StateFieldSquadMember : public ::gf::GfStateBase {
public:
    // a step of the state: the sequence update runs, none when null
    typedef void (StateFieldSquadMember::*Seq)(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    StateFieldSquadMember();  // out of line (StateFieldWalk's unit): create calls it
    // what GfComBehaviorEnemy::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldSquadMember; }
    virtual ~StateFieldSquadMember();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    void update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info);
    void seqUpdateIdle(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqWaitTurnEnd(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqUpdateMove(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    // whether the enemy may take this state (GfComBehaviorEnemy asks before requesting it)
    static bool isCondMatch(const GfComBehaviorEnemy& owner);
    // what its constructor sets (0x71004B7C28 / 0x71004B8B54; the pads' use is not known)
    TFieldExecCmd<GfComAsm> m_execCmd;
    Seq m_seq;
    // update: set while the distance to its squad position (pad_64, x and z) is below 0.1; the seqs then stand
    // and turn instead of moving (the names are not known)
    bool pad_60;
    float pad_64;
};
}}  // namespace gf::enemy

#endif
