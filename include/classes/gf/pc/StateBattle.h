#ifndef CLASSES_GF_PC_STATEBATTLE_H
#define CLASSES_GF_PC_STATEBATTLE_H

#include "classes/gf/pc/StateBattleBase.h"

namespace ai { class State; }
namespace btl { class BattleCharacter; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B66B88
class StateBattle : public ::gf::pc::StateBattleBase {
public:
    virtual ~StateBattle();  // slot 0
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
