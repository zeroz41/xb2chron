#include "classes/gf/pc/StateBattleBase.h"
#include "classes/gf/pc/StateBattleActionBase.h"
#include "classes/gf/pc/StateBattle.h"
#include "classes/gf/pc/StateBattleStart.h"
#include "classes/gf/pc/StateBattleIdle.h"
#include "classes/gf/pc/StateBattlePutOutWeapon.h"
#include "classes/gf/pc/StateBattlePutAwayWeapon.h"
#include "classes/gf/pc/StateBattleMove.h"
#include "classes/gf/pc/StateBattleKizunaMax.h"
#include "classes/gf/pc/StateBattleAttack.h"
#include "classes/gf/pc/StateBattleArts.h"
#include "classes/gf/pc/StateBattleIraSpArts.h"
#include "classes/gf/pc/StateBattleBladeArts.h"
#include "classes/gf/pc/StateBattleBladeChange.h"
#include "classes/gf/pc/StateBattleIraBladeChange.h"
#include "classes/gf/pc/StateBattleSpAttack.h"
#include "classes/gf/pc/StateBattleSupport.h"
#include "classes/gf/pc/StateBattleBladeGuard.h"
#include "classes/gf/pc/StateBattleRepelled.h"
#include "classes/gf/pc/StateBattleDown.h"
#include "classes/gf/pc/StateBattleKnockBack.h"
#include "classes/gf/pc/StateBattleBreak.h"
#include "classes/gf/pc/StateBattleDead.h"
#include "classes/gf/pc/StateBattleRescue.h"
#include "classes/gf/pc/StateBattleMindEye.h"
#include "classes/gf/pc/StateBattleOCG.h"
#include "classes/gf/pc/StateBattleHanaBusterReboot.h"
#include "classes/gf/pc/StateBattleFormationChange.h"
#include "gf/pc/AIAgentBattle.h"
#include "classes/gf/pc/PadBattle.h"
#include "classes/gf/pc/GfPropertyBattle.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/fw/NaviManager.h"
#include "ai/Hfsm.h"
#include "gf/pc/StateUtil.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfAllocator.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/CharacterManager.h"
#include "btl/challenge_battle_manager.h"
#include "gf/MsgPcBattleStart.h"
#include "mm/mtl/Delegate.h"
#include "classes/gf/npc/StateWalk.h"
#include "classes/gf/GfComBehaviorNpc.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/TFieldExecCmd.h"

namespace gf { namespace npc {

void StateWalk::enter(GfComBehaviorNpc* owner, ai::State* prev) {
    updateGoalPos(*owner);
    owner->execTurnCmdToGoal();
    m_seq = &StateWalk::seqWaitTurnEnd;
}

void StateWalk::seqWaitTurnEnd(GfComBehaviorNpc& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateWalk::seqUpdateMove;
    }
}

void StateWalk::update(GfComBehaviorNpc* owner, const fw::UpdateInfo& info) {
    updateGoalPos(*owner);
    if (owner->isStateCondMatch(static_cast<STATE_ID>(4))) {
        requestState(4);
        return;
    }
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

void StateWalk::leave(GfComBehaviorNpc* owner, ai::State* next) {}

}}  // namespace gf::npc

namespace gf { namespace pc {

const char* ASM_CB_NAME_BATTLE = "battle";

AIAgentBattle::AIAgentBattle() : m_naviObject(nullptr) {}

AIAgentBattle::~AIAgentBattle() {}

void AIAgentBattle::setup(GfComPropertyPc& property) {
    m_naviObject = fw::NaviManager::sys()->createObject();
}

void AIAgentBattle::cleanup(GfComPropertyPc& property) {
    fw::NaviManager* manager = fw::NaviManager::sys();
    navi::NvmshAcObj* object = m_naviObject;
    if (manager != nullptr && object != nullptr) {
        manager->releaseObject(object);
        m_naviObject = nullptr;
    }
}

void AIAgentBattle::update(const fw::UpdateInfo& info, GfComPropertyPc& property) {}

bool registerAsmCallbackBattle(GF_OBJ_HANDLE* obj, anm::ResASM* res) {
    return false;
}

}}  // namespace gf::pc

