#include "classes/ml/DrMan.h"
#include "ml/DrCreator.h"
#include "ml/DrMdlMan.h"
#include "ml/DrEnvironmentMan.h"
#include "ml/DrEnvColiMan.h"
#include "ml/DrCalcMan.h"
#include "ml/DrCalcClipMan.h"
#include "ml/DrShdLgtMan.h"
#include "ml/DrShdLgtGlobalIBL.h"
#include "ml/DrPixlMan.h"
#include "classes/ml/DrAPCache.h"
#include "ml/DrShdMan.h"
#include "ml/CriticalSection.h"
#include "classes/ml/DrMdlBase.h"
#include "classes/ml/DrMdoMat.h"
#include "classes/ml/DrMdoCtl.h"
#include "classes/ml/DrMdlObj.h"
#include "classes/ml/DrMdoCtlNom.h"
#include "classes/ml/DrMdoCtlPos.h"
#include "classes/ml/DrMdoCtlSeamAll.h"
#include "classes/ml/DrMdoGrpObj.h"
#include "classes/ml/DrMan.h"
#include "ml/DrMdoSmlShadowMan.h"
#include "classes/ml/DrMemHandleAllocator.h"
#include "classes/ml/IDrDrawCallback.h"
#include "ml/MdoWrkMatRes.h"
#include "cloud/CloudShaderMan.h"

namespace cloud {
using namespace grlib;

}  // namespace cloud

namespace ml {
DrMan* DrMan::getIns() { return s_pTop; }

DrMan* DrMan::get() { return s_pTop; }

bool DrMan::loopCnt() { return true; }

bool DrMan::isIBLHalfRes() const { return true; }

void DrMan::setCallBack(IDrDrawCallback* callback) {
    if (m_callBackNum < 16) {
        m_callBack[m_callBackNum] = callback;
        m_callBackNum++;
    }
}

void DrMan::releaseCallBack(IDrDrawCallback* callback) {
    for (int i = 0; i < m_callBackNum; i++) {
        if (m_callBack[i] == callback) {
            for (; i < m_callBackNum - 1; i++) {
                m_callBack[i] = m_callBack[i + 1];
            }
            m_callBackNum--;
            m_callBack[m_callBackNum] = nullptr;
            return;
        }
    }
}

void DrMan::openPixelDebugWindow(WinProc* proc) {}

void DrMan::openHistgramDebugWindow(WinProc* proc) {}

void DrMan::setAutoReduction(bool enable) { *m_pAutoReduction = enable; }

const mm::Vec3& DrMan::getGlobalWind() const { return m_globalWind[s_nDblNowIdx]; }

bool DrMan::isSRGBMode() { return s_bSRGBMode; }

bool DrMan::isFogSRGB() { return s_bFogSRGB; }

bool DrMan::isAllMiddelTexStmChk() const { return m_allMiddelTexStmChk[s_nDblStockIdx]; }

void DrMan::setSeamMapStmOk(bool ok) { m_seamMapStmOk[s_nDblIdx] = ok; }

bool DrMan::isSeamMapStmOk() const { return m_seamMapStmOk[s_nDblStockIdx]; }

void DrMan::bkgHomeMenu(bool enable) {
    if (enable) {
        m_homeMenu = true;
    }
}

void DrMdlObj::setDblBuffAlpha(bool enable) {
    if (enable) {
        m_ctlFlags2 &= ~0x40000;
    } else {
        m_ctlFlags2 |= 0x40000;
    }
}

void DrMdlObj::chageShadowObject(DrMdoSmlShadowMan* shadowMan) {
    if (m_pSmlShadowObj != nullptr) {
        shadowMan->changeViewNum(m_pSmlShadowObj, m_viewNum);
    }
}

void DrMdlObj::setMatrix(const mm::Mat44& matrix) { DrMdoCtl::setMatrix(matrix); }

void DrMdlObj::setOffsetPos(const mm::Vec3& pos) { DrMdoCtl::setOffsetPos(pos); }

int DrMdlObj::getNodeMax() const { return m_nodeMax; }

void DrMdlObj::setAlwaysMiddleTexStm(bool enable) {
    if (enable) {
        m_ctlFlags |= 0x20000;
    } else {
        m_ctlFlags &= ~0x20000;
    }
}

void DrMdlObj::setGpuClip(bool enable) {
    if (enable) {
        m_ctlFlags &= ~0x10000;
    } else {
        m_ctlFlags |= 0x10000;
    }
}

void DrMdlObj::setOcclusionQuery(bool enable) {
    if (enable) {
        m_ctlFlags &= ~0x40000;
    } else {
        m_ctlFlags |= 0x40000;
    }
}

void DrMdlObj::setAlwaysTexStm(bool enable) {
    if (enable) {
        m_ctlFlags |= 0x4;
    } else {
        m_ctlFlags &= ~0x4;
    }
}

bool DrMdlObj::isMdlTexStm() const { return true; }

bool DrMdlObj::isMemTexStm() const { return (m_ctlFlags & 0x2002) != 0x2; }

const mm::Vec3& DrMdlObj::getAABBMax() const { return m_aabbMax; }

const mm::Vec3& DrMdlObj::getAABBMin() const { return m_aabbMin; }

bool DrMdlObj::isGpuRender() const { return m_gpuRender; }

void DrMdlObj::setSpAlphaMode(bool enable) {
    if (enable) {
        m_ctlFlags |= 0x4000;
    } else {
        m_ctlFlags &= ~0x4000;
    }
}

void DrMdlObj::setCamCheckMode(bool enable) {
    if (enable) {
        m_ctlFlags |= 0x10000000;
    } else {
        m_ctlFlags &= ~0x10000000;
    }
}

bool DrMdlObj::isCamCheckResl() const { return (m_ctlFlags >> 29) & 1; }

void DrMdlObj::setAlpha(float alpha) {
    if (m_ctlFlags2 & 0x40000) {
        m_singleAlpha = alpha;
    } else {
        m_ctlFlags2 |= 0x10000 << DrMan::s_nDblStockIdx;
        m_alpha[DrMan::s_nDblStockIdx] = alpha;
    }
}

float DrMdlObj::getAlpha() const {
    if (m_ctlFlags2 & 0x40000) {
        return m_singleAlpha;
    }
    return m_alpha[DrMan::s_nDblStockIdx];
}

void DrMdlObj::setWriteStencil(bool enable) {
    if (enable) {
        if (m_ctlFlags & 0x10) {
            return;
        }
        m_ctlFlags |= 0x10;
    } else {
        if (!(m_ctlFlags & 0x10)) {
            return;
        }
        m_ctlFlags &= ~0x10;
    }
    m_dispFlags &= ~0x60;
}

MdoRimBloomWrk* DrMdlObj::getRimBloomWrk(unsigned int bank) {
    if (m_pWrkMatRes == nullptr) {
        return nullptr;
    }
    if (m_pWrkMatRes->m_pRimBloomWrk == nullptr) {
        return nullptr;
    }
    return &m_pWrkMatRes->m_pRimBloomWrk[bank];
}

void DrMdlObj::setAceColor(int index, const mm::Col3& color) {
    if (m_pWrkMatRes != nullptr && m_pWrkMatRes->m_pAce != nullptr) {
        m_pWrkMatRes->m_pAce->m_color[index] = color;
    }
}

void DrMdlObj::setAceVal(int index, float value) {
    if (m_pWrkMatRes != nullptr && m_pWrkMatRes->m_pAce != nullptr) {
        m_pWrkMatRes->m_pAce->m_val[index] = value;
    }
}

void DrMdoGrpObj::callNomSetupRender() {
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            DrMdoCtlNom* nom = static_cast<DrMdoCtlNom*>(obj);
            if (nom->m_stateFlags & 0x80) {
                nom->callNomSetupRender();
            }
        }
    }
}

