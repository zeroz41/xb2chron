#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrFogObjGbl.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrMdoCtlCldMdl.h"
#include "classes/ml/DrMdoCtlDammy.h"
#include "classes/ml/DrMdoCtlMpf.h"
#include "classes/ml/DrResMdoSortMpf.h"
#include "ml/DrResMdoSeamWrkPosMpf.h"
#include <new>
#include "classes/cloud/CloudMan.h"
#include "cloud/CloudObjMan.h"
#include "cloud/CloudMdlDataObj.h"
#include "classes/ml/DrMdoCtlNom.h"
#include "classes/ml/DrMdoCtlPos.h"
#include "classes/ml/DrResMdoSortPos.h"
#include "classes/ml/DrMdoCtlSeamAll.h"
#include "ml/DrEnvColiObj.h"
#include "ml/DrCalcClipObj.h"
#include "ml/DrResEtcTexList.h"
#include "ml/DrResEtcUniformObj.h"
#include "ml/DrCalcClipMan.h"
#include "ml/DrGlobalIBLMan.h"
#include "classes/ml/DrMdoMat.h"
#include "classes/ml/DrMdoZSortObj.h"
#include "classes/ml/DrResMdoSeamColi.h"
#include "classes/ml/DrResMdoSortSeamAll.h"
#include "classes/ml/DrResMdoSortSeamEnvMap.h"
#include "classes/ml/DevGraph.h"
#include "ml/DrResMdoPos.h"
#include "classes/ml/DrResMdoSeamWrkBase.h"
#include "classes/ml/DrResMdoSeamTexList.h"
#include "classes/ml/DrResMdoSeamTexture.h"
#include "classes/ml/DrResMdoSeamVertex.h"
#include "classes/ml/DrResMdoSeamWrkInst.h"
#include "classes/ml/DrResMdoSeamWrkLight.h"
#include "classes/ml/DrResMdoSeamWrkLow.h"
#include "classes/ml/DrResMdoSeamWrkEnv.h"
#include "classes/ml/DrEnvironmentObj.h"
#include "classes/ml/DrResMdoSeamWrkMpf.h"
#include "classes/ml/DrShdLgtClustered.h"
#include "classes/ml/DrShdLgtHybrid.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibOneUniformBlock.h"
#include "grlib/CGLibTriUniformBlock.h"
#include "grlib/CGLibUniformArray.h"
#include "math.h"
#include "stddef.h"
#include "ml/DrCalcMan.h"
#include "ml/DrCalcViewWork.h"
#include "ml/DrEnvironmentAnim.h"
#include "ml/DrIniSys.h"
#include "ml/DrMdoAnim.h"
#include "ml/DrMdoCtlMpfInst.h"
#include "classes/ml/DrCalcStmListObj.h"
#include "classes/ml/DrPixlShadowObj.h"
#include "classes/ml/DrLightObj.h"
#include "ml/DrMdoMorphing.h"
#include "ml/DrMdoSamplerMan.h"
#include "ml/DrMdoShdSetMpf.h"
#include "ml/DrMdoShdSet.h"
#include "ml/DrResShdPrePass.h"
#include "ml/DrResShdShw.h"
#include "classes/ml/DrMdlObj.h"
#include "grlib/CGLibEtcUniformBlock.h"
#include "grlib/CGLibTextureBuffer.h"
#include "ml/DrMdoTexSimpleMan.h"
#include "ml/DrMdoTextureMan.h"
#include "ml/DrMdoVertexMan.h"
#include "ml/DrPixlMdlSampler.h"
#include "ml/DrResMdoMorpObj.h"
#include "ml/DrResShdStreamOut.h"
#include "ml/DrResMdoLodObj.h"
#include "ml/DrResChkList.h"
#include "ml/DrResMdoMeshObj.h"
#include "ml/DrResEtcPamObj.h"
#include "ml/DrResEtcParams.h"
#include "ml/MdsFixAnm.h"
#include "ml/MdsMatTechnique.h"
#include "ml/DrPixlShadowMan.h"
#include "grlib/CGLibVtxInstans.h"
#include "ml/MdsMpfMatInfoHeader.h"
#include "ml/DrResShdMpf.h"
#include "ml/DrResMpfSampler.h"
#include "grlib/CGLibUniformArray.h"
#include "ml/DrMdoCtlMpfAuto.h"
#include "ml/DrMdoCtlMpfWork.h"
#include "ml/DrMdoSetup.h"
#include "ml/DrMdoSmlShadowMan.h"
#include "ml/DrMdoMpfMan.h"
#include "ml/DrLightMan.h"
#include "ml/DrMdlMan.h"
#include "ml/DrMdoZSortMan.h"
#include "ml/DrPixlDeferred.h"
#include "ml/DrPixlMan.h"
#include "ml/DrPixlOccQuery.h"
#include "ml/DrMdoNomAfterImage.h"
#include "ml/DrPixlPostMan.h"
#include "ml/DrPixlPostObjCubeMapIBL.h"
#include "ml/DrPixlPostParm.h"
#include "ml/DrPixlTileParm.h"
#include "ml/DrResMdoMat.h"
#include "ml/DrPixlShadowCacheMan.h"
#include "ml/DrCalcCpPlaneObj.h"
#include "ml/DrResMdoInstMdlInfo.h"
#include "ml/DrResMdoLight.h"
#include "ml/DrResMdoPntAlphaMan.h"
#include "ml/DrResMdoVertex.h"
#include "ml/DrResMdoTexList.h"
#include "ml/DrResMdoVtxMeshObj.h"
#include "ml/DrShdDataList.h"
#include "ml/DrShdLgtMan.h"
#include "ml/DrShdMan.h"
#include "ml/DrShdMdoMan.h"
#include "ml/DrShdMdoDecExtTbl.h"
#include "ml/MdoWrkMatRes.h"
#include "ml/DrResMdoShdObj.h"
#include "ml/MdsMatInfoHeader.h"
#include "ml/MdsMatTopHeader.h"
#include "ml/MdsMatVariableTbl.h"
#include "ml/DrResMdoUniformBlock.h"
#include "grlib/CGLibUniBaseUtility.h"
#include "ml/MdsMatValShaderCate.h"
#include "mm/Col4.h"
#include "mm/Math.h"
#include "ml/MTRand.h"
#include "mtl/MemManager.h"
#include "string.h"

namespace ml {

DrMdoCtl::DrMdoCtl(int viewNum) : DrMdoAnim(viewNum) {}

void DrMdoCtl::setMatrix(const mm::Mat44& matrix) {
    m_matrix = matrix;
}

void DrMdoCtl::setOffsetPos(const mm::Vec3& pos) {
    m_offsetPos = pos;
}

void DrMdoCtl::partsShadowBaseRender(const MdsMdlTopHeader* top) {
    int num = top->m_infoNum;
    if (num <= 0) {
        return;
    }
    DrShdDataList* list = m_pDrMan->m_shdMan->m_dataList;
    const MdsMdlInfoHeader* info = reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs);
    for (int i = 0; i < num; i++, info++) {
        if ((info->m_shadowFlags & 0x40) && !(info->m_flags & 0x20000)) {
            if (!((m_pWrkMatRes->m_pMatInfo + info->m_matIdx)->m_shdFlags & 0x4)) {
                const MdsMatInfoHeader* mat = &m_pWrkMatRes->m_pMatInfo[info->m_matIdx];
                m_pWrkMatRes->m_pVertex->setVertexBind(info->m_vtxBindIdx);
                int matIdx = info->m_matIdx;
                DrMdoShdSetShadow shd;
                shd.m_pMdl = this;
                (shd.*DrMdoShdSetShadow::s_pShwMaterial[3])(3, mat, 0, matIdx, list);
                DrResMdoVertex* vtx = m_pWrkMatRes->m_pVertex;
                if (info->m_flags & 0x2000) {
                    vtx->render(info->m_renderIdx[1]);
                } else {
                    vtx->render(info->m_renderIdx[0]);
                }
            }
        }
    }
}

void DrMdoCtl::partsShadowNukiBaseRender(const MdsMdlTopHeader* top) {
    int num = top->m_infoNum;
    if (num <= 0) {
        return;
    }
    DrShdDataList* list = m_pDrMan->m_shdMan->m_dataList;
    const MdsMdlInfoHeader* info = reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs);
    for (int i = 0; i < num; i++, info++) {
        if ((info->m_shadowFlags & 0x40) && !(info->m_flags & 0x20000)) {
            const MdsMatInfoHeader* mat = m_pWrkMatRes->m_pMatInfo + info->m_matIdx;
            if (mat->m_shdFlags & 0x4) {
                m_pWrkMatRes->m_pVertex->setVertexBind(info->m_vtxBindIdx);
                int matIdx = info->m_matIdx;
                if (mat->m_shdFlags & 0x8) {
                    DrMdoShdSetShadow shd;
                    shd.m_pMdl = this;
                    (shd.*DrMdoShdSetShadow::s_pShwMaterial[5])(5, mat, 0, matIdx, list);
                } else {
                    DrMdoShdSetShadow shd;
                    shd.m_pMdl = this;
                    (shd.*DrMdoShdSetShadow::s_pShwMaterial[4])(4, mat, 0, matIdx, list);
                }
                DrResMdoVertex* vtx = m_pWrkMatRes->m_pVertex;
                if (info->m_flags & 0x2000) {
                    vtx->render(info->m_renderIdx[1]);
                } else {
                    vtx->render(info->m_renderIdx[0]);
                }
            }
        }
    }
}

void DrMdoCtl::partsPosShadowRender(const MdsMdlTopHeader* top) {
    int num = top->m_infoNum;
    if (num <= 0) {
        return;
    }
    DrShdDataList* list = m_pDrMan->m_shdMan->m_dataList;
    DrAPCache* cache = m_pDrMan->m_apCache;
    const MdsMdlInfoHeader* info = reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs);
    for (int i = 0; i < num; i++, info++) {
        if (info->m_shadowFlags & 0x40) {
            const MdsMatInfoHeader* mat = m_pWrkMatRes->m_pMatInfo + info->m_matIdx;
            if (!(mat->m_shdFlags & 0x4) && !(info->m_flags & 0x20000)) {
                m_pWrkMatRes->m_pVertex->setVertexBind(info->m_vtxBindIdx);
                cache->setupCulling(static_cast<DrApCullType>((m_mdlFlags & 0x80) ? 2 : mat->m_cullType));
                int matIdx = info->m_matIdx;
                DrMdoShdSetShadow shd;
                shd.m_pMdl = this;
                (shd.*DrMdoShdSetShadow::s_pShwMaterial[3])(3, mat, 0, matIdx, list);
                DrResMdoVertex* vtx = m_pWrkMatRes->m_pVertex;
                if (info->m_flags & 0x2000) {
                    vtx->render(info->m_renderIdx[1]);
                } else {
                    vtx->render(info->m_renderIdx[0]);
                }
            }
        }
    }
}

void DrMdoCtl::partsPosNukiShadowRender(const MdsMdlTopHeader* top) {
    int num = top->m_infoNum;
    if (num <= 0) {
        return;
    }
    DrShdDataList* list = m_pDrMan->m_shdMan->m_dataList;
    DrAPCache* cache = m_pDrMan->m_apCache;
    const MdsMdlInfoHeader* info = reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs);
    for (int i = 0; i < num; i++, info++) {
        if (info->m_shadowFlags & 0x40) {
            const MdsMatInfoHeader* mat = m_pWrkMatRes->m_pMatInfo + info->m_matIdx;
            if ((mat->m_shdFlags & 0x4) && !(info->m_flags & 0x20000) && m_pWrkMatRes->m_ppTexture != nullptr &&
                mat->m_texEntryNum != 0) {
                m_pWrkMatRes->m_pVertex->setVertexBind(info->m_vtxBindIdx);
                cache->setupCulling(static_cast<DrApCullType>((m_mdlFlags & 0x80) ? 2 : mat->m_cullType));
                int shdIdx = (mat->m_shdFlags & 0x8) ? 5 : 4;
                int matIdx = info->m_matIdx;
                DrMdoShdSetShadow shd;
                shd.m_pMdl = this;
                (shd.*DrMdoShdSetShadow::s_pShwMaterial[shdIdx])(shdIdx, mat, 0, matIdx, list);
                DrResMdoVertex* vtx = m_pWrkMatRes->m_pVertex;
                if (info->m_flags & 0x2000) {
                    vtx->render(info->m_renderIdx[1]);
                } else {
                    vtx->render(info->m_renderIdx[0]);
                }
            }
        }
    }
}

void DrMdoCtlDammy::resourceInit() {}

void DrMdoCtlDammy::update() {}

void DrMdoCtlDammy::dispOffUpdate() {}

DrMdoCtlDammy::DrMdoCtlDammy(const void* data, DrMan* drMan, int viewNum) : DrMdlObj(viewNum) {
    m_pDrMan = drMan;
    m_pResData = data;
    m_mdlType = 6;
}

DrMdoCtlDammy::~DrMdoCtlDammy() {
    releaseMat();
}

void DrMdoCtlSeamAll::debugRender() {}

int DrMdoMat::getVanishEffectMax() const {
    if (m_pWrkMatRes == nullptr) {
        return 0;
    }
    const MdoMdlData* mdl = m_pWrkMatRes->m_pMdlData;
    if (mdl == nullptr) {
        return 0;
    }
    if ((mdl->m_flags & 0x2000) == 0) {
        return 0;
    }
    return mdl->m_vanishEffectMax > 1 ? mdl->m_vanishEffectMax : 1;
}

DrMdoSmlShadowObj* DrMdoSmlShadowMan::createObj(int viewNum, const unsigned char* data) {
    DrMdoSmlShadowObj* obj = new (m_pDrMan->m_resHandle, nullptr, 0, 4, false) DrMdoSmlShadowObj(viewNum, data, m_pDrMan);
    m_dblList[DrMan::s_nDblStockIdx].pushBack(obj);
    return obj;
}

MdoVanishEffectWrk* DrMdoMat::getVanishEffectWrk(unsigned int index, unsigned int bank) {
    if (m_pWrkMatRes == nullptr) {
        return nullptr;
    }
    if (m_pWrkMatRes->m_pMdlData == nullptr) {
        return nullptr;
    }
    if (m_pWrkMatRes->m_pVanishEffectWrk == nullptr) {
        return nullptr;
    }
    return &m_pWrkMatRes->m_pVanishEffectWrk[index * 3 + bank];
}

void DrMdoMat::setupMpfResource() {
    if (m_pWrkMatRes == nullptr) {
        return;
    }
    m_pWrkMatRes->m_pVertex = m_pDrMan->m_mdlMan->m_vertexMan->createVertexObj(m_pWrkMatRes->m_pVertexData);
    if (m_pWrkMatRes->m_texNum != 0) {
        DrMdoTextureMan* man = m_pDrMan->m_mdlMan->m_textureMan;
        const unsigned char* data = m_pWrkMatRes->m_pTexData;
        DrResMdoTexList* list;
        for (list = man->m_texList.m_pHead; list != nullptr; list = list->m_pNext) {
            if (list->m_res == data) {
                list->m_refCount++;
                goto found;
            }
        }
        list = new (man->m_pDrMan->m_resHandle, nullptr, 0, 4, false) DrResMdoTexList(data);
        if (list != nullptr) {
            man->m_texList.pushBack(list);
        }
    found:
        m_pWrkMatRes->m_pTexList = list;
        for (int i = 0; i < m_pWrkMatRes->m_pTexList->m_texNum; i++) {
            m_pWrkMatRes->m_ppTexture[i] = m_pWrkMatRes->m_pTexList->getTexObj(i);
        }
    }
}

void DrMdoCtlSeamBaseMap::releaseFreeSeamBase(DrResMdoSeamWrkBase* wrk) {
    DrResMdoSeamMemObj* memObj;
    if (wrk->m_matRes == nullptr) {
        memObj = nullptr;
    } else {
        memObj = wrk->m_memObj;
        unsigned int idx = wrk->m_dataIdx;
        m_pBaseBits[idx >> 5] &= ~(1 << (idx & 0x1F));
        idx = wrk->m_dataIdx;
        m_pBaseSubBits[idx >> 5] &= ~(1 << (idx & 0x1F));
        m_baseMemSize -= wrk->m_readSize;
        releaseBaseMapSeamMat(wrk->m_matRes);
        wrk->releaseCache(this);
        m_baseNum--;
    }
    DrResMdoSeamWrkBase* after = wrk->m_prev;
    DrResMdoSeamWrkBase* before = wrk->m_next;
    if (after == nullptr) {
        if (before != nullptr) {
            before->m_prev = nullptr;
        }
    } else {
        if (before != nullptr) {
            before->m_prev = after;
        }
        after->m_next = before;
    }
    if (m_basePool.m_usedTail == wrk) {
        m_basePool.m_usedTail = before;
    }
    if (m_basePool.m_list == wrk) {
        m_basePool.m_list = after;
        if (after != nullptr) {
            after->m_next = nullptr;
        }
    }
    if (m_basePool.m_freeTail == nullptr) {
        m_basePool.m_freeHead = wrk;
        m_basePool.m_freeTail = wrk;
        wrk->m_next = nullptr;
    } else {
        m_basePool.m_freeTail->m_prev = wrk;
        wrk->m_next = m_basePool.m_freeTail;
        m_basePool.m_freeTail = wrk;
    }
    wrk->m_prev = nullptr;
    m_basePool.m_freeNum++;
    m_basePool.m_usedNum--;
    if (memObj != nullptr) {
        wrk->m_memObj = nullptr;
        releaseFreeSeamMemObj(memObj);
    }
}

void DrMdoMat::releaseBaseMapSeamMat(MdoWrkMatRes* res) {
    if (res->m_pVertex != nullptr) {
        delete res->m_pVertex;
        res->m_pVertex = nullptr;
    }
    if (res->m_pTexList != nullptr) {
        delete res->m_pTexList;
        res->m_pTexList = nullptr;
    }
    res->m_ppTexture = nullptr;
    DrResMdoSampler* sampler = res->m_pSampler;
    if (sampler != nullptr) {
        m_pDrMan->m_mdlMan->m_samplerMan->m_samplerList.remove(sampler);
        delete sampler;
        res->m_pSampler = nullptr;
    }
    if (res->m_pDecShdObj != nullptr) {
        delete res->m_pDecShdObj;
        res->m_pDecShdObj = nullptr;
    }
    res->m_pDecShdData = nullptr;
    if (res->m_pMatUniformArray != nullptr) {
        res->m_pMatUniformArray->release();
        res->m_pMatUniformArray = nullptr;
    }
    if (res->m_pVolTexUniformArray != nullptr) {
        res->m_pVolTexUniformArray->release();
        res->m_pVolTexUniformArray = nullptr;
    }
    if (res->m_pRimBloomUniformArray != nullptr) {
        res->m_pRimBloomUniformArray->release();
        res->m_pRimBloomUniformArray = nullptr;
    }
    if (res->m_pExtUniform != nullptr && res->m_pExtUniform->m_pUniformArray != nullptr) {
        res->m_pExtUniform->m_pUniformArray->release();
        res->m_pExtUniform->m_pUniformArray = nullptr;
    }
}

void DrMdoCtlSeamBaseMap::readBaseMapCheck() {
    unsigned int flags = m_seamFlags;
    if (m_parmRead.m_posCnt == 0 && !(flags & 0x40)) {
        DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_CHECK =
            (flags & 0x80) ? SEAM_BASEMAP_READ_DEN_CHECK + 50.0f : m_pDrMan->m_seamBaseReadRange + 100.0f;
        DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_IN_CHECK = SEAM_BASEMAP_READ_IN_CHECK + 5.0f;
    } else {
        DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_CHECK =
            ((flags & 0x80) ? SEAM_BASEMAP_READ_DEN_CHECK : m_pDrMan->m_seamBaseReadRange) + 0.5f;
        DrResMdoSeamWrkBase::SEAM_BASEMAP_READ_IN_CHECK = SEAM_BASEMAP_READ_IN_CHECK + 0.5f;
    }
    DrResMdoSeamWrkBase::SEAM_BASEMAP_VERTEX_CHECK = m_pDrMan->m_seamBaseVertexCheck;
    DrResMdoSeamWrkBase::SEAM_BASEMAP_VERTEX_MIDDLE = m_pDrMan->m_seamBaseVertexMiddle;
    DrCalcViewWork* view = m_pDrMan->m_calcMan->m_pViewWork;
    bool readAll = (flags & 0x1000) || m_releaseVertexAll;
    for (DrResMdoSeamWrkBase* wrk = m_basePool.m_list; wrk != nullptr;) {
        bool release = wrk->update(view, &m_parmRead, readAll, m_seamFlags);
        if (wrk->m_cacheFlags & 0x80) {
            changeMemBaseMapParts(wrk);
        }
        DrResMdoSeamWrkBase* next = wrk->m_prev;
        if (release) {
            releaseFreeSeamBase(wrk);
        }
        wrk = next;
    }
    if (m_seamFlags & 0x80200) {
        return;
    }
    bool found = false;
    if (m_baseNum >= 5 || (m_seamFlags & 0x1000)) {
        return;
    }
    if (!readBaseModelCheck(found, m_parmRead.m_readPos, true)) {
        return;
    }
    for (int i = 0; i < m_parmRead.m_posCnt; i++) {
        if (!readBaseModelCheck(found, m_parmRead.m_pos[i], false)) {
            return;
        }
    }
}

float DrMdoCtlSeamBaseMap::SEAM_BASEMAP_READ_DEN_CHECK = 100.0f;
float DrMdoCtlSeamBaseMap::SEAM_BASEMAP_READ_IN_CHECK = 5.0f;

void DrMdoCtlSeamEnvMap::releaseFreeSeamEnvMap(DrResMdoSeamWrkEnv* wrk) {
    DrResMdoSeamMemObj* memObj = wrk->m_memObj;
    if (wrk->m_matRes != nullptr) {
        unsigned int idx = wrk->m_dataIdx;
        m_pEnvBits[idx >> 5] &= ~(1 << (idx & 0x1F));
        m_envMemSize += wrk->m_dispNum;
        releaseBaseMapSeamMat(wrk->m_matRes);
        wrk->release();
        m_envNum--;
    }
    DrResMdoSeamWrkEnv* after = wrk->m_prev;
    DrResMdoSeamWrkEnv* before = wrk->m_next;
    if (after == nullptr) {
        if (before != nullptr) {
            before->m_prev = nullptr;
        }
    } else {
        if (before != nullptr) {
            before->m_prev = after;
        }
        after->m_next = before;
    }
    if (m_envPool.m_usedTail == wrk) {
        m_envPool.m_usedTail = before;
    }
    if (m_envPool.m_list == wrk) {
        m_envPool.m_list = after;
        if (after != nullptr) {
            after->m_next = nullptr;
        }
    }
    if (m_envPool.m_freeTail == nullptr) {
        m_envPool.m_freeHead = wrk;
        m_envPool.m_freeTail = wrk;
        wrk->m_next = nullptr;
    } else {
        m_envPool.m_freeTail->m_prev = wrk;
        wrk->m_next = m_envPool.m_freeTail;
        m_envPool.m_freeTail = wrk;
    }
    wrk->m_prev = nullptr;
    m_envPool.m_freeNum++;
    m_envPool.m_usedNum--;
    if (memObj != nullptr) {
        wrk->m_memObj = nullptr;
        m_memMan.releaseFreeObj(memObj);
    }
}

void DrMdoCtlSeamEnvMap::readEnvMapCheck() {
    DrCalcViewWork* view = m_pDrMan->m_calcMan->m_pViewWork;
    bool readAll = (m_seamFlags & 0x1000) || m_releaseVertexAll;
    DrResMdoSeamWrkEnv* wrk = m_envPool.m_list;
    while (wrk != nullptr) {
        bool release = wrk->update(view->m_viewPos, readAll);
        if (!release) {
            if (wrk->m_flags & DrResMdoSeamWrkEnv::FLAG_READ) {
                MdoWrkMatRes* matRes = wrk->m_matRes;
                const MdsSeamEnvMapHead* head = reinterpret_cast<const MdsSeamEnvMapHead*>(wrk->m_memObj->m_pData);
                const unsigned char* data = reinterpret_cast<const unsigned char*>(head);
                resetBaseMapMaterial(matRes, data + head->m_dataOfs[1], data + head->m_dataOfs[0],
                                     data + head->m_dataOfs[3], data + head->m_dataOfs[6], data + head->m_dataOfs[4],
                                     0);
                if (head->m_dataOfs[2] != 0) {
                    const unsigned char* blockData = data + head->m_dataOfs[2];
                    const MdsSeamInstMatBlock* block = reinterpret_cast<const MdsSeamInstMatBlock*>(blockData);
                    matRes->m_pSeamMatBlock = blockData;
                    matRes->m_pFixAnmInf = reinterpret_cast<const MdsFixAnmInf*>(blockData + block->m_ofs0);
                    matRes->m_pFixAnmKey = reinterpret_cast<const MdsFixAnmKey*>(blockData + block->m_ofs1);
                    matRes->m_pSeamMatData = blockData + block->m_ofs2;
                }
                wrk->changeMemCall(head);
            }
        }
        DrResMdoSeamWrkEnv* next = wrk->m_prev;
        if (release) {
            releaseFreeSeamEnvMap(wrk);
        }
        wrk = next;
    }
    if (m_seamFlags & 0x81200) {
        return;
    }
    if (m_envNum > 0) {
        return;
    }
    int num = m_pMapHead->m_envMdlNum;
    for (int i = 0; i < num; i++) {
        unsigned int idx = i;
        if (!(m_pEnvBits[idx >> 5] & (1 << (idx & 0x1F)))) {
            m_parmRead.setStockEnvMdl(i + 1);
            return;
        }
    }
}

void DrMdoCtlSeamMpfMap::releaseFreeSeamMpf(DrResMdoSeamWrkMpf* wrk) {
    DrResMdoSeamMemObj* memObj = wrk->m_memObj;
    if (wrk->m_matRes != nullptr) {
        unsigned int idx = wrk->m_dataIdx;
        m_pMpfBits[idx >> 5] &= ~(1 << (idx & 0x1F));
        m_mpfMemSize -= wrk->m_readSize;
        releaseMpfMapSeamMat(wrk->m_matRes);
        wrk->releaseCache(this);
        m_mpfNum--;
    }
    DrResMdoSeamWrkMpf* after = wrk->m_prev;
    DrResMdoSeamWrkMpf* before = wrk->m_next;
    if (after == nullptr) {
        if (before != nullptr) {
            before->m_prev = nullptr;
        }
    } else {
        if (before != nullptr) {
            before->m_prev = after;
        }
        after->m_next = before;
    }
    if (m_mpfPool.m_usedTail == wrk) {
        m_mpfPool.m_usedTail = before;
    }
    if (m_mpfPool.m_list == wrk) {
        m_mpfPool.m_list = after;
        if (after != nullptr) {
            after->m_next = nullptr;
        }
    }
    if (m_mpfPool.m_freeTail == nullptr) {
        m_mpfPool.m_freeHead = wrk;
        m_mpfPool.m_freeTail = wrk;
        wrk->m_next = nullptr;
    } else {
        m_mpfPool.m_freeTail->m_prev = wrk;
        wrk->m_next = m_mpfPool.m_freeTail;
        m_mpfPool.m_freeTail = wrk;
    }
    wrk->m_prev = nullptr;
    m_mpfPool.m_freeNum++;
    m_mpfPool.m_usedNum--;
    if (memObj != nullptr) {
        wrk->m_memObj = nullptr;
        m_memMan.releaseFreeObj(memObj);
    }
}

void DrMdoCtlSeamMpfMap::readMpfMapCheck() {
    if (m_parmRead.m_posCnt == 0) {
        DrResMdoSeamWrkMpf::SEAM_MPFMAP_READ_CHECK = !(m_seamFlags & 0x40) ? 60.0f : 40.5f;
    } else {
        DrResMdoSeamWrkMpf::SEAM_MPFMAP_READ_CHECK = 40.5f;
    }
    bool readAll = (m_seamFlags & 0x1000) || m_releaseVertexAll;
    for (DrResMdoSeamWrkMpf* wrk = m_mpfPool.m_list; wrk != nullptr;) {
        bool release = wrk->update(&m_parmRead, readAll, m_seamFlags);
        if (wrk->m_cacheFlags & 0x10) {
            const MdsSeamMpfMapHead* head = reinterpret_cast<const MdsSeamMpfMapHead*>(wrk->m_memObj->m_pData);
            const unsigned char* data = reinterpret_cast<const unsigned char*>(head);
            const unsigned char* mat = data + head->m_dataOfs[1];
            const unsigned char* vtx = data + head->m_dataOfs[3];
            const unsigned char* mdl = data + head->m_dataOfs[0];
            const unsigned char* tex = data + head->m_dataOfs[4];
            MdoWrkMatRes* res = wrk->m_matRes;
            res->m_pMatData = mat;
            res->m_pTexData = tex;
            res->m_pVertexData = vtx;
            res->m_pMatInfo = reinterpret_cast<const MdsMatInfoHeader*>(
                mat + reinterpret_cast<const MdsMatDataHeader*>(mat)->m_matInfoOfs);
            if (res->m_texNum != 0) {
                res->m_pTexList->changeMemTexList(tex);
            }
            const MdoMdlData* mdlData = reinterpret_cast<const MdoMdlData*>(mdl);
            res->m_pMdlInfo = mdl;
            res->m_pMdlData = mdlData;
            res->m_mdlTopNum = mdlData->m_mdlTopNum;
            res->m_pMdlTop = reinterpret_cast<const MdsMdlTopHeader*>(mdl + mdlData->m_mdlTopOfs);
            if (mdlData->m_subDataNum != 0) {
                res->m_pMdlSubData = mdl + mdlData->m_subDataOfs;
            }
            if (res->m_pVertexData != nullptr && res->m_pVertex != nullptr) {
                res->m_pVertex->changeMemVertex(res->m_pVertexData);
            }
        }
        DrResMdoSeamWrkMpf* next = wrk->m_prev;
        if (release) {
            releaseFreeSeamMpf(wrk);
        }
        wrk = next;
    }
    if (m_seamFlags & 0x81200) {
        return;
    }
    if (m_mpfNum < 3) {
        readMpfModelCheck(m_parmRead.m_readPos);
    }
}

bool DrMdoCtlSeamMpfMap::readMpfModelCheck(const mm::Vec3& pos) {
    const MapHead* head = m_pMapHead;
    int num = head->m_mpfMdlNum;
    bool ret = true;
    const unsigned int* offBits = m_pDrMan->m_dispOffBits;
    const DrResMdoSeamWrkMpf::MapEntry* entry = reinterpret_cast<const DrResMdoSeamWrkMpf::MapEntry*>(
        reinterpret_cast<const unsigned char*>(head) + head->m_mpfMdlTblOfs);
    for (int i = 0; i < num; i++, entry++) {
        unsigned int idx = i;
        if (m_pMpfBits[idx >> 5] & (1 << (idx & 0x1F))) {
            continue;
        }
        unsigned int bit = entry->m_bitIdx;
        if (bit != 0 && (offBits[bit >> 5] & (1 << (bit & 0x1F)))) {
            continue;
        }
        if ((m_seamFlags & 0x100) && !(entry->m_flags & 1)) {
            continue;
        }
        if (entry->m_max[0] + 40.0f < pos.x || entry->m_min[0] - 40.0f > pos.x || entry->m_max[1] + 40.0f < pos.y ||
            entry->m_min[1] - 40.0f > pos.y || entry->m_max[2] + 40.0f < pos.z || entry->m_min[2] - 40.0f > pos.z) {
            continue;
        }
        m_parmRead.setStockMpfMdl(i);
        ret = false;
    }
    return ret;
}

void DrMdoCtlSeamMpfMap::createMpfMapDisplayList() {
    if (m_pDrMan->m_seamMpfRenderOff) {
        return;
    }
    DrResMdoSeamWrkMpf* wrk = m_mpfPool.m_list;
    grlib::CGLibVtxInstans* inst = m_pDrMan->m_mdlMan->m_vertexMan->m_instans;
    DrAPCache* cache = m_pDrMan->m_apCache;
    cache->setupCulling(static_cast<DrApCullType>(2));
    m_pDrMan->m_pixlMan->selectGBuffRenderTarget(0x1F);
    cache->setupDepthStencil(0x18, 1, 0, 3);
    cache->setupAlphaBlend(0);
    for (; wrk != nullptr; wrk = wrk->m_prev) {
        m_pWrkMatRes = wrk->m_matRes;
        if (m_pWrkMatRes == nullptr || wrk->m_dispOn == 0) {
            continue;
        }
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        int num = wrk->m_objNum;
        DrMdoCtlMpfWork* work = wrk->m_mpfWork;
        for (int i = 0; i < num; i++) {
            if (work->getObjChk(i) == 0) {
                continue;
            }
            const MdsMdlTopHeader* top = &m_pWrkMatRes->m_pMdlTop[i];
            int infoNum = top->m_infoNum;
            const MdsMdlInfoHeader* info =
                reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs);
            for (int j = 0; j < infoNum; j++, info++) {
                mpfDrawRender(i, info, work, inst);
            }
        }
    }
    cache->setupAlphaBlend(0);
}

void DrMdoMat::releaseMpfMapSeamMat(MdoWrkMatRes* res) {
    if (res->m_pVertex != nullptr) {
        delete res->m_pVertex;
        res->m_pVertex = nullptr;
    }
    if (res->m_pMpfSampler != nullptr) {
        for (unsigned int i = 0; i < res->m_matNum; i++) {
            res->m_pMpfSampler[i].~DrResMpfSampler();
        }
        res->m_pMpfSampler = nullptr;
    }
    DrResMdoSampler* sampler = res->m_pSampler;
    if (sampler != nullptr) {
        m_pDrMan->m_mdlMan->m_samplerMan->m_samplerList.remove(sampler);
        delete sampler;
        res->m_pSampler = nullptr;
    }
    if (res->m_pTexList != nullptr) {
        delete res->m_pTexList;
        res->m_pTexList = nullptr;
    }
    if (res->m_pMatUniformArray != nullptr) {
        res->m_pMatUniformArray->release();
        res->m_pMatUniformArray = nullptr;
    }
    res->m_ppTexture = nullptr;
}

void DrMdoAnim::updateAnimEnd(float rate, const unsigned int* dispBits, DrResEtcPamObj* pamObj) {
    const unsigned char* blockData = m_pWrkMatRes->m_pSeamMatBlock;
    if (blockData == nullptr) {
        return;
    }
    const MdsSeamInstMatBlock* block = reinterpret_cast<const MdsSeamInstMatBlock*>(blockData);
    const MdsFixAnmRange* ranges = reinterpret_cast<const MdsFixAnmRange*>(blockData + block->m_rangeOfs);
    const MdsFixAnmCate* cates = reinterpret_cast<const MdsFixAnmCate*>(blockData + block->m_cateOfs);
    const MdsMatInfoHeader* info = m_pWrkMatRes->m_pMatInfo;
    for (int i = 0; i < m_pWrkMatRes->m_matNum; i++, info++) {
        if ((dispBits[i >> 5] & (1 << (i & 0x1F))) && (info->m_shdFlags & 0x50000)) {
            float* work = m_pWrkMatRes->m_pUniformVal + info->m_uniformOfs;
            if (info->m_shdFlags & 0x10000) {
                const MdsFixAnmRange& range = ranges[info->m_fixAnmRange[0]];
                int num = range.m_cateNum;
                const MdsFixAnmCate* cate = cates + range.m_cateIdx;
                for (int j = 0; j < num; j++, cate++) {
                    float* val = work + cate->m_valOfs;
                    memcpy(val, m_pWrkMatRes->m_pMatVal + (info->m_uniformOfs + cate->m_valOfs), 0x20);
                    calcAnim(cate, &m_pWrkMatRes->m_pResMat[i], pamObj, val, rate);
                }
            }
            if (info->m_shdFlags & 0x40000) {
                const MdsFixAnmRange& range = ranges[info->m_fixAnmRange[2]];
                int num = range.m_cateNum;
                const MdsFixAnmCate* cate = cates + range.m_cateIdx;
                for (int j = 0; j < num; j++, cate++) {
                    calcAnim(cate, &m_pWrkMatRes->m_pResMat[i], pamObj, work, rate);
                }
            }
        }
    }
}

void DrMdoMat::updateMatCallBack(const unsigned int* dispBits) {
    const MdsMatCallBackTbl* tbl = m_pWrkMatRes->m_pCallBackTbl;
    if (tbl == nullptr || tbl->m_matListNum == 0) {
        return;
    }
    int num = tbl->m_matListNum;
    const unsigned char* calls = m_pWrkMatRes->m_pMatData + tbl->m_callOfs;
    const unsigned short* list = reinterpret_cast<const unsigned short*>(m_pWrkMatRes->m_pMatData + tbl->m_matListOfs);
    for (int i = 0; i < num; i++) {
        unsigned short mat = list[i];
        if (dispBits[mat >> 5] & (1 << (mat & 0x1F))) {
            const MdsMatInfoHeader* info = &m_pWrkMatRes->m_pMatInfo[mat];
            const unsigned short* call = reinterpret_cast<const unsigned short*>(calls + info->m_callBackIdx * 4);
            int cnt = info->m_callBackNum;
            for (int j = 0; j < cnt; j++) {
                (this->*s_pCallMatVal[call[0]])(info, call[1], list[i]);
                call += 2;
            }
        }
    }
}

void DrMdoMat::matCall_MatxView(const MdsMatInfoHeader* info, int slot, int matIdx) {
    mm::Mat44* dst = reinterpret_cast<mm::Mat44*>(&m_pWrkMatRes->m_pUniformVal[info->m_uniformOfs + slot]);
    const mm::Mat44* src = reinterpret_cast<const mm::Mat44*>(&m_pWrkMatRes->m_pMatVal[info->m_uniformOfs + slot]);
    dst->mulSafe(m_pDrMan->m_calcMan->m_pViewWork->m_invView, *src);
}

void DrMdoMat::matCall_OutLineVal(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    DrPixlPostParm* parm = m_pDrMan->m_postParm[m_pDrMan->m_postParmIdx];
    float far = parm->m_outLineFar;
    float near = parm->m_outLineNear;
    far = far > near ? far : near;
    float range = far - near;
    range = range > 0.01f ? range : 0.01f;
    float t = mm::clamp((m_outLineDist - near) / range, 0.0f, 1.0f);
    *dst = parm->m_outLineScale * t;
}

