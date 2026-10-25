#include "classes/ml/DrPixlShadowObj.h"
#include "classes/ml/DrAPCache.h"
#include "grlib/CGLibRenderTarget.h"
#include "ml/DrPixlPostParm.h"
#include "ml/DrPixlMan.h"
#include "ml/DrPixlPostMan.h"
#include "ml/DrPixlDeferred.h"
#include "ml/DrPixlSkyDome.h"
#include "ml/DrPixlToonGrad.h"
#include "ml/DrPixlPostObjCapture.h"
#include "ml/DrPixlPostObj.h"
#include "ml/DrPixlTileParm.h"
#include "classes/ml/DrPixlShadowObjSpt.h"
#include "classes/ml/DrMan.h"
#include "ml/DrAPGxType.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibState.h"
#include <string.h>

namespace ml {

DrPixlMan::~DrPixlMan() { releaseColorBuffer(); }

void DrPixlMan::resetRenderTarget() { m_renderTarget = 0; }

grlib::CGLibRenderTarget* DrPixlMan::getDepthObj() { return m_objTbl->m_depth[DrMan::s_nDblIdx]; }

grlib::CGLibTextureBuffer* DrPixlMan::getDammyWhiteTexObj() { return m_dammyWhiteObj->m_pTexture; }

grlib::CGLibRenderTarget* DrPixlMan::getResponsiveAAMask() { return m_objTbl->m_responsiveAAMask; }

void DrPixlMan::displayUpdate() { m_objTbl->m_deferred->displayUpdate(); }

void DrPixlMan::updateShadowDisplayList() {
    if (m_objTbl->m_flags & 0x20) {
        m_objTbl->m_flags &= ~0x20;
    }
}

void DrPixlMan::renderEnd(int) {
    if (m_objTbl->m_capture != nullptr) {
        m_objTbl->m_capture->setColorInvalidate();
    }
}

void DrPixlMan::selectGBuffRenderTarget() { selectGBuffRenderTarget(0xFF); }

void DrPixlMan::refractionGBuffInvalidate() {
    m_objTbl->m_gBuff[0][0]->setColorInvalidate();
    m_objTbl->m_gBuff[1][0]->setColorInvalidate();
    m_objTbl->m_gBuff[2][0]->setColorInvalidate();
    m_objTbl->m_gBuff[3][0]->setColorInvalidate();
    m_objTbl->m_gBuff[4][0]->setColorInvalidate();
}

void DrPixlMan::renderRefractionMap(bool useTarget, bool useHalfTarget) { m_objTbl->m_postMan->renderRefractionMap(useTarget, useHalfTarget); }

void DrPixlMan::renderSkyDome() {
    if (m_objTbl->m_postMan->m_skyDome != nullptr) {
        m_objTbl->m_postMan->m_skyDome->baseRender();
    }
}

void DrPixlMan::renderSkyGodRay() {
    if (m_objTbl->m_postMan->m_skyDome != nullptr) {
        m_objTbl->m_postMan->m_skyDome->godRayRender();
    }
}

bool DrPixlMan::isRefractionMap() { return m_objTbl->m_postMan->m_refraction != nullptr; }

grlib::CGLibRenderTarget* DrPixlMan::getBackFaceDepthTexture() { return m_objTbl->m_backFaceDepth; }

void DrPixlMan::thicknessFirstEnd() { m_objTbl->m_backFaceDepth->setColorInvalidate(); }

void DrPixlMan::lastDeferredRender() { m_objTbl->m_deferred->lastDeferredRender(); }

void DrPixlMan::occRenderEnd() { DrAPGxType::endOccQuery(); }

void DrPixlMan::depCheckEnd() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrPixlMan::shadowDirBegin() {
    m_drMan->m_apCache->shadowBegin();
    DrAPGxType::beginShadow();
}

void DrPixlMan::callFgShadowCacheUpdate() {}

void DrPixlMan::lastCapRender() {
    if (m_objTbl->m_postMan->m_capture != nullptr) {
        m_objTbl->m_postMan->m_capture->render();
    }
}

void DrPixlMan::setMainSRGBRenderTarget() { grlib::CGLibState::setMainFrameBuffer(); }

void DrPixlMan::changeHDRBuff(DrPixlRenderTarget* target) {
    if (m_objTbl->m_hdrBuff[0] == m_objTbl->m_hdrBuff[1]) {
        m_objTbl->m_hdrBuff[0] = target;
    }
    m_objTbl->m_hdrBuff[1] = target;
}

grlib::CGLibTextureBuffer* DrPixlMan::getDammyTexObj() { return m_dammyObj->m_pTexture; }

void DrPixlMan::setShadowObj(DrPixlShadowObj* obj) {
    m_shadowObj = obj;
    m_shadowUniform = &obj->m_uniform;
}

void DrPixlPostMan::setDownDepth() { m_flags |= 0x80000; }

grlib::CGLibRenderTarget* DrPixlPostMan::getDownDepth() { return m_downDepth[DrMan::s_nDblIdx]; }

grlib::CGLibRenderTarget* DrPixlPostMan::getOldDownDepth() { return m_downDepth[DrMan::s_nDblStockIdx]; }

bool DrPixlPostMan::isDepthDown() { return (m_flags >> 19) & 1; }



DrPixlPostObj::DrPixlPostObj(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : m_drMan(drMan), m_pixlMan(pixlMan), m_postMan(postMan) {}

DrPixlTileParm::~DrPixlTileParm() {}

DrPixlPostParm::DrPixlPostParm() { reset(); }

DrPixlPostParm::~DrPixlPostParm() {}

DrPixlPostParm& DrPixlPostParm::operator=(const DrPixlPostParm& other) {
    memcpy(this, &other, sizeof(DrPixlPostParm));
    return *this;
}

void DrPixlPostParm::setInst() { s_pIns = this; }

bool DrPixlPostParm::isShwRaytrace() const { return m_shwRaytrace; }

bool DrPixlPostParm::isShwRaytraceTemporalWithOthers() const {
    return DrMan::getIns()->isIBLHalfRes() && m_shwRaytraceTemporal;
}

bool DrPixlPostParm::getTMAAOn() const { return m_tmaa; }

bool DrPixlPostParm::getToneMapOn() const { return m_toneMap; }

bool DrPixlPostParm::getColTblOn() const { return m_colTbl; }

float DrPixlPostParm::getBorderBlmMul() const { return m_borderBlmMul; }

bool DrPixlPostParm::isBlm2PassExtract() const { return m_blm2PassExtract && m_tmaa; }

void DrPixlPostParm::calcOfsRenderCheck(float x, float y) {
    m_ofsRenderCheck = (unsigned int)(x * 100.0f) | ((unsigned int)(y * 100.0f) << 8);
}

void DrPixlPostParm::calcReductionBuffer(int& width, int& height) {
    if (m_reduction) {
        width = (int)(width * m_reductionScale[0]);
        height = (int)(height * m_reductionScale[1]);
        width += -width & 7;
        height += -height & 7;
    }
}

void DrPixlPostParm::setOverrideToneMap(float value) {
    m_override[DrMan::s_nDblIdx].m_overrideToneMap = true;
    m_override[DrMan::s_nDblIdx].m_toneMap = value;
}

float DrPixlPostParm::getToonDirLightScale() const {
    if (DrMan::getIns()->m_toonDirLightScale) {
        return m_toonDirLightScale;
    }
    return 1.0f;
}

void DrPixlPostParm::resetScene() { m_resetScene[DrMan::s_nDblStockIdx] = true; }

void DrPixlPostParm::setWeatherFrame(float frame) { m_weatherFrame[DrMan::s_nDblStockIdx] = frame; }

float DrPixlPostParm::getWeatherFrame() const { return m_weatherFrame[DrMan::s_nDblIdx]; }

void DrPixlPostParm::resetWeatherFrame() { m_weatherFrame[DrMan::s_nDblIdx] = 60.0f; }

void DrPixlPostParm::setOverrideMotBlur(bool value) { m_override[DrMan::s_nDblIdx].m_overrideMotBlur = value; }
void DrPixlPostParm::setOverrideDOF(bool value) { m_override[DrMan::s_nDblIdx].m_overrideDOF = value; }
void DrPixlPostParm::setDOF(bool value) { m_override[DrMan::s_nDblIdx].m_dof = value; }
void DrPixlPostParm::setDOFHlv(bool value) { m_override[DrMan::s_nDblIdx].m_dofHlv = value; }
void DrPixlPostParm::setDOFAutoFocus(bool value) { m_override[DrMan::s_nDblIdx].m_dofAutoFocus = value; }
void DrPixlPostParm::setDoFPixlRatio(float value) { m_override[DrMan::s_nDblIdx].m_dofPixlRatio = value; }
void DrPixlPostParm::setDoFDistance(float value) { m_override[DrMan::s_nDblIdx].m_dofDistance = value; }
void DrPixlPostParm::setDoFRange(float value) { m_override[DrMan::s_nDblIdx].m_dofRange = value; }
void DrPixlPostParm::setDoFStrength(float value) { m_override[DrMan::s_nDblIdx].m_dofStrength = value; }
void DrPixlPostParm::setDoFLens(float value) { m_override[DrMan::s_nDblIdx].m_dofLens = value; }
void DrPixlPostParm::setDoFBlend(float value) { m_override[DrMan::s_nDblIdx].m_dofBlend = value; }
void DrPixlPostParm::setDoFPixlLv(int value) { m_override[DrMan::s_nDblIdx].m_dofPixlLv = value; }
void DrPixlPostParm::setDoFocusNum(int value) { m_override[DrMan::s_nDblIdx].m_dofFocusNum = value; }
void DrPixlPostParm::setDofFocusMin(float value) { m_override[DrMan::s_nDblIdx].m_dofFocusMin = value; }
void DrPixlPostParm::setOverrideColorFilter(bool value) { m_override[DrMan::s_nDblIdx].m_overrideColorFilter = value; }
void DrPixlPostParm::setColorFilterNum(int value) { m_override[DrMan::s_nDblIdx].m_colorFilterNum = value; }
void DrPixlPostParm::setColorFilterFrm(float value) { m_override[DrMan::s_nDblIdx].m_colorFilterFrm = value; }
void DrPixlPostParm::setColorFilterFarNum(int value) { m_override[DrMan::s_nDblIdx].m_colorFilterFarNum = value; }

bool DrPixlPostParm::getRainDropOn() const { return m_rainDrop; }

bool DrPixlPostParm::getSSRWithTrans() const { return !DrMan::getIns()->m_autoResetScene; }


void DrPixlShadowObjSpt::renderLight() {}


}  // namespace ml
