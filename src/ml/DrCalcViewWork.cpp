#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrCalcClipWorkCone.h"
#include "classes/ml/DrCalcClipWorkPlane.h"
#include "classes/ml/DrCalcClipWorkShadowPlane.h"
#include "classes/ml/DrLightObjLocalIBL.h"
#include "classes/ml/DrShdLgtClustered.h"
#include "classes/ml/DrShdLgtHybrid.h"
#include "classes/ml/DrShdLgtTileBasedDr.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/ScnObjLightDrSys.h"
#include "classes/ml/ScnObjModelDrSys.h"
#include "classes/navi/NvmshAcObj.h"
#include "classes/navi/NvmshManager.h"
#include "classes/navi/NvmshResMan.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibUniBaseUtility.h"
#include "grlib/CGLibVtxIndex.h"
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
#include "ml/DrPixlPostObjExpStencil.h"
#include "ml/DrPixlPostObjUnbranchToDepth.h"
#include "ml/DrResMdoUniformBlock.h"
#include "ml/DrShdCubeCapFilter.h"
#include "ml/DrShdDataList.h"
#include "ml/DrShdDataObj.h"
#include "ml/DrShdLgtMan.h"
#include "navi/NvmshAcMan.h"

namespace ml {

void DrShdLgtTileBasedDr::update() {}

void DrShdLgtTileBasedDr::addViewInfo(int) {}

void DrShdLgtTileBasedDr::delViewInfo(int) {}

void DrShdLgtTileBasedDr::debugRender() {}

void ScnObjIBLDr::setReferencePos(const mm::Vec3&) {}

void ScnObjIBLDr::dispDebugWindow(bool, const char*, ml::WinProc*) {}

void ScnObjIBLDr::setName(const char*) {}

void ScnObjLightDrSys::tail() {}

void ScnObjLightDrSys::setLocalIBLName(const char*) {}

void DrCalcClipWorkCone::debugDraw() {}

DrLightObjLocalIBL::~DrLightObjLocalIBL() {}

void ScnObjModelDrSys::update() {}

void DrShdDataList::reloadShader(int) { createShader(); }

void DrShdDataList::bindShdVertex() { grlib::CGLibCtlVertex::setVertex(m_shdVertex); }

void DrShdDataList::bindQuadsTex() { grlib::CGLibCtlVertex::setVertex(m_quadsTex); }

void DrShdDataList::bindTriangle() { grlib::CGLibCtlVertex::setVertex(m_triangle); }

void DrShdDataList::bindTriangleTex() { grlib::CGLibCtlVertex::setVertex(m_triangleTex); }

void DrShdDataList::bindShdBoxVertex() { grlib::CGLibCtlVertex::setVertex(m_shdBoxVertex); }

void DrShdDataList::bindShdRainDropVertex() { grlib::CGLibCtlVertex::setVertex(m_shdRainDropVertex); }

void DrShdDataList::bindShdEffVtx() { grlib::CGLibCtlVertex::setVertex(m_shdEffVtx); }

void DrShdDataList::bindShdDepthCheck() { grlib::CGLibCtlVertex::setVertex(m_shdDepthCheck); }

void DrShdDataList::renderQuads() { m_quadsIndex.drawIndex(); }

void DrShdDataList::renderTriangle() { m_triangleIndex.drawIndex(); }

void DrShdDataList::renderBox() { m_boxIndex.drawIndex(); }

void DrShdDataList::renderRainDrop() { m_rainDropIndex.drawIndex(); }

void DrShdDataList::renderEffVtx(int instances) { m_effVtxIndex.drawInsIndex(instances); }

// GrlPrimitiveType 0 (no enumerator has a name yet): the drawing of points
void DrShdDataList::renderPoint(int count) { grlib::CGLibCtlVertex::renderVertex(GrlPrimitiveType(0), count); }

void DrShdDataList::renderPoint(int count, int instances) {
    grlib::CGLibCtlVertex::renderInstanceVertex(GrlPrimitiveType(0), count, instances);
}

void DrAPCache::endZRender() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::endThicknessRenderFirst() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::endThicknessRenderSecond() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::endMdlZRender() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::endGBuffRender() { grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 1); }

