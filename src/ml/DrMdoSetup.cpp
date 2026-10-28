#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrFogObjGbl.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrMdoCtlDammy.h"
#include "classes/ml/DrMdoCtlNom.h"
#include "classes/ml/DrMdoCtlPos.h"
#include "classes/ml/DrMdoCtlSeamAll.h"
#include "classes/ml/DrMdoMat.h"
#include "classes/ml/DrMdoZSortObj.h"
#include "classes/ml/DrResMdoSeamWrkBase.h"
#include "classes/ml/DrResMdoSeamWrkMpf.h"
#include "classes/ml/DrShdLgtClustered.h"
#include "classes/ml/DrShdLgtHybrid.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibOneUniformBlock.h"
#include "grlib/CGLibTriUniformBlock.h"
#include "grlib/CGLibUniformArray.h"
#include "math.h"
#include "stddef.h"
#include "ml/DrCalcMan.h"
#include "ml/DrCalcViewWork.h"
#include "ml/DrEnvironmentAnim.h"
#include "ml/DrIniSys.h"
#include "ml/DrMdoAnim.h"
#include "ml/DrMdoCtlMpfAuto.h"
#include "ml/DrMdoCtlMpfWork.h"
#include "ml/DrMdoSetup.h"
#include "ml/DrMdoMpfMan.h"
#include "ml/DrMdoZSortMan.h"
#include "ml/DrPixlDeferred.h"
#include "ml/DrPixlMan.h"
#include "ml/DrPixlPostMan.h"
#include "ml/DrPixlPostObjCubeMapIBL.h"
#include "ml/DrPixlPostParm.h"
#include "ml/DrPixlTileParm.h"
#include "ml/DrResMdoMat.h"
#include "ml/DrResMdoPntAlphaMan.h"
#include "ml/DrResMdoVertex.h"
#include "ml/DrShdDataList.h"
#include "ml/DrShdLgtMan.h"
#include "ml/DrShdMan.h"
#include "ml/DrShdMdoDecExtTbl.h"
#include "ml/MdoWrkMatRes.h"
#include "ml/MdsMatInfoHeader.h"
#include "ml/MdsMatValShaderCate.h"
#include "mm/Math.h"
#include "mtl/MemManager.h"
#include "string.h"

