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
#include "ml/DrPixlPostObjMotionBlur.h"
#include "ml/DrPixlPostObjBloom.h"
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
#include "grlib/CGLibTexture.h"
#include "ml/DrCalcViewWork.h"
#include "ml/DrShdDataObj.h"
#include "ml/DrShdDataList.h"
#include "ml/DrPixlOccQuery.h"
#include "ml/DrShdMan.h"
#include "ml/DrShdLgtMan.h"
#include "classes/ml/DrShdLgtHybrid.h"
#include "classes/ml/DrLightObjSpt.h"
#include "classes/ml/DrCalcClipWorkViewPoli.h"
#include "classes/grlib/CGLibUniformEtcUtility.h"
#include "mtl/MemManager.h"
#include "ml/DrPixlPostObjDepthofField.h"
#include "ml/DrPixlPostObjMotionBlur2.h"
#include "ml/DrPixlPostObjUnbranchToDepth.h"
#include "ml/DrPixlPostObjExpStencil.h"
#include "ml/DrPixlPostObjTSSAO.h"
#include "ml/DrPixlPostObjSSR.h"
#include "ml/DrPixlShadowRaytrace.h"
#include "ml/DrPixlPostObjFxAA.h"
#include "ml/DrPixlPostObjTMAA.h"
#include "ml/DrPixlPostObjRainDrop.h"
#include "ml/DrPixlPostObjToneMap.h"
#include "ml/DrPixlPostObjHistgram.h"
#include "ml/DrPixlPostObjGlassBr.h"
#include <math.h>
#include <string.h>

namespace ml {

DrPixlDeferred::~DrPixlDeferred() {
    if (m_shadowTarget != nullptr) {
        delete m_shadowTarget;
        m_shadowTarget = nullptr;
    }
    for (int i = 0; i < 2; i++) {
        if (m_shadowTargetDbl[i] != nullptr) {
            delete m_shadowTargetDbl[i];
            m_shadowTargetDbl[i] = nullptr;
        }
    }
}

void DrPixlDeferred::lgtCalcRender() {
    DrPixlMan* pixlMan = m_pixlMan;
    pixlMan->m_renderTarget = 6;
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterRenderTarget(*pixlMan->m_objTbl->m_obj[5][0], (grlib::GrlMrtType)0);
    grlib::CGLibState::setRegisterRenderTarget(*pixlMan->m_objTbl->m_obj[6][0], (grlib::GrlMrtType)1);
    grlib::CGLibState::setRegisterRenderTarget(**(pixlMan->m_objTbl->m_obj[9] + DrMan::s_nDblIdx), (grlib::GrlMrtType)2);
    grlib::CGLibState::setRegisterDepthTarget(*pixlMan->m_objTbl->m_depth[DrMan::s_nDblIdx]->m_pDepthBuffer);
    grlib::CGLibState::endRegisterRenderTarget();
    DrAPGxType::setupCullingOff();
    DrAPGxType::setupBlend(7);
    pixlMan = m_pixlMan;
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterRenderTarget(*pixlMan->m_objTbl->m_obj[5][0], (grlib::GrlMrtType)0);
    grlib::CGLibState::setRegisterDepthTarget(*pixlMan->m_objTbl->m_depth[DrMan::s_nDblIdx]->m_pDepthBuffer);
    grlib::CGLibState::endRegisterRenderTarget();
}

// lbl_71015E9690: the pixel manager the constructor registers (name inferred); used keeps get()
// from folding to null while the constructor is not written
__attribute__((used)) static DrPixlMan* s_pInstance;

void DrPixlMan::toneMapRender(bool depth) {
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    grlib::CGLibRenderTarget* downDepth = *(m_objTbl->m_postMan->m_downDepth + DrMan::s_nDblIdx);
    DrCalcViewWork* viewWork = m_drMan->m_calcMan->m_pViewWork;
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    DrAPCache* cache = m_drMan->m_apCache;
    DrAPGxType::setupScreenQuads(false);
    DrShdDataObj* obj = list->getPostShdObj(2);
    bool useDepth = downDepth != nullptr && depth;
    if (useDepth) {
        DrAPGxType::setupDepthContl(1, 1, 7);
        obj->setDeclarationIdx(obj->getDeclarationOfs("PIXL_TYPE"), 2);
    } else {
        obj->setDeclarationIdx(obj->getDeclarationOfs("PIXL_TYPE"), 1);
    }
    list->bindQuadsTex();
    obj->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    unsigned int location = obj->getCurrentShader().getTextureLocation("s0");
    float val[4];
    val[0] = m_objTbl->m_toneMapVal[0];
    val[1] = viewWork->m_proj.m[2][2];
    val[2] = viewWork->m_proj.m[3][2];
    val[3] = 0.0f;
    uniform.setF32SetVec4(0, val);
    float scale[4];
    if (parm->m_hdrFilter && depth) {
        DrPixlRenderTarget* hdrBuff = m_objTbl->m_hdrBuff[0];
        float width = hdrBuff->m_width;
        float height = hdrBuff->m_height;
        scale[0] = (width - 1.0f) / width;
        scale[1] = (height - 1.0f) / height;
        scale[2] = 1.0f / (width + width);
        scale[3] = 1.0f / (height + height);
        cache->beginTexSampling(2, 1);
    } else {
        scale[0] = 1.0f;
        scale[1] = 1.0f;
        scale[2] = 0.0f;
        scale[3] = 0.0f;
        cache->beginTexSampling(2, 0);
    }
    cache->setTexture(*m_objTbl->m_hdrBuff[0]->m_pTexture, location);
    uniform.setF32SetVec4(0x10, scale);
    if (useDepth) {
        float width = downDepth->m_width;
        float height = downDepth->m_height;
        val[0] = (width - 1.0f) / width;
        val[1] = (height - 1.0f) / height;
        val[2] = 1.0f / (width + width);
        val[3] = 1.0f / (height + height);
        uniform.setF32SetVec4(0x20, val);
        unsigned int depLocation = obj->getCurrentShader().getTextureLocation("dep");
        cache->beginTexSampling(2, 1);
        cache->setTexture(*downDepth->m_pTexture, depLocation);
        uniform.updateData();
        uniform.setUniformBlock();
        list->renderQuads();
        DrAPGxType::setupDepthContl(0, 0, 7);
    } else {
        uniform.updateData();
        uniform.setUniformBlock();
        list->renderQuads();
    }
}

DrPixlMan* DrPixlMan::get() { return s_pInstance; }

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

bool DrPixlMan::selectGBuffRenderTarget(unsigned int target) {
    if (m_renderTarget == 2 && m_renderTargetSub == (int)target) {
        return false;
    }
    m_renderTarget = 2;
    m_renderTargetSub = target;
    grlib::CGLibState::beginRegisterRenderTarget();
    // the pixel object entry of each target bit (name inferred)
    const int objIdx[11] = {0, 1, 2, 3, 4, 8, 5, 6, 7, 15, 18};
    int mrt = 0;
    for (int i = 0; i < 11; i++) {
        if ((1 << i) & target) {
            grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(objIdx[i]), (grlib::GrlMrtType)mrt);
            mrt++;
        }
    }
    grlib::CGLibState::setRegisterDepthTarget(*m_objTbl->m_depth[DrMan::s_nDblIdx]->m_pDepthBuffer);
    grlib::CGLibState::endRegisterRenderTarget();
    return true;
}

