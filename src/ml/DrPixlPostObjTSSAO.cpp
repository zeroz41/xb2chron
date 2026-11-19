#define MM_LIB_FROM_XBRD
#include "classes/grlib/CGLibUniformEtcUtility.h"
#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrCalcClipWorkCone.h"
#include "classes/ml/DrCalcClipWorkPlane.h"
#include "classes/ml/DrCalcClipWorkShadowPlane.h"
#include "classes/ml/DrLightObjLocalIBL.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrPixlMemMan.h"
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
#include "grlib/CGLibState.h"
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
#include "ml/DrIniSys.h"
#include "ml/DrLightObjGlobalIBL.h"
#include "ml/DrPixlFormat.h"
#include "ml/DrPixlMan.h"
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
#include "ml/DrShdMan.h"
#include "ml/MTRand.h"
#include "navi/NvmshAcMan.h"

namespace ml {

DrLightObjLocalIBL::DrLightObjLocalIBL()
    : pad_30(0.0f, 0.0f, 0.0f), m_cubeTex(nullptr), m_mipBias(0), m_pos(0.0f, 0.0f, 0.0f), m_radius(0.0f),
      m_shapeType(2), pad_128(0), pad_1c0(2), pad_240(nullptr) {}

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

void DrPixlPostObjCapture::renderCaputre() {
    if (m_flags & 2) {
        m_target.setRenderTarget();
        DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
        DrShdDataObj* obj = list->getSelectShdObj(1);
        obj->setDeclarationIdx(obj->getDeclarationOfs("PIXL_TYPE"), 1);
        obj->setDeclarationIdx(obj->getDeclarationOfs("MRT_NUM"), 1);
        list->bindTriangleTex();
        obj->setupShader(0u);
        unsigned int location = obj->getCurrentShader().getTextureLocation("s0");
        DrAPCache* cache = m_drMan->m_apCache;
        cache->beginTexSampling(2, 0);
        cache->setTexture(*grlib::CGLibState::getMainRenderTarget()->m_pTexture, location);
        grlib::CGLibUniformEtcUtility uniform(obj);
        uniform.setUseUniformBlock("U_POST");
        unsigned int ofs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gScal");
        float scale[4];
        scale[0] = 1.0f;
        scale[1] = 1.0f;
        scale[2] = 0.0f;
        scale[3] = 0.0f;
        uniform.setF32SetVec4(ofs, scale);
        uniform.updateData();
        uniform.setUniformBlock();
        list->renderTriangle();
    }
}

void DrPixlPostObjCapture::renderDef() {
    grlib::CGLibState::setMainFrameBuffer();
    if (!(m_flags & 2)) {
        DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
        DrShdDataObj* obj = list->getSelectShdObj(1);
        obj->setDeclarationIdx(obj->getDeclarationOfs("PIXL_TYPE"), 1);
        obj->setDeclarationIdx(obj->getDeclarationOfs("MRT_NUM"), 1);
        list->bindTriangleTex();
        obj->setupShader(0u);
        unsigned int location = obj->getCurrentShader().getTextureLocation("s0");
        DrAPCache* cache = m_drMan->m_apCache;
        cache->beginTexSampling(2, 0);
        cache->setTexture(*m_target.m_pTexture, location);
        grlib::CGLibUniformEtcUtility uniform(obj);
        uniform.setUseUniformBlock("U_POST");
        unsigned int ofs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gScal");
        float scale[4];
        scale[0] = 1.0f;
        scale[1] = 1.0f;
        scale[2] = 0.0f;
        scale[3] = 0.0f;
        uniform.setF32SetVec4(ofs, scale);
        uniform.updateData();
        uniform.setUniformBlock();
        list->renderTriangle();
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

void DrPixlPostObjGlassBr::setup() {
    m_flags &= ~1;
    const GlassData* data = static_cast<const GlassData*>(m_drMan->m_iniSys->getGlassBreakage());
    m_pGlassData = data;
    m_memPool.setupBuffer(const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(data)) + data->m_bufferOfs,
                          data->m_bufferSize);
    m_vertex.createMemVertexBuff(&m_memPool, data->m_vertexOfs, data->m_vertexSize, 0xC);
    m_index.createMemIndexBuff(&m_memPool, data->m_indexOfs, data->m_indexCount, static_cast<GrlPrimitiveType>(4),
                               static_cast<GrlIndexFormat>(1));
    unsigned int size = data->m_pieceNum << 6;
    m_pieceNum = data->m_pieceNum;
    m_pPieceWork = mtl::MemManager::allocate(m_drMan->m_allocHandle, size, 0x10, false, "no name", 0);
    m_uniform.setup(m_pieceNum * 0x30 + 0x70);
    m_target.setTextureInfo(m_drMan->m_curViewInfo->m_captureWidth * 0.5f, m_drMan->m_curViewInfo->m_captureHeight * 0.5f,
                            static_cast<GrlSurfaceFormat>(DrAPCache::TEXTYPE_RGBA_8), false, 0);
    posInt();
}

void DrPixlPostObjGlassBr::render() {
    if (!(m_flags & 4)) {
        DrAPGxType::setupScreenQuads(false);
        renderCaputre();
        renderGlass();
    }
}

void DrPixlPostObjGlassBr::renderCaputre() {
    if (m_flags & 2) {
        m_flags &= ~2;
        m_target.setRenderTarget();
        DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
        DrShdDataObj* obj = list->getSelectShdObj(1);
        obj->setDeclarationIdx(obj->getDeclarationOfs("PIXL_TYPE"), 1);
        obj->setDeclarationIdx(obj->getDeclarationOfs("MRT_NUM"), 1);
        list->bindTriangleTex();
        obj->setupShader(0u);
        unsigned int location = obj->getCurrentShader().getTextureLocation("s0");
        DrAPCache* cache = m_drMan->m_apCache;
        cache->beginTexSampling(2, 1);
        cache->setTexture(*grlib::CGLibState::getMainRenderTarget()->m_pTexture, location);
        grlib::CGLibUniformEtcUtility uniform(obj);
        uniform.setUseUniformBlock("U_POST");
        unsigned int ofs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gScal");
        float scale[4];
        scale[0] = 1.0f;
        scale[1] = 1.0f;
        scale[2] = 0.0f;
        scale[3] = 0.0f;
        uniform.setF32SetVec4(ofs, scale);
        uniform.updateData();
        uniform.setUniformBlock();
        list->renderTriangle();
    }
}

void DrPixlPostObjGlassBr::renderGlass() {
    grlib::CGLibState::getMainRenderTarget()->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xF));
    grlib::CGLibState::setMainFrameBuffer();
    grlib::CGLibPolygon::setCullingFront();
    grlib::CGLibColorCtl::setBlendControl(static_cast<GrlBlendFunc>(5), static_cast<GrlBlendFunc>(6),
                                          static_cast<GrlBlendCombine>(1), static_cast<GrlLogicType>(3));
    DrShdDataObj* obj = m_drMan->m_shdMan->m_dataList->getPostShdObj(0x3D);
    obj->setupShader(0u);
    grlib::CGLibCtlVertex::setVertex(m_vertex);
    unsigned int location = obj->getCurrentShader().getTextureLocation("s0");
    DrAPCache* cache = m_drMan->m_apCache;
    cache->beginTexSampling(2, 1);
    cache->setTexture(*m_target.m_pTexture, location);
    unsigned int ofs = obj->getCurrentShader().getUniformBlockOfs("U_POST");
    m_uniform.setUniformBlock(ofs);
    m_index.drawIndex();
    grlib::CGLibColorCtl::setBlendOffControl(static_cast<GrlLogicType>(3));
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

void DrPixlPostObjMotionBlur2::renderCalcBlur() {
    m_blurOut->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
    DrAPGxType::setupScreenQuads(false);
    m_blurOut->setRenderTarget();
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    DrShdDataObj* obj = list->getPostShdObj(0x3A);
    unsigned int hlv = parm->m_motBlurHLvMode ? 1 : 2;
    obj->setDeclarationIdx(obj->getDeclarationOfs("DECL_HLV"), hlv);
    obj->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    unsigned int location0 = obj->getCurrentShader().getTextureLocation("s0");
    unsigned int location1 = obj->getCurrentShader().getTextureLocation("s1");
    unsigned int maskLocation = obj->getCurrentShader().getTextureLocation("gTBlurMask");
    unsigned int maxVelLocation = obj->getCurrentShader().getTextureLocation("sMaxVelocity");
    unsigned int ofs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "ofs[0]");
    unsigned int sizeOfS0 = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gSizeOfS0");
    unsigned int sizeOfMaxVelocity =
        uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gSizeOfMaxVelocity");
    unsigned int sizeOfOutput =
        uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gSizeOfOutput");
    unsigned int paramOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gParam");
    unsigned int posOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gPosOffset");
    DrPixlRenderTarget* hdrBuff = m_pixlMan->m_objTbl->m_hdrBuff[0];
    DrAPCache* cache = m_drMan->m_apCache;
    float hdrWidth = hdrBuff->m_width;
    float hdrHeight = hdrBuff->m_height;
    float velWidth = m_velocityBuff[0]->m_width;
    float velHeight = m_velocityBuff[0]->m_height;
    float maxWidth = m_workOutA->m_width;
    float maxHeight = m_workOutA->m_height;
    float offsets[12];
    offsets[0] = (hdrWidth - 1.0f) / hdrWidth;
    offsets[1] = (hdrHeight - 1.0f) / hdrHeight;
    offsets[2] = 1.0f / (hdrWidth + hdrWidth);
    offsets[3] = 1.0f / (hdrHeight + hdrHeight);
    offsets[4] = (velWidth - 1.0f) / velWidth;
    offsets[5] = (velHeight - 1.0f) / velHeight;
    offsets[6] = 1.0f / (velWidth + velWidth);
    offsets[7] = 1.0f / (velHeight + velHeight);
    offsets[8] = (maxWidth - 1.0f) / maxWidth;
    offsets[9] = (maxHeight - 1.0f) / maxHeight;
    offsets[10] = 1.0f / (maxWidth + maxWidth);
    offsets[11] = 1.0f / (maxHeight + maxHeight);
    uniform.setF32SetF32Array(ofs, offsets, 12);
    mm::Vec4 sizeS0(hdrWidth, hdrHeight, 1.0f / hdrWidth, 1.0f / hdrHeight);
    uniform.setVec4SetVec4(sizeOfS0, sizeS0);
    mm::Vec4 sizeMaxVelocity;
    sizeMaxVelocity.x = m_workOutA->m_width;
    sizeMaxVelocity.y = m_workOutA->m_height;
    sizeMaxVelocity.z = 1.0f / sizeMaxVelocity.x;
    sizeMaxVelocity.w = 1.0f / sizeMaxVelocity.y;
    uniform.setVec4SetVec4(sizeOfMaxVelocity, sizeMaxVelocity);
    mm::Vec4 sizeOutput;
    sizeOutput.x = m_blurOut->m_width;
    sizeOutput.y = m_blurOut->m_height;
    sizeOutput.z = 1.0f / sizeOutput.x;
    sizeOutput.w = 1.0f / sizeOutput.y;
    uniform.setVec4SetVec4(sizeOfOutput, sizeOutput);
    float scale = 1.0f;
    if (parm->m_reduction) {
        scale = powf(parm->m_reductionScale[0] * parm->m_reductionScale[0] +
                         parm->m_reductionScale[1] * parm->m_reductionScale[1],
                     0.7f);
    }
    mm::Vec4 param;
    param.x = scale * parm->m_motBlurStrength;
    param.z = 0.0f;
    param.w = 0.0f;
    param.y = 0.0f;
    uniform.setVec4SetVec4(paramOfs, param);
    mm::Vec4 posOffset;
    posOffset.z = m_maskBuff->m_width;
    posOffset.w = m_maskBuff->m_height;
    posOffset.x = 1.0f / posOffset.z;
    posOffset.y = 1.0f / posOffset.w;
    posOffset.z = 0.5f / posOffset.z;
    posOffset.w = -0.5f / posOffset.w;
    uniform.setVec4SetVec4(posOfs, posOffset);
    cache->beginTexSampling(2, 1);
    cache->setTexture(*m_pixlMan->m_objTbl->m_hdrBuff[0]->m_pTexture, location0);
    cache->setTexture(*m_velocityBuff[0]->m_pTexture, location1);
    cache->setTexture(*m_workOutA->m_pTexture, maxVelLocation);
    cache->beginTexSampling(2, 0);
    cache->setTexture(*m_maskBuff->m_pTexture, maskLocation);
    uniform.updateData();
    uniform.setUniformBlock();
    grlib::CGLibCtlVertex::setVertex(*m_vertex[m_vertexIdx]);
    grlib::CGLibCtlVertex::renderVertex((GrlPrimitiveType)0, m_vertex[m_vertexIdx]->m_num);
    m_blurOut->setColorInvalidate();
}

