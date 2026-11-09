#include "mm/mtl/Delegate.h"
#include "classes/gf/pc/PadField.h"
#include "btl/Utility.h"
#include "anm/AsmAnnotetion.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "gf/pc/AgentUtilField.h"
#include "classes/gf/GfMoveRunControler.h"
#include "gf/pc/MoveUtilField.h"
#include "classes/gf/pc/PadField.h"
#include "gf/pc/MoveUtilField.h"
#include "classes/gf/GfMoveFallControler.h"
#include "classes/gf/GfMoveJumpBackControler.h"
#include "classes/gf/GfMoveTurnControler.h"
#include "classes/gf/GfMoveBrakeControler.h"
#include "classes/gf/GfMoveWaterSinkControler.h"
#include "classes/gf/GfMoveWaterRiseControler.h"
#include "classes/gf/GfMoveSlideControler.h"
#include "classes/fw/ParamList.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "gf/pc/AgentUtilField.h"
#include "classes/anm/ResASM.h"
#include "anm/AsmAnnotetion.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/btl/BattleGlobal.h"
#include "btl/challenge_battle_manager.h"
#include "btl/Utility.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/pc/AIAgent.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "gf/OwnerBonus.h"
#include "gf/pc/StateUtilField.h"
#include "classes/navi/NvmshAcObj.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfObjProperty.h"
#include "gf/GfTargetProperty.h"
#include "gf/pc/AIAgentField.h"
#include "mm/Math.h"
#include "mm/mtl/RTTI.h"
#include <float.h>
#include <math.h>

