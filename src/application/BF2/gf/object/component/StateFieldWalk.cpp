#include "classes/gf/GfStateBase.h"
#include "classes/gf/enemy/StateBattleBase.h"
#include "classes/gf/enemy/StateBattleActionBase.h"
#include "classes/gf/enemy/StateBattle.h"
#include "classes/gf/enemy/StateFieldHome.h"
#include "classes/gf/enemy/StateFieldSquadMember.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/enemy/StateFieldWalk.h"
#include "classes/gf/enemy/StateFieldAreaWalk.h"
#include "classes/gf/enemy/StateFieldBlade.h"
#include "classes/gf/enemy/StateFieldSpawn.h"
#include "classes/gf/GfObj.h"
#include "classes/btl/CharacterManager.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/GfComPropertyEnemy.h"
#include "gf/MsgObjectNotifyAsmCallback.h"
#include "fw/Message.h"
#include "fw/UpdateInfo.h"

namespace gf {
namespace enemy {

void StateFieldWalk::seqIdleInfinit(GfComBehaviorEnemy&, const fw::UpdateInfo& info) { m_execCmd.update(info.m_deltaTime); }

void StateFieldWalk::leave(GfComBehaviorEnemy* owner, ai::State*) { owner->pad_54e1 = false; }

void StateFieldWalk::seqWaitToIdleAtRoutePoint(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done) {
        if (m_hasPointRotY) {
            owner.execTurnCmdAccurately(m_pointRotY);
        }
        m_seq = &StateFieldWalk::seqWaitTurnEndAtRoutePoint;
    }
}

bool StateFieldWalk::isCondMatch(const GfComBehaviorEnemy& owner) {
    gmk::AGmkBase* gmk = owner.getBindedGmkInst();
    if (gmk == nullptr) {
        return false;
    }
    return static_cast<unsigned int>(gmk->getGmkType()) < 2;
}

}  // namespace enemy
}  // namespace gf
