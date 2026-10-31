#include "classes/grlib/CGLibShdListBase.h"
#include "ml/DrShdUniformBlockMan.h"
#include "grlib/CGLibDecShader.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/FileResTh.h"
#include "classes/ml/Scn.h"
#include "ml/DrShdLgtGlobalIBL.h"
#include "ml/DrShdLgtMan.h"
#include "ml/DrShdLgtObj.h"
#include "ml/DrShdMan.h"
#include "ml/DrShdFetchMan.h"
#include "ml/DrShdMdoMan.h"
#include "ml/DrShdDataList.h"
#include "ml/DrShdMdoDecExtTbl.h"
#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrCalcClipWorkCone.h"
#include "classes/ml/DrCalcClipWorkPlane.h"
#include "classes/ml/DrCalcClipWorkShadowPlane.h"
#include "classes/ml/DrLightObjLocalIBL.h"
#include "classes/ml/DrLightObjPnt.h"
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
#include "classes/grlib/CGLibShdListBase.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "grlib/CGLibTriUniformBlock.h"
#include "ml/CriticalSection.h"
#include "ml/WorkUtil.h"
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
#include "ml/DrResShdMpf.h"
#include "ml/DrResShdPrePass.h"
#include "ml/DrResShdShw.h"
#include "ml/DrResShdStreamOut.h"
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

void DrShdLgtTileBasedDr::createWork() {
    for (int i = 0; i < 4; i++) {
        int lightNum = i == 0 ? 0x100 : 0x10;
        int pntSize = lightNum * 0x30;
        int sptSize = lightNum * 0x40;
        ViewWork& view = m_viewWork[i];
        view.pntLight.setup(pntSize);
        view.sptLight.setup(sptSize);
        view.param.setup(0x280);
        view.blocks.setupArray(27);
        view.blocks.allocMem(0x3600);
        view.blocks.m_ofs = 0;
        for (int j = 0; j < 27; j++) {
            view.blocks.m_ofs += view.blocks.m_pArray[j].setupArray(0x10, view.blocks.m_mem, view.blocks.m_ofs);
        }
    }
    addViewInfo(0);
}

DrShdLgtTileBasedDr::~DrShdLgtTileBasedDr() {
    if (m_pWork) {
        mtl::MemManager::deallocate(m_pWork, 0, false);
        m_pWork = nullptr;
    }
}

void DrShdLgtTileBasedDr::stockBegin() {
    ViewWork& view = m_viewWork[m_cateIdx];
    view.pntNum = 0;
    view.sptNum = 0;
    m_pntBuffRest = view.pntLight.m_size;
    m_sptBuffRest = view.sptLight.m_size;
    m_pPntBuff = reinterpret_cast<PntLightEntry*>(view.pntLight.getBuff());
    m_pSptBuff = reinterpret_cast<float*>(view.sptLight.getBuff());
}

void DrShdLgtTileBasedDr::update() {}

void DrShdLgtTileBasedDr::addViewInfo(int) {}

void DrShdLgtTileBasedDr::delViewInfo(int) {}

void DrShdLgtTileBasedDr::stockPntList(DrLightObjPnt* light) {
    ViewWork& view = m_viewWork[m_cateIdx];
    int lightMax = m_cateIdx == 0 ? 0x100 : 0x10;
    if (lightMax != view.pntNum) {
        const mm::Mat44& mtx = m_pDrMan->m_calcMan->m_pViewWork->m_view;
        m_pntBuffRest -= sizeof(PntLightEntry);
        PntLightEntry* entry = m_pPntBuff++;
        const float* pos = light->m_pos;
        float px = mtx.m[3][0] + (pos[0] * mtx.m[0][0] + pos[1] * mtx.m[1][0] + pos[2] * mtx.m[2][0]);
        float py = mtx.m[3][1] + (pos[0] * mtx.m[0][1] + pos[1] * mtx.m[1][1] + pos[2] * mtx.m[2][1]);
        float pz = (pos[0] * mtx.m[0][2] + pos[1] * mtx.m[1][2] + pos[2] * mtx.m[2][2]) + mtx.m[3][2];
        entry->pos[0] = px;
        entry->pos[1] = py;
        entry->pos[2] = pz;
        entry->size = light->m_size;
        entry->color[0] = light->m_color[0];
        entry->color[1] = light->m_color[1];
        entry->color[2] = light->m_color[2];
        entry->param2 = light->m_lightParam2;
        entry->invSize = 1.0f / light->m_size;
        entry->zero = 0.0f;
        entry->rate = (light->m_bLightFlag << 31) | (static_cast<int>(light->m_lightRate * 255.0f) & 0x7FFFFFFF);
        entry->param = light->m_lightParam;
        view.pntNum++;
    }
}

void DrShdLgtTileBasedDr::debugRender() {}