namespace gf { namespace pc {

void AgentUtilField::setIdleInput(GfComPropertyPc& property) {
    property.setInputDirPow(property.m_moveDir, 0.0f);
}

// the formation's standalone players follow by the main PC's parameters, the others by the buddies'
float AgentUtilField::setFollowInput(float distance, navi::NvmshAcObj* nvmshAcObj, GfComPropertyPc& property) {
    if (GfGamePlayerFormation::get()->m_players[property.m_setupKind].m_standalone) {
        return funcFollowInput<FollowMainPcParam, PARAM_ID_FIELD_AI(0), PARAM_ID_FIELD_AI(1)>(distance, nvmshAcObj,
                                                                                            property);
    }
    return funcFollowInput<FollowBuddyPcParam, PARAM_ID_FIELD_AI(2), PARAM_ID_FIELD_AI(3)>(distance, nvmshAcObj,
                                                                                         property);
}

template <typename PARAM, PARAM_ID_FIELD_AI ID, PARAM_ID_FIELD_AI WATER_ID>
float funcFollowInput(float distance, navi::NvmshAcObj* nvmshAcObj, GfComPropertyPc& property) {
    const PARAM* param =
        AgentUtilField::getAIParamAdapter(property, property.m_waterLevel == 3 ? WATER_ID : ID).template get<PARAM>();
    float range = ::fabsf(param->powMaxDist - param->powMinDist);
    float pow;
    if (range > FLT_EPSILON) {
        pow = (distance - param->powMinDist) / range;
    } else {
        pow = 0.0f;
    }
    pow = mm::clamp(pow, 0.0f, 1.0f);
    property.setInputDirPow(nvmshAcObj->getMoveVec(), pow);
    return pow;
}

template float funcFollowInput<FollowMainPcParam, PARAM_ID_FIELD_AI(0), PARAM_ID_FIELD_AI(1)>(
    float, navi::NvmshAcObj*, GfComPropertyPc&);
template float funcFollowInput<FollowBuddyPcParam, PARAM_ID_FIELD_AI(2), PARAM_ID_FIELD_AI(3)>(
    float, navi::NvmshAcObj*, GfComPropertyPc&);

// the stick that follows the wall toward pos: each axis pushed fully once pos is past the field's climb thresholds
// along it (up/down by m_frontDir, to the sides by m_sideDir)
mm::Vec2 AgentUtilField::calcFollowWallInput(const mm::Vec3& pos, GfComPropertyPc& property) {
    mm::Vec2 input = mm::Vec2::zero;
    mm::Vec3 diff = pos - property.m_pos;
    float front = diff.dot(property.m_frontDir);
    if (front >= 0.0f) {
        input.y = front >= property.m_field.m_climbUpTime ? 1.0f : 0.0f;
    } else {
        input.y = front <= -property.m_field.m_climbDownTime ? -1.0f : 0.0f;
    }
    float side = diff.dot(property.m_sideDir);
    if (side >= 0.0f) {
        input.x = side >= property.m_field.m_climbSideTime ? 1.0f : 0.0f;
    } else {
        input.x = side <= -property.m_field.m_climbSideTime ? -1.0f : 0.0f;
    }
    return input;
}

// the stick toward pos on the wall: its y by the side of the facing pos is on, its x pushed fully only once pos is
// m_climbSideTime or more to either side
void AgentUtilField::setFollowWallEndInput(const mm::Vec3& pos, GfComPropertyPc& property) {
    mm::Vec3 diff = pos - property.m_pos;
    property.m_inputDir.y = diff.dot(property.m_frontDir) >= 0.0f ? 1.0f : -1.0f;
    float side = diff.dot(property.m_sideDir);
    if (side >= 0.0f) {
        property.m_inputDir.x = side >= property.m_field.m_climbSideTime ? 1.0f : 0.0f;
    } else {
        property.m_inputDir.x = side <= -property.m_field.m_climbSideTime ? -1.0f : 0.0f;
    }
}

// the transform the PC follows a wall climber by while the blackboard's bit 4 is set: its player index / 2 times
// the wall AI's delay back in the blackboard's queue; false when the queue is not that long
bool AgentUtilField::getWallFollowTransform(const BlackBoardField& bb, fw::Transform* transform) {
    GfComPropertyPc& property = *bb.m_property;
    fw::ParamAdapter adapter = getAIParamAdapter(property, PARAM_ID_FIELD_AI(5));
    if (bb.m_flags.m_value & 0x10) {
        unsigned int index = adapter.get<WallAiParam>()->delay * (property.m_setupKind >> 1);
        if (bb.m_wallFollowTransforms.size() > index) {
            *transform = bb.m_wallFollowTransforms[index];
            return true;
        }
    }
    return false;
}

fw::ParamAdapter AgentUtilField::getAIParamAdapter(GfComPropertyPc& property, PARAM_ID_FIELD_AI id) {
    GfComBehaviorPc* behavior = property.m_owner->findComponent<GfComBehaviorPc>(6);
    AIAgent* agent = mm::mtl::rttiCast<AIAgent>(behavior->m_agent.get());
    return agent->m_field.m_paramList->getAdapter(id);
}

// whether the climb toward the wall's end is over: not while the blackboard's bit 4 is set, otherwise once no player
// is within the wall AI's climbEndSafeRange of the end
bool AgentUtilField::isWallEndMove(const BlackBoardField& bb) {
    if (bb.m_flags.m_value & 0x10) {
        return false;
    }
    GfComPropertyPc& property = *bb.m_property;
    const WallAiParam* param = getAIParamAdapter(property, PARAM_ID_FIELD_AI(5)).get<WallAiParam>();
    return !StateUtilField::isNearPlayer(property, bb.m_wallEndPos, param->climbEndSafeRange);
}

// whether the PC may climb by input: not while another player is within the wall AI's nearRange of where the
// stick would take it along the wall
bool AgentUtilField::isEnableWallMove(GfComPropertyPc& property, const mm::Vec2& input) {
    float front = input.y * (input.y >= 0.0f ? property.m_field.m_climbUpTime : property.m_field.m_climbDownTime);
    float side = input.x * property.m_field.m_climbSideTime;
    mm::Vec3 pos = property.m_frontDir * front + property.m_sideDir * side + property.m_pos;
    const WallAiParam* param = getAIParamAdapter(property, PARAM_ID_FIELD_AI(5)).get<WallAiParam>();
    mm::Vec3 push;
    return !calcParentPlayerPush(property, pos, param->nearRange, &push);
}

// whether any player of the formation that is climbing (its target state 3) is within the wall AI's nearRange of pos
bool AgentUtilField::existNearChimbPlayer(GfComPropertyPc& property, const mm::Vec3& pos) {
    GfGamePlayerFormation* formation = GfGamePlayerFormation::get();
    const WallAiParam* param = getAIParamAdapter(property, PARAM_ID_FIELD_AI(5)).get<WallAiParam>();
    bool exist = false;
    for (int i = 0; i < 9; i++) {
        if (formation->m_players[i].m_standalone) {
            GfObjProperty* player = GfObjUtil::getProperty(formation->m_players[i].m_handle);
            if (player != nullptr && player->m_target->m_state == 3) {
                mm::Vec3 diff = player->m_target->pad_10 - pos;
                exist |= diff.length() - param->nearRange < 0.0f;
            }
        }
    }
    return exist;
}

// whether any player of the formation jumps off a wall (its field status bits 4 and 10)
bool AgentUtilField::isWallJumpAnyPlayer() {
    GfGamePlayerFormation* formation = GfGamePlayerFormation::get();
    bool jump = false;
    for (int i = 0; i < 9; i++) {
        if (formation->m_players[i].m_standalone) {
            GfObj* obj = GfObjUtil::getObj(formation->m_players[i].m_handle);
            if (obj != nullptr) {
                GfComPropertyPc* property = obj->findComponent<GfComPropertyPc>(5);
                if (property->m_field.m_statusFlags & 0x10) {
                    jump |= (property->m_field.m_statusFlags & 0x400) != 0;
                }
            }
        }
    }
    return jump;
}

// the state machine's S_uniqueA state carries a "look" annotation: 0 entering it, 1 leaving it
void registerAsmCallbackField(GF_OBJ_HANDLE* obj, anm::ResASM* res) {
    anm::AsmAnnotetion annotation;
    annotation.m_name = "look";
    annotation.m_type = 0;
    annotation.m_value = 0;
    res->setEnterAnnotation(1, "S_uniqueA", annotation);
    annotation.m_name = "look";
    annotation.m_type = 0;
    annotation.m_value = 1;
    res->setLeaveAnnotation(1, "S_uniqueA", annotation);
    res->sortAnnotation(1);
}

// the run speed's rate the owner bonuses give (within 1 to 1.5, less 1), less the field's slow-down in shallow water
float MoveUtilField::getSpeedEffect(GfComPropertyPc& property) {
    const OwnerBonus& bonus = GfGameManager::getOwnerBonus();
    float rate = bonus.m_speedRate + bonus.m_values[1] * 0.01f;
    if (rate < 1.0f) {
        rate = 1.0f;
    } else if (rate > 1.5f) {
        rate = 1.5f;
    }
    float effect = 0.0f;
    effect += rate - 1.0f;
    if (property.m_waterLevel == 2) {
        const GfPropertyField::MoveParam* param =
            property.m_field.m_paramList->getAdapter(0).get<GfPropertyField::MoveParam>();
        bool flagged = (property.m_stateFlags & 0x2000) != 0;
        const float& speedDown = flagged ? param->m_wadeSpeedDownFlagged : param->m_wadeSpeedDown;
        effect -= speedDown;
    }
    return effect;
}

void MoveUtilField::enterMoveRun(GfComPropertyPc& property, bool accelerate) {
    GfMoveRunControler controler;
    GfMoveRunControler::Packet packet;
    setMoveRunPacket(property, &packet);
    controler.enter(packet, accelerate);
    property.m_velocity = packet.m_velocity;
    property.m_moveVec2.y = packet.m_angularVelocity;
}

void MoveUtilField::updateMoveRun(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveRunControler controler;
    GfMoveRunControler::Packet packet;
    setMoveRunPacket(property, &packet);
    controler.update(info, packet);
    property.m_velocity = packet.m_velocity;
    property.m_moveVec2.y = packet.m_angularVelocity;
}

void MoveUtilField::updateBrake(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveBrakeControler controler;
    GfMoveBrakeControler::Packet packet;
    packet.m_velocity = property.m_velocity;
    packet.m_param = property.m_field.m_paramList->getAdapter(1);
    controler.update(info, packet);
    property.m_velocity = packet.m_velocity;
}

void MoveUtilField::updateMoveTurn(const fw::UpdateInfo& info, GfComPropertyPc& property, const mm::Vec3& target) {
    GfMoveTurnControler controler;
    GfMoveTurnControler::Packet packet;
    packet.m_angularSpeed = property.m_moveVec2.y;
    packet.m_param = property.m_field.m_paramList->getAdapter(4);
    packet.m_target = target;
    packet.m_direction = property.m_moveDir;
    controler.update(info, packet);
    property.m_moveVec2.y = packet.m_angularSpeed;
}

void MoveUtilField::updateMoveWalkTurn(const fw::UpdateInfo& info, GfComPropertyPc& property, const mm::Vec3& target) {
    GfMoveTurnControler controler;
    GfMoveTurnControler::Packet packet;
    packet.m_angularSpeed = property.m_moveVec2.y;
    packet.m_param = property.m_field.m_paramList->getAdapter(5);
    packet.m_target = target;
    packet.m_direction = property.m_moveDir;
    controler.update(info, packet);
    property.m_moveVec2.y = packet.m_angularSpeed;
}

// the stick's direction across the ground, the jump's facing without input, and its tilt
void setMoveJumpPacket(GfComPropertyPc& property, GfMoveJumpControler::Packet* packet) {
    packet->m_velocity = property.m_velocity;
    packet->m_angularVelocity = property.m_moveVec2.y;
    packet->m_param = property.m_field.m_paramList->getAdapter(6);
    packet->m_inputDirection =
        property.m_inputDir.y * property.m_groundFrontDir + property.m_inputDir.x * property.m_stickSideDir;
    if (!packet->m_inputDirection.isZero()) {
        float length = packet->m_inputDirection.length();
        float scale = 1.0f / length;
        packet->m_inputRate = mm::clamp(length, 0.0f, 1.0f);
        packet->m_inputDirection = scale * packet->m_inputDirection;
    } else {
        packet->m_inputRate = 0.0f;
        packet->m_inputDirection = property.m_moveDir;
    }
    packet->m_direction = property.m_moveDir;
}

void MoveUtilField::updateMoveJump(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveJumpControler controler;
    GfMoveJumpControler::Packet packet;
    setMoveJumpPacket(property, &packet);
    controler.update(info, packet);
    property.m_velocity = packet.m_velocity;
    property.m_moveVec2.y = packet.m_angularVelocity;
}

void MoveUtilField::updateMoveJumpBack(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveJumpBackControler controler;
    GfMoveJumpBackControler::Packet packet;
    packet.m_velocity = property.m_velocity;
    packet.m_param = property.m_field.m_paramList->getAdapter(7);
    mm::Vec3 input = property.m_inputDir.y * property.m_groundFrontDir + property.m_inputDir.x * property.m_stickSideDir;
    if (!input.isZero()) {
        packet.m_inputLength = mm::clamp(input.length(), 0.0f, 1.0f);
    } else {
        packet.m_inputLength = 0.0f;
    }
    packet.m_direction = property.m_moveDir;
    controler.update(info, packet);
    property.m_velocity = packet.m_velocity;
    property.m_moveVec2.y = 0.0f;
}

// the landing's brake: the speed kept along the facing, from the field's entry 3 by how far the stick points ahead,
// no more than the speed the PC has
void MoveUtilField::updateLandBrake(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    const GfPropertyField::LandBrakeParam* param = property.m_field.getParam<GfPropertyField::LandBrakeParam>(3);
    mm::Vec3 input = property.m_inputDir.y * property.m_groundFrontDir + property.m_inputDir.x * property.m_stickSideDir;
    float rate = input.dot(property.m_moveDir);
    rate = rate > 0.0f ? rate : 0.0f;
    float speed = param->m_minSpeed + (param->m_maxSpeed - param->m_minSpeed) * rate;
    float length = property.m_velocity.length();
    property.m_velocity = property.m_moveDir * (length > speed ? speed : length);
}

void MoveUtilField::updateFallDown(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveFallControler controler;
    GfMoveFallControler::Packet packet;
    packet.m_speed = property.m_moveVec2.x;
    packet.m_param = property.m_field.m_paramList->getAdapter(8);
    controler.update(info, packet);
    property.m_moveVec2.x = packet.m_speed;
}

void MoveUtilField::enterMoveSwim(GfComPropertyPc& property) {
    GfMoveRunControler controler;
    GfMoveRunControler::Packet packet;
    setMoveSwimPacket(property, &packet);
    controler.enter(packet, true);
    property.m_velocity = packet.m_velocity;
    property.m_moveVec2.y = packet.m_angularVelocity;
}

void MoveUtilField::updateMoveSwim(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveRunControler controler;
    GfMoveRunControler::Packet packet;
    setMoveSwimPacket(property, &packet);
    controler.update(info, packet);
    property.m_velocity = packet.m_velocity;
    property.m_moveVec2.y = packet.m_angularVelocity;
}

void MoveUtilField::updateMoveWaterTurn(const fw::UpdateInfo& info, GfComPropertyPc& property, const mm::Vec3& target) {
    GfMoveTurnControler controler;
    GfMoveTurnControler::Packet packet;
    packet.m_angularSpeed = property.m_moveVec2.y;
    packet.m_param = property.m_field.m_paramList->getAdapter(11);
    packet.m_target = target;
    packet.m_direction = property.m_moveDir;
    controler.update(info, packet);
    property.m_moveVec2.y = packet.m_angularSpeed;
}

void MoveUtilField::updateMoveWaterSink(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveWaterSinkControler controler;
    GfMoveWaterSinkControler::Packet packet;
    packet.m_speed = property.m_moveVec2.x;
    packet.m_param = property.m_field.m_paramList->getAdapter(12);
    controler.update(info, packet);
    property.m_moveVec2.x = packet.m_speed;
}

// rising through water: slowing once the child frame is near the surface (entry 13's rise parameters)
void MoveUtilField::updateMoveWaterRise(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveWaterRiseControler controler;
    GfMoveWaterRiseControler::Packet packet;
    packet.m_speed = property.m_moveVec2.x;
    packet.m_param = property.m_field.m_paramList->getAdapter(13);
    const GfPropertyField::WaterParam* water =
        property.m_field.m_paramList->getAdapter(9).get<GfPropertyField::WaterParam>();
    packet.m_decelerate = fabsf(StateUtilField::getChildFrameHeight(property)) <= water->m_riseSlowHeight;
    controler.update(info, packet);
    property.m_moveVec2.x = packet.m_speed;
}

// the same rise out of a water hole (entry 14's rise parameters)
void MoveUtilField::updateMoveWaterHoleRise(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    GfMoveWaterRiseControler controler;
    GfMoveWaterRiseControler::Packet packet;
    packet.m_speed = property.m_moveVec2.x;
    packet.m_param = property.m_field.m_paramList->getAdapter(14);
    const GfPropertyField::WaterParam* water =
        property.m_field.m_paramList->getAdapter(9).get<GfPropertyField::WaterParam>();
    packet.m_decelerate = fabsf(StateUtilField::getChildFrameHeight(property)) <= water->m_riseSlowHeight;
    controler.update(info, packet);
    property.m_moveVec2.x = packet.m_speed;
}

void MoveUtilField::updateMoveSlide(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    const SlideParam* param = property.getParamAdapter(4).get<SlideParam>();
    GfMoveSlideControler controler;
    GfMoveSlideControler::Packet packet;
    setMoveSlidePacket(property, *param, &packet);
    controler.update(info, packet);
    property.m_velocity = packet.m_velocity;
    property.m_moveVec2.y = packet.m_angularVelocity;
}

}}  // namespace gf::pc