void DrAPCache::setRefractionRender() { grlib::CGLibColorCtl::setColorChannelMask(0, 0, 0, 0); }

void DrAPCache::endRefractionRender() { grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 1); }

void DrAPCache::setTexture(const grlib::CGLibTextureBuffer& texture, const grlib::CGLibSampler& sampler,
                           unsigned int location) {
    grlib::CGLibCtlTexture::setTexture(texture, sampler, location);
}

void DrAPGxType::endOccQuery() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPGxType::beginShadow() { grlib::CGLibColorCtl::setColorBufferOff(); }

void DrAPGxType::endShadow() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPGxType::beginColorOff() { grlib::CGLibColorCtl::setColorBufferOff(); }

void DrAPGxType::endColorOff() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPGxType::setupCullingOff() { grlib::CGLibPolygon::setCullingOff(); }

void DrAPGxType::setupCullingFront() { grlib::CGLibPolygon::setCullingFront(); }

void DrAPGxType::setupCullingBack() { grlib::CGLibPolygon::setCullingBack(); }

int DrCalcViewWork::unistatic_view(float* pDst, bool) {
    grlib::ShdMat44TransposeMat34(pDst, m_view);
    return DrResMdoUniformBlock::s_nVarSizeTbl[2];
}

int DrCalcViewWork::unistatic_proj(float* pDst, bool bJitter) {
    grlib::ShdMat44TransposeMat44(pDst, bJitter ? m_proj : m_projNonJitter);
    return DrResMdoUniformBlock::s_nVarSizeTbl[3];
}

int DrCalcViewWork::unistatic_viewproj(float* pDst, bool bJitter) {
    grlib::ShdMat44TransposeMat44(pDst, bJitter ? m_viewProj : m_viewProjNonJitter);
    return DrResMdoUniformBlock::s_nVarSizeTbl[4];
}

int DrCalcViewWork::unistatic_invview(float* pDst, bool) {
    grlib::ShdMat44TransposeMat34(pDst, m_invView);
    return DrResMdoUniformBlock::s_nVarSizeTbl[6];
}

int DrCalcViewWork::unistatic_billborad_Def(float* pDst, bool) {
    grlib::ShdMat44TransposeMat34(pDst, m_billboard);
    return DrResMdoUniformBlock::s_nVarSizeTbl[45];
}

int DrCalcViewWork::unistatic_billborad_YVec(float* pDst, bool) {
    grlib::ShdMat44TransposeMat34(pDst, m_billboardYVec);
    return DrResMdoUniformBlock::s_nVarSizeTbl[46];
}

int DrCalcViewWork::unistatic_viewYvec(float* pDst, bool) {
    pDst[0] = m_viewYVec.x;
    pDst[1] = m_viewYVec.y;
    pDst[2] = m_viewYVec.z;
    return DrResMdoUniformBlock::s_nVarSizeTbl[8];
}

int DrCalcViewWork::unistatic_jitter(float* pDst, bool) {
    pDst[0] = m_jitter[0];
    pDst[1] = m_jitter[1];
    pDst[2] = m_oldJitter[0];
    pDst[3] = m_oldJitter[1];
    return DrResMdoUniformBlock::s_nVarSizeTbl[73];
}

int DrCalcViewWork::unistatic_dither_tmaa_val(float* pDst, bool) {
    grlib::ShdF32SetVec4(pDst, m_ditherTmaaVal);
    return DrResMdoUniformBlock::s_nVarSizeTbl[93];
}

int DrCalcViewWork::unistatic_proj_non_jitter(float* pDst, bool) {
    grlib::ShdMat44TransposeMat44(pDst, m_projNonJitter);
    return DrResMdoUniformBlock::s_nVarSizeTbl[115];
}

int DrCalcViewWork::unistatic_diff_pre_orijmat(float* pDst, bool) {
    grlib::ShdMat44TransposeMat44(pDst, m_diffPreOrijMat);
    return DrResMdoUniformBlock::s_nVarSizeTbl[120];
}

