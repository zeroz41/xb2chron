#include "rcha/RchaAnm.h"
#include "classes/RchaCam.h"
#include "classes/RchaCamEff.h"
#include "classes/RchaChrEff.h"
#include "classes/RchaEff.h"
#include "classes/CRchaEx.h"
#include "mm/Col4.h"
#include "mm/Vec3.h"

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
// m_anmIndex (proposed name, not the original's: the symbols leave this table unnamed, lbl_7100B71E98)
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