namespace gf {

void GfComBehaviorPc::callbackField(GfComAsm* asmCom, const CallBackCache& cache) {}

}  // namespace gf

namespace gf { namespace pc {

PadField::PadField() : m_property(nullptr) {}

void PadField::setup(int padNo, GfComPropertyPc& property) {
    m_relay.bind(padNo, 0, getAllocator(ALLOCATOR(0)));
    m_relay.bindAction("decide", this, &PadField::decideAction);
    m_relay.bindAction("jump", this, &PadField::jumpAction);
    m_relay.bindAction("lock", this, &PadField::lockAction);
    m_relay.bindAction("wall_release", this, &PadField::wallReleaseAction);
    m_relay.bindAction("lure", this, &PadField::lureAction);
    m_relay.bindAxis("move_front", this, &PadField::moveFront);
    m_relay.bindAxis("move_side", this, &PadField::moveSide);
}

void PadField::decideAction() const {
    if (btl::Utility::IsBanOperateForField() || btl::BattleGlobal::sys()->IsPause(-1)) {
        return;
    }
    setInput(InputID(0));
}

void PadField::jumpAction() const {
    if (GfGameManager::isDisableJumpForRide()) {
        return;
    }
    if (btl::Utility::IsBanOperateForField() || btl::BattleGlobal::sys()->IsPause(-1)) {
        return;
    }
    setInput(InputID(2));
}

void PadField::lockAction() const {
    if (GfGameManager::isDisableAutoRun()) {
        return;
    }
    if (btl::Utility::IsBanOperateForField() || btl::BattleGlobal::sys()->IsPause(-1)) {
        return;
    }
    setInput(InputID(1));
}

void PadField::wallReleaseAction() const {
    if (btl::Utility::IsBanOperateForField() || btl::BattleGlobal::sys()->IsPause(-1)) {
        return;
    }
    setInput(InputID(3));
}

void PadField::lureAction() const {
    if (btl::Utility::IsBanOperateForField() || btl::BattleGlobal::sys()->IsPause(-1)) {
        return;
    }
    if (btl::ChallengeBattleManager::sys()->IsResult()) {
        return;
    }
    setInput(InputID(4));
}

void PadField::moveFront(float value) {
    if (m_property != nullptr && (m_property->m_stateFlags & 1)) {
        if (btl::Utility::IsBanOperateForField()) {
            m_property->m_inputDir.y = 0.0f;
        } else {
            m_property->m_inputDir.y = value;
        }
    }
}

void PadField::moveSide(float value) {
    if (m_property != nullptr && (m_property->m_stateFlags & 1)) {
        if (btl::Utility::IsBanOperateForField()) {
            m_property->m_inputDir.x = 0.0f;
        } else {
            m_property->m_inputDir.x = value;
        }
    }
}

void PadField::cleanup(GfComPropertyPc& property) {
    m_relay.unbind();
}

void PadField::update(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    m_property = &property;
    m_relay.update();
    m_property = nullptr;
}

void PadField::setInput(InputID id) const {
    if (m_property != nullptr) {
        m_property->m_inputFlags.set(id);
    }
}

}}  // namespace gf::pc
