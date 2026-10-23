#include "classes/ml/DrFogObjGbl.h"
#include "classes/ml/DrMdoCtlDammy.h"
#include "classes/ml/DrMdoCtlSeamAll.h"
#include "classes/ml/DrMdoMat.h"
#include "math.h"
#include "ml/DrEnvironmentAnim.h"
#include "ml/DrMdoAnim.h"
#include "ml/DrResMdoMat.h"
#include "ml/MdoWrkMatRes.h"
#include "ml/MdsMatInfoHeader.h"

namespace ml {

DrFogObjGbl::~DrFogObjGbl() {}

void DrFogObjGbl::update() {}

void DrMdoCtlDammy::resourceInit() {}

void DrMdoCtlDammy::update() {}

void DrMdoCtlDammy::dispOffUpdate() {}

void DrMdoCtlSeamAll::debugRender() {}

void DrEnvironmentAnim::envlgt_amb_color_R(const LgtAnimInf* info, float frame) {
    m_color[0] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_amb_color_G(const LgtAnimInf* info, float frame) {
    m_color[1] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_amb_color_B(const LgtAnimInf* info, float frame) {
    m_color[2] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_amb_color_Intensity(const LgtAnimInf* info, float frame) {
    m_intensity = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_amb_non(const LgtAnimInf*, float) {}

// 1.0.0 keeps an out-of-line copy (0x71007DC7BC); 3.0.1's linker dropped it, every caller inlines it.
inline float DrEnvironmentAnim::getHermiteAttr(const LgtAnimInf* info, float frame) {
    if (info->m_startFrame >= frame) {
        return m_hermiteKeys[info->m_start].m_value;
    }
    if (info->m_endFrame <= frame) {
        return m_hermiteKeys[info->m_start + info->m_keyNum - 1].m_value;
    }
    const LgtAnimKey* key = &m_hermiteKeys[info->m_start + 1];
    for (int i = 1; i < info->m_keyNum; i++, key++) {
        float keyFrame = key->m_frame;
        if (keyFrame > frame) {
            const LgtAnimKey* prev = key - 1;
            float prevFrame = prev->m_frame;
            float range = keyFrame - prevFrame;
            float t = (frame - prevFrame) / range;
            float t2 = t * t;
            float t3 = t * t2;
            float h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
            float h10 = t3 - 2.0f * t2 + t;
            float h01 = 3.0f * t2 - 2.0f * t3;
            float h11 = t3 - t2;
            return prev->m_value * h00 + prev->m_outTangent * h10 + key->m_value * h01 + key->m_inTangent * h11;
        }
    }
    return 0.0f;
}

void DrEnvironmentAnim::envlgt_dir_color_R(DrLightObjDir* obj, const LgtAnimInf* info, float frame) {
    m_color[0] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_dir_color_G(DrLightObjDir* obj, const LgtAnimInf* info, float frame) {
    m_color[1] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_dir_color_B(DrLightObjDir* obj, const LgtAnimInf* info, float frame) {
    m_color[2] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_dir_color_Intensity(DrLightObjDir* obj, const LgtAnimInf* info, float frame) {
    m_intensity = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_dir_spe_Intensity(DrLightObjDir*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_dir_non(DrLightObjDir*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_dir_texonoff(DrLightObjDir*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_dir_texofsX(DrLightObjDir*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_dir_texofsY(DrLightObjDir*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_dir_size(DrLightObjDir*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_dir_rotz(DrLightObjDir* obj, const LgtAnimInf* info, float frame) {
    m_anmVal[2] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_dir_roty(DrLightObjDir* obj, const LgtAnimInf* info, float frame) {
    m_anmVal[1] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_dir_rotx(DrLightObjDir* obj, const LgtAnimInf* info, float frame) {
    m_anmVal[0] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_pnt_color_R(DrLightObjPnt* obj, const LgtAnimInf* info, float frame) {
    m_color[0] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_pnt_color_G(DrLightObjPnt* obj, const LgtAnimInf* info, float frame) {
    m_color[1] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_pnt_color_B(DrLightObjPnt* obj, const LgtAnimInf* info, float frame) {
    m_color[2] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_pnt_color_Intensity(DrLightObjPnt* obj, const LgtAnimInf* info, float frame) {
    m_intensity = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_pnt_spe_Intensity(DrLightObjPnt* obj, const LgtAnimInf* info, float frame) {
    obj->m_speIntensity = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_pnt_non(DrLightObjPnt*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_pnt_texonoff(DrLightObjPnt*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_pnt_texofsX(DrLightObjPnt*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_pnt_texofsY(DrLightObjPnt*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_pnt_size(DrLightObjPnt* obj, const LgtAnimInf* info, float frame) {
    obj->m_size = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_pnt_rotz(DrLightObjPnt* obj, const LgtAnimInf* info, float frame) {
    m_anmVal[2] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_pnt_roty(DrLightObjPnt* obj, const LgtAnimInf* info, float frame) {
    m_anmVal[1] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_pnt_rotx(DrLightObjPnt* obj, const LgtAnimInf* info, float frame) {
    m_anmVal[0] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_spt_color_R(DrLightObjSpt* obj, const LgtAnimInf* info, float frame) {
    m_color[0] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_spt_color_G(DrLightObjSpt* obj, const LgtAnimInf* info, float frame) {
    m_color[1] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_spt_color_B(DrLightObjSpt* obj, const LgtAnimInf* info, float frame) {
    m_color[2] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_spt_color_Intensity(DrLightObjSpt* obj, const LgtAnimInf* info, float frame) {
    m_intensity = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_spt_spe_Intensity(DrLightObjSpt* obj, const LgtAnimInf* info, float frame) {
    obj->m_speIntensity = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_spt_angle(DrLightObjSpt* obj, const LgtAnimInf* info, float frame) {
    obj->m_angle = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_spt_texonoff(DrLightObjSpt*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_spt_texofsX(DrLightObjSpt*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_spt_texofsY(DrLightObjSpt*, const LgtAnimInf*, float) {}

void DrEnvironmentAnim::envlgt_spt_size(DrLightObjSpt* obj, const LgtAnimInf* info, float frame) {
    obj->m_size = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_spt_rotz(DrLightObjSpt* obj, const LgtAnimInf* info, float frame) {
    m_anmVal[2] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_spt_roty(DrLightObjSpt* obj, const LgtAnimInf* info, float frame) {
    m_anmVal[1] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_spt_rotx(DrLightObjSpt* obj, const LgtAnimInf* info, float frame) {
    m_anmVal[0] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_trans_posx(const LgtAnimInf* info, float frame) {
    m_anmVal[0] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_trans_posy(const LgtAnimInf* info, float frame) {
    m_anmVal[1] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envlgt_trans_posz(const LgtAnimInf* info, float frame) {
    m_anmVal[2] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_color_R(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    m_color[0] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_color_G(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    m_color[1] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_color_B(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    m_color[2] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_color_sideR(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    m_sideColor[0] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_color_sideG(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    m_sideColor[1] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_color_sideB(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    m_sideColor[2] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_near(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    obj->m_near = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_far(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    obj->m_far = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_str(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    obj->m_str = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_pow(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    obj->m_pow = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_color_sunR(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    m_sunColor[0] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_color_sunG(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    m_sunColor[1] = getHermiteAttr(info, frame);
}

void DrEnvironmentAnim::envfog_parm_color_sunB(DrFogObjGbl* obj, const LgtAnimInf* info, float frame) {
    m_sunColor[2] = getHermiteAttr(info, frame);
}

void (DrEnvironmentAnim::*DrEnvironmentAnim::s_pCallAmb[13])(const LgtAnimInf*, float) = {
    &DrEnvironmentAnim::envlgt_amb_color_R,
    &DrEnvironmentAnim::envlgt_amb_color_G,
    &DrEnvironmentAnim::envlgt_amb_color_B,
    &DrEnvironmentAnim::envlgt_amb_color_Intensity,
    &DrEnvironmentAnim::envlgt_amb_non,
    &DrEnvironmentAnim::envlgt_amb_non,
    &DrEnvironmentAnim::envlgt_amb_non,
    &DrEnvironmentAnim::envlgt_amb_non,
    &DrEnvironmentAnim::envlgt_amb_non,
    &DrEnvironmentAnim::envlgt_amb_non,
    &DrEnvironmentAnim::envlgt_amb_non,
    &DrEnvironmentAnim::envlgt_amb_non,
    &DrEnvironmentAnim::envlgt_amb_non,
};

void (DrEnvironmentAnim::*DrEnvironmentAnim::s_pCallDir[13])(DrLightObjDir*, const LgtAnimInf*, float) = {
    &DrEnvironmentAnim::envlgt_dir_color_R,
    &DrEnvironmentAnim::envlgt_dir_color_G,
    &DrEnvironmentAnim::envlgt_dir_color_B,
    &DrEnvironmentAnim::envlgt_dir_color_Intensity,
    &DrEnvironmentAnim::envlgt_dir_spe_Intensity,
    &DrEnvironmentAnim::envlgt_dir_non,
    &DrEnvironmentAnim::envlgt_dir_texonoff,
    &DrEnvironmentAnim::envlgt_dir_texofsX,
    &DrEnvironmentAnim::envlgt_dir_texofsY,
    &DrEnvironmentAnim::envlgt_dir_size,
    &DrEnvironmentAnim::envlgt_dir_rotz,
    &DrEnvironmentAnim::envlgt_dir_roty,
    &DrEnvironmentAnim::envlgt_dir_rotx,
};

void (DrEnvironmentAnim::*DrEnvironmentAnim::s_pCallPnt[13])(DrLightObjPnt*, const LgtAnimInf*, float) = {
    &DrEnvironmentAnim::envlgt_pnt_color_R,
    &DrEnvironmentAnim::envlgt_pnt_color_G,
    &DrEnvironmentAnim::envlgt_pnt_color_B,
    &DrEnvironmentAnim::envlgt_pnt_color_Intensity,
    &DrEnvironmentAnim::envlgt_pnt_spe_Intensity,
    &DrEnvironmentAnim::envlgt_pnt_non,
    &DrEnvironmentAnim::envlgt_pnt_texonoff,
    &DrEnvironmentAnim::envlgt_pnt_texofsX,
    &DrEnvironmentAnim::envlgt_pnt_texofsY,
    &DrEnvironmentAnim::envlgt_pnt_size,
    &DrEnvironmentAnim::envlgt_pnt_rotz,
    &DrEnvironmentAnim::envlgt_pnt_roty,
    &DrEnvironmentAnim::envlgt_pnt_rotx,
};

void (DrEnvironmentAnim::*DrEnvironmentAnim::s_pCallSpt[13])(DrLightObjSpt*, const LgtAnimInf*, float) = {
    &DrEnvironmentAnim::envlgt_spt_color_R,
    &DrEnvironmentAnim::envlgt_spt_color_G,
    &DrEnvironmentAnim::envlgt_spt_color_B,
    &DrEnvironmentAnim::envlgt_spt_color_Intensity,
    &DrEnvironmentAnim::envlgt_spt_spe_Intensity,
    &DrEnvironmentAnim::envlgt_spt_angle,
    &DrEnvironmentAnim::envlgt_spt_texonoff,
    &DrEnvironmentAnim::envlgt_spt_texofsX,
    &DrEnvironmentAnim::envlgt_spt_texofsY,
    &DrEnvironmentAnim::envlgt_spt_size,
    &DrEnvironmentAnim::envlgt_spt_rotz,
    &DrEnvironmentAnim::envlgt_spt_roty,
    &DrEnvironmentAnim::envlgt_spt_rotx,
};

void (DrEnvironmentAnim::*DrEnvironmentAnim::s_pTransAnim[3])(const LgtAnimInf*, float) = {
    &DrEnvironmentAnim::envlgt_trans_posx,
    &DrEnvironmentAnim::envlgt_trans_posy,
    &DrEnvironmentAnim::envlgt_trans_posz,
};

void (DrEnvironmentAnim::*DrEnvironmentAnim::s_pFogAnim[13])(DrFogObjGbl*, const LgtAnimInf*, float) = {
    &DrEnvironmentAnim::envfog_parm_color_R,
    &DrEnvironmentAnim::envfog_parm_color_G,
    &DrEnvironmentAnim::envfog_parm_color_B,
    &DrEnvironmentAnim::envfog_parm_color_sideR,
    &DrEnvironmentAnim::envfog_parm_color_sideG,
    &DrEnvironmentAnim::envfog_parm_color_sideB,
    &DrEnvironmentAnim::envfog_parm_near,
    &DrEnvironmentAnim::envfog_parm_far,
    &DrEnvironmentAnim::envfog_parm_str,
    &DrEnvironmentAnim::envfog_parm_pow,
    &DrEnvironmentAnim::envfog_parm_color_sunR,
    &DrEnvironmentAnim::envfog_parm_color_sunG,
    &DrEnvironmentAnim::envfog_parm_color_sunB,
};

void DrMdoMat::updateMatCallBack(const unsigned int* dispBits) {
    const MdsMatCallBackTbl* tbl = m_pWrkMatRes->m_pCallBackTbl;
    if (tbl == nullptr || tbl->m_matListNum == 0) {
        return;
    }
    int num = tbl->m_matListNum;
    const unsigned char* calls = m_pWrkMatRes->m_pMatData + tbl->m_callOfs;
    const unsigned short* list = reinterpret_cast<const unsigned short*>(m_pWrkMatRes->m_pMatData + tbl->m_matListOfs);
    for (int i = 0; i < num; i++) {
        unsigned short mat = list[i];
        if (dispBits[mat >> 5] & (1 << (mat & 0x1F))) {
            const MdsMatInfoHeader* info = &m_pWrkMatRes->m_pMatInfo[mat];
            const unsigned short* call = reinterpret_cast<const unsigned short*>(calls + info->m_callBackIdx * 4);
            int cnt = info->m_callBackNum;
            for (int j = 0; j < cnt; j++) {
                (this->*s_pCallMatVal[call[0]])(info, call[1], list[i]);
                call += 2;
            }
        }
    }
}

void DrMdoMat::matCall_EmissiveTime(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* uni = m_pWrkMatRes->m_pUniformVal;
    float* mat = m_pWrkMatRes->m_pMatVal;
    unsigned int idx = info->m_uniformOfs + slot;
    unsigned int time = info->m_timeSlot + info->m_uniformOfs;
    uni[idx] = mat[idx] * uni[time];
}

void DrMdoMat::matCall_RgbTime(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* uni = m_pWrkMatRes->m_pUniformVal;
    float* mat = m_pWrkMatRes->m_pMatVal;
    unsigned int idx = info->m_uniformOfs + slot;
    float* dst = &uni[idx];
    float* src = &mat[idx];
    unsigned int time = info->m_timeSlot + info->m_uniformOfs;
    dst[0] = src[0] * uni[time];
    dst[1] = src[1] * uni[time];
    dst[2] = src[2] * uni[time];
}

void DrMdoMat::matCall_RTime(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* uni = m_pWrkMatRes->m_pUniformVal;
    float* mat = m_pWrkMatRes->m_pMatVal;
    unsigned int idx = info->m_uniformOfs + slot;
    unsigned int time = info->m_timeSlot + info->m_uniformOfs;
    uni[idx] = mat[idx] * uni[time];
}

void DrMdoMat::matCall_AccRgb1(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[0].r;
    dst[1] = m_pWrkMatRes->m_pAce->m_color[0].g;
    dst[2] = m_pWrkMatRes->m_pAce->m_color[0].b;
}

void DrMdoMat::matCall_AccRgb2(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[1].r;
    dst[1] = m_pWrkMatRes->m_pAce->m_color[1].g;
    dst[2] = m_pWrkMatRes->m_pAce->m_color[1].b;
}

void DrMdoMat::matCall_AccRgb3(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[2].r;
    dst[1] = m_pWrkMatRes->m_pAce->m_color[2].g;
    dst[2] = m_pWrkMatRes->m_pAce->m_color[2].b;
}

void DrMdoMat::matCall_AccRgb4(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[3].r;
    dst[1] = m_pWrkMatRes->m_pAce->m_color[3].g;
    dst[2] = m_pWrkMatRes->m_pAce->m_color[3].b;
}

void DrMdoMat::matCall_AccMulRgb1(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[0].r * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_color[0].g * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_color[0].b * dst[2];
}

void DrMdoMat::matCall_AccMulRgb2(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[1].r * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_color[1].g * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_color[1].b * dst[2];
}

void DrMdoMat::matCall_AccMulRgb3(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[2].r * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_color[2].g * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_color[2].b * dst[2];
}

void DrMdoMat::matCall_AccMulRgb4(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[3].r * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_color[3].g * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_color[3].b * dst[2];
}

void DrMdoMat::matCall_AccVal1(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[0];
}

void DrMdoMat::matCall_AccVal2(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[1];
}

void DrMdoMat::matCall_AccVal3(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[2];
}

void DrMdoMat::matCall_AccVal4(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[3];
}

void DrMdoMat::matCall_AccMulVal1(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[0] * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_val[0] * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_val[0] * dst[2];
}

void DrMdoMat::matCall_AccMulVal2(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[1] * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_val[1] * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_val[1] * dst[2];
}

void DrMdoMat::matCall_AccMulVal3(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[2] * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_val[2] * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_val[2] * dst[2];
}

void DrMdoMat::matCall_AccMulVal4(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[3] * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_val[3] * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_val[3] * dst[2];
}

void DrMdoMat::matCall_CalcBloom(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    float* src = m_pWrkMatRes->m_pMatVal;
    unsigned int idx = info->m_uniformOfs + slot;
    dst[idx] = src[idx] * m_colorScale;
}

void DrMdoMat::matCall_CalcColor(const MdsMatInfoHeader* info, int slot, int matIdx) {
    m_pWrkMatRes->m_pResMat[matIdx].setColor(info->m_color[0] * m_colorScale, m_colorScale * info->m_color[1],
                                             m_colorScale * info->m_color[2], info->m_color[3]);
}

void DrMdoMat::matCall_ToonId(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = dst[1] / 255.0f;
}

void DrMdoMat::matCall_VolumeTest(const MdsMatInfoHeader* info, int slot, int matIdx) {

}

void DrMdoMat::matCall_BaseColor(const MdsMatInfoHeader* info, int slot, int matIdx) {
    DrResMdoMat* mat = &m_pWrkMatRes->m_pResMat[matIdx];
    mat->m_color[0] = m_pWrkMatRes->m_pAce->m_color[slot].r;
    mat->m_color[1] = m_pWrkMatRes->m_pAce->m_color[slot].g;
    mat->m_color[2] = m_pWrkMatRes->m_pAce->m_color[slot].b;
}

void DrMdoMat::matCall_BaseVal(const MdsMatInfoHeader* info, int slot, int matIdx) {
    DrResMdoMat* mat = &m_pWrkMatRes->m_pResMat[matIdx];
    mat->m_color[0] = m_pWrkMatRes->m_pAce->m_val[slot];
    mat->m_color[1] = m_pWrkMatRes->m_pAce->m_val[slot];
    mat->m_color[2] = m_pWrkMatRes->m_pAce->m_val[slot];
}

void DrMdoMat::matCall_TransVal(const MdsMatInfoHeader* info, int slot, int matIdx) {
    m_pWrkMatRes->m_pResMat[matIdx].setAlpha(m_pWrkMatRes->m_pAce->m_val[slot]);
}

void (DrMdoMat::*DrMdoMat::s_pCallMatVal[35])(const MdsMatInfoHeader*, int, int) = {
    &DrMdoMat::matCall_MatxView,
    &DrMdoMat::matCall_EmissiveTime,
    &DrMdoMat::matCall_RgbTime,
    &DrMdoMat::matCall_RTime,
    &DrMdoMat::matCall_AccRgb1,
    &DrMdoMat::matCall_AccRgb2,
    &DrMdoMat::matCall_AccRgb3,
    &DrMdoMat::matCall_AccRgb4,
    &DrMdoMat::matCall_AccMulRgb1,
    &DrMdoMat::matCall_AccMulRgb2,
    &DrMdoMat::matCall_AccMulRgb3,
    &DrMdoMat::matCall_AccMulRgb4,
    &DrMdoMat::matCall_AccVal1,
    &DrMdoMat::matCall_AccVal2,
    &DrMdoMat::matCall_AccVal3,
    &DrMdoMat::matCall_AccVal4,
    &DrMdoMat::matCall_AccMulVal1,
    &DrMdoMat::matCall_AccMulVal2,
    &DrMdoMat::matCall_AccMulVal3,
    &DrMdoMat::matCall_AccMulVal4,
    &DrMdoMat::matCall_WaterFog,
    &DrMdoMat::matCall_MatxInvView,
    &DrMdoMat::matCall_FurShader,
    &DrMdoMat::matCall_CalcBloom,
    &DrMdoMat::matCall_CalcColor,
    &DrMdoMat::matCall_OutLineVal,
    &DrMdoMat::matCall_ToonId,
    &DrMdoMat::matCall_VolumeTest,
    &DrMdoMat::matCall_BaseColor,
    &DrMdoMat::matCall_BaseVal,
    &DrMdoMat::matCall_TransVal,
    &DrMdoMat::fn_71007701FC,
    &DrMdoMat::fn_71007710B0,
    &DrMdoMat::fn_7100772150,
    &DrMdoMat::fn_7100777C88,
};

void DrMdoAnim::animcall_UV_Scr_U(DrResMdoMat* mat, float* work, float value) {
    work[0] = value;
}

void DrMdoAnim::animcall_UV_Scr_V(DrResMdoMat* mat, float* work, float value) {
    work[5] = value;
}

void DrMdoAnim::animcall_UV_Trans_U(DrResMdoMat* mat, float* work, float value) {
    work[3] = value;
}

void DrMdoAnim::animcall_UV_Trans_V(DrResMdoMat* mat, float* work, float value) {
    work[7] = value;
}

void DrMdoAnim::animcall_UV_Rot(DrResMdoMat*, float* work, float value) {
    float rad = value * 0.0174532924f;
    float scaleU = work[0];
    float scaleV = work[5];
    float s = sinf(rad);
    float c = cosf(rad);
    work[0] = scaleU * c;
    work[1] = scaleV * s;
    work[4] = -(scaleU * s);
    work[5] = scaleV * c;
    work[3] += c * -0.5f - s * 0.5f + 0.5f;
    work[7] += s * 0.5f + c * -0.5f + 0.5f;
}

void DrMdoAnim::animcall_WorkFloat1(DrResMdoMat* mat, float* work, float value) {
    work[0] = value;
}

void DrMdoAnim::animcall_MatAlpha(DrResMdoMat* mat, float* work, float value) {
    mat->setAlpha(value);
}

void DrMdoAnim::animcall_MatColorR(DrResMdoMat* mat, float* work, float value) {
    mat->m_color[0] = value;
}

void DrMdoAnim::animcall_MatColorG(DrResMdoMat* mat, float* work, float value) {
    mat->m_color[1] = value;
}

void DrMdoAnim::animcall_MatColorB(DrResMdoMat* mat, float* work, float value) {
    mat->m_color[2] = value;
}

void DrMdoAnim::anmNodeParm_TranX(mm::Vec3* srt, float value) {
    srt[0].x = value;
}

void DrMdoAnim::anmNodeParm_TranY(mm::Vec3* srt, float value) {
    srt[0].y = value;
}

void DrMdoAnim::anmNodeParm_TranZ(mm::Vec3* srt, float value) {
    srt[0].z = value;
}

void DrMdoAnim::anmNodeParm_RotX(mm::Vec3* srt, float value) {
    srt[1].x = value;
}

void DrMdoAnim::anmNodeParm_RotY(mm::Vec3* srt, float value) {
    srt[1].y = value;
}

void DrMdoAnim::anmNodeParm_RotZ(mm::Vec3* srt, float value) {
    srt[1].z = value;
}

void DrMdoAnim::anmNodeParm_SclX(mm::Vec3* srt, float value) {
    srt[2].x = value;
}

void DrMdoAnim::anmNodeParm_SclY(mm::Vec3* srt, float value) {
    srt[2].y = value;
}

void DrMdoAnim::anmNodeParm_SclZ(mm::Vec3* srt, float value) {
    srt[2].z = value;
}

void (*DrMdoAnim::s_pCallAnim[10])(DrResMdoMat*, float*, float) = {
    &DrMdoAnim::animcall_UV_Scr_U,
    &DrMdoAnim::animcall_UV_Scr_V,
    &DrMdoAnim::animcall_UV_Trans_U,
    &DrMdoAnim::animcall_UV_Trans_V,
    &DrMdoAnim::animcall_UV_Rot,
    &DrMdoAnim::animcall_WorkFloat1,
    &DrMdoAnim::animcall_MatAlpha,
    &DrMdoAnim::animcall_MatColorR,
    &DrMdoAnim::animcall_MatColorG,
    &DrMdoAnim::animcall_MatColorB,
};

void (*DrMdoAnim::s_pCallAnmNode[9])(mm::Vec3*, float) = {
    &DrMdoAnim::anmNodeParm_TranX,
    &DrMdoAnim::anmNodeParm_TranY,
    &DrMdoAnim::anmNodeParm_TranZ,
    &DrMdoAnim::anmNodeParm_RotX,
    &DrMdoAnim::anmNodeParm_RotY,
    &DrMdoAnim::anmNodeParm_RotZ,
    &DrMdoAnim::anmNodeParm_SclX,
    &DrMdoAnim::anmNodeParm_SclY,
    &DrMdoAnim::anmNodeParm_SclZ,
};

}  // namespace ml