void DrMdoGrpObj::callZSortNomZpreePassRender() {
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            DrMdoCtlNom* nom = static_cast<DrMdoCtlNom*>(obj);
            if (nom->m_stateFlags & 0x80) {
                nom->callZSortNomZpreePassRender();
            }
        }
    }
}

void DrMdoGrpObj::callZSortThicknessRenderFirst() {
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            DrMdoCtlNom* nom = static_cast<DrMdoCtlNom*>(obj);
            if (nom->m_stateFlags & 0x80) {
                nom->callZSortThicknessRenderFirst();
            }
        }
    }
}

void DrMdoGrpObj::callZSortThicknessRenderSecond() {
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            DrMdoCtlNom* nom = static_cast<DrMdoCtlNom*>(obj);
            if (nom->m_stateFlags & 0x80) {
                nom->callZSortThicknessRenderSecond();
            }
        }
    }
}

void DrMdoGrpObj::callZSortNomRender() {
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            DrMdoCtlNom* nom = static_cast<DrMdoCtlNom*>(obj);
            if (nom->m_stateFlags & 0x80) {
                nom->callZSortNomRender();
            }
        }
    }
}

void DrMdoGrpObj::callZSortGBuffRender() {
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            DrMdoCtlNom* nom = static_cast<DrMdoCtlNom*>(obj);
            if (nom->m_stateFlags & 0x80) {
                nom->callZSortGBuffRender();
            }
        }
    }
}

void DrMdoGrpObj::callZSortLightPrePassRender() {
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            DrMdoCtlNom* nom = static_cast<DrMdoCtlNom*>(obj);
            if (nom->m_stateFlags & 0x80) {
                nom->callZSortLightPrePassRender();
            }
        }
    }
}

void DrMdoGrpObj::callZSortNomAlphaRender() {
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            DrMdoCtlNom* nom = static_cast<DrMdoCtlNom*>(obj);
            if (nom->m_stateFlags & 0x80) {
                nom->callZSortNomAlphaRender();
            }
        }
    }
}

