#include "classes/gf/TFieldExecCmd.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/enemy/StateBattle.h"
#include "classes/gf/enemy/StateFieldIdle.h"
#include "classes/gf/enemy/StateFieldSpawn.h"
#include "classes/gf/enemy/StateFieldAreaWalk.h"
#include "classes/gf/enemy/StateFieldWalk.h"
#include "classes/gf/enemy/StateFieldHome.h"
#include "classes/gf/enemy/StateFieldSquadMember.h"
#include "classes/gf/enemy/StateFieldBlade.h"
#include "classes/gf/GfComBehaviorEnemy/Listener.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComTransform.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/SDataEnemy.h"
#include "classes/gmk/AGmkBase.h"
#include "fw/UpdateInfo.h"

namespace gf {

// GfComBehavior's own empty virtuals (its table is emitted here: changeLayer is its key function)
void GfComBehavior::changeLayer(unsigned int, unsigned int) {}

void GfComBehavior::procAnimCallback(GfComAsm*, const CallBackCache&) {}

gmk::AGmkBase* GfComBehaviorEnemy::getBindedGmkInst() const {
    return gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
}

const fw::Transform& GfComBehaviorEnemy::getTransform() const {
    GfComTransform* transform = static_cast<GfObj*>(m_owner)->getComponent<GfComTransform>(0);
    return transform->getFrame()->getWorldTransform();
}

bool GfComBehaviorEnemy::isFly() const {
    DataParamAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
    return acc.getSDataEnemy()->m_actType == 3;
}

bool GfComBehaviorEnemy::isWater() const {
    DataParamAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
    return acc.getSDataEnemy()->m_actType == 1;
}

void GfComBehaviorEnemy::createFsm() {
    if (!m_buildingFsm) {
        m_buildingFsm = true;
        m_hfsm.cleanup();
    }
    m_hfsm.beginSetup(this, 16, 3);
    m_hfsm.registerState<enemy::StateBattle>(0, -1);
    m_hfsm.registerState<enemy::StateFieldIdle>(1, -1);
    m_hfsm.registerState<enemy::StateFieldIdle>(2, -1);
    m_hfsm.registerState<enemy::StateFieldIdle>(3, -1);
    m_hfsm.registerState<enemy::StateFieldIdle>(4, -1);
    m_hfsm.registerState<enemy::StateFieldIdle>(5, -1);
    m_hfsm.registerState<enemy::StateFieldSpawn>(6, -1);
    m_hfsm.registerState<enemy::StateFieldSpawn>(7, -1);
    m_hfsm.registerState<enemy::StateFieldAreaWalk>(8, -1);
    m_hfsm.registerState<enemy::StateFieldWalk>(9, -1);
    m_hfsm.registerState<enemy::StateFieldAreaWalk>(10, -1);
    m_hfsm.registerState<enemy::StateFieldWalk>(11, -1);
    m_hfsm.registerState<enemy::StateFieldHome>(13, -1);
    m_hfsm.registerState<enemy::StateFieldSquadMember>(14, -1);
    m_hfsm.registerState<enemy::StateFieldBlade>(15, -1);
    m_hfsm.endSetup();
    m_buildingFsm = false;
}

void GfComBehaviorEnemy::Listener::onWkStandbyLogout() {
    m_owner->pad_54e8 = nullptr;
}

}  // namespace gf
