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

// RchaChrEff's and CRchaEx's: the same, but each anm takes the first name it matches, and `found` is not touched
// (the name is not the original's). The count is compared as a 64-bit unsigned value, as a sizeof would give it.
static void findFirstAnms(RchaNode& node, const char** names, unsigned long count, int* index) {
    for (int i = 0; i < node.m_anmCount; i++) {
        for (int j = 0; j < count; j++) {
            if (node.m_anm[i].m_id == node.hashStr(names[j])) {
                node.m_anm[i].m_name = names[j];
                index[j] = i;
                break;
            }
        }
    }
}

// the anm names setup looks for, by RchaNode::hashStr of each; an anm found gets the name and its index goes in
// m_anmIndex (the table name is not the original's)
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

// the anm names setup looks for, by RchaNode::hashStr of each; an anm found gets the name and its index goes in
// m_anmIndex (the table name is not the original's)
static const char* s_camEffAnmNames[RchaCamEff::ANM_NUM] = {
    "camAtr/ColFilter",
    "camAtr/ColFilterNear",
    "camAtr/ColFilterFar",
    "camAtr/ColFilterFr",
};

RchaCamEff::RchaCamEff() : m_hasAnm(false) {
    // a loop: the original calls memset where clang would make a tail call of a memset of its own
    for (int i = 0; i < ANM_NUM; i++) {
        m_anmIndex[i] = -1;
    }
}

