#ifndef CLASSES_GF_GFCOMBEHAVIORENEMY_H
#define CLASSES_GF_GFCOMBEHAVIORENEMY_H

#include "mm/mtl/RTTI.h"
#include "ai/Hfsm.h"
#include "fw/Transform.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfBehaviorEnemyField.h"
#include "classes/gf/IGfBehFieldOwner.h"
#include "classes/gf/GfFieldDmg.h"
#include "classes/gf/TFieldExecCmdTurn.h"
#include "gf/GfFieldUndulator.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class ColiMoveObject; }
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class CallBackCache; }
namespace gf { class GfComAsm; }
namespace gf { class MsgObjectNotifyDead; class MsgObjectNotifyDamage; }
namespace gmk { class AGmkBase; }
namespace gf { class GfMenuCallContext; }
namespace gf { namespace enemy { enum STATE_ID : int; } }
namespace fw { class ReferenceFrame; }

namespace gf {
// table 0x7100B65E30; its IGfBehFieldOwner at 0x98
class GfComBehaviorEnemy : public ::gf::GfComBehavior, public IGfBehFieldOwner {
public:
    // table 0x7100B65F28; the constructor builds one at 0x54f0 (a member, so defined here; Listener.h includes this)
    class Listener {
    public:
        virtual void onWkStandbyLogout();  // slot 0
        GfComBehaviorEnemy* m_owner;  // the behavior it listens for (the name is not the original's)
    };
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    // the table's key function: takes the enemy out of its battle lock's count, cleans up, then the members go
    virtual ~GfComBehaviorEnemy();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    virtual void procAnimCallback(gf::GfComAsm*, gf::CallBackCache const&);  // slot 6
    // where it searches for the player from: pad_138's world transform when it has that frame, else getTransform's
    virtual const fw::Transform& getTransformToSearchPlayer() const;  // slot 7
    // its object's world transform (the transform component's frame)
    virtual const fw::Transform& getTransform() const;  // slot 8
    // its setup's CHR_EnArrange row
    virtual unsigned int getBdatId_CHR_EnArrange() const;  // slot 9
    // its squad gimmick's set row (the GmkSet's RSC_GmkSetList row) and the gimmick's battlelockname - 1; false when
    // its object is bound to no gimmick or the gimmick has no BDAT table
    virtual bool getGmkBattleLockInfo(int&, int&) const;  // slot 10
    // an animation callback of the field (empty; StateFieldHome's unit holds it)
    void callbackField(gf::GfComAsm* asmCom, const gf::CallBackCache& cache);
    // an animation callback of the battle (empty; GfEnemyBattleProperty's unit holds it)
    void callbackBattle(gf::GfComAsm* asmCom, const gf::CallBackCache& cache);
    // the gimmick its object is bound to, none when it is bound to none
    gmk::AGmkBase* getBindedGmkInst() const;
    // whether its CHR_EnArrange row's act type (SDataEnemy::m_actType) is 3 (flying) / 1 (in water)
    bool isFly() const;
    bool isWater() const;
    // flying (isFly) and its setup's actMove row (BDAT 0x6e) has actMove_Atr bit 0 (insect) / bit 1 (circle)
    bool isFlyInsect() const;
    bool isFlyCircle() const;
    // its state machine's state (-1 with none)
    gf::enemy::STATE_ID getStateId() const;
    // asks for battle (m_reqChangeBattle) unless it is in battle (state 0) already
    void reqChangeBattle();
    // 2.0.0's symbols name it. What it does: sets pad_54e2 (the flag before reqChangeBattle's) unless the state machine
    // is in state 0 (battle), reqChangeBattle's shape.
    void reqChangeBattleAfterIdle();
    // 2.0.0's symbols name it. What it does: updates the field movement by the frame's delta time; for an enemy blade
    // whose driver's character is in battle it takes state 0 (battle, setStateId); then it takes state 13 (home) when
    // m_field.pad_52a9 is set and it is not in that state already.
    void updateField(const fw::UpdateInfo& info);
    // 2.0.0's symbols name it. What it does: sets the state machine to state; for state 0 (battle) it first clears
    // pad_54e2, m_reqChangeBattle and pad_5508, sets m_pitchRoll.pad_30 and pad_31, gives its object flag bit 2 (pad_110
    // |= 4) and takes its invincibility off unless its setup's arrange row is one of the siren battle's two
    // (SirenBattleManager m_params[].m_arrangeID), and has a squad member's others ask for battle
    // (reqChangeBattleToOtherMember).
    void setStateId(gf::enemy::STATE_ID state);
    // has every other member of its squad gimmick (T: GmkEnemy, GmkRoutedEnemy) that is not in battle, nor in state
    // 0 or 13 (home), ask for battle (reqChangeBattle)
    template <typename T>
    void reqChangeBattleToOtherMember() const;
    // whether another member of its squad gimmick (T: GmkEnemy, GmkRoutedEnemy) is in battle (GfObjAcc::isBattle)
    template <typename T>
    bool isOtherMemberBattle() const;
    // makes the field movement (createBehField), then takes its first state: battle (0) for the siren battle's
    // enemies, 15 for an enemy blade, else by its gimmick's pop_act_type; battle when a squad member is in battle
    void onPopped();
    void createBehField();
    // its handlers of messages 0x100003A (a damage notice) and 0x100003B (its death), from recieveMessage
    void procMsgObjectNotifyDead(fw::MessageObject* sender, gf::MsgObjectNotifyDead& msg);
    void procMsgObjectNotifyDamage(fw::MessageObject* sender, gf::MsgObjectNotifyDamage& msg);
    // its menu object (the enemy's gauge): StateFieldSpawn disposes of it while spawning, makes it on leaving
    void disposeMenuObj();
    void createMenuObj();
    // turns the enemy to rotY (the turn command; ...Accurately: the exact direction)
    void execTurnCmd(float rotY);
    // the same with the turn's threshold (CreateInfo::pad_c), speed (pad_14) and delay (pad_18) given
    void execTurnCmd(float rotY, float speed, float threshold, float delay);
    // its object's first collision object when that is a move object (GfComBehaviorNpc::getColiObject's shape)
    fw::ColiMoveObject* getColiObject() const;
    // hands dir to its object's first collision object (ColiObject::setDir)
    void moveProc(mm::Vec3& dir);
    // turns its object's world rotation by rotY about the y axis / by rot (StateBattleActionBase::AfterUpdate)
    void rotProc(float rotY);
    void rotProc(const mm::Quat& rot);
    // half the diagonal of its first collision object's bounding box (0 without one)
    float getCollisionRadius() const;
    // whether another member of its squad gimmick (T: GmkEnemy, GmkRoutedEnemy) is in the home state (13)
    bool isOtherMemberHome() const;
    template <typename T>
    bool isOtherMemberHome() const;
    // the field state to take next, and whether a state may be taken (its isCondMatch): StateFieldAreaWalk's
    // seqChangeState asks both
    gf::enemy::STATE_ID getNextFieldStateId() const;
    bool isStateCondMatch(gf::enemy::STATE_ID state) const;
    void execTurnCmdAccurately(float rotY);
    // turns the enemy toward its move direction (GfBehaviorEnemyField::getMoveDir) in the xz plane
    void execTurnCmdToGoal();
    void extractLoco();
    // (re)makes its state machine: the enemy's 16 states (battle, field idle/spawn/walk/home/squad/blade)
    void createFsm();
    // disposes the field movement, the state machine and the menu object, cleans the plugins up and lets the
    // search frame go
    void cleanup();
    // takes its state machine down unless it is being built (inline: cleanup holds it in place)
    void disposeFsm() {
        if (!m_buildingFsm) {
            m_buildingFsm = true;
            m_hfsm.cleanup();
        }
    }
    static mm::mtl::RTTI m_rtti;
    ai::Hfsm m_hfsm;
    // set while createFsm cleans up and sets the machine up again (the name is not the original's)
    bool m_buildingFsm;
    unsigned char pad_129[0x7];
    // its menu object's call context: disposeMenuObj closes the menu and releases it (the name is not the original's)
    gf::GfMenuCallContext* m_menuContext;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> pad_138;  // getTransformToSearchPlayer's frame when set
    // its field movement (the name is not the original's)
    GfBehaviorEnemyField m_field;
    // the turn execTurnCmd starts; the field states' seqWaitTurnEnd wait for its pad_6c (the names of these three
    // are not the original's)
    TFieldExecCmdTurn<GfComAsm> m_turnCmd;
    GfFieldUndulator m_undulator;
    GfFieldDmg m_fieldDmg;
    unsigned char pad_54c8[0x8];
    mm::Vec3 pad_54d0;  // what it answers MsgObjectGetVelocity (0x1000049) with
    // set while the enemy is counted in its sensor's battle lock (GmkBattleLock::pad_c4); update counts it in and
    // out, the destructor takes it out
    bool pad_54e0;
    bool pad_54e1;  // StateFieldWalk::leave clears it
    bool pad_54e2;  // reqChangeBattleAfterIdle sets it
    // set by reqChangeBattle (the name is not the original's)
    bool m_reqChangeBattle;
    bool pad_54e4;  // recieveMessage sets it on message 0x1000044 (before the damage it hands its sender)
    unsigned char pad_54e5[0x3];
    void* pad_54e8;  // its Listener clears it on a standby logout
    // the constructor's listener (the name is not the original's)
    Listener m_listener;
    bool pad_5500;  // updateWeapon
    bool pad_5501;  // updateWeapon
    unsigned char pad_5502[0x6];
    int pad_5508;  // setStateId clears it on entering battle
    bool pad_550c;  // zeroed by the constructor
    bool pad_550d;  // onPopped: set for pop action types 5 and 6
};
}  // namespace gf

#endif
