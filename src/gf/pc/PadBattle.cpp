#include "classes/gf/pc/GfPropertyBattle.h"
#include "classes/gf/pc/StateBattleArts.h"
#include "classes/gf/pc/StateBattleAttack.h"
#include "classes/gf/pc/StateBattleBladeArts.h"
#include "classes/gf/pc/StateBattleBladeChange.h"
#include "classes/gf/pc/StateBattleBladeGuard.h"
#include "classes/gf/pc/StateBattleBreak.h"
#include "classes/gf/pc/StateBattleDown.h"
#include "classes/gf/pc/StateBattleIdle.h"
#include "classes/gf/pc/StateBattleKizunaMax.h"
#include "classes/gf/pc/StateBattleKnockBack.h"
#include "classes/gf/pc/StateBattleMove.h"
#include "classes/gf/pc/StateBattlePutAwayWeapon.h"
#include "classes/gf/pc/StateBattlePutOutWeapon.h"
#include "classes/gf/pc/StateBattleRepelled.h"
#include "classes/gf/pc/StateBattleRescue.h"
#include "classes/gf/pc/StateBattleSpAttack.h"
#include "classes/gf/pc/StateBattleStart.h"
#include "classes/gf/pc/StateBattleSupport.h"

namespace gf { namespace pc {

void GfPropertyBattle::flush(const gf::GfComPropertyPc&) {}

void StateBattleArts::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleAttack::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleBladeArts::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleBladeChange::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleBladeGuard::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleBreak::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleDown::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleIdle::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleKizunaMax::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleKnockBack::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleMove::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattlePutAwayWeapon::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattlePutOutWeapon::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleRepelled::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleRescue::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleSpAttack::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleStart::Leave(gf::GfComBehaviorPc*, ai::State*) {}

void StateBattleSupport::Leave(gf::GfComBehaviorPc*, ai::State*) {}

}}  // namespace gf::pc
