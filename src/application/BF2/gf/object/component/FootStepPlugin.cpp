#include "classes/gf/FootStepPlugin.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfComEffectCaster.h"
#include "classes/gf/GfComSound.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfSound.h"
#include "classes/fw/ParamManager.h"
#include "fw/UpdateInfo.h"
#include "gf/GfObjUtil.h"
#include "gf/GfDataUtil.h"
#include "gf/MsgFxFootPrint.h"
#include "gf/MsgObjectGetVelocity.h"
#include "gf/SoundVariable.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/IntrusivePtr.h"
#include <string.h>

namespace gf {

FootStepPlugin::FootStepPlugin() : m_running(false) {}

void FootStepPlugin::setAnkleHeight(gf::GfComBehavior& behavior) {
    const Param* param;
    {
        mm::mtl::IntrusivePtr<fw::ParamList> list = fw::ParamManager::get()->m_paramLists[24];
        param = list->getAdapter(0).get<Param>();
    }
    if (GfComEffectCaster* caster = behavior.m_owner->getComponent<GfComEffectCaster>(7)) {
        caster->m_waterDepthLimit = param->pad_4 * 0.01f;
    }
    if (GfComSound* sound = behavior.m_owner->getComponent<GfComSound>(10)) {
        const char* variable = SND_VAR_WATER_THRESOULD_NAME;
        int threshold = param->pad_4;
        sound->m_variables.setVariable(variable, threshold);
    }
}

bool FootStepPlugin::setup(gf::GfComBehavior& behavior) {
    setAnkleHeight(behavior);
    return true;
}

void FootStepPlugin::cleanup(gf::GfComBehavior&) {}

void FootStepPlugin::update(gf::GfComBehavior& behavior, fw::UpdateInfo const&) {
    const Param* param;
    {
        mm::mtl::IntrusivePtr<fw::ParamList> list = fw::ParamManager::get()->m_paramLists[24];
        param = list->getAdapter(0).get<Param>();
    }
    float runSpeed = param->pad_0 / 3.6f;
    MsgObjectGetVelocity msg;
    GfObj* owner = static_cast<GfObj*>(behavior.m_owner);
    owner->sendMessage(owner, msg);  // asks itself
    msg.m_velocity.y = 0.0f;
    m_running = msg.m_velocity.length() >= runSpeed;
    if (GfComSound* sound = behavior.m_owner->getComponent<GfComSound>(10)) {
        const char* variable = getSoundVariableName(SoundVariable(4));  // move_status
        sound->m_variables.setVariable(variable, m_running);
    }
    if (GfComEffectCaster* caster = behavior.m_owner->getComponent<GfComEffectCaster>(7)) {
        caster->m_running = m_running;
    }
}

void FootStepPlugin::onActivate() {
    m_running = false;
}

void FootStepPlugin::onDeactivate() {}

GfEnvProperty::GROUND_INDEX getFootGroundIndex(const char* name) {
    if (strcmp("right", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(2);
    }
    if (strcmp("left", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(1);
    }
    if (strcmp("right00", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(2);
    }
    if (strcmp("left00", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(1);
    }
    if (strcmp("right01", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(4);
    }
    if (strcmp("left01", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(3);
    }
    if (strcmp("right02", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(6);
    }
    if (strcmp("left02", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(5);
    }
    return static_cast<GfEnvProperty::GROUND_INDEX>(0);
}

void FootStepPlugin::notifyStep(gf::GfComBehavior& behavior, const char* name) {
    if (!m_active) {
        return;
    }
    GfEnvProperty::GROUND_INDEX ground = getFootGroundIndex(name);
    if (GfComEffectCaster* caster = behavior.m_owner->getComponent<GfComEffectCaster>(7)) {
        MsgFxFootPrint msg(ground);
        msg.m_alternate = m_running;
        GfObj* owner = static_cast<GfObj*>(behavior.m_owner);
        caster->recieveMessage(owner, msg);
    }
    playSe(behavior, ground);
}

// the step sounds by foot step kind (GfObjSetup::getFootStep), left foot (lbl_7100B65780) and right foot
// (lbl_7100B65828); kinds 8 and 0x11 are played apart (the names are not the original's; the symbols leave the
// tables unnamed)
__attribute__((used)) static const char* s_footStepSeL[21] = {
    nullptr,
    "fld_footstep_l_NORMAL",
    "fld_footstep_l_NOPON",
    "fld_footstep_l_HUGE",
    "fld_footstep_l_HANA",
    "fld_footstep_l_BENKEI",
    "fld_footstep_l_ANIMAL",
    nullptr,
    nullptr,
    "fld_footstep_l_EN_M",
    "fld_footstep_l_EN_L",
    "fld_footstep_l_EN_MECHA_L",
    "fld_footstep_l_EN_KUGUTSU",
    "fld_footstep_l_EN_YOSHITSUNE",
    "fld_footstep_l_EN_SAKURA",
    "fld_footstep_l_EN_SATAHIKO",
    "fld_footstep_l_EN_DANI",
    "dlc_fld_hanabuster_01_wl",
    "dlc_fld_footstep_l_HIGHHEELS",
    "fld_footstep_l_BL400301",
    "fld_footstep_l_NORMAL",
};
__attribute__((used)) static const char* s_footStepSeR[21] = {
    nullptr,
    "fld_footstep_r_NORMAL",
    "fld_footstep_r_NOPON",
    "fld_footstep_r_HUGE",
    "fld_footstep_r_HANA",
    "fld_footstep_r_BENKEI",
    "fld_footstep_r_ANIMAL",
    nullptr,
    nullptr,
    "fld_footstep_r_EN_M",
    "fld_footstep_r_EN_L",
    "fld_footstep_r_EN_MECHA_L",
    "fld_footstep_r_EN_KUGUTSU",
    "fld_footstep_r_EN_YOSHITSUNE",
    "fld_footstep_r_EN_SAKURA",
    "fld_footstep_r_EN_SATAHIKO",
    "fld_footstep_r_EN_DANI",
    "dlc_fld_hanabuster_01_wr",
    "dlc_fld_footstep_r_HIGHHEELS",
    "fld_footstep_r_BL400301",
    "fld_footstep_l_NORMAL",  // the left foot's, as in the original table
};

void FootStepPlugin::playSe(gf::GfComBehavior& behavior, GfEnvProperty::GROUND_INDEX ground) {
    GF_OBJ_HANDLE* handle = static_cast<GfObj*>(behavior.m_owner)->m_handle;
    GfObjSetup* setup = GfObjUtil::getObjSetup(handle);
    if (setup == nullptr) {
        return;
    }
    unsigned int kind = setup->getFootStep();
    GfComSound* sound = behavior.m_owner->getComponent<GfComSound>(10);
    mm::mtl::FixStr<64> str;
    // the left feet are the odd grounds 1, 3 and 5 (getFootGroundIndex)
    auto isLeft = [ground]() { unsigned int foot = ground - 1; return foot < 5 && foot % 2 == 0; };
    const char* name;
    if (kind == 8) {
        if (ground == 3 || ground == 4) {
            name = isLeft() ? "fld_footstep_l_HUGE" : "fld_footstep_r_HUGE";
        } else {
            name = isLeft() ? "fld_footstep_l_NORMAL" : "fld_footstep_r_NORMAL";
        }
    } else if (kind == 0x11) {
            if (GfObjUtil::isGhost(static_cast<GfObj*>(behavior.m_owner)->m_handle)) {
                return;
            }
            GfSound* gfSound = GfSound::get();
            if (gfSound == nullptr) {
                return;
            }
            name = isLeft() ? "dlc_fld_hanabuster_01_wl" : "dlc_fld_hanabuster_01_wr";
            gfSound->playSe(name, fw::SoundCategory(GfObjUtil::getSoundCategoryNormal(static_cast<GfObj*>(behavior.m_owner)->m_handle)));
            return;
    } else {
        const char*& entry = isLeft() ? s_footStepSeL[kind] : s_footStepSeR[kind];
        name = entry;
        if (kind == 1 && GfDataUtil::isIra()) {
            str = "dlc_";
            str += name;
            name = str.m_str;
        }
    }
    if (sound != nullptr && name != nullptr) {
        sound->playSe(name, 1.0f, mm::Vec3::zero, false);
    }
}

mm::mtl::RTTI FootStepPlugin::m_rtti("FootStepPlugin", &Plugin::m_rtti, nullptr);

}  // namespace gf
