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
#include "classes/ml/DrCalcTexStmObj.h"
#include "grlib/CGLibTextureBuffer.h"
#include "grlib/CGLibRenderTarget.h"
#include "ml/MlMem.h"
#include "ml/DrIniSys.h"
#include "classes/ml/DrCalcTexStreamMan.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/WorkCpu.h"
#include "ml/DrLightMan.h"
#include "ml/DrCalcClipObj.h"
#include "ml/DrCalcCpPlaneObj.h"
#include "ml/CriticalSection.h"
#include "ml/EventFileTh.h"
#include "ml/DevFileParamTh.h"
#include "classes/ml/DevFileTh.h"
#include "ml/DrAPGxType.h"
#include "ml/DrCalcClipMan.h"
#include "ml/DrCalcGpuCost.h"
#include "ml/DrCalcMan.h"
#include "ml/DrCalcViewWork.h"
#include "ml/DrPixlMan.h"
#include "ml/DrPixlPostMan.h"
#include "ml/DrPixlPostObjCubeMapMultiIBL.h"
#include "ml/DrPixlPostObjExpStencil.h"
#include "ml/DrPixlPostObjUnbranchToDepth.h"
#include "ml/DrResMdoUniformBlock.h"
#include "ml/DrShdCubeCapFilter.h"
#include "ml/DrShdDataList.h"
#include "ml/DrShdDataObj.h"
#include "ml/DrShdLgtMan.h"
#include "navi/NvmshAcMan.h"

