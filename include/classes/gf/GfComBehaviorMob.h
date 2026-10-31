#ifndef CLASSES_GF_GFCOMBEHAVIORMOB_H
#define CLASSES_GF_GFCOMBEHAVIORMOB_H

#include "mm/mtl/RTTI.h"
#include "ai/Hfsm.h"
#include "mm/Quat.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "classes/gf/TFieldExecCmdTurn.h"
#include "classes/gmk/GmkSquadNavi.h"
#include "gf/GfGameStuckMeter.h"
#include "gf/GfGameDepopMeter.h"
#include "gf/GfFieldMoveSpeed.h"
#include "gf/GfFieldLookIk.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gmk { class AGmkBase; }
namespace gf { class GfComAsm; }
namespace mm { class Vec3; }
namespace navi { class NvmshAcObj; }

namespace gf {
// table 0x7100B66500
class GfComBehaviorMob : public ::gf::GfComBehavior {
public:
    class Listener;
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
    void init(bool);
    bool isSquadMember() const;
    void execTurnCmdToPos(const mm::Vec3& pos);
    static mm::mtl::RTTI m_rtti;
    // the reaction's motion row and reach: StateReaction<GfComBehaviorMob>::seqUpdateMove keeps reacting while
    // pad_98 > 0, pad_9c and pad_9e are set and the player is within pad_98 (pad_53d0); beginReaction starts
    // FLD_NpcMobMotionId's cmdName of row pad_9e
    float pad_98;
    unsigned int pad_9c : 16;
    unsigned int pad_9e : 16;
    unsigned short pad_a0;
    unsigned short pad_a2;
    float pad_a4;  // mob::StateApproachPc's fn_71004D7468 compares it with pad_53d0
    navi::NvmshAcObj* pad_a8;  // cleanup hands it back to the navigation manager
    int pad_b0;
    void* pad_b8;  // mob::StateMove::isCondMatch: the state may run while it is set
    gmk::GmkSquadNavi m_squadNavi;  // isSquadMember reads it (the name is not the original's)
    mm::Vec3 pad_f0;
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
    unsigned char pad_5320[0x8];
    ai::Hfsm m_hfsm;
    // set while createFsm cleans up and sets the machine up again (the name is not the original's)
    bool m_buildingFsm;
    unsigned char pad_53b1[0x7];
    void* pad_53b8;  // its Listener clears it on a standby logout
    unsigned char pad_53c0[0x10];
    float pad_53d0;
    float pad_53d4;  // mob::StateApproachPc's fn_71004D7468 needs it at most 4
    unsigned char pad_53d8;
    bool pad_53d9;  // mob::StateApproachPc sets it on entering
};
}  // namespace gf

#endif