void DrPixlMan::selectLightRenderTarget() {
    if (m_renderTarget != 14) {
        m_renderTarget = 14;
        grlib::CGLibState::beginRegisterRenderTarget();
        grlib::CGLibState::setRegisterRenderTarget(*m_objTbl->m_obj[5][0], (grlib::GrlMrtType)0);
        grlib::CGLibState::setRegisterRenderTarget(*m_objTbl->m_obj[6][0], (grlib::GrlMrtType)1);
        grlib::CGLibState::setRegisterDepthTarget(*m_objTbl->m_lightDepth->m_pDepthBuffer);
        grlib::CGLibState::endRegisterRenderTarget();
        grlib::CGLibColorCtl::setMrtBlendControl((grlib::GrlMrtType)0, (GrlBlendFunc)2, (GrlBlendFunc)2, (GrlBlendCombine)1);
        grlib::CGLibColorCtl::setMrtBlendControl((grlib::GrlMrtType)1, (GrlBlendFunc)2, (GrlBlendFunc)2, (GrlBlendCombine)1);
    }
    setMainViewPort();
    DrAPGxType::setupDepthContl(1, 0, 2);
}

void DrPixlMan::selectSubtractLightRenderTarget() {
    if (m_renderTarget != 16) {
        m_renderTarget = 16;
        grlib::CGLibState::beginRegisterRenderTarget();
        grlib::CGLibState::setRegisterRenderTarget(*m_objTbl->m_gBuff[2][0], (grlib::GrlMrtType)0);
        grlib::CGLibState::setRegisterDepthTarget(*m_objTbl->m_depth[DrMan::s_nDblIdx]->m_pDepthBuffer);
        grlib::CGLibState::endRegisterRenderTarget();
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)2, (GrlBlendFunc)2, (GrlBlendCombine)4, (GrlLogicType)3);
    }
    setMainViewPort();
    DrAPGxType::setupStencilTest(0, 0, 7, 1, 0, 8, 5, 0, 0, 0);
}

