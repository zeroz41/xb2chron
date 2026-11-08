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
#include "ml/MdsMatTechnique.h"
#include "ml/MdsMpfMatTopHeader.h"
#include "ml/MdsMatVertexInfo.h"
#include "ml/DrResMdoVertex.h"
#include "grlib/CGLibUniformArray.h"
#include "grlib/CGLibVtlMemPool.h"
#include "classes/ml/DrCalcStmListObj.h"
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
#include "ml/DrPixlMan.h"
#include "ml/DrResShdMpf.h"
#include "ml/DrResShdPrePass.h"
#include "ml/DrResShdShw.h"
#include "ml/DrResShdStreamOut.h"
#include "navi/NvmshAcMan.h"

namespace ml {

DrShdDataList::DrShdDataList(DrMan* drMan)
    : m_pRes(nullptr), m_pDrMan(drMan), m_pResShdWork(nullptr), m_pMpfObj(nullptr) {
    memset(m_pShdObj, 0, sizeof(m_pShdObj));
    m_pShdList = new (m_pDrMan->m_workHandle, nullptr, 0, 4, false) grlib::CGLibShdListBase<DrShdDataObj>();
    createWork();
    createShader();
}

DrShdDataList::~DrShdDataList() {
    releaseShader();
    for (int i = 0; i < 12; i++) {
        m_vertex[i].release();
    }
    for (int i = 0; i < 8; i++) {
        m_index[i].release();
    }
    m_boneStmOut.release();
    m_oldBoneStmOut.release();
    for (int i = 0; i < 0x5B; i++) {
        m_fetchShader[i].clearWork();
    }
    m_alphaTestBlock.release();
    if (m_pShdList != nullptr) {
        delete m_pShdList;
        m_pShdList = nullptr;
    }
}

void DrShdDataList::releaseShader() {
    if (m_pResShdWork != nullptr) {
        m_pShdList->release();
        if (m_pResShdWork != nullptr) {
            mtl::MemManager::deallocate(m_pResShdWork, 0, false);
            m_pResShdWork = nullptr;
        }
    }
    if (m_pRes != nullptr) {
        m_pRes->Release();
        m_pRes = nullptr;
    }
}

void DrShdDataList::reloadShader(int) { createShader(); }

void DrShdDataList::createAlphaTestBlock() {
    m_alphaTestBlock.setupArray(11);
    m_alphaTestBlock.allocMem(11 * 0x100);
    for (int i = 0; i < 11; i++) {
        m_alphaTestBlock.m_ofs +=
            m_alphaTestBlock.m_pArray[i].setupArray(0x10, m_alphaTestBlock.m_mem, m_alphaTestBlock.m_ofs);
    }
    for (int i = 1; i < 10; i++) {
        grlib::CGLibOneUniformBlock* block = &m_alphaTestBlock.m_pArray[i];
        float* buff = reinterpret_cast<float*>(block->m_pBuff);
        buff[0] = i * 0.1f;
        buff[1] = 0.0f;
        buff[2] = 0.0f;
        buff[3] = 0.0f;
        block->updateData();
    }
    grlib::CGLibOneUniformBlock* block = &m_alphaTestBlock.m_pArray[0];
    float* buff = reinterpret_cast<float*>(block->m_pBuff);
    buff[0] = 0.01f;
    buff[1] = 0.0f;
    buff[2] = 0.0f;
    buff[3] = 0.0f;
    block->updateData();
    block = &m_alphaTestBlock.m_pArray[10];
    buff = reinterpret_cast<float*>(block->m_pBuff);
    buff[0] = 0.99f;
    buff[1] = 0.0f;
    buff[2] = 0.0f;
    buff[3] = 0.0f;
    block->updateData();
}

DrShdDataObj* DrShdDataList::getDebugShdObj(int i) { return &m_pShdObj[0][i]; }

DrShdDataObj* DrShdDataList::getSelectShdObj(int i) { return &m_pShdObj[1][i]; }

DrShdDataObj* DrShdDataList::getShadowShdObj(int i) { return &m_pShdObj[2][i]; }

DrShdDataObj* DrShdDataList::getPostShdObj(int i) { return &m_pShdObj[3][i]; }

DrShdDataObj* DrShdDataList::getComputeObj(int i) { return &m_pShdObj[9][i]; }

void DrShdDataList::bindShdVertex() { grlib::CGLibCtlVertex::setVertex(m_vertex[0]); }

void DrShdDataList::bindQuadsTex() { grlib::CGLibCtlVertex::setVertex(m_vertex[1]); }

void DrShdDataList::bindTriangle() { grlib::CGLibCtlVertex::setVertex(m_vertex[2]); }

void DrShdDataList::bindTriangleTex() { grlib::CGLibCtlVertex::setVertex(m_vertex[3]); }

void DrShdDataList::bindShdBoxVertex() { grlib::CGLibCtlVertex::setVertex(m_vertex[4]); }

void DrShdDataList::bindShdRainDropVertex() { grlib::CGLibCtlVertex::setVertex(m_vertex[8]); }

void DrShdDataList::bindShdEffVtx() { grlib::CGLibCtlVertex::setVertex(m_vertex[9]); }

void DrShdDataList::bindShdDepthCheck() { grlib::CGLibCtlVertex::setVertex(m_vertex[10]); }

void DrShdDataList::renderQuads() { m_index[0].drawIndex(); }

void DrShdDataList::renderTriangle() { m_index[1].drawIndex(); }

void DrShdDataList::renderBox() { m_index[2].drawIndex(); }

void DrShdDataList::renderRainDrop() { m_index[6].drawIndex(); }

void DrShdDataList::renderEffVtx(int instances) { m_index[7].drawInsIndex(instances); }

// GrlPrimitiveType 0 (no enumerator has a name yet): the drawing of points
void DrShdDataList::renderPoint(int count) { grlib::CGLibCtlVertex::renderVertex(GrlPrimitiveType(0), count); }

void DrShdDataList::renderPoint(int count, int instances) {
    grlib::CGLibCtlVertex::renderInstanceVertex(GrlPrimitiveType(0), count, instances);
}

DrResFetch* DrShdDataList::getFetchShader(int i) { return &m_fetchShader[i]; }

void DrShdDataObj::setupShader(unsigned int fetch) { grlib::CGLibCtlShader::setShader(*this, *m_pFetch[fetch]); }

void DrShdDataObj::setupShader(DrResFetch* fetch) { grlib::CGLibCtlShader::setShader(*this, *fetch); }

void DrShdDataObj::setupComputeShader() { grlib::CGLibCtlShader::setComputeShader(*this); }

DrShdLgtMan::DrShdLgtMan(DrMan* drMan) : m_pDrMan(drMan), m_pRes(nullptr), m_pHybrid(nullptr), m_pClustered(nullptr) {
    m_pShdList = new (m_pDrMan->m_workHandle, nullptr, 0, 4, false) grlib::CGLibShdListBase<DrShdLgtObj>;
    m_fetch.setLgtVertexParam();
    releaseLightShader();
    int idx;
    reloadShader(idx);
    m_pHybrid = new (drMan->m_workHandle, nullptr, 0, 4, false) DrShdLgtHybrid(drMan);
    m_pGlobalIBL = new (drMan->m_workHandle, nullptr, 0, 4, false) DrShdLgtGlobalIBL(drMan);
    m_pClustered = new (drMan->m_workHandle, nullptr, 0, 4, false) DrShdLgtClustered(drMan, true);
}

void DrShdLgtMan::releaseLightShader() {
    m_pShdList->release();
    if (m_pRes != nullptr) {
        m_pRes->Release();
        m_pRes = nullptr;
    }
}

void DrShdLgtMan::reloadShader(int) {
    if (Scn* scn = mm::mtl::PtrSingleton<Scn>::sys()) {
        m_pRes = scn->allocEntryRes("/monolib/shader/shd_lgt.wishp");
    }
    if (m_pRes == nullptr) {
        m_pRes = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) FileResTh();
        m_pRes->loadBlock(m_pDrMan->m_fileHandle, "/monolib/shader/shd_lgt.wishp", 0x1000, 0);
    }
    if (m_pShdList->createPacShader(m_pRes->m_data, 1011, true)) {
        for (int i = 0; i < m_pShdList->m_extNum; i++) {
            m_pExtShader[i] = &m_pShdList->getExt(i);
        }
    }
}

