#include "classes/fw/ComponentObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "classes/gf/pc/TaskFieldRetreat.h"
#include "classes/navi/NvmshAcObjBase.h"
#include "classes/navi/NvmshAcObj.h"
#include "gf/pc/AgentUtilField.h"
#include "classes/ai/TaskNode.h"
#include "mm/Math.h"

namespace gf { namespace pc {

bool TaskFieldRetreat::testCondition(const BlackBoardField& bb) {
    if (bb.m_flags & 0x10) {
        const mm::Vec3& pos = bb.m_property->m_pos;
        mm::Vec3 diff(bb.m_retreatPos.x - pos.x, bb.m_retreatPos.y - pos.y, bb.m_retreatPos.z - pos.z);
        return diff.length() > 1.0f;
    }
    return false;
}

void TaskFieldRetreat::update(BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    navi::NvmshAcObj* nvmshAcObj = bb.m_nvmshAcObj;
    nvmshAcObj->setBeginPos(property->m_pos);
    nvmshAcObj->setEndPos(bb.m_retreatPos);
    const mm::Vec3& pos = bb.m_property->m_pos;
    mm::Vec3 diff(bb.m_retreatPos.x - pos.x, bb.m_retreatPos.y - pos.y, bb.m_retreatPos.z - pos.z);
    float distance = mm::fabs(diff.dot(nvmshAcObj->getMoveVec()));
    float pow = AgentUtilField::setFollowInput(distance, nvmshAcObj, *property);
    if (distance < 3.0f && pow > 0.1f) {
        property->setInputDirPow(nvmshAcObj->getMoveVec(), 0.1f);
    }
    bb.m_flags |= 8;
}

mm::mtl::RTTI TaskFieldRetreat::m_rtti("TaskFieldRetreat", &ai::TaskNode::m_rtti, nullptr);

}}  // namespace gf::pc
