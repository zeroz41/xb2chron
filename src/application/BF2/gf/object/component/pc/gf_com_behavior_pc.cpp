#include "gf/PluginManager.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "gf/FileStaticVec3.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/pc/StateBattle.h"
#include "classes/gf/pc/AccessPlugin.h"
#include "classes/gf/pc/FallIntoColiPlugin.h"
#include "classes/gf/pc/FadePlugin.h"
#include "classes/gf/pc/LurePlugin.h"
#include "classes/gf/pc/LookAtPlugin.h"
#include "classes/gf/pc/TargetIKPlugin.h"
#include "classes/gf/pc/FallDamagePlugin.h"
#include "classes/gf/pc/TimerPlugin.h"
#include "classes/gf/pc/SlidePlugin.h"
#include "classes/gf/pc/AttachPlugin.h"
#include "classes/gf/pc/ColVelCalculatorPlugin.h"
#include "classes/gf/pc/TerrainDamagePlugin.h"
#include "classes/gf/pc/FallDistancePlugin.h"
#include "classes/gf/pc/WaterInPlugin.h"
#include "classes/gf/pc/DeadColCheckPlugin.h"
#include "classes/gf/pc/LookAxisPlugin.h"
#include "classes/gf/pc/FallDistanceAchievPlugin.h"
#include "classes/gf/pc/PadField.h"
#include "classes/gf/GfComSound.h"
#include "classes/gf/GfComEffectCaster.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/Agent.h"
#include "gf/pc/StateUtil.h"
#include "classes/gf/pc/FallDamagePlugin.h"
#include "classes/gf/GfComAsm.h"
#include "gf/MsgPcFieldSetFallMaxHeight.h"
#include "gf/MsgPcFieldChangeControlModeForIra.h"
#include "fw/Allocator.h"
#include "gf/MsgObjectNotifyDead.h"
#include "gf/MsgObjectDamage.h"
#include "gf/pc/StateUtilField.h"
#include "gf/GfObjUtil.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfGameManager.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/DataManager.h"
#include "btl/Utility.h"
#include "classes/gf/GfGameRide.h"
#include "classes/gf/pc/GfPropertyBattle.h"
#include "gf/MsgPcBattleStart.h"
#include "gf/MsgUnk_1000046.h"
#include "gf/MsgUnk_100004B.h"
#include "classes/gf/GfComEnvSensor.h"
#include "classes/gf/GfComDynamics.h"
#include "classes/gf/SCOM_OBJ_ALPHA.h"
#include "gf/pc/AgentUtilField.h"
#include "gf/MsgGameChangeTarget.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/ParamList.h"
#include <string.h>
#include "stdlib.h"
#include <stdlib.h>
#include "classes/gf/GfStateBase.h"
#include "gf/MsgObjectNotifyAsmCallback.h"
#include "gf/CallBackCache.h"
#include "anm/AsmAnnotetion.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/pc/PadField.h"
#include "classes/gf/pc/PadBattle.h"
#include "classes/gf/pc/AIAgent.h"
#include "classes/gf/pc/PadAgent.h"
#include "classes/gf/pc/StateField.h"
#include "classes/gf/pc/StateBattle.h"
#include "classes/gf/GfComSound.h"
#include "classes/gf/GfComEffectCaster.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/FootStepPlugin.h"
#include "classes/gf/EyeBlinkPlugin.h"
#include "classes/gf/LipSyncPlugin.h"
#include "classes/gf/FootIkControllerPlugin.h"
#include "classes/gf/pc/AccessPlugin.h"
#include "classes/gf/pc/FallIntoColiPlugin.h"
#include "classes/gf/pc/FadePlugin.h"
#include "classes/gf/pc/LurePlugin.h"
#include "classes/gf/pc/LookAtPlugin.h"
#include "classes/gf/pc/TargetIKPlugin.h"
#include "classes/gf/pc/TimerPlugin.h"
#include "classes/gf/pc/SlidePlugin.h"
#include "classes/gf/pc/AttachPlugin.h"
#include "classes/gf/pc/ColVelCalculatorPlugin.h"
#include "classes/gf/pc/TerrainDamagePlugin.h"
#include "classes/gf/pc/FallDistancePlugin.h"
#include "classes/gf/pc/WaterInPlugin.h"
#include "classes/gf/pc/DeadColCheckPlugin.h"
#include "classes/gf/pc/LookAxisPlugin.h"
#include "classes/gf/pc/FallDistanceAchievPlugin.h"