void DrPixlPostObjMotionBlur2::lastRender() {
    DrPixlRenderTarget* hdrBuff = m_pixlMan->m_objTbl->m_hdrBuff[0];
    hdrBuff->setRenderTarget();
    DrAPGxType::setupBlend(1);
    DrShdDataObj* obj = m_drMan->m_shdMan->m_dataList->getPostShdObj(0x46);
    obj->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    unsigned int posOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gPosOffset");
    unsigned int fragOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gFragToUV");
    mm::Vec4 posOffset = mm::Vec4::zero;
    posOffset.x = 1.0f / m_maskBuff->m_width;
    posOffset.y = 1.0f / m_maskBuff->m_height;
    uniform.setVec4SetVec4(posOfs, posOffset);
    mm::Vec4 fragToUV = mm::Vec4::zero;
    fragToUV.x = 1.0f / hdrBuff->m_width;
    fragToUV.y = 1.0f / hdrBuff->m_height;
    uniform.setVec4SetVec4(fragOfs, fragToUV);
    uniform.updateData();
    uniform.setUniformBlock();
    unsigned int location0 = obj->getCurrentShader().getTextureLocation("s0");
    unsigned int location1 = obj->getCurrentShader().getTextureLocation("s1");
    DrAPCache* cache = m_drMan->m_apCache;
    cache->beginTexSampling(2, 1);
    cache->setTexture(*m_blurOut->m_pTexture, location0);
    cache->beginTexSampling(2, 0);
    cache->setTexture(*m_maskBuff->m_pTexture, location1);
    grlib::CGLibCtlVertex::setVertex(*m_vertex[m_vertexIdx]);
    grlib::CGLibCtlVertex::renderVertex((GrlPrimitiveType)0, m_vertex[m_vertexIdx]->m_num);
    DrAPGxType::setupBlend(0);
}

