#include "mm/mtl/RTTI.h"
#include "ai/Event.h"
#include "gf/EnviromentSensor.h"
#include "gf/GfTargetProperty.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "classes/gf/pc/TaskFieldSensor.h"
#include "gf/pc/AgentUtilField.h"
#include "gf/MsgPcFieldHighJump.h"
#include "gf/MsgPcFieldWaterWarp.h"
#include "gf/MsgPcFieldWaterWarpBuddy.h"
#include "gf/FileStaticVec3.h"
#include "classes/fw/ComponentObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfObj.h"
#include "classes/ai/TaskNode.h"
#include "fw/UpdateInfo.h"
#include "mm/Math.h"

namespace gf { namespace pc {

void TaskFieldSensor::onEvent(ai::BlackBoard& bb, const ai::Event& event) {
    BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 24
    MM_ASSERT(pBB);
    switch (event.m_type) {
    case 1:
        onChangeActivate(*pBB, static_cast<const ai::ActivateEvent&>(event));
        break;
    }
}

inline void TaskFieldSensor::onChangeActivate(BlackBoardField& bb, const ai::ActivateEvent& event) {
    bb.m_property->setEnvSensorCheckFlags(0x20, event.m_active);
}

// whether the PC moved at least stackThreashold less along its velocity than the velocity would have carried it
// (1.0.0's function; 3.0.1 has no copy of it)
inline bool isStack(const GfComPropertyPc& property, const SensorAIParam& param, float deltaTime) {
    mm::Vec3 dir = property.m_velocity;
    float speed = dir.length();
    dir.normalize();
    float moved = dir.dot(property.m_pos - property.m_prevPos);
    return speed * deltaTime - moved >= param.stackThreashold;
}

void TaskFieldSensor::update(BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    const SensorAIParam* param = property->m_paramList->getAdapter(3).get<SensorAIParam>();
    GfGamePlayerFormation* formation = GfGamePlayerFormation::get();
    bb.m_followPos = formation->getFollowTransform(property->m_setupKind).position;
    bb.m_targetPos = formation->m_targetPos[property->m_setupKind];

    bb.m_flags.set(1, isStack(*property, *param, bb.m_updateInfo->m_deltaTime));

    const EnviromentSensor* sensor = property->getEnvSensor();
    const EnviromentSensor::ObstacleInfo* obstacle = sensor->getObstacleInfo();
    bb.m_flags.set(2, obstacle != nullptr && mm::acos(mm::clamp(obstacle->m_normal.dot(mm::Vec3::unitY), -1.0f, 1.0f)) *
                                                  (180.0f / 3.14159265f) >
                                              param->obstacleAngle);

    // with an obstacle: whether the PC can jump onto it (not under a low ceiling, nor with bit 5 of the sensor's
    // findings; then while its target is at least enableJumpOffset above the obstacle's plane)
    if (bb.m_flags & 2) {
        bool ceilLow =
            (sensor->m_flags & 8) && sensor->m_vertical.m_ceilHeight - property->m_pos.y <= param->enableJumpCeil;
        if ((sensor->m_flags & 0x20) || ceilLow) {
            bb.m_flags.set(4, false);
        } else {
            const EnviromentSensor::ObstacleInfo* face = sensor->getObstacleInfo();
            float dot = bb.m_targetPos.dot(face->m_normal);
            bb.m_flags.set(4, -(face->m_planeDist + dot) >= param->enableJumpOffset);
        }
    }

    // a pending notice: once its timer runs out, ask the PC to act on it each frame until it accepts or 5 seconds
    // have passed
    if (bb.m_flags & 0x40) {
        bb.m_noticeTimer -= bb.m_updateInfo->m_deltaTime;
        if (bb.m_noticeTimer <= 0.0f) {
            MsgPcFieldHighJump msg;
            GfObj* obj = static_cast<GfObj*>(property->m_owner);
            obj->sendMessage(obj, msg);
            if (msg.m_accepted || bb.m_noticeTimer <= -5.0f) {
                bb.m_flags &= ~0x40;
            }
        }
    } else if (bb.m_flags & 0x80) {
        bb.m_noticeTimer -= bb.m_updateInfo->m_deltaTime;
        if (bb.m_noticeTimer <= 0.0f) {
            MsgPcFieldWaterWarp msg;
            GfObj* obj = static_cast<GfObj*>(property->m_owner);
            obj->sendMessage(obj, msg);
            if (msg.m_accepted || bb.m_noticeTimer <= -5.0f) {
                bb.m_flags &= ~0x80;
            }
        }
    } else if (bb.m_flags & 0x200) {
        bb.m_noticeTimer -= bb.m_updateInfo->m_deltaTime;
        if (bb.m_noticeTimer <= 0.0f) {
            MsgPcFieldWaterWarpBuddy msg;
            GfObj* obj = static_cast<GfObj*>(property->m_owner);
            obj->sendMessage(obj, msg);
            if (msg.m_accepted || bb.m_noticeTimer <= -5.0f) {
                bb.m_flags &= ~0x200;
            }
        }
    }

    // a wall jump notice lasts while the PC's field status allows it
    if (!(bb.m_property->m_field.m_statusFlags & 0x10)) {
        bb.m_flags &= ~0x100;
    }
}

mm::mtl::RTTI TaskFieldSensor::m_rtti("TaskFieldSensor", &ai::TaskNode::m_rtti, nullptr);

}}  // namespace gf::pc
