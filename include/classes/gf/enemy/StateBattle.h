#ifndef CLASSES_GF_ENEMY_STATEBATTLE_H
#define CLASSES_GF_ENEMY_STATEBATTLE_H

#include "classes/gf/enemy/StateBattleActionBase.h"
#include <new>

namespace ai { class State; }
namespace btl { class BattleCharacter; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorEnemy; }

namespace gf { namespace enemy {
// table 0x7100B65BB0
class StateBattle : public ::gf::enemy::StateBattleActionBase {
public:
    StateBattle() {}
    // what GfComBehaviorEnemy::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateBattle; }
    virtual ~StateBattle() {}  // slot 0: inline (the table's slot holds ai::State's)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    virtual bool Enter(gf::GfComBehaviorEnemy*, ai::State*);  // slot 8
    virtual void Leave(gf::GfComBehaviorEnemy*, ai::State*);  // slot 9
    virtual void Update(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&);  // slot 11
    // what Enter answered: onStep runs the update slots only when set (registerState<StateBattle> sizes it 0x28;
    // the name is not the original's)
    bool m_entered;
};
}}  // namespace gf::enemy

#endif