void DrShdLgtObj::shaderSetup(DrResFetch* fetch) { grlib::CGLibCtlShader::setShader(*this, *fetch); }

void DrShdLgtMan::renderBegin() {
    m_renderIdx[0] = 0xFFFF;
    m_renderIdx[1] = 0xFFFF;
    m_lgtBuffReq = -1;
    m_renderFlag = 1;
}

DrShdLgtHybrid* DrShdLgtMan::getHybridLight() { return m_pHybrid; }

DrShdLgtObj* DrShdLgtMan::getGlobalIBLShader(GIBL_SHADER_TYPE type) { return &m_pExtShader[1][type]; }

void DrShdLgtMan::setupGlobalIBLShader(DrShdLgtObj* shader) { shader->shaderSetup(&m_fetch); }

DrShdMan::DrShdMan(DrMan* drMan) : m_dataList(nullptr), m_mdoMan(nullptr), m_fetchMan(nullptr), m_lgtMan(nullptr), m_pDrMan(drMan) {
    m_dataList = new (drMan->m_workHandle, nullptr, 0, 4, false) DrShdDataList(m_pDrMan);
    m_mdoMan = new (drMan->m_workHandle, nullptr, 0, 4, false) DrShdMdoMan;
    m_fetchMan = new (drMan->m_workHandle, nullptr, 0, 4, false) DrShdFetchMan(m_pDrMan);
    m_lgtMan = new (drMan->m_workHandle, nullptr, 0, 4, false) DrShdLgtMan(m_pDrMan);
}

DrShdMan::~DrShdMan() {
    if (m_dataList != nullptr) {
        delete m_dataList;
        m_dataList = nullptr;
    }
    if (m_mdoMan != nullptr) {
        delete m_mdoMan;
        m_mdoMan = nullptr;
    }
    if (m_fetchMan != nullptr) {
        delete m_fetchMan;
        m_fetchMan = nullptr;
    }
    if (m_lgtMan != nullptr) {
        delete m_lgtMan;
        m_lgtMan = nullptr;
    }
}

void DrShdMan::beginUpdate() { m_mdoMan->update(); }

void DrShdMan::setupCate(int cateIdx) {
    DrShdLgtMan* lgtMan = m_lgtMan;
    lgtMan->m_pHybrid->setupCate(cateIdx);
    lgtMan->m_pClustered->setupCate(cateIdx);
}

void DrShdMan::beforeUpdateCate(int cateIdx) { m_lgtMan->m_pGlobalIBL->update(cateIdx); }

void DrShdMan::updateCate(int) {
    DrShdLgtMan* lgtMan = m_lgtMan;
    lgtMan->m_pHybrid->update();
    lgtMan->m_pClustered->update();
}

void DrShdMan::addViewInfo(int viewIdx) {
    DrShdLgtMan* lgtMan = m_lgtMan;
    lgtMan->m_pHybrid->addViewInfo(viewIdx);
    lgtMan->m_pClustered->addViewInfo(viewIdx);
}

void DrShdMan::delViewInfo(int viewIdx) {
    DrShdLgtMan* lgtMan = m_lgtMan;
    lgtMan->m_pHybrid->delViewInfo(viewIdx);
    lgtMan->m_pClustered->delViewInfo(viewIdx);
    lgtMan->m_pGlobalIBL->delViewInfo(viewIdx);
}

void DrShdMan::resetColorBuff(int viewIdx) {
    if (m_lgtMan != nullptr && m_lgtMan->m_pGlobalIBL != nullptr) {
        m_lgtMan->m_pGlobalIBL->resetColorBuff(viewIdx);
    }
}

unsigned int DrShdMdoDecExtTbl::getValGlobalParam(int idx) { return m_pValGlobalParam[idx]; }

void DrShdMdoDecExtTbl::bindShader() { DrAPCache::s_pIns->setupShader(this, &m_pRes->m_pFetchObj->m_fetch); }

void DrShdUniformBlockMan::createUniformBoneObj(grlib::CGLibTriUniformBlock* block, int num) {
    new (block) grlib::CGLibTriUniformBlock;
    block->setup(num * 0x30);
}

DrResShdMpf* DrShdDataList::getMpfObj(int i) { return &m_pMpfObj[i]; }

DrResShdPrePass* DrShdDataList::getPrePassObj(int i) { return &m_pPrePassObj[i]; }

DrResShdShw* DrShdDataList::getShwObj(int i) { return &m_pShwObj[i]; }

DrResShdStreamOut* DrShdDataList::getStmOutObj(int i) { return &m_pStmOutObj[i]; }

grlib::CGLibOneUniformBlock* DrShdDataList::getAlphaTestUniform(float alpha) {
    unsigned int idx = static_cast<int>(alpha * 10.0f);
    if (idx > 10) {
        idx = 10;
    }
    return &m_alphaTestBlock.m_pArray[idx];
}

}  // namespace ml
