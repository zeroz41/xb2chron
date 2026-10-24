#include "rcha/RchaAnm.h"
#include "classes/RchaCam.h"
#include "classes/RchaCamEff.h"
#include "classes/RchaChrEff.h"
#include "classes/RchaEff.h"
#include "classes/CRchaEx.h"
#include "classes/RchaCam.h"
#include "classes/RchaCamEff.h"
#include "classes/RchaChrEff.h"
#include "classes/RchaEff.h"
#include "classes/CRchaEx.h"
#include "mm/Col4.h"
#include "mm/Vec3.h"

// what each setup does with its table of names (the name is not the original's): every anm of `node` whose id is the
// RchaNode::hashStr of one of the `count` names gets that name and its index goes in index[name], and `found` is set.
// The table is passed in: read in place, clang would make the never-written table constant (.data.rel.ro), where the
// original's stays in .data and is read again after each hashStr call.
static void findAnms(RchaNode& node, const char** names, int count, int* index, bool& found) {
    for (int i = 0; i < node.m_anmCount; i++) {
        for (int j = 0; j < count; j++) {
            if (node.m_anm[i].m_id == node.hashStr(names[j])) {
                node.m_anm[i].m_name = names[j];
                index[j] = i;
                found = true;
            }
        }
    }
}

// the anm names setup looks for, by RchaNode::hashStr of each; an anm found gets the name and its index goes in
// m_anmIndex (proposed name, not the original's: the symbols leave this table unnamed, lbl_7100B71B88)
static const char* s_camAnmNames[RchaCam::ANM_NUM] = {
    "cam/translate_x",
    "cam/translate_y",
    "cam/translate_z",
    "cam/rotate_x",
    "cam/rotate_y",
    "cam/rotate_z",
    "cam/rotate_order",
    "camAtr/translate_x",
    "camAtr/translate_y",
    "camAtr/translate_z",
    "camAtr/Dof",
    "camAtr/DofDistance",
    "camAtr/DofRange",
    "camAtr/DofPixel",
    "camAtr/DofLens",
    "camAtr/DofStrength",
    "camAtr/DofBlend",
    "camAtr/DofPixelLv",
    "camAtr/DofHlv",
    "camAtr/MBlur",
    "camAtr/MBlur_Str",
    "camAtr/MBlur_Sub",
    "camAtr/SM_Vis",
    "camAtr/Clock",
    "camAtr/ClockHour",
    "camAtr/Wtr",
    "camAtr/WtrType",
    "camAtr/WtrFade",
    "camAtr/CamLGT",
    "camAtr/NearFar",
};

RchaCam::RchaCam() : m_hasAnm(false) {
    // a loop: the original calls memset where clang would make a tail call of a memset of its own
    for (int i = 0; i < ANM_NUM; i++) {
        m_anmIndex[i] = -1;
    }
}

bool RchaCam::getPos(mm::Vec3* vec, float frame) const {
    int index = m_anmIndex[ANM_TRANSLATE_X];
    vec->x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_TRANSLATE_Y];
    vec->y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_TRANSLATE_Z];
    vec->z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    return true;
}

bool RchaCam::getRot(mm::Vec3* vec, float frame) const {
    int index = m_anmIndex[ANM_ROTATE_X];
    vec->x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_ROTATE_Y];
    vec->y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_ROTATE_Z];
    vec->z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    return true;
}

int RchaCam::getRotOrder(float frame) const {
    int index = m_anmIndex[ANM_ROTATE_ORDER];
    if (index < 0) {
        return 0;
    }
    return m_anm[index].getValueInt(frame);
}

float RchaCam::getFov(float frame) const {
    int index = m_anmIndex[ANM_ATR_TRANSLATE_Z];
    if (index < 0) {
        return 30.0f;
    }
    return m_anm[index].getValue(frame);
}

float RchaCam::getMBlurStr(float frame) const {
    int index = m_anmIndex[ANM_ATR_M_BLUR_STR];
    if (index < 0) {
        return 0.5f;
    }
    return m_anm[index].getValue(frame);
}

bool RchaCam::isEnableMBlur(float frame) const {
    int index = m_anmIndex[ANM_ATR_M_BLUR];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValue(frame) > 0.9f;
}

