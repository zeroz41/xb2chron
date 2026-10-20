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
    virtual ~StateBattleBase();  // slot 0
    virtual void Enter(gf::GfComBehaviorEnemy*, ai::State*);  // slot 8
    virtual void Leave(gf::GfComBehaviorEnemy*, ai::State*);  // slot 9
    virtual void BeforeUpdate(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&);  // slot 10
    virtual void Update(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&);  // slot 11
    virtual void AfterUpdate(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&);  // slot 12
    virtual void IsBattleActionState() const;  // slot 13
};
}}  // namespace gf::enemy

#endif