namespace gf {

GfComBehaviorPc::GfComBehaviorPc() : m_agent(), m_hfsm(fw::Allocator::getProcAllocator()), m_headFrame(),
    pad_130(nullptr), m_listener(this) {}

GfComBehaviorPc::~GfComBehaviorPc() {}

void GfComBehaviorPc::setup(const SetupInfo& info) {
    static_cast<GfObj*>(m_owner)->pad_110 |= 2;  // GfGameTarget targets it (bit 2)
    if (GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2)) {
        asmCom->m_callbacks[0].name = "system";
        asmCom->m_callbacks[0].delegate.set(static_cast<GfComBehavior*>(this), &GfComBehavior::callbackAnim);
        asmCom->m_callbacks[1].name = pc::ASM_CB_NAME_FIELD;
        asmCom->m_callbacks[1].delegate.set(this, &GfComBehaviorPc::callbackField);
        asmCom->m_callbacks[2].name = pc::ASM_CB_NAME_BATTLE;
        asmCom->m_callbacks[2].delegate.set(this, &GfComBehaviorPc::callbackBattle);
    }
    if (GfComSound* sound = m_owner->getComponent<GfComSound>(10)) {
        sound->m_customInfoCallback.set(this, &GfComBehaviorPc::callbackSound);
    }
    GfComPropertyPc* property = m_owner->getComponent<GfComPropertyPc>(5);
    bool pad = (property->m_stateFlags & 0x400) != 0;
    if (pad) {
        m_agent.reset(new (getAllocator(ALLOCATOR(0)), __FILE__, 160, 8) pc::PadAgent(0));
    } else {
        m_agent.reset(new (getAllocator(ALLOCATOR(0)), __FILE__, 165, 8) pc::AIAgent);
    }
    m_agent->setup(*property);
    GfGamePlayerFormation* formation = GfGamePlayerFormation::sys();
    bool standalone = formation != nullptr && property->m_setupKind != 0xFFFFFFFF
                          ? formation->m_players[property->m_setupKind].m_standalone
                          : false;
    m_pluginManager.beginSetup(*this, 22);
    m_pluginManager.setCreator(FootStepPlugin::PLUGIN_ID, &FootStepPlugin::create, true);
    m_pluginManager.setCreator(1, &EyeBlinkPlugin::create, info.m_eyeBlink);
    m_pluginManager.setCreator(2, &LipSyncPlugin::create, true);
    m_pluginManager.setCreator(FootIkControllerPlugin::PLUGIN_ID, &FootIkControllerPlugin::create, true);
    m_pluginManager.setCreator(pc::AccessPlugin::PLUGIN_ID, &pc::AccessPlugin::create, pad);
    m_pluginManager.setCreator(pc::FallIntoColiPlugin::PLUGIN_ID, &pc::FallIntoColiPlugin::create, pad);
    m_pluginManager.setCreator(pc::FadePlugin::PLUGIN_ID, &pc::FadePlugin::create, pad);
    m_pluginManager.setCreator(pc::LurePlugin::PLUGIN_ID, &pc::LurePlugin::create, pad);
    m_pluginManager.setCreator(pc::LookAtPlugin::PLUGIN_ID, &pc::LookAtPlugin::create, true);
    m_pluginManager.setCreator(pc::TargetIKPlugin::PLUGIN_ID, &pc::TargetIKPlugin::create, true);
    m_pluginManager.setCreator(pc::FallDamagePlugin::PLUGIN_ID, &pc::FallDamagePlugin::create, standalone);
    m_pluginManager.setCreator(pc::TimerPlugin::PLUGIN_ID, &pc::TimerPlugin::create, true);
    m_pluginManager.setCreator(pc::SlidePlugin::PLUGIN_ID, &pc::SlidePlugin::create, true);
    m_pluginManager.setCreator(pc::AttachPlugin::PLUGIN_ID, &pc::AttachPlugin::create, true);
    m_pluginManager.setCreator(pc::ColVelCalculatorPlugin::PLUGIN_ID, &pc::ColVelCalculatorPlugin::create, true);
    m_pluginManager.setCreator(pc::TerrainDamagePlugin::PLUGIN_ID, &pc::TerrainDamagePlugin::create, standalone);
    m_pluginManager.setCreator(pc::FallDistancePlugin::PLUGIN_ID, &pc::FallDistancePlugin::create, true);
    m_pluginManager.setCreator(pc::WaterInPlugin::PLUGIN_ID, &pc::WaterInPlugin::create, true);
    m_pluginManager.setCreator(pc::DeadColCheckPlugin::PLUGIN_ID, &pc::DeadColCheckPlugin::create, standalone);
    m_pluginManager.setCreator(pc::LookAxisPlugin::PLUGIN_ID, &pc::LookAxisPlugin::create, true);
    m_pluginManager.setCreator(pc::FallDistanceAchievPlugin::PLUGIN_ID, &pc::FallDistanceAchievPlugin::create,
                               standalone);
    m_pluginManager.endSetup();
    if (Plugin* plugin = m_pluginManager.m_plugins[pc::ColVelCalculatorPlugin::PLUGIN_ID]) {
        plugin->setActivate(true);
    }
    if (Plugin* plugin = m_pluginManager.m_plugins[pc::TerrainDamagePlugin::PLUGIN_ID]) {
        plugin->setActivate(true);
    }
    if (Plugin* plugin = m_pluginManager.m_plugins[2]) {
        plugin->setActivate(true);
    }
    if (Plugin* plugin = m_pluginManager.m_plugins[FootIkControllerPlugin::PLUGIN_ID]) {
        plugin->setActivate(true);
    }
    if (Plugin* plugin = m_pluginManager.m_plugins[pc::DeadColCheckPlugin::PLUGIN_ID]) {
        plugin->setActivate(true);
    }
    if (Plugin* plugin = m_pluginManager.m_plugins[pc::LookAxisPlugin::PLUGIN_ID]) {
        plugin->setActivate(true);
    }
    m_hfsm.beginSetup(this, 88, 8);
    pc::registerFieldStates(m_hfsm);
    pc::registerBattleStates(m_hfsm);
    m_hfsm.endSetup();
    m_hfsm.setState(info.m_state);
    GfComModel* model = m_owner->getComponent<GfComModel>(1);
    m_headFrame = model->createBoneReferenceFrame("JU_neck");
    if (m_headFrame.get() == nullptr) {
        m_headFrame = model->createBoneReferenceFrame("JU_spA");
        if (m_headFrame.get() == nullptr) {
            m_headFrame = m_owner->getComponent<GfComTransform>(0)->getFrame();
        }
    }
    if (GfComEffectCaster* caster = m_owner->getComponent<GfComEffectCaster>(7)) {
        caster->m_chestHeight = property->m_chestHeight;
    }
}

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

