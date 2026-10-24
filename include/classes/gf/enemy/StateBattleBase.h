#ifndef CLASSES_GF_ENEMY_STATEBATTLEBASE_H
#define CLASSES_GF_ENEMY_STATEBATTLEBASE_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }
namespace btl { class BattleCharacter; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorEnemy; }

namespace gf { namespace enemy {
// table 0x7100B65B30
class StateBattleBase : public ::gf::GfStateBase {
public:
    StateBattleBase();  // out of line: StateBattle::create calls it
    virtual ~StateBattleBase() {}  // slot 0: inline (the table's slot holds ai::State's)
    // true when the state runs (StateBattle::onEnter keeps the answer)
    virtual bool Enter(gf::GfComBehaviorEnemy*, ai::State*);  // slot 8
    virtual void Leave(gf::GfComBehaviorEnemy*, ai::State*);  // slot 9
    virtual void BeforeUpdate(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&);  // slot 10
    virtual void Update(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&);  // slot 11
    virtual void AfterUpdate(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&);  // slot 12
    virtual bool IsBattleActionState() const { return false; }  // slot 13
    // the owner while a slot runs (onEnter/onLeave/onStep/recieveMessage set it and clear it after; the name is
    // not the original's)
    void* m_owner;
};
}}  // namespace gf::enemy

#endif
