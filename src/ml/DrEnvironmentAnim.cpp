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

}  // namespace ml
