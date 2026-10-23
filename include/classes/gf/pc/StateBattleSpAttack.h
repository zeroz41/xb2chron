#ifndef CLASSES_GF_PC_STATEBATTLESPATTACK_H
#define CLASSES_GF_PC_STATEBATTLESPATTACK_H

#include "classes/gf/pc/StateBattleActionBase.h"
#include <new>

namespace ai { class State; }
namespace btl { class BattleCharacter; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B67788
class StateBattleSpAttack : public ::gf::pc::StateBattleActionBase {
public:
    // what registerBattleStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateBattleSpAttack; }
    virtual ~StateBattleSpAttack();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    virtual void Enter(gf::GfComBehaviorPc*, ai::State*);  // slot 8
    virtual void Leave(gf::GfComBehaviorPc*, ai::State*);  // slot 9
    virtual void Update(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&);  // slot 11
};
}}  // namespace gf::pc

#endif