void GfComBehaviorPc::onWarpNormal(GfComPropertyPc& property) {
    GfComTransform* transform = m_owner->findComponent<GfComTransform>(0);
    const fw::Transform& world = transform->m_frame->getWorldTransform();
    m_owner->getComponent<GfComEnvSensor>(11)->flushEnv(world);
    property.flush();
    GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2);
    if (!((property.m_field.m_statusFlags & 0x8000) != 0 && (property.m_stateFlags & 0x800) == 0)) {
        if (property.m_waterLevel == 3) {
            if (asmCom && asmCom->setState("S_wateridle", AnimLayer(0))) {
                m_hfsm.setState(0x14);
                if (GfGameRide::isVehicle(static_cast<GfObj*>(m_owner)->m_handle)) {
                    pc::StateUtilField::notifyRiderEvent(*this, pc::VehicleEvent(2));
                }
            }
        } else {
            if (asmCom && asmCom->setState("S_idle", AnimLayer(0))) {
                m_hfsm.setState(3);
                if (GfGameRide::isVehicle(static_cast<GfObj*>(m_owner)->m_handle)) {
                    pc::StateUtilField::notifyRiderEvent(*this, pc::VehicleEvent(2));
                }
            }
        }
    } else {
        if (GfGameManager::isBattle()) {
            MsgPcBattleStart msg(2);
            property.m_battle.SetStartCondition(msg);
            m_hfsm.setState(0x3F);
        }
    }
    property.m_velocity = mm::Vec3::zero;
    property.m_moveVec2.x = 0.0f;
    property.m_moveVec2.y = 0.0f;
    property.m_moveSpeed = 0.0f;
    property.m_stateFlags = (property.m_stateFlags & ~0x80) | 0x10;
    if (GfComDynamics* dynamics = m_owner->getComponent<GfComDynamics>(8)) {
        dynamics->resetMovement();
    }
    if (pc::FallDamagePlugin* plugin = getPlugin<pc::FallDamagePlugin>(pc::FallDamagePlugin::PLUGIN_ID)) {
        plugin->cacheMaxHeight(true);
    }
    if (pc::FallDistancePlugin* plugin = getPlugin<pc::FallDistancePlugin>(pc::FallDistancePlugin::PLUGIN_ID)) {
        plugin->cacheMaxHeight(true);
    }
    const pc::WarpParam* param = property.m_paramList->getAdapter(2).get<pc::WarpParam>();
    SCOM_OBJ_ALPHA::create(static_cast<GfObj*>(m_owner)->m_handle, 0.0f, 0.0f);
    SCOM_OBJ_ALPHA::create(static_cast<GfObj*>(m_owner)->m_handle, param->fadeTime, 1.0f);
    if (GfObj* obj = GfObjUtil::getObj(static_cast<GfObj*>(m_owner)->m_handle)) {
        MsgUnk_1000046 msg(false);
        static_cast<GfObj*>(m_owner)->sendMessage(obj, msg);
    }
    if (GfObj* obj = GfObjUtil::getObj(static_cast<GfObj*>(m_owner)->m_handle)) {
        MsgUnk_100004B msg;
        static_cast<GfObj*>(m_owner)->sendMessage(obj, msg);
    }
}