void DrPixlPostObjMotionBlur2::calcVelocityBlur() {
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    if (parm->m_velocityBlurScale <= 0.0f) {
        return;
    }
    DrAPCache* cache = m_drMan->m_apCache;
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrShdDataObj* obj = list->getPostShdObj(0x1C);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    list->bindQuadsTex();
    obj->setupShader(0u);
    unsigned int location = obj->getCurrentShader().getTextureLocation("s0");
    unsigned int ofs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "ofs[0]");
    float width = m_velocityBuff[1]->m_width * parm->m_velocityBlurScale;
    float height = parm->m_velocityBlurScale * m_velocityBuff[1]->m_height;
    float offsets[20];
    cache->beginTexSampling(2, 1);
    grlib::CGLibCtlShader::setMemoryBarrierBit(2);
    m_velocityBuff[1]->setRenderTarget();
    cache->setTexture(*m_velocityBuff[0]->m_pTexture, location);
    getSampleOffsets_GaussBlur_Horizontally(width, height, 2, offsets, 1.0f, 1.0f);
    uniform.setF32SetF32Array(ofs, offsets, 20);
    uniform.updateData();
    uniform.setUniformBlock();
    list->renderQuads();
    uniform.m_block.Rebuilding();
    grlib::CGLibUniBaseUtility& base = uniform;
    base.setMoveMem();
    m_velocityBuff[1]->setColorInvalidate();
    grlib::CGLibCtlShader::setMemoryBarrierBit(2);
    m_velocityBuff[0]->setRenderTarget();
    cache->setTexture(*m_velocityBuff[1]->m_pTexture, location);
    getSampleOffsets_GaussBlur_Verticaly(width, height, 2, offsets, 1.0f, 1.0f);
    uniform.setF32SetF32Array(ofs, offsets, 20);
    uniform.updateData();
    uniform.setUniformBlock();
    list->renderQuads();
    m_velocityBuff[0]->setColorInvalidate();
}