void DrMdoGrpObj::callZSortNomSpAlphaRender() {
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            DrMdoCtlNom* nom = static_cast<DrMdoCtlNom*>(obj);
            if (nom->m_stateFlags & 0x80) {
                nom->callZSortNomSpAlphaRender();
            }
        }
    }
}

void DrMdoGrpObj::callZSortNomRefractionRender() {
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            DrMdoCtlNom* nom = static_cast<DrMdoCtlNom*>(obj);
            if (nom->m_stateFlags & 0x80) {
                nom->callZSortNomRefractionRender();
            }
        }
    }
}

bool DrMdlBase::shadowCacheRender(DrPixlShadowCacheObj&) { return true; }

void DrMdlBase::setDisp(bool enable) {
    if (enable) {
        m_dispFlags |= 0x1;
    } else {
        m_dispFlags &= ~0x1;
    }
}

void DrMdlBase::setDeleteCall(int index) { m_dispFlags |= 8 << index; }

void* DrMemHandleAllocator::allocate(unsigned long size, unsigned long alignment) {
    return mtl::MemManager::allocate(m_allocHandle, size, alignment, false, "no name", 0);
}

void DrMemHandleAllocator::deallocate(void* memory) {
    if (memory != nullptr) {
        mtl::MemManager::deallocate(memory, 0, false);
    }
}

}  // namespace ml

namespace ml {
CriticalSection* DrMan::getCriticalSection() {
    // the name is not the original's: the symbols leave it unnamed (lbl_71015E95B8)
    static CriticalSection s_criticalSection;
    return &s_criticalSection;
}

void DrMan::setAlphaRenderTarget() {
    m_apCache->begin();
    m_pixlMan->resetRenderTarget();
    m_pixlMan->alphaRenderTarget();
}

void DrMan::setGblIdx(int index) {
    if ((m_dispOffBits[index >> 5] & (1 << (index & 0x1F))) == 0) {
        m_pixlMan->callShadowCacheVariance();
        m_dispOffBits[index >> 5] |= 1 << (index & 0x1F);
    }
}

void DrMan::offGblIdx(int index) {
    if ((m_dispOffBits[index >> 5] & (1 << (index & 0x1F))) != 0) {
        m_pixlMan->callShadowCacheVariance();
        m_dispOffBits[index >> 5] &= ~(1 << (index & 0x1F));
    }
}

bool DrMan::isIBLSkip() const { return m_iblSkip || !m_shdMan->m_lgtMan->m_pGlobalIBL->isEnable(); }

bool DrMan::isTemporalUPSToGlobalIBL() const {
    if (m_iblSkip) {
        return false;
    }
    return m_shdMan->m_lgtMan->m_pGlobalIBL->isEnable();
}

void DrMan::setTimeVal(float time) {
    int idx = s_nDblStockIdx;
    if (time > 1.0f) {
        m_timeVal[idx] = 1.0f;
    } else if (time < 0.0f) {
        m_timeVal[idx] = 0.0f;
    } else {
        m_timeVal[idx] = time;
    }
}

void DrMan::fn_710071E620() { m_weatherFrameReq[s_nDblStockIdx] = true; }

bool DrMan::fn_710071E640() { return m_weatherFrameReq[s_nDblIdx]; }

void DrMan::setGlobalWind(const mm::Vec3& power) {
    mm::Vec3& wind = m_globalWind[s_nDblStockIdx];
    wind.x = power.x;
    wind.y = power.y;
    wind.z = power.z;
}

void DrMan::setAllMiddelTexStmChk(bool check) { m_allMiddelTexStmChk[s_nDblIdx] |= check; }

void DrMan::fn_710071E75C() { m_seamCalc[s_nDblIdx] = true; }

bool DrMan::fn_710071E77C() { return m_seamCalc[s_nDblStockIdx]; }

DrCreator::DrCreator() : m_pDrMan(DrMan::s_pTop) {}

DrMdlObj* DrCreator::createMdl(const void* resource, const char* name, int arg) {
    return m_pDrMan->m_mdlMan->createMdl(resource, name, arg);
}

DrMdoGrpObj* DrCreator::createInstantGrp(int arg, unsigned int viewNum) {
    return m_pDrMan->m_mdlMan->createInstantGrp(arg, viewNum);
}

DrEnvironmentObj* DrCreator::createLgt(const void* resource, int view) {
    return m_pDrMan->m_envMan[view]->createObj(resource);
}

DrEnvColiObj* DrCreator::createEnvColi(const void* resource, int view) {
    return m_pDrMan->m_envMan[view]->m_envColiMan->createObj(resource);
}

DrCalcClipObj* DrCreator::createClipObj(const void* resource, int view) {
    return m_pDrMan->m_viewCalcMan[view]->m_pClipMan->createClipObj(resource);
}

DrGpuCheckBase* DrCreator::createGpuCheckObj(int arg) { return m_pDrMan->m_mdlMan->createGpuCheckObj(arg); }

DrStmReadCheck* DrCreator::createStmLoadObj(const char* name) { return m_pDrMan->m_mdlMan->createStmLoadObj(name); }
}  // namespace ml
