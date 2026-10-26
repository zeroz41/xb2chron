#ifndef CLASSES_GF_GFCOMBEHAVIORNPC_H
#define CLASSES_GF_GFCOMBEHAVIORNPC_H

#include "mm/mtl/RTTI.h"
#include "ai/Hfsm.h"
#include "mm/Quat.h"
#include "classes/gf/GfComBehavior.h"

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
        unsigned char pad_0[0x4];
        // how near (squared) the player must come for the npc to approach it: StateApproachPc compares the
        // player's squared distance with it, none when 0 (the name is not the original's)
        float m_approachDistSq;
        unsigned char pad_8[0x10];
        // the talk StateTalk::enter starts with GfPlayFactory::createTalk (the name is not the original's)
        unsigned short m_talkEventId;
        unsigned char pad_1a[0x1e];
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
    // the states call it as a command they started runs (StateApproachPc passes true once C_move ran); its unit
    // says what the flag selects
    void init(bool keep);
    void setGoalPos(const mm::Vec3& pos);
    void moveToGoal(float dt);
    // the state its schedule asks for next, -1 for none (StateIdle requests it)
    int getNexStateId();
    static mm::mtl::RTTI m_rtti;
    BdatInfo m_bdatInfo;
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
    unsigned char pad_1a0[0x140];
    // the turn command execTurnCmd starts: StateTalk::seqWaitTalkEnd treats a command with no target (-1), an angle
    // outside [0, pi] or no time as no turn (the names are not the original's)
    void* pad_2e0;
    unsigned char pad_2e8[0x4];
    float pad_2ec;
    float pad_2f0;
    float pad_2f4;
    unsigned char pad_2f8[0x54];
    bool m_turnEnded;  // set once the turn the states start ends: they wait for it (the name is not the original's)
    unsigned char pad_34d[0x3];
};
}  // namespace gf

#endif
