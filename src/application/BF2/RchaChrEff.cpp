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
// m_anmIndex (proposed name, not the original's: the symbols leave this table unnamed, lbl_7100B71CF8)
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
