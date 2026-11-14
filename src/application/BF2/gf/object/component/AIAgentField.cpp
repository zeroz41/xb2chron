#include "mm/mtl/IntrusivePtr.h"
#include "mm/Plane.h"
#include "ai/BehaviorTree.h"
#include "gf/pc/AIAgentField.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "classes/ai/ParallelNode.h"
#include "classes/ai/SelectorNode.h"
#include "classes/ai/SequenceNode.h"
#include "classes/gf/pc/TaskFieldSensor.h"
#include "classes/gf/pc/TaskFieldCheckWarp.h"
#include "classes/gf/pc/TaskFieldCheckWarpBattleWaterDead.h"
#include "classes/gf/pc/TaskFieldJump.h"
#include "classes/gf/pc/TaskFieldFollowTarget.h"
#include "classes/gf/pc/TaskFieldFollowMainPc.h"
#include "classes/gf/pc/TaskFieldWallFall.h"
#include "classes/gf/pc/TaskFieldWallJumpWait.h"
#include "classes/gf/pc/TaskFieldWallPrepare.h"
#include "classes/gf/pc/TaskFieldWallEscape.h"
#include "classes/gf/pc/TaskFieldWallFollow.h"
#include "classes/gf/pc/TaskFieldFollowBuddyPc.h"
#include "classes/gf/pc/TaskFieldRetreat.h"
#include "classes/gf/pc/TaskFieldIdleTurn.h"
#include "classes/gf/pc/TaskFieldIdle.h"
#include "classes/fw/NaviManager.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/ParamList.h"
#include "fw/Allocator.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/StateBattleBase.h"
#include "classes/gf/pc/StateBattleActionBase.h"
#include "classes/gf/pc/StateBattleBladeArts.h"
#include "classes/gf/pc/StateBattleBladeChange.h"
#include "classes/gf/pc/StateBattleHanaBusterReboot.h"
#include "classes/gf/pc/StateBattleBladeGuard.h"
#include "classes/gf/pc/StateBattleBreak.h"
#include "classes/gf/pc/StateBattleDead.h"
#include "classes/gf/pc/StateBattleDown.h"
#include "classes/gf/pc/StateBattleIdle.h"
#include "classes/gf/pc/StateBattleFormationChange.h"
#include "classes/gf/pc/StateBattleIraSpArts.h"
#include "classes/gf/pc/StateBattleIraBladeChange.h"
#include "classes/gf/pc/StateBattleKizunaMax.h"
#include "classes/gf/pc/StateBattleKnockBack.h"
#include "classes/gf/pc/StateBattleMindEye.h"
#include "classes/gf/pc/StateBattleOCG.h"
#include "classes/gf/pc/StateBattleMove.h"
#include "classes/gf/pc/StateBattlePutAwayWeapon.h"
#include "classes/gf/pc/StateBattlePutOutWeapon.h"
#include "classes/gf/pc/StateBattleRepelled.h"
#include "classes/gf/pc/StateBattleRescue.h"
#include "classes/gf/pc/StateBattleSpAttack.h"
#include "classes/gf/pc/StateBattleStart.h"
#include "classes/gf/pc/StateBattleSupport.h"
#include "classes/btl/BattleCharacter.h"
#include "btl/Utility.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "gf/MsgObjectNotifyDead.h"
#include "gf/pc/StateUtil.h"
#include "gf/pc/StateUtilBattle.h"
#include "classes/navi/NvmshAcObj.h"
#include "gf/MsgPcFieldNotifyHighJump.h"
#include "gf/MsgPcFieldNotifyBigJump.h"
#include "gf/MsgPcFieldNotifyWaterWarp.h"
#include "gf/MsgPcFieldNotifyWaterWarpBuddy.h"
#include "gf/MsgPcFieldNotifyWarp.h"
#include "gf/pc/AgentUtilField.h"
#include "fw/Transform.h"
#include "mm/Quat.h"
#include "ml/MTRand.h"
#include "math.h"

