#include "gf/FileStaticVec3.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/Agent.h"
#include "gf/pc/StateUtil.h"
#include "classes/gf/pc/FallDamagePlugin.h"
#include "classes/gf/GfComAsm.h"
#include "gf/MsgPcFieldSetFallMaxHeight.h"
#include "fw/Allocator.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/ParamList.h"
#include <string.h>
#include "classes/fw/UpdatableObject.h"

namespace gf {

GfComBehaviorPc::GfComBehaviorPc() : m_agent(), m_hfsm(fw::Allocator::getProcAllocator()), m_headFrame(),
    pad_130(nullptr), m_listener(this) {}

GfComBehaviorPc::~GfComBehaviorPc() {}

void GfComBehaviorPc::callbackSound(const fw::ResSoundData& data, fw::SoundResSourceManager::CustomInfo* info) {
    GfComPropertyPc* property = m_owner->findComponent<GfComPropertyPc>(5);
    unsigned int kind = property->m_setupKind - 1;
    if (kind < 5 && isAttenuationPack(data.m_packName)) {
        info->m_volume =
            static_cast<const float*>(fw::ParamManager::get()->m_paramLists[18].get()->m_entries->m_data)[kind];
    }
}

void GfComBehaviorPc::resetHeadColPosition(const fw::Transform& transform) {
    GfComPropertyPc* property = m_owner->getComponent<GfComPropertyPc>(5);
    if (property->m_headColiHeight > 1.1920929e-07f) {
        mm::Vec3 pos;
        calcHeadColiPos(property->m_headColiHeight, transform, &pos);
        property->m_headColiPos = pos;
    }
}

void GfComBehaviorPc::integrateMove(const fw::UpdateInfo& info) {
    pc::StateUtil::reflectionAdsorption(*this);
    GfComPropertyPc* property = m_owner->getComponent<GfComPropertyPc>(5);
    if ((property->m_stateFlags & 0x10000) != 0) {
        return;
    }
    switch (property->m_wallJumpState) {
    case 0:
        integrateMoveNormal(info, *property);
        break;
    case 1:
        integrateMoveChildHeight(info, *property);
        break;
    case 2:
        integrateMoveWall(info, *property);
        break;
    }
}

void GfComBehaviorPc::procMsgPcFieldSetFallMaxHeight(fw::MessageObject* sender, MsgPcFieldSetFallMaxHeight& msg) {
    if (pc::FallDamagePlugin* plugin = getPlugin<pc::FallDamagePlugin>(7)) {
        plugin->setActivate(true);
        plugin->procMsgPcFieldSetFallMaxHeight(sender, msg);
    }
}

void GfComBehaviorPc::procMsgPcFieldReqFallDeadMotion(fw::MessageObject*, MsgPcFieldReqFallDeadMotion&) {
    GfComPropertyPc* property = m_owner->getComponent<GfComPropertyPc>(5);  // looked up, not used
    GfComAsm* comAsm = m_owner->getComponent<GfComAsm>(2);
    if (strcmp(comAsm->getStateName(AnimLayer(0)), "S_fall") != 0) {
        comAsm->setState("S_fall", AnimLayer(0));
    }
    comAsm->execCmd("C_falldead", AnimLayer(0));
}

bool isAttenuationPack(const char* packName) {
    return strcmp(packName, "se_mov_pc_default") == 0 || strcmp(packName, "se_fld_move_nopon") == 0 ||
           strcmp(packName, "se_fld_move_large") == 0 || strcmp(packName, "se_fld_move_hana") == 0 ||
           strcmp(packName, "se_fld_move_beast") == 0 || strcmp(packName, "se_fld_move_float") == 0 ||
           strcmp(packName, "se_fld_allmap") == 0;
}

void GfComBehaviorPc::setEnableAgentField(bool enable) {
    GfComPropertyPc* property = m_owner->getComponent<GfComPropertyPc>(5);
    if (m_agent && property != nullptr) {
        m_agent->setFieldAI(*property, enable);
    }
}

void GfComBehaviorPc::setEnableAgentBattle(bool enable) {
    GfComPropertyPc* property = m_owner->getComponent<GfComPropertyPc>(5);
    if (m_agent && property != nullptr) {
        m_agent->setBattleAI(*property, enable);
    }
}

mm::mtl::RTTI GfComBehaviorPc::m_rtti("GfComBehaviorPc", &GfComBehavior::m_rtti, nullptr);

}  // namespace gf
