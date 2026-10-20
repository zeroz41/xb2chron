#ifndef CLASSES_GF_PC_STATEBATTLEBLADECHANGE_H
#define CLASSES_GF_PC_STATEBATTLEBLADECHANGE_H

#include "classes/gf/pc/StateBattleActionBase.h"

namespace ai { class State; }
namespace btl { class BattleCharacter; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B66E08
class StateBattleBladeChange : public ::gf::pc::StateBattleActionBase {
public:
    virtual ~StateBattleBladeChange();  // slot 0
    virtual void getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    virtual void Enter(gf::GfComBehaviorPc*, ai::State*);  // slot 8
    virtual void Leave(gf::GfComBehaviorPc*, ai::State*);  // slot 9
    virtual void Update(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&);  // slot 11
};
}}  // namespace gf::pc

#endif
