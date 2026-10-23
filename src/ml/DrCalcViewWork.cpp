#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrCalcClipWorkCone.h"
#include "classes/ml/DrLightObjLocalIBL.h"
#include "classes/ml/DrShdLgtTileBasedDr.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/ScnObjLightDrSys.h"
#include "classes/ml/ScnObjModelDrSys.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibUniBaseUtility.h"
#include "grlib/CGLibVtxIndex.h"
#include "ml/DrAPGxType.h"
#include "ml/DrCalcViewWork.h"
#include "ml/DrResMdoUniformBlock.h"
#include "ml/DrShdDataList.h"

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

}  // namespace ml