int DrCalcViewWork::unistatic_lightNotUse(float* pDst) {
    pDst[0] = 0.0f;
    pDst[1] = 0.0f;
    pDst[2] = 0.0f;
    pDst[3] = 0.0f;
    return DrResMdoUniformBlock::s_nVarSizeTbl[77];
}

int DrCalcViewWork::unistatic_mpf_ViewProj(float* pDst) {
    grlib::ShdMat44TransposeMat44(pDst, m_viewProj);
    return 16;
}

int DrCalcViewWork::unistatic_mpf_OldViewProj(float* pDst) {
    grlib::ShdMat44TransposeMat44(pDst, m_oldViewProj);
    return 16;
}

int DrCalcViewWork::unistatic_mpf_View(float* pDst) {
    grlib::ShdMat44TransposeMat34(pDst, m_view);
    return 12;
}

int DrCalcViewWork::unistatic_mpf_BiiMat(float* pDst) {
    grlib::ShdMat44TransposeMat34(pDst, m_billboard);
    return 12;
}

int DrCalcViewWork::unistatic_mpf_OldBiiMat(float* pDst) {
    grlib::ShdMat44TransposeMat34(pDst, m_oldBillboard);
    return 12;
}

int DrCalcViewWork::unistatic_mpf_DepthParm(float* pDst) {
    pDst[0] = m_depthParm.x;
    pDst[1] = m_depthParm.y;
    pDst[2] = m_depthParm.z;
    pDst[3] = 0.0f;
    return 4;
}

int DrCalcViewWork::unistatic_mpf_ViewYVec(float* pDst) {
    pDst[0] = m_viewYVec.x;
    pDst[1] = m_viewYVec.y;
    pDst[2] = m_viewYVec.z;
    pDst[3] = 0.0f;
    return 4;
}

int DrCalcViewWork::unistatic_mpf_ViewPos(float* pDst) {
    pDst[0] = m_viewPos.x;
    pDst[1] = m_viewPos.y;
    pDst[2] = m_viewPos.z;
    pDst[3] = 1.0f;
    return 4;
}

int DrCalcViewWork::unistatic_mpf_OldViewPos(float* pDst) {
    pDst[0] = m_oldViewPos.x;
    pDst[1] = m_oldViewPos.y;
    pDst[2] = m_oldViewPos.z;
    pDst[3] = 1.0f;
    return 4;
}

int DrCalcViewWork::unistatic_mpf_Fade(float* pDst) {
    grlib::ShdF32SetF32Array(pDst, m_fade, 12);
    return 0x30;
}

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

void ScnObjModelDrSys::setGroups(int groups) { m_pMdlObj->setGroups(groups); }

int ScnObjModelDrSys::getGroups() { return m_pMdlObj->getGroups(); }

}  // namespace ml

namespace navi {

void NvmshManager::setupResource(const void* resource, const char* name) {
    m_pResMan->setupResource(static_cast<const unsigned char*>(resource), name);
}

void NvmshManager::releaseResource() { m_pResMan->releaseResource(); }

NvmshAcObj* NvmshManager::createObj() {
    static ml::CriticalSection s_cs;  // the name is not the original's
    ml::CS lock(s_cs);
    return static_cast<NvmshAcObj*>(m_pAcMan->createObj(m_hAlloc, m_pResMan));
}

void NvmshManager::releaseObj(NvmshAcObj* object) { m_pAcMan->releaseObj(object); }

}  // namespace navi

namespace ml {

}  // namespace ml

namespace idcoli {

bool IDColiUtilColiResult::isSpherePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiResult::isCapsulePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiResult::isLineSphere(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineSphere(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false);
}

bool IDColiUtilColiResult::isLineBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineBox(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false, false);
}

bool IDColiUtilColiResult::isLineInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineBox(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false, true);
}

bool IDColiUtilColiResult::isLineCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineCapsule(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false, false);
}