void GfComBehaviorPc::onWarpWall(GfComPropertyPc& property) {
    GfComTransform* transform = m_owner->findComponent<GfComTransform>(0);
    const fw::Transform& world = transform->m_frame->getWorldTransform();
    m_owner->getComponent<GfComEnvSensor>(11)->flushEnv(world);
    property.flush();
    if (GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2)) {
        if (asmCom->setState("S_climbidle_base", AnimLayer(0))) {
            m_hfsm.setState(0x2E);
        }
    }
    if (GfComDynamics* dynamics = m_owner->getComponent<GfComDynamics>(8)) {
        dynamics->resetMovement();
    }
    const pc::WarpParam* param = property.m_paramList->getAdapter(2).get<pc::WarpParam>();
    SCOM_OBJ_ALPHA::create(static_cast<GfObj*>(m_owner)->m_handle, 0.0f, 0.0f);
    SCOM_OBJ_ALPHA::create(static_cast<GfObj*>(m_owner)->m_handle, param->fadeTime, 1.0f);
}

void GfComBehaviorPc::onWarpBattle(GfComPropertyPc& property) {
    GfComTransform* transform = m_owner->findComponent<GfComTransform>(0);
    const fw::Transform& world = transform->m_frame->getWorldTransform();
    m_owner->getComponent<GfComEnvSensor>(11)->flushEnv(world);
    property.flush();
    property.m_moveSpeed = 0.0f;
    property.m_stateFlags &= ~0x80;
    if (GfComDynamics* dynamics = m_owner->getComponent<GfComDynamics>(8)) {
        dynamics->resetMovement();
    }
    if (pc::FallDamagePlugin* plugin = getPlugin<pc::FallDamagePlugin>(pc::FallDamagePlugin::PLUGIN_ID)) {
        plugin->cacheMaxHeight(true);
    }
    if (pc::FallDistancePlugin* plugin = getPlugin<pc::FallDistancePlugin>(pc::FallDistancePlugin::PLUGIN_ID)) {
        plugin->cacheMaxHeight(true);
    }
}

