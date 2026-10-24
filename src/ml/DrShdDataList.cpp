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

void DrShdDataList::reloadShader(int) { createShader(); }

DrShdDataObj* DrShdDataList::getDebugShdObj(int i) { return &m_pDebugShdObj[i]; }

DrShdDataObj* DrShdDataList::getSelectShdObj(int i) { return &m_pSelectShdObj[i]; }

DrShdDataObj* DrShdDataList::getShadowShdObj(int i) { return &m_pShadowShdObj[i]; }

DrShdDataObj* DrShdDataList::getPostShdObj(int i) { return &m_pPostShdObj[i]; }

DrShdDataObj* DrShdDataList::getComputeObj(int i) { return &m_pComputeObj[i]; }

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

DrResFetch* DrShdDataList::getFetchShader(int i) { return &m_fetchShader[i]; }

void DrShdDataObj::setupShader(unsigned int fetch) { grlib::CGLibCtlShader::setShader(*this, *m_pFetch[fetch]); }

void DrShdDataObj::setupShader(DrResFetch* fetch) { grlib::CGLibCtlShader::setShader(*this, *fetch); }

void DrShdDataObj::setupComputeShader() { grlib::CGLibCtlShader::setComputeShader(*this); }

void DrShdLgtMan::stockBegin() {
    m_pHybrid->stockBegin();
    m_pClustered->stockBegin();
}

void DrShdLgtMan::stockEnd() {
    m_pHybrid->stockEnd();
    m_pClustered->stockEnd();
}

void DrShdLgtTileBasedDr::update() {}

void DrShdLgtTileBasedDr::addViewInfo(int) {}

void DrShdLgtTileBasedDr::delViewInfo(int) {}

void DrShdLgtTileBasedDr::debugRender() {}

}  // namespace ml