namespace gf { namespace pc {

namespace {
// a battle state and the battle character's action it runs (the names are not the original's)
struct StateAction {
    STATE_ID m_state;
    btl::BattleCharacter::ACTION_ID m_action;
};
}  // namespace

// lbl_71009C5904 (the name is not the original's): the battle states 0x3F..0x57, by action
static const StateAction s_stateActions[25] = {
    {STATE_ID(0x3F), btl::BattleCharacter::ACTION_ID(0)},
    {STATE_ID(0x40), btl::BattleCharacter::ACTION_ID(1)},
    {STATE_ID(0x41), btl::BattleCharacter::ACTION_ID(2)},
    {STATE_ID(0x42), btl::BattleCharacter::ACTION_ID(3)},
    {STATE_ID(0x43), btl::BattleCharacter::ACTION_ID(4)},
    {STATE_ID(0x44), btl::BattleCharacter::ACTION_ID(5)},
    {STATE_ID(0x45), btl::BattleCharacter::ACTION_ID(6)},
    {STATE_ID(0x46), btl::BattleCharacter::ACTION_ID(7)},
    {STATE_ID(0x47), btl::BattleCharacter::ACTION_ID(8)},
    {STATE_ID(0x48), btl::BattleCharacter::ACTION_ID(9)},
    {STATE_ID(0x49), btl::BattleCharacter::ACTION_ID(10)},
    {STATE_ID(0x4A), btl::BattleCharacter::ACTION_ID(11)},
    {STATE_ID(0x4B), btl::BattleCharacter::ACTION_ID(12)},
    {STATE_ID(0x4C), btl::BattleCharacter::ACTION_ID(13)},
    {STATE_ID(0x4D), btl::BattleCharacter::ACTION_ID(14)},
    {STATE_ID(0x4E), btl::BattleCharacter::ACTION_ID(15)},
    {STATE_ID(0x4F), btl::BattleCharacter::ACTION_ID(16)},
    {STATE_ID(0x50), btl::BattleCharacter::ACTION_ID(17)},
    {STATE_ID(0x51), btl::BattleCharacter::ACTION_ID(18)},
    {STATE_ID(0x52), btl::BattleCharacter::ACTION_ID(19)},
    {STATE_ID(0x53), btl::BattleCharacter::ACTION_ID(20)},
    {STATE_ID(0x54), btl::BattleCharacter::ACTION_ID(21)},
    {STATE_ID(0x55), btl::BattleCharacter::ACTION_ID(22)},
    {STATE_ID(0x56), btl::BattleCharacter::ACTION_ID(23)},
    {STATE_ID(0x57), btl::BattleCharacter::ACTION_ID(24)},
};

bool StateUtilBattle::IsBattleState(STATE_ID state) {
    return state >= 0x3E && state < 0x58;
}

STATE_ID StateUtilBattle::ConversionActionToState(btl::BattleCharacter::ACTION_ID action) {
    return s_stateActions[action].m_state;
}

btl::BattleCharacter::ACTION_ID StateUtilBattle::ConversionStateToAction(STATE_ID state) {
    if (state < 0x3F) {
        return btl::BattleCharacter::ACTION_ID(0);
    }
    return s_stateActions[state - 0x3F].m_action;
}

AIAgentField::AIAgentField() : m_nvmshAcObj(nullptr) {}

AIAgentField::~AIAgentField() {}

void AIAgentField::setup(GfComPropertyPc& property) {
    m_nvmshAcObj = fw::NaviManager::sys()->createObject();
    m_paramList = fw::ParamManager::sys()->m_paramLists[16];
    mm::mtl::IAllocator* allocator = fw::Allocator::getProcAllocator();
    m_tree.beginSetup(20, allocator);
    m_tree.createBlackBoard<BlackBoardField>();
    m_tree.createComposite<ai::ParallelNode>(0, "root_sequence", 3);
    m_tree.createTask<TaskFieldSensor>(1, "sensor_task");
    m_tree.createComposite<ai::SelectorNode>(2, "check_warp_selector", 2);
    m_tree.createTask<TaskFieldCheckWarp>(3, "check_warp_task");
    m_tree.createTask<TaskFieldCheckWarpBattleWaterDead>(4, "check_warp_water_dead_task");
    m_tree.createComposite<ai::SelectorNode>(6, "move_selector", 6);
    m_tree.createTask<TaskFieldJump>(14, "jump_task");
    m_tree.createComposite<ai::SequenceNode>(15, "follow_sequence", 2);
    m_tree.createTask<TaskFieldFollowTarget>(16, "follow_target_task");
    // the main PC climbs walls; a buddy retreats instead
    GfGamePlayerFormation* formation = GfGamePlayerFormation::sys();
    if (formation->m_players[property.m_setupKind].m_standalone) {
        m_tree.createTask<TaskFieldFollowMainPc>(17, "follow_task");
        m_tree.createComposite<ai::SelectorNode>(7, "wall_selector", 5);
        m_tree.createTask<TaskFieldWallFall>(8, "fall_wall_task");
        m_tree.createTask<TaskFieldWallJumpWait>(9, "wall_jump_wait_task");
        m_tree.createTask<TaskFieldWallPrepare>(10, "prepare_wall_task");
        m_tree.createTask<TaskFieldWallEscape>(11, "escape_wall_task");
        m_tree.createTask<TaskFieldWallFollow>(12, "follow_wall_task");
        m_tree.createTask<TaskFieldIdleTurn>(18, "idle_turn_task");
        m_tree.createTask<TaskFieldIdle>(19, "idle_task");
        m_tree.endSetup();
        m_tree.attachRoot(0);
        m_tree.attachComposite(0, 1, 0);
        m_tree.attachComposite(0, 2, 1);
        m_tree.attachComposite(2, 3, 0);
        m_tree.attachComposite(2, 4, 1);
        m_tree.attachComposite(0, 6, 2);
        m_tree.attachComposite(6, 7, 0);
        m_tree.attachComposite(7, 8, 0);
        m_tree.attachComposite(7, 10, 1);
        m_tree.attachComposite(7, 9, 2);
        m_tree.attachComposite(7, 11, 3);
        m_tree.attachComposite(7, 12, 4);
    } else {
        m_tree.createTask<TaskFieldFollowBuddyPc>(17, "follow_task");
        m_tree.createTask<TaskFieldRetreat>(13, "retreat_task");
        m_tree.createTask<TaskFieldIdleTurn>(18, "idle_turn_task");
        m_tree.createTask<TaskFieldIdle>(19, "idle_task");
        m_tree.endSetup();
        m_tree.attachRoot(0);
        m_tree.attachComposite(0, 1, 0);
        m_tree.attachComposite(0, 2, 1);
        m_tree.attachComposite(2, 3, 0);
        m_tree.attachComposite(2, 4, 1);
        m_tree.attachComposite(0, 6, 2);
        m_tree.attachComposite(6, 13, 2);
    }
    m_tree.attachComposite(6, 14, 1);
    m_tree.attachComposite(6, 15, 3);
    m_tree.attachComposite(15, 16, 0);
    m_tree.attachComposite(15, 17, 1);
    m_tree.attachComposite(6, 18, 4);
    m_tree.attachComposite(6, 19, 5);
}

void AIAgentField::cleanup(GfComPropertyPc& property) {
    m_tree.cleanup();
    fw::NaviManager* navi = fw::NaviManager::get();
    navi::NvmshAcObj* object = m_nvmshAcObj;
    if (navi != nullptr && object != nullptr) {
        navi->releaseObject(object);
        m_nvmshAcObj = nullptr;
    }
}

void AIAgentField::onActivate(GfComPropertyPc& property) {
    if (m_nvmshAcObj != nullptr) {
        m_nvmshAcObj->m_flags |= 2;
    }
}

void AIAgentField::onDeactivate(GfComPropertyPc& property) {
    if (m_nvmshAcObj != nullptr) {
        m_nvmshAcObj->m_flags &= ~2;
    }
}

void AIAgentField::procMsgPcFieldHighJump(fw::MessageObject* sender, MsgPcFieldNotifyHighJump& msg) {
    BlackBoardField* bb = m_tree.getBlackBoard<BlackBoardField>();
    GfComPropertyPc* property = bb->m_property;
    if (property->m_field.m_statusFlags & 4) {
        const MsgPcFieldNotifyBigJump* jump = msg.m_jump;
        fw::Transform transform;
        transform.position = jump->m_pos;
        float half = jump->m_param0 * 0.5f;
        transform.rotation.y = sinf(half);
        transform.rotation.w = cosf(half);
        transform.rotation.x = 0.0f;
        transform.rotation.z = 0.0f;
        GfGamePlayerFormation* formation = GfGamePlayerFormation::sys();
        MsgPcFieldNotifyBigJump notice;
        notice = *jump;
        formation->calcTargetTransform(transform, property->m_setupKind, &notice.m_pos);
        property->m_field.setBigJumpInfo(&notice);
        const ForceWarpAiParam* param = m_paramList->getAdapter(6).get<ForceWarpAiParam>();
        bb->m_flags |= 0x40;
        bb->m_noticeTimer = param->baseWaitTime + ml::mtRandf1() * param->waitTimeRange;
    }
}

void AIAgentField::procMsgPcFieldNotifyWaterWarp(fw::MessageObject* sender, MsgPcFieldNotifyWaterWarp& msg) {
    BlackBoardField* bb = m_tree.getBlackBoard<BlackBoardField>();
    GfComPropertyPc* property = bb->m_property;
    GfPropertyField& field = property->m_field;
    if (property->m_stateFlags & 0x20) {
        const MsgPcFieldNotifyWarp* warp = msg.m_warp;
        fw::Transform transform;
        transform.position = warp->m_pos;
        float half = warp->m_param * 0.5f;
        transform.rotation.y = sinf(half);
        transform.rotation.w = cosf(half);
        transform.rotation.x = 0.0f;
        transform.rotation.z = 0.0f;
        GfGamePlayerFormation* formation = GfGamePlayerFormation::sys();
        MsgPcFieldNotifyWarp notice;
        notice = *warp;
        formation->calcTargetTransform(transform, property->m_setupKind, &notice.m_pos);
        field.setWarpInfo(&notice);
        const ForceWarpAiParam* param = m_paramList->getAdapter(7).get<ForceWarpAiParam>();
        bb->m_flags |= 0x80;
        bb->m_noticeTimer = param->baseWaitTime + ml::mtRandf1() * param->waitTimeRange;
    }
}

void AIAgentField::procMsgPcFieldNotifyWaterWarpBuddy(fw::MessageObject* sender, MsgPcFieldNotifyWaterWarpBuddy& msg) {
    BlackBoardField* bb = m_tree.getBlackBoard<BlackBoardField>();
    GfComPropertyPc* property = bb->m_property;
    GfPropertyField& field = property->m_field;
    if (property->m_stateFlags & 0x20) {
        const MsgPcFieldNotifyWarp* warp = msg.m_warp;
        fw::Transform transform;
        transform.position = warp->m_pos;
        float half = warp->m_param * 0.5f;
        transform.rotation.y = sinf(half);
        transform.rotation.w = cosf(half);
        transform.rotation.x = 0.0f;
        transform.rotation.z = 0.0f;
        GfGamePlayerFormation* formation = GfGamePlayerFormation::sys();
        MsgPcFieldNotifyWarp notice;
        notice = *warp;
        formation->calcTargetTransform(transform, property->m_setupKind, &notice.m_pos);
        field.setWarpInfo(&notice);
        const ForceWarpAiParam* param = m_paramList->getAdapter(7).get<ForceWarpAiParam>();
        bb->m_flags |= 0x200;
        bb->m_noticeTimer = param->baseWaitTime + ml::mtRandf1() * param->waitTimeRange;
    }
}

mm::mtl::RTTI BlackBoardField::m_rtti("BlackBoardField", &::ai::BlackBoard::m_rtti, nullptr);

BlackBoardField::BlackBoardField()
    : m_property(nullptr), m_nvmshAcObj(nullptr), m_updateInfo(nullptr), m_targetPos(mm::Vec3::zero),
      m_targetDist(0.0f), m_followPos(mm::Vec3::zero), m_followDist(0.0f), m_wallPos(mm::Vec3::zero),
      m_wallPlane(mm::Vec3::unitY, 0.0f), m_wallEndPos(mm::Vec3::zero), m_retreatPos(mm::Vec3::zero), m_flags(),
      m_noticeTimer(0.0f) {}

BlackBoardField::~BlackBoardField() {}

}}  // namespace gf::pc