float RchaCam::getMBlurSub(float frame) const {
    int index = m_anmIndex[ANM_ATR_M_BLUR_SUB];
    if (index < 0) {
        return 0.1f;
    }
    return m_anm[index].getValue(frame);
}

bool RchaCam::isEnableDOF(float frame) const {
    int index = m_anmIndex[ANM_ATR_DOF];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValue(frame) > 0.9f;
}

float RchaCam::getDistanceDOF(float frame) const {
    int index = m_anmIndex[ANM_ATR_DOF_DISTANCE];
    if (index < 0) {
        return 20.0f;
    }
    return m_anm[index].getValue(frame);
}

float RchaCam::getRangeDOF(float frame) const {
    int index = m_anmIndex[ANM_ATR_DOF_RANGE];
    if (index < 0) {
        return 40.0f;
    }
    return m_anm[index].getValue(frame);
}

float RchaCam::getPixelDOF(float frame) const {
    int index = m_anmIndex[ANM_ATR_DOF_PIXEL];
    if (index < 0) {
        return 5.0f;
    }
    return m_anm[index].getValue(frame);
}

float RchaCam::getLensDOF(float frame) const {
    int index = m_anmIndex[ANM_ATR_DOF_LENS];
    if (index < 0) {
        return 0.6f;
    }
    return m_anm[index].getValue(frame);
}

float RchaCam::getStrengthDOF(float frame) const {
    int index = m_anmIndex[ANM_ATR_DOF_STRENGTH];
    if (index < 0) {
        return 4.0f;
    }
    return m_anm[index].getValue(frame);
}

float RchaCam::getBlendDOF(float frame) const {
    int index = m_anmIndex[ANM_ATR_DOF_BLEND];
    if (index < 0) {
        return 1.0f;
    }
    return m_anm[index].getValue(frame);
}

int RchaCam::getPixelLvDOF(float frame) const {
    int index = m_anmIndex[ANM_ATR_DOF_PIXEL_LV];
    if (index < 0) {
        return 0;
    }
    return m_anm[index].getValueInt(frame);
}

bool RchaCam::isHlvDOF(float frame) const {
    int index = m_anmIndex[ANM_ATR_DOF_HLV];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValue(frame) > 0.9f;
}

bool RchaCam::isSMapVis(float frame) const {
    int index = m_anmIndex[ANM_ATR_SM_VIS];
    if (index < 0) {
        return true;
    }
    return m_anm[index].getValue(frame) > 0.9f;
}

bool RchaCam::isEnableTime(float frame) const {
    int index = m_anmIndex[ANM_ATR_CLOCK];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValue(frame) > 0.9f;
}

float RchaCam::getTimeVal(float frame) const {
    float hour = 0.0f;
    int index = m_anmIndex[ANM_ATR_CLOCK_HOUR];
    if (index >= 0) {
        hour = m_anm[index].getValue(frame);
        if (hour < 0.0f) {
            hour = 0.0f;
        } else if (hour > 23.999998f) {
            hour = 23.999998f;
        }
    }
    return hour;
}

bool RchaCam::isEnableWeather(float frame) const {
    int index = m_anmIndex[ANM_ATR_WTR];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValue(frame) > 0.9f;
}

bool RchaCam::isCamLgtStop(float frame) const {
    int index = m_anmIndex[ANM_ATR_CAM_LGT];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValue(frame) > 0.9f;
}

int RchaCam::getNearFarType(float frame) const {
    int index = m_anmIndex[ANM_ATR_NEAR_FAR];
    if (index < 0) {
        return 0;
    }
    return m_anm[index].getValueInt(frame);
}

int RchaCam::getWeatherType(float frame) const {
    int index = m_anmIndex[ANM_ATR_WTR_TYPE];
    if (index < 0) {
        return 0;
    }
    return m_anm[index].getValueInt(frame);
}

int RchaCam::getWeatherFrame(float frame) const {
    int index = m_anmIndex[ANM_ATR_WTR_FADE];
    if (index < 0) {
        return 0;
    }
    return m_anm[index].getValueInt(frame);
}

bool RchaCam::setup(mtl::ALLOC_HANDLE handle, void const* data) {
    m_hasAnm = false;
    RchaNode::setup(handle, data);
    findAnms(*this, s_camAnmNames, ANM_NUM, m_anmIndex, m_hasAnm);
    return m_hasAnm;
}