void DrMdoMat::matCall_WaterFog(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* uni = m_pWrkMatRes->m_pUniformVal;
    float* mat = m_pWrkMatRes->m_pMatVal;
    unsigned int idx = info->m_uniformOfs + slot;
    float* dst = &uni[idx];
    float* src = &mat[idx];
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    float fog = m_pDrMan->m_pixlMan->m_objTbl->m_postMan->m_waterFog - 0.05f;
    fog = fog > 0.0f ? fog : 0.0f;
    dst[9] = mm::clamp(fog / 0.95f, 0.0f, 1.0f);
}

void DrMdoMat::matCall_EmissiveTime(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* uni = m_pWrkMatRes->m_pUniformVal;
    float* mat = m_pWrkMatRes->m_pMatVal;
    unsigned int idx = info->m_uniformOfs + slot;
    unsigned int time = info->m_timeSlot + info->m_uniformOfs;
    uni[idx] = mat[idx] * uni[time];
}

void DrMdoMat::matCall_RgbTime(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* uni = m_pWrkMatRes->m_pUniformVal;
    float* mat = m_pWrkMatRes->m_pMatVal;
    unsigned int idx = info->m_uniformOfs + slot;
    float* dst = &uni[idx];
    float* src = &mat[idx];
    unsigned int time = info->m_timeSlot + info->m_uniformOfs;
    dst[0] = src[0] * uni[time];
    dst[1] = src[1] * uni[time];
    dst[2] = src[2] * uni[time];
}

void DrMdoMat::matCall_RTime(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* uni = m_pWrkMatRes->m_pUniformVal;
    float* mat = m_pWrkMatRes->m_pMatVal;
    unsigned int idx = info->m_uniformOfs + slot;
    unsigned int time = info->m_timeSlot + info->m_uniformOfs;
    uni[idx] = mat[idx] * uni[time];
}

void DrMdoMat::matCall_AccRgb1(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[0].r;
    dst[1] = m_pWrkMatRes->m_pAce->m_color[0].g;
    dst[2] = m_pWrkMatRes->m_pAce->m_color[0].b;
}

void DrMdoMat::matCall_AccRgb2(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[1].r;
    dst[1] = m_pWrkMatRes->m_pAce->m_color[1].g;
    dst[2] = m_pWrkMatRes->m_pAce->m_color[1].b;
}

void DrMdoMat::matCall_AccRgb3(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[2].r;
    dst[1] = m_pWrkMatRes->m_pAce->m_color[2].g;
    dst[2] = m_pWrkMatRes->m_pAce->m_color[2].b;
}

void DrMdoMat::matCall_AccRgb4(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[3].r;
    dst[1] = m_pWrkMatRes->m_pAce->m_color[3].g;
    dst[2] = m_pWrkMatRes->m_pAce->m_color[3].b;
}

void DrMdoMat::matCall_AccMulRgb1(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[0].r * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_color[0].g * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_color[0].b * dst[2];
}

void DrMdoMat::matCall_AccMulRgb2(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[1].r * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_color[1].g * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_color[1].b * dst[2];
}

void DrMdoMat::matCall_AccMulRgb3(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[2].r * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_color[2].g * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_color[2].b * dst[2];
}

void DrMdoMat::matCall_AccMulRgb4(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_color[3].r * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_color[3].g * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_color[3].b * dst[2];
}

void DrMdoMat::matCall_AccVal1(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[0];
}

void DrMdoMat::matCall_AccVal2(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[1];
}

void DrMdoMat::matCall_AccVal3(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[2];
}

void DrMdoMat::matCall_AccVal4(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[3];
}

void DrMdoMat::matCall_AccMulVal1(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[0] * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_val[0] * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_val[0] * dst[2];
}

void DrMdoMat::matCall_AccMulVal2(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[1] * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_val[1] * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_val[1] * dst[2];
}

void DrMdoMat::matCall_AccMulVal3(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[2] * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_val[2] * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_val[2] * dst[2];
}

void DrMdoMat::matCall_AccMulVal4(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = m_pWrkMatRes->m_pAce->m_val[3] * dst[0];
    dst[1] = m_pWrkMatRes->m_pAce->m_val[3] * dst[1];
    dst[2] = m_pWrkMatRes->m_pAce->m_val[3] * dst[2];
}

void DrMdoMat::matCall_CalcBloom(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    float* src = m_pWrkMatRes->m_pMatVal;
    unsigned int idx = info->m_uniformOfs + slot;
    dst[idx] = src[idx] * m_colorScale;
}

void DrMdoMat::matCall_CalcColor(const MdsMatInfoHeader* info, int slot, int matIdx) {
    m_pWrkMatRes->m_pResMat[matIdx].setColor(info->m_color[0] * m_colorScale, m_colorScale * info->m_color[1],
                                             m_colorScale * info->m_color[2], info->m_color[3]);
}

void DrMdoMat::matCall_ToonId(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    dst[0] = dst[1] / 255.0f;
}

void DrMdoMat::matCall_VolumeTest(const MdsMatInfoHeader* info, int slot, int matIdx) {

}

void DrMdoMat::matCall_BaseColor(const MdsMatInfoHeader* info, int slot, int matIdx) {
    DrResMdoMat* mat = &m_pWrkMatRes->m_pResMat[matIdx];
    mat->m_color.r = m_pWrkMatRes->m_pAce->m_color[slot].r;
    mat->m_color.g = m_pWrkMatRes->m_pAce->m_color[slot].g;
    mat->m_color.b = m_pWrkMatRes->m_pAce->m_color[slot].b;
}

void DrMdoMat::matCall_BaseVal(const MdsMatInfoHeader* info, int slot, int matIdx) {
    DrResMdoMat* mat = &m_pWrkMatRes->m_pResMat[matIdx];
    mat->m_color.r = m_pWrkMatRes->m_pAce->m_val[slot];
    mat->m_color.g = m_pWrkMatRes->m_pAce->m_val[slot];
    mat->m_color.b = m_pWrkMatRes->m_pAce->m_val[slot];
}

void DrMdoMat::matCall_TransVal(const MdsMatInfoHeader* info, int slot, int matIdx) {
    m_pWrkMatRes->m_pResMat[matIdx].setAlpha(m_pWrkMatRes->m_pAce->m_val[slot]);
}

// Fades with the model's up axis: the matrix's Y axis, normalised; 1 when it lies flat, 0 when it points up or down.
void DrMdoMat::matCall_CalcPrjAlpha(const MdsMatInfoHeader* info, int slot, int matIdx) {
    float* dst = m_pWrkMatRes->m_pUniformVal;
    dst += info->m_uniformOfs + slot;
    const mm::Mat44& mtx = m_matrix;
    mm::Vec3 up(mtx.m[0][0] * 0.0f + mtx.m[1][0] + mtx.m[2][0] * 0.0f,
                mtx.m[0][1] * 0.0f + mtx.m[1][1] + mtx.m[2][1] * 0.0f,
                mtx.m[0][2] * 0.0f + mtx.m[1][2] + mtx.m[2][2] * 0.0f);
    float length = up.length();
    if (length <= 1e-6f) {
        up = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        up.y = up.y * scale;
    }
    float alpha = (1.0f - ::fabsf(up.y)) * 6.0f;
    if (alpha > 1.0f) {
        alpha = 1.0f;
    }
    if (alpha < 0.0f) {
        alpha = 0.0f;
    }
    *dst = alpha;
}

void (DrMdoMat::*DrMdoMat::s_pCallMatVal[35])(const MdsMatInfoHeader*, int, int) = {
    &DrMdoMat::matCall_MatxView,
    &DrMdoMat::matCall_EmissiveTime,
    &DrMdoMat::matCall_RgbTime,
    &DrMdoMat::matCall_RTime,
    &DrMdoMat::matCall_AccRgb1,
    &DrMdoMat::matCall_AccRgb2,
    &DrMdoMat::matCall_AccRgb3,
    &DrMdoMat::matCall_AccRgb4,
    &DrMdoMat::matCall_AccMulRgb1,
    &DrMdoMat::matCall_AccMulRgb2,
    &DrMdoMat::matCall_AccMulRgb3,
    &DrMdoMat::matCall_AccMulRgb4,
    &DrMdoMat::matCall_AccVal1,
    &DrMdoMat::matCall_AccVal2,
    &DrMdoMat::matCall_AccVal3,
    &DrMdoMat::matCall_AccVal4,
    &DrMdoMat::matCall_AccMulVal1,
    &DrMdoMat::matCall_AccMulVal2,
    &DrMdoMat::matCall_AccMulVal3,
    &DrMdoMat::matCall_AccMulVal4,
    &DrMdoMat::matCall_WaterFog,
    &DrMdoMat::matCall_MatxInvView,
    &DrMdoMat::matCall_FurShader,
    &DrMdoMat::matCall_CalcBloom,
    &DrMdoMat::matCall_CalcColor,
    &DrMdoMat::matCall_OutLineVal,
    &DrMdoMat::matCall_ToonId,
    &DrMdoMat::matCall_VolumeTest,
    &DrMdoMat::matCall_BaseColor,
    &DrMdoMat::matCall_BaseVal,
    &DrMdoMat::matCall_TransVal,
    &DrMdoMat::matCall_CalcPrjView,
    &DrMdoMat::matCall_CalcPrjChgView,
    &DrMdoMat::matCall_CalcPrjDefCall,
    &DrMdoMat::matCall_CalcPrjAlpha,
};

void DrMdoAnim::animcall_UV_Scr_U(DrResMdoMat* mat, float* work, float value) {
    work[0] = value;
}

void DrMdoAnim::animcall_UV_Scr_V(DrResMdoMat* mat, float* work, float value) {
    work[5] = value;
}

void DrMdoAnim::animcall_UV_Trans_U(DrResMdoMat* mat, float* work, float value) {
    work[3] = value;
}

void DrMdoAnim::animcall_UV_Trans_V(DrResMdoMat* mat, float* work, float value) {
    work[7] = value;
}

void DrMdoAnim::animcall_UV_Rot(DrResMdoMat*, float* work, float value) {
    float rad = value * 0.0174532924f;
    float scaleU = work[0];
    float scaleV = work[5];
    float s = sinf(rad);
    float c = cosf(rad);
    work[0] = scaleU * c;
    work[1] = scaleV * s;
    work[4] = -(scaleU * s);
    work[5] = scaleV * c;
    work[3] += c * -0.5f - s * 0.5f + 0.5f;
    work[7] += s * 0.5f + c * -0.5f + 0.5f;
}

void DrMdoAnim::animcall_WorkFloat1(DrResMdoMat* mat, float* work, float value) {
    work[0] = value;
}

void DrMdoAnim::animcall_MatAlpha(DrResMdoMat* mat, float* work, float value) {
    mat->setAlpha(value);
}

void DrMdoAnim::animcall_MatColorR(DrResMdoMat* mat, float* work, float value) {
    mat->m_color.r = value;
}

void DrMdoAnim::animcall_MatColorG(DrResMdoMat* mat, float* work, float value) {
    mat->m_color.g = value;
}

void DrMdoAnim::animcall_MatColorB(DrResMdoMat* mat, float* work, float value) {
    mat->m_color.b = value;
}

void DrMdoAnim::anmNodeParm_TranX(mm::Vec3* srt, float value) {
    srt[0].x = value;
}

void DrMdoAnim::anmNodeParm_TranY(mm::Vec3* srt, float value) {
    srt[0].y = value;
}

void DrMdoAnim::anmNodeParm_TranZ(mm::Vec3* srt, float value) {
    srt[0].z = value;
}

void DrMdoAnim::anmNodeParm_RotX(mm::Vec3* srt, float value) {
    srt[1].x = value;
}

void DrMdoAnim::anmNodeParm_RotY(mm::Vec3* srt, float value) {
    srt[1].y = value;
}

void DrMdoAnim::anmNodeParm_RotZ(mm::Vec3* srt, float value) {
    srt[1].z = value;
}

void DrMdoAnim::anmNodeParm_SclX(mm::Vec3* srt, float value) {
    srt[2].x = value;
}

void DrMdoAnim::anmNodeParm_SclY(mm::Vec3* srt, float value) {
    srt[2].y = value;
}

void DrMdoAnim::anmNodeParm_SclZ(mm::Vec3* srt, float value) {
    srt[2].z = value;
}

void DrMdoNomAfterImage::captureObj(const DrMdoCtlNom* nom) {
    wrkObjList* wrk = &m_list[m_cur];
    DrMdlObj* mdl = wrk->m_mdl;
    cloneMdlObj(static_cast<DrMdoCtlNom*>(mdl), nom);
    wrk->m_time = 0.0f;
    wrk->m_pos = mdl->m_matrix.getTrans();
    mdl->setDisp(false);
    m_cur++;
    if (m_num <= m_cur) {
        m_cur = 0;
    }
    if (mdl->getRimBloomWrk(2) != nullptr) {
        MdoRimBloomWrk* rim = mdl->getRimBloomWrk(2);
        rim->m_color = m_rimColorStart;
        rim->m_emissive = m_rimEmissiveStart;
        rim->m_power = m_rimPowerStart;
        rim->m_blackRatio = m_rimBlackRatioStart;
    }
}

DrMdoMpfMan::~DrMdoMpfMan() {
    m_windBlock.release();
    m_ambBlock.release();
    pad_98.release();
    if (m_pWorkBuff != nullptr) {
        mtl::MemManager::deallocate(m_pWorkBuff, 0, false);
        m_pWorkBuff = nullptr;
    }
}

void DrMdoMpfMan::begin() {
    m_windScale = 1.0f;
    m_frameWorkUsed = 0;
    m_listCount = 0;
}

void DrMdoMpfMan::update() {
    m_updateFlags |= 1;
    if (!(m_updateFlags & 2)) {
        return;
    }
    m_updateFlags &= ~2;
    DrMan* drMan = m_pDrMan;
    if (!drMan->m_mpfWindStop) {
        float power = m_windScale * 0.4f * drMan->m_mpfWindPower;
        if (power != 0.0f) {
            for (int i = 0; i < 64; i++) {
                m_windCalc[i].calcUpdate(1.0f, power, 1.0f);
            }
        }
    }
    updateUniformWork();
}

void DrMdoMpfMan::updateUniformWork() {
    float* buff = reinterpret_cast<float*>(m_windBlock.getBuff());
    for (int i = 0; i < 64; i++) {
        const mm::Mat44* mat = m_windCalc[i].m_windMat;
        grlib::ShdMat44TransposeMat34(buff, mat[0]);
        grlib::ShdMat44TransposeMat34(buff + 12, mat[1]);
        buff += 24;
    }
    m_windBlock.updateData();
    const mm::Col3& amb = m_pDrMan->m_lightMan->m_ambColor;
    float r = amb.r;
    float g = amb.g;
    float b = amb.b;
    r *= 0.5f;
    g *= 0.5f;
    b *= 0.5f;
    float* ambBuff = reinterpret_cast<float*>(m_ambBlock.getBuff());
    ambBuff[0] = r;
    ambBuff[1] = g;
    ambBuff[2] = b;
    ambBuff[3] = 0.0f;
    m_ambBlock.updateData();
}

void DrMdoMpfMan::addMpfObj() {
    m_mpfObjNum++;
}

bool DrMdoMpfMan::delMpfObj() {
    return --m_mpfObjNum < 1;
}

const char* DrMdoNode::getNodeName(int index) const {
    const unsigned char* mdl = reinterpret_cast<const unsigned char*>(m_pWrkMatRes->m_pMdlData);
    const MdsNodeTable* tbl = reinterpret_cast<const MdsNodeTable*>(mdl + m_pWrkMatRes->m_pMdlData->m_nodeTblOfs);
    const MdsNodeEntry* entries =
        reinterpret_cast<const MdsNodeEntry*>(reinterpret_cast<const char*>(tbl) + tbl->m_entryOfs);
    return reinterpret_cast<const char*>(tbl) + entries[index].m_nameOfs;
}

int DrMdoNode::getNodeIdx(const char* name) const {
    long num = m_nodeMax;
    if (num != 0) {
        const unsigned char* mdl = reinterpret_cast<const unsigned char*>(m_pWrkMatRes->m_pMdlData);
        const MdsNodeTable* tbl = reinterpret_cast<const MdsNodeTable*>(mdl + m_pWrkMatRes->m_pMdlData->m_nodeTblOfs);
        const MdsNodeEntry* entries =
            reinterpret_cast<const MdsNodeEntry*>(reinterpret_cast<const char*>(tbl) + tbl->m_entryOfs);
        for (long i = 0; i < m_nodeMax; i++) {
            if (strcmp(name, reinterpret_cast<const char*>(tbl) + entries[i].m_nameOfs) == 0) {
                return i;
            }
        }
    }
    return -1;
}

void DrMdoNode::setNodeMatrix(int index, const mm::Mat44& mat) {
    if (m_nodeMax != 0) {
        m_pNodeMats[DrMan::s_nDblStockIdx][index] = mat;
    }
}

const mm::Mat44& DrMdoNode::getNodeMatrix(int index) const {
    return m_pNodeMats[DrMan::s_nDblStockIdx][index];
}

mm::Mat44* DrMdoNode::getNodeMatrixPtr(int index) {
    return &m_pNodeMats[DrMan::s_nDblStockIdx][index];
}

void (*DrMdoAnim::s_pCallAnim[10])(DrResMdoMat*, float*, float) = {
    &DrMdoAnim::animcall_UV_Scr_U,
    &DrMdoAnim::animcall_UV_Scr_V,
    &DrMdoAnim::animcall_UV_Trans_U,
    &DrMdoAnim::animcall_UV_Trans_V,
    &DrMdoAnim::animcall_UV_Rot,
    &DrMdoAnim::animcall_WorkFloat1,
    &DrMdoAnim::animcall_MatAlpha,
    &DrMdoAnim::animcall_MatColorR,
    &DrMdoAnim::animcall_MatColorG,
    &DrMdoAnim::animcall_MatColorB,
};

void (*DrMdoAnim::s_pCallAnmNode[9])(mm::Vec3*, float) = {
    &DrMdoAnim::anmNodeParm_TranX,
    &DrMdoAnim::anmNodeParm_TranY,
    &DrMdoAnim::anmNodeParm_TranZ,
    &DrMdoAnim::anmNodeParm_RotX,
    &DrMdoAnim::anmNodeParm_RotY,
    &DrMdoAnim::anmNodeParm_RotZ,
    &DrMdoAnim::anmNodeParm_SclX,
    &DrMdoAnim::anmNodeParm_SclY,
    &DrMdoAnim::anmNodeParm_SclZ,
};

void DrMdoSetup::varStTex_ColorTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(0)->m_pTexture, location);
}

void DrMdoSetup::varStTex_NormalTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(2)->m_pTexture, location);
}

void DrMdoSetup::varStTex_LightTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(4);
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(15)->m_pTexture, location);
}

void DrMdoSetup::varStTex_DepthTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(4)->m_pTexture, location);
}

void DrMdoSetup::varStTex_RefTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
}

void DrMdoSetup::varStTex_ShadowMap(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibTextureBuffer* tex = m_pDrMan->m_pixlMan->m_objTbl->m_deferred->getShadowMapTexture();
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(*tex, location);
}

void DrMdoSetup::varStTex_AvatarFaceMap1(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    m_pDrMan->m_pixlMan->m_objTbl->m_deferred->getShadowMapTexture();
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(*m_pWrkMatRes->m_pAvatarTbl->m_faceTex[0], location);
}

void DrMdoSetup::varStTex_Capture1(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    bool valid = pixl->m_cate[1].m_capture != nullptr;
    ap->beginTexSampling(2, 1);
    if (valid) {
        ap->setTexture(*pixl->m_cate[1].m_capture->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Capture2(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    ap->beginTexSampling(2, 1);
    if (pixl->m_cate[2].m_capture != nullptr) {
        ap->setTexture(*pixl->m_cate[2].m_capture->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Capture3(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    ap->beginTexSampling(2, 1);
    if (pixl->m_cate[3].m_capture != nullptr) {
        ap->setTexture(*pixl->m_cate[3].m_capture->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Capture4(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    ap->beginTexSampling(2, 1);
    if (pixl->m_capture4 != nullptr) {
        ap->setTexture(*pixl->m_capture4->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_RefractionMap(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    grlib::CGLibRenderTarget* obj = pixl->m_objTbl->m_postMan->m_refraction;
    ap->beginTexSampling(2, 1);
    if (obj != nullptr) {
        ap->setTexture(*obj->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_ColorDepTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(0)->m_pTexture, location);
}

void DrMdoSetup::varStTex_AvatarFaceMap2(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(*m_pWrkMatRes->m_pAvatarTbl->m_faceTex[1], location);
}

void DrMdoSetup::varStTex_AvatarEyeTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->beginTexSampling(2, 1);
    ap->setMipMapOn(*m_pWrkMatRes->m_pAvatarTbl->m_eyeTex);
    ap->setTexture(*m_pWrkMatRes->m_pAvatarTbl->m_eyeTex, location);
}

void DrMdoSetup::varStTex_CaptureMain(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    bool valid = pixl->m_cate[0].m_capture != nullptr;
    ap->beginTexSampling(2, 1);
    if (valid) {
        ap->setTexture(*pixl->m_cate[0].m_capture->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_BaseColorTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(0)->m_pTexture, location);
}

void DrMdoSetup::varStTex_SpecularIBLTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    const grlib::CGLibTextureBuffer* tex;
    if (m_pDrMan->isIBLSkip()) {
        ap->beginCubeTextureSampling(true);
        tex = &m_pDrMan->m_iniSys->m_texture[12];
    } else {
        DrPixlPostObjCubeMapIBL* ibl = m_pDrMan->m_pixlMan->m_objTbl->m_postMan->m_cubeMapIBL;
        ap->beginCubeTextureSampling(true);
        tex = ibl->getPremTexture();
    }
    ap->setTexture(*tex, location);
}

void DrMdoSetup::varStTex_AmbBRDFTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[3], location);
}

void DrMdoSetup::varStTex_ScreenCapTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibRenderTarget* obj = m_pDrMan->m_pixlMan->getPixlObj(5);
    if (obj != nullptr) {
        DrAPCache* ap = m_pDrMan->m_apCache;
        ap->beginTexSampling(2, 1);
        ap->setTexture(*obj->m_pTexture, location);
    }
}

void DrMdoSetup::varStTex_ToonGradTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    grlib::CGLibTextureBuffer* tex = m_pDrMan->m_pixlMan->m_objTbl->m_postMan->getToonGradTex();
    if (tex != nullptr) {
        ap->setTexture(*tex, location);
    }
}

void DrMdoSetup::varStTex_ToonRimTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[6], location);
}

void DrMdoSetup::varStTex_DitherTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    if (info->m_flags & 4) {
        ap->beginTexSampling(0, 1);
        ap->setTexture(*m_pDrMan->m_pixlMan->getDammyWhiteTexObj(), location);
    } else {
        ap->beginTexSampling(2, 0);
        ap->setTexture(m_pDrMan->m_iniSys->m_texture[1], location);
    }
}

void DrMdoSetup::varStTex_RefLightTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
}

void DrMdoSetup::varStTex_VolumeTex00(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->begin3DTextureWarpSampling();
    int idx = 0;
    MdoVanishEffectWrk* wrk = getVanishEffectWrk(matIdx, 2);
    if (wrk != nullptr) {
        idx = wrk->m_volumeTexIdx;
    }
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[idx + 7], location);
}

void DrMdoSetup::varStTex_VolumeTex01(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->begin3DTextureWarpSampling();
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[7], location);
}

void DrMdoSetup::varStTex_GlobalIBLIndexTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
}

void DrMdoSetup::varStTex_BackFaceDepthTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getBackFaceDepthTexture()->m_pTexture, location);
}

void DrMdoSetup::varStTex_DownDepthTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(*m_pDrMan->m_pixlMan->m_objTbl->m_postMan->getDownDepth()->m_pTexture, location);
}

void DrMdoSetup::varStTex_ClusterIdxListTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
}

void DrMdoSetup::varStTex_VelocityTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(3)->m_pTexture, location);
}

void DrMdoSetup::varStTex_RefractionAfterTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    grlib::CGLibRenderTarget* obj = pixl->m_objTbl->m_postMan->m_refraction;
    ap->beginTexSampling(2, 1);
    if (obj != nullptr) {
        ap->setTexture(*obj->m_pTexture, location);
    } else {
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Movie0(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    grlib::CGLibTextureBuffer* tex = pixl->m_movieTex[0];
    if (pixl->m_movieFilter[0]) {
        ap->beginTexSampling(2, 1);
    } else {
        ap->beginTexSampling(2, 0);
    }
    if (tex != nullptr) {
        ap->setMipMapOn(*tex);
        ap->setTexture(*tex, location);
    } else {
        ap->setMipMapOn(*pixl->getDammyTexObj());
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Movie1(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    grlib::CGLibTextureBuffer* tex = pixl->m_movieTex[1];
    if (pixl->m_movieFilter[1]) {
        ap->beginTexSampling(2, 1);
    } else {
        ap->beginTexSampling(2, 0);
    }
    if (tex != nullptr) {
        ap->setMipMapOn(*tex);
        ap->setTexture(*tex, location);
    } else {
        ap->setMipMapOn(*pixl->getDammyTexObj());
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Movie2(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    grlib::CGLibTextureBuffer* tex = pixl->m_movieTex[2];
    if (pixl->m_movieFilter[2]) {
        ap->beginTexSampling(2, 1);
    } else {
        ap->beginTexSampling(2, 0);
    }
    if (tex != nullptr) {
        ap->setMipMapOn(*tex);
        ap->setTexture(*tex, location);
    } else {
        ap->setMipMapOn(*pixl->getDammyTexObj());
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_Movie3(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    DrAPCache* ap = m_pDrMan->m_apCache;
    grlib::CGLibTextureBuffer* tex = pixl->m_movieTex[3];
    if (pixl->m_movieFilter[3]) {
        ap->beginTexSampling(2, 1);
    } else {
        ap->beginTexSampling(2, 0);
    }
    if (tex != nullptr) {
        ap->setMipMapOn(*tex);
        ap->setTexture(*tex, location);
    } else {
        ap->setMipMapOn(*pixl->getDammyTexObj());
        ap->setTexture(*pixl->getDammyTexObj(), location);
    }
}

void DrMdoSetup::varStTex_DiffuseIBL(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    ap->setTexture(*m_pDrMan->m_pixlMan->getDiffIBLObj()->m_pTexture, location);
}

void DrMdoSetup::varStTex_DownBaseColorTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    DrPixlMan* pixl = m_pDrMan->m_pixlMan;
    grlib::CGLibTextureBuffer* tex;
    if (pixl->m_objTbl->m_postMan->m_waterFog >= 0.05f) {
        tex = pixl->getPixlObj(16)->m_pTexture;
    } else {
        tex = pixl->getDammyTexObj();
    }
    ap->setTexture(*tex, location);
}

void DrMdoSetup::varStTex_AOTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(2)->m_pTexture, location);
}

void DrMdoSetup::varStTex_OrientationTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(0, 0);
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[15], location);
}

void DrMdoSetup::varStTex_FlagWaveTex0(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(0, 1);
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[16], location);
}

void DrMdoSetup::varStTex_FlagWaveTex1(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(0, 1);
    ap->setTexture(m_pDrMan->m_iniSys->m_texture[17], location);
}

void DrMdoSetup::varStTex_EtcTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getPixlObj(1)->m_pTexture, location);
}

void DrMdoSetup::varStTex_ToonDarkGradTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 1);
    grlib::CGLibTextureBuffer* tex = m_pDrMan->m_pixlMan->m_objTbl->m_postMan->getToonDarkGradTex();
    if (tex != nullptr) {
        ap->setTexture(*tex, location);
    }
}

void DrMdoSetup::varStTex_StencilTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    ap->setTexture(*m_pDrMan->m_pixlMan->getDepthObj()->m_pTexture, location);
}

void DrMdoSetup::varStTex_DitherCalcTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    DrAPCache* ap = m_pDrMan->m_apCache;
    ap->beginTexSampling(2, 0);
    DrIniSys* iniSys = m_pDrMan->m_iniSys;
    if (!(m_stateFlags & 0x400)) {
        ap->setTexture(iniSys->m_texture[1], location);
    } else {
        ap->setTexture(iniSys->m_texture[2], location);
    }
}

void DrMdoSetup::varStImg_BaseColor(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibCtlTexture::setUAVTexture(*m_pDrMan->m_pixlMan->getPixlObj(0)->m_pTexture, location, 0, 0);
}

void DrMdoSetup::varStImg_Etc(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibCtlTexture::setUAVTexture(*m_pDrMan->m_pixlMan->getPixlObj(1)->m_pTexture, location, 0, 0);
}

void DrMdoSetup::varStImg_Normal(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibCtlTexture::setUAVTexture(*m_pDrMan->m_pixlMan->getPixlObj(2)->m_pTexture, location, 0, 0);
}

void DrMdoSetup::varStImg_Velocity(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibCtlTexture::setUAVTexture(*m_pDrMan->m_pixlMan->getPixlObj(3)->m_pTexture, location, 0, 0);
}

void DrMdoSetup::varStImg_ZBuff(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx) {
    grlib::CGLibCtlTexture::setUAVTexture(*m_pDrMan->m_pixlMan->getPixlObj(4)->m_pTexture, location, 0, 0);
}

DrMdoZSortObj::DrMdoZSortObj(void* owner) : m_next(nullptr), m_parent(nullptr), m_owner(owner) {}

void (DrMdoSetup::*DrMdoSetup::s_pUniBkMat[31])(const MdsMatValShaderCate*, int, int, int, bool, unsigned int) = {
    &DrMdoSetup::uniformBlock_Static,
    &DrMdoSetup::uniformBlock_Material,
    &DrMdoSetup::uniformBlock_Light,
    &DrMdoSetup::uniformBlock_Mdl,
    &DrMdoSetup::uniformBlock_Bone,
    &DrMdoSetup::uniformBlock_OldMdl,
    &DrMdoSetup::uniformBlock_OldBone,
    &DrMdoSetup::uniformBlock_no,
    &DrMdoSetup::uniformBlock_AvatarChar,
    &DrMdoSetup::uniformBlock_AvatarDoll,
    &DrMdoSetup::uniformBlock_no,
    &DrMdoSetup::uniformBlock_no,
    &DrMdoSetup::uniformBlock_no,
    &DrMdoSetup::uniformBlock_Fog,
    &DrMdoSetup::uniformBlock_no,
    &DrMdoSetup::uniformBlock_no,
    &DrMdoSetup::uniformBlock_no,
    &DrMdoSetup::uniformBlock_Toon,
    &DrMdoSetup::uniformBlock_VolTexCalc,
    &DrMdoSetup::uniformBlock_GlobalIBL,
    &DrMdoSetup::uniformBlock_ClusterParam,
    &DrMdoSetup::uniformBlock_ClusterPntList,
    &DrMdoSetup::uniformBlock_ClusterSptList,
    &DrMdoSetup::uniformBlock_ClusterIdxList,
    &DrMdoSetup::uniformBlock_ClusterAddressList,
    &DrMdoSetup::uniformBlock_RimBloomCalc,
    &DrMdoSetup::uniformBlock_no,
    &DrMdoSetup::uniformBlock_no,
    &DrMdoSetup::uniformBlock_no,
    &DrMdoSetup::uniformBlock_no,
    &DrMdoSetup::uniformBlock_Toon2,
};

void (DrMdoSetup::*DrMdoSetup::s_pStaticTexture[46])(const MdsMatInfoHeader*, unsigned int, unsigned int) = {
    &DrMdoSetup::varStTex_ColorTex,
    &DrMdoSetup::varStTex_NormalTex,
    &DrMdoSetup::varStTex_LightTex,
    &DrMdoSetup::varStTex_DepthTex,
    &DrMdoSetup::varStTex_RefTex,
    &DrMdoSetup::varStTex_ShadowMap,
    &DrMdoSetup::varStTex_AvatarFaceMap1,
    &DrMdoSetup::varStTex_Capture1,
    &DrMdoSetup::varStTex_Capture2,
    &DrMdoSetup::varStTex_Capture3,
    &DrMdoSetup::varStTex_Capture4,
    &DrMdoSetup::varStTex_RefractionMap,
    &DrMdoSetup::varStTex_ColorDepTex,
    &DrMdoSetup::varStTex_AvatarFaceMap2,
    &DrMdoSetup::varStTex_AvatarEyeTex,
    &DrMdoSetup::varStTex_CaptureMain,
    &DrMdoSetup::varStTex_BaseColorTex,
    &DrMdoSetup::varStTex_SpecularIBLTex,
    &DrMdoSetup::varStTex_AmbBRDFTex,
    &DrMdoSetup::varStTex_ScreenCapTex,
    &DrMdoSetup::varStTex_ToonGradTex,
    &DrMdoSetup::varStTex_ToonRimTex,
    &DrMdoSetup::varStTex_DitherTex,
    &DrMdoSetup::varStTex_RefLightTex,
    &DrMdoSetup::varStTex_VolumeTex00,
    &DrMdoSetup::varStTex_VolumeTex01,
    &DrMdoSetup::varStTex_GlobalIBLIndexTex,
    &DrMdoSetup::varStTex_BackFaceDepthTex,
    &DrMdoSetup::varStTex_DownDepthTex,
    &DrMdoSetup::varStTex_ClusterIdxListTex,
    &DrMdoSetup::varStTex_VelocityTex,
    &DrMdoSetup::varStTex_RefractionAfterTex,
    &DrMdoSetup::varStTex_Movie0,
    &DrMdoSetup::varStTex_Movie1,
    &DrMdoSetup::varStTex_Movie2,
    &DrMdoSetup::varStTex_Movie3,
    &DrMdoSetup::varStTex_DiffuseIBL,
    &DrMdoSetup::varStTex_DownBaseColorTex,
    &DrMdoSetup::varStTex_AOTex,
    &DrMdoSetup::varStTex_OrientationTex,
    &DrMdoSetup::varStTex_FlagWaveTex0,
    &DrMdoSetup::varStTex_FlagWaveTex1,
    &DrMdoSetup::varStTex_EtcTex,
    &DrMdoSetup::varStTex_ToonDarkGradTex,
    &DrMdoSetup::varStTex_StencilTex,
    &DrMdoSetup::varStTex_DitherCalcTex,
};

void (DrMdoSetup::*DrMdoSetup::s_pStaticImage[5])(const MdsMatInfoHeader*, unsigned int, unsigned int) = {
    &DrMdoSetup::varStImg_BaseColor,
    &DrMdoSetup::varStImg_Etc,
    &DrMdoSetup::varStImg_Normal,
    &DrMdoSetup::varStImg_Velocity,
    &DrMdoSetup::varStImg_ZBuff,
};

int (DrMdoSetup::*DrMdoSetup::s_pStockMaterial[10])(float*, DrResMdoMat*, const MdsMatInfoHeader*, const MdsMatVariableTbl*) = {
    &DrMdoSetup::unimate_depthRatio,
    &DrMdoSetup::unimate_texMatrix,
    &DrMdoSetup::unimate_workFloat4,
    &DrMdoSetup::unimate_workColor,
    &DrMdoSetup::unimate_ProjectionMat,
    &DrMdoSetup::unimate_alphaInfo,
    &DrMdoSetup::unimate_matColor,
    &DrMdoSetup::unimate_NomProjectionMat,
    &DrMdoSetup::unimate_DollTexWork,
    &DrMdoSetup::unimate_AvatarMapWrk,
};

DrMdoCtlCldMdl::DrMdoCtlCldMdl(const void* data, DrMan* drMan, int viewNum) : DrMdlObj(viewNum) {
    m_mdlType = 4;
    m_pCldMdlData = nullptr;
    m_pCldData = data;
    m_pDrMan = drMan;
}

DrMdoCtlCldMdl::~DrMdoCtlCldMdl() {
    if (m_pCldMdlData != nullptr) {
        cloud::CloudMan::sys()->m_pObjMan->releaseMdlData(m_pCldMdlData);
        m_pCldMdlData = nullptr;
        m_pCldData = nullptr;
    }
}

void DrMdoCtlCldMdl::resourceInit() {
    if (m_pCldMdlData == nullptr) {
        m_pCldMdlData = cloud::CloudMan::sys()->m_pObjMan->createMdlData(m_pCldData);
    }
}

void DrMdoCtlCldMdl::update() {
    if (m_pCldMdlData != nullptr) {
        m_pCldMdlData->setCallDisp(true);
    }
}

void DrMdoCtlCldMdl::dispOffUpdate() {
    if (m_pCldMdlData != nullptr) {
        m_pCldMdlData->setCallDisp(false);
    }
}

DrMdoCtlMpf::DrMdoCtlMpf(const void* data, const char* name, DrMan* drMan, int viewNum)
    : DrMdlObj(viewNum), m_pWorkBuf(nullptr), pad_1B8(nullptr), pad_1C0(0), m_pMpfWork(nullptr), m_pMpfAuto(nullptr),
      m_pMpfInst(nullptr), m_pPosMpf(nullptr), m_pSortMpf(nullptr) {
    m_mdlType = 2;
    drMan->m_mdlMan->addMpfObj();
    m_pDrMan = drMan;
    const unsigned char* top = static_cast<const unsigned char*>(data);
    const DataHeader* head = static_cast<const DataHeader*>(data);
    if (head->m_dataOfs[5] != 0) {
        initMpfMaterial(top + head->m_dataOfs[1], top + head->m_dataOfs[3], top + head->m_dataOfs[0],
                        top + head->m_dataOfs[5], false);
    } else {
        initMpfMaterial(top + head->m_dataOfs[1], top + head->m_dataOfs[3], top + head->m_dataOfs[0], nullptr, false);
    }
    setupMpf(top + head->m_mpfOfs);
}