namespace ml {

void DrMdoCtl::setMatrix(const mm::Mat44& matrix) {
    m_matrix = matrix;
}

void DrMdoCtl::setOffsetPos(const mm::Vec3& pos) {
    m_offsetPos = pos;
}

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

void DrMdoMpfMan::begin() {
    m_windScale = 1.0f;
    m_frameWorkUsed = 0;
    m_listCount = 0;
}

void DrMdoMpfMan::addMpfObj() {
    m_mpfObjNum++;
}

bool DrMdoMpfMan::delMpfObj() {
    return --m_mpfObjNum < 1;
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

int DrMdoCtlMpfWork::calcRenderListWork(int objNum, const MdsMpfObjData* objData) {
    int size = objNum * 0x1D0;
    return DrResMdoPntAlphaMan::getWrkSize(128) + size;
}

int DrMdoCtlMpfWork::getObjChk(int idx) {
    return m_pObjWork[idx].m_objChk;
}

void DrMdoCtlMpfAuto::setBuffTbl(_wkMpfAutoBuff** buffTbl, int buffNum) {
    m_pBuffTbl = buffTbl;
    m_buffNum = buffNum;
}

DrMdoCtlMpfWork::DrMdoCtlMpfWork() {}

void DrMdoCtlMpfWork::changeMemWork(const MdsMpfObjData* objData) {
    m_pObjData = objData;
}

void DrMdoCtlMpfWork::auto_fastSet(_wkMpfObjBuff* buff, const _MPFWorkAutoInf* inf, int idx) {
    buff->m_pAutoList = (const _MPFWorkAutoInf**)m_pMpfMan->getFrameWork(sizeof(_wkMpfObjList));
    if (buff->m_pAutoList) {
        buff->m_pAutoList[0] = inf;
        buff->m_pAutoSet = &DrMdoCtlMpfWork::auto_countSet;
        buff->m_num = 1;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

void DrMdoCtlMpfWork::auto_alpha_fastSet(_wkMpfAlphaObjBuff* buff, const _MPFWorkAutoInf* inf, int idx) {
    buff->m_pAutoList = (const _MPFWorkAutoInf**)m_pMpfMan->getFrameWork(offsetof(_wkMpfAlphaObjList, m_alpha));
    if (buff->m_pAutoList) {
        buff->m_pAutoList[0] = inf;
        buff->m_pAutoSet = &DrMdoCtlMpfWork::auto_alpha_countSet;
        buff->m_num = 1;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

void DrMdoCtlMpfWork::mpf_fastSet(_wkMpfObjBuff* buff, const MdsMpfPosData* pos, int idx) {
    buff->m_pPosList = (const MdsMpfPosData**)m_pMpfMan->getFrameWork(sizeof(_wkMpfObjList));
    if (buff->m_pPosList) {
        buff->m_pPosList[0] = pos;
        buff->m_pPosSet = &DrMdoCtlMpfWork::mpf_countSet;
        buff->m_num = 1;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

void DrMdoCtlMpfWork::mpf_alpha_fastSet(_wkMpfAlphaObjBuff* buff, const MdsMpfPosData* pos, int idx, float alpha) {
    _wkMpfAlphaObjList* list = (_wkMpfAlphaObjList*)m_pMpfMan->getFrameWork(sizeof(_wkMpfAlphaObjList));
    buff->m_pPosList = list->m_pos;
    buff->m_pAlpha = list->m_alpha;
    if (buff->m_pPosList) {
        buff->m_pPosList[0] = pos;
        buff->m_pAlpha[0] = alpha * 255.0f;
        buff->m_pPosSet = &DrMdoCtlMpfWork::mpf_alpha_countSet;
        buff->m_num = 1;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}


void DrMdoCtlMpfWork::mpf_countSet(_wkMpfObjBuff* buff, const MdsMpfPosData* pos, int idx) {
    buff->m_pPosList[buff->m_num] = pos;
    if (buff->m_num++ >= 63) {
        buff->m_pPosSet = &DrMdoCtlMpfWork::mpf_changeSet;
    }
}

void DrMdoCtlMpfWork::mpf_changeSet(_wkMpfObjBuff* buff, const MdsMpfPosData* pos, int idx) {
    _wkMpfObjChunk* next = (_wkMpfObjChunk*)m_pMpfMan->getFrameWork(sizeof(_wkMpfObjChunk));
    if (next) {
        next->m_head.m_pPosList = next->m_list.m_pos;
        next->m_list.m_pos[0] = pos;
        next->m_head.m_num = 1;
        next->m_head.m_pPosSet = &DrMdoCtlMpfWork::mpf_countSet;
        next->m_head.m_pNext = 0;
        m_pObjWork[idx].m_pLastBuff = &next->m_head;
        buff->m_pNext = &next->m_head;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

void DrMdoCtlMpfWork::auto_countSet(_wkMpfObjBuff* buff, const _MPFWorkAutoInf* inf, int idx) {
    buff->m_pAutoList[buff->m_num] = inf;
    if (buff->m_num++ >= 63) {
        buff->m_pAutoSet = &DrMdoCtlMpfWork::auto_changeSet;
    }
}

void DrMdoCtlMpfWork::auto_changeSet(_wkMpfObjBuff* buff, const _MPFWorkAutoInf* inf, int idx) {
    _wkMpfObjChunk* next = (_wkMpfObjChunk*)m_pMpfMan->getFrameWork(sizeof(_wkMpfObjChunk));
    if (next) {
        next->m_head.m_pAutoList = next->m_list.m_auto;
        next->m_list.m_auto[0] = inf;
        next->m_head.m_num = 1;
        next->m_head.m_pAutoSet = &DrMdoCtlMpfWork::auto_countSet;
        next->m_head.m_pNext = 0;
        m_pObjWork[idx].m_pLastBuff = &next->m_head;
        buff->m_pNext = &next->m_head;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

void DrMdoCtlMpfWork::mpf_alpha_countSet(_wkMpfAlphaObjBuff* buff, const MdsMpfPosData* pos, int idx, float alpha) {
    buff->m_pPosList[buff->m_num] = pos;
    buff->m_pAlpha[buff->m_num] = alpha * 255.0f;
    if (buff->m_num++ >= 15) {
        buff->m_pPosSet = &DrMdoCtlMpfWork::mpf_alpha_changeSet;
    }
}

void DrMdoCtlMpfWork::mpf_alpha_changeSet(_wkMpfAlphaObjBuff* buff, const MdsMpfPosData* pos, int idx, float alpha) {
    _wkMpfAlphaObjChunk* next = (_wkMpfAlphaObjChunk*)m_pMpfMan->getFrameWork(sizeof(_wkMpfAlphaObjChunk));
    if (next) {
        next->m_head.m_pPosList = next->m_list.m_pos;
        next->m_head.m_pAlpha = next->m_list.m_alpha;
        next->m_list.m_pos[0] = pos;
        next->m_list.m_alpha[0] = alpha * 255.0f;
        next->m_head.m_num = 1;
        next->m_head.m_pNext = 0;
        next->m_head.m_pPosSet = &DrMdoCtlMpfWork::mpf_alpha_countSet;
        m_pObjWork[idx].m_pLastAlphaBuff = &next->m_head;
        buff->m_pNext = &next->m_head;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

void DrMdoCtlMpfWork::auto_alpha_countSet(_wkMpfAlphaObjBuff* buff, const _MPFWorkAutoInf* inf, int idx) {
    buff->m_pAutoList[buff->m_num] = inf;
    if (buff->m_num++ >= 15) {
        buff->m_pAutoSet = &DrMdoCtlMpfWork::auto_alpha_changeSet;
    }
}

void DrMdoCtlMpfWork::auto_alpha_changeSet(_wkMpfAlphaObjBuff* buff, const _MPFWorkAutoInf* inf, int idx) {
    _wkMpfAlphaObjChunk* next = (_wkMpfAlphaObjChunk*)m_pMpfMan->getFrameWork(offsetof(_wkMpfAlphaObjChunk, m_list.m_alpha));
    if (next) {
        next->m_head.m_pAutoList = next->m_list.m_auto;
        next->m_list.m_auto[0] = inf;
        next->m_head.m_num = 1;
        next->m_head.m_pNext = 0;
        next->m_head.m_pAutoSet = &DrMdoCtlMpfWork::auto_alpha_countSet;
        m_pObjWork[idx].m_pLastAlphaBuff = &next->m_head;
        buff->m_pNext = &next->m_head;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

// m_stateFlags bits 0..5 select the passes an object draws in (bit 3 light pre-pass, bit 1 GBuff, bit 2
// refraction, bit 5 special alpha, bit 6 thickness, bit 20 z pre-pass, bits 25..27 last/fast/cloud-back alpha).
void DrMdoCtlNom::callShadowCacheUpdate(unsigned long bits) {
    m_shadowCacheBits &= ~bits;
}

void DrMdoCtlNom::callZSortGBuffRender() {
    if (m_stateFlags & 0x2) {
        nomCallRender(1);
    }
}

void DrMdoCtlNom::callZSortNomRefractionRender() {
    if (m_stateFlags & 0x4) {
        nomCallRender(2);
    }
}

void DrMdoCtlNom::callZSortLightPrePassRender() {
    if (m_stateFlags & 0x8) {
        nomCallRender(3);
    }
}

void DrMdoCtlNom::callZSortNomSpAlphaRender() {
    if (m_stateFlags & 0x20) {
        nomCallRender(5);
    }
}

void DrMdoCtlNom::callLastAlphaNomRender() {
    if (m_stateFlags & 0x2000000) {
        lastAlphaCallRender();
    }
}

void DrMdoCtlNom::callFastAlphaNomRender() {
    if (m_stateFlags & 0x4000000) {
        fastAlphaCallRender();
    }
}

void DrMdoCtlNom::callCldBackAlphaNomRender() {
    if (m_stateFlags & 0x8000000) {
        cldBackAlphaCallRender();
    }
}

void DrMdoCtlPos::callZpreePassRenderPosAll() {
    if (m_stateFlags & 0x100000) {
        createZBuffRenderDisplayList();
    }
}

void DrMdoCtlPos::callThicknessRenderFirstPosAll() {
    if (m_stateFlags & 0x40) {
        createThicknessRenderDisplayListSub(true);
    }
}

void DrMdoCtlPos::callThicknessRenderSecondPosAll() {
    if (m_stateFlags & 0x40) {
        createThicknessRenderDisplayListSub(false);
    }
}

void DrMdoCtlPos::callRenderPosAll() {
    if (m_stateFlags & 0x1) {
        m_renderPass = 0;
        m_renderTech = 0;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        callPosRender(0x1);
    }
}

void DrMdoCtlPos::callRefractionRenderPosAll() {
    if (m_stateFlags & 0x4) {
        m_renderPass = 2;
        m_renderTech = 8;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        callPosRender(0x4);
    }
}

void DrMdoCtlPos::callGBuffRenderPosAll() {
    if (m_stateFlags & 0x2) {
        m_renderPass = 1;
        m_renderTech = 7;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        callPosRender(0x8);
    }
}

void DrMdoCtlPos::callLightPrePassRenderPosAll() {
    if (m_stateFlags & 0x8) {
        m_renderPass = 3;
        m_renderTech = 4;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        callPosRender(0x20);
    }
}

void DrMdoCtlPos::callAlphaRenderPosAll() {
    if (m_stateFlags & 0x10) {
        m_renderPass = 4;
        m_renderTech = 1;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        callPosRender(0x2);
    }
}

void DrMdoCtlPos::callSpAlphaRenderPosAll() {
    if (m_stateFlags & 0x20) {
        m_renderPass = 5;
        m_renderTech = 1;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        callPosRender(0x40);
    }
}

void DrMdoCtlSeamAll::callZPrePassSeamAll() {
    if (!(m_stateFlags & 0x100000) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderTech = 0;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pDrMan->m_apCache->setupCulling(static_cast<DrApCullType>(2));
    createBaseZPrePassDisplayList();
    createInstZPrePassDisplayList();
    createMpfZPrePassDisplayList();
    createLowZPrePassDisplayList();
}

void DrMdoCtlSeamAll::callThicknessFirstSeamAll() {
    if (!(m_stateFlags & 0x40) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderTech = 0;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pDrMan->m_apCache->beginThicknessRenderFirst();
    m_pDrMan->m_apCache->setupCulling(static_cast<DrApCullType>(1));
    createBaseThicknesPassDisplayList(true);
    createInstThicknessPassDisplayList(true);
}

void DrMdoCtlSeamAll::callThicknessSecondSeamAll() {
    if (!(m_stateFlags & 0x40) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderTech = 0;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pDrMan->m_apCache->beginThicknessRenderSecond();
    m_pDrMan->m_apCache->setupCulling(static_cast<DrApCullType>(0));
    createBaseThicknesPassDisplayList(false);
    createInstThicknessPassDisplayList(false);
}

void DrMdoCtlSeamAll::callRenderSeamAll() {
    if (!(m_stateFlags & 0x1) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 0;
    m_renderTech = 0;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    renderSeamInstMap(0);
    renderSeamBaseMap(0);
    if (m_seamFlags & 0x8) {
        DrMan::get()->m_tileParm->begin(static_cast<DrPixlTileParm::TileType>(3));
        createMpfMapDisplayList();
        DrMan::get()->m_tileParm->end(static_cast<DrPixlTileParm::TileType>(3));
    }
    renderSeamLowMap(0);
}

void DrMdoCtlSeamAll::callGBuffRenderSeamAll() {
    if (!(m_stateFlags & 0x2) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 1;
    m_renderTech = 7;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    renderSeamInstMap(1);
    renderSeamBaseMap(1);
    renderSeamLowMap(1);
}

void DrMdoCtlSeamAll::callLightPrePassRenderSeamAll() {
    if (!(m_stateFlags & 0x8) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 3;
    m_renderTech = 4;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    renderSeamBaseMap(3);
    renderSeamInstMap(3);
    renderSeamLowMap(3);
}

void DrMdoCtlSeamAll::callAlphaRenderSeamAll() {
    if (!(m_stateFlags & 0x10) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 4;
    m_renderTech = 1;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    renderSeamLowMap(4);
    renderSeamBaseMap(4);
    renderSeamInstMap(4);
}

void DrMdoCtlSeamAll::callSpAlphaRenderSeamAll() {
    if (!(m_stateFlags & 0x20) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 5;
    m_renderTech = 1;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    renderSeamLowMap(5);
    renderSeamBaseMap(5);
    renderSeamInstMap(5);
}

void DrMdoCtlSeamAll::callRefractionRenderSeamAll() {
    if (!(m_stateFlags & 0x4) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 2;
    m_renderTech = 8;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    renderSeamInstMap(2);
    renderSeamBaseMap(2);
    renderSeamLowMap(2);
}

void DrMdoCtlSeamAll::callRenderSeamEnvMap() {
    if (!(m_stateFlags & 0x1) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 0;
    m_renderTech = 0;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    DrMdoCtlSeamEnvMap::callRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callGBuffRenderSeamEnvMap() {
    if (!(m_stateFlags & 0x2) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 1;
    m_renderTech = 7;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    DrMdoCtlSeamEnvMap::callGBuffRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callLightPrePassRenderSeamEnvMap() {
    if (!(m_stateFlags & 0x8) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 3;
    m_renderTech = 4;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    DrMdoCtlSeamEnvMap::callLightPrePassRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callAlphaRenderSeamEnvMap() {
    if (!(m_stateFlags & 0x10) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 4;
    m_renderTech = 1;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    DrMdoCtlSeamEnvMap::callAlphaRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callSpAlphaRenderSeamEnvMap() {
    if (!(m_stateFlags & 0x20) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 5;
    m_renderTech = 1;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    DrMdoCtlSeamEnvMap::callSpAlphaRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callRefractionRenderSeamEnvMap() {
    if (!(m_stateFlags & 0x4) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 2;
    m_renderTech = 8;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    DrMdoCtlSeamEnvMap::callRefractionRenderSeamEnvMap();
}

void DrMdoCtlSeamRead::waitBaseMapStream(_wkSeamReadCall* call, bool ok) {
    if (ok) {
        initBaseMapParts(call->m_pBase);
        m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitLowMdlStream(_wkSeamReadCall* call, bool ok) {
    if (ok) {
        initLowMapParts(call->m_pLow);
        m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitInstMapStream(_wkSeamReadCall* call, bool ok) {
    if (ok) {
        initInstMapParts(call->m_pInst, call->m_pInst2);
        m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitEnvMdlStream(_wkSeamReadCall* call, bool ok) {
    if (ok) {
        initEnvMapParts(call->m_pEnv);
        m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitBaseVertexStream(_wkSeamReadCall* call, bool ok) {
    DrResMdoSeamWrkBase* wrk = call->m_pBase;
    if (ok) {
        wrk->setVertexCache(call->m_cacheIdx, call->m_pMemObj, call->m_cacheParam, this);
        m_readWaitBits &= ~(1 << call->m_readIdx);
        m_pBaseVertexRead = 0;
    } else {
        wrk->m_cacheFlags |= 0x10;
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitMpfEtcStream(_wkSeamReadCall* call, bool ok) {
    DrResMdoSeamWrkMpf* wrk = call->m_pMpf;
    if (ok) {
        wrk->setEtcMpfCache(call->m_cacheIdx, call->m_pMemObj);
        m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        wrk->m_cacheFlags |= 1;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitMpfPoliStream(_wkSeamReadCall* call, bool ok) {
    DrResMdoSeamWrkMpf* wrk = call->m_pMpf;
    if (ok) {
        wrk->setMpfPoliCache(call->m_cacheIdx, call->m_pMemObj);
        m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        wrk->m_cacheFlags |= 1;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}



void DrMdoSetup::uniformBlock_no(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {}

void DrMdoSetup::uniformBlock_Static(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Material(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pWrkMatRes->m_pMatUniformArray->m_pArray[static_cast<unsigned int>(matIdx)].setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Light(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_calcMan->m_pViewWork->m_lightBlock.setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Mdl(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pWrkMatRes->m_pTriUniformArray->m_pArray[static_cast<unsigned int>(mdlIdx)].setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Bone(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_shdMan->m_dataList->m_boneStmOut.setStorageBuffer(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_AvatarChar(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pWrkMatRes->m_pAvatarTbl->m_charBlock->setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_AvatarDoll(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pWrkMatRes->m_pAvatarTbl->m_dollBlock->setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Fog(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_calcMan->m_pViewWork->m_fogBlock.setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Toon(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_calcMan->m_pViewWork->m_toonBlock.setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_VolTexCalc(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pWrkMatRes->m_pVolTexUniformArray->m_pArray[texIdx].setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_GlobalIBL(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_pixlMan->m_objTbl->m_postMan->m_cubeMapIBL->setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_ClusterParam(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    DrShdLgtClustered* clustered = m_pDrMan->m_shdMan->m_lgtMan->getHybridLight()->m_pClustered;
    unsigned int location = m_pDecExtTbl->getValGlobalParam(paramIdx);
    if (cate->m_flags & 1) {
        clustered->setParamStorageBuffer(m_pDrMan->m_postParmIdx, location);
    } else {
        clustered->setParamUniformBlock(m_pDrMan->m_postParmIdx, location);
    }
}

void DrMdoSetup::uniformBlock_ClusterPntList(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    DrShdLgtClustered* clustered = m_pDrMan->m_shdMan->m_lgtMan->getHybridLight()->m_pClustered;
    unsigned int location = m_pDecExtTbl->getValGlobalParam(paramIdx);
    if (cate->m_flags & 1) {
        clustered->setPntLightStorageBuffer(m_pDrMan->m_postParmIdx, location);
    } else {
        clustered->setPntLightUniformBlock(m_pDrMan->m_postParmIdx, location);
    }
}

void DrMdoSetup::uniformBlock_ClusterSptList(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    DrShdLgtClustered* clustered = m_pDrMan->m_shdMan->m_lgtMan->getHybridLight()->m_pClustered;
    unsigned int location = m_pDecExtTbl->getValGlobalParam(paramIdx);
    if (cate->m_flags & 1) {
        clustered->setSptLightStorageBuffer(m_pDrMan->m_postParmIdx, location);
    } else {
        clustered->setSptLightUniformBlock(m_pDrMan->m_postParmIdx, location);
    }
}

void DrMdoSetup::uniformBlock_ClusterIdxList(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    DrShdLgtClustered* clustered = m_pDrMan->m_shdMan->m_lgtMan->getHybridLight()->m_pClustered;
    unsigned int location = m_pDecExtTbl->getValGlobalParam(paramIdx);
    if (cate->m_flags & 1) {
        clustered->setLightListStorageBuffer(m_pDrMan->m_postParmIdx, location);
    } else {
        clustered->setLightListUniformBlock(m_pDrMan->m_postParmIdx, location);
    }
}

void DrMdoSetup::uniformBlock_ClusterAddressList(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    DrShdLgtClustered* clustered = m_pDrMan->m_shdMan->m_lgtMan->getHybridLight()->m_pClustered;
    unsigned int location = m_pDecExtTbl->getValGlobalParam(paramIdx);
    if (cate->m_flags & 1) {
        clustered->setPointerListStorageBuffer(m_pDrMan->m_postParmIdx, location);
    } else {
        clustered->setPointerListUniformBlock(m_pDrMan->m_postParmIdx, location);
    }
}

void DrMdoSetup::uniformBlock_RimBloomCalc(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pWrkMatRes->m_pRimBloomUniformArray->m_pArray[static_cast<unsigned int>(mdlIdx)].setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Toon2(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_calcMan->m_pViewWork->m_toon2Block.setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}
// Last alpha objects: buckets 0..3.
void DrMdoZSortMan::setViewWorldPosLastAlpha(DrMdoZSortObj* obj, const mm::Vec3& pos) {
    float dx = pos.x - m_viewPos.x;
    float dy = pos.y - m_viewPos.y;
    float dz = pos.z - m_viewPos.z;
    float dist = sqrtf(dx * dx + dy * dy + dz * dz) / m_sortFar;
    if (dist >= 1.0f) {
        stockObj(obj, 3);
    } else if (dist <= 0.001f) {
        stockObj(obj, 0);
    } else {
        int idx = static_cast<int>(powf(dist, m_sortRate) * 4.0f);
        stockObj(obj, idx > 3 ? 3 : (idx < 0 ? 0 : idx));
    }
}

DrMdoZSortMan::DrMdoZSortMan(DrMan* drMan)
    : m_pDrMan(drMan), m_pBuff(nullptr), m_pSpecial(nullptr), m_sortFar(300.0f), m_sortRate(0.8f) {
    m_pBuff = mtl::MemManager::allocate(drMan->m_workHandle, sizeof(DrMdoZSortObj*) * SORT_MAX * 2 + SORT_MAX / 8, 0x20,
                                        false, "no name", 0);
    m_top = static_cast<DrMdoZSortObj**>(m_pBuff);
    m_last = m_top + SORT_MAX;
    m_useBits = reinterpret_cast<unsigned int*>(m_last + SORT_MAX);
}

DrMdoZSortMan::~DrMdoZSortMan() {
    if (m_pBuff != nullptr) {
        mtl::MemManager::deallocate(m_pBuff, 0, false);
        m_pBuff = nullptr;
    }
}

void DrMdoZSortMan::beginViewWorld() {
    const mm::Vec3& viewPos = m_pDrMan->m_calcMan->m_pViewWork->m_viewPos;
    memset(m_useBits, 0, SORT_MAX / 8);
    m_viewPos.x = viewPos.x;
    m_viewPos.y = viewPos.y;
    m_viewPos.z = viewPos.z;
    m_head = nullptr;
    m_tail = nullptr;
    m_pSpecial = nullptr;
}

void DrMdoZSortMan::setViewCloud(DrMdoZSortObj* obj) {
    stockObj(obj, SORT_CLOUD);
}

void DrMdoZSortMan::endViewWorld() {
    for (int i = 0; i < SORT_MAX; i++) {
        if (m_useBits[i >> 5] & (1 << (i & 0x1F))) {
            if (m_head != nullptr) {
                m_tail->setNext(m_top[i]);
                m_top[i]->setParent(m_tail);
            } else {
                m_head = m_top[i];
            }
            m_tail = m_last[i];
        }
    }
}

void DrMdoZSortMan::viewSetupRender() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->SetupRender();
    }
    for (DrMdoZSortObj* obj = m_head; obj != nullptr; obj = obj->getNext()) {
        obj->SetupRender();
    }
}

void DrMdoZSortMan::viewZPrepassRender() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->ZPrepassRender();
    }
    for (DrMdoZSortObj* obj = m_head; obj != nullptr; obj = obj->getNext()) {
        obj->ZPrepassRender();
    }
}

void DrMdoZSortMan::viewThicknessRenderFirst() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->ThicknessRenderFirst();
    }
    for (DrMdoZSortObj* obj = m_head; obj != nullptr; obj = obj->getNext()) {
        obj->ThicknessRenderFirst();
    }
}

void DrMdoZSortMan::viewThicknessRenderSecond() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->ThicknessRenderSecond();
    }
    for (DrMdoZSortObj* obj = m_head; obj != nullptr; obj = obj->getNext()) {
        obj->ThicknessRenderSecond();
    }
}

void DrMdoZSortMan::viewRender() {
    for (DrMdoZSortObj* obj = m_head; obj != nullptr; obj = obj->getNext()) {
        obj->render();
    }
    if (m_pSpecial != nullptr) {
        m_pSpecial->render();
    }
}

void DrMdoZSortMan::viewGBuffRender() {
    for (DrMdoZSortObj* obj = m_head; obj != nullptr; obj = obj->getNext()) {
        obj->GBuffRender();
    }
    if (m_pSpecial != nullptr) {
        m_pSpecial->GBuffRender();
    }
}

void DrMdoZSortMan::viewLightPrePassRender() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->lightPrePassRender();
    }
    // back to front
    for (DrMdoZSortObj* obj = m_tail; obj != nullptr; obj = obj->getParent()) {
        obj->lightPrePassRender();
    }
}

void DrMdoZSortMan::viewAlphaRender() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->alphaRender();
    }
    // back to front
    for (DrMdoZSortObj* obj = m_tail; obj != nullptr; obj = obj->getParent()) {
        obj->alphaRender();
    }
}

void DrMdoZSortMan::viewSpAlphaRender() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->spAlphaRender();
    }
    // back to front
    for (DrMdoZSortObj* obj = m_tail; obj != nullptr; obj = obj->getParent()) {
        obj->spAlphaRender();
    }
}

void DrMdoZSortMan::viewRefractionRender() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->refractionRender();
    }
    // back to front
    for (DrMdoZSortObj* obj = m_tail; obj != nullptr; obj = obj->getParent()) {
        obj->refractionRender();
    }
}

}  // namespace ml
