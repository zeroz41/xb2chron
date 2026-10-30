#include "classes/gf/GfObjProperty.h"
#include "gf/GfObjUtil.h"
#include "gf/FileStaticVec3.h"
#include "gf/EnviromentSensor.h"
#include "gf/GfTargetProperty.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/pc/TaskFieldCheckWarp.h"
#include "classes/gf/pc/TaskFieldCheckWarpBattleWaterDead.h"
#include "classes/gf/pc/TaskFieldCheckWarpFallDead.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfComEnvSensor.h"
#include "classes/gf/GfGameManager.h"
#include "gf/pc/AgentUtilField.h"
#include "mm/mtl/RTTI.h"
#include "ai/Event.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "classes/ai/TaskNode.h"
#include "gf/GfObjUtil.h"
#include "fw/Transform.h"
#include "fw/UpdateInfo.h"
#include "mm/Math.h"

namespace gf { namespace pc {

void TaskFieldCheckWarp::onEvent(ai::BlackBoard& bb, const ai::Event& event) {
    BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 33
    MM_ASSERT(pBB);
    switch (event.m_type) {
    case 1:
        onChangeActivate(*pBB, static_cast<const ai::ActivateEvent&>(event));
        break;
    }
}

inline void TaskFieldCheckWarp::onChangeActivate(BlackBoardField&, const ai::ActivateEvent& event) {
    if (event.m_active) {
        m_stuckTime = 0.0f;
    }
}

inline bool TaskFieldCheckWarp::testCondition(const BlackBoardField& bb) {
    if ((bb.m_flags & 0x3C0) | (bb.m_property->m_field.m_statusFlags & 0x400)) {
        return false;
    }
    return (bb.m_property->m_stateFlags & 0x800) == 0;
}

void TaskFieldCheckWarp::update(BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    const WarpParam* param = property->m_paramList->getAdapter(2).get<WarpParam>();
    if (bb.m_flags & 1) {
        m_stuckTime += bb.m_updateInfo->m_deltaTime;
    } else {
        m_stuckTime = 0.0f;
    }

    if (!(bb.m_flags & 0x10)) {
        GfGamePlayerFormation* formation = GfGamePlayerFormation::get();
        GfObjProperty* followed =
            GfObjUtil::getProperty(formation->m_players[formation->m_players[property->m_setupKind].m_followIndex].m_handle);
        const GfObjProperty::TargetInfo* target = followed->m_target;
        if (target != nullptr && ((target->m_state | 4) == 5 || target->m_blocksFollowWarp)) {
            return;
        }
        fw::Transform warp;
        warp.rotation = formation->getFollowTransform(property->m_setupKind).rotation;
        warp.position = formation->m_formationPos[property->m_setupKind];
        mm::Vec3 diff = warp.position - property->m_pos;
        // each test with its own warp (the compiler merges the three copies)
        if (m_stuckTime >= param->stackTime) {
            property->m_warpType = 0;
            property->m_warpPos = warp.position;
            property->m_warpRot = warp.rotation;
            property->m_stateFlags |= 0x4000000;
        } else if (::fabsf(diff.y) >= param->distanceVert) {
            property->m_warpType = 0;
            property->m_warpPos = warp.position;
            property->m_warpRot = warp.rotation;
            property->m_stateFlags |= 0x4000000;
        } else if (mm::Vec3(diff.x, 0.0f, diff.z).length() >= param->distanceHorz) {
            property->m_warpType = 0;
            property->m_warpPos = warp.position;
            property->m_warpRot = warp.rotation;
            property->m_stateFlags |= 0x4000000;
        }
    } else {
        if (property->m_setupKind & 1) {
            return;
        }
        const WallAiParam* wallParam = AgentUtilField::getAIParamAdapter(*property, PARAM_ID_FIELD_AI(5)).get<WallAiParam>();
        fw::Transform transform;
        if (!AgentUtilField::getWallFollowTransform(bb, &transform)) {
            return;
        }
        mm::Vec3 push;
        if (AgentUtilField::calcParentPlayerPush(*property, transform.position, wallParam->escapeRange, &push)) {
            return;
        }
        mm::Vec3 diff = transform.position - property->m_pos;
        if (::fabsf(diff.y) >= param->distanceVertWall) {
            property->m_warpPos = transform.position;
            property->m_warpType = 1;
        } else if (mm::Vec3(diff.x, 0.0f, diff.z).length() >= param->distanceHorzWall) {
            property->m_warpType = 1;
            property->m_warpPos = transform.position;
        } else {
            return;
        }
        property->m_warpRot = transform.rotation;
        property->m_stateFlags |= 0x4000000;
    }
}

void TaskFieldCheckWarpBattleWaterDead::onEvent(ai::BlackBoard& bb, const ai::Event& event) {
    BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 191
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

inline void TaskFieldCheckWarpBattleWaterDead::onChangeActivate(BlackBoardField&, const ai::ActivateEvent& event) {
    if (event.m_active) {
        m_time = 0.0f;
    }
}

inline void TaskFieldCheckWarpBattleWaterDead::onCreate(BlackBoardField&, const ai::CreateEvent&) {
    mm::mtl::IntrusivePtr<fw::ParamList> list = fw::ParamManager::get()->m_paramLists[10];
    if (list) {
        m_param = list->getAdapter(0);
    }
}

inline bool TaskFieldCheckWarpBattleWaterDead::testCondition(const BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    if (!(property->m_field.m_statusFlags & 0x8000)) {
        return false;
    }
    return (property->m_stateFlags & 0x800) != 0;
}

void TaskFieldCheckWarpBattleWaterDead::update(BlackBoardField& bb) {
    m_time += bb.m_updateInfo->m_deltaTime;
    const float* warpTime;
    if (GfGameManager::isBattle() && (warpTime = m_param.get<float>()) != nullptr && m_time >= *warpTime) {
        GfComPropertyPc* property = bb.m_property;
        GfGamePlayerFormation* formation = GfGamePlayerFormation::get();
        GfObj* obj =
            GfObjUtil::getObj(formation->m_players[formation->m_players[property->m_setupKind].m_followIndex].m_handle);
        if (obj != nullptr) {
            GfComPropertyPc* followed = obj->getComponent<GfComPropertyPc>(5);
            // declared here: its lifetime starts before the tests, which keeps the component slot's null path
            fw::Transform warp;
            // read through a reference (a 4-byte aligned load): the original tests the flag and the water level with
            // two loads, which a load of the 16-byte aligned field would widen into one
            const unsigned int& flags = followed->m_stateFlags;
            if ((flags & 2) && followed->m_waterLevel == 0) {
                warp.rotation = formation->getFollowTransform(property->m_setupKind).rotation;
                const mm::Vec3& pos = formation->m_targetPos[property->m_setupKind];
                GfComEnvSensor* sensor = property->m_owner->getComponent<GfComEnvSensor>(11);
                const float* reach = sensor->m_param.get<float>();
                EnviromentSensor::VerticalPacket packet;
                packet.m_type = 3;
                packet.m_dir = mm::Vec3(-mm::Vec3::unitY.x, -mm::Vec3::unitY.y, -mm::Vec3::unitY.z);
                packet.m_rangeMin = -reach[0];
                packet.m_rangeMax = reach[1];
                EnviromentSensor::VerticalData data;
                packet.m_data = &data;
                EnviromentSensor::searchVertical(pos, &packet);
                if (!((packet.m_resultFlags & 2) && data.m_water.m_height - data.m_ground.m_pos.y >= 0.0f)) {
                    warp.position = pos;
                    property->m_warpType = 0;
                    property->m_warpPos = warp.position;
                    property->m_warpRot = warp.rotation;
                    property->m_stateFlags |= 0x4000000;
                }
            }
        }
    }
}

mm::mtl::RTTI TaskFieldCheckWarp::m_rtti("TaskFieldCheckWarp", &ai::TaskNode::m_rtti, nullptr);
mm::mtl::RTTI TaskFieldCheckWarpBattleWaterDead::m_rtti("TaskFieldCheckWarpBattleWaterDead", &ai::TaskNode::m_rtti, nullptr);
mm::mtl::RTTI TaskFieldCheckWarpFallDead::m_rtti("TaskFieldCheckWarpFallDead", &ai::TaskNode::m_rtti, nullptr);

}}  // namespace gf::pc
