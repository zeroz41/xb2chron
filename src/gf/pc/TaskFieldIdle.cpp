#include "classes/fw/UpdatableObject.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/pc/TaskFieldIdle.h"
#include "classes/gf/pc/TaskFieldIdleTurn.h"
#include "gf/GfObjUtil.h"
#include "classes/fw/ComponentObject.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "gf/pc/AgentUtilField.h"
#include "classes/ai/TaskNode.h"

namespace gf { namespace pc {

bool TaskFieldIdle::testCondition(const BlackBoardField&) {
    return true;
}

void TaskFieldIdle::update(BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    AgentUtilField::setIdleInput(*property);
    if (property->m_field.m_statusFlags & 4) {
        bb.m_flags &= ~8;
    }
}

bool TaskFieldIdleTurn::testCondition(const BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    GfComPropertyPc* leader = GfObjUtil::getObj(GfGameManager::getPartyLeader())->getComponent<GfComPropertyPc>(5);
    if ((property->m_field.m_statusFlags & 4) && bb.m_property->m_moveDir.dot(leader->m_moveDir) < 0.0f) {
        return (bb.m_flags & 8) != 0;
    }
    return false;
}

void TaskFieldIdleTurn::update(BlackBoardField& bb) {
    GfComPropertyPc* leader = GfObjUtil::getObj(GfGameManager::getPartyLeader())->getComponent<GfComPropertyPc>(5);
    bb.m_property->setInputDirPow(leader->m_moveDir, 1.0f);
    bb.m_flags &= ~8;
}


mm::mtl::RTTI TaskFieldIdle::m_rtti("TaskFieldIdle", &ai::TaskNode::m_rtti, nullptr);
mm::mtl::RTTI TaskFieldIdleTurn::m_rtti("TaskFieldIdleTurn", &ai::TaskNode::m_rtti, nullptr);

}}  // namespace gf::pc
