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

namespace gf { namespace pc {

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

void GfPropertyBattle::flush(const gf::GfComPropertyPc&) {}

}}  // namespace gf::pc
