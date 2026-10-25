#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrFogObjGbl.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrMdoCtlDammy.h"
#include "classes/ml/DrMdoCtlSeamAll.h"
#include "classes/ml/DrMdoMat.h"
#include "classes/ml/DrMdoZSortObj.h"
#include "grlib/CGLibCtl.h"
#include "math.h"
#include "mm/Math.h"
#include "ml/DrEnvironmentAnim.h"
#include "ml/DrIniSys.h"
#include "ml/DrMdoAnim.h"
#include "ml/DrMdoSetup.h"
#include "ml/DrPixlDeferred.h"
#include "ml/DrPixlMan.h"
#include "ml/DrPixlPostMan.h"
#include "ml/DrPixlPostObjCubeMapIBL.h"
#include "ml/DrPixlPostParm.h"
#include "ml/DrResMdoMat.h"
#include "ml/MdoWrkMatRes.h"
#include "ml/MdsMatInfoHeader.h"

namespace ml {

void DrMdoCtlDammy::resourceInit() {}

void DrMdoCtlDammy::update() {}

void DrMdoCtlDammy::dispOffUpdate() {}

void DrMdoCtlSeamAll::debugRender() {}

int DrMdoMat::getVanishEffectMax() const {
    if (m_pWrkMatRes == nullptr) {
        return 0;
    }
    const MdoMdlData* mdl = m_pWrkMatRes->m_pMdlData;
    if (mdl == nullptr) {
        return 0;
    }
    if ((mdl->m_flags & 0x2000) == 0) {
        return 0;
    }
    return mdl->m_vanishEffectMax > 1 ? mdl->m_vanishEffectMax : 1;
}

MdoVanishEffectWrk* DrMdoMat::getVanishEffectWrk(unsigned int index, unsigned int bank) {
    if (m_pWrkMatRes == nullptr) {
        return nullptr;
    }
    if (m_pWrkMatRes->m_pMdlData == nullptr) {
        return nullptr;
    }
    if (m_pWrkMatRes->m_pVanishEffectWrk == nullptr) {
        return nullptr;
    }
    return &m_pWrkMatRes->m_pVanishEffectWrk[index * 3 + bank];
}

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

void DrMdoMat::matCall_OutLineVal(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    DrPixlPostParm* parm = m_pDrMan->m_postParm[m_pDrMan->m_postParmIdx];
    float far = parm->m_outLineFar;
    float near = parm->m_outLineNear;
    far = far > near ? far : near;
    float range = far - near;
    range = range > 0.01f ? range : 0.01f;
    float t = mm::clamp((m_outLineDist - near) / range, 0.0f, 1.0f);
    *dst = parm->m_outLineScale * t;
}

void DrMdoMat::matCall_WaterFog(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* uni = m_pWrkMatRes->m_pUniformVal;
    float* mat = m_pWrkMatRes->m_pMatVal;
    unsigned int idx = info->m_uniformOfs + slot;
    float* dst = &uni[idx];
    float* src = &mat[idx];
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    float fog = m_pDrMan->m_pixlMan->m_objTbl->m_postMan->m_waterFog - 0.05f;
    fog = fog > 0.0f ? fog : 0.0f;
    dst[9] = mm::clamp(fog / 0.95f, 0.0f, 1.0f);
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

void DrMdoSetup::varStTex_ColorTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(0)->m_pTexture, location);
}

void DrMdoSetup::varStTex_NormalTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(2)->m_pTexture, location);
}

void DrMdoSetup::varStTex_LightTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(4);
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(15)->m_pTexture, location);
}

void DrMdoSetup::varStTex_DepthTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(4)->m_pTexture, location);
}

void DrMdoSetup::varStTex_RefTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
}

void DrMdoSetup::varStTex_ShadowMap(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibTextureBuffer* tex = m_pDrMan->m_pixlMan->m_objTbl->m_deferred->getShadowMapTexture();
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(*tex, location);
}

void DrMdoSetup::varStTex_AvatarFaceMap1(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    m_pDrMan->m_pixlMan->m_objTbl->m_deferred->getShadowMapTexture();
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(*m_pWrkMatRes->m_pAvatarTbl->m_faceTex[0], location);
}

