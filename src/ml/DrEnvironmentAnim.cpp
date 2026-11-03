// xbrd's library (its vector.h, algorithm.h and fixed_list.h assertions cite xbrd's mcl path)
#define MM_LIB_FROM_XBRD
#include "classes/ml/DrLightObj.h"
#include "classes/ml/DrLightObjDir.h"
#include "classes/ml/DrLightObjPnt.h"
#include "classes/ml/DrLightObjSpt.h"
#include "classes/ml/DrEnvironmentObj.h"
#include "classes/ml/DrEnvironmentObjLgt.h"
#include "ml/DrPixlMan.h"
#include "ml/DrPixlShadowMan.h"
#include "ml/DrAPGxType.h"
#include "ml/DrShdLgtGlobalIBL.h"
#include "ml/DrShdLgtMan.h"
#include "classes/ml/DrFogObjGbl.h"
#include "classes/ml/DrGlobalIBLPack.h"
#include "ml/DrFogMan.h"
#include "ml/DrLightMan.h"
#include "classes/ml/irrvol/MemHandlebaseAllocator.h"
#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrEnvironmentObj.h"
#include "classes/ml/DrEnvironmentObjLgt.h"
#include "classes/ml/DrFogObjGbl.h"
#include "classes/ml/DrGlobalIBLPack.h"
#include "classes/ml/DrLightObj.h"
#include "classes/ml/DrLightObjAmb.h"
#include "classes/ml/DrLightObjDir.h"
#include "classes/ml/DrLightObjLocalIBL.h"
#include "classes/ml/DrLightObjPnt.h"
#include "classes/ml/DrLightObjSpt.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrMdoCtlDammy.h"
#include "classes/ml/DrMdoCtlSeamAll.h"
#include "classes/ml/DrMdoMat.h"
#include "classes/ml/DrMdoZSortObj.h"
#include "classes/ml/FileResTh.h"
#include "classes/ml/irrvol/MemHandlebaseAllocator.h"
#include "grlib/CGLibCtl.h"
#include "math.h"
#include "ml/CriticalSection.h"
#include "ml/DrAPGxType.h"
#include "ml/DrCalcMan.h"
#include "ml/DrCalcViewWork.h"
#include "ml/DrEnvColiMan.h"
#include "ml/DrEnvironmentAnim.h"
#include "ml/DrEnvironmentLgtList.h"
#include "ml/DrEnvironmentMan.h"
#include "ml/DrFogMan.h"
#include "ml/DrIBLColiAcc.h"
#include "ml/DrIBLObj.h"
#include "ml/DrIniSys.h"
#include "ml/DrIrrVolMan.h"
#include "ml/irrvol/DrIrrVolCascade.h"
#include "ml/DrLightObjGlobalIBL.h"
#include "ml/DrLightMan.h"
#include "ml/DrMdoAnim.h"
#include "ml/DrMdoSetup.h"
#include "ml/DrPixlDeferred.h"
#include "ml/DrPixlMan.h"
#include "ml/DrPixlPostMan.h"
#include "ml/DrPixlPostObjCubeMapIBL.h"
#include "ml/DrPixlPostParm.h"
#include "ml/DrPixlShadowCacheMan.h"
#include "ml/DrPixlShadowMan.h"
#include "ml/DrResMdoMat.h"
#include "ml/DrResQueryObj.h"
#include "ml/DrResWrkClipList.h"
#include "ml/DrShdLgtGlobalIBL.h"
#include "ml/DrShdLgtMan.h"
#include "ml/DrShdMan.h"
#include "ml/MdoWrkMatRes.h"
#include "ml/MdsMatInfoHeader.h"
#include "ml/MlMem.h"
#include "mm/Math.h"
#include "mm/Vec3NA.h"
#include "mtl/MemManager.h"

