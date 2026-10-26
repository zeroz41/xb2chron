#define MM_LIB_FROM_XBRD
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
#include "classes/ml/DrCalcStmListObj.h"
#include "classes/ml/DrCalcTexStreamMan.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/WorkCpu.h"
#include "ml/DrLightMan.h"
#include "ml/DrCalcClipObj.h"
#include "ml/DrCalcCpPlaneObj.h"
#include "ml/CriticalSection.h"
#include "ml/EventFileTh.h"
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

void DrCalcClipWorkCone::debugDraw() {}

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

DrCalcClipWorkCone::~DrCalcClipWorkCone() {}

DrCalcClipWorkPlane::~DrCalcClipWorkPlane() {}

DrCalcClipWorkShadowPlane::~DrCalcClipWorkShadowPlane() {}

DrCalcGpuCost::~DrCalcGpuCost() {}

// DrCalcClipWork's own virtuals: the base tests nothing (its derived classes' tables share these slots)
bool DrCalcClipWork::clipLineTest(mm::Vec3 const&, mm::Vec3 const&, float) const { return false; }
bool DrCalcClipWork::clipTest(float const*, float const*) const { return false; }
bool DrCalcClipWork::clipTest(mm::Vec3 const*, int) const { return false; }
void DrCalcClipWork::debugDraw() {}
bool DrCalcClipWork::clipTest(mm::Vec3 const&, float) const { return false; }
bool DrCalcClipWork::clipTypeTest(mm::Vec3 const&, float) const { return false; }

void DrCalcMan::begin() {
    m_pViewWork->begin(m_viewIdx);
    m_pClipMan->update();
}

void DrCalcMan::end() { m_pViewWork->end(); }

bool DrCalcClipMan::testObjectClip(const mm::Vec3& pos, float radius) {
    for (DrCalcClipObj* pObj = m_pClipObj; pObj != nullptr; pObj = pObj->m_pNext) {
        if (pObj->testObjectClip(pos, radius, m_pBitTbl)) {
            return true;
        }
    }
    return false;
}

bool DrCalcClipMan::testPlaneClip(const mm::Vec3& pos, float radius) {
    for (DrCalcCpPlaneObj* pObj = m_pCpPlaneObj; pObj != nullptr; pObj = pObj->m_pNext) {
        if (!pObj->testClip(pos, radius)) {
            return false;
        }
    }
    return true;
}

void DrCalcClipObj::release() { m_relFlag |= 1 << DrMan::s_nDblStockIdx; }

void DrCalcCpPlaneObj::release() {
    m_relFlag |= 1 << DrMan::s_nDblStockIdx;
    m_planeIdx = 0;
}

DrCalcClipWorkCone::DrCalcClipWorkCone() { m_type = 2; }

DrCalcClipWorkPlane::DrCalcClipWorkPlane() {}

DrCalcClipWorkShadowPlane::DrCalcClipWorkShadowPlane() {}

void DrCalcMan::renderEnd() {
    DrCalcViewWork* pWork = m_pViewWork;
    if (pWork->m_renderReq) {
        pWork->m_renderReq = false;
    }
    pWork->m_oldView = pWork->m_view;
    pWork->m_oldBillboard = pWork->m_billboard;
}

void DrCalcMan::shadowEnd() { m_pViewWork->m_billboard = m_pViewWork->m_saveBillboard; }

DrCalcTexStreamMan::~DrCalcTexStreamMan() { release(); }

unsigned int DrCalcTexStreamMan::jobUpdate(void* man, void*) {
    static_cast<DrCalcTexStreamMan*>(man)->update();
    return 0;
}

void DrCalcTexStreamMan::entryJob() { WorkCpu::wakeup(m_jobGroup); }

void DrCalcTexStreamMan::jobWait() { WorkCpu::sync(m_jobGroup, static_cast<WKCPU_SYNC>(0), static_cast<CPUID>(0)); }

void DrCalcTexStreamMan::apiUpdate() {
    unsigned int num = m_stockNum[DrMan::s_nDblStockIdx];
    DrCalcStmListObj** pList = m_stock[DrMan::s_nDblStockIdx];
    for (unsigned int i = 0; i < num; i++) {
        pList[i]->apiUpdate();
    }
    m_stockNum[DrMan::s_nDblStockIdx] = 0;
}

bool DrCalcStmListObj::isResTex() const { return (m_flags & (FLAG_RESTEX << DrMan::s_nDblStockIdx)) != 0; }

bool DrCalcStmListObj::isResSub() const { return (m_flags & (FLAG_RESSUB << DrMan::s_nDblStockIdx)) != 0; }

void DrCalcStmListObj::setUseMode(DrTexUseMode mode) {
    if (m_useMode[DrMan::s_nDblStockIdx] <= mode) {
        m_flags |= FLAG_USEMODE << DrMan::s_nDblStockIdx;
        m_useMode[DrMan::s_nDblStockIdx] = mode;
    }
}

inline void DrCalcStmListObj::end() {
    if (!(m_flags & FLAG_KEEPMEM)) {
        if (m_pMemObj) {
            DrCalcTexStreamMan::get()->clearMemObj(m_pMemObj);
            m_pMemObj = nullptr;
        }
        m_func = m_endFunc;
        m_flags |= FLAG_END;
    }
}

inline bool DrCalcStmListObj::errWait(StmFunc retry) {
    DrCalcTexStreamMan* pMan = DrCalcTexStreamMan::get();
    pMan->m_errReadSize += m_readSize;
    if (++m_errWait >= 60) {
        m_errWait = 0;
        m_func = retry;
        return true;
    }
    return false;
}

bool DrCalcStmListObj::texstm_notfileWait() {
    m_stateNo = 19;
    m_flags |= FLAG_NOTFILE;
    end();
    return false;
}

bool DrCalcStmListObj::texstm_oldVerWait() {
    m_stateNo = 4;
    end();
    return false;
}

bool DrCalcStmListObj::texstm_stmchk_setWait() {
    m_stateNo = 3;
    end();
    return false;
}

bool DrCalcStmListObj::texstm_defErrWait() {
    m_stateNo = 7;
    return errWait(&DrCalcStmListObj::texstm_defRead);
}

bool DrCalcStmListObj::texstm_requestWait() {
    m_stateNo = 19;
    if (--m_reqWait <= 0) {
        m_func = m_reqFunc;
    }
    return false;
}

bool DrCalcStmListObj::texstm_defMidtexErrWait() {
    m_stateNo = 10;
    return errWait(&DrCalcStmListObj::texstm_deTexCheck);
}

bool DrCalcStmListObj::texstm_fastErrWait() {
    m_stateNo = 17;
    return errWait(&DrCalcStmListObj::texstm_checkTexStm);
}

bool DrCalcStmListObj::OnFileEvent(EventFileTh* pEvent) {
    if (pEvent->m_kind == 2) {
        if (m_pFile == pEvent->m_handle) {
            m_flags &= ~FLAG_READ;
            m_pFile = nullptr;
            return true;
        }
        return false;
    }
    m_flags = (m_flags & ~FLAG_READSTATE) | FLAG_READERR;
    m_pFile = nullptr;
    return false;
}

int DrCalcViewWork::unistatic_diffuseIBL(float* pDst) {
    mm::Mat44 mtx[3];
    memset(mtx, 0, sizeof(mtx));
    grlib::ShdMat44TransposeMat44Array(pDst, mtx, 3);
    return DrResMdoUniformBlock::s_nVarSizeTbl[58];
}

}  // namespace ml
