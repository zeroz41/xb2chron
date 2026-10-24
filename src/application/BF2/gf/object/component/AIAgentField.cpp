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

namespace gf { namespace pc {

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

BlackBoardField::~BlackBoardField() {}

}}  // namespace gf::pc
