#include "classes/gf/GfComPropertyPc.h"
#include "gf/FileStaticVec3.h"
#include "classes/fw/ComponentObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "classes/gf/pc/TaskFieldJump.h"
#include "classes/gf/GfGameInsideBattleLock.h"
#include "gf/pc/AgentUtilField.h"
#include "classes/ai/TaskNode.h"

namespace gf { namespace pc {

bool TaskFieldJump::testCondition(const BlackBoardField& bb) {
    if ((bb.m_flags & 6) == 6) {
        return !GfGameInsideBattleLock::get()->m_hasLock;
    }
    return false;
}

void TaskFieldJump::update(BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    const Param* param = AgentUtilField::getAIParamAdapter(*property, PARAM_ID_FIELD_AI(4)).get<Param>();
    property->m_inputFlags.m_actions |= 4;
    float speed = property->m_velocity.length();
    if (!(speed > param->m_minSpeed)) {
        speed = param->m_minSpeed;
    }
    property->m_velocity = property->m_moveDir * speed;
}

mm::mtl::RTTI TaskFieldJump::m_rtti("TaskFieldJump", &ai::TaskNode::m_rtti, nullptr);

}}  // namespace gf::pc
