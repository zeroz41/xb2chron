#include "classes/gf/GfObjProperty.h"
#include "gf/GfObjUtil.h"
#include "mm/mtl/RTTI.h"
#include "ai/Event.h"
#include "gf/GfTargetProperty.h"
#include "gf/EnviromentSensor.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/navi/NvmshAcObjBase.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "classes/gf/pc/TaskFieldFollowTarget.h"
#include "classes/gf/pc/TaskFieldFollowMainPc.h"
#include "classes/gf/pc/TaskFieldFollowBuddyPc.h"
#include "gf/pc/AgentUtilField.h"
#include "gf/GfObjUtil.h"
#include "gf/FileStaticVec3.h"
#include "classes/navi/NvmshAcObj.h"
#include "classes/ai/TaskNode.h"
#include "fw/UpdateInfo.h"
#include "mm/Math.h"

namespace gf { namespace pc {

bool TaskFieldFollowTarget::testCondition(const BlackBoardField& bb) {
    navi::NvmshAcObj* nvmshAcObj = bb.m_nvmshAcObj;
    bool noNotice = (bb.m_flags & 0x3C0) == 0;  // none of the notices the sensor acts on is pending
    bool hasMoveVec = (nvmshAcObj->m_flags & 2) != 0;
    return noNotice && hasMoveVec;
}

void TaskFieldFollowTarget::update(BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    navi::NvmshAcObj* nvmshAcObj = bb.m_nvmshAcObj;
    nvmshAcObj->setBeginPos(property->m_pos);
    nvmshAcObj->setEndPos(bb.m_targetPos);
    mm::Vec3 toTarget(bb.m_targetPos.x - property->m_pos.x, 0.0f, bb.m_targetPos.z - property->m_pos.z);
    bb.m_targetDist = toTarget.length();
    mm::Vec3 toFollow(bb.m_followPos.x - property->m_pos.x, 0.0f, bb.m_followPos.z - property->m_pos.z);
    bb.m_followDist = toFollow.length();
}

void TaskFieldFollowMainPc::onEvent(ai::BlackBoard& bb, const ai::Event& event) {
    BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 117
    MM_ASSERT(pBB);
    switch (event.m_type) {
    case 1:
        onChangeActivate(*pBB, static_cast<const ai::ActivateEvent&>(event));
        break;
    case 2:
        onCreate(*pBB, static_cast<const ai::CreateEvent&>(event));
        break;
    }
}

inline void TaskFieldFollowMainPc::onChangeActivate(BlackBoardField&, const ai::ActivateEvent& event) {
    if (!event.m_active) {
        m_adjustTimer = 0.0f;
    }
}

inline void TaskFieldFollowMainPc::onCreate(BlackBoardField&, const ai::CreateEvent&) {
    m_adjustTimer = 0.0f;
    m_adjusting = false;
}

// whether the PC follows the main PC: always as the main PC, beyond the AI's followDist from the formation
// transform it follows, while the battle leader drives, and beyond stopDist from its target while it (standalone)
// or the player it follows is moving
bool isFollowMainPc(const BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    if (property->m_setupKind == 0) {
        return true;
    }
    const FollowMainPcParam* param =
        AgentUtilField::getAIParamAdapter(*property, PARAM_ID_FIELD_AI(property->m_waterLevel == 3)).get<FollowMainPcParam>();
    if (bb.m_followDist > param->followDist) {
        return true;
    }
    if (GfGameParty::isBtlLeaderDirver()) {
        return true;
    }
    if (bb.m_targetDist > param->stopDist) {
        GfGamePlayerFormation* formation = GfGamePlayerFormation::get();
        if (formation->m_players[property->m_setupKind].m_standalone) {
            return property->m_velocity.dot(property->m_velocity) > 0.0f || property->m_moveSpeed > 0.0f;
        }
        unsigned int followIndex = formation->m_players[property->m_setupKind].m_followIndex;
        if (followIndex != 0xFFFFFFFF) {
            GfObjProperty* followed = GfObjUtil::getProperty(formation->m_players[followIndex].m_handle);
            if (followed->m_target != nullptr) {
                return followed->m_target->m_isMoving;
            }
        }
    }
    return false;
}

inline bool TaskFieldFollowMainPc::testCondition(const BlackBoardField& bb) {
    bool follow = isFollowMainPc(bb);
    if (follow) {
        m_adjustTimer = 0.0f;
        m_adjusting = true;
    } else if (m_adjusting) {
        m_adjustTimer += bb.m_updateInfo->m_deltaTime;
    } else {
        m_adjustTimer = 0.0f;
    }
    const FollowMainPcParam* param = AgentUtilField::getAIParamAdapter(
        *bb.m_property, PARAM_ID_FIELD_AI(bb.m_property->m_waterLevel == 3)).get<FollowMainPcParam>();
    if (m_adjustTimer >= param->adjustTime && m_adjusting) {
        follow |= bb.m_targetDist >= param->adjustDist;
        m_adjusting = false;
    }
    return follow;
}

inline void TaskFieldFollowMainPc::update(BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    navi::NvmshAcObj* nvmshAcObj = bb.m_nvmshAcObj;
    const FollowMainPcParam* param =
        AgentUtilField::getAIParamAdapter(*property, PARAM_ID_FIELD_AI(property->m_waterLevel == 3)).get<FollowMainPcParam>();
    if (!(bb.m_flags & 0x400) && bb.m_followDist < param->walkDistStopFollower) {
        property->setInputDirPow(nvmshAcObj->getMoveVec(), 0.1f);
    } else {
        AgentUtilField::setFollowInput(bb.m_targetDist, nvmshAcObj, *property);
    }
    bb.m_flags |= 8;
}

// whether the PC follows the player it follows in the formation: not while that one is in target state 3; beyond
// the AI's stopDist from its target while it is moving, or while it (standalone) or the player it follows is
bool isFollowBuddyPc(const BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    GfGamePlayerFormation* formation = GfGamePlayerFormation::get();
    GfObjProperty* followed =
        GfObjUtil::getProperty(formation->m_players[formation->m_players[property->m_setupKind].m_followIndex].m_handle);
    if (followed->m_target->m_state == 3) {
        return false;
    }
    const FollowBuddyPcParam* param = AgentUtilField::getAIParamAdapter(
        *property, PARAM_ID_FIELD_AI(property->m_waterLevel == 3 ? 3 : 2)).get<FollowBuddyPcParam>();
    if (bb.m_targetDist > param->stopDist) {
        if (mm::fabs(property->m_moveVec2.y) > 0.0f) {
            return true;
        }
        if (property->m_velocity.dot(property->m_velocity) > 0.0f) {
            return true;
        }
        if (property->m_moveSpeed > 0.0f) {
            return true;
        }
    }
    formation = GfGamePlayerFormation::get();
    if (formation->m_players[property->m_setupKind].m_standalone) {
        return property->m_velocity.dot(property->m_velocity) > 0.0f || property->m_moveSpeed > 0.0f;
    }
    unsigned int followIndex = formation->m_players[property->m_setupKind].m_followIndex;
    if (followIndex != 0xFFFFFFFF) {
        GfObjProperty* followedNow = GfObjUtil::getProperty(formation->m_players[followIndex].m_handle);
        if (followedNow->m_target != nullptr) {
            return followedNow->m_target->m_isMoving;
        }
    }
    return false;
}

bool TaskFieldFollowBuddyPc::testCondition(const BlackBoardField& bb) {
    return isFollowBuddyPc(bb);
}

void TaskFieldFollowBuddyPc::update(BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    navi::NvmshAcObj* nvmshAcObj = bb.m_nvmshAcObj;
    const FollowBuddyPcParam* param = AgentUtilField::getAIParamAdapter(
        *property, PARAM_ID_FIELD_AI(property->m_waterLevel == 3 ? 3 : 2)).get<FollowBuddyPcParam>();
    if (!(bb.m_flags & 0x400) && bb.m_followDist < param->walkDistStopFollower) {
        property->setInputDirPow(nvmshAcObj->getMoveVec(), 0.1f);
    } else {
        AgentUtilField::setFollowInput(bb.m_targetDist, nvmshAcObj, *property);
    }
    bb.m_flags |= 8;
}

mm::mtl::RTTI TaskFieldFollowTarget::m_rtti("TaskFieldFollowTarget", &ai::TaskNode::m_rtti, nullptr);
mm::mtl::RTTI TaskFieldFollowMainPc::m_rtti("TaskFieldFollowMainPc", &ai::TaskNode::m_rtti, nullptr);
mm::mtl::RTTI TaskFieldFollowBuddyPc::m_rtti("TaskFieldFollowBuddyPc", &ai::TaskNode::m_rtti, nullptr);

}}  // namespace gf::pc
