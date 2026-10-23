#include "classes/gf/TFieldExecCmd.h"
#include "classes/gf/GfComBehaviorMob.h"
#include "classes/gf/mob/StateIdle.h"
#include "classes/gf/mob/StateMove.h"
#include "classes/gf/mob/StateSquadMember.h"
#include "classes/gf/mob/StateApproachPc.h"
#include "classes/gf/npc/StateAreaMove.h"
#include "classes/gf/npc/StateReaction.h"
#include "classes/gf/npc/StateBattle.h"
#include "classes/gf/GfComBehaviorMob/Listener.h"
#include "classes/gf/GfObj.h"
#include "classes/gmk/AGmkBase.h"
#include "fw/UpdateInfo.h"

namespace gf {

gmk::AGmkBase* GfComBehaviorMob::getBindedGmkInst() const {
    return gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
}

void GfComBehaviorMob::createFsm() {
    if (!m_buildingFsm) {
        m_buildingFsm = true;
        m_hfsm.cleanup();
    }
    m_hfsm.beginSetup(this, 7, 1);
    m_hfsm.registerState<mob::StateIdle>(0, -1);
    m_hfsm.registerState<mob::StateMove>(1, -1);
    m_hfsm.registerState<npc::StateAreaMove<GfComBehaviorMob> >(2, -1);
    m_hfsm.registerState<mob::StateSquadMember>(3, -1);
    m_hfsm.registerState<npc::StateReaction<GfComBehaviorMob> >(4, -1);
    m_hfsm.registerState<npc::StateBattle<GfComBehaviorMob> >(5, -1);
    m_hfsm.registerState<mob::StateApproachPc>(6, -1);
    m_hfsm.endSetup();
    m_buildingFsm = false;
}

void GfComBehaviorMob::Listener::onWkStandbyLogout() {
    m_owner->pad_53b8 = nullptr;
}

}  // namespace gf
