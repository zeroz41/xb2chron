#define MM_LIB_FROM_XBRD
#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrCalcClipWorkCone.h"
#include "classes/ml/DrCalcClipWorkPlane.h"
#include "classes/ml/DrCalcClipWorkShadowPlane.h"
#include "classes/ml/DrLightObjLocalIBL.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrShdLgtClustered.h"
#include "classes/ml/DrShdLgtHybrid.h"
#include "classes/ml/DrShdLgtTileBasedDr.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnObjLightDrSys.h"
#include "classes/ml/ScnObjModelDrSys.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/navi/NvmshAcObj.h"
#include "classes/navi/NvmshManager.h"
#include "classes/navi/NvmshResMan.h"
#include "grlib/CGLibCtl.h"
#include "mm/Math.h"
#include "mtl/MemManager.h"
#include "grlib/CGLibUniBaseUtility.h"
#include "grlib/CGLibVtxIndex.h"
#include "grlib/CGLibVtxVertex.h"
#include "idcoli/IDColiGrandObj.h"
#include "idcoli/IDColiInput.h"
#include "idcoli/IDColiTreeTop.h"
#include "idcoli/IDColiUtilColi.h"
#include "ml/CriticalSection.h"
#include "ml/DrAPGxType.h"
#include "ml/DrCalcClipMan.h"
#include "ml/DrCalcGpuCost.h"
#include "ml/DrCalcMan.h"
#include "ml/DrCalcViewWork.h"
#include "ml/DrLightObjGlobalIBL.h"
#include "ml/DrPixlPostMan.h"
#include "ml/DrPixlPostParm.h"
#include "ml/DrPixlPostObjCapture.h"
#include "ml/DrPixlPostObjCubeMapMultiIBL.h"
#include "ml/DrPixlPostObjExpStencil.h"
#include "ml/DrPixlPostObjGlassBr.h"
#include "ml/DrPixlPostObjMotionBlur2.h"
#include "ml/DrPixlPostObjSSR.h"
#include "ml/DrPixlPostObjTMAA.h"
#include "ml/DrPixlPostObjTSSAO.h"
#include "ml/DrPixlPostObjUnbranchToDepth.h"
#include "ml/DrPixlShadowRaytrace.h"
#include "ml/DrRequetIBL.h"
#include "ml/DrResMdoUniformBlock.h"
#include "ml/DrShdCubeCapFilter.h"
#include "ml/DrShdDataList.h"
#include "ml/DrShdDataObj.h"
#include "ml/DrShdLgtMan.h"
#include "navi/NvmshAcMan.h"

namespace ml {

DrLightObjLocalIBL::~DrLightObjLocalIBL() {}

DrPixlPostObjCapture::DrPixlPostObjCapture(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), m_flags(3) {}

DrPixlPostObjCapture::~DrPixlPostObjCapture() {
    m_target.release();
    m_flags = 3;
}

void DrPixlPostObjCapture::update() {
    if (m_flags & 4) {
        m_flags |= 8;
        return;
    }
    if (m_flags & 1) {
        m_flags &= ~1;
        m_target.setTextureInfo(m_drMan->m_curViewInfo->m_captureWidth, m_drMan->m_curViewInfo->m_captureHeight,
                                static_cast<GrlSurfaceFormat>(DrAPCache::TEXTYPE_RGBA_8), false, 0);
    }
}

void DrPixlPostObjCapture::render() {
    if (!(m_flags & 4)) {
        DrAPGxType::setupScreenQuads(false);
        renderCaputre();
        renderDef();
        m_flags &= ~2;
    }
}

unsigned int DrPixlPostObjCubeMapMultiIBL::getPremMipCount() const { return m_premMipCount; }

bool DrPixlPostObjCubeMapMultiIBL::requestIBL(DrRequetIBL& request) {
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    if (!parm->m_multiIBL || m_requests.full()) {
        return false;
    }
    int count = 0;
    for (mm::mtl::FixedQueue<DrRequetIBL, 30>::iterator it = m_requests.begin(); it != m_requests.end(); ++it) {
        if ((*it).m_id == request.m_id) {
            if (*(*it).m_pState == 1) {
                return false;
            }
            if (++count == 4) {
                return false;
            }
        }
    }
    *request.m_pState = 1;
    m_requests.push_back(request);
    return true;
}

void DrPixlPostObjCubeMapMultiIBL::cancelIBL(unsigned long id) {
    const mm::mtl::FixedQueue<DrRequetIBL, 30>& requests = m_requests;
    for (mm::mtl::FixedQueue<DrRequetIBL, 30>::const_iterator it = requests.begin(); it != requests.end(); ++it) {
        if ((*it).m_id == id) {
            *(*it).m_pState = 3;
        }
    }
}

DrPixlPostObjExpStencil::DrPixlPostObjExpStencil(DrMan* drMan) : m_pDrMan(drMan) {}

DrPixlPostObjExpStencil::~DrPixlPostObjExpStencil() {}

void DrPixlPostObjExpStencil::render() {}

DrPixlPostObjGlassBr::DrPixlPostObjGlassBr(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan) {
    m_pPieceWork = nullptr;
    m_param[0] = 0.0f;
    m_param[1] = 0.0f;
    m_flags = 3;
    m_param[2] = 0.0f;
    m_time = 0.0f;
}

DrPixlPostObjGlassBr::~DrPixlPostObjGlassBr() {
    m_target.release();
    m_vertex.release();
    m_index.release();
    m_memPool.release();
    m_uniform.release();
    if (m_pPieceWork) {
        mtl::MemManager::deallocate(m_pPieceWork, 0, false);
        m_pPieceWork = nullptr;
    }
    m_flags = 3;
}

void DrPixlPostObjGlassBr::render() {
    if (!(m_flags & 4)) {
        DrAPGxType::setupScreenQuads(false);
        renderCaputre();
        renderGlass();
    }
}

DrPixlPostObjMotionBlur2::DrPixlPostObjMotionBlur2(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), m_blurOut(nullptr), m_velocityBuff(), m_vertexIdx(0), m_blurOn(true) {
    m_velocityBuff[0] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_velocityBuff[1] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_workOutA = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_maskBuff = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_workOutB = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_blurOut = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    for (int i = 0; i < 2; i++) {
        m_vertex[i] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) grlib::CGLibVtxVertex();
    }
    calcBludBuffColorBuff();
    m_state = 0;
}