DrShdLgtMan::~DrShdLgtMan() {
    releaseLightShader();
    m_fetch.clearWork();
    if (m_pHybrid != nullptr) {
        delete m_pHybrid;
        m_pHybrid = nullptr;
    }
    if (m_pGlobalIBL != nullptr) {
        delete m_pGlobalIBL;
        m_pGlobalIBL = nullptr;
    }
    if (m_pClustered != nullptr) {
        delete m_pClustered;
        m_pClustered = nullptr;
    }
    if (m_pShdList != nullptr) {
        delete m_pShdList;
        m_pShdList = nullptr;
    }
}

void DrShdLgtMan::setupLgtBuff() {
    if (m_lgtBuffReq != 0) {
        m_lgtBuffReq = 0;
        DrAPGxType::setupCullingOff();
        DrAPGxType::setupBlend(7);
        m_pDrMan->m_pixlMan->selectLightRenderTarget();
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
        const float* pos = &light->m_pos.x;
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

DrShdMdoDecShdObj* DrShdMdoMan::createShaderObj(const unsigned char* shdData, const unsigned char* tblData,
                                                const MdsMatTechnique* tech) {
    for (DrShdMdoDecShdObj* obj = m_pTop; obj != nullptr; obj = obj->m_pNext) {
        if (obj->m_pShdData == shdData) {
            obj->m_refCount++;
            return obj;
        }
    }
    DrShdMdoDecShdObj* obj =
        new (DrMan::getIns()->m_resHandle, nullptr, 0, 4, false) DrShdMdoDecShdObj(shdData, tblData, tech);
    if (obj != nullptr) {
        append(obj);
    }
    return obj;
}

DrShdMdoDecShdObj* DrShdMdoMan::createShaderObj(DrCalcStmListObj* stmObj, const unsigned char* tblData,
                                                const MdsMatTechnique* tech) {
    for (DrShdMdoDecShdObj* obj = m_pTop; obj != nullptr; obj = obj->m_pNext) {
        if (obj->m_pShdData == stmObj) {
            obj->m_refCount++;
            return obj;
        }
    }
    DrCalcStmListObj::ResTexObj* res = stmObj->getResShaderObj();
    DrShdMdoDecShdObj* obj =
        new (DrMan::getIns()->m_resHandle, nullptr, 0, 4, false) DrShdMdoDecShdObj(res->m_pData, tblData, tech);
    obj->m_pStmObj = stmObj;
    if (obj != nullptr) {
        append(obj);
    }
    return obj;
}

void DrShdMdoMan::releaseShaderObj(DrShdMdoDecShdObj* obj) {
    if (--obj->m_refCount < 0) {
        obj->m_refCount = 0;
    }
    if (obj->m_refCount > 0) {
        return;
    }
    DrShdMdoDecShdObj* prev = obj->m_pPrev;
    DrShdMdoDecShdObj* next = obj->m_pNext;
    if (prev == nullptr) {
        if (next == nullptr) {
            m_pTop = nullptr;
            m_pEnd = nullptr;
        } else {
            m_pTop = next;
            next->m_pPrev = nullptr;
        }
    } else if (next == nullptr) {
        m_pEnd = prev;
        prev->m_pNext = nullptr;
    } else {
        prev->m_pNext = next;
        obj->m_pNext->m_pPrev = obj->m_pPrev;
    }
    obj->m_pPrev = nullptr;
    obj->m_pNext = nullptr;
    delete obj;
}

void DrShdMdoDecShdObj::update() {
    if (m_pStmObj != nullptr) {
        DrCalcStmListObj::ResTexObj* res = m_pStmObj->getResShaderObj();
        if (res->m_flags & 1) {
            changeMemShader(res->m_pData, nullptr, nullptr);
        }
    }
}

DrShdMdoDecShdObj::DrShdMdoDecShdObj(const unsigned char* shdData, const unsigned char* tblData, const MdsMatTechnique* tech)
    : m_pPrev(nullptr), m_pNext(nullptr), m_pShdData(shdData), m_refCount(1), m_pStmObj(nullptr) {
    m_shdList.createPacShader(shdData, 0, true);
    DrShdFetchMan* fetchMan = DrMan::getIns()->m_shdMan->m_fetchMan;
    for (int i = 0; i < m_shdList.m_num; i++) {
        m_shdList.get(i).setVertexParam(fetchMan, tech[i].m_vtxInfoNum,
                                            reinterpret_cast<const MdsMatVertexInfo*>(tblData + tech[i].m_vtxInfoOfs));
    }
}

void DrShdMdoDecRes::setVertexParam(DrShdFetchMan* fetchMan, int num, const MdsMatVertexInfo* info) {
    if (m_pFetchObj != nullptr) {
        fetchMan->releaseFetchObj(m_pFetchObj);
    }
    m_pFetchObj = fetchMan->createFetchObj(num, info);
}

DrShdMdoDecShdObj::~DrShdMdoDecShdObj() { m_shdList.release(); }

void DrShdMdoDecShdObj::changeMemShader(const unsigned char* shdData, const unsigned char*, const MdsMatTechnique*) {
    m_shdList.m_pPac = reinterpret_cast<const grlib::CGLibShdPacHeader*>(shdData);
    const grlib::CGLibShdPacHeader* head = reinterpret_cast<const grlib::CGLibShdPacHeader*>(shdData);
    unsigned int bufSize = head->m_bufSize;
    unsigned int alignSize = bufSize + (-bufSize & 0xFFF);
    m_shdList.m_memPool.setupBuffer(const_cast<unsigned char*>(shdData) + head->m_bufOfs, alignSize);
    const unsigned char* data = reinterpret_cast<const unsigned char*>(m_shdList.m_pPac);
    const grlib::CGLibShdPacEntry* entries = reinterpret_cast<const grlib::CGLibShdPacEntry*>(data + head->m_entryOfs);
    const unsigned char* programs = data + head->m_progOfs;
    const unsigned char* shaders = data + head->m_shdOfs;
    for (int i = 0; i < m_shdList.m_num; i++) {
        m_shdList.m_pList[i].changeMemPoolSetMem(shaders + entries[i].m_ofs, programs, &m_shdList.m_memPool);
    }
}

void DrShdMdoDecRes::releaseObj() {
    release();
    if (m_pFetchObj != nullptr) {
        DrMan::getIns()->m_shdMan->m_fetchMan->releaseFetchObj(m_pFetchObj);
        m_pFetchObj = nullptr;
    }
}

int DrShdMdoExtTblObj::getDecWorkSize(int valNum, const unsigned char* pac) {
    const grlib::CGLibShdPacHeader* header = reinterpret_cast<const grlib::CGLibShdPacHeader*>(pac);
    int extSize = header->m_num * sizeof(DrShdMdoDecExtTbl);
    int valSize = valNum * sizeof(unsigned int);
    const grlib::CGLibShdPacEntry* entry = reinterpret_cast<const grlib::CGLibShdPacEntry*>(pac + header->m_entryOfs);
    const unsigned char* shd = pac + header->m_shdOfs;
    unsigned int tblSize = 0;
    for (int i = 0; i < header->m_num; i++) {
        tblSize += grlib::CGLibDecShader::calcTblSize(shd + entry[i].m_ofs);
    }
    int pad = (tblSize & 3) != 0 ? 4 - (tblSize & 3) : 0;
    return extSize + valSize + tblSize + pad;
}

unsigned int DrShdMdoDecExtTbl::getValGlobalParam(int idx) { return m_pValGlobalParam[idx]; }

void DrShdMdoDecExtTbl::bindShader() { DrAPCache::s_pIns->setupShader(this, &m_pRes->m_pFetchObj->m_fetch); }

void DrShdUniformBlockMan::createUniformBoneObj(grlib::CGLibTriUniformBlock* block, int num) {
    new (block) grlib::CGLibTriUniformBlock;
    block->setup(num * 0x30);
}

void DrShdUniformBlockMan::createUniformMdlObj(grlib::CGLibTriUniformArray* array, int num) {
    new (array) grlib::CGLibTriUniformArray;
    int size = DrResMdoUniformBlock::getMdlUniformBlockSize();
    array->setupArray(num);
    unsigned int memSize = 0;
    for (int i = 0; i < num; i++) {
        memSize += (size + (-size & 0xFF)) * 3;
    }
    array->allocMem(memSize);
    array->m_ofs = 0;
    for (int i = 0; i < num; i++) {
        array->m_ofs += array->m_pArray[i].setupArray(size, array->m_mem, array->m_ofs);
    }
}

void DrShdUniformBlockMan::createUniformVolTexCalcObj(grlib::CGLibDblUniformArray* array, unsigned int num) {
    new (array) grlib::CGLibDblUniformArray;
    int size = DrResMdoUniformBlock::getVolTexCalcUniformBlockSize();
    array->setupArray(num);
    unsigned int memSize = 0;
    for (unsigned int i = 0; i < num; i++) {
        memSize += (size + (-size & 0xFF)) * 2;
    }
    array->allocMem(memSize);
    array->m_ofs = 0;
    for (unsigned int i = 0; i < num; i++) {
        array->m_ofs += array->m_pArray[i].setupArray(size, array->m_mem, array->m_ofs);
    }
}

void DrShdUniformBlockMan::createUniformRimBloomCalcObj(grlib::CGLibDblUniformArray* array) {
    new (array) grlib::CGLibDblUniformArray;
    int size = DrResMdoUniformBlock::getRimBloomCalcUniformBlockSize();
    array->setupArray(1);
    unsigned int memSize = 0;
    for (unsigned int i = 0; i < 1; i++) {
        memSize += (size + (-size & 0xFF)) * 2;
    }
    array->allocMem(memSize);
    array->m_ofs = 0;
    for (unsigned int i = 0; i < 1; i++) {
        array->m_ofs += array->m_pArray[i].setupArray(size, array->m_mem, array->m_ofs);
    }
}

void DrShdUniformBlockMan::createMotionBlendObj(grlib::CGLibOneUniformArray* array, const unsigned char* data,
                                                DrResMdoVertex* vtx) {
    const BlockHeader* header =
        reinterpret_cast<const BlockHeader*>(data + reinterpret_cast<const DataHead*>(data)->m_blockHeaderOfs);
    grlib::CGLibVtlMemPool* pool = vtx->m_memPool;
    const unsigned char* poolData = pool->m_pMem;
    const BlockInfo* info = reinterpret_cast<const BlockInfo*>(data + header->m_infoOfs);
    array->setupArray(header->m_num);
    array->m_ofs = 0;
    for (int i = 0; i < header->m_num; i++, info++) {
        if (info->m_flags & 1) {
            int size = info->m_num * info->m_size;
            array->m_ofs += size + (-size & 0xFF);
        }
    }
    array->allocMem(array->m_ofs);
    array->m_ofs = 0;
    info = reinterpret_cast<const BlockInfo*>(data + header->m_infoOfs);
    for (int i = 0; i < header->m_num; i++, info++) {
        int size = info->m_num * info->m_size;
        if (info->m_flags & 1) {
            array->m_ofs += array->m_pArray[static_cast<unsigned int>(i)].setupArray(size, array->m_mem, array->m_ofs);
            memcpy(array->m_pArray[static_cast<unsigned int>(i)].m_pBuff, poolData + info->m_dataOfs,
                   info->m_num * static_cast<long>(info->m_size));
        } else {
            unsigned int ofs = info->m_dataOfs;
            array->m_pArray[static_cast<unsigned int>(i)].setupArray(pool, size, ofs);
        }
    }
    for (unsigned int i = 0; i < array->m_num; i++) {
        array->m_pArray[i].updateData();
    }
}

void DrShdUniformBlockMan::changeMotionBlendObj(grlib::CGLibOneUniformArray* array, const unsigned char* data,
                                                DrResMdoVertex* vtx) {
    const BlockHeader* header =
        reinterpret_cast<const BlockHeader*>(data + reinterpret_cast<const DataHead*>(data)->m_blockHeaderOfs);
    grlib::CGLibVtlMemPool* pool = vtx->m_memPool;
    const BlockInfo* info = reinterpret_cast<const BlockInfo*>(data + header->m_infoOfs);
    for (int i = 0; i < header->m_num; i++, info++) {
        if (!(info->m_flags & 1)) {
            int size = info->m_num * info->m_size;
            array->m_pArray[static_cast<unsigned int>(i)].setupArray(pool, size, info->m_dataOfs);
        }
    }
}

void DrShdUniformBlockMan::createUniformMpfMaterialObj(grlib::CGLibDblUniformArray* array,
                                                       const MdsMpfMatTopHeader* header) {
    new (array) grlib::CGLibDblUniformArray;
    int size = DrResMdoUniformBlock::getMpfMaterialUniformBlockSize();
    array->setupArray(header->m_matNum);
    array->m_ofs = 0;
    for (unsigned int i = 0; i < header->m_matNum; i++) {
        array->m_ofs += (size + (-size & 0xFF)) * 2;
    }
    array->allocMem(array->m_ofs);
    array->m_ofs = 0;
    for (int i = 0; i < static_cast<int>(header->m_matNum); i++) {
        array->m_ofs += array->m_pArray[static_cast<unsigned int>(i)].setupArray(size, array->m_mem, array->m_ofs);
    }
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

// DrShdDataList::createWork's list (not written yet)
template class grlib::CGLibShdListBase<ml::DrShdDataObj>;
