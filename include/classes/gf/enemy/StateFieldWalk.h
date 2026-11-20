#ifndef CLASSES_GF_ENEMY_STATEFIELDWALK_H
#define CLASSES_GF_ENEMY_STATEFIELDWALK_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include "mm/Vec3.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }
namespace gf { class GfComBehaviorEnemy; }

namespace gf { namespace enemy {
// table 0x7100B66030
class StateFieldWalk : public ::gf::GfStateBase {
public:
    // a step of the state: the sequence update runs, none when null
    typedef void (StateFieldWalk::*Seq)(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    StateFieldWalk() : pad_18(0), pad_19(false), pad_1c(0), m_seq(nullptr), pad_68(0), pad_70(mm::Vec3::zero), pad_80(-1), pad_84(-1), m_hasPointRotY(false), m_pointRotY(0.0f), pad_90(0), pad_94(0.0f), pad_98(5.0f), pad_9c(0.0f) {}
    // what GfComBehaviorEnemy::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWalk; }
    virtual ~StateFieldWalk() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateFieldWalk"; }  // slot 2
    // the slots hand the owner to the state's own functions
    virtual void onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorEnemy*>(owner), prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { leave(static_cast<GfComBehaviorEnemy*>(owner), next); }  // slot 4
    virtual void onStep(void* owner, const void* arg) {  // slot 5
        update(static_cast<GfComBehaviorEnemy*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
    }
    void enter(GfComBehaviorEnemy* owner, ai::State* prev);
    void leave(GfComBehaviorEnemy* owner, ai::State* next);
    void update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info);
    void seqIdleInfinit(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqInitGoalPos(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void pollToShiftLandingSeq(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqWaitToIdle(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqUpdateMove(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqWaitTurnEnd(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqWaitToIdleAtRoutePoint(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqWaitTurnEndAtRoutePoint(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqPlayMotAtRoutePoint(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqWaitSpecialEndAtRoutePoint(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqWaitSyncLoco(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqMoveToBeginLanding(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqLandingIdle(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqWaitTakeOffEnd(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    // whether the enemy may take this state (GfComBehaviorEnemy asks before requesting it)
    static bool isCondMatch(const GfComBehaviorEnemy& owner);
    // its actMove row's actMove_Atr (enter reads it; bit 5: the walk speed follows the pitch)
    unsigned char pad_18;
    bool pad_19;
    unsigned int pad_1c;
    TFieldExecCmd<GfComAsm> m_execCmd;
    Seq m_seq;
    // the time seqLandingIdle counts up (seqWaitTurnEndAtRoutePoint clears it)
    float pad_68;
    mm::Vec3 pad_70;
    int pad_80;
    int pad_84;
    // whether a route point has a direction to turn to, and that direction (seqWaitToIdleAtRoutePoint turns the
    // enemy to it; the names are not the original's)
    bool m_hasPointRotY;
    float m_pointRotY;
    // the route point action: 2, 3 play a unique motion, 4, 5 a special one moving by its locomotion, 6 lands
    unsigned int pad_90;
    float pad_94;
    float pad_98;
    float pad_9c;
};
}}  // namespace gf::enemy

#endif
