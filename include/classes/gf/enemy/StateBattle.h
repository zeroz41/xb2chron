#ifndef CLASSES_GF_ENEMY_STATEBATTLE_H
#define CLASSES_GF_ENEMY_STATEBATTLE_H

#include "classes/gf/enemy/StateBattleActionBase.h"

namespace ai { class State; }
namespace btl { class BattleCharacter; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorEnemy; }

namespace gf { namespace enemy {
// table 0x7100B65BB0
class StateBattle : public ::gf::enemy::StateBattleActionBase {
public:
    virtual ~StateBattle();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    virtual void Enter(gf::GfComBehaviorEnemy*, ai::State*);  // slot 8
    virtual void Leave(gf::GfComBehaviorEnemy*, ai::State*);  // slot 9
    virtual void Update(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&);  // slot 11
};
}}  // namespace gf::enemy

#endif