void DrMdoSetup::varStTex_Capture1(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    bool valid = pixl->m_cate[1].m_capture != nullptr;
    ap->beginTexSampling(2, 1);
    if (valid) {
        ap->setTexture(*pixl->m_cate[1].m_capture->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Capture2(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    ap->beginTexSampling(2, 1);
    if (pixl->m_cate[2].m_capture != nullptr) {
        ap->setTexture(*pixl->m_cate[2].m_capture->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Capture3(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    ap->beginTexSampling(2, 1);
    if (pixl->m_cate[3].m_capture != nullptr) {
        ap->setTexture(*pixl->m_cate[3].m_capture->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Capture4(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    ap->beginTexSampling(2, 1);
    if (pixl->m_capture4 != nullptr) {
        ap->setTexture(*pixl->m_capture4->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_RefractionMap(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    grlib::CGLibRenderTarget* obj = pixl->m_objTbl->m_postMan->m_refraction;
    ap->beginTexSampling(2, 1);
    if (obj != nullptr) {
        ap->setTexture(*obj->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_ColorDepTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(0)->m_pTexture, location);
}

void DrMdoSetup::varStTex_AvatarFaceMap2(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(*m_pWrkMatRes->m_pAvatarTbl->m_faceTex[1], location);
}

void DrMdoSetup::varStTex_AvatarEyeTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->beginTexSampling(2, 1);
    ap->setMipMapOn(*m_pWrkMatRes->m_pAvatarTbl->m_eyeTex);
    ap->setTexture(*m_pWrkMatRes->m_pAvatarTbl->m_eyeTex, location);
}

void DrMdoSetup::varStTex_CaptureMain(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    bool valid = pixl->m_cate[0].m_capture != nullptr;
    ap->beginTexSampling(2, 1);
    if (valid) {
        ap->setTexture(*pixl->m_cate[0].m_capture->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_BaseColorTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(0)->m_pTexture, location);
}

void DrMdoSetup::varStTex_SpecularIBLTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    const grlib::CGLibTextureBuffer* tex;
    if (m_pDrMan->isIBLSkip()) {
        ap->beginCubeTextureSampling(true);
        tex = &m_pDrMan->m_iniSys->m_texture[12];
    } else {
        DrPixlPostObjCubeMapIBL* ibl = m_pDrMan->m_pixlMan->m_objTbl->m_postMan->m_cubeMapIBL;
        ap->beginCubeTextureSampling(true);
        tex = ibl->getPremTexture();
    }
    ap->setTexture(*tex, location);
}

void DrMdoSetup::varStTex_AmbBRDFTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[3], location);
}

void DrMdoSetup::varStTex_ScreenCapTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibRenderTarget* obj = m_pDrMan->m_pixlMan->getPixlObj(5);
    if (obj != nullptr) {
        DrAPCache* ap = m_pDrMan->m_apCache;
        ap->beginTexSampling(2, 1);
        ap->setTexture(*obj->m_pTexture, location);
    }
}

void DrMdoSetup::varStTex_ToonGradTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    grlib::CGLibTextureBuffer* tex = m_pDrMan->m_pixlMan->m_objTbl->m_postMan->getToonGradTex();
    if (tex != nullptr) {
        ap->setTexture(*tex, location);
    }
}

void DrMdoSetup::varStTex_ToonRimTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[6], location);
}

void DrMdoSetup::varStTex_DitherTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    if (info->m_flags & 4) {
        ap->beginTexSampling(0, 1);
        ap->setTexture(*m_pDrMan->m_pixlMan->getDammyWhiteTexObj(), location);
    } else {
        ap->beginTexSampling(2, 0);
        ap->setTexture(m_pDrMan->m_iniSys->m_texture[1], location);
    }
}

void DrMdoSetup::varStTex_RefLightTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
}

void DrMdoSetup::varStTex_VolumeTex00(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->begin3DTextureWarpSampling();
    int idx = 0;
    MdoVanishEffectWrk* wrk = getVanishEffectWrk(matIdx, 2);
    if (wrk != nullptr) {
        idx = wrk->m_volumeTexIdx;
    }
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[idx + 7], location);
}

void DrMdoSetup::varStTex_VolumeTex01(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->begin3DTextureWarpSampling();
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[7], location);
}

void DrMdoSetup::varStTex_GlobalIBLIndexTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
}

void DrMdoSetup::varStTex_BackFaceDepthTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getBackFaceDepthTexture()->m_pTexture, location);
}