void DrPixlMan::skyRenderTarget() {
    if (m_renderTarget != 12) {
        m_renderTarget = 12;
        grlib::CGLibState::beginRegisterRenderTarget();
        grlib::CGLibState::setRegisterRenderTarget(*m_objTbl->m_obj[5][0], (grlib::GrlMrtType)0);
        grlib::CGLibState::setRegisterRenderTarget(*m_objTbl->m_gBuff[3][0], (grlib::GrlMrtType)1);
        grlib::CGLibState::setRegisterDepthTarget(*m_objTbl->m_depth[DrMan::s_nDblIdx]->m_pDepthBuffer);
        grlib::CGLibState::endRegisterRenderTarget();
        grlib::CGLibColorCtl::setColorChannelMask((grlib::GrlMrtType)1, 1, 1, 0, 1);
        setMainViewPort();
    }
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

bool DrPixlMan::renderRefractionBegin() {
    m_drMan->m_apCache->begin();
    m_renderTarget = 5;
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterDepthTarget(*m_objTbl->m_depth[DrMan::s_nDblIdx]->m_pDepthBuffer);
    grlib::CGLibState::endRegisterRenderTarget();
    m_drMan->m_tileParm->begin((DrPixlTileParm::TileType)2);
    DrPixlPostMan* postMan = m_objTbl->m_postMan;
    if (!(postMan->m_flags & 0x200000)) {
        return false;
    }
    if (postMan->m_refractionQuery != nullptr) {
        postMan->m_refractionQuery->begin(postMan->m_pixlMan->m_occQuery);
    }
    return true;
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

void DrPixlMan::occRenderBegin(bool useDepth) {
    m_renderTarget = 0;
    if (useDepth) {
        grlib::CGLibState::beginRegisterRenderTarget();
        grlib::CGLibState::setRegisterDepthTarget(*m_objTbl->m_depth[DrMan::s_nDblIdx]->m_pDepthBuffer);
        grlib::CGLibState::endRegisterRenderTarget();
    } else {
        m_objTbl->m_depthCheck->setRenderTarget();
    }
    DrPixlOccQuery* occQuery = m_occQuery;
    DrAPGxType::beginOccQuery();
    occQuery->m_shdList->bindShdBoxVertex();
    occQuery->m_renderCount = 0;
    occQuery->m_shader->setupShader(0u);
    occQuery->m_uniformOfs = occQuery->m_shader->getCurrentShader().getUniformBlockOfs("U_POST");
}

void DrPixlMan::lastUpdate() {
    DrPixlOccQuery* occQuery = m_occQuery;
    DrResQueryObj* obj = occQuery->m_useHead;
    while (obj != nullptr) {
        bool done = obj->update();
        DrResQueryObj* next = obj->m_next;
        if (done) {
            occQuery->releaseObj(obj);
        }
        obj = next;
    }
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

void DrPixlShadowCacheMan::fastRender() {
    if (m_flags & 0x28) {
        if ((m_flags & 0x8) && m_updateCount != 0 && !DrMan::get()->m_shadowRenderOff) {
            shadowmapRender(0);
            shadowmapRender(1);
            shadowmapRender(2);
        } else {
            m_workTbl[0].m_dirDepth.clearDepth(false);
            m_workTbl[1].m_dirDepth.clearDepth(false);
            m_workTbl[2].m_dirDepth.clearDepth(false);
            m_workTbl[3].m_dirDepth.clearDepth(false);
        }
        shadowmapRender(3);
        m_flags &= ~0x20;
    }
}

void DrPixlMan::lastRender() {
    m_objTbl->m_postMan->render();
    if (m_drMan->m_postParm[m_drMan->m_postParmIdx]->m_dbgShadow) {
        m_objTbl->m_shadowMan->shadowRender();
    } else if (m_drMan->m_postParm[m_drMan->m_postParmIdx]->m_dbgShadowCache) {
        m_shadowCacheMan->debugShadowCacheRender();
    }
    if (m_drMan->m_postParm[m_drMan->m_postParmIdx]->m_dbgDeferred) {
        m_objTbl->m_deferred->debugRender();
    }
    if (m_drMan->m_postParm[m_drMan->m_postParmIdx]->m_dbgReduction) {
        debugReductionRender();
    }
}

void DrPixlShadowCacheMan::debugShadowCacheRender() {
    DrMan* drMan = DrMan::get();
    int level = (int)(drMan->m_postParm[drMan->m_postParmIdx]->m_dbgShadowCacheLevel - 1.0f);
    if (level < 0) {
        level = 0;
    }
    if (level > 3) {
        level = 3;
    }
    int size = DrMan::get()->m_curViewInfo->m_width / 8;
    int x = 0;
    int y = 0;
    int col = 0;
    for (int i = 0; i < m_cacheNum; i++) {
        DrMan::get()->m_pixlMan->debugRender(*m_workTbl[level].m_cacheObj[i].m_depth.m_pSubTexture, x, y, size, size, false, false,
                                             1.0f, true);
        col++;
        if (col < m_cacheCols) {
            x += size;
        } else {
            x = 0;
            y += size;
            col = 0;
        }
    }
    m_pixlMan->debugRender(*m_workTbl[level].m_dirDepth.m_pSubTexture, x, y, size, size, false, false, 1.0f, true);
}

void DrPixlMan::gammaRender(bool depth) {
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    grlib::CGLibRenderTarget* downDepth = *(m_objTbl->m_postMan->m_downDepth + DrMan::s_nDblIdx);
    DrCalcViewWork* viewWork = m_drMan->m_calcMan->m_pViewWork;
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    DrAPCache* cache = m_drMan->m_apCache;
    DrAPGxType::setupScreenQuads(false);
    DrShdDataObj* obj = list->getSelectShdObj(5);
    bool useDepth = downDepth != nullptr && depth;
    if (useDepth) {
        DrAPGxType::setupDepthContl(1, 1, 7);
        obj->setDeclarationIdx(obj->getDeclarationOfs("PIXL_TYPE"), 2);
    } else {
        obj->setDeclarationIdx(obj->getDeclarationOfs("PIXL_TYPE"), 1);
    }
    list->bindQuadsTex();
    obj->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    float val[4];
    val[0] = m_objTbl->m_toneMapVal[0];
    val[1] = viewWork->m_proj.m[2][2];
    val[2] = viewWork->m_proj.m[3][2];
    val[3] = 0.0f;
    uniform.setF32SetVec4(0, val);
    float scale[4];
    if (parm->m_hdrFilter && depth) {
        scale[0] = 1.0f;
        scale[1] = 1.0f;
        scale[2] = 0.0f;
        scale[3] = 0.0f;
        cache->beginTexSampling(2, 1);
    } else {
        scale[0] = 1.0f;
        scale[1] = 1.0f;
        scale[2] = 0.0f;
        scale[3] = 0.0f;
        cache->beginTexSampling(2, 0);
    }
    unsigned int location = obj->getCurrentShader().getTextureLocation("s0");
    cache->setTexture(*m_objTbl->m_hdrBuff[0]->m_pTexture, location);
    uniform.setF32SetVec4(0x10, scale);
    if (useDepth) {
        unsigned int depLocation = obj->getCurrentShader().getTextureLocation("dep");
        float width = downDepth->m_width;
        float height = downDepth->m_height;
        val[0] = (width - 1.0f) / width;
        val[1] = (height - 1.0f) / height;
        val[2] = 1.0f / (width + width);
        val[3] = 1.0f / (height + height);
        uniform.setF32SetVec4(0x20, val);
        cache->beginTexSampling(2, 1);
        cache->setTexture(*downDepth->m_pTexture, depLocation);
        uniform.updateData();
        uniform.setUniformBlock();
        list->renderQuads();
        DrAPGxType::setupDepthContl(0, 0, 7);
    } else {
        uniform.updateData();
        uniform.setUniformBlock();
        list->renderQuads();
    }
}

void DrPixlMan::offScreenAlphaRender() {
    DrAPGxType::setupScreenQuads(false);
    m_objTbl->m_capture->setRenderTarget(*m_objTbl->m_depth[DrMan::s_nDblIdx]->m_pDepthBuffer);
    DrAPGxType::setupStencilTest(0, 0, 7, 0, 0, 0, 7, 0, 0, 0);
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrShdDataObj* obj = list->getPostShdObj(19);
    list->bindQuadsTex();
    obj->setupShader(0u);
    unsigned int location0 = obj->getCurrentShader().getTextureLocation("s0");
    unsigned int location1 = obj->getCurrentShader().getTextureLocation("s1");
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    float val[4] = {m_objTbl->m_toneMapVal[0], 0.0f, 0.0f, 0.0f};
    uniform.setF32SetVec4(0, val);
    uniform.updateData();
    uniform.setUniformBlock();
    DrAPCache* cache = m_drMan->m_apCache;
    cache->beginTexSampling(2, 0);
    cache->setTexture(*m_objTbl->m_hdrBuff[0]->m_pTexture, location0);
    cache->setTexture(*m_objTbl->m_capture->m_pTexture, location1);
    list->renderQuads();
    DrAPGxType::setupAlphaChanel(false);
}

void DrPixlMan::captureMainFrameBuffer(grlib::CGLibTextureBuffer* tex, unsigned int width, unsigned int height) {
    if (static_cast<unsigned short>(tex->getWidth()) != width || static_cast<unsigned short>(tex->getHeight()) != height ||
        !tex->isInitialized()) {
        grlib::CGLibTexture::createTextureBuff(*tex, width, height, (GrlSurfaceFormat)0x25);
    }
    grlib::CGLibRenderTarget target;
    target.setTextureInfo(*tex);
    target.setRenderTarget();
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrShdDataObj* obj = list->getSelectShdObj(1);
    grlib::CGLibRenderTarget* mainTarget = grlib::CGLibState::getMainRenderTarget();
    obj->setDeclarationIdx(obj->getDeclarationOfs("PIXL_TYPE"), 1);
    obj->setDeclarationIdx(obj->getDeclarationOfs("MRT_NUM"), 1);
    list->bindQuadsTex();
    obj->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    unsigned int ofs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gScal");
    unsigned int location = obj->getCurrentShader().getTextureLocation("s0");
    float mainWidth = mainTarget->m_width;
    float mainHeight = mainTarget->m_height;
    DrAPCache* cache = m_drMan->m_apCache;
    float scale[4];
    scale[0] = (mainWidth - 1.0f) / mainWidth;
    scale[1] = (mainHeight - 1.0f) / mainHeight;
    scale[2] = 1.0f / (mainWidth + mainWidth);
    scale[3] = 1.0f / (mainHeight + mainHeight);
    cache->beginTexSampling(2, 1);
    cache->setTexture(*mainTarget->m_pTexture, location);
    uniform.setF32SetVec4(ofs, scale);
    uniform.updateData();
    uniform.setUniformBlock();
    list->renderQuads();
    grlib::CGLibState::setMainFrameBuffer();
}

void DrPixlMan::debugIlluminanceRender() {
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    DrAPCache* cache = m_drMan->m_apCache;
    DrAPGxType::setupScreenQuads(false);
    DrShdDataObj* obj = list->getDebugShdObj(14);
    list->bindQuadsTex();
    obj->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    float val[4] = {1.0f / parm->m_illuminanceScale, 0.0f, 0.0f, 0.0f};
    uniform.setF32SetVec4(0, val);
    uniform.updateData();
    uniform.setUniformBlock();
    unsigned int location = obj->getCurrentShader().getTextureLocation("s0");
    cache->beginTexSampling(2, 0);
    cache->setTexture(*m_objTbl->m_hdrBuff[0]->m_pTexture, location);
    list->renderQuads();
}

void DrPixlMan::callShadowCacheVariance() { m_shadowCacheMan->m_flags |= 0x400; }

void DrPixlMan::pixelEndMode() { m_shadowCacheMan->m_flags |= 0x40; }

void DrPixlMan::setupShadowUnifrom(int index) {
    m_shadowUniform = &m_shadowCacheMan->m_uniforms.m_pArray[(unsigned int)index];
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

void DrPixlPostMan::renderDeferredFast() {
    bool tmaa = m_drMan->isTemporalUPSToGlobalIBL() || m_drMan->m_postParm[m_drMan->m_postParmIdx]->m_tmaa;
    if (m_downDepth[DrMan::s_nDblIdx] != nullptr) {
        renderDownDepth(true, tmaa, true);
    }
    if (m_unbranchToDepth != nullptr) {
        m_unbranchToDepth->render();
    }
    if (m_expStencil != nullptr) {
        m_expStencil->render();
    }
    if (m_tssao != nullptr) {
        m_tssao->render_beforeTemporal();
    }
    if (m_shadowRaytrace != nullptr) {
        m_shadowRaytrace->render_beforeTemporal();
    }
    if (m_ssr != nullptr) {
        m_ssr->render();
    }
}

void DrPixlPostMan::resetColorBuff() {
    if (m_tssao != nullptr) {
        m_tssao->resetColorBuff(false);
    }
    setupDepthBuff();
    if (m_bloom != nullptr) {
        m_bloom->resetColorBuff(false);
    }
    if (m_ssr != nullptr) {
        m_ssr->resetColorBuff();
    }
    if (m_tmaa != nullptr) {
        m_tmaa->resetColorBuff();
    }
    if (m_shadowRaytrace != nullptr) {
        m_shadowRaytrace->resetColorBuff();
    }
    if (m_drMan->m_postParm[m_drMan->m_postParmIdx]->m_iblColorMode == 2) {
        return;
    }
    if (m_depthOfField != nullptr) {
        m_depthOfField->resetColorBuff();
    }
    if (m_motionBlur != nullptr) {
        m_motionBlur->calcBludBuffColorBuff();
    }
    if (m_motionBlur2 != nullptr) {
        m_motionBlur2->resetColorBuff();
    }
    if (DrPixlPostObjFxAA* fxaa = m_fxaa) {
        DrMan* drMan = fxaa->m_drMan;
        fxaa->m_width = drMan->m_curViewInfo->m_width;
        fxaa->m_height = drMan->m_curViewInfo->m_height;
    }
    if (m_volume != nullptr) {
        m_volume->calcColorBuff();
    }
    if (m_rainDrop != nullptr) {
        m_rainDrop->resetColorBuff();
    }
}

DrPixlOccQuery::DrPixlOccQuery(DrMan* drMan, DrPixlMan* pixlMan)
    : m_drMan(drMan), m_pixlMan(pixlMan), m_renderCount(0), m_freeHead(nullptr), m_freeTail(nullptr),
      m_useHead(nullptr), m_useTail(nullptr), m_objs(nullptr), m_useCount(0), m_freeCount(0), m_capacity(0) {
    m_shdList = drMan->m_shdMan->m_dataList;
    m_shader = m_shdList->getSelectShdObj(4);
    m_occTypeOfs = m_shader->getDeclarationOfs("OCC_TYPE");
    m_buffer = static_cast<DrResQueryObj*>(mtl::MemManager::allocate(DrMan::getIns()->m_queryHandle,
                                                                     sizeof(DrResQueryObj) * 0x800, 0x40, false,
                                                                     "no name", 0));
    m_objs = m_buffer;
    m_capacity = 0x800;
    for (long i = 0; i < m_capacity; i++) {
        new (&m_objs[i]) DrResQueryObj();
    }
    DrResQueryObj* objs = m_objs;
    int num = m_capacity;
    m_useCount = 0;
    m_freeCount = num;
    m_freeHead = objs;
    m_freeTail = &objs[num - 1];
    for (int i = 0; i < num - 1; i++) {
        objs[i].m_next = &objs[i + 1];
        objs[i + 1].m_prev = &objs[i];
    }
}

DrResQueryObj* DrPixlOccQuery::createObj() {
    DrResQueryObj* obj = m_freeHead;
    if (obj == nullptr) {
        return nullptr;
    }
    DrResQueryObj* next = obj->m_next;
    if (next == nullptr) {
        m_freeHead = nullptr;
        m_freeTail = nullptr;
    } else {
        m_freeHead = next;
        next->m_prev = nullptr;
    }
    if (m_useTail != nullptr) {
        m_useTail->m_next = obj;
    }
    if (m_useHead == nullptr) {
        m_useHead = obj;
    }
    obj->m_prev = m_useTail;
    obj->m_next = nullptr;
    m_useTail = obj;
    m_freeCount--;
    m_useCount++;
    obj->m_user = nullptr;
    obj->m_userWork = nullptr;
    obj->m_flags = 0;
    return obj;
}

inline DrPixlPostMan::VolumeWork::VolumeWork(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : m_drMan(drMan), m_pixlMan(pixlMan), m_postMan(postMan), m_flag(false) {
    m_volume[0] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) RenderVolume(m_drMan);
    m_volume[0]->setTextureInfo(16.0f, 16.0f, 16.0f, static_cast<GrlSurfaceFormat>(0x25), false, 0);
    m_volume[1] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) RenderVolume(m_drMan);
    m_volume[1]->setTextureInfo(16.0f, 16.0f, 16.0f, static_cast<GrlSurfaceFormat>(0x25), false, 0);
}

DrPixlPostMan::DrPixlPostMan(DrMan* drMan, DrPixlMan* pixlMan, int)
    : m_drMan(drMan), m_pixlMan(pixlMan), m_volumeWork(nullptr), m_toneMap(nullptr), m_bloom(nullptr),
      m_volume(nullptr), m_depthOfField(nullptr), m_fxaa(nullptr), m_cubeMapMultiIBL(nullptr), m_cubeMapIBL(nullptr),
      m_motionBlur(nullptr), m_motionBlur2(nullptr), m_histgram(nullptr), m_tmaa(nullptr), m_ssr(nullptr),
      m_tssao(nullptr), m_expStencil(nullptr), m_skyDome(nullptr), m_toonGrad(nullptr), m_rainDrop(nullptr),
      m_glassBr(nullptr), m_capture(nullptr), m_unbranchToDepth(nullptr), m_downDepth(), m_refraction(nullptr),
      m_refractionHalf(nullptr), m_quaterNormal(nullptr), m_depthBuff(nullptr), m_refractionQuery(nullptr), m_flags(0),
      m_waterFog(0.0f) {
    m_volumeWork = new (m_drMan->m_workHandle, nullptr, 0, 4, false) VolumeWork(m_drMan, m_pixlMan, this);
    m_toneMap = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjToneMap(m_drMan, m_pixlMan, this);
    m_fxaa = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjFxAA(m_drMan, m_pixlMan, this);
    m_cubeMapMultiIBL = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjCubeMapMultiIBL(m_drMan, m_pixlMan, this);
    m_cubeMapIBL = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjCubeMapIBL(m_drMan, m_pixlMan, this);
    m_downDepth[0] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_downDepth[1] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_quaterNormal = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_depthBuff = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_bloom = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjBloom(m_drMan, m_pixlMan, this);
    m_volume = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjVolume(m_drMan, m_pixlMan, this);
    m_skyDome = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlSkyDome(m_drMan);
    m_rainDrop = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjRainDrop(m_drMan, m_pixlMan, this);
    m_toonGrad = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlToonGrad(m_drMan);
    m_tmaa = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjTMAA(m_drMan, pixlMan, this);
    m_ssr = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjSSR(m_drMan, pixlMan, this);
    m_tssao = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjTSSAO(m_drMan, pixlMan, this);
    m_expStencil = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjExpStencil(m_drMan);
    m_refractionQuery = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrResUseQueryObj();
    m_histgram = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjHistgram(m_drMan, m_pixlMan, this);
    m_unbranchToDepth = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjUnbranchToDepth(m_drMan, m_pixlMan, this);
    m_shadowRaytrace = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlShadowRaytrace(m_drMan);
    setupDepthBuff();
    m_refractionHalf = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
}

DrPixlPostMan::~DrPixlPostMan() {
    if (m_refractionQuery != nullptr) {
        delete m_refractionQuery;
        m_refractionQuery = nullptr;
    }
    if (m_shadowRaytrace != nullptr) {
        delete m_shadowRaytrace;
        m_shadowRaytrace = nullptr;
    }
    if (m_expStencil != nullptr) {
        delete m_expStencil;
        m_expStencil = nullptr;
    }
    if (m_downDepth[0] != nullptr) {
        delete m_downDepth[0];
        m_downDepth[0] = nullptr;
    }
    if (m_downDepth[1] != nullptr) {
        delete m_downDepth[1];
        m_downDepth[1] = nullptr;
    }
    if (m_quaterNormal != nullptr) {
        delete m_quaterNormal;
        m_quaterNormal = nullptr;
    }
    if (m_refraction != nullptr) {
        delete m_refraction;
        m_refraction = nullptr;
    }
    if (m_refractionHalf != nullptr) {
        delete m_refractionHalf;
        m_refractionHalf = nullptr;
    }
    if (m_depthBuff != nullptr) {
        delete m_depthBuff;
        m_depthBuff = nullptr;
    }
    if (m_toonGrad != nullptr) {
        delete m_toonGrad;
        m_toonGrad = nullptr;
    }
    if (m_skyDome != nullptr) {
        delete m_skyDome;
        m_skyDome = nullptr;
    }
    if (m_rainDrop != nullptr) {
        delete m_rainDrop;
        m_rainDrop = nullptr;
    }
    if (m_fxaa != nullptr) {
        delete m_fxaa;
        m_fxaa = nullptr;
    }
    if (m_volumeWork != nullptr) {
        delete m_volumeWork;
        m_volumeWork = nullptr;
    }
    if (m_toneMap != nullptr) {
        delete m_toneMap;
        m_toneMap = nullptr;
    }
    if (m_bloom != nullptr) {
        delete m_bloom;
        m_bloom = nullptr;
    }
    if (m_volume != nullptr) {
        delete m_volume;
        m_volume = nullptr;
    }
    if (m_depthOfField != nullptr) {
        delete m_depthOfField;
        m_depthOfField = nullptr;
    }
    if (m_motionBlur != nullptr) {
        delete m_motionBlur;
        m_motionBlur = nullptr;
    }
    if (m_motionBlur2 != nullptr) {
        delete m_motionBlur2;
        m_motionBlur2 = nullptr;
    }
    if (m_cubeMapMultiIBL != nullptr) {
        delete m_cubeMapMultiIBL;
        m_cubeMapMultiIBL = nullptr;
    }
    if (m_cubeMapIBL != nullptr) {
        delete m_cubeMapIBL;
        m_cubeMapIBL = nullptr;
    }
    if (m_histgram != nullptr) {
        delete m_histgram;
        m_histgram = nullptr;
    }
    if (m_tmaa != nullptr) {
        delete m_tmaa;
        m_tmaa = nullptr;
    }
    if (m_ssr != nullptr) {
        delete m_ssr;
        m_ssr = nullptr;
    }
    if (m_tssao != nullptr) {
        delete m_tssao;
        m_tssao = nullptr;
    }
    if (m_glassBr != nullptr) {
        delete m_glassBr;
        m_glassBr = nullptr;
    }
    if (m_capture != nullptr) {
        delete m_capture;
        m_capture = nullptr;
    }
    if (m_unbranchToDepth != nullptr) {
        delete m_unbranchToDepth;
        m_unbranchToDepth = nullptr;
    }
}


void DrPixlPostMan::setBlur(bool on) {
    if (on) {
        m_flags |= 0x80040;
        if (m_motionBlur2 == nullptr) {
            m_motionBlur2 = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjMotionBlur2(m_drMan, m_pixlMan, this);
        }
    } else if (m_flags & 0x40) {
        if (m_motionBlur != nullptr) {
            delete m_motionBlur;
            m_motionBlur = nullptr;
        }
        if (m_motionBlur2 != nullptr) {
            delete m_motionBlur2;
            m_motionBlur2 = nullptr;
        }
        m_flags &= ~0x40;
    }
}

void DrPixlPostMan::setDepthField(bool on) {
    if (on) {
        m_flags |= 0x80020;
        if (m_depthOfField == nullptr) {
            m_depthOfField = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlPostObjDepthofField(m_drMan, m_pixlMan, this);
        }
    } else if (m_flags & 0x20) {
        m_flags &= ~0x20;
        if (m_depthOfField != nullptr) {
            delete m_depthOfField;
            m_depthOfField = nullptr;
        }
    }
}

void DrPixlPostMan::setVolumePos(const mm::Vec3& pos) {
    if (m_volume != nullptr) {
        m_volume->m_pos = pos;
    }
}

DrPixlMemMan::DrPixlMemMan() { setupMemBuff(); }

DrPixlMemMan::~DrPixlMemMan() {}

DrPixlPostObj::DrPixlPostObj(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : m_drMan(drMan), m_pixlMan(pixlMan), m_postMan(postMan) {}

float DrPixlPostObj::gaussianDistribution(float x, float y, float rho) {
    float g = 1.0f / sqrtf(2.0f * 3.14159265f * rho * rho);
    return g * expf((x * x + y * y) / (-2.0f * rho * rho));
}

// binds target's texture at location with point (or, with filter, linear) sampling and sets the vec4 at ofs to a
// unit scale and zero offset; the shader is not used
void DrPixlPostObj::setUVScale_UB(grlib::CGLibUniformEtcUtility& uniform, DrShdDataObj*, const DrPixlRenderTarget* target,
                                  bool filter, unsigned int location, unsigned int ofs) {
    DrAPCache* cache = m_drMan->m_apCache;
    mm::Vec4 scale(1.0f, 1.0f, 0.0f, 0.0f);
    if (filter) {
        cache->beginTexSampling(2, 1);
    } else {
        cache->beginTexSampling(2, 0);
    }
    cache->setTexture(*target->m_pTexture, location);
    uniform.setF32SetVec4(ofs, &scale.x);
}

void DrPixlPostObj::calc1PixlOfs(float& width, float& height) {
    int w = (int)width;
    int h = (int)height;
    width = (float)(w + (w & 1));
    height = (float)(h + (h & 1));
}

DrPixlTileParm::~DrPixlTileParm() {}

float DrPixlPostObjBloom::BLOOMTEX_SCALE = 0.25f;

void DrPixlPostObjBloom::resetColorBuff(bool all) {
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    float width;
    float height;
    if (parm->m_reduction) {
        DrMan* drMan = DrMan::getIns();
        float scale = parm->m_bloomReductionScale[0];
        if (drMan->m_qualityMode == 0) {
            width = scale * parm->m_bloomAspect[0];
            height = parm->m_bloomReductionScale[1] * parm->m_bloomAspect[1];
            DrMan::ViewInfo* view = m_drMan->m_curViewInfo;
            float screen = (scale * (float)view->m_captureWidth) / (scale * (float)view->m_captureHeight);
            float target = (parm->m_bloomAspect[0] / parm->m_bloomAspect[1]) * screen;
            if (screen < target) {
                height *= target / screen;
            } else {
                width *= screen / target;
            }
        } else {
            width = scale;
            height = parm->m_bloomReductionScale[1];
        }
    } else {
        width = 1.0f;
        height = 1.0f;
    }
    DrMan::ViewInfo* view = m_drMan->m_curViewInfo;
    createBloomTexture(width * ((float)view->m_captureWidth * BLOOMTEX_SCALE),
                       height * (BLOOMTEX_SCALE * (float)view->m_captureHeight), all);
}

void DrPixlPostObjBloom::releaseColorBuff(bool all) {
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    if (parm->m_iblColorMode == 3 || all) {
        m_dblBuff[0]->releaseTexture();
        m_dblBuff[1]->releaseTexture();
    } else {
        m_dblBuff[DrMan::s_nDblIdx]->releaseTexture();
    }
    if (parm->m_iblColorMode == 2 && !all) {
        return;
    }
    m_bloomBuff[0]->releaseTexture();
    m_bloomBuff[1]->releaseTexture();
    for (int i = 0; i < 5; i++) {
        m_scaleBuff[i]->releaseTexture();
        m_scaleWorkBuff[i]->releaseTexture();
    }
    m_bloomBuff[2]->releaseTexture();
    m_bloomBuff[3]->releaseTexture();
}

void DrPixlPostObjMotionBlur::render() {
    DrAPGxType::setupScreenQuads(false);
    calcBlurWork();
    if (!m_drMan->m_calcMan->m_pViewWork->m_velocityBlurOff) {
        DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
        if (parm->m_velocityBlur && parm->m_velocityBlurRate > 0.0f) {
            calcVelocityBlur();
        }
    }
    m_drMan->blurCallBackRender();
    m_blurVel[0]->setColorInvalidate();
    renderCalcBlur();
    lastRender();
}

void DrPixlPostObjBloom::calcRender() {
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    int type = parm->m_bloomType;
    if (m_bloomType != type) {
        BLOOMTEX_SCALE = type == 1 ? 0.25f : 0.5f;
        releaseColorBuff(true);
        resetColorBuff(true);
        m_flags |= 1;
        m_bloomType = type;
    }
    DrAPGxType::setupScreenQuads(false);
    if (m_drMan->m_postParm[m_drMan->m_postParmIdx]->isBlm2PassExtract()) {
        calculateDownScaleImpl(DownScale_2PassFirst);
        grlib::CGLibCtlShader::setMemoryBarrierBit(2);
        calculateDownScaleImpl(DownScale_2PassSecond);
    } else {
        calculateDownScaleImpl(DownScale_Normal);
    }
    calculateGaussBlur();
}

void DrPixlPostObjBloom::calcCollectRender(bool withVolume) {
    DrAPGxType::setupBlend(0);
    m_bloomBuff[0]->setRenderTarget();
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrShdDataObj* obj = list->getPostShdObj(9);
    unsigned int volumeIdx = withVolume ? 1 : 2;
    obj->setDeclarationIdx(obj->getDeclarationOfs("DECL_WITH_VOLUME"), volumeIdx);
    unsigned int lumaIdx = parm->m_bloomType == 1 ? 1 : 2;
    obj->setDeclarationIdx(obj->getDeclarationOfs("USE_LUMA4"), lumaIdx);
    bool secondPass = parm->m_bloomBuffSel;
    list->bindQuadsTex();
    obj->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    setShaderBloom(obj, uniform);
    DrAPCache* cache = m_drMan->m_apCache;
    unsigned int volumeLoc = obj->getCurrentShader().getTextureLocation("vl");
    cache->setTexture(*m_postMan->m_volume->m_volumeBuff[2]->m_pTexture, volumeLoc);
    unsigned int ofs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gScal");
    float width = m_bloomBuff[0]->m_width;
    float height = m_bloomBuff[0]->m_height;
    float vec[4];
    vec[0] = (width - 1.0f) / width;
    vec[1] = (height - 1.0f) / height;
    vec[2] = 1.0f / (width + width);
    vec[3] = 1.0f / (height + height);
    uniform.setF32SetVec4(ofs, vec);
    ofs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gParm");
    vec[0] = m_pixlMan->m_objTbl->m_toneMapVal[0];
    vec[1] = vec[2] = vec[3] = 0.0f;
    uniform.setF32SetVec4(ofs, vec);
    uniform.updateData();
    uniform.setUniformBlock();
    list->renderQuads();
    m_bloomBuff[0]->setColorInvalidate();
    if (secondPass) {
        grlib::CGLibCtlShader::setMemoryBarrierBit(2);
        m_bloomBuff[1]->setRenderTarget();
        DrShdDataObj* obj2 = list->getPostShdObj(0x43);
        list->bindQuadsTex();
        obj2->setupShader(0u);
        grlib::CGLibUniformEtcUtility uniform2(obj2);
        uniform2.setUseUniformBlock("U_POST");
        unsigned int location = obj2->getCurrentShader().getTextureLocation("b");
        cache->beginTexSampling(2, 1);
        cache->setTexture(*m_bloomBuff[0]->m_pTexture, location);
        ofs = uniform2.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform2.m_location, "gScal");
        float width2 = m_bloomBuff[1]->m_width;
        float height2 = m_bloomBuff[1]->m_height;
        vec[0] = (width2 - 1.0f) / width2;
        vec[1] = (height2 - 1.0f) / height2;
        vec[2] = 1.0f / (width2 + width2);
        vec[3] = 1.0f / (height2 + height2);
        uniform2.setF32SetVec4(ofs, vec);
        ofs = uniform2.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform2.m_location, "gParm");
        vec[0] = 0.0f;
        vec[1] = 0.0f;
        vec[2] = 1.0f / width2;
        vec[3] = 1.0f / height2;
        uniform2.setF32SetVec4(ofs, vec);
        uniform2.updateData();
        uniform2.setUniformBlock();
        list->renderQuads();
    }
}

grlib::CGLibTextureBuffer* DrPixlPostMan::getToonGradTex() const {
    return m_toonGrad != nullptr ? &m_toonGrad->getGradTex() : nullptr;
}

grlib::CGLibTextureBuffer* DrPixlPostMan::getToonDarkGradTex() const {
    return m_toonGrad != nullptr ? &m_toonGrad->getDarkGradTex() : nullptr;
}

DrPixlPostObjBloom::DrPixlPostObjBloom(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), m_bloomBuff(), m_scaleBuff(), m_perFrame(0), m_flags(0) {
    m_bloomBuff[0] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_bloomBuff[1] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_bloomBuff[2] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_bloomBuff[3] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    for (int i = 0; i < 5; i++) {
        m_scaleBuff[i] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
        m_scaleWorkBuff[i] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    }
    for (int i = 0; i < 2; i++) {
        m_dblBuff[i] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    }
    m_flags |= 1;
    m_bloomType = 0;
}

void DrPixlPostObjBloom::releaseBloomTexture() {
    for (int i = 0; i < 4; i++) {
        if (m_bloomBuff[i]) {
            delete m_bloomBuff[i];
            m_bloomBuff[i] = nullptr;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (m_scaleBuff[i]) {
            delete m_scaleBuff[i];
            m_scaleBuff[i] = nullptr;
        }
        if (m_scaleWorkBuff[i]) {
            delete m_scaleWorkBuff[i];
            m_scaleWorkBuff[i] = nullptr;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (m_dblBuff[i]) {
            delete m_dblBuff[i];
            m_dblBuff[i] = nullptr;
        }
    }
}

void DrPixlPostObjBloom::calculateGaussBlur() {
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    calculateGaussBlurImplPS();
    if (parm->m_lensFlare) {
        calculateFlareBuff();
        calculateLensFlare();
        DrAPGxType::setupBlend(2);
        m_scaleBuff[2]->setRenderTarget();
        setScaleShader(m_bloomBuff[3]);
        m_scaleBuff[2]->setColorInvalidate();
        DrAPGxType::setupBlend(0);
    }
}

void DrPixlPostObjBloom::calculateLensFlare() {
    m_bloomBuff[3]->setRenderTarget();
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrShdDataObj* obj = list->getPostShdObj(7);
    list->bindQuadsTex();
    obj->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_CMN");
    DrAPCache* cache = m_drMan->m_apCache;
    unsigned int location = obj->getCurrentShader().getTextureLocation("s0");
    unsigned int scaleOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gScal");
    unsigned int ratioOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "ratio");
    cache->beginBorderBlack();
    cache->setTexture(*m_bloomBuff[2]->m_pTexture, location);
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    float width = m_bloomBuff[2]->m_width;
    float height = m_bloomBuff[2]->m_height;
    float scaleX = (width - 1.0f) / width;
    float scaleY = (height - 1.0f) / height;
    float vec[4];
    vec[0] = scaleX;
    vec[1] = scaleY;
    vec[2] = 1.0f / (width + width);
    vec[3] = 1.0f / (height + height);
    uniform.setF32SetVec4(scaleOfs, vec);
    vec[0] = parm->m_lensFlareRatio[0];
    vec[1] = parm->m_lensFlareRatio[1];
    vec[2] = parm->m_lensFlareRatio[2] * 0.1f;
    vec[3] = parm->m_lensFlareRatio[3];
    uniform.setF32SetVec4(ratioOfs, vec);
    grlib::CGLibUniformEtcUtility loop(obj);
    loop.setUseUniformBlock("U_LOOP");
    unsigned int spuvOfs = loop.m_pDecShader->getCurrentShader().getUniformBlockValOfs(loop.m_location, "spuv");
    float angle = parm->m_lensFlareAngle * 0.017453292f;
    float uvX = 1.0f / width * scaleX;
    float uvY = 1.0f / height * scaleY;
    vec[0] = uvX * cosf(angle);
    vec[1] = uvY * sinf(angle);
    vec[2] = parm->m_lensFlareSpread + 0.8f;
    vec[3] = 0.0f;
    loop.setF32SetVec4(spuvOfs, vec);
    uniform.updateData();
    uniform.setUniformBlock();
    loop.updateData();
    loop.setUniformBlock();
    list->renderQuads();
    int num = parm->m_lensFlareNum;
    if (num != 0) {
        DrAPGxType::setupBlend(2);
        for (int i = 1; i < num; i++) {
            grlib::CGLibUniformEtcUtility each(obj);
            each.setUseUniformBlock("U_LOOP");
            angle += 1.0f / (float)num * 3.1415927f;
            vec[0] = uvX * cosf(angle);
            vec[1] = uvY * sinf(angle);
            if (parm->m_reduction) {
                float scaleW = parm->m_reductionScale[0];
                float scaleH = parm->m_reductionScale[1];
                vec[0] /= scaleW;
                vec[1] /= scaleH;
            }
            each.setF32SetVec4(spuvOfs, vec);
            each.updateData();
            each.setUniformBlock();
            list->renderQuads();
        }
    }
    m_bloomBuff[3]->setColorInvalidate();
}

DrPixlPostObjDepthofField::~DrPixlPostObjDepthofField() {
    for (int i = 0; i < 3; i++) {
        if (m_calcBuff[i] != nullptr) {
            delete m_calcBuff[i];
            m_calcBuff[i] = nullptr;
        }
    }
    if (m_lastBuff != nullptr) {
        delete m_lastBuff;
        m_lastBuff = nullptr;
    }
    if (m_autoBuff != nullptr) {
        delete m_autoBuff;
        m_autoBuff = nullptr;
    }
    if (m_calcSampBuff != nullptr) {
        delete m_calcSampBuff;
        m_calcSampBuff = nullptr;
    }
    if (m_float2Buff != nullptr) {
        delete m_float2Buff;
        m_float2Buff = nullptr;
    }
}

DrPixlPostObjMotionBlur::~DrPixlPostObjMotionBlur() {
    for (int i = 0; i < 2; i++) {
        if (m_blurVel[i] != nullptr) {
            delete m_blurVel[i];
            m_blurVel[i] = nullptr;
        }
    }
    if (m_blurOut != nullptr) {
        delete m_blurOut;
        m_blurOut = nullptr;
    }
}

DrPixlPostObjVolume::~DrPixlPostObjVolume() {
    for (int i = 0; i < 3; i++) {
        if (m_volumeBuff[i] != nullptr) {
            delete m_volumeBuff[i];
            m_volumeBuff[i] = nullptr;
        }
    }
}

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

bool DrPixlPostParm::getSSROn() const {
    if (DrMan::getIns()->m_pixlMan->m_objTbl->m_postMan->m_waterFog < 0.01f) {
        return false;
    }
    if (DrMan::getIns()->m_calcMan->m_pViewWork->m_gpuCheckAllVisible && m_ssrGpuCheckOff) {
        return false;
    }
    return m_ssr;
}


DrPixlRenderTarget::DrPixlRenderTarget(DrMan* drMan) { m_drMan = drMan; }

DrPixlRenderTarget::~DrPixlRenderTarget() { releaseWork(); }

DrPixlRenderCubeMapMipMap::DrPixlRenderCubeMapMipMap(DrMan* drMan) { m_drMan = drMan; }

DrPixlRenderCubeMapMipMap::~DrPixlRenderCubeMapMipMap() { releaseWork(); }

void DrPixlShadowCacheMan::buffUpdate() {
    createCacheBuff();
    DrMan::get();
    if (m_flags & 2) {
        for (int i = 0; i < 4; i++) {
            m_workTbl[i].m_dirDepth.release();
        }
        m_flags &= ~2;
    }
    m_flags |= 2;
    resetColorBuff();
}

unsigned int DrPixlShadowCacheMan::clipDirShadowChk(const mm::Vec3& pos, float radius, bool skipView) {
    if (!(m_flags & 8)) {
        return 0;
    }
    if (!skipView) {
        DrCalcViewWork* viewWork = DrMan::get()->m_calcMan->m_pViewWork;
        const mm::Vec3& dir = m_lightDir;
        if (!viewWork->m_clipPoli.clipLineTest(pos, dir, radius)) {
            return 0;
        }
    }
    unsigned int result = 0;
    for (int i = 0; i < 3; i++) {
        int type = m_dirClip[i].clipTypeTest(pos, radius);
        if (type == 0) {
            continue;
        }
        result |= 0x800 << i;
        if (type != 2) {
            break;
        }
    }
    return result;
}

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

DrPixlShadowMan::~DrPixlShadowMan() { releaseTexWork(); }

void DrPixlShadowMan::releaseTexWork() {
    for (int i = 0; i < 16; i++) {
        if (m_texWork[i].m_useCount != 0) {
            m_texWork[i].release();
        }
    }
}

void DrPixlShadowMan::releaseShadow(DrPixlShadowObj* obj) {
    for (int i = 0; i < m_objNum; i++) {
        if (m_objs[i] == obj) {
            TexWork* work = obj->m_depthTarget;
            if (work->m_useCount != 0 && --work->m_useCount == 0) {
                work->release();
                work->m_type = 0;
                work->m_index = 0;
                work->m_size = 0.0f;
                work->m_useCount = 0;
            }
            delete obj;
            for (int j = i + 1; j < m_objNum; j++) {
                m_objs[j - 1] = m_objs[j];
            }
            m_objNum--;
            return;
        }
    }
}

bool DrPixlShadowMan::setAddObjPos(mm::Vec3 const& pos, float radius) {
    DrMan* drMan = m_drMan;
    if (drMan->m_postParm[drMan->m_postParmIdx]->m_shadowAddObjPos && m_dirShadow) {
        return m_dirShadow->setAddObjPos(pos, radius);
    }
    return false;
}

bool DrPixlShadowMan::setSptCalcPos(mm::Vec3 const& pos, float radius) {
    bool result = false;
    for (int i = 0; i < m_objNum; i++) {
        DrPixlShadowObj* obj = m_objs[i];
        if (obj->m_active != 0) {
            result |= obj->setSptCalcPos(pos, radius);
        }
    }
    return result;
}

void DrPixlShadowObj::renderSetup() {
    if (!(m_flags & 1)) {
        m_depthTarget->clearDepth(false);
        m_drMan->m_apCache->shadowBegin();
        DrAPGxType::beginShadow();
        m_drMan->m_pixlMan->m_renderTarget = 0;
        m_depthTarget->setRenderTarget();
        m_drMan->m_calcMan->m_pViewWork->shadowBegin(m_parmTbl);
        m_flags |= 1;
    }
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

bool DrPixlShadowObjDir::clipChk(mm::Vec3 const& pos, float radius, bool noLineTest) {
    if (!(m_flags & 8) || m_typeClipRange <= radius) {
        return false;
    }
    bool hit = m_clip.clipTest(pos, radius);
    if (noLineTest || !hit) {
        return hit;
    }
    return m_drMan->m_calcMan->m_pViewWork->m_clipPoli.clipLineTest(pos, m_shadowDir, radius);
}

int DrPixlShadowObjDir::clipTypeChk(mm::Vec3 const& pos, float radius) {
    if (!(m_flags & 8) || m_typeClipRange <= radius) {
        return 0;
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

int DrPixlShadowObjSpt::clipTypeChk(mm::Vec3 const& pos, float radius) {
    if (m_clipRange < radius) {
        return 0;
    }
    return m_clip.clipTypeTest(pos, radius);
}

bool DrPixlShadowObjSpt::dispChk() { return (m_flags >> 1) & 1; }

void DrPixlShadowObjSpt::stockTile() {
    DrLightObjSpt* light = static_cast<DrLightObjSpt*>(m_lightObj);
    m_drMan->m_shdMan->m_lgtMan->m_pHybrid->stockSptList(light);
}

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
