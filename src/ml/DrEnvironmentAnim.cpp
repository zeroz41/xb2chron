#include "classes/ml/DrLightObj.h"
#include "classes/ml/DrLightObjDir.h"
#include "classes/ml/DrLightObjPnt.h"
#include "classes/ml/DrLightObjSpt.h"
#include "classes/ml/DrEnvironmentObj.h"
#include "classes/ml/DrEnvironmentObjLgt.h"
#include "ml/DrPixlMan.h"
#include "ml/DrPixlShadowMan.h"
#include "ml/DrAPGxType.h"
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
#include "classes/ml/DrLightObjPnt.h"
#include "classes/ml/DrLightObjSpt.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrMdoCtlDammy.h"
#include "classes/ml/DrMdoCtlSeamAll.h"
#include "classes/ml/DrMdoMat.h"
#include "classes/ml/DrMdoZSortObj.h"
#include "classes/ml/irrvol/MemHandlebaseAllocator.h"
#include "grlib/CGLibCtl.h"
#include "math.h"
#include "ml/DrAPGxType.h"
#include "ml/DrEnvColiMan.h"
#include "ml/DrEnvironmentAnim.h"
#include "ml/DrEnvironmentMan.h"
#include "ml/DrFogMan.h"
#include "ml/DrIniSys.h"
#include "ml/DrLightMan.h"
#include "ml/DrMdoAnim.h"
#include "ml/DrMdoSetup.h"
#include "ml/DrPixlDeferred.h"
#include "ml/DrPixlMan.h"
#include "ml/DrPixlPostMan.h"
#include "ml/DrPixlPostObjCubeMapIBL.h"
#include "ml/DrPixlPostParm.h"
#include "ml/DrPixlShadowMan.h"
#include "ml/DrResMdoMat.h"
#include "ml/DrShdLgtMan.h"
#include "ml/DrShdMan.h"
#include "ml/MdoWrkMatRes.h"
#include "ml/MdsMatInfoHeader.h"
#include "mm/Math.h"
#include "mm/Vec3NA.h"
#include "mtl/MemManager.h"

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

void DrEnvironmentObjLgt::setFrame(float frame) {
    m_frame = frame;
    for (int i = 0; i < m_rangeNum; i++) {
        float end = m_frameRange[i].m_endFrame;
        m_rangeFrame[i] = end < frame ? end : frame;
    }
}

void DrEnvironmentObjLgt::debugRenderLgt() {
    if (m_lgtNum != 0 && m_renderLgtNum != 0) {
        renderLgt();
    }
}

bool DrEnvironmentObjLgt::callback_Chk_non(DrEnvironmentLgtList*, DrCalcViewWork*, const LgtObjData*) {
    return false;
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
}  // namespace irrvol

// --- DrEnvironmentObjLgt render / release callbacks ---
DrEnvironmentMan::DrEnvironmentMan(DrMan* drMan, DrLightMan* lightMan, DrFogMan* fogMan, int lgtArg) {
    m_drMan = drMan;
    m_lightMan = lightMan;
    m_fogMan = fogMan;
    m_lgtArg = lgtArg;
    memset(m_objList, 0, 0x48);
    m_envColiMan = new (drMan->m_workHandle, nullptr, 0, 4, false) DrEnvColiMan(drMan);
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

// --- DrGlobalIBLPack ---
bool DrGlobalIBLPack::checkFileType(const void* data) {
    const GlobalIBLFileHeader* header = static_cast<const GlobalIBLFileHeader*>(data);
    if (header->m_magic != 0x4C424947) {  // "GIBL"
        return false;
    }
    return header->m_version == 10100 || header->m_version == 20000;
}

// --- DrFogMan ---
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

}  // namespace ml