void DrPixlPostObjMotionBlur2::calcMaxVelocityPerTile() {
    DrAPCache* cache = m_drMan->m_apCache;
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrShdDataObj* obj = list->getPostShdObj(0x40);
    list->bindQuadsTex();
    obj->setupShader(0u);
    DrAPGxType::setupBlend(0);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    unsigned int location = obj->getCurrentShader().getTextureLocation("s0");
    unsigned int sizeOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "size");
    unsigned int ofs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "ofs[0]");
    cache->beginTexSampling(2, 1);
    m_workOutB->setRenderTarget();
    cache->setTexture(*m_velocityBuff[0]->m_pTexture, location);
    mm::Vec4 size;
    size.x = 1.0f / m_workOutB->m_width;
    size.y = 1.0f / m_workOutB->m_height;
    uniform.setVec4SetVec4(sizeOfs, size);
    float offsets[20];
    for (int i = 0; i < 5; i++) {
        offsets[i * 4 + 0] = i / static_cast<float>(m_velocityBuff[0]->m_width);
        offsets[i * 4 + 1] = 0.0f;
    }
    uniform.setF32SetF32Array(ofs, offsets, 20);
    uniform.updateData();
    uniform.setUniformBlock();
    list->renderQuads();
    uniform.m_block.Rebuilding();
    grlib::CGLibUniBaseUtility& base = uniform;
    base.setMoveMem();
    m_workOutB->setColorInvalidate();
    m_workOutA->setRenderTarget();
    cache->setTexture(*m_velocityBuff[1]->m_pTexture, location);
    size.x = 1.0f / m_workOutA->m_width;
    size.y = 1.0f / m_workOutA->m_height;
    uniform.setVec4SetVec4(sizeOfs, size);
    for (int i = 0; i < 5; i++) {
        offsets[i * 4 + 0] = 0.0f;
        offsets[i * 4 + 1] = i / static_cast<float>(m_workOutB->m_height);
    }
    uniform.setF32SetF32Array(ofs, offsets, 20);
    uniform.updateData();
    uniform.setUniformBlock();
    list->renderQuads();
    m_workOutA->setColorInvalidate();
}

