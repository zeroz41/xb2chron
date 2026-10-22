#include "gf/FileStaticVec3.h"
#include "gf/EnviromentSensor.h"
#include "gf/GfTargetProperty.h"
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

// update (0x71004EEF28) is not matched yet. Written with a local fw::Transform for the warp (its rotation, then the
// formation position), the distance as mm::Vec3(diff.x, 0, diff.z).length() and the warp stores inside
// `if (stuck long enough || too far vertically || too far horizontally)`, and on a wall
// `if (vertical) {pos; type} else if (horizontal) {type; pos} else return;`, the wall branch is identical; the
// first branch differs by register allocation only: the original computes the address of the warp transform's
// rotation slice (SROA's [12, 32) partition, 4 bytes into the stack slot) before the getFollowTransform call and keeps
// it in x23, ours computes it in the store block

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

// update (0x71004EF2F0) is not matched yet: written as nested ifs (isBattle, the parameter, the time; the followed
// player's object; its property's state flag bit 1 and water level 0) with an fw::Transform holding the follow
// transform's rotation, a VerticalPacket (type 3, down along -unitY, reach -p[0] to p[1]) and a VerticalData on the
// stack, it differs only where the followed player's property is read: the original keeps the component slot's
// null path (cbz, then a load through null) and tests the flag (ldrb, tbz) and the water level in separate blocks;
// ours drops the null path and merges both tests into one 64-bit load

mm::mtl::RTTI TaskFieldCheckWarp::m_rtti("TaskFieldCheckWarp", &ai::TaskNode::m_rtti, nullptr);
mm::mtl::RTTI TaskFieldCheckWarpBattleWaterDead::m_rtti("TaskFieldCheckWarpBattleWaterDead", &ai::TaskNode::m_rtti, nullptr);
mm::mtl::RTTI TaskFieldCheckWarpFallDead::m_rtti("TaskFieldCheckWarpFallDead", &ai::TaskNode::m_rtti, nullptr);

}}  // namespace gf::pc
