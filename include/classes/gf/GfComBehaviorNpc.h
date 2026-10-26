#ifndef CLASSES_GF_GFCOMBEHAVIORNPC_H
#define CLASSES_GF_GFCOMBEHAVIORNPC_H

#include "mm/mtl/RTTI.h"
#include "ai/Hfsm.h"
#include "mm/Quat.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "classes/gf/TFieldExecCmdTurn.h"
#include "mm/Vec3.h"
#include "gf/GfFieldMoveSpeed.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }
namespace gmk { class AGmkBase; }
namespace mm { class Vec3; }

namespace gf { namespace npc {
// the IDs createFsm registers the npc's states under (0 StateIdle, 1 StateWalk, 2 StateAreaMove, 3 StateApproachPc,
// 4 StateReaction, 5 StateBattle, 6 StateTalk); the enumerator names are unknown
enum STATE_ID {};
}}  // namespace gf::npc

namespace gf {
// table 0x7100B66840
class GfComBehaviorNpc : public ::gf::GfComBehavior {
public:
    class Listener;
    class LocalSteerIsTargetNotPlayer;
    // the npc's row of its BDAT sheets (BdatInfo::create reads it); only what this unit's code shows is declared
    class BdatInfo {
    public:
        // how far above or below an npc a target may be (2): static or not, the symbol cannot tell
        static float getDistYThreshold();
        // whether a talk with the npc earns a bonus, and marks it earned (StateTalk::seqWaitTalkEnd)
        bool isIconTalkBonus() const;
        void setTalkBonusFlag() const;
        // create reads each from the row's column of the same name ("ShopID", "CloseRange", ...); the field
        // names follow the columns and are not the original's
        unsigned short m_shopId;
        unsigned char pad_2[0x2];
        // how near (squared: CloseRange * CloseRange) the player must come for the npc to approach it:
        // StateApproachPc compares the player's squared distance with it, none when 0
        float m_approachDistSq;
        float m_moveSpeed;
        // ReactionRange squared: StateReaction keeps reacting while the player is within it
        float m_reactionRangeSq;
        // one 32-bit unit: StateReaction<T>::seqUpdateMove loads both halves at once
        unsigned int m_reactionPercent : 16;
        unsigned int m_reactionMot : 16;  // the FLD_NpcMobMotionId row StateReaction::beginReaction runs
        unsigned short m_battleReaction;
        unsigned short m_battleMot;  // the FLD_NpcMobMotionId row StateBattle::seqApplyBattleMot runs
        // the talk StateTalk::enter starts with GfPlayFactory::createTalk ("EventID", or GfDataBlade's normal talk)
        unsigned short m_talkEventId;
        // set by create when m_talkEventId lies in BDAT sheet 0xeb's id range and m_shopId is 0
        bool pad_1a;
        unsigned char pad_1b[0x5];
    };
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorNpc();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    // its object's asm component (slot 2), none when the slot holds another kind
    virtual GfComAsm* getComAsm() const;  // slot 7
    // the gimmick its object is bound to, none when it is bound to none
    gmk::AGmkBase* getBindedGmkInst() const;
    // (re)makes its state machine: the npc's 7 states, one level deep
    void createFsm();
    // points its local steering at what the state with that ID needs (the npc states' enter and leave)
    void validateLocalSteer(npc::STATE_ID state);
    void execTurnCmdToPos(const mm::Vec3& pos);
    void execTurnCmd(float rotY, float speed, float threshold, float delay);
    // turns the npc by rotY (plus its local steering's current angle)
    void execTurnCmd(float rotY);
    // where its object stands (its transform's world position)
    const mm::Vec3& getPos() const;
    // the states call it as a command they started runs (StateApproachPc passes true once C_move ran); its unit
    // says what the flag selects
    void init(bool keep);
    void setGoalPos(const mm::Vec3& pos);
    void moveToGoal(float dt);
    // the state its schedule asks for next, -1 for none (StateIdle requests it)
    int getNexStateId();
    static mm::mtl::RTTI m_rtti;
    // its row's BDAT values (BdatInfo::create)
    BdatInfo m_bdatInfo;
    void* pad_b8;  // the destructor hands it to fw::NaviManager::releaseObject (a navi::NvmshAcObj)
    // where the npc walks to (setGoalPos; the name is not the original's)
    mm::Vec3 m_goalPos;
    // StateReaction<GfComBehaviorNpc>::onLeave hands its saved rotation back to it (the name is not the original's)
    mm::Quat m_reactionRot;
    // the player's squared distance from the npc across (x, z) and up (y): StateApproachPc compares them with
    // m_approachDistSq and getDistYThreshold's square (the names are not the original's)
    float m_playerDistSq;
    float m_playerDistYSq;
    unsigned char pad_e8[0x18];
    bool pad_100;  // StateTalk::seqWaitTalkEnd waits while it is set
    unsigned char pad_101[0x7];
    ai::Hfsm m_hfsm;
    // set while createFsm cleans up and sets the machine up again (the name is not the original's)
    bool m_buildingFsm;
    unsigned char pad_191[0x7];
    void* pad_198;  // its Listener clears it on a standby logout
    unsigned char pad_1a0[0xd0];
    // its walking speed (StateBattle::seqUpdateMove sets it; the name is not the original's)
    GfFieldMoveSpeed m_moveSpeed;
    unsigned char pad_2a0[0x40];
    // the turn command execTurnCmd starts; the states wait for its pad_6c (set once the turn ends) (the name is
    // not the original's)
    TFieldExecCmdTurn<GfComAsm> m_turnCmd;
    // execTurnCmd adds its current angle to the turn (the name is not the original's)
    GfFieldLocalSteer m_localSteer;
};
}  // namespace gf

#endif