void DrPixlPostObjMotionBlur2::calcBlurMask() {
    DrAPCache* cache = m_drMan->m_apCache;
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrShdDataObj* obj = list->getPostShdObj(0x49);
    list->bindQuadsTex();
    obj->setupShader(0u);
    DrAPGxType::setupBlend(0);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    unsigned int location = obj->getCurrentShader().getTextureLocation("s0");
    unsigned int ofs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "vOfs");
    cache->beginTexSampling(2, 1);
    m_maskBuff->setRenderTarget();
    cache->setTexture(*m_workOutA->m_pTexture, location);
    mm::Vec4 vOfs;
    vOfs.x = 0.5f / m_maskBuff->m_width;
    vOfs.y = 0.5f / m_maskBuff->m_height;
    uniform.setVec4SetVec4(ofs, vOfs);
    uniform.updateData();
    uniform.setUniformBlock();
    list->renderQuads();
    m_maskBuff->setColorInvalidate();
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

const float DrPixlPostObjSSR::RAYMARCH_BUFFER_SCALE = 0.25f;
const float DrPixlPostObjSSR::TEMPORAL_BUFFER_SCALE = 0.5f;

void DrPixlPostObjSSR::resetColorBuff() {
    float width = m_drMan->m_curViewInfo->m_width;
    float height = m_drMan->m_curViewInfo->m_height;
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    if (parm->m_iblColorMode == 3) {
        for (unsigned int i = 0; i < 2; i++) {
            m_reflectionBuff[i]->setTextureInfo(width * TEMPORAL_BUFFER_SCALE, height * TEMPORAL_BUFFER_SCALE,
                                                DrPixlFormat::s_SsrFormat, true,
                                                DrPixlMemMan::get()->getSSROfs(i));
        }
    } else {
        unsigned int idx = DrMan::s_nDblIdx;
        m_reflectionBuff[idx]->setTextureInfo(width * TEMPORAL_BUFFER_SCALE, height * TEMPORAL_BUFFER_SCALE,
                                              DrPixlFormat::s_SsrFormat, true,
                                              DrPixlMemMan::get()->getSSROfs(idx));
    }
    if (parm->m_iblColorMode == 2) {
        return;
    }
    m_buffFirst->setTextureInfo(width * RAYMARCH_BUFFER_SCALE, height * RAYMARCH_BUFFER_SCALE, DrPixlFormat::s_SsrFormat, true,
                                DrPixlMemMan::get()->getSSROfs(2));
    m_buffLast->setTextureInfo(width * RAYMARCH_BUFFER_SCALE, height * RAYMARCH_BUFFER_SCALE, DrPixlFormat::s_DepthBufferFormat,
                               true, DrPixlMemMan::get()->getSSROfs(3));
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

void DrPixlPostObjTMAA::resetColorBuff() {
    float width = m_drMan->m_curViewInfo->m_width;
    float height = m_drMan->m_curViewInfo->m_height;
    if (m_drMan->m_postParm[m_drMan->m_postParmIdx]->m_iblColorMode == 3) {
        for (unsigned int i = 0; i < 2; i++) {
            m_colorBuff[i]->setTextureInfo(width, height, DrPixlFormat::s_TMAAFormat, true,
                                           DrPixlMemMan::get()->getTMAAOfs(i * 2));
            m_bloomBuff[i]->setTextureInfo(width, height, DrPixlFormat::s_TMAAFormat, true,
                                           DrPixlMemMan::get()->getTMAAOfs(i * 2 + 1));
        }
    } else {
        unsigned int idx = DrMan::s_nDblIdx;
        m_colorBuff[idx]->setTextureInfo(width, height, DrPixlFormat::s_TMAAFormat, true,
                                         DrPixlMemMan::get()->getTMAAOfs(idx * 2));
        m_bloomBuff[idx]->setTextureInfo(width, height, DrPixlFormat::s_TMAAFormat, true,
                                         DrPixlMemMan::get()->getTMAAOfs(idx * 2 + 1));
    }
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

const float DrPixlPostObjTSSAO::RAW_SSAO_SCALE = 0.25f;
const float DrPixlPostObjTSSAO::HISTORY_SCALE = 0.25f;
const float DrPixlPostObjTSSAO::BLUR_SCALE_LOW = 0.25f;
const float DrPixlPostObjTSSAO::UPSCALE_MIDDLE = 0.5f;

void DrPixlPostObjTSSAO::resetColorBuff(bool force) {
    float width = m_drMan->m_curViewInfo->m_width;
    float height = m_drMan->m_curViewInfo->m_height;
    m_frame = 0;
    float ssaoWidth = width * RAW_SSAO_SCALE;
    float ssaoHeight = height * RAW_SSAO_SCALE;
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    if (parm->m_iblColorMode == 3 || force) {
        m_flags |= 2;
        for (unsigned int i = 0; i < 2; i++) {
            m_ssaoBuff[i]->setTextureInfo(ssaoWidth, ssaoHeight, DrPixlFormat::s_SSAOWorkFormat, true,
                                          DrPixlMemMan::get()->getSSAOOfs(i));
            m_historyBuff[i]->setTextureInfo(width * HISTORY_SCALE, height * HISTORY_SCALE, DrPixlFormat::s_SSAOWorkFormat, true,
                                             DrPixlMemMan::get()->getSSAOOfs(2 + i));
        }
    } else {
        m_ssaoBuff[DrMan::s_nDblIdx]->setTextureInfo(ssaoWidth, ssaoHeight, DrPixlFormat::s_SSAOWorkFormat,
                                                     true, DrPixlMemMan::get()->getSSAOOfs(DrMan::s_nDblIdx));
        m_historyBuff[DrMan::s_nDblIdx]->setTextureInfo(width * HISTORY_SCALE, height * HISTORY_SCALE, DrPixlFormat::s_SSAOWorkFormat,
                                                        true, DrPixlMemMan::get()->getSSAOOfs(DrMan::s_nDblIdx + 2));
        if (parm->m_iblColorMode == 2) {
            return;
        }
    }
    float midWidth = width * UPSCALE_MIDDLE;
    float midHeight = height * UPSCALE_MIDDLE;
    m_workBuff->setTextureInfo(width * BLUR_SCALE_LOW, height * BLUR_SCALE_LOW, DrPixlFormat::s_SSAOWorkFormat, true,
                               DrPixlMemMan::get()->getSSAOOfs(4));
    m_blurBuffA->setTextureInfo(width * BLUR_SCALE_LOW, height * BLUR_SCALE_LOW, DrPixlFormat::s_SSAOWorkFormat, true,
                                DrPixlMemMan::get()->getSSAOOfs(5));
    m_blurBuffB->setTextureInfo(width * BLUR_SCALE_LOW, height * BLUR_SCALE_LOW, DrPixlFormat::s_SSAOWorkFormat, true,
                                DrPixlMemMan::get()->getSSAOOfs(6));
    m_outBuff->setTextureInfo(midWidth, midHeight, DrPixlFormat::s_SSAOOutFormat, true,
                              DrPixlMemMan::get()->getSSAOOfs(7));
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

void DrPixlPostObjTSSAO::passBlur_Sub(BlurAxis axis, float blur, DrPixlRenderTarget* src, DrPixlRenderTarget* dst,
                                      bool depthTest) {
    grlib::CGLibColorCtl::setBlendOffControl(static_cast<GrlLogicType>(3));
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrShdDataObj* obj = list->getPostShdObj(0x2D);
    unsigned int branchLess = depthTest ? 1 : 2;
    obj->setDeclarationIdx(obj->getDeclarationOfs("BRANCH_LESS"), branchLess);
    obj->setDeclarationIdx(obj->getDeclarationOfs("TAP_AXIS"), axis);
    list->bindQuadsTex();
    obj->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    unsigned int paramOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gParam");
    unsigned int gbuvOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gCoordToGBUV");
    unsigned int uvOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gCoordToUV");
    unsigned int sourceLocation = obj->getCurrentShader().getTextureLocation("gTSource");
    unsigned int depthLocation = obj->getCurrentShader().getTextureLocation("gTDepth");
    unsigned int similarityLocation = obj->getCurrentShader().getTextureLocation("gTSimilarity");
    unsigned int prevSimilarityLocation = obj->getCurrentShader().getTextureLocation("gTPrevSimilarity");
    grlib::CGLibRenderTarget* depth = m_postMan->getDownDepth();
    mm::Vec4 param;
    param.x = blur;
    param.y = m_frame;
    param.z = mtRand(0, dst->m_width);
    param.w = mtRand(0, dst->m_height);
    uniform.setF32SetVec4(paramOfs, &param.x);
    mm::Vec4 gbuv;
    gbuv.x = 1.0f / dst->m_width;
    gbuv.y = 1.0f / dst->m_height;
    gbuv.z = 0.5f / dst->m_width;
    gbuv.w = 0.5f / dst->m_height;
    uniform.setF32SetVec4(gbuvOfs, &gbuv.x);
    mm::Vec4 uv;
    uv.x = 1.0f / dst->m_width;
    uv.y = 1.0f / dst->m_height;
    uv.z = -0.5f / depth->m_width;
    uv.w = -0.5f / depth->m_height;
    uniform.setF32SetVec4(uvOfs, &uv.x);
    DrAPCache* cache = m_drMan->m_apCache;
    cache->beginTexSampling(2, 1);
    cache->setTexture(*src->m_pTexture, sourceLocation);
    cache->setTexture(*depth->m_pTexture, depthLocation);
    cache->beginBorderWhite();
    cache->setTexture(*m_blurBuffB->m_pTexture, similarityLocation);
    cache->setTexture(*m_historyBuff[DrMan::s_nDblStockIdx]->m_pTexture, prevSimilarityLocation);
    if (depthTest) {
        dst->setRenderTarget(*m_pixlMan->m_objTbl->m_quaterDepth->m_pDepthBuffer);
        grlib::CGLibDepthCtl::setDepthControl(1, 0, static_cast<GrlCompare>(3));
    } else {
        dst->setRenderTarget();
    }
    uniform.updateData();
    uniform.setUniformBlock();
    list->renderQuads();
    dst->setColorInvalidate();
}

void DrPixlPostObjTSSAO::passUpScaleToMiddle() {
    DrPixlRenderTarget* dst = m_outBuff;
    grlib::CGLibColorCtl::setBlendOffControl(static_cast<GrlLogicType>(3));
    m_postMan->getDownDepth();
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrShdDataObj* obj = list->getPostShdObj(0x4A);
    list->bindQuadsTex();
    obj->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    unsigned int sampleOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gSampleOffset");
    unsigned int paramOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gParam");
    unsigned int fragOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gFragCoordToGBUV");
    unsigned int taoLocation = obj->getCurrentShader().getTextureLocation("gTAO");
    unsigned int depthLocation = obj->getCurrentShader().getTextureLocation("gTDepth");
    unsigned int halfDepthLocation = obj->getCurrentShader().getTextureLocation("gTHalfDepth");
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    DrPixlRenderTarget* src = m_ssaoBuff[DrMan::s_nDblIdx];
    mm::Vec4 sampleOffset;
    sampleOffset.x = 1.5f / dst->m_width;
    sampleOffset.y = 1.5f / dst->m_height;
    sampleOffset.z = 0.0f;
    sampleOffset.w = 0.0f;
    uniform.setF32SetVec4(sampleOfs, &sampleOffset.x);
    mm::Vec4 param;
    param.x = parm->pad_17C;
    param.y = (float)src->m_width / (float)dst->m_width;
    param.z = mm::clamp(1.0f - parm->pad_190, 0.0f, 1.0f);
    param.w = parm->pad_184;
    uniform.setF32SetVec4(paramOfs, &param.x);
    mm::Vec4 frag;
    frag.x = 1.0f / src->m_width;
    frag.y = 1.0f / src->m_height;
    frag.z = (0.5f - m_frame) / src->m_width;
    frag.w = (0.5f - m_frame) / src->m_height;
    uniform.setF32SetVec4(fragOfs, &frag.x);
    DrAPCache* cache = m_drMan->m_apCache;
    cache->beginBorderDepthMax();
    cache->setTexture(*m_postMan->getDownDepth()->m_pTexture, depthLocation);
    cache->setTexture(*m_postMan->getOldDownDepth()->m_pTexture, halfDepthLocation);
    cache->beginTexSampling(2, 1);
    cache->setTexture(*src->m_pTexture, taoLocation);
    uniform.updateData();
    uniform.setUniformBlock();
    dst->setRenderTarget();
    list->renderQuads();
    dst->setColorInvalidate();
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

void DrPixlPostObjUnbranchToDepth::renderFull() {
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrShdDataObj* obj = list->getPostShdObj(0x3E);
    obj->setupShader(0u);
    m_drMan->m_pixlMan->m_objTbl->m_lightDepth->setRenderTarget();
    DrAPCache* cache = m_drMan->m_apCache;
    grlib::CGLibRenderTarget* etc = m_drMan->m_pixlMan->getPixlObj(1);
    grlib::CGLibRenderTarget* col = m_drMan->m_pixlMan->getPixlObj(0);
    unsigned int etcLocation = obj->getCurrentShader().getTextureLocation("gTEtc");
    unsigned int stencilLocation = obj->getCurrentShader().getTextureLocation("gTStencil");
    unsigned int colLocation = obj->getCurrentShader().getTextureLocation("gTCol");
    cache->setTexture(*etc->m_pTexture, etcLocation);
    cache->setTexture(*col->m_pTexture, colLocation);
    cache->setTexture(*m_drMan->m_pixlMan->getDepthObj()->m_pTexture, stencilLocation);
    DrAPGxType::setupDepthContl(1, 1, 7);
    list->bindTriangle();
    grlib::CGLibColorCtl::setColorBufferOff();
    list->renderTriangle();
    grlib::CGLibColorCtl::setColorBufferOn();
}

void DrPixlPostObjUnbranchToDepth::renderQuater() {
    DrShdDataList* list = m_drMan->m_shdMan->m_dataList;
    DrShdDataObj* obj = list->getPostShdObj(0x45);
    obj->setupShader(0u);
    m_drMan->m_pixlMan->m_objTbl->m_quaterDepth->setRenderTarget();
    DrAPCache* cache = m_drMan->m_apCache;
    grlib::CGLibRenderTarget* etc = m_drMan->m_pixlMan->getPixlObj(1);
    grlib::CGLibRenderTarget* col = m_drMan->m_pixlMan->getPixlObj(0);
    unsigned int etcLocation = obj->getCurrentShader().getTextureLocation("gTEtc");
    unsigned int stencilLocation = obj->getCurrentShader().getTextureLocation("gTStencil");
    unsigned int colLocation = obj->getCurrentShader().getTextureLocation("gTCol");
    unsigned int downDepthLocation = obj->getCurrentShader().getTextureLocation("gTDownDepth");
    cache->beginTexSampling(2, 0);
    cache->setTexture(*etc->m_pTexture, etcLocation);
    cache->setTexture(*col->m_pTexture, colLocation);
    cache->setTexture(*m_drMan->m_pixlMan->getDepthObj()->m_pTexture, stencilLocation);
    cache->setTexture(*m_drMan->m_pixlMan->m_objTbl->m_postMan->getDownDepth()->m_pTexture, downDepthLocation);
    grlib::CGLibUniformEtcUtility uniform(obj);
    uniform.setUseUniformBlock("U_POST");
    unsigned int sclOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gScal");
    unsigned int paramOfs = uniform.m_pDecShader->getCurrentShader().getUniformBlockValOfs(uniform.m_location, "gParam");
    DrPixlPostParm* parm = m_drMan->m_postParm[m_drMan->m_postParmIdx];
    mm::Vec4 v(1.0f, 1.0f, 0.0f, 0.0f);
    uniform.setVec4SetVec4(sclOfs, v);
    v.x = parm->m_unbranchQuaterParam;
    v.y = v.z = v.w = 0.0f;
    uniform.setVec4SetVec4(paramOfs, v);
    uniform.updateData();
    uniform.setUniformBlock();
    DrAPGxType::setupDepthContl(1, 1, 7);
    list->bindTriangleTex();
    grlib::CGLibColorCtl::setColorBufferOff();
    list->renderTriangle();
    grlib::CGLibColorCtl::setColorBufferOn();
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

void ScnObjModelDrSys::apply() {
    getTrans(false)->update();
    if (isDisp()) {
        if (m_pMdlObj != nullptr) {
            m_pMdlObj->setDisp(true);
            DrMdlObj* mdl = m_pMdlObj;
            if (isClip()) {
                mdl->m_dispFlags |= 0x2;
            } else {
                mdl->m_dispFlags &= ~0x2;
            }
            float& speed = m_pMdlObj->m_speed;
            speed = m_unkFlag6 ? m_frameSpd : 0.0f;
        }
    } else if (m_pMdlObj != nullptr) {
        m_pMdlObj->setDisp(false);
    }
}

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