void DrMdoCtlMpf::setupMpf(const unsigned char* data) {
    if (m_pWorkBuf != nullptr) {
        mtl::MemManager::deallocate(m_pWorkBuf, 0, false);
        m_pWorkBuf = nullptr;
    }
    const DrResMdoSeamWrkMpf::MpfData* mpf = reinterpret_cast<const DrResMdoSeamWrkMpf::MpfData*>(data);
    m_objNum = mpf->m_objNum;
    m_pObjData = reinterpret_cast<const MdsMpfObjData*>(data + mpf->m_objOfs);
    int size = DrMdoCtlMpfWork::calcRenderListWork(m_objNum, m_pObjData) + m_pWrkMatRes->m_pMdlData->m_infoTotal * 4 +
               m_pWrkMatRes->m_mdlTopNum * 0x40 + 0x220;
    if (mpf->m_autoOfs != 0) {
        size += (0x10 - size % 0x10) % 0x10;
        size += DrMdoCtlMpfAuto::calcWorkSize(data + mpf->m_autoOfs);
    }
    m_pWorkBuf = static_cast<unsigned char*>(
        mtl::MemManager::allocate(m_pDrMan->m_allocHandle, size, 0x20, false, "no name", 0));
    m_pMpfWork = reinterpret_cast<DrMdoCtlMpfWork*>(m_pWorkBuf);
    m_pMpfAuto = reinterpret_cast<DrMdoCtlMpfAuto*>(m_pWorkBuf + 0x48);
    new (m_pMpfWork) DrMdoCtlMpfWork();
    new (m_pMpfAuto) DrMdoCtlMpfAuto();
    m_pMpfInst = reinterpret_cast<DrMdoCtlMpfInst*>(m_pWorkBuf + 0x1B8);
    m_pPosMpf = reinterpret_cast<DrResMdoSeamWrkPosMpf*>(m_pWorkBuf + 0x1D0);
    new (m_pMpfInst) DrMdoCtlMpfInst();
    m_pMpfInst->setupInstMpf(data);
    m_pPosMpf->setupMpfBasePos(data);
    DrMdoMpfMan* mpfMan = m_pDrMan->m_mdlMan->m_mpfMan;
    int used = m_pMpfWork->setupRenderListWork(m_pWorkBuf + 0x200, m_objNum, m_pObjData, mpfMan);
    m_pSortMpf = reinterpret_cast<DrResMdoSortMpf*>(used + 0x200 + m_pWorkBuf);
    new (m_pSortMpf) DrResMdoSortMpf(this);
    m_pRenderEntry = reinterpret_cast<RenderEntry*>(m_pWorkBuf + (used + 0x220));
    m_pRenderList = reinterpret_cast<RenderEntry**>(m_pRenderEntry + m_pWrkMatRes->m_pMdlData->m_infoTotal);
    if (mpf->m_autoOfs != 0) {
        int ofs = used + 0x220 + m_pWrkMatRes->m_pMdlData->m_infoTotal * 4 + m_pWrkMatRes->m_mdlTopNum * 0x40;
        ofs += (0x10 - ofs % 0x10) % 0x10;
        m_pMpfAuto->setupAutoMpf(data, data + mpf->m_autoOfs, m_pWorkBuf + ofs);
    }
}

DrMdoCtlMpf::~DrMdoCtlMpf() {
    releaseMpf();
}

void DrMdoCtlMpf::releaseMpf() {
    m_pMpfAuto->autoMpfRelease();
    m_pMpfAuto->~DrMdoCtlMpfAuto();
    m_pSortMpf->~DrResMdoSortMpf();
    if (m_pWorkBuf != nullptr) {
        mtl::MemManager::deallocate(m_pWorkBuf, 0, false);
        m_pWorkBuf = nullptr;
    }
    if (pad_1B8 != nullptr) {
        mtl::MemManager::deallocate(pad_1B8, 0, false);
        pad_1B8 = nullptr;
    }
    releaseMat();
    m_pDrMan->m_mdlMan->delMpfObj();
}

void DrMdoCtlMpf::resourceInit() {
    setupMpfResource();
}

void DrMdoCtlMpfAuto::setupAutoMpf(const unsigned char* data, const unsigned char* autoData, unsigned char* work) {
    const MdsMpfAutoHead* head = reinterpret_cast<const MdsMpfAutoHead*>(autoData);
    m_pHeader = head;
    m_pEntry = reinterpret_cast<const Entry*>(data + head->m_entryOfs);
    m_pPoliData = nullptr;
    m_pBuff = reinterpret_cast<_wkMpfAutoBuff*>(work);
    m_pCurBuff = reinterpret_cast<_wkMpfAutoBuff*>(work);
    int size = 0;
    if (head->m_poliOfs == 0) {
        m_pBuffTbl = reinterpret_cast<_wkMpfAutoBuff**>(work + 0x70);
        m_pBuffTbl[0] = reinterpret_cast<_wkMpfAutoBuff*>(work);
        m_buffNum = 1;
        m_pCurBuff->m_max[0] = m_pHeader->m_buffMax[0];
        m_pCurBuff->m_min[0] = m_pHeader->m_buffMin[0];
        m_pCurBuff->m_max[1] = m_pHeader->m_buffMax[1];
        m_pCurBuff->m_min[1] = m_pHeader->m_buffMin[1];
        m_pCurBuff->m_pPoli = reinterpret_cast<const MdsMpfAutoPoli*>(data + m_pHeader->m_buffPoliOfs);
        m_pCurBuff->m_pTbl[0] = data + m_pHeader->m_buffTblOfs[0];
        m_pCurBuff->m_pTbl[1] = data + m_pHeader->m_buffTblOfs[1];
        m_pCurBuff->m_pTbl[2] = data + m_pHeader->m_buffTblOfs[2];
        m_pCurBuff->m_pTbl[3] = data + m_pHeader->m_buffTblOfs[3];
        m_pColTbl = m_pCurBuff->m_pTbl[3];
        if (m_pHeader->m_buffTreeOfs != 0) {
            m_pCurBuff->m_pTree = reinterpret_cast<const MdsMpfAutoTree*>(data + m_pHeader->m_buffTreeOfs);
        } else {
            m_pCurBuff->m_pTree = nullptr;
        }
        m_pCurBuff->m_pPoliList = reinterpret_cast<const unsigned int*>(data + m_pHeader->m_buffPoliListOfs);
        m_pCurBuff->m_pCell = reinterpret_cast<const unsigned int*>(data + m_pHeader->m_buffCellOfs);
        m_pCurBuff->m_pGrid = reinterpret_cast<const float(*)[2]>(data + m_pHeader->m_buffGridOfs);
        if (m_pHeader->m_instOfs != 0 && m_pHeader->m_instType == -13) {
            m_pCurBuff->m_pInstData = reinterpret_cast<const _wkMpfAutoBuff::Inst*>(data + m_pHeader->m_instOfs);
            m_pCurBuff->m_pPosTree = reinterpret_cast<const MdsMpfAutoPosTree*>(data + m_pHeader->m_posTreeOfs);
            m_pCurBuff->m_pIdxTbl = reinterpret_cast<const unsigned int*>(data + m_pHeader->m_idxTblOfs);
            m_pIdxTbl = m_pCurBuff->m_pIdxTbl;
            m_pTbl[0] = data + m_pHeader->m_tblOfs[1];
            m_pTbl[1] = data + m_pHeader->m_tblOfs[2];
            m_pTbl[2] = data + m_pHeader->m_tblOfs[3];
            m_pPoliData = data + m_pHeader->m_tblOfs[0];
        } else {
            m_pCurBuff->m_pInstData = nullptr;
        }
        size = 0x78;
    } else if (head->m_tblOfs[0] != 0 && head->m_instType == -13) {
        m_pColTbl = data + head->m_buffTblOfs[3];
        m_pIdxTbl = reinterpret_cast<const unsigned int*>(data + head->m_idxTblOfs);
        m_pTbl[0] = data + head->m_tblOfs[1];
        m_pTbl[1] = data + head->m_tblOfs[2];
        m_pTbl[2] = data + head->m_tblOfs[3];
        m_pPoliData = data + head->m_tblOfs[0];
    }
    m_param74 = 0;
    m_pWorkTbl = reinterpret_cast<_MPFWorkAutoInf**>(work + size);
    size += m_pHeader->m_num * sizeof(_MPFWorkAutoInf*);
    m_pWorkLast = reinterpret_cast<_MPFWorkAutoInf**>(work + size);
    size += m_pHeader->m_num * sizeof(_MPFWorkAutoInf*);
    size += (0x10 - size % 0x10) % 0x10;
    m_pPrePos = reinterpret_cast<mm::Vec3*>(work + size);
    size += m_pHeader->m_num * sizeof(mm::Vec3);
    size += (0x10 - size % 0x10) % 0x10;
    for (int i = 0; i < m_pHeader->m_num; i++) {
        mm::Vec3* pos = &m_pPrePos[i];
        pos->x = -100000.0f;
        pos->y = -100000.0f;
        pos->z = -100000.0f;
        m_pWorkTbl[i] = nullptr;
        m_pWorkLast[i] = nullptr;
    }
    m_pHit = reinterpret_cast<Hit*>(work + size);
}

void DrMdoCtlMpf::update() {
    if (m_ctlFlags2 & 0x40000) {
        m_ctlFlags2 &= ~0x30000;
    } else {
        int idx = DrMan::s_nDblIdx;
        unsigned int bit = 0x10000 << idx;
        if (bit & m_ctlFlags2) {
            m_ctlFlags2 &= ~bit;
            m_singleAlpha = m_alpha[idx];
        }
    }
    m_aabbMax.x = 1.0f;
    m_aabbMax.y = 1.0f;
    m_aabbMax.z = 1.0f;
    m_aabbMin.x = -1.0f;
    m_aabbMin.y = -1.0f;
    m_aabbMin.z = -1.0f;
    m_length = 100000.0f;
    m_stateFlags = 0;
    m_mdlFlags = 0;
    m_center.x = 0.0f;
    m_center.y = 0.0f;
    m_center.z = 0.0f;
    DrMdoMpfMan* mpfMan = m_pDrMan->m_mdlMan->m_mpfMan;
    if (mpfMan != nullptr) {
        mpfMan->m_windScale = m_speed;
    }
    calcMpfRenderList();
    updateMpfMatUniformBlock();
    if (m_stateFlags & 0x8000) {
        m_pDrMan->m_mdlMan->m_pPassReq[0] = true;
    }
    if (m_stateFlags & 0x10000) {
        m_pDrMan->m_mdlMan->m_pPassReq[1] = true;
    }
}

void DrMdoSetup::updateMpfMatUniformBlock() {
    const MdsMatDataHeader* head = reinterpret_cast<const MdsMatDataHeader*>(m_pWrkMatRes->m_pMatData);
    if (head->m_mpfParamNum > 0) {
        const MdsMatDataHeader::MpfMatParam* param = reinterpret_cast<const MdsMatDataHeader::MpfMatParam*>(
            reinterpret_cast<const unsigned char*>(head) + head->m_mpfParamOfs);
        for (int i = 0; i < head->m_mpfParamNum; i++, param++) {
            grlib::CGLibDblUniformBlock* block = &m_pWrkMatRes->m_pMatUniformArray->m_pArray[static_cast<unsigned int>(i)];
            float* dst = reinterpret_cast<float*>(block->getBuff());
            struct {
                unsigned int m_val[6];
                float m_zero[2];
                float m_fade[4];
            } buf;
            buf.m_val[0] = param->m_val[0];
            buf.m_val[1] = param->m_val[1];
            buf.m_val[2] = param->m_val[2];
            buf.m_val[3] = param->m_val[3] | param->m_shift << 4;
            buf.m_val[4] = param->m_val[4];
            buf.m_val[5] = param->m_val[5];
            buf.m_zero[0] = 0.0f;
            buf.m_zero[1] = 0.0f;
            float fadeNear = param->m_fadeNear;
            float fadeFar = param->m_fadeFar;
            float fadeScale = param->m_fadeScale;
            if (fadeNear == 0.0f && fadeFar == 0.0f && fadeScale == 0.0f) {
                fadeNear = 7000.0f;
                fadeFar = 8000.0f;
                fadeScale = 1.0f;
            }
            buf.m_fade[0] = fadeNear;
            buf.m_fade[1] = 1.0f / (fadeFar - fadeNear + 1e-06f);
            buf.m_fade[2] = fadeScale;
            buf.m_fade[3] = 0.0f;
            grlib::ShdF32SetF32Array(dst, reinterpret_cast<const float*>(&buf), 12);
            block->updateData();
        }
    }
}

void DrMdoCtlMpfWork::beginList() {
    char* work = m_pMpfMan->getFrameWork(m_objNum * (sizeof(_wkMpfObjBuff) + sizeof(_wkMpfAlphaObjBuff)));
    _wkMpfObjBuff* buff = reinterpret_cast<_wkMpfObjBuff*>(work);
    _wkMpfAlphaObjBuff* alphaBuff = reinterpret_cast<_wkMpfAlphaObjBuff*>(work + m_objNum * sizeof(_wkMpfObjBuff));
    const MdsMpfObjData* objData = m_pObjData;
    for (long i = 0; i < m_objNum; i++) {
        m_ppObjBuff[i] = &buff[i];
        m_ppAlphaObjBuff[i] = &alphaBuff[i];
        m_pObjWork[i].m_pLastBuff = m_ppObjBuff[i];
        m_pObjWork[i].m_pLastBuff->m_num = 0;
        m_pObjWork[i].m_pLastBuff->m_pNext = nullptr;
        m_pObjWork[i].m_pLastAlphaBuff = m_ppAlphaObjBuff[i];
        m_pObjWork[i].m_pLastAlphaBuff->m_num = 0;
        m_pObjWork[i].m_pLastAlphaBuff->m_pNext = nullptr;
        m_pObjWork[i].m_selFlags &= ~8;
        m_pObjWork[i].m_objChk = 0;
        switch (objData[i].m_type) {
        case 1:
        case 3:
            m_pObjWork[i].m_pLastBuff->m_pAutoSet = &DrMdoCtlMpfWork::auto_fastSet;
            m_pObjWork[i].m_pLastAlphaBuff->m_pAutoSet = &DrMdoCtlMpfWork::auto_alpha_fastSet;
            break;
        default:
            m_pObjWork[i].m_pLastBuff->m_pPosSet = &DrMdoCtlMpfWork::mpf_fastSet;
            m_pObjWork[i].m_pLastAlphaBuff->m_pPosSet = &DrMdoCtlMpfWork::mpf_alpha_fastSet;
            break;
        }
    }
    m_pPntAlphaMan->update(DrMan::getIns()->m_mpfWindPower);
    int size = m_objNum << 7;
    memset(m_pWorkBuf, 0, size);
}

void DrMdoCtlMpf::defMpfrender() {
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pWrkMatRes->m_pVertex->beginVertexSetup();
    grlib::CGLibVtxInstans* inst = m_pDrMan->m_mdlMan->m_vertexMan->m_instans;
    DrAPCache* cache = m_pDrMan->m_apCache;
    cache->setupCulling(static_cast<DrApCullType>(2));
    m_pDrMan->m_pixlMan->selectGBuffRenderTarget(0x1F);
    cache->setupDepthStencil(0x18, 1, 0, 3);
    cache->setupAlphaBlend(0);
    for (int i = 0; i < m_objNum; i++) {
        if (m_pMpfWork->getObjChk(i) == 0) {
            continue;
        }
        RenderEntry* entry = *(i * 8 + m_pRenderList + m_renderPass);
        if (entry == nullptr) {
            continue;
        }
        const MdsMdlTopHeader* top = &m_pWrkMatRes->m_pMdlTop[i];
        const MdsMdlInfoHeader* infos = reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs);
        for (;;) {
            mpfDrawRender(i, &infos[entry->m_infoIdx], m_pMpfWork, inst);
            unsigned int next = entry->m_next;
            if (next == 0) {
                break;
            }
            entry = &m_pRenderEntry[next - 1];
        }
    }
    cache->setupAlphaBlend(0);
}

void DrMdoCtlMpf::defMpfZPreRender() {
    m_renderPass = 0;
    m_renderTech = 0;
    m_curTriBlockIdx = -1;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pWrkMatRes->m_pVertex->beginVertexSetup();
    grlib::CGLibVtxInstans* inst = m_pDrMan->m_mdlMan->m_vertexMan->m_instans;
    m_pDrMan->m_apCache->setupCulling(static_cast<DrApCullType>(2));
    for (int i = 0; i < m_objNum; i++) {
        if (m_pMpfWork->getObjChk(i) == 0) {
            continue;
        }
        RenderEntry* entry = *(i * 8 + m_pRenderList + m_renderPass);
        if (entry == nullptr) {
            continue;
        }
        const MdsMdlTopHeader* top = &m_pWrkMatRes->m_pMdlTop[i];
        const MdsMdlInfoHeader* infos = reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs);
        for (;;) {
            mpfZPrePassRender(i, &infos[entry->m_infoIdx], m_pMpfWork, inst);
            unsigned int next = entry->m_next;
            if (next == 0) {
                break;
            }
            entry = &m_pRenderEntry[next - 1];
        }
    }
}

void DrMdoCtlMpf::callZPrepassRender() {
    if (m_stateFlags & 0x1) {
        defMpfZPreRender();
    }
}

void DrMdoCtlMpf::callRenderMpf() {
    if (!(m_stateFlags & 0x1)) {
        return;
    }
    DrMan::get()->m_tileParm->begin(static_cast<DrPixlTileParm::TileType>(3));
    m_renderTech = 0;
    m_renderPass = 0;
    defMpfrender();
    DrMan::get()->m_tileParm->end(static_cast<DrPixlTileParm::TileType>(3));
}

int DrMdoCtlMpfWork::calcRenderListWork(int objNum, const MdsMpfObjData* objData) {
    int size = objNum * 0x1D0;
    return DrResMdoPntAlphaMan::getWrkSize(128) + size;
}

int DrMdoCtlMpfWork::getObjChk(int idx) {
    return m_pObjWork[idx].m_objChk;
}

void DrMdoCtlMpfWork::createAutoList(int idx, DrCalcViewWork* view, grlib::CGLibVtxInstans* inst) {
    _wkMpfObjSelect* sel = &m_pObjWork[idx];
    float range = m_pObjData[idx].m_range * 0.01f;
    if (sel->m_selFlags & 1) {
        createAutoMdlRenderList(sel, view, inst, range, m_ppObjBuff[idx], m_ppAlphaObjBuff[idx]);
    } else {
        createAutoBillRenderList(sel, view, inst, range, m_ppObjBuff[idx], m_ppAlphaObjBuff[idx]);
    }
}

void DrMdoCtlMpfInst::setupInstMpf(const unsigned char* data) {
    m_pInstData = reinterpret_cast<const MdsMpfObjData*>(data + reinterpret_cast<const ResHeader*>(data)->m_instOfs);
}

DrMdoCtlMpfInst::DrMdoCtlMpfInst() {}

int DrMdoCtlMpfAuto::calcWorkSize(const unsigned char* data) {
    const MdsMpfAutoHead* head = reinterpret_cast<const MdsMpfAutoHead*>(data);
    int size = 0;
    if (head->m_poliOfs == 0) {
        size = 0x78;
    }
    size += head->m_num * 0x10;
    size += 0x50;
    size += (0x10 - size % 0x10) % 0x10;
    size += head->m_num * 0x10;
    size += (0x10 - size % 0x10) % 0x10;
    return size;
}

void DrMdoCtlMpfAuto::autoMpfRelease() {
    if (m_pHeader == nullptr) {
        return;
    }
    int num = m_pHeader->m_num;
    for (int i = 0; i < num; i++) {
        _MPFWorkAutoInf* inf = m_pWorkTbl[i];
        while (inf != nullptr) {
            _MPFWorkAutoInf* next = inf->m_pNext;
            m_pMpfMan->freeMemWork(inf);
            inf = next;
        }
        m_pWorkTbl[i] = nullptr;
        m_pWorkLast[i] = nullptr;
    }
    m_pHeader = nullptr;
    m_buffNum = 0;
}

DrMdoCtlMpfAuto::DrMdoCtlMpfAuto() {
    m_buffNum = 0;
    m_autoFlags = 0;
    m_lodMask = 0;
    m_workNum = 0;
    m_workNum2 = 0;
    m_pos[0] = m_pos[1] = m_pos[2] = 0.0f;
    m_pHeader = nullptr;
    m_pPoliData = nullptr;
}

DrMdoCtlMpfAuto::~DrMdoCtlMpfAuto() {
    autoMpfRelease();
}

void DrMdoMpfMan::freeMemWork(_MPFWorkAutoInf* inf) {
    _MPFWorkAutoInf* prev = inf->m_pBlockPrev;
    bool link;
    if (prev == nullptr || (prev->m_flags & 2)) {
        link = true;
    } else {
        prev->m_size += inf->m_size;
        _MPFWorkAutoInf* blockNext = inf->m_pBlockNext;
        prev->m_pBlockNext = blockNext;
        if (blockNext != nullptr) {
            blockNext->m_pBlockPrev = prev;
        }
        memset(inf, 0, sizeof(_MPFWorkAutoInf));
        link = false;
        inf = prev;
    }
    _MPFWorkAutoInf* blockNext = inf->m_pBlockNext;
    if (blockNext != nullptr && !(blockNext->m_flags & 2)) {
        inf->m_size += blockNext->m_size;
        _MPFWorkAutoInf* after = blockNext->m_pBlockNext;
        inf->m_pBlockNext = after;
        if (after != nullptr) {
            after->m_pBlockPrev = inf;
        }
        _MPFWorkAutoInf* next = blockNext->m_pNext;
        _MPFWorkAutoInf* prevFree = blockNext->m_pPrev;
        if (next == nullptr) {
            if (prevFree == nullptr) {
                m_pFreeHead = nullptr;
                m_pFreeTail = nullptr;
            } else {
                m_pFreeTail = prevFree;
                prevFree->m_pNext = nullptr;
            }
        } else if (prevFree == nullptr) {
            m_pFreeHead = next;
            next->m_pPrev = nullptr;
        } else {
            next->m_pPrev = prevFree;
            blockNext->m_pPrev->m_pNext = blockNext->m_pNext;
        }
    }
    if (link) {
        inf->m_flags = 0;
        if (m_pFreeTail == nullptr) {
            m_pFreeHead = inf;
            inf->m_pPrev = nullptr;
        } else {
            inf->m_pPrev = m_pFreeTail;
            m_pFreeTail->m_pNext = inf;
        }
        inf->m_pNext = nullptr;
        m_pFreeTail = inf;
    }
}

void DrMdoCtlMpfAuto::changeMemAutoMpf(const unsigned char* data, const unsigned char* autoData) {
    const MdsMpfAutoHead* head = reinterpret_cast<const MdsMpfAutoHead*>(autoData);
    m_pHeader = head;
    m_pEntry = reinterpret_cast<const Entry*>(data + head->m_entryOfs);
    m_pCurBuff = m_pBuff;
    if (head->m_poliOfs == 0) {
        m_pCurBuff->m_pPoli = reinterpret_cast<const MdsMpfAutoPoli*>(data + m_pHeader->m_buffPoliOfs);
        m_pCurBuff->m_pTbl[0] = data + m_pHeader->m_buffTblOfs[0];
        m_pCurBuff->m_pTbl[1] = data + m_pHeader->m_buffTblOfs[1];
        m_pCurBuff->m_pTbl[2] = data + m_pHeader->m_buffTblOfs[2];
        m_pCurBuff->m_pTbl[3] = data + m_pHeader->m_buffTblOfs[3];
        m_pColTbl = m_pCurBuff->m_pTbl[3];
        if (m_pHeader->m_buffTreeOfs != 0) {
            m_pCurBuff->m_pTree = reinterpret_cast<const MdsMpfAutoTree*>(data + m_pHeader->m_buffTreeOfs);
        } else {
            m_pCurBuff->m_pTree = nullptr;
        }
        m_pCurBuff->m_pPoliList = reinterpret_cast<const unsigned int*>(data + m_pHeader->m_buffPoliListOfs);
        m_pCurBuff->m_pCell = reinterpret_cast<const unsigned int*>(data + m_pHeader->m_buffCellOfs);
        m_pCurBuff->m_pGrid = reinterpret_cast<const float(*)[2]>(data + m_pHeader->m_buffGridOfs);
        if (m_pHeader->m_instOfs != 0 && m_pHeader->m_instType == -13) {
            m_pCurBuff->m_pInstData = reinterpret_cast<const _wkMpfAutoBuff::Inst*>(data + m_pHeader->m_instOfs);
            m_pCurBuff->m_pPosTree = reinterpret_cast<const MdsMpfAutoPosTree*>(data + m_pHeader->m_posTreeOfs);
            m_pCurBuff->m_pIdxTbl = reinterpret_cast<const unsigned int*>(data + m_pHeader->m_idxTblOfs);
            m_pIdxTbl = m_pCurBuff->m_pIdxTbl;
            m_pTbl[0] = data + m_pHeader->m_tblOfs[1];
            m_pTbl[1] = data + m_pHeader->m_tblOfs[2];
            m_pTbl[2] = data + m_pHeader->m_tblOfs[3];
            m_pPoliData = data + m_pHeader->m_tblOfs[0];
        } else {
            m_pCurBuff->m_pInstData = nullptr;
        }
    } else if (head->m_tblOfs[0] != 0 && head->m_instType == -13) {
        m_pColTbl = data + head->m_buffTblOfs[3];
        m_pIdxTbl = reinterpret_cast<const unsigned int*>(data + head->m_idxTblOfs);
        m_pTbl[0] = data + head->m_tblOfs[1];
        m_pTbl[1] = data + head->m_tblOfs[2];
        m_pTbl[2] = data + head->m_tblOfs[3];
        m_pPoliData = data + head->m_tblOfs[0];
    }
}

void DrMdoCtlMpfAuto::resetPrePos() {
    for (int i = 0; i < m_pHeader->m_num; i++) {
        mm::Vec3* pos = &m_pPrePos[i];
        pos->x = -100000.0f;
        pos->y = -100000.0f;
        pos->z = -100000.0f;
    }
}

void DrMdoCtlMpfAuto::setBuffTbl(_wkMpfAutoBuff** buffTbl, int buffNum) {
    m_pBuffTbl = buffTbl;
    m_buffNum = buffNum;
}

void DrMdoCtlMpfAuto::getMemWork(_MPFWorkAutoInf* inf) {
    DrMdoMpfMan* man = m_pMpfMan;
    unsigned int used = inf->m_num * 0x20;
    unsigned int need = used + 0x1C0;
    if (inf->m_size < need) {
        _MPFWorkAutoInf* next = inf->m_pNext;
        _MPFWorkAutoInf* prev = inf->m_pPrev;
        if (next == nullptr) {
            if (prev == nullptr) {
                man->m_pFreeHead = nullptr;
                man->m_pFreeTail = nullptr;
            } else {
                man->m_pFreeTail = prev;
                prev->m_pNext = nullptr;
            }
        } else if (prev == nullptr) {
            man->m_pFreeHead = next;
            next->m_pPrev = nullptr;
        } else {
            next->m_pPrev = prev;
            inf->m_pPrev->m_pNext = inf->m_pNext;
        }
    } else {
        used += 0x60;
        _MPFWorkAutoInf* rest = reinterpret_cast<_MPFWorkAutoInf*>(reinterpret_cast<unsigned char*>(inf) + used);
        memset(rest, 0, sizeof(_MPFWorkAutoInf));
        _MPFWorkAutoInf* blockNext = inf->m_pBlockNext;
        rest->m_pBlockNext = blockNext;
        rest->m_pBlockPrev = inf;
        if (blockNext != nullptr) {
            blockNext->m_pBlockPrev = rest;
        }
        inf->m_pBlockNext = rest;
        rest->m_size = inf->m_size - used;
        inf->m_size = used;
        _MPFWorkAutoInf* prev = inf->m_pPrev;
        if (prev == nullptr) {
            man->m_pFreeHead = rest;
        } else {
            rest->m_pPrev = prev;
            prev->m_pNext = rest;
        }
        _MPFWorkAutoInf* next = inf->m_pNext;
        if (next == nullptr) {
            man->m_pFreeTail = rest;
        } else {
            rest->m_pNext = next;
            next->m_pPrev = rest;
        }
    }
    inf->m_flags = 2;
    inf->m_scale = 0.0f;
    if (m_pWorkTbl[m_workIdx] == nullptr) {
        m_pWorkTbl[m_workIdx] = inf;
        inf->m_pPrev = nullptr;
    } else {
        m_pWorkLast[m_workIdx]->m_pNext = inf;
        inf->m_pPrev = m_pWorkLast[m_workIdx];
    }
    m_pWorkLast[m_workIdx] = inf;
    inf->m_pNext = nullptr;
    if (m_autoFlags & 2) {
        inf->m_flags |= 0x200;
    } else if (m_autoFlags & 4) {
        inf->m_flags |= 0x20;
    } else if (m_autoFlags & 8) {
        inf->m_flags |= 0x40;
    }
    if (m_autoFlags & 0x80) {
        inf->m_scale = 1.0f;
    } else {
        inf->m_flags |= 0x80;
    }
    if (m_autoFlags & 0x400) {
        inf->m_flags |= 0x400;
    }
}

// Scatters each hit's colour by the entry's m_colRand and stocks the hit's height (m_pos[1]) with it; true when a
// stock filled and went to setHeMemWork.
bool DrMdoCtlMpfAuto::StockPoint() {
    m_col.a = m_alpha;
    bool full = false;
    for (int i = 0; i < m_hitNum; i++) {
        int range = m_pCurEntry->m_colRand;
        if (range != 0) {
            int width = range * 2;
            int ofs = range * 4;
            int r = m_pHit[i].m_col.r + static_cast<int>(mtRand()) % width * 4 - ofs;
            int g = m_pHit[i].m_col.g + static_cast<int>(mtRand()) % width * 4 - ofs;
            int b = m_pHit[i].m_col.b + static_cast<int>(mtRand()) % width * 4 - ofs;
            if (r > 0x1FF) {
                r = 0x1FF;
            } else if (r < 0) {
                r = 0;
            }
            if (g > 0x1FF) {
                g = 0x1FF;
            } else if (g < 0) {
                g = 0;
            }
            if (b > 0x1FF) {
                b = 0x1FF;
            } else if (b < 0) {
                b = 0;
            }
            m_col.r = r >> 1;
            m_col.g = g >> 1;
            m_col.b = b >> 1;
        } else {
            m_col.r = m_pHit[i].m_col.r >> 1;
            m_col.g = m_pHit[i].m_col.g >> 1;
            m_col.b = m_pHit[i].m_col.b >> 1;
        }
        m_pos[1] = m_pHit[i].m_y;
        full |= StockWorkPoint();
    }
    return full;
}

void DrMdoCtlMpfAuto::gridInstColiCalc() {
    m_hitNum = 0;
    for (int i = 0; i < m_buffNum; i++) {
        m_pCurBuff = m_pBuffTbl[i];
        if (m_pCurBuff->m_min[0] > m_pos[0] || m_pCurBuff->m_max[0] < m_pos[0] ||
            m_pCurBuff->m_min[1] > m_pos[2] || m_pCurBuff->m_max[1] < m_pos[2]) {
            continue;
        }
        if (m_pCurBuff->m_pTree != nullptr) {
            gridTreeColiCalc(m_pCurBuff->m_pTree);
        }
        if (m_pCurBuff->m_pInstData != nullptr) {
            seachInstTree(m_pCurBuff->m_pPosTree);
        }
    }
    StockPoint();
}

bool DrMdoCtlMpfAuto::gridChkColiRange(float maxX, float minX, float maxZ, float minZ) {
    int num = m_buffNum;
    m_rangeMin[0] = minX;
    m_rangeMin[1] = minZ;
    m_rangeMax[0] = maxX;
    m_rangeMax[1] = maxZ;
    _wkMpfAutoBuff** tbl = m_pBuffTbl;
    _wkMpfAutoBuff* buf;
    for (int i = 0; i < num; i++) {
        buf = tbl[i];
        m_pCurBuff = buf;
        if (buf->m_min[0] > maxX || buf->m_max[0] < minX || buf->m_min[1] > maxZ || buf->m_max[1] < minZ) {
            continue;
        }
        if (buf->m_pTree != nullptr) {
            if (gridColiRangeChk(buf->m_pTree)) {
                return true;
            }
            if (buf->m_pInstData == nullptr) {
                continue;
            }
        }
        if (gridColiInstPosRangeChk(buf->m_pPosTree)) {
            return true;
        }
    }
    return false;
}

DrMdoCtlMpfWork::DrMdoCtlMpfWork() {}

// Adds the current point (m_pos .. 0xF0) to the stocked height within m_stockRange of m_pos[1], or stocks a new
// height (up to five); a stock that grows past 0x600 bytes of work goes to setHeMemWork.
bool DrMdoCtlMpfAuto::StockWorkPoint() {
    if (m_stockCnt == 0) {
        m_stockHeight[0] = m_pos[1];
        memcpy(m_pStockBuf[0], m_pos, 0x20);
        m_stockNum[0] = 1;
        m_stockCnt++;
        return false;
    }
    m_stockCnt++;
    for (int i = 0; i < m_stockHeightNum; i++) {
        if (fabsf(m_pos[1] - m_stockHeight[i]) <= m_stockRange) {
            float rate = 1.0f / (m_stockNum[i] + 1);
            m_stockHeight[i] = m_pos[1] * rate + m_stockHeight[i] * (1.0f - rate);
            memcpy(m_pStockBuf[i] + m_stockNum[i] * 0x20, m_pos, 0x20);
            m_stockNum[i]++;
            if (m_stockNum[i] * 0x170UL >= 0x600) {
                return setHeMemWork(i);
            }
            return false;
        }
    }
    if (m_stockHeightNum > 4) {
        return false;
    }
    m_stockHeight[m_stockHeightNum] = m_pos[1];
    memcpy(m_pStockBuf[m_stockHeightNum], m_pos, 0x20);
    m_stockNum[m_stockHeightNum] = 1;
    m_stockHeightNum++;
    return false;
}

void DrMdoCtlMpfAuto::CreateDisplayList(DrCalcViewWork* view, DrMdoCtlMpfWork* work) {
    float fadeIn = DrMan::getIns()->m_mpfWindPower * (1.0f / 15.0f);
    float fadeOut = DrMan::getIns()->m_mpfWindPower * (1.0f / 15.0f);
    int num = m_pHeader->m_num;
    for (int i = 0; i < num; i++) {
        int obj = m_pEntry[i].m_objIdx;
        for (_MPFWorkAutoInf* inf = m_pWorkTbl[i]; inf != nullptr; inf = inf->m_pNext) {
            if (inf->m_num != 0 && !(inf->m_flags & 0x100)) {
                unsigned int flags = inf->m_flags;
                if (flags & 0x80) {
                    if ((flags & 0xC) == 4) {
                        if (view->m_gpuCheckAllVisible) {
                            inf->m_scale = 0.0f;
                        } else {
                            inf->m_scale -= fadeOut;
                        }
                        if (inf->m_scale <= 0.0f) {
                            inf->m_scale = 0.0f;
                        }
                    } else {
                        if (view->m_gpuCheckAllVisible) {
                            inf->m_scale = 1.0f;
                        } else {
                            inf->m_scale += fadeIn;
                        }
                        if (inf->m_scale >= 1.0f) {
                            flags &= ~0x80;
                            inf->m_scale = 1.0f;
                            inf->m_flags = flags;
                        }
                    }
                }
                float radius = (flags & 0x40) ? 56.5685425f
                             : (flags & 0x20) ? 28.2842712f
                             : !(flags & 0x200) ? 7.07106781f : 14.1421356f;
                if (view->m_clipPlane.clipTest(reinterpret_cast<const mm::Vec3&>(inf->m_pos), radius)) {
                    work->m_pObjWork[obj].m_objChk += inf->m_num;
                    const _MPFWorkAutoInf::Point* pt = reinterpret_cast<const _MPFWorkAutoInf::Point*>(inf + 1);
                    int n = inf->m_num;
                    for (int j = 0; j < n; j++, pt++) {
                        unsigned int addr = static_cast<unsigned int>(reinterpret_cast<unsigned long>(pt));
                        unsigned long idx = (addr >> 8) + (addr >> 16) + (addr >> 24);
                        work->m_pObjWork[obj].m_pHashCount[idx & 0xF]++;
                    }
                    _wkMpfAlphaObjBuff* buff = work->m_pObjWork[obj].m_pLastAlphaBuff;
                    (work->*buff->m_pAutoSet)(buff, inf, obj);
                }
            }
        }
    }
}

void DrMdoCtlMpfWork::changeMemWork(const MdsMpfObjData* objData) {
    m_pObjData = objData;
}

