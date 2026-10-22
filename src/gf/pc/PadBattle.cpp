#include "classes/gf/pc/GfPropertyBattle.h"
#include "classes/gf/pc/StateBattleArts.h"
#include "classes/gf/pc/StateBattleAttack.h"

namespace gf { namespace pc {

void GfPropertyBattle::flush(const gf::GfComPropertyPc&) {}

void StateBattleArts::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleAttack::Leave(gf::GfComBehaviorPc*, ai::State*) {}

}}  // namespace gf::pc