void GfComBehaviorPc::procMsgGameChangeTarget(fw::MessageObject* sender, MsgGameChangeTarget& msg) {
    pc::TargetIKPlugin* targetIK = getPlugin<pc::TargetIKPlugin>(pc::TargetIKPlugin::PLUGIN_ID);
    if (!targetIK) {
        return;
    }
    pc::LookAtPlugin* lookAt = getPlugin<pc::LookAtPlugin>(pc::LookAtPlugin::PLUGIN_ID);
    GfComPropertyPc* property = m_owner->getComponent<GfComPropertyPc>(5);
    if (msg.m_target == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        targetIK->setActivate(false);
        if (lookAt && (property->m_field.m_statusFlags & 2) != 0) {
            lookAt->setActivate(true);
        }
    } else {
        if (lookAt) {
            lookAt->setActivate(false);
        }
        if ((property->m_stateFlags & 0x100) != 0) {
            targetIK->setActivate(true);
        }
    }
    targetIK->procMsgGameChangeTarget(sender, msg);
}

void GfComBehaviorPc::procMsgPcFieldSetFallMaxHeight(fw::MessageObject* sender, MsgPcFieldSetFallMaxHeight& msg) {
    if (pc::FallDamagePlugin* plugin = getPlugin<pc::FallDamagePlugin>(7)) {
        plugin->setActivate(true);
        plugin->procMsgPcFieldSetFallMaxHeight(sender, msg);
    }
}

void GfComBehaviorPc::procMsgPcFieldChangeControlModeForIra(fw::MessageObject*,
                                                            MsgPcFieldChangeControlModeForIra& msg) {
    GfComPropertyPc* property = m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2);
    unsigned int flags = property->m_stateFlags;
    bool pad = (flags & 0x400) != 0;
    property->m_stateFlags = flags & ~0x4000000;
    if ((flags & 1) != 0) {
        m_hfsm.clearState();
    }
    if (!pad) {
        if (m_agent) {
            m_agent->cleanup(*property);
            m_agent.reset();
        }
    } else {
        if (m_agent) {
            m_agent->cleanup(*property);
            m_agent.reset();
        }
        m_pluginManager.destroyPlugin<pc::DeadColCheckPlugin>();
        m_pluginManager.destroyPlugin<pc::TerrainDamagePlugin>();
        m_pluginManager.destroyPlugin<pc::AccessPlugin>();
        m_pluginManager.destroyPlugin<pc::FallIntoColiPlugin>();
        m_pluginManager.destroyPlugin<pc::FallDamagePlugin>();
        m_pluginManager.destroyPlugin<pc::FadePlugin>();
        m_pluginManager.destroyPlugin<pc::LurePlugin>();
        m_pluginManager.destroyPlugin<pc::FallDistanceAchievPlugin>();
        property->setPadControl(false);
    }
    if (msg.m_mode == 0) {
        m_agent.reset(new (getAllocator(ALLOCATOR(0)), __FILE__, 2320, 8) pc::PadAgent(0));
        m_agent->setup(*property);
        property->setPadControl(true);
        m_pluginManager.createPlugin<pc::AccessPlugin>();
        m_pluginManager.createPlugin<pc::FallIntoColiPlugin>();
        m_pluginManager.createPlugin<pc::FallDamagePlugin>();
        m_pluginManager.createPlugin<pc::FadePlugin>();
        m_pluginManager.createPlugin<pc::LurePlugin>();
        m_pluginManager.createPlugin<pc::TerrainDamagePlugin>();
        m_pluginManager.createPlugin<pc::DeadColCheckPlugin>();
        m_pluginManager.createPlugin<pc::FallDistanceAchievPlugin>();
        if ((flags & 1) != 0) {
            m_hfsm.setState(3);
            asmCom->setState("S_idle", AnimLayer(0));
        }
        if (Plugin* plugin = m_pluginManager.m_plugins[pc::TerrainDamagePlugin::PLUGIN_ID]) {
            plugin->setActivate(true);
        }
        if (Plugin* plugin = m_pluginManager.m_plugins[pc::DeadColCheckPlugin::PLUGIN_ID]) {
            plugin->setActivate(true);
        }
    } else if (msg.m_mode == 1) {
        m_agent.reset(new (getAllocator(ALLOCATOR(0)), __FILE__, 2357, 8) pc::AIAgent);
        m_agent->setup(*property);
        if ((flags & 1) != 0) {
            m_hfsm.setState(3);
            asmCom->setState("S_idle", AnimLayer(0));
        }
    }
}