void DrMdoCtlMpfWork::auto_fastSet(_wkMpfObjBuff* buff, const _MPFWorkAutoInf* inf, int idx) {
    buff->m_pAutoList = (const _MPFWorkAutoInf**)m_pMpfMan->getFrameWork(sizeof(_wkMpfObjList));
    if (buff->m_pAutoList) {
        buff->m_pAutoList[0] = inf;
        buff->m_pAutoSet = &DrMdoCtlMpfWork::auto_countSet;
        buff->m_num = 1;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

void DrMdoCtlMpfWork::auto_alpha_fastSet(_wkMpfAlphaObjBuff* buff, const _MPFWorkAutoInf* inf, int idx) {
    buff->m_pAutoList = (const _MPFWorkAutoInf**)m_pMpfMan->getFrameWork(offsetof(_wkMpfAlphaObjList, m_alpha));
    if (buff->m_pAutoList) {
        buff->m_pAutoList[0] = inf;
        buff->m_pAutoSet = &DrMdoCtlMpfWork::auto_alpha_countSet;
        buff->m_num = 1;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

void DrMdoCtlMpfWork::mpf_fastSet(_wkMpfObjBuff* buff, const MdsMpfPosData* pos, int idx) {
    buff->m_pPosList = (const MdsMpfPosData**)m_pMpfMan->getFrameWork(sizeof(_wkMpfObjList));
    if (buff->m_pPosList) {
        buff->m_pPosList[0] = pos;
        buff->m_pPosSet = &DrMdoCtlMpfWork::mpf_countSet;
        buff->m_num = 1;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

void DrMdoCtlMpfWork::mpf_alpha_fastSet(_wkMpfAlphaObjBuff* buff, const MdsMpfPosData* pos, int idx, float alpha) {
    _wkMpfAlphaObjList* list = (_wkMpfAlphaObjList*)m_pMpfMan->getFrameWork(sizeof(_wkMpfAlphaObjList));
    buff->m_pPosList = list->m_pos;
    buff->m_pAlpha = list->m_alpha;
    if (buff->m_pPosList) {
        buff->m_pPosList[0] = pos;
        buff->m_pAlpha[0] = alpha * 255.0f;
        buff->m_pPosSet = &DrMdoCtlMpfWork::mpf_alpha_countSet;
        buff->m_num = 1;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}


void DrMdoCtlMpfWork::mpf_countSet(_wkMpfObjBuff* buff, const MdsMpfPosData* pos, int idx) {
    buff->m_pPosList[buff->m_num] = pos;
    if (buff->m_num++ >= 63) {
        buff->m_pPosSet = &DrMdoCtlMpfWork::mpf_changeSet;
    }
}

void DrMdoCtlMpfWork::mpf_changeSet(_wkMpfObjBuff* buff, const MdsMpfPosData* pos, int idx) {
    _wkMpfObjChunk* next = (_wkMpfObjChunk*)m_pMpfMan->getFrameWork(sizeof(_wkMpfObjChunk));
    if (next) {
        next->m_head.m_pPosList = next->m_list.m_pos;
        next->m_list.m_pos[0] = pos;
        next->m_head.m_num = 1;
        next->m_head.m_pPosSet = &DrMdoCtlMpfWork::mpf_countSet;
        next->m_head.m_pNext = 0;
        m_pObjWork[idx].m_pLastBuff = &next->m_head;
        buff->m_pNext = &next->m_head;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

void DrMdoCtlMpfWork::auto_countSet(_wkMpfObjBuff* buff, const _MPFWorkAutoInf* inf, int idx) {
    buff->m_pAutoList[buff->m_num] = inf;
    if (buff->m_num++ >= 63) {
        buff->m_pAutoSet = &DrMdoCtlMpfWork::auto_changeSet;
    }
}

void DrMdoCtlMpfWork::auto_changeSet(_wkMpfObjBuff* buff, const _MPFWorkAutoInf* inf, int idx) {
    _wkMpfObjChunk* next = (_wkMpfObjChunk*)m_pMpfMan->getFrameWork(sizeof(_wkMpfObjChunk));
    if (next) {
        next->m_head.m_pAutoList = next->m_list.m_auto;
        next->m_list.m_auto[0] = inf;
        next->m_head.m_num = 1;
        next->m_head.m_pAutoSet = &DrMdoCtlMpfWork::auto_countSet;
        next->m_head.m_pNext = 0;
        m_pObjWork[idx].m_pLastBuff = &next->m_head;
        buff->m_pNext = &next->m_head;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

void DrMdoCtlMpfWork::mpf_alpha_countSet(_wkMpfAlphaObjBuff* buff, const MdsMpfPosData* pos, int idx, float alpha) {
    buff->m_pPosList[buff->m_num] = pos;
    buff->m_pAlpha[buff->m_num] = alpha * 255.0f;
    if (buff->m_num++ >= 15) {
        buff->m_pPosSet = &DrMdoCtlMpfWork::mpf_alpha_changeSet;
    }
}

void DrMdoCtlMpfWork::mpf_alpha_changeSet(_wkMpfAlphaObjBuff* buff, const MdsMpfPosData* pos, int idx, float alpha) {
    _wkMpfAlphaObjChunk* next = (_wkMpfAlphaObjChunk*)m_pMpfMan->getFrameWork(sizeof(_wkMpfAlphaObjChunk));
    if (next) {
        next->m_head.m_pPosList = next->m_list.m_pos;
        next->m_head.m_pAlpha = next->m_list.m_alpha;
        next->m_list.m_pos[0] = pos;
        next->m_list.m_alpha[0] = alpha * 255.0f;
        next->m_head.m_num = 1;
        next->m_head.m_pNext = 0;
        next->m_head.m_pPosSet = &DrMdoCtlMpfWork::mpf_alpha_countSet;
        m_pObjWork[idx].m_pLastAlphaBuff = &next->m_head;
        buff->m_pNext = &next->m_head;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

void DrMdoCtlMpfWork::auto_alpha_countSet(_wkMpfAlphaObjBuff* buff, const _MPFWorkAutoInf* inf, int idx) {
    buff->m_pAutoList[buff->m_num] = inf;
    if (buff->m_num++ >= 15) {
        buff->m_pAutoSet = &DrMdoCtlMpfWork::auto_alpha_changeSet;
    }
}

void DrMdoCtlMpfWork::auto_alpha_changeSet(_wkMpfAlphaObjBuff* buff, const _MPFWorkAutoInf* inf, int idx) {
    _wkMpfAlphaObjChunk* next = (_wkMpfAlphaObjChunk*)m_pMpfMan->getFrameWork(offsetof(_wkMpfAlphaObjChunk, m_list.m_alpha));
    if (next) {
        next->m_head.m_pAutoList = next->m_list.m_auto;
        next->m_list.m_auto[0] = inf;
        next->m_head.m_num = 1;
        next->m_head.m_pNext = 0;
        next->m_head.m_pAutoSet = &DrMdoCtlMpfWork::auto_alpha_countSet;
        m_pObjWork[idx].m_pLastAlphaBuff = &next->m_head;
        buff->m_pNext = &next->m_head;
    } else {
        m_pObjWork[idx].m_objChk--;
        buff->m_num = 0;
    }
}

// m_stateFlags bits 0..5 select the passes an object draws in (bit 3 light pre-pass, bit 1 GBuff, bit 2
// refraction, bit 5 special alpha, bit 6 thickness, bit 20 z pre-pass, bits 25..27 last/fast/cloud-back alpha).
DrMdoCtlNom::~DrMdoCtlNom() {
    if ((m_ctlFlags & 0x100) && m_viewNum == 0) {
        m_pDrMan->m_pixlMan->m_shadowCacheMan->delShadowCacheUpdate();
    }
    releaseNom();
}

void DrMdoCtlNom::setDeleteCall(int index) {
    m_dispFlags |= 8 << index;
    if (m_cldMdlData != nullptr) {
        m_cldMdlData->setCallDisp(false);
    }
    if (m_light != nullptr) {
        m_light->setDisp(false);
    }
}

void DrMdoCtlNom::setDisp(bool disp) {
    if (disp) {
        m_dispFlags |= 0x1;
    } else {
        m_dispFlags &= ~0x1;
    }
    if (m_light != nullptr) {
        m_light->setDisp(disp);
    }
}

void DrMdoCtlNom::update() {
    stmResSetup();
    if (m_ctlFlags2 & 0x40000) {
        m_ctlFlags2 &= ~0x30000;
    } else {
        unsigned int bit = 0x10000 << DrMan::s_nDblIdx;
        if (m_ctlFlags2 & bit) {
            m_ctlFlags2 &= ~bit;
            m_singleAlpha = m_alpha[DrMan::s_nDblIdx];
        }
    }
    updateNom();
    DrMdlMan* mdlMan = m_pDrMan->m_mdlMan;
    if (m_stateFlags & 0x8000) {
        mdlMan->m_pPassReq[0] = true;
    }
    if (m_stateFlags & 0x10000) {
        mdlMan->m_pPassReq[1] = true;
    }
    if (m_stateFlags & 0x40000) {
        mdlMan->m_pPassReq[7] = true;
    }
    if (m_stateFlags & 0x8) {
        mdlMan->m_pPassReq[3] = true;
    }
    if (m_stateFlags & 0x4) {
        mdlMan->m_pPassReq[4] = true;
    }
    if (m_stateFlags & 0x100) {
        mdlMan->m_pPassReq[8] = true;
    }
    if (m_stateFlags & 0x200) {
        mdlMan->m_pPassReq[9] = true;
    }
    if (m_cldMdlData != nullptr) {
        m_cldMdlData->setCallDisp(true);
    }
}

void DrMdoCtlNom::callShadowCacheUpdate(unsigned long bits) {
    m_shadowCacheBits &= ~bits;
}

void DrMdoCtlNom::updateRimBloomCalcUniformBlock() {
    MdoRimBloomWrk* wrk = getRimBloomWrk(2);
    if (wrk == nullptr) {
        return;
    }
    grlib::CGLibDblUniformBlock* block = m_pWrkMatRes->m_pRimBloomUniformArray->m_pArray;
    bool on = wrk->m_emissive > 0.0f || wrk->m_blackRatio > 0.0f;
    mm::Vec4* buf = reinterpret_cast<mm::Vec4*>(block->getBuff());
    if (m_mdlFlags & 0x100) {
        float rate = m_rimBloomFade + m_rimBloomFade;
        rate = rate < 0.0f ? 0.0f : rate;
        rate = rate > 1.0f ? 1.0f : rate;
        float inv = 1.0f - rate;
        if (on) {
            buf[0] = mm::Vec4(rate * 0.1f + inv * wrk->m_color.r, rate * 0.1f + inv * wrk->m_color.g,
                              rate * 0.1f + inv * wrk->m_color.b, 0.0f);
            buf[1] = mm::Vec4(rate * 2.0f + inv * wrk->m_power, rate * 1.0f + inv * wrk->m_blackRatio,
                              rate * 1.0f + inv * wrk->m_emissive, 0.0f);
        } else {
            buf[0] = mm::Vec4(inv * 0.0f + rate * 0.1f, inv * 0.0f + rate * 0.1f, inv * 0.0f + rate * 0.1f, 0.0f);
            buf[1] = mm::Vec4(inv * 1.0f + rate * 2.0f, inv * 0.0f + rate * 1.0f, inv * 0.0f + rate * 1.0f, 0.0f);
        }
        on = true;
    } else {
        buf[0] = mm::Vec4(wrk->m_color.r, wrk->m_color.g, wrk->m_color.b, 0.0f);
        buf[1] = mm::Vec4(wrk->m_power, wrk->m_blackRatio, wrk->m_emissive, 0.0f);
    }
    block->updateData();
    m_shdObj->setDecShdParm(wrk->m_decShdIdx, on ? 1 : 2);
}

void DrMdoCtlNom::nomCallRender(int pass) {
    // by pass: the createWeightVtx type and m_renderTech (proposed names, not the original's: the symbols leave
    // them unnamed, lbl_71009D4910 and lbl_71009D4916)
    static const unsigned char s_weightType[] = {0, 3, 2, 4, 1, 1};
    static const short s_renderTech[] = {0, 7, 8, 4, 1, 1};
    if (m_nodeMax != 0) {
        grlib::CGLibCtlShader::setMemoryBarrierBit(1);
        if (pass == 0) {
            unsigned int dispBits = m_lodObj->m_dispBits;
            if (m_vtxMesh != nullptr) {
                dispBits |= m_vtxMesh->isRender();
            }
            createWeightVtx(0, m_ctlFlags2, dispBits, false);
            createWeightVtx(0, m_ctlFlags2, dispBits, true);
        } else {
            createWeightVtx(s_weightType[pass], m_ctlFlags2, m_lodObj->m_dispBits, false);
        }
        grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
    }
    if (pass == 0 && !(m_stateFlags & 0x200000)) {
        DrAPCache* cache = m_pDrMan->m_apCache;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        cache->beginMdlZRender();
        zPrePassRender();
        cache->endMdlZRender();
    }
    m_renderPass = pass;
    m_renderTech = s_renderTech[pass];
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pWrkMatRes->m_pVertex->beginVertexSetup();
    const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop;
    for (int i = 0; i < m_pWrkMatRes->m_mdlTopNum; i++, top++) {
        DrResChkList* chk = *(m_passChk[i] + m_renderPass);
        if (chk != nullptr) {
            nomRender(top, chk);
        }
    }
}

void DrMdoCtlNom::lastAlphaCallRender() {
    if (m_nodeMax != 0) {
        grlib::CGLibCtlShader::setMemoryBarrierBit(1);
        createWeightVtx(1, m_ctlFlags2, m_lodObj->m_dispBits, false);
        grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
    }
    m_renderPass = 4;
    m_renderTech = 1;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pWrkMatRes->m_pVertex->beginVertexSetup();
    const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop;
    for (int i = 0; i < m_pWrkMatRes->m_mdlTopNum; i++, top++) {
        if (m_alphaSort->m_lastChk[i] != nullptr) {
            nomRender(top, m_alphaSort->m_lastChk[i]);
        }
    }
}

void DrMdoCtlNom::fastAlphaCallRender() {
    if (m_nodeMax != 0) {
        grlib::CGLibCtlShader::setMemoryBarrierBit(1);
        createWeightVtx(1, m_ctlFlags2, m_lodObj->m_dispBits, false);
        grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
    }
    m_renderPass = 4;
    m_renderTech = 1;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pWrkMatRes->m_pVertex->beginVertexSetup();
    const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop;
    for (int i = 0; i < m_pWrkMatRes->m_mdlTopNum; i++, top++) {
        if (m_alphaSort->m_fastChk[i] != nullptr) {
            nomRender(top, m_alphaSort->m_fastChk[i]);
        }
    }
}

void DrMdoCtlNom::cldBackAlphaCallRender() {
    if (m_nodeMax != 0) {
        grlib::CGLibCtlShader::setMemoryBarrierBit(1);
        createWeightVtx(1, m_ctlFlags2, m_lodObj->m_dispBits, false);
        grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
    }
    m_renderPass = 4;
    m_renderTech = 1;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pWrkMatRes->m_pVertex->beginVertexSetup();
    const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop;
    for (int i = 0; i < m_pWrkMatRes->m_mdlTopNum; i++, top++) {
        if (m_alphaSort->m_cldBackChk[i] != nullptr) {
            nomRender(top, m_alphaSort->m_cldBackChk[i]);
        }
    }
}

void DrMdoCtlNom::shadowMapDirRender(int idx) {
    m_pDrMan->m_pixlMan->setupShadowUnifrom(idx);
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pWrkMatRes->m_pVertex->beginVertexSetup();
    const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop;
    for (int i = 0; i < m_pWrkMatRes->m_mdlTopNum; i++, top++) {
        DrResChkList* chk = m_passChk[i][6];
        if (chk != nullptr) {
            const MdsMdlInfoHeader* infos =
                reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs);
            bool hasNode = m_nodeMax != 0;
            for (;;) {
                const MdsMdlInfoHeader* info = &infos[chk->m_idx];
                const DrResMdoMeshParts* parts;
                if ((info->m_flags & 0x100) && ((parts = (m_mesh->m_parts + info->m_meshNo))->m_flags & 1)) {
                    partsShadowDirRender(info, parts->m_triIdx, 0);
                } else {
                    partsShadowDirRender(info, 0, info->m_shaderOfs + hasNode);
                }
                unsigned int next = chk->m_next;
                if (next == 0) {
                    break;
                }
                chk = &m_chkPool[next - 1];
            }
        }
    }
}

void DrMdoCtlNom::shadowCacheOnlyRender() {
    if ((m_stateFlags & 0x10000000) && (m_stateFlags & 0x3800)) {
        DrPixlMan* pixl = m_pDrMan->m_pixlMan;
        if ((!(m_stateFlags & 0x80000000) || pixl->m_objTbl->m_shadowMan->clipDirShadowChk(m_center, m_length, true)) &&
            m_viewNum == 0 && !m_pDrMan->m_shadowRenderOff) {
            if (!(m_mdlFlags & 0x8)) {
                if (m_nodeMax != 0) {
                    calcOfsMat();
                }
                updateMdlUniformBlock();
                m_mdlFlags |= 0x8;
            }
            updateFlagWaveTbl();
            if (m_nodeMax != 0) {
                grlib::CGLibCtlShader::setMemoryBarrierBit(1);
                createWeightVtx(0, m_ctlFlags2, m_lodObj->m_dispBits, false);
                grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
            }
            pixl->shadowDirBegin();
            if (m_stateFlags & 0x800) {
                pixl->setShadowDirRenderTarget(0);
                shadowMapDirRender(0);
            }
            if (m_stateFlags & 0x1000) {
                pixl->setShadowDirRenderTarget(1);
                shadowMapDirRender(1);
            }
            if (m_stateFlags & 0x2000) {
                pixl->setShadowDirRenderTarget(2);
                shadowMapDirRender(2);
            }
            pixl->shadowDirEnd();
        }
    }
}

void DrMdoCtlNom::shadowRender() {
    if (!(m_mdlFlags & 0x20) || !(m_ctlFlags & 0x1)) {
        return;
    }
    DrPixlShadowObj* shadow = m_pDrMan->m_pixlMan->m_shadowObj;
    if (!(m_mdlFlags & 0x40) && shadow->m_active == 1) {
        return;
    }
    bool on = (m_ctlFlags & 0x100) ? shadow->m_lightObj->isBaseMapShadow() : shadow->m_lightObj->isCharShadow();
    if (on && shadow->clipTypeChk(m_center, m_length) != 0) {
        if (!(m_mdlFlags & 0x8)) {
            if (m_nodeMax != 0) {
                calcOfsMat();
            }
            updateMdlUniformBlock();
            m_mdlFlags |= 0x8;
        }
        updateFlagWaveTbl();
        if (m_nodeMax != 0) {
            grlib::CGLibCtlShader::setMemoryBarrierBit(1);
            createWeightVtx(0, m_ctlFlags2, m_lodObj->m_dispBits, false);
            grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
        }
        shadow->renderSetup();
        m_renderPass = 6;
        m_renderTech = 0;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        if (shadow->m_active == 1) {
            m_bindFlags[0] |= 4;
        }
        const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop;
        for (int i = 0; i < m_pWrkMatRes->m_mdlTopNum; i++, top++) {
            if (*(m_passChk[i] + m_renderPass) != nullptr) {
                shwRender(top, *(m_passChk[i] + m_renderPass));
            }
        }
    }
}

void DrMdoCtlNom::callNomSetupRender() {
    if ((m_ctlFlags & 0x1) && m_morpObj != nullptr && (m_lodObj->m_flags & 0x2)) {
        m_morpObj->update(m_pWrkMatRes, m_etcParams);
    }
}

void DrMdoCtlNom::callZSortNomZpreePassRender() {
    if ((m_stateFlags & 0x300000) == 0x300000) {
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        if (m_nodeMax != 0) {
            grlib::CGLibCtlShader::setMemoryBarrierBit(1);
            createWeightVtx(6, m_ctlFlags2, m_lodObj->m_dispBits, false);
            grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
        }
        zPrePassRender();
    }
}

void DrMdoCtlNom::callZSortThicknessRenderFirst() {
    if (m_stateFlags & 0x40) {
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        if (m_nodeMax != 0) {
            grlib::CGLibCtlShader::setMemoryBarrierBit(1);
            createWeightVtx(5, m_ctlFlags2, m_lodObj->m_dispBits, false);
            grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
        }
        thicknessRender(true);
    }
}

void DrMdoCtlNom::callZSortThicknessRenderSecond() {
    if (m_stateFlags & 0x40) {
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        if (m_nodeMax != 0) {
            grlib::CGLibCtlShader::setMemoryBarrierBit(1);
            createWeightVtx(5, m_ctlFlags2, m_lodObj->m_dispBits, false);
            grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
        }
        thicknessRender(false);
    }
}

void DrMdoCtlNom::callZSortNomRender() {
    if (m_stateFlags & 0x1) {
        nomCallRender(0);
        if (m_vtxMesh != nullptr) {
            m_vtxMesh->stmRender(m_nodeMax != 0);
        }
        if ((m_stateFlags & 0x3800) && m_viewNum == 0 && !m_pDrMan->m_shadowRenderOff) {
            DrPixlMan* pixl = m_pDrMan->m_pixlMan;
            if (!(m_stateFlags & 0x80000000) || !pixl->m_objTbl->m_shadowMan->clipDirShadowChk(m_center, m_length, true)) {
                pixl->shadowDirBegin();
                if (m_stateFlags & 0x800) {
                    pixl->setShadowDirRenderTarget(0);
                    shadowMapDirRender(0);
                }
                if (m_stateFlags & 0x1000) {
                    pixl->setShadowDirRenderTarget(1);
                    shadowMapDirRender(1);
                }
                if (m_stateFlags & 0x2000) {
                    pixl->setShadowDirRenderTarget(2);
                    shadowMapDirRender(2);
                }
                pixl->shadowDirEnd();
            }
        }
    }
}

void DrMdoCtlNom::callZSortNomAlphaRender() {
    if (m_stateFlags & 0x10) {
        nomCallRender(4);
    }
    if (m_vtxMesh != nullptr) {
        m_vtxMesh->alpRender();
    }
}

void DrMdoCtlNom::callZSortGBuffRender() {
    if (m_stateFlags & 0x2) {
        nomCallRender(1);
    }
}

void DrMdoCtlNom::callZSortNomRefractionRender() {
    if (m_stateFlags & 0x4) {
        nomCallRender(2);
    }
}

void DrMdoCtlNom::callZSortLightPrePassRender() {
    if (m_stateFlags & 0x8) {
        nomCallRender(3);
    }
}

void DrMdoCtlNom::callZSortNomSpAlphaRender() {
    if (m_stateFlags & 0x20) {
        nomCallRender(5);
    }
}

void DrMdoCtlNom::callLastAlphaNomRender() {
    if (m_stateFlags & 0x2000000) {
        lastAlphaCallRender();
    }
}

void DrMdoCtlNom::callFastAlphaNomRender() {
    if (m_stateFlags & 0x4000000) {
        fastAlphaCallRender();
    }
}

void DrMdoCtlNom::callCldBackAlphaNomRender() {
    if (m_stateFlags & 0x8000000) {
        cldBackAlphaCallRender();
    }
}

void DrMdoCtlNom::occRender() {
    if (m_mdlFlags & 0x2) {
        m_pDrMan->m_pixlMan->m_occQuery->occRenderAABB(m_queryAcc, m_center, m_extent);
    }
    if (m_mdlFlags & 0x4) {
        MdoWrkMatRes::InstOcc* occ = m_pWrkMatRes->m_pInstOcc;
        m_pDrMan->m_pixlMan->m_occQuery->occRenderPosAABB(occ->m_queryAcc, occ->m_mtx, occ->m_bits, occ->m_num);
    }
}

bool DrMdoCtlNom::cloneMdlObj(DrMdlObj* obj) {
    bool cloned = DrMdoNomClone::cloneMdlObj(static_cast<DrMdoCtlNom*>(obj), this);
    if (cloned) {
        m_dispFlags &= ~0x60;
    }
    return cloned;
}

void DrMdoCtlNom::createAfterImage(float a0, float a1, float a2, const mm::Col3& c0, float a3, float a4, float a5,
                                   const mm::Col3& c1, float a6, float a7, float a8) {
    if (m_afterImage != nullptr) {
        m_afterImage->m_flags |= 1 << DrMan::s_nDblStockIdx;
    }
    DrMdoNomAfterImage* image = new (DrMan::getIns()->m_workHandle, nullptr, 0, 4, false) DrMdoNomAfterImage;
    image->create(this, a0, a1, a2, c0, a3, a4, a5, c1, a6, a7, a8);
    m_afterImageStock[DrMan::s_nDblStockIdx] = image;
}

void DrMdoCtlNom::releaseAfterImage() {
    if (m_afterImage != nullptr) {
        m_afterImage->m_flags |= 1 << DrMan::s_nDblStockIdx;
    }
    if (m_afterImageStock[DrMan::s_nDblMemIdx] != nullptr) {
        m_afterImageStock[DrMan::s_nDblMemIdx]->m_flags |= 1 << DrMan::s_nDblStockIdx;
    }
    if (m_afterImageStock[DrMan::s_nDblStockIdx] != nullptr) {
        delete m_afterImageStock[DrMan::s_nDblStockIdx];
        m_afterImageStock[DrMan::s_nDblStockIdx] = nullptr;
    }
}

void DrMdoCtlPos::releasePos() {
    m_pDrMan->m_pixlMan->m_shadowCacheMan->delShadowCacheUpdate();
    for (int i = 0; i < m_posNum; i++) {
        m_pPosList[i].~DrResMdoPos();
    }
    m_posNum = 0;
    m_instAnm.release();
    if (m_pAddList != nullptr) {
        m_pAddList->release();
        m_pAddList = nullptr;
    }
    if (m_instMdlInfo != nullptr) {
        DrResMdoInstMdlInfo::release(m_instMdlInfo);
    }
    m_pSortPos->~DrResMdoSortPos();
    for (int i = 0; i < m_buffNum; i++) {
        if (m_ppBuffList[i] != nullptr) {
            mtl::MemManager::deallocate(m_ppBuffList[i], 0, false);
            m_ppBuffList[i] = nullptr;
        }
    }
    if (m_pWorkB != nullptr) {
        mtl::MemManager::deallocate(m_pWorkB, 0, false);
        m_pWorkB = nullptr;
    }
    if (m_pWorkA != nullptr) {
        mtl::MemManager::deallocate(m_pWorkA, 0, false);
        m_pWorkA = nullptr;
    }
    releaseMat();
}

DrMdoCtlPos::~DrMdoCtlPos() {
    releasePos();
}

void DrMdoCtlPos::update() {
    if (m_ctlFlags2 & 0x40000) {
        m_ctlFlags2 &= ~0x30000;
    } else {
        unsigned int bit = 0x10000 << DrMan::s_nDblIdx;
        if (m_ctlFlags2 & bit) {
            m_ctlFlags2 &= ~bit;
            m_singleAlpha = m_alpha[DrMan::s_nDblIdx];
        }
    }
    if (m_mdlFlags & 8) {
        m_ctlFlags |= 0x4000000;
    } else {
        m_ctlFlags &= ~0x4000000;
    }
    m_stateFlags = 0;
    m_mdlFlags = 0;
    updateMdlPos();
    createMdlList();
    DrMdlMan* mdlMan = m_pDrMan->m_mdlMan;
    if (m_stateFlags & 0x8000) {
        mdlMan->m_pPassReq[0] = true;
    }
    if (m_stateFlags & 0x10000) {
        mdlMan->m_pPassReq[1] = true;
    }
    if (m_stateFlags & 0x20000) {
        mdlMan->m_pPassReq[2] = true;
    }
    if (m_stateFlags & 0x40000) {
        mdlMan->m_pPassReq[7] = true;
    }
    if (m_stateFlags & 0x8) {
        mdlMan->m_pPassReq[3] = true;
    }
    if (m_stateFlags & 0x4) {
        mdlMan->m_pPassReq[4] = true;
    }
    if (m_stateFlags & 0x100) {
        mdlMan->m_pPassReq[8] = true;
    }
    if (m_stateFlags & 0x200) {
        mdlMan->m_pPassReq[9] = true;
    }
}

void DrMdoCtlPos::dispOffUpdate() {
    if (m_instMdlInfo != nullptr) {
        m_pViewWork = m_pDrMan->m_calcMan->m_pViewWork;
        DrResMdlInstMdlArg arg;
        arg.m_viewPos = &m_pViewWork->m_viewPos;
        arg.m_gpuCheckAllVisible = m_pViewWork->m_gpuCheckAllVisible;
        arg.m_disp = false;
        arg.m_viewNum = m_viewNum;
        arg.pad_8 = nullptr;
        arg.m_speed = m_speed;
        m_instMdlInfo->update(arg);
    }
}

void DrMdoCtlPos::resourceInit() {
    setupResource(false);
    if (m_pWrkMatRes->m_texNum != 0) {
        DrMdoTextureMan* man = m_pDrMan->m_mdlMan->m_textureMan;
        const unsigned char* data = m_pWrkMatRes->m_pTexData;
        DrResMdoTexList* list;
        for (list = man->m_texList.m_pHead; list != nullptr; list = list->m_pNext) {
            if (list->m_res == data) {
                list->m_refCount++;
                goto found;
            }
        }
        list = new (man->m_pDrMan->m_resHandle, nullptr, 0, 4, false) DrResMdoTexList(data);
        if (list != nullptr) {
            man->m_texList.pushBack(list);
        }
    found:
        m_pWrkMatRes->m_pTexList = list;
        for (int i = 0; i < m_pWrkMatRes->m_pTexList->m_texNum; i++) {
            m_pWrkMatRes->m_ppTexture[i] = m_pWrkMatRes->m_pTexList->getTexObj(i);
        }
    }
    m_pDrMan->m_pixlMan->m_shadowCacheMan->addShadowCacheUpdate(false);
    pad_24C = 0;
}

void DrMdoCtlPos::setDeleteCall(int index) {
    m_dispFlags |= 8 << index;
    if (m_instMdlInfo != nullptr) {
        m_instMdlInfo->releaseCall();
    }
    if (m_cpPlane != nullptr) {
        m_cpPlane->release();
        m_cpPlane = nullptr;
    }
}

void DrMdoCtlPos::callShadowCacheUpdate(unsigned long bits) {
    m_shadowCacheBits &= ~bits;
    if (m_shadowCacheReq & bits) {
        m_shadowCacheReq = 0;
        m_shadowCacheCount = 0;
    }
}

bool DrMdoCtlPos::chankRenderMdl(const MdsPosRangeTreeData* tree, MdoArgInst& arg) {
    const DrCalcViewWork* view = m_pViewWork;
    float dx = view->m_viewPos.x - tree->m_center[0];
    float dy = view->m_viewPos.y - tree->m_center[1];
    float dz = view->m_viewPos.z - tree->m_center[2];
    if (dx * dx + dy * dy + dz * dz > tree->m_distSq) {
        return false;
    }
    if (!view->m_clipPlane.clipTest(tree->center(), tree->m_radius)) {
        return false;
    }
    bool rendered = false;
    int childNum = tree->m_childNum;
    if (childNum != 0) {
        const unsigned short* child = tree->childTbl(m_pPosHead);
        for (int i = 0; i < childNum; i++) {
            rendered |= chankRenderMdl(m_pRangeTree + child[i], arg);
        }
    }
    if (tree->m_mdlNum != 0) {
        rendered |= clipRenderMdl(tree, arg);
    }
    return rendered;
}

void DrMdoCtlPos::chankShadowRenderMdl(const MdsPosRangeTreeData* tree, DrPixlShadowCacheObj& cache) {
    if (!cache.clipTest(tree->center(), tree->m_radius)) {
        return;
    }
    int childNum = tree->m_childNum;
    if (childNum != 0) {
        const unsigned short* child = tree->childTbl(m_pPosHead);
        for (int i = 0; i < childNum; i++) {
            chankShadowRenderMdl(m_pRangeTree + child[i], cache);
        }
    }
    if (tree->m_mdlNum != 0) {
        clipShadowRenderMdl(tree, cache);
    }
}

void DrMdoCtlPos::nomTreeShadowRenderMdl(const MdsPosRangeTreeData* tree, DrPixlShadowObj* shadow) {
    const DrCalcViewWork* view = m_pViewWork;
    float dx = view->m_viewPos.x - tree->m_center[0];
    float dy = view->m_viewPos.y - tree->m_center[1];
    float dz = view->m_viewPos.z - tree->m_center[2];
    if (dx * dx + dy * dy + dz * dz > tree->m_distSq) {
        return;
    }
    if (!shadow->clipTypeChk(tree->center(), tree->m_radius)) {
        return;
    }
    int childNum = tree->m_childNum;
    if (childNum != 0) {
        const unsigned short* child = tree->childTbl(m_pPosHead);
        for (int i = 0; i < childNum; i++) {
            nomTreeShadowRenderMdl(m_pRangeTree + child[i], shadow);
        }
    }
    if (tree->m_mdlNum != 0) {
        nomTreeListShadowRenderMdl(tree, shadow);
    }
}

void DrMdoSetup::createUniformBlock(const MdsMatInfoHeader* info, DrResMdoMat* mat) {
    MdoWrkMatRes* res = m_pWrkMatRes;
    const MdsMatInfoHeader::TechEntry* entry =
        reinterpret_cast<const MdsMatInfoHeader::TechEntry*>(res->m_pMatData + info->m_techEntryOfs);
    const MdsMatTechnique* tech = &res->m_pTechnique[entry->m_techIdx];
    if (tech->m_varTblNum == 0) {
        return;
    }
    switch (entry->m_type) {
    case 0:
    case 7:
    case 8:
        m_renderPass = 0;
        break;
    default:
        m_renderPass = 4;
        break;
    }
    int num = tech->m_varTblNum;
    const MdsMatVariableTbl* var = reinterpret_cast<const MdsMatVariableTbl*>(res->m_pTechData + tech->m_varTblOfs);
    grlib::CGLibDblUniformBlock* block = &res->m_pMatUniformArray->m_pArray[entry->m_uniformIdx];
    float* buf = reinterpret_cast<float*>(block->getBuff());
    for (int i = 0; i < num; i++) {
        buf += (this->*s_pStockMaterial[var->m_stockIdx])(buf, mat, info, var);
        var++;
    }
    block->updateData();
}

void DrMdoCtlPos::shadowRender() {
    m_renderTech = 0;
    m_renderPass = 6;
    DrPixlShadowObj* shadow = m_pDrMan->m_pixlMan->m_shadowObj;
    if (shadow->m_lightObj->isInstMapShadow()) {
        m_pViewWork = m_pDrMan->m_calcMan->m_pViewWork;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        const PosHead* head = m_pPosHead;
        for (int i = 0; i < head->m_treeNum; i++) {
            nomTreeShadowRenderMdl(&m_pRangeTree[i], shadow);
        }
    }
}

bool DrMdoCtlPos::shadowCacheRender(DrPixlShadowCacheObj& cache) {
    if (m_shadowCacheBits & cache.m_cacheBit) {
        return true;
    }
    if (m_shadowCacheReq == 0) {
        m_shadowCacheReq = cache.m_cacheBit;
        m_shadowCacheCount = 0;
    } else if (!(m_shadowCacheReq & cache.m_cacheBit)) {
        m_shadowCacheReq = cache.m_cacheBit;
        m_shadowCacheCount = 0;
        return true;
    }
    if (m_pWrkMatRes->m_pVertex != nullptr) {
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        m_renderTech = 0;
        m_renderPass = 6;
        if (cache.m_flags & 0x10) {
            m_mdlFlags |= 0x80;
        }
        m_shadowRange = DrPixlShadowCacheMan::SHADOW_CHECK_RANGE_TBL[static_cast<unsigned int>(cache.m_level)];
        const PosHead* head = m_pPosHead;
        for (int i = 0; i < head->m_treeNum; i++) {
            chankShadowRenderMdl(&m_pRangeTree[i], cache);
        }
        m_mdlFlags &= ~0x80;
    }
    m_shadowCacheCount = 0;
    m_shadowCacheReq = 0;
    if (!(cache.m_flags & 8)) {
        m_shadowCacheBits |= cache.m_cacheBit;
    }
    return true;
}

void DrMdoCtlPos::callZpreePassRenderPosAll() {
    if (m_stateFlags & 0x100000) {
        createZBuffRenderDisplayList();
    }
}

void DrMdoCtlPos::callThicknessRenderFirstPosAll() {
    if (m_stateFlags & 0x40) {
        createThicknessRenderDisplayListSub(true);
    }
}

void DrMdoCtlPos::callThicknessRenderSecondPosAll() {
    if (m_stateFlags & 0x40) {
        createThicknessRenderDisplayListSub(false);
    }
}

void DrMdoCtlPos::callRenderPosAll() {
    if (m_stateFlags & 0x1) {
        m_renderPass = 0;
        m_renderTech = 0;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        callPosRender(0x1);
    }
}

void DrMdoCtlPos::callRefractionRenderPosAll() {
    if (m_stateFlags & 0x4) {
        m_renderPass = 2;
        m_renderTech = 8;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        callPosRender(0x4);
    }
}

void DrMdoCtlPos::callGBuffRenderPosAll() {
    if (m_stateFlags & 0x2) {
        m_renderPass = 1;
        m_renderTech = 7;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        callPosRender(0x8);
    }
}

void DrMdoCtlPos::callLightPrePassRenderPosAll() {
    if (m_stateFlags & 0x8) {
        m_renderPass = 3;
        m_renderTech = 4;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        callPosRender(0x20);
    }
}

void DrMdoCtlPos::callAlphaRenderPosAll() {
    if (m_stateFlags & 0x10) {
        m_renderPass = 4;
        m_renderTech = 1;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        callPosRender(0x2);
    }
}

void DrMdoCtlPos::callSpAlphaRenderPosAll() {
    if (m_stateFlags & 0x20) {
        m_renderPass = 5;
        m_renderTech = 1;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        callPosRender(0x40);
    }
}

void DrMdoCtlSeam::releaseSeam() {
    resourceRelease();
    m_instAnm.release();
    if (m_instMdlInfo != nullptr) {
        DrResMdoInstMdlInfo::release(m_instMdlInfo);
    }
    if (m_posAddList != nullptr) {
        m_posAddList->release();
        m_posAddList = nullptr;
    }
    if (m_sortSeamAll != nullptr) {
        m_sortSeamAll->~DrResMdoSortSeamAll();
    }
    if (m_sortSeamEnvMap != nullptr) {
        m_sortSeamEnvMap->~DrResMdoSortSeamEnvMap();
    }
    m_sortSeamAll = nullptr;
    m_sortSeamEnvMap = nullptr;
    m_texturePool.release();
    m_texListPool.release();
    m_vertexPool.release();
    m_coliPool.release();
    m_basePool.release();
    m_lowPool.release();
    m_instPool.release();
    m_mpfPool.release();
    m_envPool.release();
    m_lightPool.release();
    m_memMan.releaseMem();
    if (m_triUniformArray != nullptr) {
        m_triUniformArray->release();
        m_triUniformArray = nullptr;
    }
    DevGraph::releaseMemPoolBuffer(m_memPoolBuf);
    if (m_workBuf != nullptr) {
        mtl::MemManager::deallocate(m_workBuf, 0, false);
        m_workBuf = nullptr;
    }
    if (m_memPoolBuf != nullptr) {
        mtl::MemManager::deallocate(m_memPoolBuf, 0, false);
        m_memPoolBuf = nullptr;
    }
    m_seamRead.release();
    m_pDrMan->m_mdlMan->delMpfObj();
    if (m_pDrMan->m_cloudMan != nullptr) {
        m_pDrMan->m_cloudMan->m_rate = 1.0f;
    }
}

void DrMdoCtlSeam::resourceRelease() {
    if (m_instMdlInfo != nullptr) {
        m_instMdlInfo->releaseCall();
    }
    if (m_cldMdlData != nullptr) {
        m_cldMdlData->release();
        m_cldMdlData = nullptr;
    }
    if (m_envObj != nullptr) {
        m_envObj->release();
        m_envObj = nullptr;
    }
    if (m_envColi != nullptr) {
        m_envColi->release();
        m_envColi = nullptr;
    }
    if (m_calcClip != nullptr) {
        m_calcClip->release();
        m_calcClip = nullptr;
    }
    if (m_etcTexList != nullptr) {
        m_etcTexList->release();
        m_etcTexList = nullptr;
    }
    if (m_cpPlane != nullptr) {
        m_cpPlane->release();
        m_cpPlane = nullptr;
    }
    DrGlobalIBLMan* iblMan = *(m_pDrMan->m_iblMan + m_viewNum);
    for (DrGlobalIBLPack* pack : m_iblPacks) {
        iblMan->releaseObj(pack);
    }
    m_iblPacks.clear();
    for (DrEnvironmentObj* env : m_envObjs) {
        if (env != nullptr) {
            env->release();
        }
    }
    m_envObjs.clear();
}

void DrMdoCtlSeam::calcEnd() {
    bool readIdle;
    if (m_seamFlags & 0x10000) {
        m_seamFlags &= ~0x8000;
        m_readIdleCnt = 0;
        readIdle = false;
    } else if (++m_readIdleCnt >= 5) {
        m_readIdleCnt = 4;
        m_seamFlags |= 0x8000;
        readIdle = true;
    } else {
        m_seamFlags &= ~0x8000;
        readIdle = false;
    }
    if (readIdle) {
        m_seamFlags &= ~0x20000;
        m_readBusyCnt = 0;
    } else if (++m_readBusyCnt >= 900) {
        m_readBusyCnt = 900;
        m_seamFlags |= 0x20000;
    } else {
        m_seamFlags &= ~0x20000;
    }
    if (m_seamFlags & 0x20000) {
        m_seamFlags |= 0x8000;
        m_readIdleCnt = 4;
    }
    if (m_seamFlags & 0x200000) {
        m_seamFlags |= 0x400000;
        m_readErrWait = 30;
    }
    bool stmIdle;
    if (m_seamFlags & 0x400) {
        m_seamFlags &= ~0x800;
        m_stmIdleCnt = 0;
        stmIdle = false;
    } else if (++m_stmIdleCnt >= 5) {
        m_stmIdleCnt = 4;
        m_seamFlags |= 0x800;
        stmIdle = true;
    } else {
        m_seamFlags &= ~0x800;
        stmIdle = false;
    }
    if (stmIdle) {
        m_seamFlags &= ~0x100000;
        m_stmBusyCnt = 0;
    } else if (++m_stmBusyCnt >= 900) {
        m_stmBusyCnt = 900;
        m_seamFlags |= 0x100000;
    } else {
        m_seamFlags &= ~0x100000;
    }
    if (m_seamFlags & 0x100000) {
        m_seamFlags |= 0x800;
        m_stmIdleCnt = 4;
    }
    if (m_seamFlags & 0x800) {
        m_pDrMan->setSeamMapStmOk(false);
    } else {
        m_pDrMan->setSeamMapStmOk(true);
    }
}

void DrMdoCtlSeam::updateTexutreSeam() {
    if (m_releaseVertexAll) {
        DrResMdoSeamTexture::SEAMRES_HEIGHT_CNTMAX = 3;
        DrResMdoSeamTexture::SEAMRES_NOM_CNTMAX = 10;
        DrResMdoSeamTexList::setListCnt(10);
    } else {
        if (m_parmRead.m_posCnt == 0) {
            DrResMdoSeamTexList::setListCnt(60);
            DrResMdoSeamTexture::SEAMRES_NOM_CNTMAX = 120;
        } else {
            DrResMdoSeamTexList::setListCnt(10);
            DrResMdoSeamTexture::SEAMRES_NOM_CNTMAX = 10;
        }
        if (m_seamFlags & 0x20) {
            DrResMdoSeamTexture::SEAMRES_HEIGHT_CNTMAX = 3;
        } else {
            DrResMdoSeamTexture::SEAMRES_HEIGHT_CNTMAX = 60;
        }
    }
    DrResMdoSeamTexture* tex = m_texturePool.m_list;
    if (m_releaseVertexAll) {
        while (tex != nullptr) {
            DrResMdoSeamTexture* next = tex->m_prev;
            releaseFreeSeamTexture(tex, false);
            tex = next;
        }
        m_textureMemSize = 0;
    } else {
        while (tex != nullptr) {
            if (tex->update()) {
                const MapHead::TexSize* tbl = reinterpret_cast<const MapHead::TexSize*>(
                    reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_textureTblOfs);
                DrResMdoSeamTexture* next = tex->m_prev;
                m_textureMemSize -= tbl[tex->m_dataIdx].m_size;
                if (tex->m_heightReady == 1) {
                    m_textureMemSize -= tbl[tex->m_dataIdx].m_heightSize;
                }
                releaseFreeSeamTexture(tex, false);
                tex = next;
            } else {
                if (tex->m_readIn != 0) {
                    const MapHead::TexSize* tbl = reinterpret_cast<const MapHead::TexSize*>(
                        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_textureTblOfs);
                    const MapHead::TexSize* entry = &tbl[tex->m_dataIdx];
                    if (tex->m_heightReady == 1) {
                        unsigned int heightSize = tbl[tex->m_dataIdx].m_heightSize;
                        unsigned int rest = heightSize & 0xFFF;
                        tex->changeMemTexture((rest == 0 ? 0 : 0x1000 - rest) + heightSize, entry->m_size);
                    } else {
                        tex->changeMemTexture(entry->m_size);
                    }
                } else if (tex->m_heightReady == 1 && tex->updateHeight()) {
                    const MapHead::TexSize* tbl = reinterpret_cast<const MapHead::TexSize*>(
                        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_textureTblOfs);
                    tex->m_heightReady = 0;
                    const MapHead::TexSize* entry = &tbl[tex->m_dataIdx];
                    unsigned int heightSize = entry->m_heightSize;
                    unsigned int rest = heightSize & 0xFFF;
                    unsigned int allocSize = (rest == 0 ? 0 : 0x1000 - rest) + heightSize;
                    m_textureMemSize -= heightSize;
                    DrResMdoSeamMemObj* memObj = tex->m_memObj;
                    tex->m_memObj = m_memMan.createParentFreeObj(memObj, allocSize);
                    tex->resetTexture(entry->m_size);
                    releaseFreeSeamMemObj(memObj);
                }
                tex = tex->m_prev;
            }
        }
    }
    DrResMdoSeamTexList* list = m_texListPool.m_list;
    if (m_releaseVertexAll) {
        while (list != nullptr) {
            DrResMdoSeamTexList* next = list->m_prev;
            releaseFreeSeamTexList(list, false);
            list = next;
        }
        m_textureMemSize = 0;
    } else {
        while (list != nullptr) {
            if (list->update(&m_parmRead)) {
                DrResMdoSeamTexList* next = list->m_prev;
                const MapHead::ResSize* tbl = reinterpret_cast<const MapHead::ResSize*>(
                    reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_texListTblOfs);
                m_textureMemSize -= tbl[list->m_dataIdx].m_size;
                releaseFreeSeamTexList(list, false);
                list = next;
            } else {
                list = list->m_prev;
            }
        }
    }
}

void DrMdoCtlSeam::releaseFreeSeamTexture(DrResMdoSeamTexture* tex, bool keepMem) {
    auto toFree = [&](DrResMdoSeamTexture* res) {
        DrResMdoSeamTexture* after = res->m_prev;
        DrResMdoSeamTexture* before = res->m_next;
        if (after == nullptr) {
            if (before != nullptr) {
                before->m_prev = nullptr;
            }
        } else {
            if (before != nullptr) {
                before->m_prev = after;
            }
            after->m_next = before;
        }
        if (m_texturePool.m_usedTail == res) {
            m_texturePool.m_usedTail = before;
        }
        if (m_texturePool.m_list == res) {
            m_texturePool.m_list = after;
            if (after != nullptr) {
                after->m_next = nullptr;
            }
        }
        if (m_texturePool.m_freeTail == nullptr) {
            m_texturePool.m_freeHead = res;
            m_texturePool.m_freeTail = res;
            res->m_next = nullptr;
        } else {
            m_texturePool.m_freeTail->m_prev = res;
            res->m_next = m_texturePool.m_freeTail;
            m_texturePool.m_freeTail = res;
        }
        res->m_prev = nullptr;
        m_texturePool.m_freeNum++;
        m_texturePool.m_usedNum--;
    };
    if (keepMem) {
        tex->release();
        toFree(tex);
    } else {
        DrResMdoSeamMemObj* memObj = tex->m_memObj;
        DrResMdoSeamMemObj* heightMemObj = tex->m_heightMemObj;
        m_pTextureNo[tex->m_dataIdx] = 0;
        tex->release();
        tex->m_memObj = nullptr;
        toFree(tex);
        if (memObj != nullptr) {
            releaseFreeSeamMemObj(memObj);
        }
        if (heightMemObj != nullptr) {
            releaseFreeSeamMemObj(heightMemObj);
        }
    }
}

DrMdoCtlSeamAll::~DrMdoCtlSeamAll() {
    releaseSeamAll();
}

void DrMdoCtlSeam::releaseFreeSeamMemObj(DrResMdoSeamMemObj* obj) {
    m_memMan.releaseFreeObj(obj);
}

void DrMdoCtlSeam::releaseFreeSeamTexList(DrResMdoSeamTexList* list, bool keepMem) {
    auto toFree = [&](DrResMdoSeamTexList* res) {
        DrResMdoSeamTexList* after = res->m_prev;
        DrResMdoSeamTexList* before = res->m_next;
        if (after == nullptr) {
            if (before != nullptr) {
                before->m_prev = nullptr;
            }
        } else {
            if (before != nullptr) {
                before->m_prev = after;
            }
            after->m_next = before;
        }
        if (m_texListPool.m_usedTail == res) {
            m_texListPool.m_usedTail = before;
        }
        if (m_texListPool.m_list == res) {
            m_texListPool.m_list = after;
            if (after != nullptr) {
                after->m_next = nullptr;
            }
        }
        if (m_texListPool.m_freeTail == nullptr) {
            m_texListPool.m_freeHead = res;
            m_texListPool.m_freeTail = res;
            res->m_next = nullptr;
        } else {
            m_texListPool.m_freeTail->m_prev = res;
            res->m_next = m_texListPool.m_freeTail;
            m_texListPool.m_freeTail = res;
        }
        res->m_prev = nullptr;
        m_texListPool.m_freeNum++;
        m_texListPool.m_usedNum--;
    };
    if (keepMem) {
        list->release();
        toFree(list);
    } else {
        DrResMdoSeamMemObj* memObj = list->m_memObj;
        m_pTexListNo[list->m_dataIdx] = 0;
        list->release();
        list->m_memObj = nullptr;
        toFree(list);
        if (memObj != nullptr) {
            releaseFreeSeamMemObj(memObj);
        }
    }
}

void DrMdoCtlSeam::updateVertexSeam() {
    if (m_releaseVertexAll) {
        DrResMdoSeamVertex::SEAMRES_CNTMAX = 10;
        DrResMdoSeamVertex* vtx = m_vertexPool.m_list;
        while (vtx != nullptr) {
            DrResMdoSeamVertex* next = vtx->m_prev;
            releaseFreeSeamVertex(vtx, false);
            vtx = next;
        }
        m_vertexMemSize = 0;
    } else {
        DrResMdoSeamVertex::SEAMRES_CNTMAX = m_parmRead.m_posCnt == 0 ? 60 : 10;
        DrResMdoSeamVertex* vtx = m_vertexPool.m_list;
        while (vtx != nullptr) {
            if (vtx->update()) {
                DrResMdoSeamVertex* next = vtx->m_prev;
                const MapHead::ResSize* tbl = reinterpret_cast<const MapHead::ResSize*>(
                    reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_vertexTblOfs);
                m_vertexMemSize -= tbl[vtx->m_dataIdx].m_size;
                releaseFreeSeamVertex(vtx, false);
                vtx = next;
            } else {
                if (vtx->m_readIn != 0) {
                    vtx->changeMemVertex();
                }
                vtx = vtx->m_prev;
            }
        }
    }
}

void DrMdoCtlSeam::releaseFreeSeamVertex(DrResMdoSeamVertex* vtx, bool keepMem) {
    auto toFree = [&](DrResMdoSeamVertex* res) {
        DrResMdoSeamVertex* after = res->m_prev;
        DrResMdoSeamVertex* before = res->m_next;
        if (after == nullptr) {
            if (before != nullptr) {
                before->m_prev = nullptr;
            }
        } else {
            if (before != nullptr) {
                before->m_prev = after;
            }
            after->m_next = before;
        }
        if (m_vertexPool.m_usedTail == res) {
            m_vertexPool.m_usedTail = before;
        }
        if (m_vertexPool.m_list == res) {
            m_vertexPool.m_list = after;
            if (after != nullptr) {
                after->m_next = nullptr;
            }
        }
        if (m_vertexPool.m_freeTail == nullptr) {
            m_vertexPool.m_freeHead = res;
            m_vertexPool.m_freeTail = res;
            res->m_next = nullptr;
        } else {
            m_vertexPool.m_freeTail->m_prev = res;
            res->m_next = m_vertexPool.m_freeTail;
            m_vertexPool.m_freeTail = res;
        }
        res->m_prev = nullptr;
        m_vertexPool.m_freeNum++;
        m_vertexPool.m_usedNum--;
    };
    if (keepMem) {
        vtx->release();
        toFree(vtx);
    } else {
        DrResMdoSeamMemObj* memObj = vtx->m_memObj;
        m_pVertexNo[vtx->m_dataIdx] = 0;
        vtx->release();
        vtx->m_memObj = nullptr;
        toFree(vtx);
        if (memObj != nullptr) {
            releaseFreeSeamMemObj(memObj);
        }
    }
}

DrMdoCtlSeamAll::DrMdoCtlSeamAll(const void* data, const char* name, DrMan* drMan, int viewNum)
    : DrMdoCtlSeamRead(viewNum) {
    m_pDrMan = drMan;
    setupSeamMapHead(data, name);
}

void DrMdoCtlSeamAll::releaseSeamAll() {
    if (m_viewNum == 0) {
        m_pDrMan->m_pixlMan->m_shadowCacheMan->delShadowCacheUpdate();
    }
    for (DrResMdoSeamWrkBase* wrk = m_basePool.m_list; wrk != nullptr;) {
        DrResMdoSeamWrkBase* next = wrk->m_prev;
        releaseFreeSeamBase(wrk);
        wrk = next;
    }
    m_baseMemSize = 0;
    for (DrResMdoSeamWrkLow* wrk = m_lowPool.m_list; wrk != nullptr;) {
        DrResMdoSeamWrkLow* next = wrk->m_prev;
        releaseFreeSeamLow(wrk);
        wrk = next;
    }
    m_lowMemSize = 0;
    for (DrResMdoSeamWrkInst* wrk = m_instPool.m_list; wrk != nullptr;) {
        DrResMdoSeamWrkInst* next = wrk->m_pLink;
        releaseFreeSeamInst(wrk);
        wrk = next;
    }
    for (DrResMdoSeamWrkMpf* wrk = m_mpfPool.m_list; wrk != nullptr;) {
        DrResMdoSeamWrkMpf* next = wrk->m_prev;
        releaseFreeSeamMpf(wrk);
        wrk = next;
    }
    m_baseMemSize = 0;
    for (DrResMdoSeamWrkEnv* wrk = m_envPool.m_list; wrk != nullptr;) {
        DrResMdoSeamWrkEnv* next = wrk->m_prev;
        releaseFreeSeamEnvMap(wrk);
        wrk = next;
    }
    m_envMemSize = 0;
    for (DrResMdoSeamWrkLight* wrk = m_lightPool.m_list; wrk != nullptr;) {
        DrResMdoSeamWrkLight* next = wrk->m_prev;
        releaseFreeSeamLight(wrk);
        wrk = next;
    }
    m_lightMemSize = 0;
    m_lightNum = 0;
    releaseSeam();
}

void DrMdoCtlSeamAll::callShadowCacheUpdate(unsigned long bits) {
    m_baseShadowCacheDone &= ~bits;
    for (DrResMdoSeamWrkBase* wrk = m_basePool.m_list; wrk != nullptr; wrk = wrk->m_prev) {
        if (wrk->m_matRes != nullptr) {
            wrk->callShadowCacheBaseUpdate(bits);
        }
    }
    m_instShadowCacheDone &= ~bits;
    for (DrResMdoSeamWrkInst* wrk = m_instPool.m_list; wrk != nullptr; wrk = wrk->m_pLink) {
        if (wrk->m_pWrkMatRes != nullptr) {
            wrk->callShadowCacheInstUpdate(bits);
        }
    }
}

bool DrMdoCtlSeamAll::callDeleteUpdate() {
    if (!(m_seamFlags & 0x10000000)) {
        return true;
    }
    if (m_seamFlags & 0x20000000) {
        resourceRelease();
        if (m_seamFlags & 0x2000) {
            for (DrResMdoSeamWrkBase* wrk = m_basePool.m_list; wrk != nullptr;) {
                DrResMdoSeamWrkBase* next = wrk->m_prev;
                releaseFreeSeamBase(wrk);
                wrk = next;
            }
            m_baseMemSize = 0;
            for (DrResMdoSeamWrkLow* wrk = m_lowPool.m_list; wrk != nullptr;) {
                DrResMdoSeamWrkLow* next = wrk->m_prev;
                releaseFreeSeamLow(wrk);
                wrk = next;
            }
            m_lowMemSize = 0;
            for (DrResMdoSeamWrkInst* wrk = m_instPool.m_list; wrk != nullptr;) {
                DrResMdoSeamWrkInst* next = wrk->m_pLink;
                releaseFreeSeamInst(wrk);
                wrk = next;
            }
            for (DrResMdoSeamWrkMpf* wrk = m_mpfPool.m_list; wrk != nullptr;) {
                DrResMdoSeamWrkMpf* next = wrk->m_prev;
                releaseFreeSeamMpf(wrk);
                wrk = next;
            }
            m_baseMemSize = 0;
            for (DrResMdoSeamWrkEnv* wrk = m_envPool.m_list; wrk != nullptr;) {
                DrResMdoSeamWrkEnv* next = wrk->m_prev;
                releaseFreeSeamEnvMap(wrk);
                wrk = next;
            }
            m_envMemSize = 0;
            for (DrResMdoSeamWrkLight* wrk = m_lightPool.m_list; wrk != nullptr;) {
                DrResMdoSeamWrkLight* next = wrk->m_prev;
                releaseFreeSeamLight(wrk);
                wrk = next;
            }
            m_lightMemSize = 0;
            m_lightNum = 0;
            m_seamFlags &= ~0x2000;
        }
    }
    if (m_cldMdlData != nullptr) {
        m_cldMdlData->setCallDisp(false);
    }
    return false;
}

void DrMdoCtlSeamAll::dispOffUpdate() {
    if (m_ctlFlags2 & 0x40000) {
        m_ctlFlags2 &= ~0x30000;
    } else {
        unsigned int bit = 0x10000 << DrMan::s_nDblIdx;
        if (m_ctlFlags2 & bit) {
            m_ctlFlags2 &= ~bit;
            m_singleAlpha = m_alpha[DrMan::s_nDblIdx];
        }
    }
    if (calcBegin()) {
        callDeleteUpdate();
    }
    calcEnd();
}

void DrMdoCtlSeamAll::noOffScreenUpdate() {
    m_offScreenCnt++;
    if (!m_seamRead.isRead()) {
        m_seamRead.release();
        if (m_offScreenCnt >= 4) {
            m_dispFlags |= 0x18;
        }
    }
    if (!(m_seamFlags & 0x1000)) {
        m_seamFlags |= 0x1000;
        if (m_viewNum == 0) {
            m_pDrMan->m_pixlMan->m_shadowCacheMan->delShadowCacheUpdate();
        }
    }
}

void DrMdoCtlSeamBaseMap::createBaseThicknesPassDisplayList(bool first) {
    if (m_pDrMan->m_seamBaseShadowOff) {
        return;
    }
    for (DrResMdoSeamWrkBase* wrk = m_basePool.m_list; wrk != nullptr; wrk = wrk->m_prev) {
        m_pWrkMatRes = wrk->m_matRes;
        if (m_pWrkMatRes == nullptr || !(wrk->m_cacheFlags & 0x8)) {
            continue;
        }
        int num = wrk->m_renderNum[7];
        if (num == 0) {
            continue;
        }
        DrResMdoAlpTbl* alpTbl = wrk->m_instans;
        wrk->beginRender();
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[1] = 0;
        m_bindFlags[0] |= 0x10;
        int list = m_pWrkMatRes->m_matNum * 7;
        for (int i = 0; i < num; i++) {
            for (DrResMdoSeamWrkBase::RenderEntry* entry = wrk->m_renderList[list + i]; entry != nullptr;
                 entry = entry->m_next != 0 ? &wrk->m_renderEntries[entry->m_next - 1] : nullptr) {
                wrk->selectVertex(entry->m_vertexIdx);
                const MdsMdlInfoHeader* info =
                    reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + entry->m_infoOfs);
                if (info->m_drawFlags & 0x8000) {
                    partsThicknessRender(info, 0, 0, alpTbl, entry->m_alpIdx, first);
                }
            }
        }
        wrk->endRender();
    }
}

void DrMdoCtlSeamInstMap::createInstThicknessPassDisplayList(bool first) {
    if (m_pDrMan->m_seamOccRenderOff) {
        return;
    }
    MdoInstancePrePassArg arg;
    arg.m_first = 0x34;
    arg.m_first2 = first;
    for (DrResMdoSeamWrkInst* wrk = m_instPool.m_list; wrk != nullptr; wrk = wrk->m_pLink) {
        m_pWrkMatRes = wrk->m_pWrkMatRes;
        if (m_pWrkMatRes == nullptr || (wrk->m_cacheFlags & 0x110) != 0x110) {
            continue;
        }
        wrk->beginMdl();
        while (const DrResMdoSeamWrkInst::MdlInfo* info = wrk->getMdlInfo()) {
            unsigned int num = info->m_num;
            if (num == 0) {
                continue;
            }
            if (info->m_vtxNo == 0xFFFF) {
                m_pWrkMatRes->m_pVertex = wrk->m_vertex;
            } else {
                unsigned int no = m_pVertexNo[info->m_vtxNo];
                m_pWrkMatRes->m_pVertex = m_vertexPool.m_works[no - 1].m_vertex;
            }
            arg.m_bill = false;
            m_curShaderIdx = -1;
            m_curBindIdx = -1;
            m_bindFlags[1] = 0;
            m_bindFlags[0] |= 0x10;
            m_pWrkMatRes->m_pVertex->beginVertexSetup();
            const MdsMdlTopHeader* top = &m_pWrkMatRes->m_pMdlTop[info->m_topIdx];
            int partNum = top->m_infoNum;
            arg.m_info = reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs);
            arg.m_count = info->m_count;
            arg.m_instances = num;
            arg.m_billNum = 0;
            arg.m_billArg = 0;
            for (int i = 0; i < partNum; i++, arg.m_info++) {
                if ((m_pWrkMatRes->m_pResMat + arg.m_info->m_matIdx)->m_color.a > 0.0f &&
                    (arg.m_info->m_drawFlags & 0x8000) && (arg.m_info->m_flags & 0x24000) == 0x4000) {
                    partsInstanceThicknessRender(arg);
                }
            }
        }
    }
}

void DrMdoCtlSeamInstMap::initInstMapParts(DrResMdoSeamWrkInst* wrk, DrResMdoSeamWrkInst* pair) {
    const MdsSeamInstMapHead* head = reinterpret_cast<const MdsSeamInstMapHead*>(wrk->m_memObj->m_pData);
    const unsigned char* data = reinterpret_cast<const unsigned char*>(head);
    MdoWrkMatRes* matRes = nullptr;
    initInstMapMaterial(matRes, data + head->m_dataOfs[1], data + head->m_dataOfs[0], data + head->m_extOfs, nullptr,
                        head->m_matArg);
    m_pWrkMatRes = matRes;
    if (head->m_dataOfs[2] != 0) {
        const unsigned char* blockData = data + head->m_dataOfs[2];
        const MdsSeamInstMatBlock* block = reinterpret_cast<const MdsSeamInstMatBlock*>(blockData);
        m_pWrkMatRes->m_pSeamMatBlock = blockData;
        m_pWrkMatRes->m_pFixAnmInf = reinterpret_cast<const MdsFixAnmInf*>(m_pWrkMatRes->m_pSeamMatBlock + block->m_ofs0);
        m_pWrkMatRes->m_pFixAnmKey = reinterpret_cast<const MdsFixAnmKey*>(m_pWrkMatRes->m_pSeamMatBlock + block->m_ofs1);
        m_pWrkMatRes->m_pSeamMatData = m_pWrkMatRes->m_pSeamMatBlock + block->m_ofs2;
    }
    const DrResMdoSeamWrkInst::MapEntry* tbl = reinterpret_cast<const DrResMdoSeamWrkInst::MapEntry*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_instMapTblOfs);
    m_instMemSize += tbl[wrk->m_dataIdx].m_size;
    wrk->setupWork(matRes, m_triUniformArray, m_pDrMan->m_allocHandle, this, head, m_pDrMan->m_dispOffBits, 500,
                   &m_instAnm);
    unsigned int idx = wrk->m_dataIdx;
    m_pInstBits[idx >> 5] |= 1 << (idx & 0x1F);
    m_instNum++;
    if (pair != nullptr) {
        pair->m_pPair = wrk;
        wrk->m_pPair = pair;
    }
    if (m_viewNum == 0) {
        m_pDrMan->m_pixlMan->m_shadowCacheMan->callSelectShadowCacheUpdate(~0UL);
    }
    m_instShadowCacheDone = 0;
}

void DrMdoCtlSeamInstMap::releaseFreeSeamInst(DrResMdoSeamWrkInst* wrk) {
    DrResMdoSeamMemObj* memObj;
    if (wrk->m_pWrkMatRes == nullptr) {
        memObj = nullptr;
    } else {
        memObj = wrk->m_memObj;
        unsigned int idx = wrk->m_dataIdx;
        m_pInstBits[idx >> 5] &= ~(1 << (idx & 0x1F));
        m_instMemSize -= wrk->m_readSize;
        releaseInstMapSeamMat(wrk->m_pWrkMatRes);
        wrk->releaseCache(this);
        m_instNum--;
    }
    DrResMdoSeamWrkInst* after = wrk->m_pLink;
    DrResMdoSeamWrkInst* before = wrk->m_pBackLink;
    if (after == nullptr) {
        if (before != nullptr) {
            before->m_pLink = nullptr;
        }
    } else {
        if (before != nullptr) {
            before->m_pLink = after;
        }
        after->m_pBackLink = before;
    }
    if (m_instPool.m_usedTail == wrk) {
        m_instPool.m_usedTail = before;
    }
    if (m_instPool.m_list == wrk) {
        m_instPool.m_list = after;
        if (after != nullptr) {
            after->m_pBackLink = nullptr;
        }
    }
    if (m_instPool.m_freeTail == nullptr) {
        m_instPool.m_freeHead = wrk;
        m_instPool.m_freeTail = wrk;
        wrk->m_pBackLink = nullptr;
    } else {
        m_instPool.m_freeTail->m_pLink = wrk;
        wrk->m_pBackLink = m_instPool.m_freeTail;
        m_instPool.m_freeTail = wrk;
    }
    wrk->m_pLink = nullptr;
    m_instPool.m_freeNum++;
    m_instPool.m_usedNum--;
    if (memObj != nullptr) {
        wrk->m_memObj = nullptr;
        releaseFreeSeamMemObj(memObj);
    }
}

void DrMdoCtlSeamLowMap::initLowMapParts(DrResMdoSeamWrkLow* wrk) {
    const MdsSeamLowMapHead* head = reinterpret_cast<const MdsSeamLowMapHead*>(wrk->m_memObj->m_pData);
    const unsigned char* data = reinterpret_cast<const unsigned char*>(head);
    MdoWrkMatRes* matRes = nullptr;
    initBaseMapMaterial(matRes, data + head->m_dataOfs[1], data + head->m_dataOfs[0], data + head->m_matOfs[0],
                        data + head->m_matOfs[2], data + head->m_matOfs[1], 0);
    m_pWrkMatRes = matRes;
    if (head->m_dataOfs[2] != 0) {
        const unsigned char* blockData = data + head->m_dataOfs[2];
        const MdsSeamInstMatBlock* block = reinterpret_cast<const MdsSeamInstMatBlock*>(blockData);
        m_pWrkMatRes->m_pSeamMatBlock = blockData;
        m_pWrkMatRes->m_pFixAnmInf = reinterpret_cast<const MdsFixAnmInf*>(m_pWrkMatRes->m_pSeamMatBlock + block->m_ofs0);
        m_pWrkMatRes->m_pFixAnmKey = reinterpret_cast<const MdsFixAnmKey*>(m_pWrkMatRes->m_pSeamMatBlock + block->m_ofs1);
        m_pWrkMatRes->m_pSeamMatData = m_pWrkMatRes->m_pSeamMatBlock + block->m_ofs2;
    }
    const MdsSeamLowData* tbl = reinterpret_cast<const MdsSeamLowData*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_lowMdlTblOfs);
    const MdsSeamLowData* entry = &tbl[wrk->m_dataIdx];
    m_lowMemSize += entry->m_size;
    wrk->setupWork(matRes, m_triUniformArray, m_pDrMan->m_allocHandle, head, entry, 500);
    unsigned int idx = wrk->m_dataIdx;
    m_pLowBits[idx >> 5] |= 1 << (idx & 0x1F);
    m_lowNum++;
}

void DrMdoCtlSeamLowMap::releaseFreeSeamLow(DrResMdoSeamWrkLow* wrk) {
    DrResMdoSeamMemObj* memObj = wrk->m_memObj;
    if (wrk->m_matRes != nullptr) {
        unsigned int idx = wrk->m_dataIdx;
        m_pLowBits[idx >> 5] &= ~(1 << (idx & 0x1F));
        m_lowMemSize -= wrk->m_readSize;
        releaseBaseMapSeamMat(wrk->m_matRes);
        wrk->release();
        m_lowNum--;
    }
    DrResMdoSeamWrkLow* after = wrk->m_prev;
    DrResMdoSeamWrkLow* before = wrk->m_next;
    if (after == nullptr) {
        if (before != nullptr) {
            before->m_prev = nullptr;
        }
    } else {
        if (before != nullptr) {
            before->m_prev = after;
        }
        after->m_next = before;
    }
    if (m_lowPool.m_usedTail == wrk) {
        m_lowPool.m_usedTail = before;
    }
    if (m_lowPool.m_list == wrk) {
        m_lowPool.m_list = after;
        if (after != nullptr) {
            after->m_next = nullptr;
        }
    }
    if (m_lowPool.m_freeTail == nullptr) {
        m_lowPool.m_freeHead = wrk;
        m_lowPool.m_freeTail = wrk;
        wrk->m_next = nullptr;
    } else {
        m_lowPool.m_freeTail->m_prev = wrk;
        wrk->m_next = m_lowPool.m_freeTail;
        m_lowPool.m_freeTail = wrk;
    }
    wrk->m_prev = nullptr;
    m_lowPool.m_freeNum++;
    m_lowPool.m_usedNum--;
    if (memObj != nullptr) {
        wrk->m_memObj = nullptr;
        m_memMan.releaseFreeObj(memObj);
    }
}

void DrMdoCtlSeamInstMap::renderInstShadowCacheRender(DrResMdoSeamWrkInst* wrk, const mm::Mat44& mtx,
                                                      unsigned int vtxNo, const MdsMdlTopHeader* top) {
    if (vtxNo == 0xFFFF) {
        m_pWrkMatRes->m_pVertex = wrk->m_vertex;
    } else {
        unsigned int no = m_pVertexNo[vtxNo];
        m_pWrkMatRes->m_pVertex = m_vertexPool.m_works[no - 1].m_vertex;
    }
    m_pWrkMatRes->m_pVertex->beginVertexSetup();
    grlib::CGLibEtcUniformBlock block;
    grlib::ShdMat44TransposeMat44(static_cast<float*>(block.getBuff()), mtx);
    block.updateData(0x40);
    m_pEtcBlock = &block;
    m_bindFlags[0] |= 2;
    partsPosShadowRender(top);
    partsPosNukiShadowRender(top);
}

void DrMdoCtlSeamInstMap::beginResAll(MdoWrkMatRes* res) {
    m_pSavedWrkMatRes = m_pWrkMatRes;
    m_pWrkMatRes = res;
}

void DrMdoCtlSeamInstMap::endResAll() {
    m_pWrkMatRes = m_pSavedWrkMatRes;
}

void DrMdoCtlSeamLight::releaseFreeSeamLight(DrResMdoSeamWrkLight* wrk) {
    DrResMdoSeamMemObj* memObj = wrk->m_memObj;
    // gives the work back to the free list; the original has this code on both paths (the name is not the original's)
    auto freeWork = [&]() {
        DrResMdoSeamWrkLight* after = wrk->m_prev;
        DrResMdoSeamWrkLight* before = wrk->m_next;
        if (after == nullptr) {
            if (before != nullptr) {
                before->m_prev = nullptr;
            }
        } else {
            if (before != nullptr) {
                before->m_prev = after;
            }
            after->m_next = before;
        }
        if (m_lightPool.m_usedTail == wrk) {
            m_lightPool.m_usedTail = before;
        }
        if (m_lightPool.m_list == wrk) {
            m_lightPool.m_list = after;
            if (after != nullptr) {
                after->m_next = nullptr;
            }
        }
        if (m_lightPool.m_freeTail == nullptr) {
            m_lightPool.m_freeHead = wrk;
            m_lightPool.m_freeTail = wrk;
            wrk->m_next = nullptr;
        } else {
            m_lightPool.m_freeTail->m_prev = wrk;
            wrk->m_next = m_lightPool.m_freeTail;
            m_lightPool.m_freeTail = wrk;
        }
        wrk->m_prev = nullptr;
        m_lightPool.m_freeNum++;
        m_lightPool.m_usedNum--;
    };
    if (memObj != nullptr) {
        m_lightMemSize -= wrk->m_id;
        unsigned int idx = wrk->m_dataIdx;
        m_pLightBits[idx >> 5] &= ~(1 << (idx & 0x1F));
        m_lightNum--;
        wrk->release();
        freeWork();
        wrk->m_memObj = nullptr;
        m_memMan.releaseFreeObj(memObj);
    } else {
        freeWork();
    }
}

void DrMdoCtlSeamAll::callZPrePassSeamAll() {
    if (!(m_stateFlags & 0x100000) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderTech = 0;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pDrMan->m_apCache->setupCulling(static_cast<DrApCullType>(2));
    createBaseZPrePassDisplayList();
    createInstZPrePassDisplayList();
    createMpfZPrePassDisplayList();
    createLowZPrePassDisplayList();
}

void DrMdoCtlSeamBaseMap::createBaseZPrePassDisplayList() {
    if (!(m_seamFlags & 2) || m_pDrMan->m_seamBaseShadowOff) {
        return;
    }
    for (DrResMdoSeamWrkBase* wrk = m_basePool.m_list; wrk != nullptr; wrk = wrk->m_prev) {
        m_pWrkMatRes = wrk->m_matRes;
        if (m_pWrkMatRes == nullptr || !(wrk->m_cacheFlags & 0x8)) {
            continue;
        }
        int num = wrk->m_renderNum[0];
        if (num == 0) {
            continue;
        }
        DrResMdoAlpTbl* alpTbl = wrk->m_instans;
        wrk->beginRender();
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[1] = 0;
        m_bindFlags[0] |= 0x10;
        for (int i = 0; i < num; i++) {
            for (DrResMdoSeamWrkBase::RenderEntry* entry = wrk->m_renderList[i]; entry != nullptr;
                 entry = entry->m_next != 0 ? &wrk->m_renderEntries[entry->m_next - 1] : nullptr) {
                wrk->selectVertex(entry->m_vertexIdx);
                const MdsMdlInfoHeader* info =
                    reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + entry->m_infoOfs);
                if (!(info->m_drawFlags & 0x8000)) {
                    partsZPrePassRender(info, 0, 0, alpTbl, entry->m_alpIdx);
                }
            }
        }
        wrk->endRender();
    }
}

void DrMdoCtlSeamMpfMap::createMpfZPrePassDisplayList() {
    if (!(m_seamFlags & 0x8) || m_pDrMan->m_seamMpfRenderOff) {
        return;
    }
    DrResMdoSeamWrkMpf* wrk = m_mpfPool.m_list;
    grlib::CGLibVtxInstans* inst = m_pDrMan->m_mdlMan->m_vertexMan->m_instans;
    m_pDrMan->m_apCache->setupCulling(static_cast<DrApCullType>(2));
    for (; wrk != nullptr; wrk = wrk->m_prev) {
        m_pWrkMatRes = wrk->m_matRes;
        if (m_pWrkMatRes == nullptr || wrk->m_dispOn == 0) {
            continue;
        }
        int num = wrk->m_objNum;
        DrMdoCtlMpfWork* work = wrk->m_mpfWork;
        for (int i = 0; i < num; i++) {
            if (work->getObjChk(i) == 0) {
                continue;
            }
            const MdsMdlTopHeader* top = &m_pWrkMatRes->m_pMdlTop[i];
            int infoNum = top->m_infoNum;
            const MdsMdlInfoHeader* info =
                reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs);
            for (int j = 0; j < infoNum; j++, info++) {
                mpfZPrePassRender(i, info, work, inst);
            }
        }
    }
}

void DrMdoCtlSeamLowMap::createLowZPrePassDisplayList() {
    m_stateFlags &= ~0x40000000;
    for (DrResMdoSeamWrkLow* wrk = m_lowPool.m_list; wrk != nullptr; wrk = wrk->m_prev) {
        m_pWrkMatRes = wrk->m_matRes;
        if (m_pWrkMatRes == nullptr || !(wrk->m_cacheFlags & 0x4)) {
            continue;
        }
        int num = wrk->m_renderNum[0];
        if (num == 0) {
            continue;
        }
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[1] = 0;
        m_bindFlags[0] |= 0x10;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        DrResMdoAlpTbl* alpTbl = wrk->m_instans;
        for (int i = 0; i < num; i++) {
            for (DrResMdoSeamWrkLow::RenderEntry* entry = wrk->m_renderList[i]; entry != nullptr;
                 entry = entry->m_next != 0 ? &wrk->m_renderEntries[entry->m_next - 1] : nullptr) {
                const MdsMdlInfoHeader* info =
                    reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + entry->m_infoOfs);
                if (entry->m_flags & 0x2) {
                    m_stateFlags |= 0x20000000;
                } else {
                    m_stateFlags &= ~0x20000000;
                }
                partsZPrePassRender(info, 0, 0, alpTbl, entry->m_alpIdx);
            }
        }
    }
}

void DrMdoCtlSeamAll::callThicknessFirstSeamAll() {
    if (!(m_stateFlags & 0x40) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderTech = 0;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pDrMan->m_apCache->beginThicknessRenderFirst();
    m_pDrMan->m_apCache->setupCulling(static_cast<DrApCullType>(1));
    createBaseThicknesPassDisplayList(true);
    createInstThicknessPassDisplayList(true);
}

void DrMdoCtlSeamAll::callThicknessSecondSeamAll() {
    if (!(m_stateFlags & 0x40) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderTech = 0;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    m_pDrMan->m_apCache->beginThicknessRenderSecond();
    m_pDrMan->m_apCache->setupCulling(static_cast<DrApCullType>(0));
    createBaseThicknesPassDisplayList(false);
    createInstThicknessPassDisplayList(false);
}

void DrMdoCtlSeamAll::callRenderSeamAll() {
    if (!(m_stateFlags & 0x1) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 0;
    m_renderTech = 0;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    renderSeamInstMap(0);
    renderSeamBaseMap(0);
    if (m_seamFlags & 0x8) {
        DrMan::get()->m_tileParm->begin(static_cast<DrPixlTileParm::TileType>(3));
        createMpfMapDisplayList();
        DrMan::get()->m_tileParm->end(static_cast<DrPixlTileParm::TileType>(3));
    }
    renderSeamLowMap(0);
}

void DrMdoCtlSeamAll::callGBuffRenderSeamAll() {
    if (!(m_stateFlags & 0x2) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 1;
    m_renderTech = 7;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    renderSeamInstMap(1);
    renderSeamBaseMap(1);
    renderSeamLowMap(1);
}

void DrMdoCtlSeamAll::callLightPrePassRenderSeamAll() {
    if (!(m_stateFlags & 0x8) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 3;
    m_renderTech = 4;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    renderSeamBaseMap(3);
    renderSeamInstMap(3);
    renderSeamLowMap(3);
}

void DrMdoCtlSeamAll::callAlphaRenderSeamAll() {
    if (!(m_stateFlags & 0x10) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 4;
    m_renderTech = 1;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    renderSeamLowMap(4);
    renderSeamBaseMap(4);
    renderSeamInstMap(4);
}

void DrMdoCtlSeamAll::callSpAlphaRenderSeamAll() {
    if (!(m_stateFlags & 0x20) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 5;
    m_renderTech = 1;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    renderSeamLowMap(5);
    renderSeamBaseMap(5);
    renderSeamInstMap(5);
}

void DrMdoCtlSeamAll::callRefractionRenderSeamAll() {
    if (!(m_stateFlags & 0x4) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 2;
    m_renderTech = 8;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    renderSeamInstMap(2);
    renderSeamBaseMap(2);
    renderSeamLowMap(2);
}

void DrMdoCtlSeamEnvMap::callRenderSeamEnvMap() {
    if (m_pDrMan->m_seamEnvRenderOff) {
        return;
    }
    for (DrResMdoSeamWrkEnv* wrk = m_envPool.m_list; wrk != nullptr; wrk = wrk->m_prev) {
        m_pWrkMatRes = wrk->m_matRes;
        if (m_pWrkMatRes == nullptr || !(wrk->m_type & 0x1)) {
            continue;
        }
        m_renderPass = 0;
        m_renderTech = 0;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        DrResMdoMat* mats = m_pWrkMatRes->m_pResMat;
        // draws the parts of one top header that are in this pass and visible
        auto renderParts = [&](const MdsMdlInfoHeader* info, int num) {
            for (int j = 0; j < num; j++, info++) {
                if ((info->m_passFlags & 0x1) && mats[info->m_matIdx].m_color.a > 0.0f) {
                    partsDefRender(info, 0, 0, false);
                }
            }
        };
        const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop;
        for (int i = 0; i < m_pWrkMatRes->m_mdlTopNum; i++, top++) {
            renderParts(reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs),
                        top->m_infoNum);
        }
    }
}

void DrMdoCtlSeamAll::callRenderSeamEnvMap() {
    if (!(m_stateFlags & 0x1) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 0;
    m_renderTech = 0;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    DrMdoCtlSeamEnvMap::callRenderSeamEnvMap();
}

void DrMdoCtlSeamEnvMap::callGBuffRenderSeamEnvMap() {
    if (m_pDrMan->m_seamEnvRenderOff) {
        return;
    }
    for (DrResMdoSeamWrkEnv* wrk = m_envPool.m_list; wrk != nullptr; wrk = wrk->m_prev) {
        m_pWrkMatRes = wrk->m_matRes;
        if (m_pWrkMatRes == nullptr || !(wrk->m_type & 0x2)) {
            continue;
        }
        m_renderPass = 1;
        m_renderTech = 7;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        DrResMdoMat* mats = m_pWrkMatRes->m_pResMat;
        // draws the parts of one top header that are in this pass and visible
        auto renderParts = [&](const MdsMdlInfoHeader* info, int num) {
            for (int j = 0; j < num; j++, info++) {
                if ((info->m_passFlags & 0x8) && mats[info->m_matIdx].m_color.a > 0.0f) {
                    partsDefRender(info, 0, 0, false);
                }
            }
        };
        const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop;
        for (int i = 0; i < m_pWrkMatRes->m_mdlTopNum; i++, top++) {
            renderParts(reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs),
                        top->m_infoNum);
        }
    }
}

void DrMdoCtlSeamAll::callGBuffRenderSeamEnvMap() {
    if (!(m_stateFlags & 0x2) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 1;
    m_renderTech = 7;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    DrMdoCtlSeamEnvMap::callGBuffRenderSeamEnvMap();
}

void DrMdoCtlSeamEnvMap::callLightPrePassRenderSeamEnvMap() {
    if (m_pDrMan->m_seamEnvRenderOff) {
        return;
    }
    for (DrResMdoSeamWrkEnv* wrk = m_envPool.m_list; wrk != nullptr; wrk = wrk->m_prev) {
        m_pWrkMatRes = wrk->m_matRes;
        if (m_pWrkMatRes == nullptr || !(wrk->m_type & 0x8)) {
            continue;
        }
        m_renderPass = 3;
        m_renderTech = 4;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        DrResMdoMat* mats = m_pWrkMatRes->m_pResMat;
        // draws the parts of one top header that are in this pass and visible
        auto renderParts = [&](const MdsMdlInfoHeader* info, int num) {
            for (int j = 0; j < num; j++, info++) {
                if ((info->m_passFlags & 0x20) && mats[info->m_matIdx].m_color.a > 0.0f) {
                    partsDefRender(info, 0, 0, false);
                }
            }
        };
        const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop;
        for (int i = 0; i < m_pWrkMatRes->m_mdlTopNum; i++, top++) {
            renderParts(reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs),
                        top->m_infoNum);
        }
    }
}

void DrMdoCtlSeamAll::callLightPrePassRenderSeamEnvMap() {
    if (!(m_stateFlags & 0x8) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 3;
    m_renderTech = 4;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    DrMdoCtlSeamEnvMap::callLightPrePassRenderSeamEnvMap();
}

void DrMdoCtlSeamEnvMap::callAlphaRenderSeamEnvMap() {
    if (m_pDrMan->m_seamEnvRenderOff) {
        return;
    }
    for (DrResMdoSeamWrkEnv* wrk = m_envPool.m_list; wrk != nullptr; wrk = wrk->m_prev) {
        m_pWrkMatRes = wrk->m_matRes;
        if (m_pWrkMatRes == nullptr || !(wrk->m_type & 0x10)) {
            continue;
        }
        m_renderPass = 4;
        m_renderTech = 1;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        DrResMdoMat* mats = m_pWrkMatRes->m_pResMat;
        // draws the parts of one top header that are in this pass and visible
        auto renderParts = [&](const MdsMdlInfoHeader* info, int num) {
            for (int j = 0; j < num; j++, info++) {
                if ((info->m_passFlags & 0x2) && mats[info->m_matIdx].m_color.a > 0.0f) {
                    partsDefRender(info, 0, 0, false);
                }
            }
        };
        const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop;
        for (int i = 0; i < m_pWrkMatRes->m_mdlTopNum; i++, top++) {
            renderParts(reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs),
                        top->m_infoNum);
        }
    }
}

void DrMdoCtlSeamAll::callAlphaRenderSeamEnvMap() {
    if (!(m_stateFlags & 0x10) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 4;
    m_renderTech = 1;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    DrMdoCtlSeamEnvMap::callAlphaRenderSeamEnvMap();
}

void DrMdoCtlSeamEnvMap::callSpAlphaRenderSeamEnvMap() {
    if (m_pDrMan->m_seamEnvRenderOff) {
        return;
    }
    for (DrResMdoSeamWrkEnv* wrk = m_envPool.m_list; wrk != nullptr; wrk = wrk->m_prev) {
        m_pWrkMatRes = wrk->m_matRes;
        if (m_pWrkMatRes == nullptr || !(wrk->m_type & 0x20)) {
            continue;
        }
        m_renderPass = 5;
        m_renderTech = 1;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        DrResMdoMat* mats = m_pWrkMatRes->m_pResMat;
        // draws the parts of one top header that are in this pass and visible
        auto renderParts = [&](const MdsMdlInfoHeader* info, int num) {
            for (int j = 0; j < num; j++, info++) {
                if ((info->m_passFlags & 0x40) && mats[info->m_matIdx].m_color.a > 0.0f) {
                    partsDefRender(info, 0, 0, false);
                }
            }
        };
        const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop;
        for (int i = 0; i < m_pWrkMatRes->m_mdlTopNum; i++, top++) {
            renderParts(reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs),
                        top->m_infoNum);
        }
    }
}

void DrMdoCtlSeamAll::callSpAlphaRenderSeamEnvMap() {
    if (!(m_stateFlags & 0x20) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 5;
    m_renderTech = 1;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    DrMdoCtlSeamEnvMap::callSpAlphaRenderSeamEnvMap();
}

void DrMdoCtlSeamEnvMap::callRefractionRenderSeamEnvMap() {
    if (m_pDrMan->m_seamEnvRenderOff) {
        return;
    }
    for (DrResMdoSeamWrkEnv* wrk = m_envPool.m_list; wrk != nullptr; wrk = wrk->m_prev) {
        m_pWrkMatRes = wrk->m_matRes;
        if (m_pWrkMatRes == nullptr || !(wrk->m_type & 0x4)) {
            continue;
        }
        m_renderPass = 2;
        m_renderTech = 8;
        m_curShaderIdx = -1;
        m_curBindIdx = -1;
        m_bindFlags[0] = 0x10;
        m_bindFlags[1] = 0;
        m_pWrkMatRes->m_pVertex->beginVertexSetup();
        DrResMdoMat* mats = m_pWrkMatRes->m_pResMat;
        // draws the parts of one top header that are in this pass and visible
        auto renderParts = [&](const MdsMdlInfoHeader* info, int num) {
            for (int j = 0; j < num; j++, info++) {
                if ((info->m_passFlags & 0x4) && mats[info->m_matIdx].m_color.a > 0.0f) {
                    partsDefRender(info, 0, 0, false);
                }
            }
        };
        const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop;
        for (int i = 0; i < m_pWrkMatRes->m_mdlTopNum; i++, top++) {
            renderParts(reinterpret_cast<const MdsMdlInfoHeader*>(m_pWrkMatRes->m_pMdlInfo + top->m_infoOfs),
                        top->m_infoNum);
        }
    }
}

void DrMdoCtlSeamAll::callRefractionRenderSeamEnvMap() {
    if (!(m_stateFlags & 0x4) || m_pDrMan->m_seamRenderOff) {
        return;
    }
    m_renderPass = 2;
    m_renderTech = 8;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[0] = 0x10;
    m_bindFlags[1] = 0;
    DrMdoCtlSeamEnvMap::callRefractionRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::shadowCacheAddRender(int idx) {
    if ((m_dispFlags & 1) && !(m_seamFlags & 0x10000000)) {
        m_pDrMan->m_pixlMan->setupShadowUnifrom(idx);
        callInstShadowCacheAddRender(idx);
    }
}

void DrMdoCtlSeamBaseMap::callShadowMapRenderSeamBaseMap(DrPixlShadowObj* shadow) {
    if (m_pDrMan->m_seamBaseShadowOff) {
        return;
    }
    DrCalcViewWork* view = m_pDrMan->m_calcMan->m_pViewWork;
    grlib::CGLibEtcUniformBlock block;
    grlib::ShdMat44TransposeMat44(static_cast<float*>(block.getBuff()), view->m_view);
    block.updateData(0x40);
    m_pEtcBlock = &block;
    for (DrResMdoSeamWrkBase* wrk = m_basePool.m_list; wrk != nullptr; wrk = wrk->m_prev) {
        m_pWrkMatRes = wrk->m_matRes;
        if (m_pWrkMatRes != nullptr && (wrk->m_cacheFlags & 0x8)) {
            m_curShaderIdx = -1;
            m_curBindIdx = -1;
            m_bindFlags[1] = 0;
            m_bindFlags[0] |= 0x10;
            wrk->seachDefShadowBaseMapRender(shadow, this);
        }
    }
}

void DrMdoCtlSeamInstMap::callInstShadowCacheAddRender(int idx) {
    if (!(m_seamFlags & 0x4000) || m_pDrMan->m_seamOccRenderOff) {
        return;
    }
    DrResMdoSeamWrkInst* wrk = m_instPool.m_list;
    m_curShaderIdx = -1;
    m_curBindIdx = -1;
    m_bindFlags[1] = 0;
    m_bindFlags[0] |= 0x10;
    grlib::CGLibVtxInstans* inst = m_pDrMan->m_mdlMan->m_vertexMan->m_instans;
    for (; wrk != nullptr; wrk = wrk->m_pLink) {
        m_pWrkMatRes = wrk->m_pWrkMatRes;
        if (m_pWrkMatRes == nullptr || !(wrk->m_cacheFlags & 0x10)) {
            continue;
        }
        int num = wrk->m_shadowMdlNum;
        if (num != 0) {
            const unsigned int* vtxNo = reinterpret_cast<const unsigned int*>(
                reinterpret_cast<const unsigned char*>(wrk->m_header) + wrk->m_header->m_vtxNoOfs);
            DrResMdoSeamWrkInst::MdlInfo** list = wrk->m_shadowMdlList;
            for (int i = 0; i < num; i++, list++) {
                DrResMdoSeamWrkInst::MdlInfo* info = *list;
                const MdsMdlTopHeader* top = m_pWrkMatRes->m_pMdlTop + info->m_topIdx;
                if (!(top->m_shadowFlags & 0x4)) {
                    continue;
                }
                unsigned int no = vtxNo[info->m_topIdx];
                if (no == 0xFFFF) {
                    m_pWrkMatRes->m_pVertex = wrk->m_vertex;
                } else {
                    unsigned int vtx = m_pVertexNo[no];
                    if (vtx == 0) {
                        continue;
                    }
                    m_pWrkMatRes->m_pVertex = m_vertexPool.m_works[vtx - 1].m_vertex;
                }
                m_pWrkMatRes->m_pVertex->beginVertexSetup();
                m_pWrkMatRes->m_pEtcRef->m_etcIdx = info->m_etcIdx;
                partsPosNoamShadowRender(top, inst, info->m_count, 0x34, info->m_num);
            }
        }
        wrk->renderShadowPosAnime(this, &m_instAnm, idx);
    }
}

void DrMdoCtlSeamAll::occRender() {
    if (!(m_dispFlags & 1) || (m_seamFlags & 0x10000000) || m_pDrMan->m_seamOccRenderOff) {
        return;
    }
    for (DrResMdoSeamWrkInst* wrk = m_instPool.m_list; wrk != nullptr; wrk = wrk->m_pLink) {
        m_pWrkMatRes = wrk->m_pWrkMatRes;
        if (m_pWrkMatRes != nullptr) {
            wrk->occRender();
        }
    }
}

void DrMdoCtlSeamAll::setDeleteCall(int idx) {
    m_seamFlags |= 0x40000000 << idx;
    m_seamRead.readCancel();
    resourceRelease();
}

void DrMdoCtlSeamRead::callBaseMapStream(_wkSeamReadWait* wait) {
    const DrResMdoSeamWrkBase::MapEntry* tbl = reinterpret_cast<const DrResMdoSeamWrkBase::MapEntry*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_baseMapTblOfs);
    const DrResMdoSeamWrkBase::MapEntry* entry = &tbl[wait->m_idx];
    unsigned int rest = entry->m_size & 0xFFF;
    DrResMdoSeamMemObj* memObj = m_memMan.createFreeObj((rest == 0 ? 0 : 0x1000 - rest) + entry->m_size);
    if (memObj != nullptr) {
        DrResMdoSeamWrkBase* wrk = m_basePool.m_freeHead;
        if (wrk != nullptr) {
            DrResMdoSeamWrkBase* next = wrk->m_prev;
            if (next == nullptr) {
                m_basePool.m_freeHead = nullptr;
                m_basePool.m_freeTail = nullptr;
            } else {
                m_basePool.m_freeHead = next;
                next->m_next = nullptr;
            }
            if (m_basePool.m_usedTail != nullptr) {
                m_basePool.m_usedTail->m_prev = wrk;
            }
            if (m_basePool.m_list == nullptr) {
                m_basePool.m_list = wrk;
            }
            wrk->m_next = m_basePool.m_usedTail;
            wrk->m_prev = nullptr;
            m_basePool.m_freeNum--;
            m_basePool.m_usedNum++;
            m_basePool.m_usedTail = wrk;
            int readIdx;
            if (m_seamRead.read(readIdx, entry->m_ofs, entry->m_size, memObj)) {
                wrk->m_memObj = memObj;
                wrk->m_dataIdx = wait->m_idx;
                wrk->m_mapEntry = entry;
                wrk->m_readSize = entry->m_size;
                memObj->m_flags |= 4;
                int num = m_readCallNum++;
                if (num >= 7) {
                    m_seamFlags |= 0x80000;
                }
                _wkSeamReadCall* call = &m_readCall[num];
                call->m_pMemObj = memObj;
                call->m_pBase = wrk;
                call->m_cacheParam = entry->m_size;
                call->m_type = 0;
                call->m_readIdx = readIdx;
                call->m_cacheIdx = wait->m_idx;
                call->m_attr = wait->m_attr;
                m_seamFlags |= 0x10000;
                return;
            }
            releaseFreeSeamBase(wrk);
        }
        m_memMan.releaseFreeObj(memObj);
    }
    m_seamFlags |= 0x200000;
    unsigned int size = entry->m_size;
    m_readErrType[m_readErrIdx] = 0;
    m_readErrSize[m_readErrIdx] = size;
    m_readErrIdx = static_cast<short>(m_readErrIdx + 1) >= 4 ? 0 : m_readErrIdx + 1;
}

void DrMdoCtlSeamRead::callLowMdlStream(_wkSeamReadWait* wait) {
    const MdsSeamLowData* tbl = reinterpret_cast<const MdsSeamLowData*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_lowMdlTblOfs);
    const MdsSeamLowData* entry = &tbl[wait->m_idx];
    unsigned int rest = entry->m_size & 0xFFF;
    DrResMdoSeamMemObj* memObj = m_memMan.createFreeObj((rest == 0 ? 0 : 0x1000 - rest) + entry->m_size);
    if (memObj != nullptr) {
        DrResMdoSeamWrkLow* wrk = m_lowPool.m_freeHead;
        if (wrk != nullptr) {
            DrResMdoSeamWrkLow* next = wrk->m_prev;
            if (next == nullptr) {
                m_lowPool.m_freeHead = nullptr;
                m_lowPool.m_freeTail = nullptr;
            } else {
                m_lowPool.m_freeHead = next;
                next->m_next = nullptr;
            }
            if (m_lowPool.m_usedTail != nullptr) {
                m_lowPool.m_usedTail->m_prev = wrk;
            }
            if (m_lowPool.m_list == nullptr) {
                m_lowPool.m_list = wrk;
            }
            wrk->m_next = m_lowPool.m_usedTail;
            wrk->m_prev = nullptr;
            m_lowPool.m_freeNum--;
            m_lowPool.m_usedNum++;
            m_lowPool.m_usedTail = wrk;
            int readIdx;
            if (m_seamRead.read(readIdx, entry->m_ofs, entry->m_size, memObj)) {
                wrk->m_memObj = memObj;
                wrk->m_dataIdx = wait->m_idx;
                memObj->m_flags |= 4;
                int num = m_readCallNum++;
                if (num >= 7) {
                    m_seamFlags |= 0x80000;
                }
                _wkSeamReadCall* call = &m_readCall[num];
                call->m_pMemObj = memObj;
                call->m_pLow = wrk;
                call->m_cacheParam = entry->m_size;
                call->m_type = 1;
                call->m_readIdx = readIdx;
                call->m_cacheIdx = wait->m_idx;
                call->m_attr = wait->m_attr;
                return;
            }
            releaseFreeSeamLow(wrk);
        }
        m_memMan.releaseFreeObj(memObj);
    }
    unsigned int size = entry->m_size;
    m_readErrType[m_readErrIdx] = 1;
    m_readErrSize[m_readErrIdx] = size;
    m_readErrIdx = static_cast<short>(m_readErrIdx + 1) >= 4 ? 0 : m_readErrIdx + 1;
    m_seamFlags |= 0x200000;
}

void DrMdoCtlSeamRead::callInstMapStream(_wkSeamReadWait* wait) {
    const DrResMdoSeamWrkInst::MapEntry* tbl = reinterpret_cast<const DrResMdoSeamWrkInst::MapEntry*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_instMapTblOfs);
    const DrResMdoSeamWrkInst::MapEntry* entry = &tbl[wait->m_idx];
    unsigned int rest = entry->m_size & 0xFFF;
    DrResMdoSeamMemObj* memObj = m_memMan.createFreeObj((rest == 0 ? 0 : 0x1000 - rest) + entry->m_size);
    if (memObj != nullptr) {
        DrResMdoSeamWrkInst* wrk = m_instPool.m_freeHead;
        if (wrk != nullptr) {
            DrResMdoSeamWrkInst* next = wrk->m_pLink;
            if (next == nullptr) {
                m_instPool.m_freeHead = nullptr;
                m_instPool.m_freeTail = nullptr;
            } else {
                m_instPool.m_freeHead = next;
                next->m_pBackLink = nullptr;
            }
            if (m_instPool.m_usedTail != nullptr) {
                m_instPool.m_usedTail->m_pLink = wrk;
            }
            if (m_instPool.m_list == nullptr) {
                m_instPool.m_list = wrk;
            }
            wrk->m_pBackLink = m_instPool.m_usedTail;
            wrk->m_pLink = nullptr;
            m_instPool.m_freeNum--;
            m_instPool.m_usedTail = wrk;
            m_instPool.m_usedNum++;
            int readIdx;
            if (m_seamRead.read(readIdx, entry->m_ofs, entry->m_size, memObj)) {
                wrk->m_memObj = memObj;
                wrk->m_dataIdx = wait->m_idx;
                wrk->m_mapEntry = entry;
                wrk->m_readSize = entry->m_size;
                memObj->m_flags |= 4;
                int num = m_readCallNum++;
                if (num >= 7) {
                    m_seamFlags |= 0x80000;
                }
                _wkSeamReadCall* call = &m_readCall[num];
                call->m_pMemObj = memObj;
                call->m_pInst = wrk;
                call->m_pInst2 = wait->m_pInst;
                call->m_cacheParam = entry->m_size;
                call->m_type = 2;
                call->m_readIdx = readIdx;
                call->m_cacheIdx = wait->m_idx;
                call->m_attr = wait->m_attr;
                m_seamFlags |= 0x10000;
                return;
            }
            releaseFreeSeamInst(wrk);
        }
        m_memMan.releaseFreeObj(memObj);
    }
    unsigned int size = entry->m_size;
    m_readErrType[m_readErrIdx] = 2;
    m_readErrSize[m_readErrIdx] = size;
    m_readErrIdx = static_cast<short>(m_readErrIdx + 1) >= 4 ? 0 : m_readErrIdx + 1;
    m_seamFlags |= 0x200000;
}

void DrMdoCtlSeamRead::callMpfMdlStream(_wkSeamReadWait* wait) {
    const DrResMdoSeamWrkMpf::MapEntry* tbl = reinterpret_cast<const DrResMdoSeamWrkMpf::MapEntry*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_mpfMdlTblOfs);
    const DrResMdoSeamWrkMpf::MapEntry* entry = &tbl[wait->m_idx];
    unsigned int rest = entry->m_size & 0xFFF;
    DrResMdoSeamMemObj* memObj = m_memMan.createFreeObj((rest == 0 ? 0 : 0x1000 - rest) + entry->m_size);
    if (memObj != nullptr) {
        DrResMdoSeamWrkMpf* wrk = m_mpfPool.m_freeHead;
        if (wrk != nullptr) {
            DrResMdoSeamWrkMpf* next = wrk->m_prev;
            if (next == nullptr) {
                m_mpfPool.m_freeHead = nullptr;
                m_mpfPool.m_freeTail = nullptr;
            } else {
                m_mpfPool.m_freeHead = next;
                next->m_next = nullptr;
            }
            if (m_mpfPool.m_usedTail != nullptr) {
                m_mpfPool.m_usedTail->m_prev = wrk;
            }
            if (m_mpfPool.m_list == nullptr) {
                m_mpfPool.m_list = wrk;
            }
            wrk->m_next = m_mpfPool.m_usedTail;
            wrk->m_prev = nullptr;
            m_mpfPool.m_freeNum--;
            m_mpfPool.m_usedNum++;
            m_mpfPool.m_usedTail = wrk;
            int readIdx;
            if (m_seamRead.read(readIdx, entry->m_ofs, entry->m_size, memObj)) {
                wrk->m_memObj = memObj;
                wrk->m_dataIdx = wait->m_idx;
                wrk->m_mapEntry = entry;
                wrk->m_readSize = entry->m_size;
                memObj->m_flags |= 4;
                int num = m_readCallNum++;
                if (num >= 7) {
                    m_seamFlags |= 0x80000;
                }
                _wkSeamReadCall* call = &m_readCall[num];
                call->m_pMemObj = memObj;
                call->m_pMpf = wrk;
                call->m_cacheParam = entry->m_size;
                call->m_type = 3;
                call->m_readIdx = readIdx;
                call->m_cacheIdx = wait->m_idx;
                call->m_attr = wait->m_attr;
                m_seamFlags |= 0x10000;
                return;
            }
            releaseFreeSeamMpf(wrk);
        }
        m_memMan.releaseFreeObj(memObj);
    }
    unsigned int size = entry->m_size;
    m_readErrType[m_readErrIdx] = 3;
    m_readErrSize[m_readErrIdx] = size;
    m_readErrIdx = static_cast<short>(m_readErrIdx + 1) >= 4 ? 0 : m_readErrIdx + 1;
    m_seamFlags |= 0x200000;
}

void DrMdoCtlSeamRead::callEnvMdlStream(_wkSeamReadWait* wait) {
    const MapHead::MdlEntry* tbl = reinterpret_cast<const MapHead::MdlEntry*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_envMdlTblOfs);
    const MapHead::MdlEntry* entry = &tbl[wait->m_idx];
    unsigned int rest = entry->m_size & 0xFFF;
    DrResMdoSeamMemObj* memObj = m_memMan.createFreeObj((rest == 0 ? 0 : 0x1000 - rest) + entry->m_size);
    if (memObj != nullptr) {
        DrResMdoSeamWrkEnv* wrk = m_envPool.m_freeHead;
        if (wrk != nullptr) {
            DrResMdoSeamWrkEnv* next = wrk->m_prev;
            if (next == nullptr) {
                m_envPool.m_freeHead = nullptr;
                m_envPool.m_freeTail = nullptr;
            } else {
                m_envPool.m_freeHead = next;
                next->m_next = nullptr;
            }
            if (m_envPool.m_usedTail != nullptr) {
                m_envPool.m_usedTail->m_prev = wrk;
            }
            if (m_envPool.m_list == nullptr) {
                m_envPool.m_list = wrk;
            }
            wrk->m_next = m_envPool.m_usedTail;
            wrk->m_prev = nullptr;
            m_envPool.m_freeNum--;
            m_envPool.m_usedNum++;
            m_envPool.m_usedTail = wrk;
            int readIdx;
            if (m_seamRead.read(readIdx, entry->m_ofs, entry->m_size, memObj)) {
                wrk->m_memObj = memObj;
                wrk->m_dataIdx = wait->m_idx;
                memObj->m_flags |= 4;
                int num = m_readCallNum++;
                if (num >= 7) {
                    m_seamFlags |= 0x80000;
                }
                _wkSeamReadCall* call = &m_readCall[num];
                call->m_pMemObj = memObj;
                call->m_pEnv = wrk;
                call->m_cacheParam = entry->m_size;
                call->m_type = 4;
                call->m_readIdx = readIdx;
                call->m_cacheIdx = wait->m_idx;
                call->m_attr = wait->m_attr;
                m_seamFlags |= 0x10000;
                return;
            }
            releaseFreeSeamEnvMap(wrk);
        }
        m_memMan.releaseFreeObj(memObj);
    }
    m_seamFlags |= 0x200000;
}

void DrMdoCtlSeamRead::callBaseVertexStream(_wkSeamReadWait* wait) {
    DrResMdoSeamWrkBase* wrk = wait->m_pBase;
    const MapHead::ResSize* tbl = reinterpret_cast<const MapHead::ResSize*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_baseVertexTblOfs);
    const MapHead::ResSize* entry = &tbl[wait->m_idx];
    unsigned int rest = entry->m_size & 0xFFF;
    DrResMdoSeamMemObj* memObj = m_memMan.createFreeObj((rest == 0 ? 0 : 0x1000 - rest) + entry->m_size);
    if (memObj != nullptr) {
        int readIdx;
        if (m_seamRead.read(readIdx, entry->m_ofs, entry->m_size, memObj)) {
            wrk->m_cacheFlags |= 0x10;
            memObj->m_flags |= 4;
            int num = m_readCallNum++;
            if (num >= 7) {
                m_seamFlags |= 0x80000;
            }
            _wkSeamReadCall* call = &m_readCall[num];
            call->m_pMemObj = memObj;
            call->m_pBase = wrk;
            call->m_cacheParam = entry->m_size;
            call->m_type = 5;
            call->m_readIdx = readIdx;
            call->m_cacheIdx = wait->m_idx;
            call->m_attr = wait->m_attr;
            m_seamFlags |= 0x10000;
            return;
        }
        m_memMan.releaseFreeObj(memObj);
    }
    unsigned int size = entry->m_size;
    m_readErrType[m_readErrIdx] = 5;
    m_readErrSize[m_readErrIdx] = size;
    m_readErrIdx = static_cast<short>(m_readErrIdx + 1) >= 4 ? 0 : m_readErrIdx + 1;
    m_seamFlags |= 0x200000;
}

void DrMdoCtlSeamRead::callHeightTexutreStream(_wkSeamReadWait* wait) {
    if (m_pTextureNo[wait->m_idx] == 0) {
        return;
    }
    const MapHead::TexSize* tbl = reinterpret_cast<const MapHead::TexSize*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_textureTblOfs);
    const MapHead::TexSize* entry = &tbl[wait->m_idx];
    unsigned int rest = entry->m_heightSize & 0xFFF;
    unsigned int heightSize = (rest == 0 ? 0 : 0x1000 - rest) + entry->m_heightSize;
    rest = entry->m_size & 0xFFF;
    unsigned int size = (rest == 0 ? 0 : 0x1000 - rest) + entry->m_size + heightSize;
    rest = size & 0xFFF;
    size += rest == 0 ? 0 : 0x1000 - rest;
    DrResMdoSeamMemObj* memObj = m_memMan.createBackFreeObj(size);
    if (memObj != nullptr) {
        int readIdx;
        if (m_seamRead.read(readIdx, entry->m_heightOfs, entry->m_heightSize, memObj)) {
            unsigned int texNo = m_pTextureNo[wait->m_idx] - 1;
            DrResMdoSeamTexture* tex = &m_texturePool.m_works[texNo];
            tex->m_cnt = 0;
            tex->m_heightCnt = 0;
            memObj->m_flags |= 4;
            int num = m_readCallNum++;
            if (num >= 7) {
                m_seamFlags |= 0x80000;
            }
            _wkSeamReadCall* call = &m_readCall[num];
            call->m_pMemObj = memObj;
            call->m_pTexture = tex;
            call->m_cacheParam = entry->m_heightSize;
            call->m_type = 8;
            call->m_readIdx = readIdx;
            call->m_cacheIdx = wait->m_idx;
            call->m_attr = wait->m_attr;
            memcpy(memObj->m_pData + heightSize, tex->m_memObj->m_pData, entry->m_size);
            tex->m_heightMemObj = memObj;
            tex->createHeightMoveTexture(heightSize, entry->m_size);
            tex->m_memObj->m_flags |= 4;
            return;
        }
        m_memMan.releaseFreeObj(memObj);
    }
    m_heightReadWait = 60;
    unsigned int errSize = entry->m_heightSize;
    m_readErrType[m_readErrIdx] = 8;
    m_readErrSize[m_readErrIdx] = errSize;
    m_readErrIdx = static_cast<short>(m_readErrIdx + 1) >= 4 ? 0 : m_readErrIdx + 1;
}

void DrMdoCtlSeamRead::callInstPosStream(_wkSeamReadWait* wait) {
    DrResMdoSeamWrkInst* wrk = wait->m_pInst;
    const MapHead::ResSize* tbl = reinterpret_cast<const MapHead::ResSize*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_instPosTblOfs);
    const MapHead::ResSize* entry = &tbl[wait->m_idx];
    unsigned int rest = entry->m_size & 0xFFF;
    DrResMdoSeamMemObj* memObj = m_memMan.createFreeObj((rest == 0 ? 0 : 0x1000 - rest) + entry->m_size);
    if (memObj != nullptr) {
        int readIdx;
        if (m_seamRead.read(readIdx, entry->m_ofs, entry->m_size, memObj)) {
            wrk->m_cacheFlags |= 0x20;
            memObj->m_flags |= 4;
            int num = m_readCallNum++;
            if (num >= 7) {
                m_seamFlags |= 0x80000;
            }
            _wkSeamReadCall* call = &m_readCall[num];
            call->m_pMemObj = memObj;
            call->m_pInst = wrk;
            call->m_cacheParam = entry->m_size;
            call->m_type = 10;
            call->m_readIdx = readIdx;
            call->m_cacheIdx = wait->m_idx;
            call->m_attr = wait->m_attr;
            m_seamFlags |= 0x10000;
            return;
        }
        m_memMan.releaseFreeObj(memObj);
    }
    unsigned int size = entry->m_size;
    m_readErrType[m_readErrIdx] = 10;
    m_readErrSize[m_readErrIdx] = size;
    m_readErrIdx = static_cast<short>(m_readErrIdx + 1) >= 4 ? 0 : m_readErrIdx + 1;
    m_seamFlags |= 0x200000;
}

void DrMdoCtlSeamRead::callMpfEtclStream(_wkSeamReadWait* wait) {
    const MapHead::ResSize* tbl = reinterpret_cast<const MapHead::ResSize*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_mpfEtcTblOfs);
    const MapHead::ResSize* entry = &tbl[wait->m_idx];
    unsigned int rest = entry->m_size & 0xFFF;
    DrResMdoSeamMemObj* memObj = m_memMan.createFreeObj((rest == 0 ? 0 : 0x1000 - rest) + entry->m_size);
    if (memObj != nullptr) {
        int readIdx;
        if (m_seamRead.read(readIdx, entry->m_ofs, entry->m_size, memObj)) {
            DrResMdoSeamWrkMpf* wrk = wait->m_pMpf;
            wrk->m_cacheFlags |= 1;
            memObj->m_flags |= 4;
            int num = m_readCallNum++;
            if (num >= 7) {
                m_seamFlags |= 0x80000;
            }
            _wkSeamReadCall* call = &m_readCall[num];
            call->m_pMemObj = memObj;
            call->m_pMpf = wrk;
            call->m_cacheParam = entry->m_size;
            call->m_type = 11;
            call->m_readIdx = readIdx;
            call->m_cacheIdx = wait->m_idx;
            call->m_attr = wait->m_attr;
            m_seamFlags |= 0x10000;
            return;
        }
        m_memMan.releaseFreeObj(memObj);
    }
    unsigned int size = entry->m_size;
    m_readErrType[m_readErrIdx] = 11;
    m_readErrSize[m_readErrIdx] = size;
    m_readErrIdx = static_cast<short>(m_readErrIdx + 1) >= 4 ? 0 : m_readErrIdx + 1;
    m_seamFlags |= 0x200000;
}

void DrMdoCtlSeamRead::callMpfPolilStream(_wkSeamReadWait* wait) {
    const MapHead::ResSize* tbl = reinterpret_cast<const MapHead::ResSize*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_mpfPoliTblOfs);
    const MapHead::ResSize* entry = &tbl[wait->m_idx];
    unsigned int rest = entry->m_size & 0xFFF;
    DrResMdoSeamMemObj* memObj = m_memMan.createFreeObj((rest == 0 ? 0 : 0x1000 - rest) + entry->m_size);
    if (memObj != nullptr) {
        int readIdx;
        if (m_seamRead.read(readIdx, entry->m_ofs, entry->m_size, memObj)) {
            DrResMdoSeamWrkMpf* wrk = wait->m_pMpf;
            wrk->m_cacheFlags |= 1;
            memObj->m_flags |= 4;
            int num = m_readCallNum++;
            if (num >= 7) {
                m_seamFlags |= 0x80000;
            }
            _wkSeamReadCall* call = &m_readCall[num];
            call->m_pMemObj = memObj;
            call->m_pMpf = wrk;
            call->m_cacheParam = entry->m_size;
            call->m_type = 12;
            call->m_readIdx = readIdx;
            call->m_cacheIdx = wait->m_idx;
            call->m_attr = wait->m_attr;
            m_seamFlags |= 0x10000;
            return;
        }
        m_memMan.releaseFreeObj(memObj);
    }
    unsigned int size = entry->m_size;
    m_readErrType[m_readErrIdx] = 12;
    m_readErrSize[m_readErrIdx] = size;
    m_readErrIdx = static_cast<short>(m_readErrIdx + 1) >= 4 ? 0 : m_readErrIdx + 1;
    m_seamFlags |= 0x200000;
}

void DrMdoCtlSeamRead::callLightStream(_wkSeamReadWait* wait) {
    const MdsSeamLgtMapData* tbl = reinterpret_cast<const MdsSeamLgtMapData*>(
        reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_lightTblOfs);
    const MdsSeamLgtMapData* entry = &tbl[wait->m_idx];
    unsigned int rest = entry->id & 0xFFF;
    DrResMdoSeamMemObj* memObj = m_memMan.createFreeObj((rest == 0 ? 0 : 0x1000 - rest) + entry->id);
    if (memObj != nullptr) {
        DrResMdoSeamWrkLight* wrk = m_lightPool.m_freeHead;
        if (wrk != nullptr) {
            DrResMdoSeamWrkLight* next = wrk->m_prev;
            if (next == nullptr) {
                m_lightPool.m_freeHead = nullptr;
                m_lightPool.m_freeTail = nullptr;
            } else {
                m_lightPool.m_freeHead = next;
                next->m_next = nullptr;
            }
            if (m_lightPool.m_usedTail != nullptr) {
                m_lightPool.m_usedTail->m_prev = wrk;
            }
            if (m_lightPool.m_list == nullptr) {
                m_lightPool.m_list = wrk;
            }
            wrk->m_next = m_lightPool.m_usedTail;
            wrk->m_prev = nullptr;
            m_lightPool.m_freeNum--;
            m_lightPool.m_usedNum++;
            m_lightPool.m_usedTail = wrk;
            int readIdx;
            if (m_seamRead.read(readIdx, entry->m_ofs, entry->id, memObj)) {
                wrk->m_memObj = memObj;
                wrk->m_dataIdx = wait->m_idx;
                memObj->m_flags |= 4;
                int num = m_readCallNum++;
                if (num >= 7) {
                    m_seamFlags |= 0x80000;
                }
                _wkSeamReadCall* call = &m_readCall[num];
                call->m_pMemObj = memObj;
                call->m_pLight = wrk;
                call->m_cacheParam = entry->id;
                call->m_type = 13;
                call->m_readIdx = readIdx;
                call->m_cacheIdx = wait->m_idx;
                call->m_attr = wait->m_attr;
                m_seamFlags |= 0x10000;
                return;
            }
            releaseFreeSeamLight(wrk);
        }
        m_memMan.releaseFreeObj(memObj);
    }
    unsigned int size = entry->id;
    m_readErrType[m_readErrIdx] = 13;
    m_readErrSize[m_readErrIdx] = size;
    m_readErrIdx = static_cast<short>(m_readErrIdx + 1) >= 4 ? 0 : m_readErrIdx + 1;
    m_seamFlags |= 0x200000;
}

void DrMdoCtlSeamRead::waitMpfMdlStream(_wkSeamReadCall* call, bool ok) {
    if (ok) {
        DrResMdoSeamWrkMpf* wrk = call->m_pMpf;
        const MdsSeamMpfMapHead* head = reinterpret_cast<const MdsSeamMpfMapHead*>(wrk->m_memObj->m_pData);
        const unsigned char* data = reinterpret_cast<const unsigned char*>(head);
        initMpfMaterial(data + head->m_dataOfs[1], data + head->m_dataOfs[3], data + head->m_dataOfs[0],
                        data + head->m_dataOfs[4], true);
        const DrResMdoSeamWrkMpf::MapEntry* tbl = reinterpret_cast<const DrResMdoSeamWrkMpf::MapEntry*>(
            reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_mpfMdlTblOfs);
        m_mpfMemSize += tbl[wrk->m_dataIdx].m_size;
        MdoWrkMatRes* matRes = m_pWrkMatRes;
        m_pMpfBits[wrk->m_dataIdx >> 5] |= 1 << (wrk->m_dataIdx & 0x1F);
        m_mpfNum++;
        wrk->setupWork(matRes, m_pDrMan->m_allocHandle, head, m_pDrMan->m_mdlMan->m_mpfMan);
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitBaseMapStream(_wkSeamReadCall* call, bool ok) {
    if (ok) {
        initBaseMapParts(call->m_pBase);
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitLowMdlStream(_wkSeamReadCall* call, bool ok) {
    if (ok) {
        initLowMapParts(call->m_pLow);
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitInstMapStream(_wkSeamReadCall* call, bool ok) {
    if (ok) {
        initInstMapParts(call->m_pInst, call->m_pInst2);
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitEnvMdlStream(_wkSeamReadCall* call, bool ok) {
    if (ok) {
        initEnvMapParts(call->m_pEnv);
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitBaseVertexStream(_wkSeamReadCall* call, bool ok) {
    DrResMdoSeamWrkBase* wrk = call->m_pBase;
    if (ok) {
        wrk->setVertexCache(call->m_cacheIdx, call->m_pMemObj, call->m_cacheParam, this);
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
        m_baseShadowCacheDone = 0;
    } else {
        wrk->m_cacheFlags |= 0x10;
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitVertexStream(_wkSeamReadCall* call, bool ok) {
    DrResMdoSeamVertex* vtx = call->m_pVertex;
    vtx->m_cnt = 0;
    if (ok) {
        const MapHead::ResSize* tbl = reinterpret_cast<const MapHead::ResSize*>(
            reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_vertexTblOfs);
        vtx->createVertex();
        m_vertexMemSize += tbl[vtx->m_dataIdx].m_size;
        unsigned short idx = vtx->m_dataIdx;
        m_pVertexNo[idx] = vtx->m_no + 1;
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 3) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitTexutreStream(_wkSeamReadCall* call, bool ok) {
    DrResMdoSeamTexture* tex = call->m_pTexture;
    tex->m_cnt = 0;
    if (ok) {
        const MapHead::TexSize* tbl = reinterpret_cast<const MapHead::TexSize*>(
            reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_textureTblOfs);
        tex->createTexture(tbl[tex->m_dataIdx].m_size);
        m_textureMemSize += tbl[tex->m_dataIdx].m_size;
        unsigned short idx = tex->m_dataIdx;
        m_pTextureNo[idx] = tex->m_no + 1;
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 4) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitHeightTexutreStream(_wkSeamReadCall* call, bool ok) {
    DrResMdoSeamTexture* tex = call->m_pTexture;
    tex->m_cnt = 0;
    tex->m_heightCnt = 0;
    if (tex->m_heightMemObj != nullptr) {
        DrResMdoSeamMemObj* memObj = tex->m_memObj;
        tex->m_memObj = tex->m_heightMemObj;
        tex->m_heightMemObj = nullptr;
        releaseFreeSeamMemObj(memObj);
    }
    if (ok) {
        const MapHead::TexSize* tbl = reinterpret_cast<const MapHead::TexSize*>(
            reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_textureTblOfs);
        const MapHead::TexSize* entry = &tbl[tex->m_dataIdx];
        unsigned int rest = entry->m_heightSize & 0xFFF;
        tex->createHeightTexture((rest == 0 ? 0 : 0x1000 - rest) + entry->m_heightSize, entry->m_size);
        tex->m_heightReady = 1;
        m_textureMemSize += entry->m_heightSize;
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    }
}

void DrMdoCtlSeamRead::waitTexListStream(_wkSeamReadCall* call, bool ok) {
    DrResMdoSeamTexList* list = call->m_pTexList;
    list->m_cnt = 0;
    if (ok) {
        const MapHead::ResSize* tbl = reinterpret_cast<const MapHead::ResSize*>(
            reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_texListTblOfs);
        list->createTextureList(m_pDrMan->m_allocHandle);
        m_textureMemSize += tbl[list->m_dataIdx].m_size;
        unsigned short idx = list->m_dataIdx;
        m_pTexListNo[idx] = list->m_no + 1;
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 2) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitInstPosStream(_wkSeamReadCall* call, bool ok) {
    DrResMdoSeamWrkInst* wrk = call->m_pInst;
    if (ok) {
        if (wrk->setEtcPosCache(m_pDrMan->m_allocHandle, call->m_cacheIdx, call->m_pMemObj, &m_instAnm)) {
            m_instShadowCacheDone = 0;
        } else {
            releaseFreeSeamMemObj(call->m_pMemObj);
        }
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
        wrk->m_cacheFlags |= 0x20;
    }
}

void DrMdoCtlSeamRead::waitMpfEtcStream(_wkSeamReadCall* call, bool ok) {
    DrResMdoSeamWrkMpf* wrk = call->m_pMpf;
    if (ok) {
        wrk->setEtcMpfCache(call->m_cacheIdx, call->m_pMemObj);
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        wrk->m_cacheFlags |= 1;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitMpfPoliStream(_wkSeamReadCall* call, bool ok) {
    DrResMdoSeamWrkMpf* wrk = call->m_pMpf;
    if (ok) {
        wrk->setMpfPoliCache(call->m_cacheIdx, call->m_pMemObj);
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        wrk->m_cacheFlags |= 1;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoCtlSeamRead::waitLightStream(_wkSeamReadCall* call, bool ok) {
    if (ok) {
        DrResMdoSeamWrkLight* lgt = call->m_pLight;
        const MdsSeamLgtMapData* tbl = reinterpret_cast<const MdsSeamLgtMapData*>(
            reinterpret_cast<const unsigned char*>(m_pMapHead) + m_pMapHead->m_lightTblOfs);
        const MdsSeamLgtMapData* data = &tbl[lgt->m_dataIdx];
        m_lightMemSize += data->id;
        m_pLightBits[static_cast<unsigned int>(lgt->m_dataIdx) >> 5] |= 1 << (lgt->m_dataIdx & 0x1F);
        m_lightNum++;
        lgt->setupWork(data);
        DrEnvironmentObj* env = lgt->m_envObj;
        env->m_flags |= 4;
        env->m_group = m_lightGroup;
        m_seamRead.m_readWaitBits &= ~(1 << call->m_readIdx);
    } else {
        m_seamFlags |= 0x10000;
        if (m_pDrMan->m_seamReadErrMode >= 1) {
            m_seamFlags |= 0x400;
        }
    }
}

void DrMdoSetup::uniformBlock_no(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {}

void DrMdoSetup::uniformBlock_Static(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Material(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pWrkMatRes->m_pMatUniformArray->m_pArray[static_cast<unsigned int>(matIdx)].setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Light(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_calcMan->m_pViewWork->m_lightBlock.setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Mdl(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pWrkMatRes->m_pTriUniformArray->m_pArray[static_cast<unsigned int>(mdlIdx)].setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Bone(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_shdMan->m_dataList->m_boneStmOut.setStorageBuffer(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_OldMdl(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    grlib::CGLibTriUniformBlock* block = &m_pWrkMatRes->m_pTriUniformArray->m_pArray[static_cast<unsigned int>(mdlIdx)];
    unsigned int location = m_pDecExtTbl->getValGlobalParam(paramIdx);
    if (!(m_mdlFlags & 0x200)) {
        block->setOldUniformBlock(location);
    } else {
        block->setUniformBlock(location);
    }
}

void DrMdoSetup::uniformBlock_OldBone(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    DrShdDataList* list = m_pDrMan->m_shdMan->m_dataList;
    unsigned int location = m_pDecExtTbl->getValGlobalParam(paramIdx);
    if (!(m_mdlFlags & 0x200)) {
        list->m_oldBoneStmOut.setStorageBuffer(location);
    } else {
        list->m_boneStmOut.setStorageBuffer(location);
    }
}

void DrMdoSetup::uniformBlock_AvatarChar(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pWrkMatRes->m_pAvatarTbl->m_charBlock->setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_AvatarDoll(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pWrkMatRes->m_pAvatarTbl->m_dollBlock->setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Fog(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_calcMan->m_pViewWork->m_fogBlock.setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Toon(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_calcMan->m_pViewWork->m_toonBlock.setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_VolTexCalc(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pWrkMatRes->m_pVolTexUniformArray->m_pArray[texIdx].setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_GlobalIBL(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_pixlMan->m_objTbl->m_postMan->m_cubeMapIBL->setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_ClusterParam(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    DrShdLgtClustered* clustered = m_pDrMan->m_shdMan->m_lgtMan->getHybridLight()->m_pClustered;
    unsigned int location = m_pDecExtTbl->getValGlobalParam(paramIdx);
    if (cate->m_flags & 1) {
        clustered->setParamStorageBuffer(m_pDrMan->m_postParmIdx, location);
    } else {
        clustered->setParamUniformBlock(m_pDrMan->m_postParmIdx, location);
    }
}

void DrMdoSetup::uniformBlock_ClusterPntList(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    DrShdLgtClustered* clustered = m_pDrMan->m_shdMan->m_lgtMan->getHybridLight()->m_pClustered;
    unsigned int location = m_pDecExtTbl->getValGlobalParam(paramIdx);
    if (cate->m_flags & 1) {
        clustered->setPntLightStorageBuffer(m_pDrMan->m_postParmIdx, location);
    } else {
        clustered->setPntLightUniformBlock(m_pDrMan->m_postParmIdx, location);
    }
}

void DrMdoSetup::uniformBlock_ClusterSptList(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    DrShdLgtClustered* clustered = m_pDrMan->m_shdMan->m_lgtMan->getHybridLight()->m_pClustered;
    unsigned int location = m_pDecExtTbl->getValGlobalParam(paramIdx);
    if (cate->m_flags & 1) {
        clustered->setSptLightStorageBuffer(m_pDrMan->m_postParmIdx, location);
    } else {
        clustered->setSptLightUniformBlock(m_pDrMan->m_postParmIdx, location);
    }
}

void DrMdoSetup::uniformBlock_ClusterIdxList(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    DrShdLgtClustered* clustered = m_pDrMan->m_shdMan->m_lgtMan->getHybridLight()->m_pClustered;
    unsigned int location = m_pDecExtTbl->getValGlobalParam(paramIdx);
    if (cate->m_flags & 1) {
        clustered->setLightListStorageBuffer(m_pDrMan->m_postParmIdx, location);
    } else {
        clustered->setLightListUniformBlock(m_pDrMan->m_postParmIdx, location);
    }
}

void DrMdoSetup::uniformBlock_ClusterAddressList(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    DrShdLgtClustered* clustered = m_pDrMan->m_shdMan->m_lgtMan->getHybridLight()->m_pClustered;
    unsigned int location = m_pDecExtTbl->getValGlobalParam(paramIdx);
    if (cate->m_flags & 1) {
        clustered->setPointerListStorageBuffer(m_pDrMan->m_postParmIdx, location);
    } else {
        clustered->setPointerListUniformBlock(m_pDrMan->m_postParmIdx, location);
    }
}

void DrMdoSetup::uniformBlock_RimBloomCalc(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pWrkMatRes->m_pRimBloomUniformArray->m_pArray[static_cast<unsigned int>(mdlIdx)].setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

void DrMdoSetup::uniformBlock_Toon2(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx) {
    m_pDrMan->m_calcMan->m_pViewWork->m_toon2Block.setUniformBlock(m_pDecExtTbl->getValGlobalParam(paramIdx));
}

int DrMdoSetup::unimate_texMatrix(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var) {
    grlib::ShdF32SetF32Array(out, m_pWrkMatRes->m_pUniformVal + (info->m_uniformOfs + var->m_valIdx), var->m_num * 8);
    return DrResMdoUniformBlock::s_nVarSizeTbl[17] * var->m_num;
}

int DrMdoSetup::unimate_workFloat4(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var) {
    grlib::ShdF32SetF32Array(out, m_pWrkMatRes->m_pUniformVal + (info->m_uniformOfs + var->m_valIdx), var->m_num * 4);
    return DrResMdoUniformBlock::s_nVarSizeTbl[18] * var->m_num;
}

int DrMdoSetup::unimate_workColor(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var) {
    grlib::ShdF32SetF32Array(out, m_pWrkMatRes->m_pUniformVal + (info->m_uniformOfs + var->m_valIdx), var->m_num * 4);
    return DrResMdoUniformBlock::s_nVarSizeTbl[19] * var->m_num;
}

int DrMdoSetup::unimate_ProjectionMat(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var) {
    const float* src = m_pWrkMatRes->m_pUniformVal + (info->m_uniformOfs + var->m_valIdx);
    for (int i = 0; i < var->m_num; i++) {
        grlib::ShdF32TransposeMat34(&out[i * 12], &src[i * 16]);
    }
    return DrResMdoUniformBlock::s_nVarSizeTbl[20] * var->m_num;
}

int DrMdoSetup::unimate_alphaInfo(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var) {
    out[0] = 1.0f;
    out[1] = mat->m_alphaParam;
    float alpha = mat->m_color.a;
    if (!(info->m_flags & 1)) {
        alpha *= m_singleAlpha;
    }
    out[2] = alpha;
    out[3] = m_colorScale;
    return DrResMdoUniformBlock::s_nVarSizeTbl[23];
}

int DrMdoSetup::unimate_matColor(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var) {
    if (m_renderPass == 0 && !(info->m_shdFlags & 0x80)) {
        out[0] = mat->m_color.r;
        out[1] = mat->m_color.g;
        out[2] = mat->m_color.b;
    } else {
        float rate = m_pDrMan->m_pixlMan->m_rate;
        out[0] = powf(mat->m_color.r, rate);
        out[1] = powf(mat->m_color.g, rate);
        out[2] = powf(mat->m_color.b, rate);
    }
    float alpha = mat->m_color.a;
    if (!(info->m_flags & 1)) {
        alpha *= m_singleAlpha;
    }
    out[3] = alpha;
    return DrResMdoUniformBlock::s_nVarSizeTbl[24];
}

int DrMdoSetup::unimate_NomProjectionMat(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var) {
    const float* src = m_pWrkMatRes->m_pUniformVal + (info->m_uniformOfs + var->m_valIdx);
    for (int i = 0; i < var->m_num; i++) {
        grlib::ShdF32TransposeMat34(&out[i * 12], &src[i * 16]);
    }
    return DrResMdoUniformBlock::s_nVarSizeTbl[50] * var->m_num;
}

int DrMdoSetup::unimate_AvatarMapWrk(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var) {
    const MdsMatAvatarMap* map = m_pWrkMatRes->m_pAvatarMap + info->m_avatarMapIdx;
    const mm::Col3& color0 = m_pAvatarColor[map->m_colorIdx[0]];
    const mm::Col3& color1 = m_pAvatarColor[map->m_colorIdx[1]];
    const mm::Col3& color2 = m_pAvatarColor[map->m_colorIdx[2]];
    out[0] = color0.r;
    out[1] = color0.g;
    out[2] = color0.b;
    out[3] = 0.0f;
    out[4] = color1.r;
    out[5] = color1.g;
    out[6] = color1.b;
    out[7] = 0.0f;
    out[8] = color2.r;
    out[9] = color2.g;
    out[10] = color2.b;
    out[11] = 0.0f;
    return DrResMdoUniformBlock::s_nVarSizeTbl[51];
}
// Opaque objects: buckets 4..505 (the comment is inferred).
void DrMdoZSortMan::setViewWorldPos(DrMdoZSortObj* obj, const mm::Vec3& pos) {
    float dx = pos.x - m_viewPos.x;
    float dy = pos.y - m_viewPos.y;
    float dz = pos.z - m_viewPos.z;
    float dist = sqrtf(dx * dx + dy * dy + dz * dz) / m_sortFar;
    if (dist >= 1.0f) {
        stockObj(obj, 505);
    } else if (dist <= 0.001f) {
        stockObj(obj, 4);
    } else {
        int idx = static_cast<int>(powf(dist, m_sortRate) * 502.0f);
        stockObj(obj, idx + 4 > 505 ? 505 : (idx < 0 ? 4 : idx + 4));
    }
}

// Last alpha objects: buckets 0..3.
void DrMdoZSortMan::setViewWorldPosLastAlpha(DrMdoZSortObj* obj, const mm::Vec3& pos) {
    float dx = pos.x - m_viewPos.x;
    float dy = pos.y - m_viewPos.y;
    float dz = pos.z - m_viewPos.z;
    float dist = sqrtf(dx * dx + dy * dy + dz * dz) / m_sortFar;
    if (dist >= 1.0f) {
        stockObj(obj, 3);
    } else if (dist <= 0.001f) {
        stockObj(obj, 0);
    } else {
        int idx = static_cast<int>(powf(dist, m_sortRate) * 4.0f);
        stockObj(obj, idx > 3 ? 3 : (idx < 0 ? 0 : idx));
    }
}

// Fast alpha objects: buckets 506..509 (the comment is inferred).
void DrMdoZSortMan::setViewWorldPosFastAlpha(DrMdoZSortObj* obj, const mm::Vec3& pos) {
    float dx = pos.x - m_viewPos.x;
    float dy = pos.y - m_viewPos.y;
    float dz = pos.z - m_viewPos.z;
    float dist = sqrtf(dx * dx + dy * dy + dz * dz) / m_sortFar;
    if (dist >= 1.0f) {
        stockObj(obj, 509);
    } else if (dist <= 0.001f) {
        stockObj(obj, 506);
    } else {
        int idx = static_cast<int>(powf(dist, m_sortRate) * 4.0f);
        stockObj(obj, idx + 506 >= 509 ? 509 : (idx < 0 ? 506 : idx + 506));
    }
}

DrMdoSmlShadowMan::DrMdoSmlShadowMan(DrMan* man)
    : pad_0(0), m_viewIdx(0), m_pDrMan(man), m_viewList(), m_dblList(), m_delList() {}

DrMdoSmlShadowMan::~DrMdoSmlShadowMan() {
    for (int i = 0; i < 2; i++) {
        m_dblList[i].deleteAll();
    }
    m_delList.deleteAll();
    for (int i = 0; i < 4; i++) {
        m_viewList[i].deleteAll();
    }
}

void DrMdoSmlShadowMan::addObjList(int viewNum) {
    DrMdoSmlShadowObj* obj = m_dblList[DrMan::s_nDblIdx].m_pHead;
    while (obj != nullptr) {
        if (obj->m_viewNum == viewNum) {
            DrMdoSmlShadowObj* next = obj->m_pNext;
            m_dblList[DrMan::s_nDblIdx].remove(obj);
            m_viewList[viewNum].pushBack(obj);
            obj = next;
        } else {
            obj = obj->m_pNext;
        }
    }
}

void DrMdoSmlShadowMan::updateList() {
    DrMdoSmlShadowObj* obj = m_viewList[m_viewIdx].m_pHead;
    if (obj == nullptr) {
        return;
    }
    unsigned int mask = 0x4000 << DrMan::s_nDblIdx;
    while (obj != nullptr) {
        if (obj->m_flags & mask) {
            DrMdoSmlShadowObj* next = obj->m_pNext;
            m_viewList[m_viewIdx].remove(obj);
            m_delList.pushBack(obj);
            obj = next;
        } else {
            obj = obj->m_pNext;
        }
    }
}

bool DrMdoSmlShadowMan::checkDisp() {
    for (DrMdoSmlShadowObj* obj = m_viewList[m_viewIdx].m_pHead; obj != nullptr; obj = obj->m_pNext) {
        if (obj->m_flags & 1) {
            return true;
        }
    }
    return false;
}

void DrMdoSmlShadowMan::delObjList() {
    m_dblList[DrMan::s_nDblIdx].m_pHead = nullptr;
    m_dblList[DrMan::s_nDblIdx].m_pTail = nullptr;
    m_delList.deleteAll();
}

void DrMdoSmlShadowMan::changeViewNum(DrMdoSmlShadowObj* obj, int viewNum) {
    if (obj->m_viewNum != viewNum) {
        m_viewList[obj->m_viewNum].remove(obj);
        m_viewList[viewNum].pushBack(obj);
        obj->m_viewNum = viewNum;
    }
}

DrMdoTexSimpleMan::DrMdoTexSimpleMan(DrMan* drMan)
    : m_pDrMan(drMan), m_list0(), m_list1(), m_list3(), m_list2() {}

DrMdoTexSimpleMan::~DrMdoTexSimpleMan() {
    m_list0.deleteAll();
    m_list1.deleteAll();
    m_list2.deleteAll();
    m_list3.deleteAll();
}

DrMdoTextureMan::DrMdoTextureMan(DrMan* drMan) : m_pDrMan(drMan), m_texList(), m_etcTexList() {}

DrMdoTextureMan::~DrMdoTextureMan() {
    m_texList.deleteAll();
    m_etcTexList.deleteAll();
}

grlib::CGLibTextureBuffer* DrMdoTextureMan::getTextureID(unsigned int id) {
    for (DrResEtcTexList* list = m_etcTexList.m_pHead; list != nullptr; list = list->m_pNext) {
        grlib::CGLibTextureBuffer* texture = list->getTextureID(id);
        if (texture != nullptr) {
            return texture;
        }
    }
    return nullptr;
}

void DrMdoTextureMan::update() {
    for (DrResMdoTexList* list = m_texList.m_pHead; list != nullptr; list = list->m_pNext) {
        list->update();
    }
    DrResEtcTexList* list = m_etcTexList.m_pHead;
    while (list != nullptr) {
        DrResEtcTexList* next = list->m_pNext;
        if (list->m_flags & 1) {
            m_etcTexList.remove(list);
            delete list;
        }
        list = next;
    }
}

DrMdoVertexMan::DrMdoVertexMan() : m_vertexList(), m_instans(nullptr) {
    m_instans = new (DrMan::getIns()->m_workHandle, nullptr, 0, 4, false) grlib::CGLibVtxInstans;
    m_instans->createInstansBuffer(s_nInstansBuffSize);
}

DrMdoVertexMan::~DrMdoVertexMan() {
    m_vertexList.deleteAll();
    if (m_instans != nullptr) {
        delete m_instans;
        m_instans = nullptr;
    }
}

void DrMdoVertexMan::update() {
    for (DrResMdoVertex* vertex = m_vertexList.m_pHead; vertex != nullptr; vertex = vertex->m_pNext) {
        vertex->update();
    }
}

void DrMdoVertexMan::begin() { m_instans->beginInstansBuff(); }

void DrMdoVertexMan::end() { m_instans->updateInstansBuff(); }

}  // namespace ml

template void grlib::CGLibUniformArray<grlib::CGLibOneUniformBlock>::setupArray(unsigned int);
template void grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>::setupArray(unsigned int);
template void grlib::CGLibUniformArray<grlib::CGLibTriUniformBlock>::setupArray(unsigned int);

namespace ml {
DrResMdoVertex* DrMdoVertexMan::createVertexObj(DrCalcStmListObj* stm) {
    for (DrResMdoVertex* vertex = m_vertexList.m_pHead; vertex != nullptr; vertex = vertex->m_pNext) {
        if (vertex->m_resData == static_cast<const void*>(stm)) {
            vertex->m_state++;
            return vertex;
        }
    }
    DrCalcStmListObj::ResTexObj* res = stm->getResVertexObj();
    DrResMdoVertex* vertex = new (DrMan::getIns()->m_resHandle, nullptr, 0, 4, false) DrResMdoVertex(res->m_pData);
    vertex->m_stream = stm;
    if (vertex != nullptr) {
        m_vertexList.pushBack(vertex);
    }
    return vertex;
}

void DrMdoVertexMan::releaseVertexObj(DrResMdoVertex* vertex) {
    if (--vertex->m_state < 0) {
        vertex->m_state = 0;
    }
    if (vertex->m_state > 0) {
        return;
    }
    m_vertexList.remove(vertex);
    delete vertex;
}

DrMdoZSortMan::DrMdoZSortMan(DrMan* drMan)
    : m_pDrMan(drMan), m_pBuff(nullptr), m_pSpecial(nullptr), m_sortFar(300.0f), m_sortRate(0.8f) {
    m_pBuff = mtl::MemManager::allocate(drMan->m_workHandle, sizeof(DrMdoZSortObj*) * SORT_MAX * 2 + SORT_MAX / 8, 0x20,
                                        false, "no name", 0);
    m_top = static_cast<DrMdoZSortObj**>(m_pBuff);
    m_last = m_top + SORT_MAX;
    m_useBits = reinterpret_cast<unsigned int*>(m_last + SORT_MAX);
}

DrMdoZSortMan::~DrMdoZSortMan() {
    if (m_pBuff != nullptr) {
        mtl::MemManager::deallocate(m_pBuff, 0, false);
        m_pBuff = nullptr;
    }
}

void DrMdoZSortMan::beginViewWorld() {
    const mm::Vec3& viewPos = m_pDrMan->m_calcMan->m_pViewWork->m_viewPos;
    memset(m_useBits, 0, SORT_MAX / 8);
    m_viewPos.x = viewPos.x;
    m_viewPos.y = viewPos.y;
    m_viewPos.z = viewPos.z;
    m_head = nullptr;
    m_tail = nullptr;
    m_pSpecial = nullptr;
}

void DrMdoZSortMan::setViewCloud(DrMdoZSortObj* obj) {
    stockObj(obj, SORT_CLOUD);
}

void DrMdoZSortMan::endViewWorld() {
    for (int i = 0; i < SORT_MAX; i++) {
        if (m_useBits[i >> 5] & (1 << (i & 0x1F))) {
            if (m_head != nullptr) {
                m_tail->setNext(m_top[i]);
                m_top[i]->setParent(m_tail);
            } else {
                m_head = m_top[i];
            }
            m_tail = m_last[i];
        }
    }
}

void DrMdoZSortMan::viewSetupRender() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->SetupRender();
    }
    for (DrMdoZSortObj* obj = m_head; obj != nullptr; obj = obj->getNext()) {
        obj->SetupRender();
    }
}

void DrMdoZSortMan::viewZPrepassRender() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->ZPrepassRender();
    }
    for (DrMdoZSortObj* obj = m_head; obj != nullptr; obj = obj->getNext()) {
        obj->ZPrepassRender();
    }
}

void DrMdoZSortMan::viewThicknessRenderFirst() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->ThicknessRenderFirst();
    }
    for (DrMdoZSortObj* obj = m_head; obj != nullptr; obj = obj->getNext()) {
        obj->ThicknessRenderFirst();
    }
}

void DrMdoZSortMan::viewThicknessRenderSecond() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->ThicknessRenderSecond();
    }
    for (DrMdoZSortObj* obj = m_head; obj != nullptr; obj = obj->getNext()) {
        obj->ThicknessRenderSecond();
    }
}

void DrMdoZSortMan::viewRender() {
    for (DrMdoZSortObj* obj = m_head; obj != nullptr; obj = obj->getNext()) {
        obj->render();
    }
    if (m_pSpecial != nullptr) {
        m_pSpecial->render();
    }
}

void DrMdoZSortMan::viewGBuffRender() {
    for (DrMdoZSortObj* obj = m_head; obj != nullptr; obj = obj->getNext()) {
        obj->GBuffRender();
    }
    if (m_pSpecial != nullptr) {
        m_pSpecial->GBuffRender();
    }
}

void DrMdoZSortMan::viewLightPrePassRender() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->lightPrePassRender();
    }
    // back to front
    for (DrMdoZSortObj* obj = m_tail; obj != nullptr; obj = obj->getParent()) {
        obj->lightPrePassRender();
    }
}

void DrMdoZSortMan::viewAlphaRender() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->alphaRender();
    }
    // back to front
    for (DrMdoZSortObj* obj = m_tail; obj != nullptr; obj = obj->getParent()) {
        obj->alphaRender();
    }
}

void DrMdoZSortMan::viewSpAlphaRender() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->spAlphaRender();
    }
    // back to front
    for (DrMdoZSortObj* obj = m_tail; obj != nullptr; obj = obj->getParent()) {
        obj->spAlphaRender();
    }
}

void DrMdoZSortMan::viewRefractionRender() {
    if (m_pSpecial != nullptr) {
        m_pSpecial->refractionRender();
    }
    // back to front
    for (DrMdoZSortObj* obj = m_tail; obj != nullptr; obj = obj->getParent()) {
        obj->refractionRender();
    }
}

DrMdoSamplerMan::DrMdoSamplerMan(DrMan* drMan) : m_samplerList(), m_pDrMan(drMan) {}

DrMdoSamplerMan::~DrMdoSamplerMan() { m_samplerList.deleteAll(); }

void DrMdoSamplerMan::begin() {
    if (DrMan::get()->m_pMdlSampler->update()) {
        for (DrResMdoSampler* sampler = m_samplerList.m_pHead; sampler != nullptr; sampler = sampler->m_pNext) {
            sampler->setup();
        }
    }
}

DrMdoMorphing::DrMdoMorphing(MdoWrkMatRes* wrkMatRes, DrResMdoMorpObj* morpObj, DrResEtcPamObj* pamObj)
    : m_pWrkMatRes(wrkMatRes), m_pMorpObj(morpObj), m_pPamObj(pamObj) {}

DrMdoMorphing::~DrMdoMorphing() {}

int DrMdoMorphing::isBlendCheck() const {
    int ret = 0;
    int fixed = 0;
    for (unsigned int i = 0; i < m_pMorpObj->m_targetNum; i++) {
        const DrResMdoMorpObj::Target& target = m_pMorpObj->m_pTarget[i];
        if (target.m_prevWeight == target.m_weight) {
            if (target.m_weight != 0.0f) {
                fixed = 2;
                if (ret == 1) {
                    return 2;
                }
            }
        } else {
            if (fixed == 2) {
                return 2;
            }
            if (target.m_weight != 0.0f) {
                return 2;
            }
            ret = 1;
        }
    }
    return ret;
}

void DrMdoMorphing::parmsUpdate() {
    for (unsigned int i = 0; i < m_pMorpObj->m_targetNum; i++) {
        DrResMdoMorpObj::Target& target = m_pMorpObj->m_pTarget[i];
        target.m_prevWeight = target.m_weight;
    }
}

void DrMdoMorphing::updateParms() {
    if (m_pMorpObj->m_flag0 == 0) {
        m_parmsState = -1;
        for (unsigned int i = 0; i < m_pMorpObj->m_targetNum; i++) {
            DrResMdoMorpObj::Target& target = m_pMorpObj->m_pTarget[i];
            if (target.m_data->m_type == 7) {
                target.m_weight = m_pPamObj->m_params[target.m_data->m_paramNo].getParams();
            }
        }
    }
}

void DrMdoMorphing::resetDefVertex() {
    const unsigned char* data = m_pWrkMatRes->m_pVertex->m_vtxData;
    const DrResMdoVertex::MorphHead* head = reinterpret_cast<const DrResMdoVertex::MorphHead*>(
        data + reinterpret_cast<const DrResMdoVertex::VertexHead*>(data)->morphOfs);
    const DrResMdoVertex::MorphEntry* entry = reinterpret_cast<const DrResMdoVertex::MorphEntry*>(data + head->entryOfs);
    const DrResMdoVertex::MorphBuffer* buffer =
        reinterpret_cast<const DrResMdoVertex::MorphBuffer*>(data + head->bufferOfs);
    DrShdDataList* list = DrMan::getIns()->m_shdMan->m_dataList;
    grlib::CGLibPolygon::setRasterizer(1);
    DrResShdStreamOut* stmOut = list->getStmOutObj(5);
    int decl = -1;
    for (int i = 0; i < head->entryNum; i++, entry++) {
        int idx = entry->declIdx;
        if (idx != decl) {
            stmOut->m_data->setDeclarationIdx(0, idx);
            stmOut->setupStreamShader(0);
            decl = idx;
        }
        unsigned int no = entry->uniformNo;
        grlib::CGLibCtlVertex::setUniformVertex(m_pWrkMatRes->m_pMofBlendArray->m_pArray[no + 1], 0x20, 0, 0, 0);
        grlib::CGLibOneUniformArray* array = m_pWrkMatRes->m_pMofBlendArray;
        array->m_pArray[entry->uniformNo].setStorageBuffer(0);
        grlib::CGLibCtlVertex::renderVertex(static_cast<GrlPrimitiveType>(0), buffer[no + 1].vertexNum);
    }
    grlib::CGLibPolygon::setRasterizer(0);
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
}

void DrMdoMorphing::oldPosVertex() {
    const unsigned char* data = m_pWrkMatRes->m_pVertex->m_vtxData;
    const DrResMdoVertex::MorphHead* head = reinterpret_cast<const DrResMdoVertex::MorphHead*>(
        data + reinterpret_cast<const DrResMdoVertex::VertexHead*>(data)->morphOfs);
    const DrResMdoVertex::MorphEntry* entry = reinterpret_cast<const DrResMdoVertex::MorphEntry*>(data + head->entryOfs);
    const DrResMdoVertex::MorphBuffer* buffer =
        reinterpret_cast<const DrResMdoVertex::MorphBuffer*>(data + head->bufferOfs);
    DrShdDataList* list = DrMan::getIns()->m_shdMan->m_dataList;
    grlib::CGLibPolygon::setRasterizer(1);
    list->getStmOutObj(8)->setupStreamShader(0);
    for (int i = 0; i < head->entryNum; i++, entry++) {
        unsigned int no = entry->uniformNo;
        grlib::CGLibCtlVertex::setUniformVertex(m_pWrkMatRes->m_pMofBlendArray->m_pArray[no + 1], 0x20, 0, 0, 0);
        grlib::CGLibOneUniformArray* array = m_pWrkMatRes->m_pMofBlendArray;
        array->m_pArray[entry->uniformNo].setStorageBuffer(0);
        grlib::CGLibCtlVertex::renderVertex(static_cast<GrlPrimitiveType>(0), buffer[no + 1].vertexNum);
    }
    grlib::CGLibPolygon::setRasterizer(0);
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
}

const unsigned char DrMdoShdSetShadow::s_pShwUseShdader[30] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4,
                                                            0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4};
const unsigned char DrMdoShdSetShadow::s_pShwFethcDef[30] = {13, 14, 14, 13, 14, 14, 15, 16, 16, 17, 18, 18, 73, 73, 73,
                                                         13, 14, 14, 13, 14, 14, 15, 16, 16, 17, 18, 18, 73, 73, 73};
// s_pShwFethcMof is 1.0.0's name (s_pShwFethcTbl[1]); the 3.0.1 symbols leave it unnamed (lbl_71009D4964).
const unsigned char DrMdoShdSetShadow::s_pShwFethcMof[30] = {86, 87, 87, 86, 87, 87, 88, 89, 89, 17, 18, 18, 73, 73, 73,
                                                         86, 87, 87, 86, 87, 87, 88, 89, 89, 17, 18, 18, 73, 73, 73};
const unsigned char DrMdoShdSetShadow::s_pShwTypeDec[30] = {17, 33, 49, 17, 33, 49, 17, 33, 49, 17, 33, 49, 17, 33, 49,
                                                        18, 34, 50, 18, 34, 50, 18, 34, 50, 18, 34, 50, 18, 34, 50};
const unsigned char* DrMdoShdSetShadow::s_pShwFethcTbl[2] = {s_pShwFethcDef, s_pShwFethcMof};

void DrMdoShdSetShadow::shwShd_Obj(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list) {
    DrResShdShw* obj = list->getShwObj(s_pShwUseShdader[shd]);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        unsigned char dec = s_pShwTypeDec[shd];
        obj->setDecAType(dec >> 4);
        obj->setDecBType(dec & 0xF);
        obj->setupShader(list->getFetchShader(s_pShwFethcTbl[m_pMdl->m_bindFlags[1]][shd]));
        m_pMdl->m_pDrMan->m_pixlMan->m_shadowUniform->setUniformBlock(obj->m_shaderSel[2]);
        (m_pMdl->m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[1]);
    } else if (m_pMdl->m_curTriBlockIdx != triIdx) {
        (m_pMdl->m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[1]);
    }
    m_pMdl->m_curTriBlockIdx = triIdx;
}

void DrMdoShdSetShadow::shwShd_ObjT(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list) {
    DrResShdShw* obj = list->getShwObj(s_pShwUseShdader[shd]);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        unsigned char dec = s_pShwTypeDec[shd];
        obj->setDecAType(dec >> 4);
        obj->setDecBType(dec & 0xF);
        obj->setupShader(list->getFetchShader(s_pShwFethcTbl[m_pMdl->m_bindFlags[1]][shd]));
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[3]);
        m_pMdl->m_pDrMan->m_pixlMan->m_shadowUniform->setUniformBlock(obj->m_shaderSel[2]);
        (m_pMdl->m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[1]);
    } else if (m_pMdl->m_curTriBlockIdx != triIdx) {
        (m_pMdl->m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[1]);
    }
    m_pMdl->m_curTriBlockIdx = triIdx;
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
}

void DrMdoShdSetShadow::shwShd_Inst(int shd, const MdsMatInfoHeader*, int, int, DrShdDataList* list) {
    DrResShdShw* obj = list->getShwObj(s_pShwUseShdader[shd]);
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        unsigned char dec = s_pShwTypeDec[shd];
        obj->setDecAType(dec >> 4);
        obj->setDecBType(dec & 0xF);
        obj->setupShader(list->getFetchShader(s_pShwFethcDef[shd]));
        m_pMdl->m_pEtcBlock->setUniformBlock(obj->m_shaderSel[1]);
    } else if (m_pMdl->m_bindFlags[0] & 2) {
        m_pMdl->m_pEtcBlock->setUniformBlock(obj->m_shaderSel[1]);
    }
    m_pMdl->m_bindFlags[0] &= ~2;
}

void DrMdoShdSetShadow::shwShd_InstT(int shd, const MdsMatInfoHeader* info, int, int, DrShdDataList* list) {
    DrResShdShw* obj = list->getShwObj(s_pShwUseShdader[shd]);
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        unsigned char dec = s_pShwTypeDec[shd];
        obj->setDecAType(dec >> 4);
        obj->setDecBType(dec & 0xF);
        obj->setupShader(list->getFetchShader(s_pShwFethcDef[shd]));
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[3]);
        m_pMdl->m_pEtcBlock->setUniformBlock(obj->m_shaderSel[1]);
    } else if (m_pMdl->m_bindFlags[0] & 2) {
        m_pMdl->m_pEtcBlock->setUniformBlock(obj->m_shaderSel[1]);
    }
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
    m_pMdl->m_bindFlags[0] &= ~2;
}

void DrMdoShdSetShadow::shwShd_Mot(int shd, const MdsMatInfoHeader* info, int, int, DrShdDataList* list) {
    DrResShdShw* obj = list->getShwObj(s_pShwUseShdader[shd]);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        unsigned char dec = s_pShwTypeDec[shd];
        obj->setDecAType(dec >> 4);
        obj->setDecBType(dec & 0xF);
        obj->setupShader(list->getFetchShader(s_pShwFethcTbl[m_pMdl->m_bindFlags[1]][shd]));
        m_pMdl->m_pDrMan->m_pixlMan->m_shadowUniform->setUniformBlock(obj->m_shaderSel[2]);
        list->m_boneStmOut.setStorageBuffer(obj->m_shaderSel[1]);
    }
}

void DrMdoShdSetShadow::shwShd_MotT(int shd, const MdsMatInfoHeader* info, int, int, DrShdDataList* list) {
    DrResShdShw* obj = list->getShwObj(s_pShwUseShdader[shd]);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        unsigned char dec = s_pShwTypeDec[shd];
        obj->setDecAType(dec >> 4);
        obj->setDecBType(dec & 0xF);
        obj->setupShader(list->getFetchShader(s_pShwFethcTbl[m_pMdl->m_bindFlags[1]][shd]));
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[3]);
        m_pMdl->m_pDrMan->m_pixlMan->m_shadowUniform->setUniformBlock(obj->m_shaderSel[2]);
        list->m_boneStmOut.setStorageBuffer(obj->m_shaderSel[1]);
    }
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
}

void DrMdoShdSetShadow::shwShd_InstMot(int shd, const MdsMatInfoHeader*, int, int, DrShdDataList* list) {
    DrResShdShw* obj = list->getShwObj(s_pShwUseShdader[shd]);
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        unsigned char dec = s_pShwTypeDec[shd];
        obj->setDecAType(dec >> 4);
        obj->setDecBType(dec & 0xF);
        obj->setupShader(list->getFetchShader(s_pShwFethcDef[shd]));
        m_pMdl->m_pDrMan->m_pixlMan->m_shadowUniform->setUniformBlock(obj->m_shaderSel[2]);
    }
    m_pMdl->m_pDrMan->m_mdlMan->m_etcUniform->setUniformBlock(m_pMdl->m_pWrkMatRes->m_pEtcRef->m_etcIdx,
                                                              obj->m_shaderSel[1]);
}

void DrMdoShdSetShadow::shwShd_InstMotT(int shd, const MdsMatInfoHeader* info, int, int, DrShdDataList* list) {
    DrResShdShw* obj = list->getShwObj(s_pShwUseShdader[shd]);
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        unsigned char dec = s_pShwTypeDec[shd];
        obj->setDecAType(dec >> 4);
        obj->setDecBType(dec & 0xF);
        obj->setupShader(list->getFetchShader(s_pShwFethcDef[shd]));
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[3]);
        m_pMdl->m_pDrMan->m_pixlMan->m_shadowUniform->setUniformBlock(obj->m_shaderSel[2]);
    }
    m_pMdl->m_pDrMan->m_mdlMan->m_etcUniform->setUniformBlock(m_pMdl->m_pWrkMatRes->m_pEtcRef->m_etcIdx,
                                                              obj->m_shaderSel[1]);
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
}

void DrMdoShdSetShadow::shwShd_Fw(int shd, const MdsMatInfoHeader* info, int triIdx, int matIdx, DrShdDataList* list) {
    DrResShdShw* obj = list->getShwObj(s_pShwUseShdader[shd]);
    unsigned int decA = s_pShwTypeDec[shd] >> 4;
    unsigned int decB = s_pShwTypeDec[shd] & 0xF;
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setDecAType(decA);
        obj->setDecBType(decB);
        obj->setupShader(list->getFetchShader(s_pShwFethcDef[shd]));
        if (decA != 1) {
            list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[3]);
        }
        m_pMdl->m_pDrMan->m_pixlMan->m_shadowUniform->setUniformBlock(obj->m_shaderSel[2]);
        (m_pMdl->m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[1]);
        unsigned int loc = obj->m_shaderSel[5];
        DrAPCache* ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(0, 1);
        ap->setTexture(DrMan::get()->m_iniSys->m_texture[16], loc);
        loc = obj->m_shaderSel[6];
        ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(0, 1);
        ap->setTexture(DrMan::get()->m_iniSys->m_texture[17], loc);
    } else if (m_pMdl->m_curTriBlockIdx != triIdx) {
        (m_pMdl->m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[1]);
    }
    if (decA != 1) {
        setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
    }
    MdoFlagWaveRes* fw = m_pMdl->m_pWrkMatRes->m_pFlagWave;
    if (fw) {
        fw->m_pUniformArray->m_pArray[fw->m_pData[matIdx]].setUniformBlock(obj->m_shaderSel[4]);
    }
    m_pMdl->m_curTriBlockIdx = triIdx;
}

void DrMdoShdSetShadow::shwShd_Spt_Inst(int shd, const MdsMatInfoHeader*, int, int, DrShdDataList* list) {
    DrResShdShw* obj = list->getShwObj(s_pShwUseShdader[shd]);
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        unsigned char dec = s_pShwTypeDec[shd];
        obj->setDecAType(dec >> 4);
        obj->setDecBType(dec & 0xF);
        obj->setupShader(list->getFetchShader(s_pShwFethcDef[shd]));
        m_pMdl->m_pEtcBlock->setUniformBlock(obj->m_shaderSel[1]);
        m_pMdl->m_pDrMan->m_pixlMan->m_shadowUniform->setUniformBlock(obj->m_shaderSel[2]);
    } else if (m_pMdl->m_bindFlags[0] & 2) {
        m_pMdl->m_pEtcBlock->setUniformBlock(obj->m_shaderSel[1]);
    }
    m_pMdl->m_bindFlags[0] &= ~2;
}

void DrMdoShdSetShadow::shwShd_Spt_InstT(int shd, const MdsMatInfoHeader* info, int, int, DrShdDataList* list) {
    DrResShdShw* obj = list->getShwObj(s_pShwUseShdader[shd]);
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        unsigned char dec = s_pShwTypeDec[shd];
        obj->setDecAType(dec >> 4);
        obj->setDecBType(dec & 0xF);
        obj->setupShader(list->getFetchShader(s_pShwFethcDef[shd]));
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[3]);
        m_pMdl->m_pEtcBlock->setUniformBlock(obj->m_shaderSel[1]);
        m_pMdl->m_pDrMan->m_pixlMan->m_shadowUniform->setUniformBlock(obj->m_shaderSel[2]);
    } else if (m_pMdl->m_bindFlags[0] & 2) {
        m_pMdl->m_pEtcBlock->setUniformBlock(obj->m_shaderSel[1]);
    }
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
    m_pMdl->m_bindFlags[0] &= ~2;
}

void DrMdoShdSetMpf::mpfshd_stm_bill(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader*,
                                     const DrResMpfSampler*, bool) {
    shd->setupShader(0);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
}

void DrMdoShdSetMpf::mpfshd_stm_bill_wind(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader*,
                                     const DrResMpfSampler*, bool) {
    shd->setupShader(0);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    grlib::CGLibTriUniformBlock& wind = m_pMdo->m_pDrMan->m_mdlMan->m_mpfMan->m_windBlock;
    wind.setUniformBlock(shd->m_shaderSel[3]);
    wind.setOldUniformBlock(shd->m_shaderSel[4]);
}

void DrMdoShdSetMpf::mpfshd_stm_wind(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader*,
                                     const DrResMpfSampler*, bool) {
    shd->setupShader(0);
    grlib::CGLibTriUniformBlock& wind = m_pMdo->m_pDrMan->m_mdlMan->m_mpfMan->m_windBlock;
    wind.setUniformBlock(shd->m_shaderSel[3]);
    wind.setOldUniformBlock(shd->m_shaderSel[4]);
}

void DrMdoShdSetMpf::mpfshd_pre_bill(DrResShdMpf* shd, DrShdDataList* dataList, const MdsMpfMatInfoHeader* info,
                                     const DrResMpfSampler* sampler, bool dither) {
    shd->setupShader(dither ? 2 : 0);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    if (dither) {
        dataList->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(shd->m_shaderSel[7]);
        unsigned int location = shd->m_shaderSel[2];
        DrAPCache* cache = DrMan::get()->m_apCache;
        cache->beginTexSampling(2, 0);
        cache->setTexture(DrMan::get()->m_iniSys->m_texture[1], location);
    }
}

void DrMdoShdSetMpf::mpfshd_pre_bill_nuki(DrResShdMpf* shd, DrShdDataList* dataList, const MdsMpfMatInfoHeader* info,
                                     const DrResMpfSampler* sampler, bool dither) {
    shd->setupShader(dither ? 2 : 0);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    DrAPCache* texCache = m_pMdo->m_pDrMan->m_apCache;
    dataList->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(shd->m_shaderSel[7]);
    texCache->setTexture(*m_pWrkMatRes->m_ppTexture[info->m_texIdx1], *sampler->m_sampler[1], shd->m_shaderSel[0]);
    if (dither) {
        unsigned int location = shd->m_shaderSel[2];
        DrAPCache* cache = DrMan::get()->m_apCache;
        cache->beginTexSampling(2, 0);
        cache->setTexture(DrMan::get()->m_iniSys->m_texture[1], location);
    }
}

void DrMdoShdSetMpf::mpfshd_pre_mdl(DrResShdMpf* shd, DrShdDataList* dataList, const MdsMpfMatInfoHeader* info,
                                     const DrResMpfSampler* sampler, bool dither) {
    shd->setupShader(dither ? 2 : 0);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    if (dither) {
        dataList->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(shd->m_shaderSel[7]);
        unsigned int location = shd->m_shaderSel[2];
        DrAPCache* cache = DrMan::get()->m_apCache;
        cache->beginTexSampling(2, 0);
        cache->setTexture(DrMan::get()->m_iniSys->m_texture[1], location);
    }
}

void DrMdoShdSetMpf::mpfshd_pre_mdl_nuki(DrResShdMpf* shd, DrShdDataList* dataList, const MdsMpfMatInfoHeader* info,
                                     const DrResMpfSampler* sampler, bool dither) {
    shd->setupShader(dither ? 2 : 0);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    dataList->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(shd->m_shaderSel[7]);
    m_pMdo->m_pDrMan->m_apCache->setTexture(*m_pWrkMatRes->m_ppTexture[info->m_texIdx1], *sampler->m_sampler[1],
                                            shd->m_shaderSel[0]);
    if (dither) {
        unsigned int location = shd->m_shaderSel[2];
        DrAPCache* cache = DrMan::get()->m_apCache;
        cache->beginTexSampling(2, 0);
        cache->setTexture(DrMan::get()->m_iniSys->m_texture[1], location);
    }
}

void DrMdoShdSetMpf::mpfshd_drw_bill(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader* info,
                                    const DrResMpfSampler* sampler, bool) {
    unsigned int flags = info->m_flags;
    shd->setupShader((flags >> 8) & 1);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    if (flags & 0x100) {
        (m_pWrkMatRes->m_pMatUniformArray->m_pArray + info->m_matUniformIdx)->setUniformBlock(shd->m_shaderSel[5]);
    }
    m_pMdo->m_pDrMan->m_apCache->setTexture(*m_pWrkMatRes->m_ppTexture[info->m_texIdx], *sampler->m_sampler[0],
                                            shd->m_shaderSel[0]);
}

void DrMdoShdSetMpf::mpfshd_drw_mdl(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader* info,
                                    const DrResMpfSampler* sampler, bool) {
    unsigned int flags = info->m_flags;
    shd->setupShader((flags >> 8) & 1);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    if (flags & 0x100) {
        (m_pWrkMatRes->m_pMatUniformArray->m_pArray + info->m_matUniformIdx)->setUniformBlock(shd->m_shaderSel[5]);
    }
    m_pMdo->m_pDrMan->m_apCache->setTexture(*m_pWrkMatRes->m_ppTexture[info->m_texIdx], *sampler->m_sampler[0],
                                            shd->m_shaderSel[0]);
}

void DrMdoShdSetMpf::mpfshd_drw_mdl_nonom(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader* info,
                                    const DrResMpfSampler* sampler, bool) {
    unsigned int flags = info->m_flags;
    shd->setupShader((flags >> 8) & 1);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    if (flags & 0x100) {
        (m_pWrkMatRes->m_pMatUniformArray->m_pArray + info->m_matUniformIdx)->setUniformBlock(shd->m_shaderSel[5]);
    }
    m_pMdo->m_pDrMan->m_apCache->setTexture(*m_pWrkMatRes->m_ppTexture[info->m_texIdx], *sampler->m_sampler[0],
                                            shd->m_shaderSel[0]);
}

void DrMdoShdSetMpf::mpfshd_drw_mdl_def(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader* info,
                                    const DrResMpfSampler* sampler, bool) {
    unsigned int flags = info->m_flags;
    shd->setupShader((flags >> 8) & 1);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    if (flags & 0x100) {
        (m_pWrkMatRes->m_pMatUniformArray->m_pArray + info->m_matUniformIdx)->setUniformBlock(shd->m_shaderSel[5]);
    }
    m_pMdo->m_pDrMan->m_apCache->setTexture(*m_pWrkMatRes->m_ppTexture[info->m_texIdx], *sampler->m_sampler[0],
                                            shd->m_shaderSel[0]);
}

void DrMdoShdSetMpf::mpfshd_drw_mdl_defnonom(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader* info,
                                    const DrResMpfSampler* sampler, bool) {
    unsigned int flags = info->m_flags;
    shd->setupShader((flags >> 8) & 1);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    if (flags & 0x100) {
        (m_pWrkMatRes->m_pMatUniformArray->m_pArray + info->m_matUniformIdx)->setUniformBlock(shd->m_shaderSel[5]);
    }
    m_pMdo->m_pDrMan->m_apCache->setTexture(*m_pWrkMatRes->m_ppTexture[info->m_texIdx], *sampler->m_sampler[0],
                                            shd->m_shaderSel[0]);
}

void DrMdoShdSetMpf::mpfshd_drw_mdl_normalmap(DrResShdMpf* shd, DrShdDataList* dataList, const MdsMpfMatInfoHeader* info,
                                     const DrResMpfSampler* sampler, bool) {
    unsigned int flags = info->m_flags;
    shd->setupShader((flags >> 8) & 1);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    if (flags & 0x100) {
        (m_pWrkMatRes->m_pMatUniformArray->m_pArray + info->m_matUniformIdx)->setUniformBlock(shd->m_shaderSel[5]);
    }
    DrAPCache* cache = m_pMdo->m_pDrMan->m_apCache;
    cache->setTexture(*m_pWrkMatRes->m_ppTexture[info->m_texIdx], *sampler->m_sampler[0], shd->m_shaderSel[0]);
    cache->setTexture(*m_pWrkMatRes->m_ppTexture[info->m_texIdx2], *sampler->m_sampler[2], shd->m_shaderSel[1]);
}

void DrMdoShdSetMpf::mpfshd_pre_Dithe_nom(DrResShdMpf* shd, DrShdDataList* dataList, const MdsMpfMatInfoHeader* info,
                                     const DrResMpfSampler*, bool) {
    shd->setupShader(0);
    dataList->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(shd->m_shaderSel[7]);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    unsigned int location = shd->m_shaderSel[2];
    DrAPCache* cache = DrMan::get()->m_apCache;
    cache->beginTexSampling(2, 0);
    cache->setTexture(DrMan::get()->m_iniSys->m_texture[1], location);
}

void DrMdoShdSetMpf::mpfshd_pre_Dithe_nuki(DrResShdMpf* shd, DrShdDataList* dataList, const MdsMpfMatInfoHeader* info,
                                     const DrResMpfSampler* sampler, bool) {
    shd->setupShader(0);
    dataList->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(shd->m_shaderSel[7]);
    m_pMdo->m_pDrMan->m_calcMan->m_pViewWork->m_mpfBlock.setUniformBlock(shd->m_shaderSel[6]);
    m_pMdo->m_pDrMan->m_apCache->setTexture(*m_pWrkMatRes->m_ppTexture[info->m_texIdx1], *sampler->m_sampler[1],
                                            shd->m_shaderSel[0]);
    unsigned int location = shd->m_shaderSel[2];
    DrAPCache* cache = DrMan::get()->m_apCache;
    cache->beginTexSampling(2, 0);
    cache->setTexture(DrMan::get()->m_iniSys->m_texture[1], location);
}

void DrMdoShdSetMpf::mpfshd_cull_fade_mdl(DrResShdMpf*, DrShdDataList*, const MdsMpfMatInfoHeader*,
                                          const DrResMpfSampler*, bool) {}

void DrMdoShdSetPrePass::preshd_Obj(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(m_pMdl->m_bindFlags[1], type);
        (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
    } else if (m_pMdl->m_curTriBlockIdx != triIdx) {
        (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
    }
    m_pMdl->m_curTriBlockIdx = triIdx;
}

void DrMdoShdSetPrePass::preshd_ObjT(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(m_pMdl->m_bindFlags[1], type);
        (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
    } else {
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        if (m_pMdl->m_curTriBlockIdx != triIdx) {
            (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        }
    }
    m_pMdl->m_curTriBlockIdx = triIdx;
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
}

void DrMdoShdSetPrePass::preshd_ObjT_Al(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(m_pMdl->m_bindFlags[1], type);
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        unsigned int flags = m_pMdl->m_stateFlags;
        unsigned int texLoc = obj->m_shaderSel[1];
        unsigned int blkLoc = obj->m_shaderSel[9];
        DrAPCache* ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(2, 0);
        if (flags & 0x20000000) {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags &= ~0x40000000;
        } else {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
        (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
    } else {
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        if (m_pMdl->m_curTriBlockIdx != triIdx) {
            (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        }
        unsigned int flags = m_pMdl->m_stateFlags;
        if (flags & 0x20000000) {
            if (flags & 0x40000000) {
                unsigned int texLoc = obj->m_shaderSel[1];
                unsigned int blkLoc = obj->m_shaderSel[9];
                DrAPCache* ap = DrMan::get()->m_apCache;
                ap->beginTexSampling(2, 0);
                ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
                DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
                m_pMdl->m_stateFlags &= ~0x40000000;
            }
        } else if (!(flags & 0x40000000)) {
            unsigned int texLoc = obj->m_shaderSel[1];
            unsigned int blkLoc = obj->m_shaderSel[9];
            DrAPCache* ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(2, 0);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
    }
    m_pMdl->m_curTriBlockIdx = triIdx;
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
}

void DrMdoShdSetPrePass::preshd_Mot(int shd, const MdsMatInfoHeader* info, int, int, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx == shd) {
        return;
    }
    m_pMdl->m_curShaderIdx = shd;
    obj->setupShader(m_pMdl->m_bindFlags[1], type);
    DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
    list->m_boneStmOut.setStorageBuffer(0);
}

void DrMdoShdSetPrePass::preshd_MotT(int shd, const MdsMatInfoHeader* info, int, int, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(m_pMdl->m_bindFlags[1], type);
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
        list->m_boneStmOut.setStorageBuffer(0);
    }
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
}

void DrMdoShdSetPrePass::preshd_MotT_Al(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(m_pMdl->m_bindFlags[1], type);
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
        unsigned int flags = m_pMdl->m_stateFlags;
        unsigned int texLoc = obj->m_shaderSel[1];
        unsigned int blkLoc = obj->m_shaderSel[9];
        DrAPCache* ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(2, 0);
        if (flags & 0x20000000) {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags &= ~0x40000000;
        } else {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
        list->m_boneStmOut.setStorageBuffer(0);
    } else {
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        if (m_pMdl->m_curTriBlockIdx != triIdx) {
            (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        }
        unsigned int flags = m_pMdl->m_stateFlags;
        if (flags & 0x20000000) {
            if (flags & 0x40000000) {
                unsigned int texLoc = obj->m_shaderSel[1];
                unsigned int blkLoc = obj->m_shaderSel[9];
                DrAPCache* ap = DrMan::get()->m_apCache;
                ap->beginTexSampling(2, 0);
                ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
                DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
                m_pMdl->m_stateFlags &= ~0x40000000;
            }
        } else if (!(flags & 0x40000000)) {
            unsigned int texLoc = obj->m_shaderSel[1];
            unsigned int blkLoc = obj->m_shaderSel[9];
            DrAPCache* ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(2, 0);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
    }
    m_pMdl->m_curTriBlockIdx = triIdx;
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
}

void DrMdoShdSetPrePass::preshd_Inst(int shd, const MdsMatInfoHeader*, int, int, DrShdDataList* list,
                                     PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    if (m_pMdl->m_curShaderIdx == shd) {
        return;
    }
    m_pMdl->m_curShaderIdx = shd;
    obj->setupShader(0, type);
    DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
}

void DrMdoShdSetPrePass::preshd_InstT(int shd, const MdsMatInfoHeader* info, int, int, DrShdDataList* list,
                                      PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(0, type);
        DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
    }
    list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
}

void DrMdoShdSetPrePass::preshd_Obj_Al(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(m_pMdl->m_bindFlags[1], type);
        unsigned int flags = m_pMdl->m_stateFlags;
        unsigned int texLoc = obj->m_shaderSel[1];
        unsigned int blkLoc = obj->m_shaderSel[9];
        DrAPCache* ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(2, 0);
        if (flags & 0x20000000) {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags &= ~0x40000000;
        } else {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
        (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
    } else {
        if (m_pMdl->m_curTriBlockIdx != triIdx) {
            (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        }
        unsigned int flags = m_pMdl->m_stateFlags;
        if (flags & 0x20000000) {
            if (flags & 0x40000000) {
                unsigned int texLoc = obj->m_shaderSel[1];
                unsigned int blkLoc = obj->m_shaderSel[9];
                DrAPCache* ap = DrMan::get()->m_apCache;
                ap->beginTexSampling(2, 0);
                ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
                DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
                m_pMdl->m_stateFlags &= ~0x40000000;
            }
        } else if (!(flags & 0x40000000)) {
            unsigned int texLoc = obj->m_shaderSel[1];
            unsigned int blkLoc = obj->m_shaderSel[9];
            DrAPCache* ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(2, 0);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
    }
    list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
    m_pMdl->m_curTriBlockIdx = triIdx;
}

void DrMdoShdSetPrePass::preshd_ObjT_Al_FS(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(m_pMdl->m_bindFlags[1], type);
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        {
            unsigned int texLoc = obj->m_shaderSel[1];
            unsigned int blkLoc = obj->m_shaderSel[9];
            DrAPCache* ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(2, 0);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
        }
        unsigned int flags = m_pMdl->m_stateFlags;
        unsigned int texLoc = obj->m_shaderSel[2];
        unsigned int blkLoc = obj->m_shaderSel[9];
        DrAPCache* ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(2, 0);
        if (flags & 0x20000000) {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags &= ~0x40000000;
        } else {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
        (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
    } else {
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        if (m_pMdl->m_curTriBlockIdx != triIdx) {
            (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        }
        unsigned int flags = m_pMdl->m_stateFlags;
        if (flags & 0x20000000) {
            if (flags & 0x40000000) {
                unsigned int texLoc = obj->m_shaderSel[2];
                unsigned int blkLoc = obj->m_shaderSel[9];
                DrAPCache* ap = DrMan::get()->m_apCache;
                ap->beginTexSampling(2, 0);
                ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
                DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
                m_pMdl->m_stateFlags &= ~0x40000000;
            }
        } else if (!(flags & 0x40000000)) {
            unsigned int texLoc = obj->m_shaderSel[2];
            unsigned int blkLoc = obj->m_shaderSel[9];
            DrAPCache* ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(2, 0);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
    }
    m_pMdl->m_curTriBlockIdx = triIdx;
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
}

void DrMdoShdSetPrePass::preshd_Mot_Al(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(m_pMdl->m_bindFlags[1], type);
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
        unsigned int flags = m_pMdl->m_stateFlags;
        unsigned int texLoc = obj->m_shaderSel[1];
        unsigned int blkLoc = obj->m_shaderSel[9];
        DrAPCache* ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(2, 0);
        if (flags & 0x20000000) {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags &= ~0x40000000;
        } else {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
        list->m_boneStmOut.setStorageBuffer(0);
    } else {
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        if (m_pMdl->m_curTriBlockIdx != triIdx) {
            (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        }
        unsigned int flags = m_pMdl->m_stateFlags;
        if (flags & 0x20000000) {
            if (flags & 0x40000000) {
                unsigned int texLoc = obj->m_shaderSel[1];
                unsigned int blkLoc = obj->m_shaderSel[9];
                DrAPCache* ap = DrMan::get()->m_apCache;
                ap->beginTexSampling(2, 0);
                ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
                DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
                m_pMdl->m_stateFlags &= ~0x40000000;
            }
        } else if (!(flags & 0x40000000)) {
            unsigned int texLoc = obj->m_shaderSel[1];
            unsigned int blkLoc = obj->m_shaderSel[9];
            DrAPCache* ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(2, 0);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
    }
    m_pMdl->m_curTriBlockIdx = triIdx;
}

void DrMdoShdSetPrePass::preshd_MotT_Al_FS(int shd, const MdsMatInfoHeader* info, int triIdx, int, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(m_pMdl->m_bindFlags[1], type);
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
        {
            unsigned int texLoc = obj->m_shaderSel[1];
            unsigned int blkLoc = obj->m_shaderSel[9];
            DrAPCache* ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(2, 0);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
        }
        unsigned int flags = m_pMdl->m_stateFlags;
        unsigned int texLoc = obj->m_shaderSel[2];
        unsigned int blkLoc = obj->m_shaderSel[9];
        DrAPCache* ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(2, 0);
        if (flags & 0x20000000) {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags &= ~0x40000000;
        } else {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
        list->m_boneStmOut.setStorageBuffer(0);
    } else {
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        if (m_pMdl->m_curTriBlockIdx != triIdx) {
            (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        }
        unsigned int flags = m_pMdl->m_stateFlags;
        if (flags & 0x20000000) {
            if (flags & 0x40000000) {
                unsigned int texLoc = obj->m_shaderSel[2];
                unsigned int blkLoc = obj->m_shaderSel[9];
                DrAPCache* ap = DrMan::get()->m_apCache;
                ap->beginTexSampling(2, 0);
                ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
                DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
                m_pMdl->m_stateFlags &= ~0x40000000;
            }
        } else if (!(flags & 0x40000000)) {
            unsigned int texLoc = obj->m_shaderSel[2];
            unsigned int blkLoc = obj->m_shaderSel[9];
            DrAPCache* ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(2, 0);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
    }
    m_pMdl->m_curTriBlockIdx = triIdx;
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
}

void DrMdoShdSetPrePass::preshd_Inst_Al(int shd, const MdsMatInfoHeader* info, int, int, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(0, type);
        list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        unsigned int flags = m_pMdl->m_stateFlags;
        unsigned int texLoc = obj->m_shaderSel[1];
        unsigned int blkLoc = obj->m_shaderSel[9];
        DrAPCache* ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(2, 0);
        if (flags & 0x20000000) {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags &= ~0x40000000;
        } else {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
        DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
    } else {
        list->getAlphaTestUniform(info->m_alphaRef == 0.0f ? 0.5f : info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        unsigned int flags = m_pMdl->m_stateFlags;
        if (flags & 0x20000000) {
            if (flags & 0x40000000) {
                unsigned int texLoc = obj->m_shaderSel[1];
                unsigned int blkLoc = obj->m_shaderSel[9];
                DrAPCache* ap = DrMan::get()->m_apCache;
                ap->beginTexSampling(2, 0);
                ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
                DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
                m_pMdl->m_stateFlags &= ~0x40000000;
            }
        } else if (!(flags & 0x40000000)) {
            unsigned int texLoc = obj->m_shaderSel[1];
            unsigned int blkLoc = obj->m_shaderSel[9];
            DrAPCache* ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(2, 0);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
    }
}

void DrMdoShdSetPrePass::preshd_InstT_Al(int shd, const MdsMatInfoHeader* info, int, int, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(0, type);
        list->getAlphaTestUniform(info->m_alphaRef == 0.0f ? 0.5f : info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        unsigned int flags = m_pMdl->m_stateFlags;
        unsigned int texLoc = obj->m_shaderSel[1];
        unsigned int blkLoc = obj->m_shaderSel[9];
        DrAPCache* ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(2, 0);
        if (flags & 0x20000000) {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags &= ~0x40000000;
        } else {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
        DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
    } else {
        list->getAlphaTestUniform(info->m_alphaRef == 0.0f ? 0.5f : info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
        unsigned int flags = m_pMdl->m_stateFlags;
        if (flags & 0x20000000) {
            if (flags & 0x40000000) {
                unsigned int texLoc = obj->m_shaderSel[1];
                unsigned int blkLoc = obj->m_shaderSel[9];
                DrAPCache* ap = DrMan::get()->m_apCache;
                ap->beginTexSampling(2, 0);
                ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
                DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
                m_pMdl->m_stateFlags &= ~0x40000000;
            }
        } else if (!(flags & 0x40000000)) {
            unsigned int texLoc = obj->m_shaderSel[1];
            unsigned int blkLoc = obj->m_shaderSel[9];
            DrAPCache* ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(2, 0);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
    }
    setOneTexShaderSet(info->m_texEntryIdx, obj->m_shaderSel[0]);
}

void DrMdoShdSetPrePass::preshd_Fw(int shd, const MdsMatInfoHeader* info, int triIdx, int matIdx, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(m_pMdl->m_bindFlags[1], type);
        (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        unsigned int loc = obj->m_shaderSel[3];
        DrAPCache* ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(0, 1);
        ap->setTexture(DrMan::get()->m_iniSys->m_texture[16], loc);
        loc = obj->m_shaderSel[4];
        ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(0, 1);
        ap->setTexture(DrMan::get()->m_iniSys->m_texture[17], loc);
    } else if (m_pMdl->m_curTriBlockIdx != triIdx) {
        (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
    }
    MdoFlagWaveRes* fw = m_pMdl->m_pWrkMatRes->m_pFlagWave;
    if (fw) {
        fw->m_pUniformArray->m_pArray[fw->m_pData[matIdx]].setUniformBlock(obj->m_shaderSel[10]);
    }
    m_pMdl->m_curTriBlockIdx = triIdx;
}

void DrMdoShdSetPrePass::preshd_Fw_Al(int shd, const MdsMatInfoHeader* info, int triIdx, int matIdx, DrShdDataList* list,
                                    PrePassType type) {
    DrResShdPrePass* obj = list->getPrePassObj(shd);
    DrMdoCtl* mdl = m_pMdl;
    if (info->m_shdFlags & 0x8000) {
        if (mdl->m_bindFlags[1] != 1) {
            mdl->m_bindFlags[1] = 1;
            m_pMdl->m_curShaderIdx = -1;
        }
    } else if (mdl->m_bindFlags[1] != 0) {
        mdl->m_bindFlags[1] = 0;
        m_pMdl->m_curShaderIdx = -1;
    }
    if (m_pMdl->m_curShaderIdx != shd) {
        m_pMdl->m_curShaderIdx = shd;
        obj->setupShader(m_pMdl->m_bindFlags[1], type);
        unsigned int flags = m_pMdl->m_stateFlags;
        unsigned int texLoc = obj->m_shaderSel[1];
        unsigned int blkLoc = obj->m_shaderSel[9];
        DrAPCache* ap = DrMan::get()->m_apCache;
        ap->beginTexSampling(2, 0);
        if (flags & 0x20000000) {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags &= ~0x40000000;
        } else {
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
        (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        DrMan::get()->m_calcMan->m_pViewWork->m_staticBlock.setUniformBlock(obj->m_shaderSel[6]);
        {
            unsigned int loc = obj->m_shaderSel[3];
            DrAPCache* ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(0, 1);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[16], loc);
            loc = obj->m_shaderSel[4];
            ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(0, 1);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[17], loc);
        }
    } else {
        if (m_pMdl->m_curTriBlockIdx != triIdx) {
            (m_pWrkMatRes->m_pTriUniformArray->m_pArray + static_cast<unsigned int>(triIdx))->setUniformBlock(obj->m_shaderSel[5]);
        }
        unsigned int flags = m_pMdl->m_stateFlags;
        if (flags & 0x20000000) {
            if (flags & 0x40000000) {
                unsigned int texLoc = obj->m_shaderSel[1];
                unsigned int blkLoc = obj->m_shaderSel[9];
                DrAPCache* ap = DrMan::get()->m_apCache;
                ap->beginTexSampling(2, 0);
                ap->setTexture(DrMan::get()->m_iniSys->m_texture[2], texLoc);
                DrMan::get()->m_calcMan->m_pViewWork->m_invDitherBlock.setUniformBlock(blkLoc);
                m_pMdl->m_stateFlags &= ~0x40000000;
            }
        } else if (!(flags & 0x40000000)) {
            unsigned int texLoc = obj->m_shaderSel[1];
            unsigned int blkLoc = obj->m_shaderSel[9];
            DrAPCache* ap = DrMan::get()->m_apCache;
            ap->beginTexSampling(2, 0);
            ap->setTexture(DrMan::get()->m_iniSys->m_texture[1], texLoc);
            DrMan::get()->m_calcMan->m_pViewWork->m_ditherBlock.setUniformBlock(blkLoc);
            m_pMdl->m_stateFlags |= 0x40000000;
        }
    }
    list->getAlphaTestUniform(info->m_alphaRef)->setUniformBlock(obj->m_shaderSel[8]);
    MdoFlagWaveRes* fw = m_pMdl->m_pWrkMatRes->m_pFlagWave;
    if (fw) {
        fw->m_pUniformArray->m_pArray[fw->m_pData[matIdx]].setUniformBlock(obj->m_shaderSel[10]);
    }
    m_pMdl->m_curTriBlockIdx = triIdx;
}

}  // namespace ml