namespace ml {

void DrLightObjPnt::setMat(const mm::Mat44& mtx) {
    m_mat = mtx;
    m_pos = m_mat.getTrans();
}

void DrLightObjPnt::setPos(const mm::Vec3& pos) {
    m_pos = pos;
    m_mat.setTransRow(pos);
}

void DrLightObjSpt::setPos(const mm::Vec3& pos) {
    m_pos = pos;
    m_mat.setTransRow(pos);
}

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

DrFogObjGbl::~DrFogObjGbl() {}

void DrFogObjGbl::update() {}

// --- DrEnvironmentObj ---
void DrEnvironmentObj::release() {
    m_flags |= FLAG_RELEASE << DrMan::s_nDblStockIdx;
}

float DrEnvironmentObj::getFrame() const {
    return m_frame;
}

float DrEnvironmentObj::getMaxFrame() const {
    return m_maxFrame;
}

void DrEnvironmentObj::setFrameSpd(float spd) {
    m_frameSpd = spd;
}

float DrEnvironmentObj::getFrameSpd() {
    return m_frameSpd;
}

// --- DrEnvironmentObjLgt ---
DrEnvironmentObjLgt::~DrEnvironmentObjLgt() {
    releaseLgt();
}

void DrEnvironmentObjLgt::resourceInit() {
    setupLgt(m_lgtArg);
}

void DrEnvironmentObjLgt::setupPoint(DrEnvironmentLgtList* list, DrLightObjPnt* light, const LgtObjData* data,
                                     const LgtPosData* pos) {
    mm::Col3 col(data->m_color[0], data->m_color[1], data->m_color[2]);
    float g = col.g * data->m_intensity;
    float r = col.r * data->m_intensity;
    float b = col.b * data->m_intensity;
    const LgtParamData* param =
        reinterpret_cast<const LgtParamData*>(static_cast<const char*>(m_resource) + data->m_paramOfs);
    light->m_color[0] = r;
    light->m_color[1] = g;
    light->m_color[2] = b;
    light->setMat(pos->m_mat);
    light->m_speIntensity = param->m_speIntensity;
    light->m_size = pos->m_range;
    light->m_paramC = param->m_paramC;
    light->m_lightParam = data->m_param == 0.0f ? 1.0f : data->m_param;
    if (data->m_flags & 0x10) {
        light->m_flags |= 0x800;
    }
    if (param->m_kind == 1) {
        light->m_flags |= 2;
    }
    if (data->m_flags2 & 0x10) {
        light->m_flags |= DrLightObj::FLAG_SUBTRACT;
    }
    list->m_light = light;
}

void DrEnvironmentObjLgt::setFrame(float frame) {
    m_frame = frame;
    for (int i = 0; i < m_anim.m_rangeNum; i++) {
        float end = m_anim.m_frameRange[i].m_endFrame;
        m_anim.m_rangeFrame[i] = end < frame ? end : frame;
    }
}

void DrEnvironmentObjLgt::updatePosLgt() {
    unsigned int bitsSize = (m_lgtNum / 32 + 1) * 4;
    memset(m_calcBits, 0, bitsSize + (-bitsSize & 0x1F));
    DrEnvironmentLgtList** renderList = m_renderList;
    m_renderList = m_prevRenderList;
    m_prevRenderList = renderList;
    m_renderList[0] = nullptr;
    m_prevRenderLgtNum = m_renderLgtNum;
    m_renderLgtNum = 0;
    if (m_work2 != nullptr) {
        m_work2->update(m_drMan->m_calcMan->m_pClipMan);
    }
    DrCalcViewWork* work = m_drMan->m_calcMan->m_pViewWork;
    m_frame += m_frameSpd;
    if (m_maxFrame < m_frame) {
        m_frame = 0.0f;
    }
    m_viewPos.x = work->m_viewPos.x - m_offsetPos.x;
    m_viewPos.y = work->m_viewPos.y - m_offsetPos.y;
    m_viewPos.z = work->m_viewPos.z - m_offsetPos.z;
    if (!(m_flags & FLAG_OFS_MATRIX)) {
        if (m_offsetPos.x != m_prevOfsPos.x || m_offsetPos.y != m_prevOfsPos.y || m_offsetPos.z != m_prevOfsPos.z) {
            m_prevOfsPos.x = m_offsetPos.x;
            m_prevOfsPos.y = m_offsetPos.y;
            m_prevOfsPos.z = m_offsetPos.z;
            setupOfsPos();
        }
        calcTreePos(m_posTree, work);
    } else {
        setupCalcMatrix();
        for (int i = 0; i < m_lgtNum; i++) {
            calcLgtObj(i, work);
        }
    }
    DrEnvironmentLgtList** prevList = m_prevRenderList;
    for (int i = 0; i < m_prevRenderLgtNum; i++, prevList++) {
        DrEnvironmentLgtList* list = *prevList;
        int idx = list->m_idx;
        if ((m_calcBits[idx >> 5] & (1 << (idx & 0x1F))) == 0) {
            (this->*s_pCallEnvRelase[list->m_data->m_type])(list->m_light);
        }
    }
    if (m_updateReq & 2) {
        m_lightMan->m_ambColor = m_ambColor;
    }
}

void DrEnvironmentObjLgt::calcTreePos(const LgtPosTreeRange* node, DrCalcViewWork* work) {
    int lgtNum = node->m_lgtNum;
    if (lgtNum != 0) {
        const int* lgt = reinterpret_cast<const int*>(static_cast<const char*>(m_resource) + node->m_lgtOfs);
        for (int i = 0; i < lgtNum; i++) {
            calcLgtObj(*lgt++, work);
        }
    }
    int childNum = node->m_childNum;
    if (childNum != 0) {
        const unsigned short* child =
            reinterpret_cast<const unsigned short*>(static_cast<const char*>(m_resource) + node->m_childOfs);
        for (int i = 0; i < childNum; i++, child++) {
            const LgtPosTreeRange* range = m_posTree + *child;
            if (range->m_max[0] < m_viewPos.x || range->m_min[0] > m_viewPos.x || range->m_max[1] < m_viewPos.y ||
                range->m_min[1] > m_viewPos.y || range->m_max[2] < m_viewPos.z || range->m_min[2] > m_viewPos.z) {
                continue;
            }
            calcTreePos(range, work);
        }
    }
}

void DrEnvironmentObjLgt::calcLgtObj(int idx, DrCalcViewWork* work) {
    DrEnvironmentLgtList* list = &m_lgtList[idx];
    const LgtObjData* data = list->m_data;
    if (data->m_animFlags & 1) {
        unsigned int anim = data->m_animIdx;
        const EnvFrameRange* range = &m_anim.m_frameRange[anim];
        float* frame = &m_anim.m_rangeFrame[anim];
        *frame += m_frameSpd;
        if (*frame > range->m_endFrame) {
            *frame = (range->m_endFrame - *frame) + range->m_loopFrame;
        }
    }
    if (data->m_calcFlags & 4) {
        list->m_rate = 1.0f;
    } else if (!(this->*s_pCallEnvChk[data->m_type])(list, work, data)) {
        return;
    }
    if ((this->*s_pCallCalcEnv[data->m_type])(list, work)) {
        m_calcBits[idx >> 5] |= 1 << (idx & 0x1F);
        list->m_light->update(m_lightMan);
        m_renderList[m_renderLgtNum] = list;
        m_renderLgtNum++;
    }
}

void DrEnvironmentObjLgt::renderLgt() {
    if (!(m_flags & FLAG_HIDE) && m_lgtNum != 0 && m_renderLgtNum != 0) {
        DrShdLgtMan* shdLgtMan = m_drMan->m_shdMan->m_lgtMan;
        DrEnvironmentLgtList** list = m_renderList;
        for (int i = 0; i < m_renderLgtNum; ++i, ++list) {
            DrEnvironmentLgtList* lgt = *list;
            DrLightObj* light = lgt->m_light;
            (this->*s_pCallLgtRender[lgt->m_data->m_type])(light, shdLgtMan);
        }
    }
}

void DrEnvironmentObjLgt::debugRenderLgt() {
    if (m_lgtNum != 0 && m_renderLgtNum != 0) {
        renderLgt();
    }
}

bool DrEnvironmentObjLgt::callback_Chk_Ambinet_Directional(DrEnvironmentLgtList* list, DrCalcViewWork*,
                                                           const LgtObjData* data) {
    if (data->m_flags & 1) {
        const LgtPosData* pos = list->m_posData;
        float dx = m_viewPos.x - pos->m_pos[0];
        float dy = m_viewPos.y - pos->m_pos[1];
        float dz = m_viewPos.z - pos->m_pos[2];
        if (dx * dx + dy * dy + dz * dz > pos->m_radius * pos->m_radius) {
            return false;
        }
    }
    if (data->m_group != 0 && (m_flags & 4) && m_group != data->m_group) {
        return false;
    }
    list->m_rate = 1.0f;
    return true;
}

bool DrEnvironmentObjLgt::callback_Chk_Point(DrEnvironmentLgtList* list, DrCalcViewWork* work, const LgtObjData* data) {
    const LgtPosData* pos = list->m_posData;
    if (pos->m_id != 0) {
        int idx = pos->m_id - 1;
        if ((m_work2->m_work[idx >> 5] & (1 << (idx & 0x1F))) != 0) {
            return false;
        }
    }
    unsigned int dispIdx = pos->m_dispIdx;
    if (dispIdx != 0 && (*(m_drMan->m_dispOffBits + (dispIdx >> 5)) & (1 << (dispIdx & 0x1F))) != 0) {
        return false;
    }
    if (data->m_flags & 1) {
        float dx = m_viewPos.x - pos->m_pos[0];
        float dy = m_viewPos.y - pos->m_pos[1];
        float dz = m_viewPos.z - pos->m_pos[2];
        float dist2 = dx * dx + dy * dy + dz * dz;
        float range = pos->m_radius + pos->m_range;
        if (dist2 > range * range) {
            return false;
        }
        float inner = range * 0.75f;
        if (dist2 > inner * inner) {
            list->m_rate = 1.0f - (sqrtf(dist2) - inner) / (range - inner);
        } else {
            list->m_rate = 1.0f;
        }
    } else {
        list->m_rate = 1.0f;
    }
    if (data->m_group != 0 && (m_flags & 4) && m_group != data->m_group) {
        return false;
    }
    DrLightObjPnt* light = static_cast<DrLightObjPnt*>(list->m_light);
    if (data->m_animFlags & 4) {
        m_anim.calcAnimTransPnt(light, data, m_offsetPos);
    }
    float range = pos->m_range;
    const mm::Vec3& lightPos = light->m_pos;
    return work->m_clipPlane.clipTest(lightPos, range);
}

bool DrEnvironmentObjLgt::callback_Chk_Spot(DrEnvironmentLgtList* list, DrCalcViewWork* work, const LgtObjData* data) {
    const LgtPosData* pos = list->m_posData;
    if (pos->m_id != 0) {
        int idx = pos->m_id - 1;
        if ((m_work2->m_work[idx >> 5] & (1 << (idx & 0x1F))) != 0) {
            return false;
        }
    }
    unsigned int dispIdx = pos->m_dispIdx;
    if (dispIdx != 0 && (*(m_drMan->m_dispOffBits + (dispIdx >> 5)) & (1 << (dispIdx & 0x1F))) != 0) {
        return false;
    }
    if (data->m_flags & 1) {
        float dx = m_viewPos.x - pos->m_pos[0];
        float dy = m_viewPos.y - pos->m_pos[1];
        float dz = m_viewPos.z - pos->m_pos[2];
        float dist2 = dx * dx + dy * dy + dz * dz;
        float range = pos->m_radius + pos->m_range;
        if (dist2 > range * range) {
            return false;
        }
        float inner = range * 0.75f;
        if (dist2 > inner * inner) {
            list->m_rate = 1.0f - (sqrtf(dist2) - inner) / (range - inner);
        } else {
            list->m_rate = 1.0f;
        }
    } else {
        list->m_rate = 1.0f;
    }
    if (data->m_group != 0 && (m_flags & 4) && m_group != data->m_group) {
        return false;
    }
    DrLightObjSpt* light = static_cast<DrLightObjSpt*>(list->m_light);
    if (data->m_animFlags & 4) {
        m_anim.calcAnimTransSpt(light, data, m_offsetPos);
    }
    float range = pos->m_range;
    const mm::Vec3& lightPos = light->m_pos;
    return work->m_clipPlane.clipTest(lightPos, range);
}

bool DrEnvironmentObjLgt::callback_Chk_non(DrEnvironmentLgtList*, DrCalcViewWork*, const LgtObjData*) {
    return false;
}

bool DrEnvironmentObjLgt::callback_Chk_LocalIBL(DrEnvironmentLgtList* list, DrCalcViewWork* work, const LgtObjData*) {
    const LgtPosData* pos = list->m_posData;
    DrLightObjLocalIBL* light = static_cast<DrLightObjLocalIBL*>(list->m_light);
    const mm::Vec3& lightPos = light->m_pos;
    list->m_rate = 1.0f;
    unsigned int dispIdx = pos->m_dispIdx;
    if (dispIdx != 0 && (*(m_drMan->m_dispOffBits + (dispIdx >> 5)) & (1 << (dispIdx & 0x1F))) != 0) {
        return false;
    }
    return work->m_clipPlane.clipTest(lightPos, light->m_radius);
}

bool DrEnvironmentObjLgt::callback_Calc_Non(DrEnvironmentLgtList*, DrCalcViewWork*) {
    return true;
}

bool DrEnvironmentObjLgt::callback_Calc_LocalIBL(DrEnvironmentLgtList*, DrCalcViewWork*) {
    return true;
}

void DrEnvironmentObjLgt::callback_Ren_Non(DrLightObj*, DrShdLgtMan*) {}

void DrEnvironmentObjLgt::callback_Ren2D_Non(DrLightObj*, DrShdLgtMan*) {}

void DrEnvironmentObjLgt::callback_Relase_Non(DrLightObj*) {}

// --- DrLightObj ---
void DrLightObj::setSubtractOn(bool on) {
    if (on) {
        m_flags |= FLAG_SUBTRACT;
    } else {
        m_flags &= ~FLAG_SUBTRACT;
    }
}

bool DrLightObj::isCullON() const {
    return (m_flags & FLAG_CULL) != 0;
}

DrLightObj::DrLightObj() : m_prev(nullptr), m_next(nullptr), m_flags(0), m_pixlMan(nullptr), m_shadowObj(nullptr) {}

bool DrLightObj::isPnt() const {
    return m_type == TYPE_PNT;
}

bool DrLightObj::isCharShadow() const {
    return (m_flags & FLAG_CHAR_SHADOW) != 0;
}

bool DrLightObj::isBaseMapShadow() const {
    return (m_flags & FLAG_BASE_MAP_SHADOW) != 0;
}

bool DrLightObj::isInstMapShadow() const {
    return (m_flags & FLAG_INST_MAP_SHADOW) != 0;
}

bool DrLightObj::isInstSelMapShadow() const {
    return (m_flags & FLAG_INST_SEL_MAP_SHADOW) != 0;
}

bool DrLightObj::isCacheShadow() const {
    return (m_flags & FLAG_CACHE_SHADOW) != 0;
}

DrLightObjAmb::~DrLightObjAmb() {
    ;
}

void DrLightObjDir::deleteDirShadow() {
    if (m_shadowObj != nullptr) {
        DrPixlShadowMan* shadowMan = m_pixlMan->m_objTbl->m_shadowMan;
        m_flags &= ~FLAG_SHADOW;
        shadowMan->releaseShadow(m_shadowObj);
        m_shadowObj = nullptr;
    }
}

void DrLightObjDir::releaseDir() {
    deleteDirShadow();
}

DrLightObjDir::~DrLightObjDir() {
    releaseDir();
}

void DrLightObjPnt::deletePntShadow() {
    if (m_shadowObj != nullptr) {
        DrPixlShadowMan* shadowMan = m_pixlMan->m_objTbl->m_shadowMan;
        m_flags &= ~FLAG_SHADOW;
        shadowMan->releaseShadow(m_shadowObj);
        m_shadowObj = nullptr;
    }
}

void DrLightObjPnt::releasePnt() {
    deletePntShadow();
}

DrLightObjPnt::~DrLightObjPnt() {
    releasePnt();
}

void DrLightObjSpt::deleteSptShadow() {
    if (m_shadowObj != nullptr) {
        DrPixlShadowMan* shadowMan = m_pixlMan->m_objTbl->m_shadowMan;
        m_flags &= ~FLAG_SHADOW;
        shadowMan->releaseShadow(m_shadowObj);
        m_shadowObj = nullptr;
    }
}

void DrLightObjSpt::releaseSpt() {
    deleteSptShadow();
}

DrLightObjSpt::~DrLightObjSpt() {
    releaseSpt();
}

// --- irrvol::convertSHMatrix ---
namespace irrvol {
void convertSHMatrix(mm::Mat44& mtx, const float* sh) {
    const float c1 = 0.429043f;
    const float c2 = 0.511664f;
    const float c3 = 0.743125f;
    const float c4 = 0.886227f;
    const float c5 = 0.247708f;
    mtx.m[0][0] = c1 * sh[8];
    mtx.m[0][1] = c1 * sh[4];
    mtx.m[0][2] = c1 * sh[7];
    mtx.m[0][3] = c2 * sh[3];
    mtx.m[1][0] = c1 * sh[4];
    mtx.m[1][1] = -c1 * sh[8];
    mtx.m[1][2] = c1 * sh[5];
    mtx.m[1][3] = c2 * sh[1];
    mtx.m[2][0] = c1 * sh[7];
    mtx.m[2][1] = c1 * sh[5];
    mtx.m[2][2] = c3 * sh[6];
    mtx.m[2][3] = c2 * sh[2];
    mtx.m[3][0] = c2 * sh[3];
    mtx.m[3][1] = c2 * sh[1];
    mtx.m[3][2] = c2 * sh[2];
    mtx.m[3][3] = c4 * sh[0] - c5 * sh[6];
}
}  // namespace irrvol

// --- irrvol::MemHandlebaseAllocator ---
namespace irrvol {
void* MemHandlebaseAllocator::allocate(unsigned long size, unsigned long alignment) {
    return mtl::MemManager::allocate(m_handle, size, alignment, false, "no name", 0);
}

void MemHandlebaseAllocator::deallocate(void* memory) {
    if (memory != nullptr) {
        mtl::MemManager::deallocate(memory, 0, false);
    }
}

DrIrrVolCascade::~DrIrrVolCascade() {
    for (int i = 0; i < BLOCK_NUM; ++i) {
        if (m_blocks[i] != nullptr) {
            delete m_blocks[i];
            m_blocks[i] = nullptr;
        }
    }
    memset(m_blockInfo, 0, sizeof(m_blockInfo));
    if (m_resMan != nullptr) {
        delete m_resMan;
        m_resMan = nullptr;
    }
}
}  // namespace irrvol

// --- DrIrrVolMan ---
DrIrrVolMan::DrIrrVolMan(DrMan* drMan)
    : m_drMan(drMan), m_globalInfo(nullptr), m_cascades(nullptr),
      m_allocator(MlMem::getProductMem()), m_time(0.0f), m_frameParity(0), m_enable(true), m_debugDraw(false) {
    const mm::Vec3 pos = mm::Vec3::zero;
    m_rate = 1.0f;
    m_state = 0;
    m_cascadeIdx = 2;
    m_pos = pos;
    m_prevPos = pos;
    m_prevRate = m_rate;
    m_prevState = m_state;
    m_prevCascadeIdx = m_cascadeIdx;
}

DrIrrVolMan::~DrIrrVolMan() {
    release();
}

void DrIrrVolMan::tail() {
    m_prevPos = m_pos;
    m_prevRate = m_rate;
    m_prevState = m_state;
    m_prevCascadeIdx = m_cascadeIdx;
    m_frameParity ^= 1;
}

void DrIrrVolMan::release() {
    if (m_globalInfo != nullptr) {
        for (unsigned int i = 0; i < m_globalInfo->m_cascadeNum; ++i) {
            if (m_cascades[i] != nullptr) {
                delete m_cascades[i];
                m_cascades[i] = nullptr;
            }
        }
        if (m_cascades != nullptr) {
            delete[] m_cascades;
            m_cascades = nullptr;
        }
        m_globalInfo = nullptr;
    }
}

// --- DrEnvironmentObjLgt render / release callbacks ---
DrEnvironmentMan::DrEnvironmentMan(DrMan* drMan, DrLightMan* lightMan, DrFogMan* fogMan, int lgtArg) {
    m_drMan = drMan;
    m_lightMan = lightMan;
    m_fogMan = fogMan;
    m_lgtArg = lgtArg;
    memset(m_objList, 0, 0x48);
    m_envColiMan = new (drMan->m_workHandle, nullptr, 0, 4, false) DrEnvColiMan(drMan);
}

DrEnvironmentMan::~DrEnvironmentMan() {
    if (m_extra != nullptr) {
        FileResTh* camLight = m_drMan->m_iniSys->m_camLight;
        if (camLight != nullptr) {
            camLight->Release();
        }
    }
    if (m_envColiMan != nullptr) {
        delete m_envColiMan;
        m_envColiMan = nullptr;
    }
    for (int i = 0; i < 2; ++i) {
        m_objList[i].deleteAll();
    }
    m_subList[1].deleteAll();
    m_subList[0].deleteAll();
}

DrEnvironmentObj* DrEnvironmentMan::createObj(const void* resource) {
    DrEnvironmentObjLgt* obj = new (m_drMan->m_resHandle, nullptr, 0, 4, false)
        DrEnvironmentObjLgt(resource, m_drMan, m_lightMan, m_fogMan, m_lgtArg);
    ObjList& list = m_objList[DrMan::s_nDblStockIdx];
    if (list.m_tail != nullptr) {
        list.m_tail->m_next = obj;
        obj->m_prev = list.m_tail;
        list.m_tail = obj;
    } else {
        list.m_head = obj;
        list.m_tail = obj;
        obj->m_prev = nullptr;
    }
    obj->m_next = nullptr;
    m_lightMan->releaseFastLight();
    return obj;
}

void DrLightMan::releaseFastLight() {
    if (m_ambLight != nullptr) {
        releaseAmbLight(static_cast<DrLightObjAmb*>(m_ambLight));
        m_ambLight = nullptr;
    }
    if (m_dirLight != nullptr) {
        releaseDirLight(static_cast<DrLightObjDir*>(m_dirLight));
        m_dirLight = nullptr;
    }
}

void DrEnvironmentObjLgt::callback_Ren_Point(DrLightObj* light, DrShdLgtMan* shdLgtMan) {
    DrAPGxType::setupCullingFront();
    DrAPGxType::setupDepthContl(1, 1, 3);
    DrAPGxType::setupBlend(0);
    shdLgtMan->renderDebugPnt(static_cast<DrLightObjPnt*>(light));
}

void DrEnvironmentObjLgt::callback_Ren_Spot(DrLightObj* light, DrShdLgtMan* shdLgtMan) {
    DrAPGxType::setupCullingFront();
    DrAPGxType::setupDepthContl(1, 1, 3);
    DrAPGxType::setupBlend(0);
    shdLgtMan->renderDebugSpt(static_cast<DrLightObjSpt*>(light));
}

void DrEnvironmentObjLgt::callback_Relase_Point(DrLightObj* light) {
    if (light->m_flags & DrLightObj::FLAG_SHADOW) {
        static_cast<DrLightObjPnt*>(light)->deletePntShadow();
    }
}

void DrEnvironmentObjLgt::callback_Relase_Spot(DrLightObj* light) {
    if (light->m_flags & DrLightObj::FLAG_SHADOW) {
        static_cast<DrLightObjSpt*>(light)->deleteSptShadow();
    }
}

void (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallEnvRelase[7])(DrLightObj*) = {
    &DrEnvironmentObjLgt::callback_Relase_Non,
    &DrEnvironmentObjLgt::callback_Relase_Non,
    &DrEnvironmentObjLgt::callback_Relase_Point,
    &DrEnvironmentObjLgt::callback_Relase_Spot,
    &DrEnvironmentObjLgt::callback_Relase_Non,
    &DrEnvironmentObjLgt::callback_Relase_Non,
    &DrEnvironmentObjLgt::callback_Relase_Non,
};

bool (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallEnvChk[7])(DrEnvironmentLgtList*, DrCalcViewWork*,
                                                                    const LgtObjData*) = {
    &DrEnvironmentObjLgt::callback_Chk_Ambinet_Directional,
    &DrEnvironmentObjLgt::callback_Chk_Ambinet_Directional,
    &DrEnvironmentObjLgt::callback_Chk_Point,
    &DrEnvironmentObjLgt::callback_Chk_Spot,
    &DrEnvironmentObjLgt::callback_Chk_non,
    &DrEnvironmentObjLgt::callback_Chk_non,
    &DrEnvironmentObjLgt::callback_Chk_LocalIBL,
};

bool (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallCalcEnv[7])(DrEnvironmentLgtList*, DrCalcViewWork*) = {
    &DrEnvironmentObjLgt::callback_Calc_Ambient,
    &DrEnvironmentObjLgt::callback_Calc_Directional,
    &DrEnvironmentObjLgt::callback_Calc_Point,
    &DrEnvironmentObjLgt::callback_Calc_Spot,
    &DrEnvironmentObjLgt::callback_Calc_Non,
    &DrEnvironmentObjLgt::callback_Calc_Non,
    &DrEnvironmentObjLgt::callback_Calc_LocalIBL,
};

void (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallLgtRender[7])(DrLightObj*, DrShdLgtMan*) = {
    &DrEnvironmentObjLgt::callback_Ren_Non,
    &DrEnvironmentObjLgt::callback_Ren_Non,
    &DrEnvironmentObjLgt::callback_Ren_Point,
    &DrEnvironmentObjLgt::callback_Ren_Spot,
    &DrEnvironmentObjLgt::callback_Ren_Non,
    &DrEnvironmentObjLgt::callback_Ren_Non,
    &DrEnvironmentObjLgt::callback_Ren_Non,
};

void (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallLgtRender2D[7])(DrLightObj*, DrShdLgtMan*) = {
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_LocalIBL,
};

// --- DrGlobalIBLPack ---
bool DrGlobalIBLPack::checkFileType(const void* data) {
    const GlobalIBLFileHeader* header = static_cast<const GlobalIBLFileHeader*>(data);
    if (header->m_magic != 0x4C424947) {  // "GIBL"
        return false;
    }
    return header->m_version == 10100 || header->m_version == 20000;
}

DrGlobalIBLPack::DrGlobalIBLPack(const void* data, int viewIdx)
    : m_prev(nullptr), m_next(nullptr), m_viewIdx(viewIdx), m_data(data), m_flags(0), m_prevFlags(0),
      m_captureMode(1) {}

DrGlobalIBLPack::~DrGlobalIBLPack() {
    for (unsigned int i = 0; i < m_lights.size(); ++i) {
        if (m_lights[i] != nullptr) {
            delete m_lights[i];
            m_lights[i] = nullptr;
        }
    }
    m_lights.destroy();
    m_memPool.release();
}

void DrGlobalIBLPack::release() {
    DrMan* man = DrMan::getIns();
    for (unsigned int i = 0; i < m_lights.size(); ++i) {
        man->m_lightMan->m_shdLgtMan->m_pGlobalIBL->removeObj(m_lights[i], m_viewIdx);
    }
}

// --- DrLightObjGlobalIBL ---
DrLightObjGlobalIBL::DrLightObjGlobalIBL()
    : pad_0(nullptr), m_version(0), pad_10(0), pad_18(0), pad_48(0), pad_50(mm::Vec3::zero), pad_60(mm::Vec3::zero),
      m_bindIndex(0) {
    pad_390 = mm::Vec3::zero;
    pad_3b8 = 0;
    pad_3c0 = 0;
    pad_3c4 = false;
    m_meshes.clear();
    for (int i = 0; i < 4; i++) {
        pad_410[i] = mm::Vec4::zero;
    }
}

void DrLightObjGlobalIBL::bindVertex(unsigned int index) {
    m_bindIndex = index;
    grlib::CGLibCtlVertex::setVertex(m_meshes[index].m_vertex);
}

void DrLightObjGlobalIBL::drawVertex() {
    m_meshes[m_bindIndex].m_index.drawIndex();
}

unsigned int DrLightObjGlobalIBL::getPriority() const {
    return m_priority;
}

void DrLightObjGlobalIBL::beginOccQuery() {
    DrPixlOccQuery* occ = DrMan::getIns()->m_pixlMan->m_occQuery;
    m_meshes[m_bindIndex].m_query->begin(occ);
}

void DrLightObjGlobalIBL::endOccQuery() {
    m_meshes[m_bindIndex].m_query->end();
}

// --- DrFogMan ---
DrFogMan::DrFogMan(DrMan* drMan)
    : m_drMan(drMan), m_head(nullptr), m_tail(nullptr), m_color(0.5f, 0.5f, 0.5f), m_sideColor(0.0f, 0.0f, 0.0f),
      m_sunColor(0.0f, 0.0f, 0.0f), m_near(0.1f), m_far(10000.0f), m_str(1.0f), m_parmA(1.0f), m_pow(1.0f),
      m_parmB{1.0f, 1.0f, 0.0f, 1.0f}, m_fogOn(false), m_enable(true) {}

DrFogMan::~DrFogMan() {
    releaseAll();
}

void DrFogMan::releaseAll() {
    DrFogObjGbl* obj = m_head;
    while (obj != nullptr) {
        DrFogObjGbl* next = obj->m_next;
        delete obj;
        obj = next;
    }
    m_head = nullptr;
    m_tail = nullptr;
}

bool DrFogMan::isFogOn() const {
    return m_fogOn;
}

// --- DrLightMan ---
DrLightMan::~DrLightMan() {
    releaseAll();
}

void DrLightMan::stockBegin() {
    m_stockState = 0;
    m_stockCount = 0;
    m_drMan->m_shdMan->m_lgtMan->stockBegin();
}

void DrLightMan::update() {
    updateAmb();
    updateDir();
    LightList& pnt = m_stockList[DrLightObj::TYPE_PNT][DrMan::s_nDblIdx];
    for (DrLightObj* obj = pnt.m_head; obj != nullptr;) {
        DrLightObj* next = obj->m_next;
        m_list[DrLightObj::TYPE_PNT].append(obj);
        obj = next;
    }
    pnt.m_head = pnt.m_tail = nullptr;
    LightList& spt = m_stockList[DrLightObj::TYPE_SPT][DrMan::s_nDblIdx];
    for (DrLightObj* obj = spt.m_head; obj != nullptr;) {
        DrLightObj* next = obj->m_next;
        m_list[DrLightObj::TYPE_SPT].append(obj);
        obj = next;
    }
    spt.m_head = spt.m_tail = nullptr;
}

void DrLightMan::stockEnd() {
    updateAfterPnt();
    updateAfterSpt();
    m_drMan->m_shdMan->m_lgtMan->stockEnd();
}

void DrLightMan::releaseInstantPntLight(DrLightObjPnt* light) {
    light->m_flags |= DrLightObj::FLAG_RELEASE << DrMan::s_nDblIdx;
    light->m_flags |= DrLightObj::FLAG_RELEASE << DrMan::s_nDblStockIdx;
    if (--m_instantPntNum < 0) {
        m_instantPntNum = 0;
    }
}

void DrLightMan::releaseInstantSptLight(DrLightObjSpt* light) {
    light->m_flags |= DrLightObj::FLAG_RELEASE << DrMan::s_nDblIdx;
    light->m_flags |= DrLightObj::FLAG_RELEASE << DrMan::s_nDblStockIdx;
    if (--m_instantSptNum < 0) {
        m_instantSptNum = 0;
    }
}

void DrLightMan::releaseAmbLight(DrLightObjAmb* light) {
    CS lock(*DrMan::getCriticalSection());
    light->m_flags |= DrLightObj::FLAG_RELEASE << DrMan::s_nDblStockIdx;
    if (--m_ambNum < 0) {
        m_ambNum = 0;
    }
}

void DrLightMan::releaseDirLight(DrLightObjDir* light) {
    CS lock(*DrMan::getCriticalSection());
    light->m_flags |= DrLightObj::FLAG_RELEASE << DrMan::s_nDblStockIdx;
    if (--m_dirNum < 0) {
        m_dirNum = 0;
    }
}

void DrLightMan::releasePntLight(DrLightObjPnt* light) {
    CS lock(*DrMan::getCriticalSection());
    light->m_flags |= DrLightObj::FLAG_RELEASE << DrMan::s_nDblStockIdx;
    if (--m_instantPntNum < 0) {
        m_instantPntNum = 0;
    }
}

void DrLightMan::releaseSptLight(DrLightObjSpt* light) {
    CS lock(*DrMan::getCriticalSection());
    light->m_flags |= DrLightObj::FLAG_RELEASE << DrMan::s_nDblStockIdx;
    if (--m_instantSptNum < 0) {
        m_instantSptNum = 0;
    }
}

void DrLightMan::releaseAllAmbLight() {
    m_list[DrLightObj::TYPE_AMB].deleteAll();
    m_stockList[DrLightObj::TYPE_AMB][0].deleteAll();
    m_stockList[DrLightObj::TYPE_AMB][1].deleteAll();
    m_ambNum = 0;
    m_ambLight = nullptr;
}

void DrLightMan::releaseAllDirLight() {
    m_list[DrLightObj::TYPE_DIR].deleteAll();
    m_stockList[DrLightObj::TYPE_DIR][0].deleteAll();
    m_stockList[DrLightObj::TYPE_DIR][1].deleteAll();
    m_dirNum = 0;
    m_dirLight = nullptr;
}

float DrLightMan::getSkyLuminance() const {
    const DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    float ambRate = parm->m_skyLumAmbRate;
    float colorRate = parm->m_skyLumColorRate;
    float r = ambRate * m_ambColor.r + colorRate * m_lumColor[0];
    float g = ambRate * m_ambColor.g + colorRate * m_lumColor[1];
    float b = ambRate * m_ambColor.b + colorRate * m_lumColor[2];
    return r * 0.299f + g * 0.587f + b * 0.114f;
}

// --- DrLightObjDir ---
void DrLightObjDir::update(DrLightMan*) {
    if (m_flags & FLAG_SHADOW) {
        if (m_shadowRate > 0.0f) {
            m_pixlMan->m_shadowCacheMan->m_flags |= 0x4;
        } else {
            m_pixlMan->m_shadowCacheMan->m_flags |= 0x20;
        }
    }
}

// --- DrIBLColiAcc ---
bool DrIBLColiAcc::envcoli_box(const unsigned char* data, const mm::Vec3& pos, float range) {
    const float* d = reinterpret_cast<const float*>(data);
    float dx = pos.x - d[12];
    float dy = pos.y - d[13];
    float dz = pos.z - d[14];
    float r = d[15] + range;
    if (!(dx * dx + dy * dy + dz * dz <= r * r)) return false;
    float t = dx * d[0] + dy * d[4] + dz * d[8];
    if (!(d[16] + range >= t)) return false;
    if (!(-d[16] - range <= t)) return false;
    t = dx * d[2] + dy * d[6] + dz * d[10];
    if (!(d[18] + range >= t)) return false;
    if (!(-d[18] - range <= t)) return false;
    t = dx * d[1] + dy * d[5] + dz * d[9];
    if (!(d[17] + range >= t)) return false;
    return -d[17] - range <= t;
}

bool DrIBLColiAcc::envcoli_sphere(const unsigned char* data, const mm::Vec3& pos, float range) {
    const float* d = reinterpret_cast<const float*>(data);
    float dx = pos.x - d[0];
    float dy = pos.y - d[1];
    float dz = pos.z - d[2];
    float r = d[3] + range;
    return dx * dx + dy * dy + dz * dz <= r * r;
}

bool DrIBLColiAcc::envcoli_cylinder(const unsigned char* data, const mm::Vec3& pos, float range) {
    const float* d = reinterpret_cast<const float*>(data);
    float dx = pos.x - d[12];
    float dy = pos.y - d[13];
    float dz = pos.z - d[14];
    float r = d[15] + range;
    if (!(dx * dx + dy * dy + dz * dz <= r * r)) return false;
    float t = dx * d[1] + dy * d[5] + dz * d[9];
    if (!(d[17] + range >= t)) return false;
    if (!(-d[17] - range <= t)) return false;
    float u = dx * d[0] + dy * d[4] + dz * d[8];
    float v = dx * d[2] + dy * d[6] + dz * d[10];
    float rr = d[16] + range;
    return u * u + v * v <= rr * rr;
}

bool DrIBLColiAcc::envcoli_notrot_box(const unsigned char* data, const mm::Vec3& pos, float range) {
    const float* d = reinterpret_cast<const float*>(data);
    float dx = pos.x - d[0];
    float dy = pos.y - d[1];
    float dz = pos.z - d[2];
    float r = d[3] + range;
    if (!(dx * dx + dy * dy + dz * dz <= r * r)) return false;
    if (!(d[4] + range >= dx)) return false;
    if (!(-d[4] - range <= dx)) return false;
    if (!(d[6] + range >= dz)) return false;
    if (!(-d[6] - range <= dz)) return false;
    if (!(d[5] + range >= dy)) return false;
    return -d[5] - range <= dy;
}

bool DrIBLColiAcc::envcoli_notrot_cylinder(const unsigned char* data, const mm::Vec3& pos, float range) {
    const float* d = reinterpret_cast<const float*>(data);
    float dy = pos.y - d[1];
    if (!(d[4] + range >= dy)) return false;
    if (!(-d[4] - range <= dy)) return false;
    float dx = pos.x - d[0];
    float dz = pos.z - d[2];
    float r = d[3] + range;
    return dx * dx + dz * dz <= r * r;
}

bool (DrIBLColiAcc::*DrIBLColiAcc::s_pColiTest[5])(const unsigned char*, const mm::Vec3&, float) = {
    &DrIBLColiAcc::envcoli_box,        &DrIBLColiAcc::envcoli_sphere,          &DrIBLColiAcc::envcoli_cylinder,
    &DrIBLColiAcc::envcoli_notrot_box, &DrIBLColiAcc::envcoli_notrot_cylinder,
};

DrIBLObj::~DrIBLObj() {
    if (m_coliAcc != nullptr) {
        delete m_coliAcc;
        m_coliAcc = nullptr;
    }
    for (unsigned int i = 0; i < m_texNum; ++i) {
        m_texA[i].release();
        m_texB[i].release();
    }
    if (m_texA != nullptr) {
        delete[] m_texA;
        m_texA = nullptr;
    }
    if (m_texB != nullptr) {
        delete[] m_texB;
        m_texB = nullptr;
    }
}

}  // namespace ml

// the IBL vectors' growth (their users are not written yet)
template void mm::mtl::Vector<ml::DrLightObjGlobalIBL*>::resize(size_t);