bool IDColiUtilColiResult::isLineInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineCapsule(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false, true);
}

bool IDColiUtilColiResult::isLinePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiResult::isRayPoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isSphereBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isSphereBox(result, static_cast<const CLSphereWork*>(input.getShape()), static_cast<const CLBoxWork*>(pOther));
}

bool IDColiUtilColiSimple::isSpherePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isCapsuleBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isCapsuleBox(result, static_cast<const CLCapsuleWork*>(input.getShape()), static_cast<const CLBoxWork*>(pOther));
}

bool IDColiUtilColiSimple::isCapsuleInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isCapsuleInBox(result, static_cast<const CLCapsuleWork*>(input.getShape()), static_cast<const CLBoxWork*>(pOther));
}

bool IDColiUtilColiSimple::isCapsulePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isBoxSphere(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isSphereBox(result, static_cast<const CLSphereWork*>(pOther), static_cast<const CLBoxWork*>(input.getShape()));
}

bool IDColiUtilColiSimple::isBoxBox(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isBoxCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isCapsuleBox(result, static_cast<const CLCapsuleWork*>(pOther), static_cast<const CLBoxWork*>(input.getShape()));
}

bool IDColiUtilColiSimple::isBoxPoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isLineBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineBox(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false);
}

bool IDColiUtilColiSimple::isLineCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineCapsule(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false);
}

bool IDColiUtilColiSimple::isLinePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isLineInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineBox(result, static_cast<const CLLineWork*>(input.getShape()), pOther, true);
}

bool IDColiUtilColiSimple::isLineInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineCapsule(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false);
}

bool IDColiUtilColiSimple::isRayPoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

}  // namespace idcoli

namespace ml {

DrCalcClipWorkCone::~DrCalcClipWorkCone() {}

DrCalcClipWorkPlane::~DrCalcClipWorkPlane() {}

DrCalcClipWorkShadowPlane::~DrCalcClipWorkShadowPlane() {}

DrCalcGpuCost::~DrCalcGpuCost() {}

DrPixlPostObjExpStencil::~DrPixlPostObjExpStencil() {}

DrPixlPostObjUnbranchToDepth::~DrPixlPostObjUnbranchToDepth() {}

DrShdCubeCapFilter::~DrShdCubeCapFilter() {}

}  // namespace ml

namespace idcoli {

IDColiGrandObj::~IDColiGrandObj() {}

IDColiTreeTop::~IDColiTreeTop() {}

}  // namespace idcoli