namespace ml {

bool (DrCalcClipObj::*DrCalcClipObj::s_pColiCheck[5])(const unsigned char*, const mm::Vec3&) = {
    &DrCalcClipObj::clipcoli_box,        &DrCalcClipObj::clipcoli_sphere,
    &DrCalcClipObj::clipcoli_cylinder,   &DrCalcClipObj::clipcoli_notrot_box,
    &DrCalcClipObj::clipcoli_notrot_cylinder,
};

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

int DrCalcViewWork::unistatic_dither_param(float* pDst) {
    mm::Vec4 v;
    v.x = 1.0f;
    v.y = 0.0f;
    v.z = m_ditherParam[0];
    v.w = m_ditherParam[1];
    grlib::ShdVec4SetVec4(pDst, v);
    return 4;
}

int DrCalcViewWork::unistatic_inv_dither_param(float* pDst) {
    mm::Vec4 v;
    v.x = -1.0f;
    v.y = 1.0f;
    v.z = m_ditherParam[0];
    v.w = m_ditherParam[1];
    grlib::ShdVec4SetVec4(pDst, v);
    return 4;
}

DrCalcClipWorkCone::~DrCalcClipWorkCone() {}

DrCalcClipWorkPlane::~DrCalcClipWorkPlane() {}

DrCalcClipWorkShadowPlane::~DrCalcClipWorkShadowPlane() {}

DrCalcGpuCost::~DrCalcGpuCost() {}

DrCalcMan::DrCalcMan(DrMan* drMan, int viewIdx) {
    m_pDrMan = drMan;
    m_viewIdx = viewIdx;
    m_pViewWork = new (drMan->m_workHandle, nullptr, 0, 4, false) DrCalcViewWork(drMan);
    m_pClipMan = new (m_pDrMan->m_workHandle, nullptr, 0, 4, false) DrCalcClipMan(drMan, m_pViewWork);
}

DrCalcMan::~DrCalcMan() {
    if (m_pViewWork != nullptr) {
        delete m_pViewWork;
        m_pViewWork = nullptr;
    }
    if (m_pClipMan != nullptr) {
        delete m_pClipMan;
        m_pClipMan = nullptr;
    }
}

void DrCalcViewWork::shadowBegin(const mm::Mat44& mtx) {
    m_billboard = mtx;
    m_billboard.m[3][1] = 0.0f;
    m_billboard.m[3][0] = 0.0f;
    m_billboard.m[3][2] = 0.0f;
}

int DrCalcViewWork::unistatic_depth_change(float* pDst, bool) {
    pDst[0] = m_depthParm.x;
    pDst[1] = m_depthParm.y;
    pDst[2] = m_depthParm.z;
    pDst[3] = m_pDrMan->m_pixlMan->m_rate;
    return DrResMdoUniformBlock::s_nVarSizeTbl[25];
}

int DrCalcViewWork::unistatic_digher_val(float* pDst, bool) {
    grlib::CGLibTextureBuffer* pTex = &m_pDrMan->m_iniSys->m_texture[1];
    float w = static_cast<unsigned short>(pTex->getWidth());
    float h = static_cast<unsigned short>(pTex->getHeight());
    pDst[0] = m_pDrMan->m_curViewInfo->m_width * 0.25f;
    pDst[1] = (1.0f / h) * m_pDrMan->m_curViewInfo->m_height;
    pDst[2] = 4.0f / w;
    pDst[3] = w * 0.25f;
    return DrResMdoUniformBlock::s_nVarSizeTbl[26];
}

int DrCalcViewWork::unistatic_screenSize(float* pDst, bool) {
    mm::Vec4 size = mm::Vec4::unit;
    grlib::CGLibRenderTarget* pObj = m_pDrMan->m_pixlMan->getPixlObj(5);
    if (pObj != nullptr) {
        size = mm::Vec4(1.0f / pObj->m_width, 1.0f / pObj->m_height, 0.0f, 0.0f);
    }
    grlib::ShdF32SetVec4(pDst, &size.x);
    return DrResMdoUniformBlock::s_nVarSizeTbl[62];
}

int DrCalcViewWork::unistatic_specularIBL(float* pDst) {
    DrPixlPostObjCubeMapMultiIBL* pIBL = m_pDrMan->m_pixlMan->m_objTbl->m_postMan->m_cubeMapMultiIBL;
    if (pIBL != nullptr) {
        bool bSkip = m_pDrMan->isIBLSkip();
        mm::Vec4 parm = mm::Vec4::zero;
        if (!bSkip) {
            parm.x = pIBL->getPremMipCount();
        }
        grlib::ShdF32SetVec4(pDst, &parm.x);
    }
    return DrResMdoUniformBlock::s_nVarSizeTbl[59];
}

// DrCalcClipWork's own virtuals: the base tests nothing (its derived classes' tables share these slots)
bool DrCalcClipWork::clipLineTest(mm::Vec3 const&, mm::Vec3 const&, float) const { return false; }
bool DrCalcClipWork::clipTest(float const*, float const*) const { return false; }
bool DrCalcClipWork::clipTest(mm::Vec3 const*, int) const { return false; }
void DrCalcClipWork::debugDraw() {}
bool DrCalcClipWork::clipTest(mm::Vec3 const&, float) const { return false; }
int DrCalcClipWork::clipTypeTest(mm::Vec3 const&, float) const { return 0; }

void DrCalcMan::begin() {
    m_pViewWork->begin(m_viewIdx);
    m_pClipMan->update();
}

void DrCalcMan::end() { m_pViewWork->end(); }

void DrCalcClipMan::release() {
    DrCalcClipObj* pObj = m_clipList.m_head;
    while (pObj != nullptr) {
        DrCalcClipObj* pNext = pObj->m_next;
        delete pObj;
        pObj = pNext;
    }
    m_clipList.m_head = nullptr;
    m_clipList.m_tail = nullptr;
    for (int i = 0; i < 2; i++) {
        pObj = m_clipStockLists[i].m_head;
        while (pObj != nullptr) {
            DrCalcClipObj* pNext = pObj->m_next;
            delete pObj;
            pObj = pNext;
        }
        m_clipStockLists[i].m_head = nullptr;
        m_clipStockLists[i].m_tail = nullptr;
    }
    DrCalcCpPlaneObj* pPlaneObj = m_cpPlaneList.m_head;
    while (pPlaneObj != nullptr) {
        DrCalcCpPlaneObj* pNext = pPlaneObj->m_next;
        delete pPlaneObj;
        pPlaneObj = pNext;
    }
    m_cpPlaneList.m_head = nullptr;
    m_cpPlaneList.m_tail = nullptr;
    for (int i = 0; i < 2; i++) {
        pPlaneObj = m_cpPlaneStockLists[i].m_head;
        while (pPlaneObj != nullptr) {
            DrCalcCpPlaneObj* pNext = pPlaneObj->m_next;
            delete pPlaneObj;
            pPlaneObj = pNext;
        }
        m_cpPlaneStockLists[i].m_head = nullptr;
        m_cpPlaneStockLists[i].m_tail = nullptr;
    }
    if (m_pBitTbl != nullptr) {
        mtl::MemManager::deallocate(m_pBitTbl, 0, false);
        m_pBitTbl = nullptr;
    }
}

void DrCalcClipMan::update() {
    int idx = DrMan::s_nDblIdx;
    m_flags &= ~6;
    DrResChankList<DrCalcClipObj>& stock = m_clipStockLists[idx];
    DrCalcClipObj* pObj = stock.m_head;
    while (pObj != nullptr) {
        DrCalcClipObj* pNext = pObj->m_next;
        m_clipList.pushBack(pObj);
        m_flags |= 1;
        pObj = pNext;
    }
    stock.m_head = nullptr;
    stock.m_tail = nullptr;
    if (m_flags & 1) {
        calcBitTbl();
    }
    if (m_bitTblSize != 0) {
        memset(m_pBitTbl, 0, m_bitTblSize);
        pObj = m_clipList.m_head;
        while (pObj != nullptr) {
            DrCalcClipObj* pNext;
            if (pObj->m_relFlag & (1 << idx)) {
                pNext = pObj->m_next;
                m_clipList.remove(pObj);
                delete pObj;
                m_flags |= 1;
            } else {
                const mm::Vec3& viewPos = m_pViewWork->m_viewPos;
                pObj->m_pBitTbl = m_pBitTbl;
                pObj->m_relFlag &= ~0xC;
                pObj->seachTree(pObj->m_pTree, viewPos);
                if (pObj->m_relFlag & 4) {
                    m_flags |= 2;
                }
                if (pObj->m_relFlag & 8) {
                    m_flags |= 4;
                }
                pNext = pObj->m_next;
            }
            pObj = pNext;
        }
    }
    DrResChankList<DrCalcCpPlaneObj>& planeStock = m_cpPlaneStockLists[idx];
    DrCalcCpPlaneObj* pPlaneObj = planeStock.m_head;
    while (pPlaneObj != nullptr) {
        DrCalcCpPlaneObj* pNext = pPlaneObj->m_next;
        m_cpPlaneList.pushBack(pPlaneObj);
        pPlaneObj = pNext;
    }
    planeStock.m_head = nullptr;
    planeStock.m_tail = nullptr;
    pPlaneObj = m_cpPlaneList.m_head;
    while (pPlaneObj != nullptr) {
        DrCalcCpPlaneObj* pNext;
        if (!(pPlaneObj->m_relFlag & (1 << idx))) {
            pPlaneObj->update(m_pViewWork);
            pNext = pPlaneObj->m_next;
        } else {
            pNext = pPlaneObj->m_next;
            m_cpPlaneList.remove(pPlaneObj);
            delete pPlaneObj;
        }
        pPlaneObj = pNext;
    }
}

void DrCalcClipMan::calcBitTbl() {
    m_flags &= ~1;
    int bitNum = 0;
    for (DrCalcClipObj* pObj = m_clipList.m_head; pObj != nullptr; pObj = pObj->m_next) {
        if (bitNum < pObj->m_bitNum) {
            bitNum = pObj->m_bitNum;
        }
    }
    if (bitNum != 0) {
        int size = bitNum / 32 * 4 + 4;
        size += (32 - size % 32) % 32;
        if (m_bitTblSize != size) {
            if (m_pBitTbl != nullptr) {
                mtl::MemManager::deallocate(m_pBitTbl, 0, false);
                m_pBitTbl = nullptr;
            }
            m_bitTblSize = size;
            m_pBitTbl = static_cast<unsigned int*>(
                mtl::MemManager::allocate(m_pDrMan->m_allocHandle, size, 0x20, false, "no name", 0));
        }
    } else {
        if (m_pBitTbl != nullptr) {
            mtl::MemManager::deallocate(m_pBitTbl, 0, false);
            m_pBitTbl = nullptr;
        }
        m_bitTblSize = 0;
    }
}

bool DrCalcClipMan::testObjectClip(const mm::Vec3& pos, float radius) {
    for (DrCalcClipObj* pObj = m_clipList.m_head; pObj != nullptr; pObj = pObj->m_next) {
        if (pObj->testObjectClip(pos, radius, m_pBitTbl)) {
            return true;
        }
    }
    return false;
}

bool DrCalcClipMan::testPlaneClip(const mm::Vec3& pos, float radius) {
    for (DrCalcCpPlaneObj* pObj = m_cpPlaneList.m_head; pObj != nullptr; pObj = pObj->m_next) {
        if (!pObj->testClip(pos, radius)) {
            return false;
        }
    }
    return true;
}

DrCalcClipObj* DrCalcClipMan::createClipObj(const void* resource) {
    CS lock(*DrMan::getCriticalSection());
    DrCalcClipObj* pObj = new (m_pDrMan->m_workHandle, nullptr, 0, 4, false)
        DrCalcClipObj(static_cast<const unsigned char*>(resource), m_pDrMan);
    m_clipStockLists[DrMan::s_nDblStockIdx].pushBack(pObj);
    return pObj;
}

DrCalcCpPlaneObj* DrCalcClipMan::createCpPlaneObj(const void* resource) {
    CS lock(*DrMan::getCriticalSection());
    DrCalcCpPlaneObj* pObj = new (m_pDrMan->m_workHandle, nullptr, 0, 4, false) DrCalcCpPlaneObj(resource);
    m_cpPlaneStockLists[DrMan::s_nDblStockIdx].pushBack(pObj);
    return pObj;
}

bool DrCalcClipObj::testObjectClip(const mm::Vec3& pos, float radius, unsigned int* pBitTbl) {
    if (m_pBitData == nullptr) {
        return false;
    }
    m_pBitTbl = pBitTbl;
    memset(m_pBitWork, 0, m_bitWorkSize);
    m_hitPriority = -1;
    m_hitNum = 0;
    const ResHeader* pRes = m_pRes;
    seachCheckTree(getTree(pRes->checkTreeOfs), pos, radius);
    seachOffTree(getTree(pRes->offTreeOfs), pos, radius);
    bool clip = false;
    for (int i = 0; i < m_hitNum; i++) {
        unsigned short bit = m_hits[i];
        if (m_pBitWork[bit >> 5] & (1 << (bit & 31))) {
            clip = !(m_pBitData[bit].flags & 1);
        }
    }
    return clip;
}

void DrCalcClipObj::setupClip(const unsigned char* pRes, DrMan* drMan) {
    const ResHeader* pHeader = reinterpret_cast<const ResHeader*>(pRes);
    m_pRes = pHeader;
    m_pShapeData = reinterpret_cast<const ShapeEntry*>(getResData(pHeader->shapeOfs));
    m_pTree = getTree(pHeader->treeOfs);
    m_bitNum = pHeader->bitNum;
    m_pCheckData = reinterpret_cast<const CheckEntry*>(getResData(pHeader->checkDataOfs));
    if (m_pBitWork != nullptr) {
        mtl::MemManager::deallocate(m_pBitWork, 0, false);
        m_pBitWork = nullptr;
    }
    if (pHeader->bitDataNum != 0) {
        m_pBitData = reinterpret_cast<const BitInfo*>(getResData(pHeader->bitDataOfs));
        short size = pHeader->bitDataNum / 32 * 4 + 4;
        size += (32 - size % 32) % 32;
        m_bitWorkSize = size;
        m_pBitWork = static_cast<unsigned int*>(
            mtl::MemManager::allocate(drMan->m_allocHandle, m_bitWorkSize, 0x20, false, "no name", 0));
    } else {
        m_pBitData = nullptr;
    }
}

void DrCalcClipObj::release() { m_relFlag |= 1 << DrMan::s_nDblStockIdx; }

bool DrCalcClipObj::clipcoli_sphere(const unsigned char* pData, const mm::Vec3& pos) {
    const ShapeData* pShape = reinterpret_cast<const ShapeData*>(pData);
    float dx = pos.x - pShape->pos[0];
    float dy = pos.y - pShape->pos[1];
    float dz = pos.z - pShape->pos[2];
    return dx * dx + dy * dy + dz * dz <= pShape->radiusSq;
}

void DrCalcClipObj::seachTree(const MdsClipListTreeData* pTree, const mm::Vec3& pos) {
    if (pTree->max[0] < pos.x || pTree->min[0] > pos.x || pTree->max[2] < pos.z || pTree->min[2] > pos.z ||
        pTree->max[1] < pos.y || pTree->min[1] > pos.y) {
        return;
    }
    int childNum = pTree->childNum;
    if (childNum != 0) {
        const unsigned short* pChildren = reinterpret_cast<const unsigned short*>(getResData(pTree->childOfs));
        for (int i = 0; i < childNum; i++) {
            seachTree(m_pTree + pChildren[i], pos);
        }
    }
    int leafNum = pTree->leafNum;
    if (leafNum != 0) {
        const unsigned short* pLeaves = reinterpret_cast<const unsigned short*>(getResData(pTree->leafOfs));
        for (int i = 0; i < leafNum; i++) {
            const ShapeEntry* pShape = m_pShapeData + pLeaves[i];
            if (!(m_pBitTbl[pShape->bit >> 5] & (1 << (pShape->bit & 31)))) {
                const CheckEntry* pCheck = m_pCheckData + pLeaves[i];
                if (pCheck->dispBit == 0 ||
                    !(DrMan::getIns()->m_dispOffBits[pCheck->dispBit >> 5] & (1 << (pCheck->dispBit & 31)))) {
                    if ((this->*s_pColiCheck[pShape->type])(reinterpret_cast<const unsigned char*>(m_pRes) + pShape->dataOfs, pos)) {
                        m_pBitTbl[pShape->bit >> 5] |= 1 << (pShape->bit & 31);
                        if (m_pBitData != nullptr) {
                            const BitInfo* pBit = m_pBitData + pShape->bit;
                            if (pBit->flags & 8) {
                                m_relFlag |= 4;
                            }
                            if (pBit->flags & 4) {
                                m_relFlag |= 8;
                            }
                        }
                    }
                }
            }
        }
    }
}

void DrCalcClipObj::seachCheckTree(const MdsClipListTreeData* pTree, const mm::Vec3& pos, float radius) {
    if (pTree->max[0] < pos.x || pTree->min[0] > pos.x || pTree->max[2] < pos.z || pTree->min[2] > pos.z ||
        pTree->max[1] < pos.y || pTree->min[1] > pos.y) {
        return;
    }
    int childNum = pTree->childNum;
    if (childNum != 0) {
        const unsigned short* pChildren = reinterpret_cast<const unsigned short*>(getResData(pTree->childOfs));
        for (int i = 0; i < childNum; i++) {
            seachCheckTree(m_pTree + pChildren[i], pos, radius);
        }
    }
    int leafNum = pTree->leafNum;
    if (leafNum != 0) {
        const unsigned short* pLeaves = reinterpret_cast<const unsigned short*>(getResData(pTree->leafOfs));
        for (int i = 0; i < leafNum; i++) {
            const ShapeEntry* pShape = m_pShapeData + pLeaves[i];
            const BitInfo* pBit = m_pBitData + pShape->bit;
            if (!(pBit->flags & 2) && (m_pBitTbl[pShape->bit >> 5] & (1 << (pShape->bit & 31)))) {
                const CheckEntry* pCheck = m_pCheckData + pLeaves[i];
                if ((pCheck->dispBit == 0 ||
                     !(DrMan::getIns()->m_dispOffBits[pCheck->dispBit >> 5] & (1 << (pCheck->dispBit & 31)))) &&
                    !(pBit->range < radius) && pBit->priority >= m_hitPriority &&
                    !(m_pBitWork[pShape->bit >> 5] & (1 << (pShape->bit & 31)))) {
                    if ((this->*s_pColiCheck[pShape->type])(reinterpret_cast<const unsigned char*>(m_pRes) + pShape->dataOfs,
                                                            pos) &&
                        m_hitNum < 8) {
                        if (pBit->priority > m_hitPriority) {
                            m_hitNum = 0;
                            m_hitPriority = pBit->priority;
                        }
                        m_hits[m_hitNum++] = pShape->bit;
                        m_pBitWork[pShape->bit >> 5] |= 1 << (pShape->bit & 31);
                    }
                }
            }
        }
    }
}

void DrCalcClipObj::seachOffTree(const MdsClipListTreeData* pTree, const mm::Vec3& pos, float radius) {
    if (pTree->max[0] < pos.x || pTree->min[0] > pos.x || pTree->max[2] < pos.z || pTree->min[2] > pos.z ||
        pTree->max[1] < pos.y || pTree->min[1] > pos.y) {
        return;
    }
    int childNum = pTree->childNum;
    if (childNum != 0) {
        const unsigned short* pChildren = reinterpret_cast<const unsigned short*>(getResData(pTree->childOfs));
        for (int i = 0; i < childNum; i++) {
            seachOffTree(m_pTree + pChildren[i], pos, radius);
        }
    }
    int leafNum = pTree->leafNum;
    if (leafNum != 0) {
        const unsigned short* pLeaves = reinterpret_cast<const unsigned short*>(getResData(pTree->leafOfs));
        for (int i = 0; i < leafNum; i++, pLeaves++) {
            const ShapeEntry* pShape = m_pShapeData + *pLeaves;
            if (m_pBitWork[pShape->bit >> 5] & (1 << (pShape->bit & 31))) {
                const CheckEntry* pCheck = m_pCheckData + *pLeaves;
                if (pCheck->dispBit == 0 ||
                    !(DrMan::getIns()->m_dispOffBits[pCheck->dispBit >> 5] & (1 << (pCheck->dispBit & 31)))) {
                    const BitInfo* pBit = m_pBitData + pShape->bit;
                    if (!(pBit->range < radius) && pBit->priority >= m_hitPriority) {
                        if ((this->*s_pColiCheck[pShape->type])(
                                reinterpret_cast<const unsigned char*>(m_pRes) + pShape->dataOfs, pos)) {
                            for (int j = 0; j < m_hitNum; j++) {
                                if (m_hits[j] == pShape->bit) {
                                    m_pBitWork[pShape->bit >> 5] &= ~(1 << (pShape->bit & 31));
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool DrCalcClipObj::clipcoli_box(const unsigned char* pData, const mm::Vec3& pos) {
    const RotShapeData* pShape = reinterpret_cast<const RotShapeData*>(pData);
    float dx = pos.x - pShape->pos[0];
    float dy = pos.y - pShape->pos[1];
    float dz = pos.z - pShape->pos[2];
    if (!(dx * dx + dy * dy + dz * dz <= pShape->radiusSq)) {
        return false;
    }
    float lx = dx * pShape->mtx[0][0] + dy * pShape->mtx[1][0] + dz * pShape->mtx[2][0];
    if (!(pShape->size[0] >= lx && lx >= -pShape->size[0])) {
        return false;
    }
    float lz = dx * pShape->mtx[0][2] + dy * pShape->mtx[1][2] + dz * pShape->mtx[2][2];
    if (!(pShape->size[2] >= lz && lz >= -pShape->size[2])) {
        return false;
    }
    float ly = dx * pShape->mtx[0][1] + dy * pShape->mtx[1][1] + dz * pShape->mtx[2][1];
    if (!(pShape->size[1] >= ly)) {
        return false;
    }
    if (!(ly >= -pShape->size[1])) {
        return false;
    }
    return true;
}


bool DrCalcClipObj::clipcoli_cylinder(const unsigned char* pData, const mm::Vec3& pos) {
    const RotShapeData* pShape = reinterpret_cast<const RotShapeData*>(pData);
    float dx = pos.x - pShape->pos[0];
    float dy = pos.y - pShape->pos[1];
    float dz = pos.z - pShape->pos[2];
    if (!(dx * dx + dy * dy + dz * dz <= pShape->radiusSq)) {
        return false;
    }
    float ly = dx * pShape->mtx[0][1] + dy * pShape->mtx[1][1] + dz * pShape->mtx[2][1];
    if (!(pShape->size[1] >= ly && ly >= -pShape->size[1])) {
        return false;
    }
    float lx = dx * pShape->mtx[0][0] + dy * pShape->mtx[1][0] + dz * pShape->mtx[2][0];
    float lz = dx * pShape->mtx[0][2] + dy * pShape->mtx[1][2] + dz * pShape->mtx[2][2];
    return lx * lx + lz * lz <= pShape->size[0];
}

bool DrCalcClipObj::clipcoli_notrot_box(const unsigned char* pData, const mm::Vec3& pos) {
    const ShapeData* pShape = reinterpret_cast<const ShapeData*>(pData);
    float dx = pos.x - pShape->pos[0];
    float dy = pos.y - pShape->pos[1];
    float dz = pos.z - pShape->pos[2];
    if (!(dx * dx + dy * dy + dz * dz <= pShape->radiusSq)) {
        return false;
    }
    if (!(pShape->size[0] >= dx && dx >= -pShape->size[0])) {
        return false;
    }
    if (!(pShape->size[2] >= dz && dz >= -pShape->size[2])) {
        return false;
    }
    if (pShape->size[1] >= dy) {
        return dy >= -pShape->size[1];
    }
    return false;
}

bool DrCalcClipObj::clipcoli_notrot_cylinder(const unsigned char* pData, const mm::Vec3& pos) {
    const ShapeData* pShape = reinterpret_cast<const ShapeData*>(pData);
    float dy = pos.y - pShape->pos[1];
    if (!(pShape->size[0] >= dy && dy >= -pShape->size[0])) {
        return false;
    }
    float dx = pos.x - pShape->pos[0];
    float dz = pos.z - pShape->pos[2];
    return dx * dx + dz * dz <= pShape->radiusSq;
}

void DrCalcCpPlaneObj::release() {
    m_relFlag |= 1 << DrMan::s_nDblStockIdx;
    m_planeIdx = 0;
}

DrCalcClipWorkCone::DrCalcClipWorkCone() { m_type = 2; }

void DrCalcClipWorkCone::setConeWork(const mm::Vec3& pos, const mm::Vec3& dir, float angle, float length) {
    m_pos = pos;
    m_dir = dir;
    m_axis = dir * length;
    m_dirDotPos = m_dir.dot(m_pos);
    m_angle = angle;
    m_sin = sinf(angle);
    m_cosHalf = cosf(angle * 0.5f);
    m_length = length;
}

bool DrCalcClipWorkCone::clipTest(const mm::Vec3& pos, float radius) const {
    mm::Vec3 v = pos - m_pos;
    float range = m_length + radius;
    float lenSq = v.dot(v);
    if (lenSq > range * range) {
        return false;
    }
    if (-(pos.dot(m_dir) - m_dirDotPos) > radius) {
        return false;
    }
    float len = sqrtf(lenSq);
    mm::Vec3 n;
    if (len <= 1e-6f) {
        n = mm::Vec3::zero;
    } else {
        n = v * (1.0f / len);
    }
    if (n.dot(m_dir) - m_cosHalf > 0.0f) {
        return true;
    }
    mm::Vec3 side = v.cross(m_dir);
    mm::Vec3 out = m_dir.cross(side);
    float outLen = out.length();
    if (outLen <= 1e-6f) {
        out = mm::Vec3::zero;
    } else {
        float scale = 1.0f / outLen;
        out.x = out.x * scale;
        out.y = out.y * scale;
        out.z = out.z * scale;
    }
    mm::Vec3 edge = m_dir + out * m_sin;
    mm::Vec3 normal = edge.cross(side);
    float normalLen = normal.length();
    if (normalLen <= 1e-6f) {
        normal = mm::Vec3::zero;
    } else {
        float scale = 1.0f / normalLen;
        normal.x = scale * normal.x;
        normal.y = scale * normal.y;
        normal.z = scale * normal.z;
    }
    return normal.dot(pos) - normal.dot(m_pos) <= radius;
}

// the same test as clipTest: 0 outside, 1 touching or inside
int DrCalcClipWorkCone::clipTypeTest(const mm::Vec3& pos, float radius) const {
    mm::Vec3 v = pos - m_pos;
    float range = m_length + radius;
    float lenSq = v.dot(v);
    if (lenSq > range * range) {
        return 0;
    }
    if (-(pos.dot(m_dir) - m_dirDotPos) > radius) {
        return 0;
    }
    float len = sqrtf(lenSq);
    mm::Vec3 n;
    if (len <= 1e-6f) {
        n = mm::Vec3::zero;
    } else {
        n = v * (1.0f / len);
    }
    if (n.dot(m_dir) - m_cosHalf > 0.0f) {
        return 1;
    }
    mm::Vec3 side = v.cross(m_dir);
    mm::Vec3 out = m_dir.cross(side);
    float outLen = out.length();
    if (outLen <= 1e-6f) {
        out = mm::Vec3::zero;
    } else {
        float scale = 1.0f / outLen;
        out.x = out.x * scale;
        out.y = out.y * scale;
        out.z = out.z * scale;
    }
    mm::Vec3 edge = m_dir + out * m_sin;
    mm::Vec3 normal = edge.cross(side);
    float normalLen = normal.length();
    if (normalLen <= 1e-6f) {
        normal = mm::Vec3::zero;
    } else {
        float scale = 1.0f / normalLen;
        normal.x = scale * normal.x;
        normal.y = scale * normal.y;
        normal.z = scale * normal.z;
    }
    return normal.dot(pos) - normal.dot(m_pos) <= radius;
}

DrCalcClipWorkPlane::DrCalcClipWorkPlane() {}

DrCalcClipWorkShadowPlane::DrCalcClipWorkShadowPlane() {}

bool DrCalcClipWorkPlane::clipTest(const mm::Vec3& pos, float radius) const {
    for (int i = 0; i < 6; i++) {
        if (pos.dot(m_planes[i].normal) + m_planes[i].d > radius) {
            return false;
        }
    }
    return true;
}

int DrCalcClipWorkPlane::clipTypeTest(const mm::Vec3& pos, float radius) const {
    int type = 1;
    for (int i = 0; i < 6; i++) {
        float dist = pos.dot(m_planes[i].normal) + m_planes[i].d;
        if (dist > radius) {
            return 0;
        }
        if (radius - dist < radius + radius) {
            type = 2;
        }
    }
    return type;
}

bool DrCalcClipWorkViewPlane::clipTest(const mm::Vec3& pos, float radius) const {
    for (int i = 0; i < 5; i++) {
        if (pos.dot(m_planes[i].normal) + m_planes[i].d > radius) {
            return false;
        }
    }
    return true;
}

// an axis-aligned box (center, half size) is out when all eight corners lie on the outer side of one plane
bool DrCalcClipWorkViewPlane::clipTest(const float* center, const float* size) const {
    float maxX = center[0] + size[0];
    float maxY = center[1] + size[1];
    float maxZ = center[2] + size[2];
    float minX = center[0] - size[0];
    float minY = center[1] - size[1];
    float minZ = center[2] - size[2];
    for (int i = 0; i < 5; i++) {
        const mm::Plane& plane = m_planes[i];
        if (mm::Vec3(maxX, maxY, maxZ).dot(plane.normal) + plane.d < 0.0f) continue;
        if (mm::Vec3(maxX, maxY, minZ).dot(plane.normal) + plane.d < 0.0f) continue;
        if (mm::Vec3(minX, maxY, maxZ).dot(plane.normal) + plane.d < 0.0f) continue;
        if (mm::Vec3(minX, maxY, minZ).dot(plane.normal) + plane.d < 0.0f) continue;
        if (mm::Vec3(maxX, minY, maxZ).dot(plane.normal) + plane.d < 0.0f) continue;
        if (mm::Vec3(maxX, minY, minZ).dot(plane.normal) + plane.d < 0.0f) continue;
        if (mm::Vec3(minX, minY, maxZ).dot(plane.normal) + plane.d < 0.0f) continue;
        if (mm::Vec3(minX, minY, minZ).dot(plane.normal) + plane.d < 0.0f) continue;
        return false;
    }
    return true;
}

// points are out when all of them lie on the outer side of one plane
bool DrCalcClipWorkViewPlane::clipTest(const mm::Vec3* points, int num) const {
    for (int i = 0; i < 5; i++) {
        int j;
        for (j = 0; j < num; j++) {
            if (points[j].dot(m_planes[i].normal) + m_planes[i].d < 0.0f) {
                break;
            }
        }
        if (j >= num) {
            return false;
        }
    }
    return true;
}

int DrCalcClipWorkViewPlane::clipTypeTest(const mm::Vec3& pos, float radius) const {
    int type = 1;
    for (int i = 0; i < 5; i++) {
        float dist = pos.dot(m_planes[i].normal) + m_planes[i].d;
        if (dist > radius) {
            return 0;
        }
        if (radius - dist < radius + radius) {
            type = 2;
        }
    }
    return type;
}

bool DrCalcClipWorkShadowPlane::clipTest(const mm::Vec3& pos, float radius) const {
    for (int i = 0; i < 4; i++) {
        if (pos.dot(m_planes[i].normal) + m_planes[i].d > radius) {
            return false;
        }
    }
    return true;
}

int DrCalcClipWorkShadowPlane::clipTypeTest(const mm::Vec3& pos, float radius) const {
    int type = 1;
    for (int i = 0; i < 4; i++) {
        float dist = pos.dot(m_planes[i].normal) + m_planes[i].d;
        if (dist > radius) {
            return 0;
        }
        if (radius - dist < radius + radius) {
            type = 2;
        }
    }
    return type;
}

void DrCalcClipWorkViewPoli::createLineNormal(mm::Vec3& out, const mm::Vec3& origin, const mm::Vec3& dir,
                                              const mm::Vec3& point) const {
    float lenSq = dir.dot(dir);
    float t = dir.dot(point - origin) / lenSq;
    mm::Vec3 pos = origin + dir * t;
    out.x = point.x - pos.x;
    out.y = point.y - pos.y;
    out.z = point.z - pos.z;
    float len = out.length();
    if (len <= 1e-6f) {
        out = mm::Vec3::zero;
    } else {
        float scale = 1.0f / len;
        out.x = scale * out.x;
        out.y = scale * out.y;
        out.z = scale * out.z;
    }
}

void DrCalcMan::renderEnd() {
    DrCalcViewWork* pWork = m_pViewWork;
    if (pWork->m_renderReq) {
        pWork->m_renderReq = false;
    }
    pWork->m_oldView = pWork->m_view;
    pWork->m_oldBillboard = pWork->m_billboard;
}

void DrCalcMan::shadowEnd() { m_pViewWork->m_billboard = m_pViewWork->m_saveBillboard; }

unsigned int DrCalcTexStreamMan::MEM_4K_ALIGNMENT = 0x1000;

CriticalSection& DrCalcTexStreamMan::getCriticalSection() {
    static CriticalSection s_cs;  // Proposed name, not the original's (lbl_71015E9BF8)
    return s_cs;
}

DrCalcTexStreamMan::~DrCalcTexStreamMan() { release(); }

unsigned int DrCalcTexStreamMan::jobUpdate(void* man, void*) {
    static_cast<DrCalcTexStreamMan*>(man)->update();
    return 0;
}

void DrCalcTexStreamMan::update() {
    calcUpdateList();
    m_errReadSize = 0;
    pad_249C = pad_2498;
    pad_2498 = 3;
    for (DrCalcStmListObj* p = m_stmLists[0].m_head; p != nullptr; p = p->m_pNext) {
        if (p->m_flags & (0x1000000 << DrMan::s_nDblIdx)) {
            p->m_curUseMode = p->m_useMode[DrMan::s_nDblIdx];
            p->m_flags &= ~(0x1000000 << DrMan::s_nDblIdx);
            p->m_useMode[DrMan::s_nDblIdx] = 0;
        }
        if (p->m_useCount == 0) {
            p->m_curUseMode = 0;
        }
        while ((p->*p->m_func)()) {
        }
    }
    calcMemOptimization();
    afterUpdate();
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

void DrCalcTexStreamMan::cntMemUpdate() {
    if (pad_2068 & 1) {
        if (pad_2488++ < 1) {
            int freeNum = 0;
            for (int i = 0; i < pad_248C; i++) {
                DrCalcTexStmObj* pObj = m_memCache[i];
                if (pObj == nullptr) {
                    freeNum++;
                } else if (!(pObj->m_flags & 2)) {
                    clearMemObj(pObj);
                    m_memCache[i] = nullptr;
                    freeNum++;
                }
            }
            if (freeNum == pad_248C) {
                pad_2488 = 0;
                pad_248C = 0;
                pad_2068 &= ~1;
            }
        } else {
            pad_2488 = 0;
            pad_2068 &= ~1;
            for (int i = 0; i < pad_248C; i++) {
                if (m_memCache[i] != nullptr) {
                    clearMemObj(m_memCache[i]);
                    m_memCache[i] = nullptr;
                }
            }
            pad_248C = 0;
        }
    }
}

bool DrCalcStmListObj::texstm_stmchk_topheader() {
    m_stateNo = 0;
    m_idleFrame[0] = 0;
    m_idleFrame[1] = 0;
    if (!(m_flags & FLAG_KEEPMEM)) {
        end();
    } else {
        DrCalcTexStreamMan* pMan = DrCalcTexStreamMan::get();
        if (pMan->pad_2498 >= 0) {
            pMan->pad_2498 = 0;
        }
        if (!(pMan->pad_2068 & 0x20)) {
            m_pMemObj = pMan->createReadFreeObj(0x1000);
            if (m_pMemObj == nullptr) {
                DrCalcTexStreamMan::get()->m_errReadSize += 0x1000;
            } else {
                DevFileParamTh param;
                param.pad_4c = 0;
                param.pad_50 = 0x40;
                param.m_buffer = m_pMemObj->m_pMem;
                param.m_size = 0x1000;
                param.m_listener = this;
                param.m_path = m_name.m_str;
                m_pFile = DevFileTh::readFile(param);
                if (m_pFile == nullptr) {
                    if (m_pMemObj) {
                        DrCalcTexStreamMan::get()->clearMemObj(m_pMemObj);
                        m_pMemObj = nullptr;
                    }
                    m_func = &DrCalcStmListObj::texstm_notfileWait;
                    m_endFunc = &DrCalcStmListObj::texstm_notfileWait;
                } else {
                    m_pMemObj->m_flags |= 0x24;
                    m_func = &DrCalcStmListObj::texstm_stmchk_topWait;
                    m_flags |= FLAG_READ;
                    DrMan::get()->setAllMiddelTexStmChk(true);
                }
            }
        }
    }
    return false;
}

bool DrCalcStmListObj::isResTex() const { return (m_flags & (FLAG_RESTEX << DrMan::s_nDblStockIdx)) != 0; }

bool DrCalcStmListObj::isResSub() const { return (m_flags & (FLAG_RESSUB << DrMan::s_nDblStockIdx)) != 0; }

void DrCalcStmListObj::setUseMode(DrTexUseMode mode) {
    if (m_useMode[DrMan::s_nDblStockIdx] <= mode) {
        m_flags |= FLAG_USEMODE << DrMan::s_nDblStockIdx;
        m_useMode[DrMan::s_nDblStockIdx] = mode;
    }
}

DrCalcStmListObj::ResTexObj* DrCalcStmListObj::getResVertexObj() {
    return &m_pResObj[DrMan::s_nDblStockIdx][m_vertexIdx];
}

DrCalcStmListObj::ResTexObj* DrCalcStmListObj::getResShaderObj() {
    return &m_pResObj[DrMan::s_nDblStockIdx][m_shaderIdx];
}

DrCalcStmListObj::ResTexObj* DrCalcStmListObj::getResLowTexObj() {
    return &m_pResObj[DrMan::s_nDblStockIdx][m_lowTexIdx];
}

grlib::CGLibTextureBuffer* DrCalcStmListObj::getTexObj(unsigned int idx) {
    return &m_texBuf[idx];
}

void* DrCalcStmListObj::getAdder() {
    if ((m_flags & 0x10000) && m_pAddMemObj != nullptr) {
        return m_pAddMemObj->m_pMem;
    }
    return nullptr;
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

bool DrCalcStmListObj::texstm_stmchk_topWait() {
    m_stateNo = 1;
    m_idleFrame[0] = 0;
    m_idleFrame[1] = 0;
    DrCalcTexStreamMan* pMan = DrCalcTexStreamMan::get();
    if (pMan->pad_2498 >= 0) {
        pMan->pad_2498 = 0;
    }
    if (m_flags & FLAG_READ) {
        DrMan::get()->setAllMiddelTexStmChk(true);
    } else if (!(m_flags & FLAG_KEEPMEM)) {
        end();
    } else if (!(m_flags & FLAG_READERR)) {
        if (pMan->pad_2068 & 0x20) {
            return false;
        }
        DrCalcTexStmObj* pObj = m_pMemObj;
        const unsigned int* pHead = static_cast<const unsigned int*>(pObj->m_pMem);
        if (pHead[0] == 0x4D535244 || pHead[1] == 10001) {
            unsigned int size = pHead[2];
            unsigned int readSize;
            if (size > 0x1000) {
                unsigned int align = DrCalcTexStreamMan::MEM_4K_ALIGNMENT;
                readSize = (align - size % align) % align + size;
                pObj = pMan->createReadFreeObj(readSize);
                pMan = DrCalcTexStreamMan::get();
                if (pObj == nullptr) {
                    pMan->m_errReadSize += readSize;
                    return false;
                }
                if (m_pMemObj) {
                    pMan->clearMemObj(m_pMemObj);
                    m_pMemObj = nullptr;
                }
                m_pMemObj = pObj;
            } else {
                readSize = 0x1000;
            }
            DevFileParamTh param;
            param.pad_4c = pHead[3];
            param.pad_50 = pHead[2];
            param.m_buffer = pObj->m_pMem;
            param.m_size = readSize;
            param.m_path = m_name.m_str;
            param.m_listener = this;
            m_pFile = DevFileTh::readFile(param);
            m_pMemObj->m_flags |= 0x24;
            m_func = &DrCalcStmListObj::texstm_stmchk_topLast;
            m_flags |= FLAG_READ;
            DrMan::get()->setAllMiddelTexStmChk(true);
        } else {
            m_func = &DrCalcStmListObj::texstm_oldVerWait;
            if (pObj) {
                pMan->clearMemObj(pObj);
                m_pMemObj = nullptr;
            }
        }
    } else {
        m_flags &= ~FLAG_READERR;
        if (m_pMemObj) {
            DrCalcTexStreamMan::get()->clearMemObj(m_pMemObj);
            m_pMemObj = nullptr;
        }
        m_func = &DrCalcStmListObj::texstm_notfileWait;
    }
    return false;
}

bool DrCalcStmListObj::texstm_stmchk_topLast() {
    m_stateNo = 2;
    m_idleFrame[0] = 0;
    m_idleFrame[1] = 0;
    DrCalcTexStreamMan* pMan = DrCalcTexStreamMan::get();
    if (pMan->pad_2498 >= 0) {
        pMan->pad_2498 = 0;
    }
    if (m_flags & FLAG_READ) {
        DrMan::get()->setAllMiddelTexStmChk(true);
    } else if (!(m_flags & FLAG_KEEPMEM)) {
        end();
    } else if (m_flags & FLAG_READERR) {
        m_flags &= ~FLAG_READERR;
        if (m_pMemObj) {
            DrCalcTexStreamMan::get()->clearMemObj(m_pMemObj);
            m_pMemObj = nullptr;
        }
        m_func = &DrCalcStmListObj::texstm_notfileWait;
    } else {
        m_func = &DrCalcStmListObj::texstm_stmchk_setWait;
        m_flags |= 0x4000;
    }
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

// the memory object cut from obj's end after size bytes: a spare object takes the rest and is linked after obj;
// null when obj is smaller or no spare is left (inline in the reads' waits; the name is not the original's)
inline DrCalcTexStmObj* DrCalcTexStreamMan::splitMemObj(DrCalcTexStmObj* obj, unsigned int size) {
    if (static_cast<unsigned int>(obj->m_size) < size) {
        return nullptr;
    }
    DrCalcTexStreamMan* pMan = get();
    DrCalcTexStmObj* pSpare = pMan->m_spareList.m_head;
    if (pSpare != nullptr) {
        pMan->m_spareList.remove(pSpare);
        int total = obj->m_size;
        obj->m_size = size;
        pSpare->m_size = total - size;
        pSpare->m_pMem = static_cast<unsigned char*>(obj->m_pMem) + size;
        pSpare->m_flags = 1;
        pMan->m_memList.insertNext(obj, pSpare);
    }
    return pSpare;
}

bool DrCalcStmListObj::texstm_defReadWait() {
    m_stateNo = 6;
    m_idleFrame[0] = 0;
    m_idleFrame[1] = 0;
    DrCalcTexStreamMan* pMan = DrCalcTexStreamMan::get();
    if (pMan->pad_2498 >= 0) {
        pMan->pad_2498 = 0;
    }
    if (m_flags & FLAG_READ) {
        DrMan::get()->setAllMiddelTexStmChk(true);
        return false;
    }
    if (m_flags & FLAG_READERR) {
        m_flags &= ~FLAG_READERR;
        if (m_pAddMemObj) {
            DrCalcTexStreamMan::get()->clearMemObj(m_pAddMemObj);
            m_pAddMemObj = nullptr;
        }
        m_reqFunc = &DrCalcStmListObj::texstm_defRead;
        m_reqWait = 90;
        m_func = &DrCalcStmListObj::texstm_requestWait;
        return false;
    }
    DrCalcTexStmObj* pObj = m_pAddMemObj;
    pad_94 = pObj->m_size;
    pObj->m_flags &= ~0x24;
    int num = 0;
    if (m_flags & 0x100) {
        m_texObjs[0] = m_pAddMemObj;
        num = 1;
    }
    unsigned int prev = 0;
    if (m_flags & 0x200) {
        if (num == 0) {
            m_texObjs[0] = m_pAddMemObj;
        } else {
            m_texObjs[num] = DrCalcTexStreamMan::splitMemObj(m_texObjs[num - 1], m_texInfo[m_shaderIdx].m_offset);
            prev = m_texInfo[m_shaderIdx].m_offset;
        }
        num++;
    }
    if (m_flags & 0x400) {
        if (num == 0) {
            m_texObjs[0] = m_pAddMemObj;
        } else {
            m_texObjs[num] = DrCalcTexStreamMan::splitMemObj(m_texObjs[num - 1], m_texInfo[m_lowTexIdx].m_offset - prev);
        }
        num++;
    }
    m_pAddMemObj = nullptr;
    pad_a2 = num;
    for (int i = 0; i < num; i++) {
        ResTexObj* pRes0 = &m_pResObj[0][i];
        ResTexObj* pRes1 = &m_pResObj[1][i];
        pRes0->m_pData = pRes1->m_pData = static_cast<const unsigned char*>(m_texObjs[i]->m_pMem);
        pRes0->m_size = pRes1->m_size = m_texObjs[i]->m_size;
        pRes0->m_flags = pRes1->m_flags = 0;
        pRes0->pad_c = pRes1->pad_c = 0;
        m_texObjs[i]->m_flags |= 8;
    }
    m_flags |= 8;
    m_func = &DrCalcStmListObj::texstm_deTexCheck;
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

bool DrCalcStmListObj::texstm_defMidTexWait() {
    m_stateNo = 9;
    m_idleFrame[0] = 0;
    m_idleFrame[1] = 0;
    DrCalcTexStreamMan* pMan = DrCalcTexStreamMan::get();
    if (pMan->pad_2498 > 0) {
        pMan->pad_2498 = 1;
    }
    if (m_flags & FLAG_READ) {
        DrMan::get()->setAllMiddelTexStmChk(true);
        return false;
    }
    DrCalcTexStmObj* pObj = m_pAddMemObj;
    pad_98 = pObj->m_size;
    pObj->m_flags &= ~0x24;
    m_texObjs[m_heightBegin] = m_pAddMemObj;
    unsigned int prev = 0;
    for (unsigned int i = m_heightBegin + 1; i < m_heightEnd; i++) {
        m_texObjs[i] = DrCalcTexStreamMan::splitMemObj(m_texObjs[i - 1], m_texInfo[i].m_offset - prev);
        prev = m_texInfo[i].m_offset;
    }
    m_pAddMemObj = nullptr;
    for (unsigned int i = m_heightBegin; i < m_heightEnd; i++) {
        ResTexObj* pRes0 = &m_pResObj[0][i];
        ResTexObj* pRes1 = &m_pResObj[1][i];
        pRes0->m_pData = pRes1->m_pData = static_cast<const unsigned char*>(m_texObjs[i]->m_pMem);
        pRes0->m_size = pRes1->m_size = m_texObjs[i]->m_size;
        pRes0->m_flags = pRes1->m_flags = 0;
        pRes0->pad_c = pRes1->pad_c = 0;
    }
    pad_90 = 0;
    m_func = &DrCalcStmListObj::texstm_defMidTexUpdate;
    m_flags |= 0x10;
    return false;
}

bool DrCalcStmListObj::texstm_defMidtexErrWait() {
    m_stateNo = 10;
    return errWait(&DrCalcStmListObj::texstm_deTexCheck);
}

bool DrCalcStmListObj::texstm_defHeightWait() {
    m_stateNo = 12;
    m_idleFrame[0] = 0;
    m_idleFrame[1] = 0;
    DrCalcTexStreamMan* pMan = DrCalcTexStreamMan::get();
    if (pMan->pad_2498 >= 2) {
        pMan->pad_2498 = 2;
    }
    if (++m_heightWait >= 2) {
        m_heightWait = 3;
        if (m_pAddMemObj) {
            pMan->clearMemObj(m_pAddMemObj);
            m_pAddMemObj = nullptr;
        }
    }
    if (!(m_flags & FLAG_READ) && m_heightWait >= 2) {
        m_heightWait = 0;
        m_texObjs[m_heightIdx]->m_flags &= ~0xA4;
        m_texObjs[m_heightIdx]->m_flags |= 0x310;
        m_func = &DrCalcStmListObj::texstm_defMidTexUpdate;
        pad_90 = 0;
        return true;
    }
    return false;
}

bool DrCalcStmListObj::texstm_defHeightRelease() {
    m_stateNo = 13;
    m_idleFrame[0] = 0;
    m_idleFrame[1] = 0;
    if (++m_errWait >= 2) {
        m_errWait = 0;
        m_func = &DrCalcStmListObj::texstm_defMidTexUpdate;
        pad_90 = 0;
        for (unsigned int i = m_heightBegin; i < m_heightEnd; i++) {
            DrCalcTexStmObj* pObj = m_texObjs[i];
            if (pObj->m_flags & 0x80) {
                DrCalcTexStreamMan* pMan = DrCalcTexStreamMan::get();
                unsigned int size = pObj->pad_28;
                DrCalcTexStmObj* pSpare = pMan->m_spareList.m_head;
                pMan->m_spareList.remove(pSpare);
                int total = pObj->m_size;
                pObj->m_size = size;
                pSpare->m_size = total - size;
                pSpare->m_pMem = static_cast<unsigned char*>(pObj->m_pMem) + size;
                pSpare->m_flags = 1;
                pMan->m_memList.insertNext(pObj, pSpare);
                pSpare->m_flags = (m_texObjs[i]->m_flags | pSpare->m_flags) & ~0x1A0;
                DrCalcTexStmObj* pOld = m_texObjs[i];
                m_texObjs[i] = pSpare;
                if (pOld) {
                    DrCalcTexStreamMan::get()->clearMemObj(pOld);
                }
            }
        }
        return true;
    }
    return false;
}

bool DrCalcStmListObj::texstm_fastReadWait() {
    m_stateNo = 18;
    m_idleFrame[0] = 0;
    m_idleFrame[1] = 0;
    DrCalcTexStreamMan* pMan = DrCalcTexStreamMan::get();
    if (pMan->pad_2498 > 0) {
        pMan->pad_2498 = 1;
    }
    if (m_flags & FLAG_READ) {
        return false;
    }
    if (m_flags & FLAG_READERR) {
        m_flags &= ~FLAG_READERR;
        if (m_pAddMemObj) {
            DrCalcTexStreamMan::get()->clearMemObj(m_pAddMemObj);
            m_pAddMemObj = nullptr;
        }
        m_reqFunc = &DrCalcStmListObj::texstm_checkTexStm;
        m_reqWait = 90;
        m_func = &DrCalcStmListObj::texstm_requestWait;
        return false;
    }
    DrCalcTexStmObj* pObj = m_pAddMemObj;
    pad_98 = pObj->m_size;
    pObj->m_flags &= ~0x24;
    m_texObjs[0] = m_pAddMemObj;
    for (int i = 1; i < m_entryNum; i++) {
        m_texObjs[i] = DrCalcTexStreamMan::splitMemObj(m_texObjs[i - 1], m_texInfo[i].m_offset);
    }
    m_pAddMemObj = nullptr;
    for (int i = 0; i < m_entryNum; i++) {
        ResTexObj* pRes0 = &m_pResObj[0][i];
        ResTexObj* pRes1 = &m_pResObj[1][i];
        pRes0->m_pData = pRes1->m_pData = static_cast<const unsigned char*>(m_texObjs[i]->m_pMem);
        pRes0->m_size = pRes1->m_size = m_texObjs[i]->m_size;
        pRes0->m_flags = pRes1->m_flags = 0;
        pRes0->pad_c = pRes1->pad_c = 0;
    }
    m_func = &DrCalcStmListObj::texstm_defupdate;
    m_flags |= 0x10;
    return true;
}

bool DrCalcStmListObj::texstm_fastErrWait() {
    m_stateNo = 17;
    return errWait(&DrCalcStmListObj::texstm_checkTexStm);
}

bool DrCalcStmListObj::texstm_defupdate() {
    m_stateNo = 19;
    if (m_curUseMode != 0) {
        m_idleFrame[0] = 0;
        m_idleFrame[1] = 0;
    }
    if (!(m_flags & 0x10)) {
        m_func = &DrCalcStmListObj::texstm_checkTexStm;
    }
    return false;
}

void DrCalcStmListObj::release() {
    CS cs(DrCalcTexStreamMan::getCriticalSection());
    if (--m_useCount < 0) {
        m_useCount = 0;
    }
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

int DrCalcViewWork::unistatic_lightDir(float* pDst) {
    DrLightMan* pLightMan = m_pDrMan->m_lightMan;
    int num = pLightMan->m_stockCount;
    int n = num > 2 ? 2 : num;
    const mm::Vec3* pDir = pLightMan->m_stockDir;
    for (int i = 0; i < n; i++, pDir++) {
        float x = -pDir->x;
        float y = -pDir->y;
        float z = -pDir->z;
        mm::Vec3 dir(m_view.m[0][0] * x + m_view.m[1][0] * y + m_view.m[2][0] * z,
                     m_view.m[0][1] * x + m_view.m[1][1] * y + m_view.m[2][1] * z,
                     m_view.m[0][2] * x + m_view.m[1][2] * y + m_view.m[2][2] * z);
        float len = dir.length();
        if (len <= 1e-6f) {
            dir = mm::Vec3::zero;
        } else {
            float scale = 1.0f / len;
            dir.x = dir.x * scale;
            dir.y = dir.y * scale;
            dir.z = scale * dir.z;
        }
        pDst[i * 4 + 0] = dir.x;
        pDst[i * 4 + 1] = dir.y;
        pDst[i * 4 + 2] = dir.z;
    }
    for (int i = n; i < 2; i++) {
        pDst[i * 4 + 0] = 0.0f;
        pDst[i * 4 + 1] = 0.0f;
        pDst[i * 4 + 2] = 1.0f;
    }
    pDst[3] = 1.0f / m_pDrMan->m_pixlMan->m_objTbl->m_toneMapVal[0];
    return DrResMdoUniformBlock::s_nVarSizeTbl[28];
}

int DrCalcViewWork::unistatic_lightCol(float* pDst) {
    DrLightMan* pLightMan = m_pDrMan->m_lightMan;
    int num = pLightMan->m_stockCount;
    int n = num > 2 ? 2 : num;
    const mm::Col3* pCol = pLightMan->m_stockColor;
    for (int i = 0; i < n; i++, pCol++) {
        pDst[i * 4 + 0] = pCol->r;
        pDst[i * 4 + 1] = pCol->g;
        pDst[i * 4 + 2] = pCol->b;
    }
    for (int i = n; i < 2; i++) {
        pDst[i * 4 + 0] = 0.0f;
        pDst[i * 4 + 1] = 0.0f;
        pDst[i * 4 + 2] = 0.0f;
    }
    return DrResMdoUniformBlock::s_nVarSizeTbl[29];
}

int DrCalcViewWork::unistatic_diffuseIBL(float* pDst) {
    mm::Mat44 mtx[3];
    memset(mtx, 0, sizeof(mtx));
    grlib::ShdMat44TransposeMat44Array(pDst, mtx, 3);
    return DrResMdoUniformBlock::s_nVarSizeTbl[58];
}

}  // namespace ml
