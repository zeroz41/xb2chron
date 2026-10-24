#ifndef CLASSES_GF_ENEMY_STATEBATTLEACTIONBASE_H
#define CLASSES_GF_ENEMY_STATEBATTLEACTIONBASE_H

#include "classes/gf/enemy/StateBattleBase.h"

namespace ai { class State; }
namespace btl { class BattleCharacter; }
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorEnemy; }

namespace gf { namespace enemy {
// table none (its derived classes')
// its base is StateBattleBase: StateBattle::create calls StateBattleBase's constructor and stores only StateBattle's
// table, so this constructor is inline and adds nothing
class StateBattleActionBase : public ::gf::enemy::StateBattleBase {
public:
    StateBattleActionBase() {}
    virtual ~StateBattleActionBase() {}  // slot 0: inline (StateBattle's destructor folds into ai::State's)
    virtual bool recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    virtual bool Enter(gf::GfComBehaviorEnemy*, ai::State*) = 0;  // slot 8
    virtual void Leave(gf::GfComBehaviorEnemy*, ai::State*) = 0;  // slot 9
    virtual void BeforeUpdate(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&);  // slot 10
    virtual void Update(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&) = 0;  // slot 11
    // 1.0.0's name, from its table (same slot)
    virtual void AfterUpdate(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&);  // slot 12
    virtual bool IsBattleActionState() const { return true; }  // slot 13
};
}}  // namespace gf::enemy

#endif