void GfComBehaviorPc::procMsgObjectNotifyDead(fw::MessageObject* sender, MsgObjectNotifyDead& msg) {
    if (pc::StateUtilField::testVechile(*this)) {
        pc::StateUtilField::requestGetOffRider(*this);
        pc::StateUtil::sendMessageToBuddy(*this, msg);
    } else {
        GfComPropertyPc* property = m_owner->getComponent<GfComPropertyPc>(5);
        if ((property->m_stateFlags & 0x200) != 0) {
            pc::StateUtilField::requestGetOffRider(*this);
        }
        if ((property->m_stateFlags & 0x800) == 0 || msg.m_deadType == 4) {
            GfStateBase::MessageEvent event = {sender, &msg};
            m_hfsm.execEvent(&event);
        }
    }
    GF_OBJ_HANDLE* handle = static_cast<GfObj*>(m_owner)->m_handle;
    if (GfGameManager::getPartyLeaderDriver() == handle) {
        btl::BattleGlobal* global = btl::BattleGlobal::sys();
        if (!global->pad_bit1) {
            btl::DataManager::sys()->SetPartyGauge(0, true);
        } else {
            switch (msg.m_deadType) {
            case 4:
                global->m_controlCharacterDead = true;
                break;
            case 3:
                if (msg.m_cause && msg.m_cause->m_id == 0x1000035) {
                    unsigned int maxHp = GfGameUtil::getMaxHp(handle, GfObjUtil::getObjType(handle),
                                                              GfObjUtil::getGameObjectID(handle));
                    if (static_cast<const MsgObjectDamage*>(msg.m_cause)->m_damage >= maxHp) {
                        btl::BattleGlobal::sys()->m_controlCharacterDead = true;
                    }
                }
                break;
            }
        }
    }
    btl::Utility::NotifyDead(handle, msg);
}

void GfComBehaviorPc::procAnimCallback(GfComAsm* asmCom, const CallBackCache& cache) {
    const char* name = cache.m_event->m_name;
    if (strcmp(name, "look") == 0) {
        pc::StateUtil::setEnableLookIK(*this, cache.m_event->m_value != 0);
    } else if (strcmp(name, "changeLookAxis") == 0) {
        if (pc::LookAxisPlugin* plugin = getPlugin<pc::LookAxisPlugin>(pc::LookAxisPlugin::PLUGIN_ID)) {
            plugin->changeAxisYaw(atof(cache.m_event->m_text));
        }
    } else {
        MsgObjectNotifyAsmCallback msg(asmCom, cache.m_event);
        GfStateBase::MessageEvent event = {static_cast<GfObj*>(m_owner), &msg};
        m_hfsm.execEvent(&event);
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