bool RchaCamEff::getColFilter(int& value, float frame) const {
    int index = m_anmIndex[ANM_ATR_COL_FILTER];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

int RchaCamEff::getNearColFilter(float frame) const {
    int index = m_anmIndex[ANM_ATR_COL_FILTER_NEAR];
    if (index < 0) {
        return 0;
    }
    return m_anm[index].getValueInt(frame);
}

int RchaCamEff::getFarColFilter(float frame) const {
    int index = m_anmIndex[ANM_ATR_COL_FILTER_FAR];
    if (index < 0) {
        return 0;
    }
    return m_anm[index].getValueInt(frame);
}

float RchaCamEff::getFrColFilter(float frame) const {
    int index = m_anmIndex[ANM_ATR_COL_FILTER_FR];
    if (index < 0) {
        return 0.0f;
    }
    return m_anm[index].getValue(frame);
}

bool RchaCamEff::setup(mtl::ALLOC_HANDLE handle, void const* data) {
    m_hasAnm = false;
    RchaNode::setup(handle, data);
    findAnms(*this, s_camEffAnmNames, ANM_NUM, m_anmIndex, m_hasAnm);
    return m_hasAnm;
}

// the anm names setup looks for, by RchaNode::hashStr of each; an anm found gets the name and its index goes in
// m_anmIndex (the table name is not the original's)
static const char* s_chrEffAnmNames[RchaChrEff::ANM_NUM] = {
    "chrEff/VolumeFade",
    "chrEff/VolumeFadeId",
    "chrEff/VolumeFadeUVWScaleX",
    "chrEff/VolumeFadeUVWScaleY",
    "chrEff/VolumeFadeUVWScaleZ",
    "chrEff/VolumeFadeCenterPosX",
    "chrEff/VolumeFadeCenterPosY",
    "chrEff/VolumeFadeCenterPosZ",
    "chrEff/VolumeFadeDistance",
    "chrEff/VolumeFadeDirectivity",
    "chrEff/VolumeFadeMeshNo",
    "chrEff/VolumeFadeRatio",
    "chrEff/RimBloom",
    "chrEff/RimBloomId",
    "chrEff/AfterImage",
    "chrEff/AfterImageId1",
    "chrEff/AfterImageId2",
    "chrEff/AfterImageCaptureFrame",
    "chrEff/AfterImageExistFrame",
    "chrEff/AfterImageFadeOutFrame",
};

RchaChrEff::RchaChrEff() : m_hasAnm(false) {
    // a loop: the original calls memset where clang would make a tail call of a memset of its own
    for (int i = 0; i < ANM_NUM; i++) {
        m_anmIndex[i] = -1;
    }
}

bool RchaChrEff::getVolumeFade(int& value, float frame) const {
    int index = m_anmIndex[ANM_VOLUME_FADE];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

bool RchaChrEff::getVolumeFadeId(int& value, float frame) const {
    int index = m_anmIndex[ANM_VOLUME_FADE_ID];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

void RchaChrEff::getVolumeFadeUVWScale(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_VOLUME_FADE_UVW_SCALE_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_VOLUME_FADE_UVW_SCALE_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_VOLUME_FADE_UVW_SCALE_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
}

void RchaChrEff::getVolumeFadeCenterPos(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_VOLUME_FADE_CENTER_POS_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_VOLUME_FADE_CENTER_POS_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_VOLUME_FADE_CENTER_POS_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
}

bool RchaChrEff::getVolumeFadeDistance(float& value, float frame) const {
    int index = m_anmIndex[ANM_VOLUME_FADE_DISTANCE];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValue(frame);
    return true;
}

bool RchaChrEff::getVolumeFadeDirectivity(float& value, float frame) const {
    int index = m_anmIndex[ANM_VOLUME_FADE_DIRECTIVITY];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValue(frame);
    return true;
}

bool RchaChrEff::getVolumeFadeMesh(int& value, float frame) const {
    int index = m_anmIndex[ANM_VOLUME_FADE_MESH_NO];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

bool RchaChrEff::getVolumeFadeRatio(float& value, float frame) const {
    int index = m_anmIndex[ANM_VOLUME_FADE_RATIO];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValue(frame);
    return true;
}

bool RchaChrEff::getRimBloom(int& value, float frame) const {
    int index = m_anmIndex[ANM_RIM_BLOOM];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

bool RchaChrEff::getRimBloomId(int& value, float frame) const {
    int index = m_anmIndex[ANM_RIM_BLOOM_ID];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

bool RchaChrEff::getAfterImage(int& value, float frame) const {
    int index = m_anmIndex[ANM_AFTER_IMAGE];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

bool RchaChrEff::getAfterImageId1(int& value, float frame) const {
    int index = m_anmIndex[ANM_AFTER_IMAGE_ID1];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

bool RchaChrEff::getAfterImageId2(int& value, float frame) const {
    int index = m_anmIndex[ANM_AFTER_IMAGE_ID2];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

bool RchaChrEff::getAfterImageCaptureFrame(float& value, float frame) const {
    int index = m_anmIndex[ANM_AFTER_IMAGE_CAPTURE_FRAME];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValue(frame);
    return true;
}

bool RchaChrEff::getAfterImageExistFrame(float& value, float frame) const {
    int index = m_anmIndex[ANM_AFTER_IMAGE_EXIST_FRAME];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValue(frame);
    return true;
}

bool RchaChrEff::getAfterImageFadeOutFrame(float& value, float frame) const {
    int index = m_anmIndex[ANM_AFTER_IMAGE_FADE_OUT_FRAME];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValue(frame);
    return true;
}

void RchaChrEff::clear() {
    RchaNode::clear();
    m_hasAnm = false;
}

bool RchaChrEff::setup(mtl::ALLOC_HANDLE handle, void const* data) {
    RchaNode::setup(handle, data);
    findFirstAnms(*this, s_chrEffAnmNames, ANM_NUM, m_anmIndex);
    m_hasAnm = true;
    return true;
}

// the anm names setup looks for, by RchaNode::hashStr of each; an anm found gets the name and its index goes in
// m_anmIndex (the table name is not the original's)
static const char* s_effAnmNames[RchaEff::ANM_NUM] = {
    "eff/translate_x",
    "eff/translate_y",
    "eff/translate_z",
    "eff/rotate_x",
    "eff/rotate_y",
    "eff/rotate_z",
    "eff/scale_x",
    "eff/scale_y",
    "eff/scale_z",
    "effAtr/translate_x",
    "effAtr/translate_y",
    "effAtr/translate_z",
    "effAtr/rotate_x",
    "effAtr/rotate_y",
    "effAtr/rotate_z",
    "effAtr/scale_x",
    "effAtr/scale_y",
    "effAtr/scale_z",
    "effAtr/end",
    "effAtr/kill",
};

RchaEff::RchaEff() : m_hasAnm(false) {
    // a loop: the original calls memset where clang would make a tail call of a memset of its own
    for (int i = 0; i < ANM_NUM; i++) {
        m_anmIndex[i] = -1;
    }
}

void RchaEff::clear() {
    RchaNode::clear();
}

bool RchaEff::getPos(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_TRANSLATE_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_TRANSLATE_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_TRANSLATE_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    return true;
}

bool RchaEff::getRot(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_ROTATE_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_ROTATE_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_ROTATE_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    return true;
}

bool RchaEff::getScl(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_SCALE_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_SCALE_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_SCALE_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    return true;
}

bool RchaEff::getProgress(int& current, int& total, float frame) const {
    int index = m_anmIndex[ANM_ATR_SCALE_X];
    current = index < 0 ? 0 : static_cast<int>(m_anm[index].getValue(frame));
    index = m_anmIndex[ANM_ATR_SCALE_Y];
    total = index < 0 ? 0 : static_cast<int>(m_anm[index].getValue(frame));
    return true;
}

bool RchaEff::getCol(mm::Col4& col, float frame) const {
    int index = m_anmIndex[ANM_ATR_ROTATE_X];
    col.r = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_ATR_ROTATE_Y];
    col.g = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_ATR_ROTATE_Z];
    col.b = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_ATR_TRANSLATE_Z];
    col.a = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    return true;
}

bool RchaEff::isGenelate(float frame) const {
    int index = m_anmIndex[ANM_ATR_TRANSLATE_Y];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValue(frame) > 0.8f;
}

bool RchaEff::isEnd(float frame) const {
    int index = m_anmIndex[ANM_ATR_END];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValue(frame) > 0.8f;
}

bool RchaEff::isKill(float frame) const {
    int index = m_anmIndex[ANM_ATR_KILL];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValue(frame) > 0.8f;
}

bool RchaEff::getSpeed(float& value, float frame) const {
    int index = m_anmIndex[ANM_ATR_TRANSLATE_X];
    value = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    return true;
}

bool RchaEff::setup(mtl::ALLOC_HANDLE handle, void const* data) {
    m_hasAnm = false;
    RchaNode::setup(handle, data);
    findAnms(*this, s_effAnmNames, ANM_NUM, m_anmIndex, m_hasAnm);
    return m_hasAnm;
}

// the anm names setup looks for, by RchaNode::hashStr of each; an anm found gets the name and its index goes in
// m_anmIndex (the table name is not the original's)
static const char* s_exAnmNames[CRchaEx::ANM_NUM] = {
    "dmy",
    "ptExAnm/DynamicsBlend",
    "ptExAnm/WeaponDisp",
    "ptExAnm/WeaponMount",
    "ptExAnm/WeaponBattle",
    "ptExAnm/WeaponSpMot",
    "ptExAnm/WeaponTranslateX",
    "ptExAnm/WeaponTranslateY",
    "ptExAnm/WeaponTranslateZ",
    "ptExAnm/WeaponRotateX",
    "ptExAnm/WeaponRotateY",
    "ptExAnm/WeaponRotateZ",
    "ptExAnm/WeaponScale",
    "ptExAnm/FootEffectL",
    "ptExAnm/FootEffectR",
    "ptExAnm/AO_actionid",
    "ptExAnm/AO_facePrisetType",
    "ptExAnm/AO_eyeType",
    "ptExAnm/AO_translate_x",
    "ptExAnm/AO_translate_y",
    "ptExAnm/AO_translate_z",
    "ptExAnm/AO_rotate_x",
    "ptExAnm/AO_rotate_y",
    "ptExAnm/AO_rotate_z",
    "ptExAnm/AO_scale",
    "ptExAnm/AOTGT_enable",
    "ptExAnm/AOTGT_translate_x",
    "ptExAnm/AOTGT_translate_y",
    "ptExAnm/AOTGT_translate_z",
};

CRchaEx::CRchaEx() : m_hasAnm(false) {
    // a loop: the original calls memset where clang would make a tail call of a memset of its own
    for (int i = 0; i < ANM_NUM; i++) {
        m_anmIndex[i] = -1;
    }
}

bool CRchaEx::getVisible(int& visible, const char* name, float frame) const {
    visible = 0;
    mm::mtl::FixStr<64> anmName("ptVisAnm/");
    anmName += name;
    unsigned int id = hashStr(anmName.m_str);
    for (int i = 0; i < m_anmCount; i++) {
        if (m_anm[i].m_id == id) {
            visible = static_cast<int>(m_anm[i].getValue(frame));
            return true;
        }
    }
    return false;
}

bool CRchaEx::getDynamicsBlend(float& value, float frame) const {
    int index = m_anmIndex[ANM_DYNAMICS_BLEND];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValue(frame);
    return true;
}

bool CRchaEx::getWeaponDisp(int& value, float frame) const {
    int index = m_anmIndex[ANM_WEAPON_DISP];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

bool CRchaEx::getWeaponMount(int& value, float frame) const {
    int index = m_anmIndex[ANM_WEAPON_MOUNT];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

bool CRchaEx::getWeaponBattle(int& value, float frame) const {
    int index = m_anmIndex[ANM_WEAPON_BATTLE];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

bool CRchaEx::getWeaponSpMotion(float frame) const {
    int index = m_anmIndex[ANM_WEAPON_SP_MOT];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValueInt(frame) != 0;
}

void CRchaEx::getWeaponPos(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_WEAPON_TRANSLATE_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_WEAPON_TRANSLATE_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_WEAPON_TRANSLATE_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
}

void CRchaEx::getWeaponRot(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_WEAPON_ROTATE_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame) * 0.0174532924f;
    index = m_anmIndex[ANM_WEAPON_ROTATE_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame) * 0.0174532924f;
    index = m_anmIndex[ANM_WEAPON_ROTATE_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame) * 0.0174532924f;
}

void CRchaEx::getWeaponScl(float& value, float frame) const {
    int index = m_anmIndex[ANM_WEAPON_SCALE];
    value = index < 0 ? 1.0f : m_anm[index].getValue(frame);
}

bool CRchaEx::getFootEffectL(int& value, float frame) const {
    int index = m_anmIndex[ANM_FOOT_EFFECT_L];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

bool CRchaEx::getFootEffectR(int& value, float frame) const {
    int index = m_anmIndex[ANM_FOOT_EFFECT_R];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

int CRchaEx::getActionType(float frame) const {
    int index = m_anmIndex[ANM_AO_ACTIONID];
    if (index < 0) {
        return -1;
    }
    return m_anm[index].getValueInt(frame);
}

int CRchaEx::getFacePrisetType(float frame) const {
    int index = m_anmIndex[ANM_AO_FACE_PRISET_TYPE];
    if (index < 0) {
        return -1;
    }
    return m_anm[index].getValueInt(frame);
}

int CRchaEx::getEyeType(float frame) const {
    int index = m_anmIndex[ANM_AO_EYE_TYPE];
    if (index < 0) {
        return -1;
    }
    return m_anm[index].getValueInt(frame);
}

void CRchaEx::getObjPos(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_AO_TRANSLATE_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_AO_TRANSLATE_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_AO_TRANSLATE_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
}

void CRchaEx::getObjRot(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_AO_ROTATE_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame) * 0.0174532924f;
    index = m_anmIndex[ANM_AO_ROTATE_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame) * 0.0174532924f;
    index = m_anmIndex[ANM_AO_ROTATE_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame) * 0.0174532924f;
}

void CRchaEx::getObjScl(float& value, float frame) const {
    int index = m_anmIndex[ANM_AO_SCALE];
    value = index < 0 ? 1.0f : m_anm[index].getValue(frame);
}

bool CRchaEx::isTargetEnable(float frame) const {
    int index = m_anmIndex[ANM_AOTGT_ENABLE];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValueInt(frame) == 1;
}

void CRchaEx::getTarget(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_AOTGT_TRANSLATE_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_AOTGT_TRANSLATE_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_AOTGT_TRANSLATE_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
}

void CRchaEx::clear() {
    RchaNode::clear();
    m_hasAnm = false;
}

bool CRchaEx::setup(mtl::ALLOC_HANDLE handle, void const* data) {
    RchaNode::setup(handle, data);
    findFirstAnms(*this, s_exAnmNames, ANM_NUM, m_anmIndex);
    m_hasAnm = true;
    return true;
}