void DrMdoSetup::varStTex_DownDepthTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(*m_pDrMan->m_pixlMan->m_objTbl->m_postMan->getDownDepth()->m_pTexture, location);
}

void DrMdoSetup::varStTex_ClusterIdxListTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
}

void DrMdoSetup::varStTex_VelocityTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(3)->m_pTexture, location);
}

void DrMdoSetup::varStTex_RefractionAfterTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    grlib::CGLibRenderTarget* obj = pixl->m_objTbl->m_postMan->m_refraction;
    ap->beginTexSampling(2, 1);
    if (obj != nullptr) {
        ap->setTexture(*obj->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Movie0(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    grlib::CGLibTextureBuffer* tex = pixl->m_movieTex[0];
    if (pixl->m_movieFilter[0]) {
        ap->beginTexSampling(2, 1);
    } else {
        ap->beginTexSampling(2, 0);
    }
    if (tex != nullptr) {
        ap->setMipMapOn(*tex);
        ap->setTexture(*tex, location);
    } else {
        ap->setMipMapOn(*pixl->getDammyTexObj());
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Movie1(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    grlib::CGLibTextureBuffer* tex = pixl->m_movieTex[1];
    if (pixl->m_movieFilter[1]) {
        ap->beginTexSampling(2, 1);
    } else {
        ap->beginTexSampling(2, 0);
    }
    if (tex != nullptr) {
        ap->setMipMapOn(*tex);
        ap->setTexture(*tex, location);
    } else {
        ap->setMipMapOn(*pixl->getDammyTexObj());
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Movie2(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    grlib::CGLibTextureBuffer* tex = pixl->m_movieTex[2];
    if (pixl->m_movieFilter[2]) {
        ap->beginTexSampling(2, 1);
    } else {
        ap->beginTexSampling(2, 0);
    }
    if (tex != nullptr) {
        ap->setMipMapOn(*tex);
        ap->setTexture(*tex, location);
    } else {
        ap->setMipMapOn(*pixl->getDammyTexObj());
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Movie3(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    grlib::CGLibTextureBuffer* tex = pixl->m_movieTex[3];
    if (pixl->m_movieFilter[3]) {
        ap->beginTexSampling(2, 1);
    } else {
        ap->beginTexSampling(2, 0);
    }
    if (tex != nullptr) {
        ap->setMipMapOn(*tex);
        ap->setTexture(*tex, location);
    } else {
        ap->setMipMapOn(*pixl->getDammyTexObj());
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_DiffuseIBL(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(*m_pDrMan->m_pixlMan->getDiffIBLObj()->m_pTexture, location);
}

void DrMdoSetup::varStTex_DownBaseColorTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    grlib::CGLibTextureBuffer* tex;
    if (pixl->m_objTbl->m_postMan->m_waterFog >= 0.05f) {
        tex = pixl->getPixlObj(16)->m_pTexture;
    } else {
        tex = pixl->getDammyTexObj();
    }
    ap->setTexture(*tex, location);
}

void DrMdoSetup::varStTex_AOTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(2)->m_pTexture, location);
}

void DrMdoSetup::varStTex_OrientationTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(0, 0);
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[15], location);
}

void DrMdoSetup::varStTex_FlagWaveTex0(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(0, 1);
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[16], location);
}

void DrMdoSetup::varStTex_FlagWaveTex1(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(0, 1);
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[17], location);
}

void DrMdoSetup::varStTex_EtcTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(1)->m_pTexture, location);
}

void DrMdoSetup::varStTex_ToonDarkGradTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    grlib::CGLibTextureBuffer* tex = m_pDrMan->m_pixlMan->m_objTbl->m_postMan->getToonDarkGradTex();
    if (tex != nullptr) {
        ap->setTexture(*tex, location);
    }
}

void DrMdoSetup::varStImg_BaseColor(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibCtlTexture::setUAVTexture(*m_pDrMan->m_pixlMan->getPixlObj(0)->m_pTexture, location, 0, 0);
}

void DrMdoSetup::varStImg_Etc(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibCtlTexture::setUAVTexture(*m_pDrMan->m_pixlMan->getPixlObj(1)->m_pTexture, location, 0, 0);
}

