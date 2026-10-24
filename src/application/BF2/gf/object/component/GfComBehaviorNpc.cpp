#include "classes/gf/TFieldExecCmd.h"
#include "classes/gf/GfComBehaviorNpc.h"
#include "classes/gf/npc/StateIdle.h"
#include "classes/gf/npc/StateWalk.h"
#include "classes/gf/npc/StateAreaMove.h"
#include "classes/gf/npc/StateApproachPc.h"
#include "classes/gf/npc/StateReaction.h"
#include "classes/gf/npc/StateBattle.h"
#include "classes/gf/npc/StateTalk.h"
#include "classes/gf/GfComBehaviorNpc/Listener.h"
#include "classes/gf/GfComBehaviorNpc/LocalSteerIsTargetNotPlayer.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfObj.h"
#include "classes/gmk/AGmkBase.h"
#include "fw/UpdateInfo.h"

namespace gf {

float GfComBehaviorNpc::BdatInfo::getDistYThreshold() {
    return 2.0f;
}

bool GfComBehaviorNpc::LocalSteerIsTargetNotPlayer::operator()(const GfFieldLocalSteer& steer,
                                                                GF_OBJ_HANDLE* target) const {
    return GfGameManager::getPartyLeader() != target;
}

gmk::AGmkBase* GfComBehaviorNpc::getBindedGmkInst() const {
    return gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
}

void GfComBehaviorNpc::createFsm() {
    if (!m_buildingFsm) {
        m_buildingFsm = true;
        m_hfsm.cleanup();
    }
    m_hfsm.beginSetup(this, 7, 1);
    m_hfsm.registerState<npc::StateIdle>(0, -1);
    m_hfsm.registerState<npc::StateWalk>(1, -1);
    m_hfsm.registerState<npc::StateAreaMove<GfComBehaviorNpc> >(2, -1);
    m_hfsm.registerState<npc::StateApproachPc>(3, -1);
    m_hfsm.registerState<npc::StateReaction<GfComBehaviorNpc> >(4, -1);
    m_hfsm.registerState<npc::StateBattle<GfComBehaviorNpc> >(5, -1);
    m_hfsm.registerState<npc::StateTalk>(6, -1);
    m_hfsm.endSetup();
    m_buildingFsm = false;
}

GfComAsm* GfComBehaviorNpc::getComAsm() const {
    return m_owner->getComponent<GfComAsm>(2);
}

void GfComBehaviorNpc::Listener::onWkStandbyLogout() {
    m_owner->pad_198 = nullptr;
}

}  // namespace gf