namespace gf {

void GfComBehaviorPc::callbackBattle(GfComAsm* asmCom, const CallBackCache& cache) {}

}  // namespace gf

namespace gf { namespace pc {

PadBattle::PadBattle() : m_property(nullptr) {}

void PadBattle::setup(int padNo, GfComPropertyPc& property) {
    m_relay0.bind(padNo, 1, getAllocator(ALLOCATOR(0)));
    m_relay0.bindAction("btl_start", this, &PadBattle::battleStart);
    m_relay0.bindAction("btl_end", this, &PadBattle::battleEnd);
    m_relay0.bindAction("art_01", this, &PadBattle::art01);
    m_relay0.bindAction("art_02", this, &PadBattle::art02);
    m_relay0.bindAction("art_03", this, &PadBattle::art03);
    m_relay0.bindAction("blade_change_00", this, &PadBattle::bladeChange00);
    m_relay0.bindAction("blade_change_01", this, &PadBattle::bladeChange01);
    m_relay0.bindAction("blade_change_02", this, &PadBattle::bladeChange02);
    m_relay0.bindAction("kakusei", this, &PadBattle::kakusei);
    m_relay0.bindAction("request_permit_01", this, &PadBattle::requestPermit01);
    m_relay0.bindAction("request_permit_02", this, &PadBattle::requestPermit02);
    m_relay0.bindAction("sp_attack", this, &PadBattle::spAttack);
    m_relay0.bindAction("chain_attack", this, &PadBattle::chainAttack);
    m_relay0.bindAction("battle_rescue", this, &PadBattle::battlRescue);
    m_relay0.bindAction("change_camera_mode", this, &PadBattle::changeCameraMode);
    m_relay0.bindAction("tactics", this, &PadBattle::orderRally);
    m_relay0.bindAction("auto_switch", this, &PadBattle::switchAuto);
    m_relay0.bindAction("mind_eye", this, &PadBattle::mindEye);
    m_relay0.bindAction("ira_formation_change", this, &PadBattle::iraFormationChange);
    m_relay0.bindAction("ira_formation_change2", this, &PadBattle::iraFormationChange);
    m_relay0.bindAction("ira_blade_change", this, &PadBattle::iraBladeChange);
    m_relay0.bindAction("ira_tactics_00", this, &PadBattle::iraTactics00);
    m_relay0.bindAction("ira_tactics_01", this, &PadBattle::iraTactics01);
    m_relay0.bindAction("ira_tactics_02", this, &PadBattle::iraTactics02);
    m_relay0.bindAction("ira_tactics_03", this, &PadBattle::iraTactics03);
    m_relay0.bindAction("ira_talent_arts", this, &PadBattle::iraTalentArts);
    m_relay0.bindAction("spskill", this, &PadBattle::ocg);
    m_relay0.bindAxis("move_front", this, &PadBattle::moveFront);
    m_relay0.bindAxis("move_side", this, &PadBattle::moveSide);
    m_relay1.bind(padNo, 3, getAllocator(ALLOCATOR(0)));
    m_relay1.bindAction("select_right", this, &PadBattle::changeTargetR);
    m_relay1.bindAction("select_left", this, &PadBattle::changeTargetL);
}

inline bool PadBattle::isInputEnable() const {
    if (m_property == nullptr) {
        return false;
    }
    if (btl::BattleGlobal::sys()->m_challengeAnySuccess && !btl::ChainAttackManager::sys()->IsProc(true) &&
        btl::BattleGlobal::sys()->m_controlHandle != static_cast<GfObj*>(m_property->m_owner)->m_handle) {
        return false;
    }
    return true;
}

inline void PadBattle::setInput(InputID id) const {
    m_property->m_inputFlags.change(id, true);
}

void PadBattle::battleStart() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(5));
}