void DrMdoSetup::varStImg_Normal(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibCtlTexture::setUAVTexture(*m_pDrMan->m_pixlMan->getPixlObj(2)->m_pTexture, location, 0, 0);
}

void DrMdoSetup::varStImg_Velocity(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibCtlTexture::setUAVTexture(*m_pDrMan->m_pixlMan->getPixlObj(3)->m_pTexture, location, 0, 0);
}

void DrMdoSetup::varStImg_ZBuff(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibCtlTexture::setUAVTexture(*m_pDrMan->m_pixlMan->getPixlObj(4)->m_pTexture, location, 0, 0);
}

DrMdoZSortObj::DrMdoZSortObj(void* owner) : m_next(nullptr), m_parent(nullptr), m_owner(owner) {}

void (DrMdoSetup::*DrMdoSetup::s_pStaticTexture[46])(const MdsMatInfoHeader*, unsigned int, unsigned int) = {
    &DrMdoSetup::varStTex_ColorTex,
    &DrMdoSetup::varStTex_NormalTex,
    &DrMdoSetup::varStTex_LightTex,
    &DrMdoSetup::varStTex_DepthTex,
    &DrMdoSetup::varStTex_RefTex,
    &DrMdoSetup::varStTex_ShadowMap,
    &DrMdoSetup::varStTex_AvatarFaceMap1,
    &DrMdoSetup::varStTex_Capture1,
    &DrMdoSetup::varStTex_Capture2,
    &DrMdoSetup::varStTex_Capture3,
    &DrMdoSetup::varStTex_Capture4,
    &DrMdoSetup::varStTex_RefractionMap,
    &DrMdoSetup::varStTex_ColorDepTex,
    &DrMdoSetup::varStTex_AvatarFaceMap2,
    &DrMdoSetup::varStTex_AvatarEyeTex,
    &DrMdoSetup::varStTex_CaptureMain,
    &DrMdoSetup::varStTex_BaseColorTex,
    &DrMdoSetup::varStTex_SpecularIBLTex,
    &DrMdoSetup::varStTex_AmbBRDFTex,
    &DrMdoSetup::varStTex_ScreenCapTex,
    &DrMdoSetup::varStTex_ToonGradTex,
    &DrMdoSetup::varStTex_ToonRimTex,
    &DrMdoSetup::varStTex_DitherTex,
    &DrMdoSetup::varStTex_RefLightTex,
    &DrMdoSetup::varStTex_VolumeTex00,
    &DrMdoSetup::varStTex_VolumeTex01,
    &DrMdoSetup::varStTex_GlobalIBLIndexTex,
    &DrMdoSetup::varStTex_BackFaceDepthTex,
    &DrMdoSetup::varStTex_DownDepthTex,
    &DrMdoSetup::varStTex_ClusterIdxListTex,
    &DrMdoSetup::varStTex_VelocityTex,
    &DrMdoSetup::varStTex_RefractionAfterTex,
    &DrMdoSetup::varStTex_Movie0,
    &DrMdoSetup::varStTex_Movie1,
    &DrMdoSetup::varStTex_Movie2,
    &DrMdoSetup::varStTex_Movie3,
    &DrMdoSetup::varStTex_DiffuseIBL,
    &DrMdoSetup::varStTex_DownBaseColorTex,
    &DrMdoSetup::varStTex_AOTex,
    &DrMdoSetup::varStTex_OrientationTex,
    &DrMdoSetup::varStTex_FlagWaveTex0,
    &DrMdoSetup::varStTex_FlagWaveTex1,
    &DrMdoSetup::varStTex_EtcTex,
    &DrMdoSetup::varStTex_ToonDarkGradTex,
    &DrMdoSetup::fn_710077C23C,
    &DrMdoSetup::fn_710077C294,
};

void (DrMdoSetup::*DrMdoSetup::s_pStaticImage[5])(const MdsMatInfoHeader*, unsigned int, unsigned int) = {
    &DrMdoSetup::varStImg_BaseColor,
    &DrMdoSetup::varStImg_Etc,
    &DrMdoSetup::varStImg_Normal,
    &DrMdoSetup::varStImg_Velocity,
    &DrMdoSetup::varStImg_ZBuff,
};

}  // namespace ml
