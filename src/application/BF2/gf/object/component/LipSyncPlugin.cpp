#include "gf/FileStaticVec3.h"
#include "classes/gf/GfComAsm.h"
#include "gf/GfObjUtil.h"
#include "gf/GfGameUtil.h"
#include "classes/fw/ComponentObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/LipSyncPlugin.h"

namespace gf {

LipSyncPlugin::LipSyncPlugin()
    : m_behavior(nullptr), m_speed(1.0f), m_weight(1.0f), m_isPlaying(false), m_forcePlay(false) {}

bool LipSyncPlugin::setup(gf::GfComBehavior& behavior) {
    m_behavior = &behavior;
    return true;
}

void LipSyncPlugin::cleanup(gf::GfComBehavior&) {}

void LipSyncPlugin::onActivate() {
    m_speed = 1.0f;
    m_weight = 1.0f;
}

void LipSyncPlugin::onDeactivate() {
    GfComAsm* comAsm = m_behavior->m_owner->getComponent<GfComAsm>(2);
    if (m_isPlaying && comAsm != nullptr) {
        comAsm->easeOut("S_lip_talk", 0.0f, ANIM_LAYER_LIP);
        m_isPlaying = false;
    }
}

void LipSyncPlugin::update(gf::GfComBehavior&, const fw::UpdateInfo&) {
    GfComAsm* comAsm = m_behavior->m_owner->getComponent<GfComAsm>(2);
    if (comAsm == nullptr) {
        return;
    }
    GF_OBJ_HANDLE* handle = static_cast<GfObj*>(m_behavior->m_owner)->m_handle;
    // voice and talk are both asked every frame
    bool play = GfGameUtil::isPlayVoice(handle) | GfObjUtil::isTalking(handle);
    if (m_forcePlay) {
        play = true;
    }
    if (play != m_isPlaying) {
        if (play) {
            comAsm->easeIn("S_lip_talk", 0.0f, ANIM_LAYER_LIP);
            comAsm->setSpeedAdditiveState("S_lip_talk", m_speed, ANIM_LAYER_LIP);
            comAsm->setWeightAdditiveState("S_lip_talk", m_weight, ANIM_LAYER_LIP);
        } else {
            comAsm->easeOut("S_lip_talk", 0.05f, ANIM_LAYER_LIP);
        }
        m_isPlaying = play;
    }
}

void LipSyncPlugin::setSpeed(float speed) {
    m_speed = speed;
    GfComAsm* comAsm = m_behavior->m_owner->getComponent<GfComAsm>(2);
    if (comAsm != nullptr && comAsm->isActiveAdditiveState("S_lip_talk", ANIM_LAYER_LIP)) {
        comAsm->setSpeedAdditiveState("S_lip_talk", m_speed, ANIM_LAYER_LIP);
    }
}

void LipSyncPlugin::setWeight(float weight) {
    m_weight = weight;
    GfComAsm* comAsm = m_behavior->m_owner->getComponent<GfComAsm>(2);
    if (comAsm != nullptr && comAsm->isActiveAdditiveState("S_lip_talk", ANIM_LAYER_LIP)) {
        comAsm->setWeightAdditiveState("S_lip_talk", m_weight, ANIM_LAYER_LIP);
    }
}

mm::mtl::RTTI LipSyncPlugin::m_rtti("LipSyncPlugin", &Plugin::m_rtti, nullptr);

}  // namespace gf