DrPixlPostObjMotionBlur2::~DrPixlPostObjMotionBlur2() {
    for (int i = 0; i < 2; i++) {
        if (m_vertex[i]) {
            delete m_vertex[i];
            m_vertex[i] = nullptr;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (m_velocityBuff[i]) {
            delete m_velocityBuff[i];
            m_velocityBuff[i] = nullptr;
        }
    }
    if (m_workOutA) {
        delete m_workOutA;
        m_workOutA = nullptr;
    }
    if (m_maskBuff) {
        delete m_maskBuff;
        m_maskBuff = nullptr;
    }
    if (m_workOutB) {
        delete m_workOutB;
        m_workOutB = nullptr;
    }
    if (m_blurOut) {
        delete m_blurOut;
        m_blurOut = nullptr;
    }
}

void DrPixlPostObjMotionBlur2::resetColorBuff() { calcBludBuffColorBuff(); }

void DrPixlPostObjMotionBlur2::update() {}

void DrPixlPostObjMotionBlur2::render() {
    DrAPGxType::setupScreenQuads(false);
    calcBlurWork();
    if (!m_drMan->m_calcMan->m_pViewWork->m_gpuCheckAllVisible &&
        m_drMan->m_postParm[m_drMan->m_postParmIdx]->m_velocityBlur) {
        calcVelocityBlur();
    }
    m_drMan->blurCallBackRender();
    calcMaxVelocityPerTile();
    grlib::CGLibCtlShader::setMemoryBarrierBit(2);
    calcBlurMask();
    grlib::CGLibCtlShader::setMemoryBarrierBit(3);
    if (m_blurOn) {
        renderCalcBlur();
    }
    grlib::CGLibCtlShader::setMemoryBarrierBit(2);
    if (m_blurOn) {
        lastRender();
    }
}

DrPixlPostObjSSR::DrPixlPostObjSSR(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), m_flags(0) {
    m_buffFirst = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    for (int i = 0; i < 2; i++) {
        m_reflectionBuff[i] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    }
    m_buffLast = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_flags |= 3;
    resetColorBuff();
}

DrPixlPostObjSSR::~DrPixlPostObjSSR() {
    for (int i = 0; i < 2; i++) {
        if (m_reflectionBuff[i]) {
            delete m_reflectionBuff[i];
            m_reflectionBuff[i] = nullptr;
        }
    }
    if (m_buffFirst) {
        delete m_buffFirst;
        m_buffFirst = nullptr;
    }
    if (m_buffLast) {
        delete m_buffLast;
        m_buffLast = nullptr;
    }
}

void DrPixlPostObjSSR::render() {
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    if (!parm->getSSROn()) {
        m_flags |= 2;
        return;
    }
    if (m_flags & 2) {
        m_flags &= ~2;
        for (int i = 0; i < 2; i++) {
            m_reflectionBuff[i]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
        }
    }
    if (m_flags & 1) {
        m_reflectionBuff[DrMan::s_nDblIdx]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
        m_flags &= ~1;
    } else {
        raymarch2();
        temporalSuperSampling2();
    }
}

DrPixlRenderTarget* DrPixlPostObjSSR::getReflectionTexture() const { return m_reflectionBuff[DrMan::s_nDblIdx]; }

DrPixlPostObjTMAA::DrPixlPostObjTMAA(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), m_flags(0) {
    for (int i = 0; i < 2; i++) {
        m_colorBuff[i] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
        m_bloomBuff[i] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    }
    m_flags |= 1;
}

DrPixlPostObjTMAA::~DrPixlPostObjTMAA() {
    for (int i = 0; i < 2; i++) {
        if (m_colorBuff[i]) {
            delete m_colorBuff[i];
            m_colorBuff[i] = nullptr;
        }
        if (m_bloomBuff[i]) {
            delete m_bloomBuff[i];
            m_bloomBuff[i] = nullptr;
        }
    }
}

void DrPixlPostObjTMAA::render() {
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    if (!parm->getTMAAOn()) {
        return;
    }
    if (m_flags & 2) {
        for (int i = 0; i < 2; i++) {
            m_colorBuff[i]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
            m_bloomBuff[i]->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
        }
        m_flags &= ~2;
    }
    if (parm->m_tmaaReset) {
        m_flags |= 1;
        m_drMan->m_postParm[m_drMan->m_postParmIdx]->m_tmaaReset = false;
    }
    if (m_flags & 1) {
        m_flags &= ~4;
    } else {
        m_flags |= 4;
    }
    renderTMAA();
    if (m_flags & 1) {
        m_flags &= ~1;
    }
}

DrPixlRenderTarget* DrPixlPostObjTMAA::getBloomTexture() { return m_bloomBuff[DrMan::s_nDblIdx]; }

void DrPixlPostObjTMAA::renderSharpness() {
    if (DrMan::getIns()->m_qualityMode != 0) {
        renderSharpnessImpl(SHARPNESS_TYPE_4);
        return;
    }
    if (m_flags & 4) {
        renderSharpnessImpl(SHARPNESS_TYPE_1);
    }
    renderSharpnessImpl(SHARPNESS_TYPE_2);
}

DrPixlPostObjTSSAO::DrPixlPostObjTSSAO(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), m_flags(0), m_extraBuff(), m_frame(0) {
    m_workBuff = new (drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(drMan);
    for (int i = 0; i < 2; i++) {
        m_ssaoBuff[i] = new (drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(drMan);
        m_historyBuff[i] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(drMan);
    }
    m_blurBuffA = new (drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(drMan);
    m_blurBuffB = new (drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(drMan);
    m_outBuff = new (drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(drMan);
    resetColorBuff(true);
}

DrPixlPostObjTSSAO::~DrPixlPostObjTSSAO() {
    if (m_blurBuffB) {
        delete m_blurBuffB;
        m_blurBuffB = nullptr;
    }
    for (int i = 1; i >= 0; i--) {
        if (m_extraBuff[i]) {
            delete m_extraBuff[i];
            m_extraBuff[i] = nullptr;
        }
    }
    if (m_outBuff) {
        delete m_outBuff;
        m_outBuff = nullptr;
    }
    if (m_blurBuffA) {
        delete m_blurBuffA;
        m_blurBuffA = nullptr;
    }
    for (int i = 0; i < 2; i++) {
        if (m_ssaoBuff[i]) {
            delete m_ssaoBuff[i];
            m_ssaoBuff[i] = nullptr;
        }
        if (m_historyBuff[i]) {
            delete m_historyBuff[i];
            m_historyBuff[i] = nullptr;
        }
    }
    if (m_workBuff) {
        delete m_workBuff;
        m_workBuff = nullptr;
    }
}

void DrPixlPostObjTSSAO::update() { m_postMan->setDownDepth(); }

void DrPixlPostObjTSSAO::render_beforeTemporal() {
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    if (parm->m_ssao) {
        if (parm->m_ssaoQuaterNormal) {
            passQuaterNormal();
        }
        passSSAO();
        grlib::CGLibCtlShader::setMemoryBarrierBit(2);
        float blur = m_drMan->m_postParm[m_drMan->m_postParmIdx]->m_ssaoBlur;
        passBlur_Sub(BLUR_AXIS_1, blur, m_workBuff, m_blurBuffA, false);
        grlib::CGLibCtlShader::setMemoryBarrierBit(2);
        passBlur_Sub(BLUR_AXIS_2, blur, m_blurBuffA, m_workBuff, false);
        passTemporalFiltering();
    }
}

void DrPixlPostObjTSSAO::render_afterTemporal() {
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    if (parm->m_ssao) {
        float blur = parm->m_ssaoBlurAfter;
        DrPixlRenderTarget* buff = m_ssaoBuff[DrMan::s_nDblIdx];
        float weights[4];
        for (int i = 0; i < 4; i++) {
            weights[i] = gaussianDistribution(static_cast<float>(i), 0.0f, 1.0f);
        }
        passBlur_Sub(BLUR_AXIS_1, blur, buff, m_blurBuffA, false);
        grlib::CGLibCtlShader::setMemoryBarrierBit(2);
        passBlur_Sub(BLUR_AXIS_2, blur, m_blurBuffA, buff, false);
        passUpScaleToMiddle();
    }
}

DrPixlPostObjUnbranchToDepth::DrPixlPostObjUnbranchToDepth(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan) {}

DrPixlPostObjUnbranchToDepth::~DrPixlPostObjUnbranchToDepth() {}

void DrPixlPostObjUnbranchToDepth::render() {
    renderFull();
    if (m_drMan->m_unbranchQuater) {
        renderQuater();
    }
}

DrPixlShadowRaytrace::DrPixlShadowRaytrace(DrMan* drMan) : m_drMan(drMan), m_blurOn(true) {
    m_buffFirst = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    for (int i = 0; i < 2; i++) {
        m_temporalBuff[i] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    }
    m_buffFourth = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
    m_buffLast = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
}

DrPixlShadowRaytrace::~DrPixlShadowRaytrace() {
    if (m_buffLast) {
        delete m_buffLast;
        m_buffLast = nullptr;
    }
    if (m_buffFourth) {
        delete m_buffFourth;
        m_buffFourth = nullptr;
    }
    for (int i = 0; i < 2; i++) {
        if (m_temporalBuff[i]) {
            delete m_temporalBuff[i];
            m_temporalBuff[i] = nullptr;
        }
    }
    if (m_buffFirst) {
        delete m_buffFirst;
        m_buffFirst = nullptr;
    }
}

void DrPixlShadowRaytrace::render_beforeTemporal() {
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    raytracePass();
    if (m_blurOn) {
        m_buffFourth->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
        m_buffLast->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
        grlib::CGLibCtlShader::setMemoryBarrierBit(2);
        blurPassSub(BLUR_AXIS_1, m_buffFirst, m_buffFourth);
        grlib::CGLibCtlShader::setMemoryBarrierBit(2);
        blurPassSub(BLUR_AXIS_2, m_buffFourth, m_buffLast);
    }
    if (!parm->isShwRaytraceTemporalWithOthers()) {
        temporalFiltering();
    }
}

grlib::CGLibTextureBuffer* DrPixlShadowRaytrace::getScreenSpaceShadow() const {
    return m_temporalBuff[DrMan::s_nDblIdx]->m_pTexture;
}

DrPixlRenderTarget* DrPixlShadowRaytrace::getTemporalOutputTexture() { return m_temporalBuff[DrMan::s_nDblIdx]; }

DrPixlRenderTarget* DrPixlShadowRaytrace::getTemporalHistoryTexture() { return m_temporalBuff[DrMan::s_nDblStockIdx]; }

DrRequetIBL::DrRequetIBL(DrLightObjGlobalIBL* ibl) : m_pIBL(ibl), m_id(reinterpret_cast<unsigned long>(ibl)) {}

unsigned int DrRequetIBL::getTextureNum() const { return m_pIBL->m_textureNum; }

const grlib::CGLibTextureBuffer* DrRequetIBL::getTexture(unsigned int index) const { return &m_pIBL->m_texture[index]; }

const mm::Mat44* DrRequetIBL::getSHMatrix(unsigned int index, unsigned int term) const {
    return m_pIBL->m_shMatrix + (term + index * 4);
}

float DrRequetIBL::getSkyIntensity() const { return m_pIBL->m_skyIntensity; }

float DrRequetIBL::getDirLightIntensity() const { return m_pIBL->m_dirLightIntensity; }

const mm::Vec3* DrRequetIBL::getAdditionalAmbient() const { return &m_pIBL->m_additionalAmbient; }

unsigned int DrRequetIBL::getVersion() const { return m_pIBL->m_version; }

DrShdLgtHybrid::DrShdLgtHybrid(DrMan* drMan) {
    m_pDrMan = drMan;
    m_pClustered = new (drMan->m_workHandle, nullptr, 0, 4, false) DrShdLgtClustered(drMan, false);
    m_pTileBasedDr = new (drMan->m_workHandle, nullptr, 0, 4, false) DrShdLgtTileBasedDr(drMan);
}

DrShdLgtHybrid::~DrShdLgtHybrid() {
    if (m_pClustered) {
        delete m_pClustered;
        m_pClustered = nullptr;
    }
    if (m_pTileBasedDr) {
        delete m_pTileBasedDr;
        m_pTileBasedDr = nullptr;
    }
}

DrShdCubeCapFilter::DrShdCubeCapFilter(DrMan* drMan) : m_pDrMan(drMan) {}

DrShdCubeCapFilter::~DrShdCubeCapFilter() {}

void DrShdLgtHybrid::stockBegin() {
    m_pClustered->stockBegin();
    m_pTileBasedDr->stockBegin();
}

void DrShdLgtHybrid::stockEnd() {
    m_pClustered->stockEnd();
    m_pTileBasedDr->stockEnd();
}

void DrShdLgtHybrid::update() {
    m_pClustered->update();
    m_pTileBasedDr->update();
}

void DrShdLgtHybrid::setupCate(int cateIdx) {
    m_cateIdx = cateIdx;
    m_pClustered->setupCate(cateIdx);
    m_pTileBasedDr->setupCate(cateIdx);
}

void DrShdLgtHybrid::addViewInfo(int view) {
    m_pClustered->addViewInfo(view);
    m_pTileBasedDr->addViewInfo(view);
}

void DrShdLgtHybrid::delViewInfo(int view) {
    m_pClustered->delViewInfo(view);
    m_pTileBasedDr->delViewInfo(view);
}

void DrShdLgtHybrid::stockPntList(DrLightObjPnt* light) {
    m_pClustered->stockPntList(light);
    m_pTileBasedDr->stockPntList(light);
}

void DrShdLgtHybrid::stockSptList(DrLightObjSpt* light) {
    m_pClustered->stockSptList(light);
    m_pTileBasedDr->stockSptList(light);
}

void DrShdLgtHybrid::render(DrShdLgtMan* shdLgtMan, DrLightMan* lightMan) {
    switch (m_pDrMan->m_shdLgtType) {
    case 0:
        m_pTileBasedDr->render(shdLgtMan, lightMan);
        break;
    case 1:
        if (!DrMan::getIns()->m_clusteredRenderOff) {
            m_pClustered->render(shdLgtMan, lightMan);
        }
        break;
    }
}

void DrShdLgtHybrid::debugRender() {
    switch (m_pDrMan->m_shdLgtType) {
    case 0:
        m_pTileBasedDr->debugRender();
        break;
    case 1:
        m_pClustered->debugRender();
        break;
    }
}

ScnObjModelDrSys::ScnObjModelDrSys(Scn* scn, const void* res, const char* name)
    : ScnObjModel(scn, name), m_pMdlObj(nullptr), m_pRes(res), m_unkFlag(false), m_unkValue(0) {
    m_drMan = m_scn->m_renderDrSys->m_drMan;
}

void ScnObjModelDrSys::update() {}

void ScnObjModelDrSys::setGroups(int groups) { m_pMdlObj->setGroups(groups); }

int ScnObjModelDrSys::getGroups() { return m_pMdlObj->getGroups(); }

void ScnObjModelDrSys::setAlpha(float alpha) { m_pMdlObj->setAlpha(alpha); }

float ScnObjModelDrSys::getAlpha() const { return m_pMdlObj->getAlpha(); }

void ScnObjModelDrSys::setWriteStencil(bool enable) { m_pMdlObj->setWriteStencil(enable); }

void ScnObjModelDrSys::setAlwaysTexStm(bool enable) { m_pMdlObj->setAlwaysTexStm(enable); }

bool ScnObjModelDrSys::isMdlTexStm() const { return m_pMdlObj->isMdlTexStm(); }

bool ScnObjModelDrSys::isMemTexStm() const { return m_pMdlObj->isMemTexStm(); }

const mm::Vec3& ScnObjModelDrSys::getAABBMax() const { return m_pMdlObj->getAABBMax(); }

const mm::Vec3& ScnObjModelDrSys::getAABBMin() const { return m_pMdlObj->getAABBMin(); }

const mm::Vec3& ScnObjModelDrSys::getCenter() const { return m_pMdlObj->getCenter(); }

float ScnObjModelDrSys::getLength() const { return m_pMdlObj->getLength(); }

}  // namespace ml
