#define MM_LIB_FROM_XBRD
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
#include "ml/DrPixlShadowMan.h"
#include "ml/DrPixlShadowCacheMan.h"
#include "ml/DrPixlPostObjCubeMapMultiIBL.h"
#include "ml/DrPixlPostObjCubeMapIBL.h"
#include "ml/DrPixlPostObjVolume.h"
#include "ml/DrPixlMdlSampler.h"
#include "ml/DrCalcMan.h"
#include "ml/DrPixlRenderTarget.h"
#include "classes/ml/DrPixlShadowObjDir.h"
#include "classes/ml/DrPixlMemMan.h"
#include "classes/ml/DrPixlShadowObjSpt.h"
#include "classes/ml/DrMan.h"
#include "ml/DrAPGxType.h"
#include "grlib/CGLibCtl.h"
#include "ml/DrResQueryObj.h"
#include "mm/Col4.h"
#include "grlib/CGLibState.h"
#include <string.h>

namespace ml {

DrPixlMan::~DrPixlMan() { releaseColorBuffer(); }

void DrPixlMan::setMainViewPort() {
    float width = m_drMan->m_curViewInfo->m_width;
    float height = m_drMan->m_curViewInfo->m_height;
    grlib::LibMainStateViewPort viewport;
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = width;
    viewport.height = height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    grlib::CGLibState::setViewport(viewport);
}

void DrPixlMan::setMainRenderTarget() {
    if (m_objTbl->m_capture != nullptr) {
        grlib::CGLibState::beginRegisterRenderTarget();
        grlib::CGLibState::setRegisterRenderTarget(*m_objTbl->m_capture, (grlib::GrlMrtType)0);
        grlib::CGLibState::endRegisterRenderTarget();
    } else {
        grlib::CGLibState::setMainFrameBuffer();
    }
    float width = m_drMan->m_curViewInfo->m_renderWidth;
    float height = m_drMan->m_curViewInfo->m_renderHeight;
    grlib::LibMainStateViewPort viewport;
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = width;
    viewport.height = height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    grlib::CGLibState::setViewport(viewport);
}

void DrPixlMan::resetRenderTarget() { m_renderTarget = 0; }

grlib::CGLibDepthTarget* DrPixlMan::getDepthObj() { return m_objTbl->m_depth[DrMan::s_nDblIdx]; }

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

void DrPixlMan::selectZprepassRenderTarget() {
    m_renderTarget = 1;
    m_renderTargetSub = 0;
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterDepthTarget(*m_objTbl->m_depth[DrMan::s_nDblIdx]->m_pDepthBuffer);
    grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::thicknessFirstBegin() {
    m_renderTarget = 13;
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterRenderTarget(*m_objTbl->m_backFaceDepth, (grlib::GrlMrtType)0);
    grlib::CGLibState::setRegisterDepthTarget(*m_objTbl->m_depth[DrMan::s_nDblIdx]->m_pDepthBuffer);
    grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectGBuffRenderTarget() { selectGBuffRenderTarget(0xFF); }

void DrPixlMan::endGBuffRenderTarget() {
    m_objTbl->m_gBuff[0][0]->setColorInvalidate();
    m_objTbl->m_gBuff[1][0]->setColorInvalidate();
    m_objTbl->m_gBuff[2][0]->setColorInvalidate();
    m_objTbl->m_gBuff[3][0]->setColorInvalidate();
    m_objTbl->m_gBuff[4][0]->setColorInvalidate();
    m_objTbl->m_obj[8][0]->setColorInvalidate();
    m_objTbl->m_obj[5][0]->setColorInvalidate();
    m_objTbl->m_obj[6][0]->setColorInvalidate();
}

void DrPixlMan::setupGodRay() {
    if (m_drMan->m_postParm[m_drMan->m_postParmIdx]->m_godRay && (m_objTbl->m_postMan->m_flags & 0x10000)) {
        m_objTbl->m_obj[7][0]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
    }
}

void DrPixlMan::alphaRenderTarget() {
    if (selectGBuffRenderTarget(0x1C0)) {
        setMainViewPort();
    }
}

void DrPixlMan::skyGodRayRenderTarget() {
    if (selectGBuffRenderTarget(0x100)) {
        setMainViewPort();
    }
}

void DrPixlMan::refractionGBuffInvalidate() {
    m_objTbl->m_gBuff[0][0]->setColorInvalidate();
    m_objTbl->m_gBuff[1][0]->setColorInvalidate();
    m_objTbl->m_gBuff[2][0]->setColorInvalidate();
    m_objTbl->m_gBuff[3][0]->setColorInvalidate();
    m_objTbl->m_gBuff[4][0]->setColorInvalidate();
}

void DrPixlMan::renderRefractionMap(bool useTarget, bool useHalfTarget) { m_objTbl->m_postMan->renderRefractionMap(useTarget, useHalfTarget); }

void DrPixlTileParm::begin(TileType type) {
    if (m_work[m_idx][0].m_on) {
        if (type != 0) {
            return;
        }
    } else if (!m_work[m_idx][type].m_on) {
        return;
    }
    grlib::CGLibGPUCache::setTiledCacheSize(m_work[m_idx][type].m_width, m_work[m_idx][type].m_height);
    grlib::CGLibGPUCache::setTiledCacheAction((GrlTiledCacheAction)1);
}

void DrPixlMan::renderRefractionEnd() {
    m_drMan->m_tileParm->end((DrPixlTileParm::TileType)2);
    if (m_objTbl->m_postMan->m_refractionQuery != nullptr) {
        m_objTbl->m_postMan->m_refractionQuery->end();
    }
}

void DrPixlTileParm::end(TileType type) {
    if (m_work[m_idx][0].m_on) {
        if (type != 0) {
            return;
        }
    } else if (!m_work[m_idx][type].m_on) {
        return;
    }
    grlib::CGLibGPUCache::setTiledCacheAction((GrlTiledCacheAction)3);
    grlib::CGLibGPUCache::setTiledCacheAction((GrlTiledCacheAction)2);
}

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

void DrPixlMan::setShadowDirRenderTarget(int index) {
    m_shadowCacheMan->m_workTbl[index].m_dirDepth.setRenderTarget();
}

void DrPixlMan::depCheckBegin(bool useDepth) {
    m_renderTarget = 0;
    if (useDepth) {
        grlib::CGLibState::beginRegisterRenderTarget();
        grlib::CGLibState::setRegisterDepthTarget(*m_objTbl->m_depth[DrMan::s_nDblIdx]->m_pDepthBuffer);
        grlib::CGLibState::endRegisterRenderTarget();
    } else {
        m_objTbl->m_depthCheck->setRenderTarget();
    }
    grlib::CGLibPolygon::setCullingOff();
    grlib::CGLibColorCtl::setColorBufferOff();
    grlib::CGLibDepthCtl::setDepthControl(1, 0, (GrlCompare)3);
}

void DrPixlMan::shadowDirEnd() {
    DrAPGxType::endShadow();
    m_renderTarget = 0;
    selectGBuffRenderTarget();
    setMainViewPort();
}

void DrPixlMan::fastRender() {
    DrPixlPostMan* postMan = m_objTbl->m_postMan;
    if (postMan->m_cubeMapMultiIBL) {
        postMan->m_cubeMapMultiIBL->render();
    }
    if (postMan->m_cubeMapIBL) {
        postMan->m_cubeMapIBL->render();
    }
    if (postMan->m_toonGrad) {
        postMan->m_toonGrad->render();
    }
    if (m_cateIdx == 0) {
        m_shadowCacheMan->shadowCacheRender();
        m_shadowCacheMan->fastRender();
    }
}

void DrPixlMan::callShadowCacheVariance() { m_shadowCacheMan->m_flags |= 0x400; }

void DrPixlMan::pixelEndMode() { m_shadowCacheMan->m_flags |= 0x40; }

void DrPixlMan::setupShadowUnifrom(int index) {
    m_shadowUniform = &m_shadowCacheMan->m_uniforms[(unsigned int)index];
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

void DrPixlPostMan::setVolumePos(const mm::Vec3& pos) {
    if (m_volume != nullptr) {
        m_volume->m_pos = pos;
    }
}

DrPixlMemMan::DrPixlMemMan() { setupMemBuff(); }

DrPixlMemMan::~DrPixlMemMan() {}



DrPixlPostObj::DrPixlPostObj(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : m_drMan(drMan), m_pixlMan(pixlMan), m_postMan(postMan) {}

void DrPixlPostObj::calc1PixlOfs(float& width, float& height) {
    int w = (int)width;
    int h = (int)height;
    width = (float)(w + (w & 1));
    height = (float)(h + (h & 1));
}

DrPixlTileParm::~DrPixlTileParm() {}

void DrPixlTileParm::update() { m_idx = DrMan::get()->m_qualityMode == 0; }

DrPixlMdlSampler::DrPixlMdlSampler() {
    m_cur.m_value0 = 4;
    m_cur.m_value1 = 1;
    m_cur.m_flag = false;
    m_next.m_value0 = 4;
    m_next.m_value1 = 1;
    m_next.m_flag = false;
}

bool DrPixlMdlSampler::update() {
    if (m_cur.m_value0 != m_next.m_value0 || m_cur.m_value1 != m_next.m_value1 || m_cur.m_flag != m_next.m_flag) {
        m_cur.m_value0 = m_next.m_value0;
        m_cur.m_value1 = m_next.m_value1;
        m_cur.m_flag = m_next.m_flag;
        return true;
    }
    return false;
}

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

void DrPixlPostParm::getRanDropLayerInfo(unsigned int layer, stRainDropLayerInfo& info) const {
    info.m_param0 = m_rainDropLayer[0][layer];
    info.m_param1 = m_rainDropLayer[1][layer];
    info.m_param2 = m_rainDropLayer[2][layer];
    info.m_param3 = m_rainDropLayer[4][layer];
    info.m_param4 = m_rainDropLayer[3][layer];
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

float DrPixlPostParm::getTMAASharpness(unsigned int type) const {
    return DrMan::getIns()->m_qualityMode == 0 ? m_tmaaSharpnessAlt[type] : m_tmaaSharpness[type];
}

bool DrPixlPostParm::getSSRWithTrans() const { return !DrMan::getIns()->m_autoResetScene; }


DrPixlRenderTarget::DrPixlRenderTarget(DrMan* drMan) { m_drMan = drMan; }

DrPixlRenderTarget::~DrPixlRenderTarget() { releaseWork(); }

DrPixlRenderCubeMapMipMap::DrPixlRenderCubeMapMipMap(DrMan* drMan) { m_drMan = drMan; }

DrPixlRenderCubeMapMipMap::~DrPixlRenderCubeMapMipMap() { releaseWork(); }

void DrPixlShadowCacheMan::addShadowCacheUpdate(bool) {
    m_updateCount++;
    m_flags |= 0x80;
}

void DrPixlShadowCacheMan::delShadowCacheUpdate() {
    m_updateCount--;
    if (m_updateCount < 0) {
        m_updateCount = 0;
    }
    m_flags |= 0x180;
}

void DrPixlShadowCacheMan::callSelectShadowCacheUpdate(unsigned long mask) { m_selectUpdate &= ~mask; }

bool DrPixlShadowCacheObj::clipTest(mm::Vec3 const& pos, float radius) { return m_clip.clipTest(pos, radius); }

bool DrPixlShadowMan::setAddObjPos(mm::Vec3 const& pos, float radius) {
    DrMan* drMan = m_drMan;
    if (drMan->m_postParm[drMan->m_postParmIdx]->m_shadowAddObjPos && m_dirShadow) {
        return m_dirShadow->setAddObjPos(pos, radius);
    }
    return false;
}

bool DrPixlShadowObj::renderEnd() {
    if (!(m_flags & 1)) {
        return false;
    }
    grlib::CGLibGPUCache::depthInvalidate(*m_depthTarget->m_pDepthBuffer);
    DrAPGxType::endShadow();
    m_drMan->m_calcMan->shadowEnd();
    return true;
}

void DrPixlShadowObj::setInstSelMapShadow(bool enable) {
    if (enable) {
        m_flags |= 4;
    } else {
        m_flags &= ~4;
    }
}

DrPixlShadowObjDir::~DrPixlShadowObjDir() {
    m_uniform.release();
    delete m_next;
}

bool DrPixlShadowObjDir::dispChk() { return (m_flags >> 1) & 1; }

bool DrPixlShadowObjDir::clipTypeChk(mm::Vec3 const& pos, float radius) {
    if (!(m_flags & 8) || m_typeClipRange <= radius) {
        return false;
    }
    return m_clip.clipTypeTest(pos, radius);
}

DrPixlShadowObjSpt::~DrPixlShadowObjSpt() {
    m_uniform.release();
    delete m_next;
}

bool DrPixlShadowObjSpt::clipChk(mm::Vec3 const& pos, float radius, bool) {
    if (m_clipRange < radius) {
        return false;
    }
    return m_clip.clipTest(pos, radius);
}

bool DrPixlShadowObjSpt::clipTypeChk(mm::Vec3 const& pos, float radius) {
    if (m_clipRange < radius) {
        return false;
    }
    return m_clip.clipTypeTest(pos, radius);
}

bool DrPixlShadowObjSpt::dispChk() { return (m_flags >> 1) & 1; }

void DrPixlShadowObjSpt::renderLight() {}

grlib::CGLibRenderTarget* DrPixlMan::getPixlObj(int index) {
    bool dbl = (0x27200ull >> (unsigned int)index) & 1;
    DrPixlObjTbl* tbl = m_objTbl;
    if (dbl) {
        return tbl->m_obj[index][DrMan::s_nDblIdx];
    }
    return tbl->m_obj[index][0];
}

void DrPixlMan::setupCate(int cate) {
    m_objTbl = &m_cate[cate];
    m_cateIdx = cate;
}

grlib::CGLibRenderTarget* DrPixlMan::getDeactivePixlObj(int index) {
    if ((0x27200ull >> (unsigned int)index) & 1) {
        return m_objTbl->m_obj[index][DrMan::s_nDblIdx ^ 1];
    }
    return nullptr;
}

grlib::CGLibRenderTarget* DrPixlMan::getSpecIBLObj() {
    DrMan* drMan = m_drMan;
    int index = drMan->m_postParm[drMan->m_postParmIdx]->m_iblSel ? 9 : 11;
    return drMan->m_pixlMan->getPixlObj(index);
}

grlib::CGLibRenderTarget* DrPixlMan::getDiffIBLObj() {
    DrMan* drMan = m_drMan;
    int index = drMan->m_postParm[drMan->m_postParmIdx]->m_iblSel ? 14 : 10;
    return drMan->m_pixlMan->getPixlObj(index);
}


}  // namespace ml
