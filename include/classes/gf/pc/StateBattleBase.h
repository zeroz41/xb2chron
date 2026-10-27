#ifndef CLASSES_GF_PC_STATEBATTLEBASE_H
#define CLASSES_GF_PC_STATEBATTLEBASE_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }
namespace btl { class BattleCharacter; }
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class GfComPropertyPc; }
namespace gf { class MsgObjectNotifyDead; }
namespace gf { namespace pc { class GfPropertyBattle; } }

namespace gf { namespace pc {
// a player state's ID (the Hfsm's state IDs)
enum STATE_ID : int;

// table 0x7100B66D08
class StateBattleBase : public ::gf::GfStateBase {
public:
    StateBattleBase();  // out of line (the states' create functions call it)
    virtual ~StateBattleBase() {}  // slot 0: inline (its derived states' deleting destructors only free them)
    virtual bool recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    // bool: StateBattleStart::Enter tests what StateBattleActionBase::Enter returns and returns 0 or 1
    virtual bool Enter(gf::GfComBehaviorPc*, ai::State*);  // slot 8
    virtual void Leave(gf::GfComBehaviorPc*, ai::State*);  // slot 9: out of line (0x71004E75DC)
    virtual void BeforeUpdate(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&) {}  // slot 10
    virtual void Update(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&);  // slot 11: out of line (0x71004E6DD8)
    virtual void AfterUpdate(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&) {}  // slot 12
    virtual bool IsBattleActionState() const { return false; }  // slot 13
    // what the battle states' onEnter/onLeave/onStep slots hand the owner to
    void enter(gf::GfComBehaviorPc* behavior, ai::State* prev);
    void leave(gf::GfComBehaviorPc* behavior, ai::State* next);
    void update(gf::GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    btl::BattleCharacter* GetBattleCharacter();
    // asks the machine for state (once per step: ai_state.h's assertion) and keeps arg in the battle property's
    // m_actionParam (the PC's battle property); nothing when already in it
    void ChangeState(STATE_ID state, int arg);
    // the owner's property component (none when slot 5 holds another kind)
    GfComPropertyPc* GetProperty();
    const GfPropertyBattle* GetBattlePropertyConst() const;
    // a death the PC's battle character was told of: a controlled character's dead kinds 3 and 4 set the battle's
    // flag; relayed to the buddy while the character is a blade (fn_710002F1F8)
    void procMsgObjectNotifyDead(gf::GfComBehaviorPc* behavior, fw::MessageObject* from, gf::MsgObjectNotifyDead& msg);

    // Every battle state is 0x28 bytes (registerBattleStates' sizes)
    // the owner while a slot runs (enter/leave/update/recieveMessage set it and clear it after; the name is not the
    // original's)
    gf::GfComBehaviorPc* m_owner;
    // what Enter answered: update runs the update slots only when set (the name is not the original's)
    bool m_entered;
    // set with each state change the battle state requests (StateBattleActionBase::Update sets it with m_reqState);
    // the name is not the original's
    bool m_stateChangeRequested;
};
}}  // namespace gf::pc

#endif
