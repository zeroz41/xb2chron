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

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class CallBackCache; }
namespace gf { class GfComAsm; }
namespace gmk { class AGmkBase; }
namespace gf { class GfMenuCallContext; }
namespace gf { namespace enemy { enum STATE_ID : int; } }
namespace fw { class ReferenceFrame; }

namespace gf {
// table 0x7100B65E30; its IGfBehFieldOwner at 0x98
class GfComBehaviorEnemy : public ::gf::GfComBehavior, public IGfBehFieldOwner {
public:
    class Listener;
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
    virtual void getGmkBattleLockInfo(int&, int&) const;  // slot 10
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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits between
    // reqChangeBattle and validatePopPos and reads this class's state machine. What it does: sets pad_54e2 (the
    // flag before reqChangeBattle's) unless the state machine is in state 0 (battle), reqChangeBattle's shape.
    void fn_71004C1D20();
    // its menu object (the enemy's gauge): StateFieldSpawn disposes of it while spawning, makes it on leaving
    void disposeMenuObj();
    void createMenuObj();
    // turns the enemy to rotY (the turn command; ...Accurately: the exact direction)
    void execTurnCmd(float rotY);
    // the field state to take next, and whether a state may be taken (its isCondMatch): StateFieldAreaWalk's
    // seqChangeState asks both
    gf::enemy::STATE_ID getNextFieldStateId() const;
    bool isStateCondMatch(gf::enemy::STATE_ID state) const;
    void execTurnCmdAccurately(float rotY);
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
    unsigned char pad_54c8[0x18];
    // set while the enemy is counted in its sensor's battle lock (GmkBattleLock::pad_c4); update counts it in and
    // out, the destructor takes it out
    bool pad_54e0;
    bool pad_54e1;  // StateFieldWalk::leave clears it
    bool pad_54e2;  // fn_71004C1D20 sets it
    // set by reqChangeBattle (the name is not the original's)
    bool m_reqChangeBattle;
    unsigned char pad_54e4[0x4];
    void* pad_54e8;  // its Listener clears it on a standby logout
};
}  // namespace gf

#endif
