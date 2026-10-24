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