namespace ml {

// DrCalcClipWork's own virtuals: the base tests nothing (its derived classes' tables share these slots)
bool DrCalcClipWork::clipLineTest(mm::Vec3 const&, mm::Vec3 const&, float) const { return false; }
bool DrCalcClipWork::clipTest(float const*, float const*) const { return false; }
bool DrCalcClipWork::clipTest(mm::Vec3 const*, int) const { return false; }
void DrCalcClipWork::debugDraw() {}
bool DrCalcClipWork::clipTest(mm::Vec3 const&, float) const { return false; }
bool DrCalcClipWork::clipTypeTest(mm::Vec3 const&, float) const { return false; }

float ScnObjLightDrSys::getFrame() const {
    if (m_pEnvObj == nullptr) {
        return 0.0f;
    }
    return m_pEnvObj->getFrame();
}

float ScnObjLightDrSys::getMaxFrame() const {
    if (m_pEnvObj == nullptr) {
        return 0.0f;
    }
    return m_pEnvObj->getMaxFrame();
}

float ScnObjLightDrSys::getFrameSpd() const {
    if (m_pEnvObj == nullptr) {
        return 0.0f;
    }
    return m_pEnvObj->getFrameSpd();
}

int ScnObjLightDrSys::getGroup() const { return m_pEnvObj->m_group; }

const mm::Vec3& ScnObjLightDrSys::getOffsetPos() const { return m_pEnvObj->m_offsetPos; }

DrPixlPostObjExpStencil::DrPixlPostObjExpStencil(DrMan* drMan) : m_pDrMan(drMan) {}

DrShdCubeCapFilter::DrShdCubeCapFilter(DrMan* drMan) : m_pDrMan(drMan) {}

DrShdDataObj* DrShdDataList::getDebugShdObj(int i) { return &m_pDebugShdObj[i]; }
DrShdDataObj* DrShdDataList::getSelectShdObj(int i) { return &m_pSelectShdObj[i]; }
DrShdDataObj* DrShdDataList::getShadowShdObj(int i) { return &m_pShadowShdObj[i]; }
DrShdDataObj* DrShdDataList::getPostShdObj(int i) { return &m_pPostShdObj[i]; }
DrShdDataObj* DrShdDataList::getComputeObj(int i) { return &m_pComputeObj[i]; }
DrResFetch* DrShdDataList::getFetchShader(int i) { return &m_fetchShader[i]; }

void DrShdDataObj::setupShader(unsigned int fetch) { grlib::CGLibCtlShader::setShader(*this, *m_pFetch[fetch]); }
void DrShdDataObj::setupShader(DrResFetch* fetch) { grlib::CGLibCtlShader::setShader(*this, *fetch); }
void DrShdDataObj::setupComputeShader() { grlib::CGLibCtlShader::setComputeShader(*this); }

void DrAPCache::beginTexSampling(int sampling, int wrap) {
    m_specialSampler = 0;
    m_specialSamplerKind = 0;
    m_texSampling[0] = sampling;
    m_texSampling[1] = sampling;
    m_texWrap = wrap;
    m_mipMap = 0;
}

void DrAPCache::begin3DTextureSampling() {
    m_specialSampler = 0x41;
    m_specialSamplerKind = 1;
}

void DrAPCache::begin3DTexturePointSampling() {
    m_specialSampler = 0x42;
    m_specialSamplerKind = 1;
}

void DrAPCache::begin3DTextureWarpSampling() {
    m_specialSampler = 0x43;
    m_specialSamplerKind = 1;
}

void DrAPCache::beginCubeTextureSampling(bool b) {
    m_specialSampler = b ? 0x47 : 0x45;
    m_specialSamplerKind = 2;
}

void DrAPCache::beginCubeTexturePointSampling(bool b) {
    m_specialSampler = b ? 0x48 : 0x46;
    m_specialSamplerKind = 2;
}

void DrAPCache::beginDepthCompare() {
    m_specialSampler = 0x49;
    m_specialSamplerKind = 0;
}

void DrAPCache::beginBorderWhite() {
    m_specialSampler = 0x4A;
    m_specialSamplerKind = 0;
}

void DrAPCache::beginBorderBlack() {
    m_specialSampler = 0x4B;
    m_specialSamplerKind = 0;
}

void DrAPCache::beginBorderDepthMax() {
    m_specialSampler = 0x4C;
    m_specialSamplerKind = 0;
}

void DrAPCache::beginBorderDepthMinusMax() {
    m_specialSampler = 0x4D;
    m_specialSamplerKind = 0;
}

void DrAPCache::setGBuffRender(unsigned int render) {
    if (m_gBuffRender == render) {
        return;
    }
    m_gBuffRender = render;
    switch (render) {
    case 0x77777777:
        grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 1);
        break;
    case 0xFFFFFFFF:
        grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 0);
        break;
    }
}

void DrShdLgtMan::stockBegin() {
    m_pHybrid->stockBegin();
    m_pClustered->stockBegin();
}

void DrShdLgtMan::stockEnd() {
    m_pHybrid->stockEnd();
    m_pClustered->stockEnd();
}

void DrShdLgtHybrid::stockBegin() {
    m_pClustered->stockBegin();
    m_pTileBasedDr->stockBegin();
}

void DrShdLgtHybrid::stockEnd() {
    m_pClustered->stockEnd();
    m_pTileBasedDr->stockEnd();
}

void DrCalcMan::begin() {
    m_pViewWork->begin(m_viewIdx);
    m_pClipMan->update();
}

void DrCalcMan::end() { m_pViewWork->end(); }

}  // namespace ml