void PadBattle::battleEnd() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(btl::BattleGlobal::sys()->pad_bit40 ? 6 : 9));
}

void PadBattle::art01() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(btl::BattleGlobal::sys()->pad_bit40 ? 13 : 7));
}

void PadBattle::art02() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(btl::BattleGlobal::sys()->pad_bit40 ? 22 : 8));
}

void PadBattle::art03() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(btl::BattleGlobal::sys()->pad_bit40 ? 6 : 9));
}

void PadBattle::bladeChange00() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(10));
}

void PadBattle::bladeChange01() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(11));
}

void PadBattle::bladeChange02() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(12));
}

void PadBattle::kakusei() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(btl::BattleGlobal::sys()->pad_bit40 ? 13 : 7));
}

void PadBattle::requestPermit01() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(14));
}

void PadBattle::requestPermit02() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(15));
}

void PadBattle::spAttack() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(btl::BattleGlobal::sys()->pad_bit40 ? 21 : 16));
}

void PadBattle::chainAttack() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(17));
}

void PadBattle::battlRescue() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(18));
}

void PadBattle::changeCameraMode() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(19));
}

void PadBattle::orderRally() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(20));
}

void PadBattle::switchAuto() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(23));
}

void PadBattle::mindEye() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(24));
}

void PadBattle::iraFormationChange() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(25));
}

void PadBattle::iraBladeChange() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(26));
}

void PadBattle::iraTactics00() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(27));
}

void PadBattle::iraTactics01() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(28));
}

void PadBattle::iraTactics02() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(29));
}

void PadBattle::iraTactics03() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(30));
}

void PadBattle::iraTalentArts() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(31));
}

void PadBattle::ocg() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(32));
}

void PadBattle::moveFront(float value) {
    if (m_property != nullptr && (m_property->m_stateFlags & 2)) {
        m_property->m_inputDir.y = value;
    }
}

void PadBattle::moveSide(float value) {
    if (m_property != nullptr && (m_property->m_stateFlags & 2)) {
        m_property->m_inputDir.x = value;
    }
}

void PadBattle::changeTargetR() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(btl::BattleGlobal::sys()->pad_bit40 ? 21 : 16));
}

void PadBattle::changeTargetL() const {
    if (btl::ChallengeBattleManager::sys()->IsExit()) {
        return;
    }
    if (!isInputEnable()) {
        return;
    }
    setInput(InputID(btl::BattleGlobal::sys()->pad_bit40 ? 22 : 8));
}

void PadBattle::cleanup(GfComPropertyPc& property) {
    m_relay0.unbind();
    m_relay1.unbind();
}

void PadBattle::update(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    m_property = &property;
    m_relay0.update();
    m_relay1.update();
    m_property = nullptr;
}

GfPropertyBattle::GfPropertyBattle() : m_registerId(-1), m_actionParam(0), pad_10(1.0f), m_startValue(0), pad_17(0), pad_18(0) {}

void GfPropertyBattle::setup(const GfComPropertyPc& property) {
    m_registerId = btl::CharacterManager::sys()->Register(static_cast<GfObj*>(property.m_owner)->m_handle, false);
}

void GfPropertyBattle::cleanup(const GfComPropertyPc& property) {
    if (m_registerId >= 0) {
        btl::CharacterManager::sys()->Release(m_registerId, static_cast<GfObj*>(property.m_owner)->m_handle);
        m_registerId = -1;
    }
}

void GfPropertyBattle::flush(const gf::GfComPropertyPc&) {}

void GfPropertyBattle::SetStartCondition(MsgPcBattleStart& msg) {
    m_startValue = msg.m_value;
    m_startParam0 = msg.m_param0;
    m_startParam1 = msg.m_param1;
}

}}  // namespace gf::pc
