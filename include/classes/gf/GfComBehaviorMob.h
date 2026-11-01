#ifndef CLASSES_GF_GFCOMBEHAVIORMOB_H
#define CLASSES_GF_GFCOMBEHAVIORMOB_H

#include "mm/mtl/RTTI.h"
#include "ai/Hfsm.h"
#include "mm/Quat.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "classes/gf/GfFieldLocalSteer/TIsTargetNotSameSquad.h"
#include "classes/gf/TFieldExecCmdTurn.h"
#include "classes/gmk/GmkSquadNavi.h"
#include "gf/GfGameStuckMeter.h"
#include "gf/GfGameDepopMeter.h"
#include "gf/GfFieldMoveSpeed.h"
#include "gf/GfFieldLookIk.h"

namespace fw { class ColiMoveObject; }
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gmk { class AGmkBase; }
namespace gf { class GfComAsm; }
namespace mm { class Vec3; }
namespace navi { class NvmshAcObj; }
class CBdatWrapper;

namespace gf {
// table 0x7100B66500
class GfComBehaviorMob : public ::gf::GfComBehavior {
public:
    // table 0x7100B66570; the constructor installs it at 0x53c0
    class Listener {
    public:
        Listener() : m_owner(nullptr) {}
        virtual void onWkStandbyLogout();  // slot 0
        GfComBehaviorMob* m_owner;  // the behavior it listens for (the name is not the original's)
    };
    GfComBehaviorMob();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorMob();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    // the object's world position and rotation (its transform's frame, synced)
    virtual const mm::Vec3& getPos() const;  // slot 7
    virtual const mm::Quat& getRot() const;  // slot 8
    // the gimmick its object is bound to, none when it is bound to none
    gmk::AGmkBase* getBindedGmkInst() const;
    // (re)makes its state machine: the mob's 7 states, one level deep
    void createFsm();
    // cleans its state machine up once (1.0.0 has it out of line; 3.0.1 keeps no copy)
    void disposeFsm() {
        if (!m_buildingFsm) {
            m_buildingFsm = true;
            m_hfsm.cleanup();
        }
    }
    // what the object factory calls before destroying it; the destructor does the same
    void cleanup();
    // (re)starts its movement; the states pass true on entering, the approach state false
    // while its navigation mesh object moves: from its position to pad_110 at its speed (km/h to m/s, by the setup's
    // scale) over the frame's time, counting the frames in pad_b0
    void updateNaviMeshObj(float deltaTime);
    void init(bool);
    // the collision object of its collider (component 4) when it is a fw::ColiMoveObject, else none
    fw::ColiMoveObject* getColiObject() const;
    // its walking speed: the setup's speed percent (GfObjSetupMob::pad_90) of the slowest, eased over the time given
    void initMoveSpeed(float duration);
    bool isSquadMember() const;
    // false while its turn is set up and not done; else whether it has a collision object that follows its frame and
    // either pad_b8, a place in a squad, or a bound gimmick whose INFO shape is not 1
    bool isMove() const;
    void execTurnCmdToPos(const mm::Vec3& pos);
    // turns to the given yaw plus its steering's angle (the same body as GfComBehaviorNpc's execTurnCmd, with
    // CreateInfo's defaults; mob::StateMove's fn_71004D82FC calls it). Inferred name: execTurnCmd
    void fn_71004D459C(float rotY);
    // turns toward its navigation mesh object's move vector, or toward pad_110 when it has none
    void execTurnCmdToGoal();
    // where it walks to: pad_110 (no copy of it exists; StateBattle's sequences store the goal in place)
    void setGoalPos(const mm::Vec3& pos) { pad_110 = pos; }
    void moveToGoal(float);
    // whether it reached pad_110: its steering timed out, or the goal is within its collision's height and radius
    bool isArrivedToGoal() const;
    static mm::mtl::RTTI m_rtti;
    // the mob's row of its BDAT sheet (BdatInfo::create reads it); create reads each from the row's column of the
    // same name ("ReactionRange", ...): the field names follow the columns and are not the original's
    class BdatInfo {
    public:
        // the constructor clears all of it (two 8-byte stores)
        BdatInfo()
            : m_reactionRangeSq(0.0f), m_reactionPercent(0), m_reactionMot(0), m_battleReaction(0), m_battleMot(0),
              m_approachDistSq(0.0f) {}
        void create(const CBdatWrapper& bdat, int row);
        // ReactionRange squared: StateReaction keeps reacting while the player is within it
        float m_reactionRangeSq;
        // one 32-bit unit: StateReaction<T>::seqUpdateMove loads both halves at once
        unsigned int m_reactionPercent : 16;
        unsigned int m_reactionMot : 16;  // the FLD_NpcMobMotionId row StateReaction::beginReaction runs
        // plain halves: StateBattle<T>::isCondMatch's one 32-bit load of both is GVN widening its second load
        unsigned short m_battleReaction;
        unsigned short m_battleMot;  // the FLD_NpcMobMotionId row StateBattle::seqApplyBattleMot runs
        // CloseRange squared (read only when GfGameManager::fn_71002A9E68 answers true): mob::StateApproachPc's
        // fn_71004D7468 compares it with pad_53d0
        float m_approachDistSq;
    };
    BdatInfo m_bdatInfo;
    navi::NvmshAcObj* pad_a8;  // cleanup hands it back to the navigation manager
    int pad_b0;
    void* pad_b8;  // mob::StateMove::isCondMatch: the state may run while it is set
    gmk::GmkSquadNavi m_squadNavi;  // isSquadMember reads it (the name is not the original's)
    mm::Vec3 pad_100;  // what it answers MsgObjectGetVelocity (0x1000049) with
    // mob::StateSquadMember::seqUpdateIdle starts moving once the owner is pad_18 away from it on the ground plane
    mm::Vec3 pad_110;
    // StateReaction<GfComBehaviorMob>::onLeave hands its saved rotation back to it (the name is not the original's)
    mm::Quat m_reactionRot;
    GfGameStuckMeter m_stuckMeter;  // the names of these four are not the original's
    GfGameDepopMeter m_depopMeter;
    GfFieldMoveSpeed m_moveSpeed;
    GfFieldLookIk m_lookIk;
    // the turn execTurnCmdToPos starts; the states wait for its pad_6c (the name is not the original's)
    TFieldExecCmdTurn<GfComAsm> m_turnCmd;
    // execTurnCmdToPos adds its current angle to the turn (the name is not the original's)
    GfFieldLocalSteer m_localSteer;
    // the filter its steering asks about targets (the name is not the original's)
    GfFieldLocalSteer::TIsTargetNotSameSquad<GfComBehaviorMob> m_steerFilter;
    ai::Hfsm m_hfsm;
    // set while createFsm cleans up and sets the machine up again (the name is not the original's)
    bool m_buildingFsm;
    unsigned char pad_53b1[0x7];
    void* pad_53b8;  // its Listener clears it on a standby logout
    Listener m_listener;  // (the name is not the original's)
    float pad_53d0;
    float pad_53d4;  // mob::StateApproachPc's fn_71004D7468 needs it at most 4
    unsigned char pad_53d8;
    bool pad_53d9;  // mob::StateApproachPc sets it on entering
};
}  // namespace gf

#endif
