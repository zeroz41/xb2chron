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
#include "ml/DrIniSys.h"
#include "mtl/MemManager.h"
#include "ml/DrMdoMpfMan.h"
#include "classes/ml/FileResTh.h"
#include "classes/ml/DrPixlShadowObj.h"
#include "ml/DrMdoVertexMan.h"
#include "ml/DrMdoTextureMan.h"
#include "ml/DrMdoSamplerMan.h"
#include "ml/DrMdoZSortMan.h"
#include "ml/DrMdoTexSimpleMan.h"
#include "ml/DrResOccUniformObj.h"
#include "ml/DrResEtcUniformObj.h"
#include "ml/DrGpuCheckRender.h"
#include "ml/DrResFilterData.h"
#include "ml/WorkUtil.h"
#include "classes/ml/Scn.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include <string.h>
#include "stdio.h"
#include "grlib/CGLibTexture.h"
#include "ml/DrIrrVolMan.h"
#include "classes/ml/DrCalcTexStreamMan.h"
#include "classes/cloud/CloudMan.h"
#include "csvb/CsvbData.h"

namespace cloud {
using namespace grlib;

}  // namespace cloud

namespace ml {
// the shader library files DrIniSys reads (data of this file, in its order)
const char* SYSTEM_INI_FILE = "/monolib/shader/lib_nx.ini";
// 2.0.0's symbols name it
const char* SYSTEM_INI_DLC_FILE = "/monolib/shader/lib_dlc_nx.ini";
const char* DITHER_FILE01 = "dither1";
const char* DITHER_FILE02 = "dither2";
const char* DITHER_FILE03 = "dither3";
const char* VOLUME_FILE = "volume";
const char* AMBBRDF_FILE = "ambientbrdf";
const char* TOON_GRAD_FILE = "toon_grad";  // 1.0.0's name (the symbols leave it unnamed, lbl_7100B7A4A8)
const char* TOON_GRAD_NIGHT_FILE = "toon_grad_night";  // 1.0.0's name (lbl_7100B7A4B0)
// 2.0.0's symbols name it
const char* TOON_GRAD_DLC_FILE = "toon_dlc_grad";
// 2.0.0's symbols name it
const char* TOON_GRAD_NIGHT_DLC_FILE = "toon_dlc_grad_night";
const char* TOON_RIM_FILE = "toon_rim";
const char* DUMMY_CUBEMAP_FILE = "dummy_cube";
const char* MIRROR_BALL_MDL_FILE = "mirror_ball";
const char* WETNESS_CSVB_FILE = "wetness_param";
const char* RAIN_DROP_FILE = "rain_drop";
const char* RAIN_DROP_DEPTH_FILE = "rain_drop_depth";
const char* GLASS_BREAKAGE = "glassbr.data";
const char* CAM_LGT_FILE = "night_light";
const char* ORIENTATION_FILE = "orientation";
const char* FLAG_WAVE0_FILE = "flag_wave_0";
const char* FLAG_WAVE1_FILE = "flag_wave_1";

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71015E9398). The path DrIniSys formats
// its file names into.
static char s_pathBuf[0x200];

void DrIniSys::dataWorkClear() {
    for (int i = 0; i < 18; i++) {
        if (m_texRes[i] != nullptr) {
            m_texture[i].release();
            if (m_texRes[i] != nullptr) {
                m_texRes[i]->Release();
                m_texRes[i] = nullptr;
            }
        }
    }
    if (m_mirrorBallRes != nullptr) {
        m_mirrorBallRes->Release();
        m_mirrorBallRes = nullptr;
    }
    if (m_camLight != nullptr) {
        m_camLight->Release();
        m_camLight = nullptr;
    }
    if (m_glassBreakage != nullptr) {
        m_glassBreakage->Release();
        m_glassBreakage = nullptr;
    }
    if (m_filterLut != nullptr) {
        m_filterLut->Release();
        m_filterLut = nullptr;
    }
    if (m_wetnessCsv != nullptr) {
        delete m_wetnessCsv;
        m_wetnessCsv = nullptr;
    }
}

FileResTh* DrIniSys::readTextureMapFile(const char* name) {
    snprintf(s_pathBuf, sizeof(s_pathBuf), "/monolib/shader/%s.witex", name);
    FileResTh* res = nullptr;
    if (Scn* scn = mm::mtl::PtrSingleton<Scn>::sys()) {
        res = scn->allocEntryRes(s_pathBuf);
    }
    if (res == nullptr) {
        res = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) FileResTh();
        res->loadBlock(m_pDrMan->m_fileHandle, s_pathBuf, 0x1000, 0);
    }
    return res;
}

void DrIniSys::loadIBLEnvTexture() {
    FileResTh* res = nullptr;
    if (Scn* scn = mm::mtl::PtrSingleton<Scn>::sys()) {
        res = scn->allocEntryRes(m_iblEnvPath);
    }
    if (res != nullptr) {
        return;
    }
    res = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) FileResTh();
    if (res->loadBlock(m_pDrMan->m_fileHandle, m_iblEnvPath, 0x1000, 0)) {
        if (m_texRes[12] != nullptr) {
            m_texRes[12]->Release();
            m_texRes[12] = nullptr;
        }
        m_texRes[12] = res;
        grlib::CGLibTexture::createTextureImagePtrs(m_texture[12], res->m_data, res->m_size, false, nullptr, true);
    }
}

void DrIniSys::loadGlassBreakage() {
    snprintf(s_pathBuf, sizeof(s_pathBuf), "/monolib/shader/%s", GLASS_BREAKAGE);
    FileResTh* res = nullptr;
    if (Scn* scn = mm::mtl::PtrSingleton<Scn>::sys()) {
        res = scn->allocEntryRes(s_pathBuf);
    }
    if (res == nullptr) {
        res = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) FileResTh();
        res->loadBlock(m_pDrMan->m_fileHandle, s_pathBuf, 0x1000, 0);
    }
    m_glassBreakage = res;
}

void DrIniSys::loadCameraLight() {
    snprintf(s_pathBuf, sizeof(s_pathBuf), "/monolib/shader/%s.wilgt", CAM_LGT_FILE);
    FileResTh* res = nullptr;
    if (Scn* scn = mm::mtl::PtrSingleton<Scn>::sys()) {
        res = scn->allocEntryRes(s_pathBuf);
    }
    if (res == nullptr) {
        res = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) FileResTh();
        res->loadBlock(m_pDrMan->m_fileHandle, s_pathBuf, 0x1000, 0);
    }
    m_camLight = res;
}

void DrIniSys::loadFilterLutTexture() {
    if (m_pDrMan->m_dlcShaderMode == 1) {
        snprintf(s_pathBuf, sizeof(s_pathBuf), "/monolib/shader/filterlut_dlc.%s", "wiltp");
    } else {
        snprintf(s_pathBuf, sizeof(s_pathBuf), "/monolib/shader/filterlut.%s", "wiltp");
    }
    if (m_filterLut != nullptr) {
        m_filterLut->Release();
        m_filterLut = nullptr;
    }
    FileResTh* res = nullptr;
    if (Scn* scn = mm::mtl::PtrSingleton<Scn>::sys()) {
        res = scn->allocEntryRes(s_pathBuf);
    }
    if (res == nullptr) {
        res = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) FileResTh();
        res->loadBlock(m_pDrMan->m_fileHandle, s_pathBuf, 0x1000, 0);
    }
    m_filterLut = res;
    m_pDrMan->m_filterData->setFilterData(res->m_data);
}

void DrIniSys::getWetnessSetting(unsigned short row, WetSetting& setting) const {
    if (m_wetnessCsv->GetRowCount() == 0) {
        setting.m_enable = false;
        setting.m_param1 = 0;
        setting.m_param2 = 0;
        setting.m_value = m_wetDefault;
        return;
    }
    row = (row == 0 || row >= m_wetnessCsv->GetRowCount()) ? 0 : row;
    setting.m_enable = m_wetnessCsv->GetInt(row, 0) == 1;
    setting.m_param1 = m_wetnessCsv->GetInt(row, 1);
    setting.m_param2 = m_wetnessCsv->GetInt(row, 2);
    setting.m_value = m_wetnessCsv->GetColumCount(row) >= 4 ? m_wetnessCsv->GetFloat(row, 3) : m_wetDefault;
}

const void* DrIniSys::getGlassBreakage() const { return m_glassBreakage->m_data; }

DrMan* DrMan::getIns() { return s_pTop; }

DrMan* DrMan::get() { return s_pTop; }

void DrMan::createAddRenderSystem(DR_VIEW_PARAM* param) {
    CS lock(*getCriticalSection());
    int idx = s_nDblStockIdx;
    m_addViewParam[idx][m_addViewNum[idx]] = *param;
    m_addViewNum[idx]++;
}

void DrMan::setModelTexture(DR_MODEL_TEXTURE* texture, unsigned int slot) {
    CS lock(*getCriticalSection());
    m_modelTexture[s_nDblStockIdx][slot] = *texture;
    m_modelTextureReq[s_nDblStockIdx] |= 1 << slot;
}

void DrMan::resetModelTexture(unsigned int slot) {
    CS lock(*getCriticalSection());
    m_modelTexture[s_nDblStockIdx][slot].m_texture = nullptr;
    m_modelTexture[s_nDblStockIdx][slot].m_enable = false;
    m_modelTextureReq[s_nDblStockIdx] |= 1 << slot;
}

void DrMan::deleteAddRenderSystem(unsigned int index) {
    CS lock(*getCriticalSection());
    int idx = s_nDblStockIdx;
    m_delViewIdx[idx][m_delViewNum[idx]] = index;
    m_delViewNum[idx]++;
}

void DrMan::end() {
    if (m_cloudMan != nullptr) {
        m_cloudMan->end();
    }
    for (int i = 0; i < m_callBackNum; i++) {
        m_callBack[i]->end();
    }
    m_endFlag = m_endFlagReq;
    m_curViewInfo = &m_viewInfo[0];
    m_calcMan = m_viewCalcMan[0];
    m_postParmIdx = 0;
    m_lightMan = m_viewLightMan[0];
    m_fogMan = m_viewFogMan[0];
    m_curEnvMan = m_envMan[0];
    m_pixlMan->setupCate(0);
    DrMdlMan* mdlMan = m_mdlMan;
    mdlMan->m_pExtraList = &mdlMan->m_extraList;
    mdlMan->m_curZSortMan = mdlMan->m_zsortMan;
    mdlMan->m_pMdlList = &mdlMan->m_lists[0];
    mdlMan->pad_238 = 0;
    mdlMan->m_pGrpList = &mdlMan->m_lists[10];
    mdlMan->m_smlShadowMan->m_viewIdx = 0;
    m_shdMan->setupCate(0);
}

bool DrMan::loopCnt() { return true; }

void DrMan::blurCallBackRender() {
    for (int i = 0; i < m_callBackNum; i++) {
        m_callBack[i]->blurRender(&m_drawWorkInfo[m_postParmIdx]);
    }
}

void DrMan::tail() {
    m_texStreamMan->jobWait();
    s_nDblIdx = !s_nDblIdx;
    s_nDblStockIdx = !s_nDblIdx;
    if (!m_mdlDblPause) {
        s_nDblMemIdx = s_nDblIdx;
    }
    s_nDblNowIdx = s_nDblIdx;
    s_nTriNowIdx = s_nTriNowIdx > 1 ? 0 : s_nTriNowIdx + 1;
    m_irrVolMan->tail();
    if (m_cloudMan != nullptr) {
        m_cloudMan->tail();
    }
}

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

bool DrMdlMan::shadowRender(DrPixlShadowObj* shadowObj) {
    DrMan* man = m_pDrMan;
    if (man->m_shadowRenderOff || man->m_mdlShadowOff) {
        return false;
    }
    DrPixlMan* pixlMan = man->m_pixlMan;
    pixlMan->setShadowObj(shadowObj);
    shadowObj->m_flags &= ~1;
    for (DrMdlBase* obj = m_pMdlList->m_pTop; obj != nullptr; obj = obj->m_pNext) {
        if ((obj->m_dispFlags & 1) && (m_shadowViewMask & (1 << obj->m_groups))) {
            obj->shadowRender();
        }
    }
    if (shadowObj->renderEnd()) {
        pixlMan->resetRenderTarget();
        return true;
    }
    return false;
}

bool DrMdlMan::shadowCacheRender(DrPixlShadowCacheObj& cacheObj) {
    for (DrMdlBase* obj = m_pMdlList->m_pTop; obj != nullptr; obj = obj->m_pNext) {
        if ((obj->m_dispFlags & 1) && (m_shadowViewMask & (1 << obj->m_groups))) {
            if (!obj->shadowCacheRender(cacheObj)) {
                return false;
            }
        }
    }
    return true;
}

void DrMdlMan::shadowCacheAddRender(int index) {
    for (DrMdlBase* obj = m_pMdlList->m_pTop; obj != nullptr; obj = obj->m_pNext) {
        if ((obj->m_dispFlags & 1) && (m_shadowViewMask & (1 << obj->m_groups))) {
            obj->shadowCacheAddRender(index);
        }
    }
}

void DrMdlMan::callShadowCacheUpdate(unsigned long value) {
    for (DrMdlBase* obj = m_pMdlList->m_pTop; obj != nullptr; obj = obj->m_pNext) {
        obj->callShadowCacheUpdate(value);
    }
}

void DrMdlMan::addMpfObj() {
    if (m_mpfMan != nullptr) {
        m_mpfMan->addMpfObj();
    } else {
        m_mpfMan = new (m_pDrMan->m_workHandle, nullptr, 0, 4, false) DrMdoMpfMan(m_pDrMan);
    }
}

void DrMdlMan::delMpfObj() {
    if (m_mpfMan != nullptr && m_mpfMan->delMpfObj()) {
        if (m_mpfMan != nullptr) {
            delete m_mpfMan;
            m_mpfMan = nullptr;
        }
    }
}

DrMdlObj::DrMdlObj(int viewNum) : DrMdoCtl(viewNum) {}

void DrMdlObj::chageShadowObject(DrMdoSmlShadowMan* shadowMan) {
    if (m_pSmlShadowObj != nullptr) {
        shadowMan->changeViewNum(m_pSmlShadowObj, m_viewNum);
    }
}

int DrMdlObj::getNodeIdx(const char* name) const { return DrMdoNode::getNodeIdx(name); }

const char* DrMdlObj::getNodeName(int index) const { return DrMdoNode::getNodeName(index); }

void DrMdlObj::setResBoneMat(int index, const mm::Mat44& mat) { DrMdoNode::setNodeMatrix(index, mat); }

const mm::Mat44& DrMdlObj::getResBoneMat(int index) const { return getNodeMatrix(index); }

mm::Mat44* DrMdlObj::getResBoneMatPtr(int index) { return getNodeMatrixPtr(index); }

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

DrMdoGrpObj::DrMdoGrpObj(int viewNum, unsigned int listNum) : DrMdlBase(viewNum), m_sortGrp(this) {
    m_mdlType = 5;
    int num = listNum;
    if (num < 0) {
        num = 1;
    }
    if (num > 0xFF) {
        num = 0xFF;
    }
    m_listMax = num;
    m_listNum = 0;
    m_pListBuf = mtl::MemManager::allocate(DrMan::s_pTop->m_resHandle, m_listMax * sizeof(MdlList) + m_listMax * sizeof(MdlList*),
                                           0x10, false, "no name", 0);
    m_pLists = static_cast<MdlList*>(m_pListBuf);
    m_ppList = reinterpret_cast<MdlList**>(m_pLists + m_listMax);
    for (long i = 0; i < m_listMax; i++) {
        m_pLists[i].reset();
    }
    m_lists[0].reset();
    m_lists[1].reset();
    m_lists[2].reset();
}

DrMdoGrpObj::~DrMdoGrpObj() {
    for (long i = 0; i < m_listMax; i++) {
        m_pLists[i].deleteAll();
    }
    if (m_pListBuf != nullptr) {
        mtl::MemManager::deallocate(m_pListBuf, 0, false);
        m_pListBuf = nullptr;
    }
    m_lists[0].deleteAll();
    m_lists[1].deleteAll();
    m_lists[2].deleteAll();
}

void DrMdoGrpObj::dispOffUpdate() {
    updateList();
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            obj->dispOffUpdate();
        }
    }
}

void DrMdoGrpObj::shadowRender() {
    unsigned int mask = DrMan::s_pTop->m_mdlMan->m_shadowViewMask;
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            if ((obj->m_dispFlags & 1) && ((1 << obj->m_groups) & mask)) {
                obj->shadowRender();
            }
        }
    }
}

bool DrMdoGrpObj::shadowCacheRender(DrPixlShadowCacheObj& cacheObj) {
    unsigned int mask = DrMan::s_pTop->m_mdlMan->m_shadowViewMask;
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            if ((obj->m_dispFlags & 1) && ((1 << obj->m_groups) & mask)) {
                if (!obj->shadowCacheRender(cacheObj)) {
                    return false;
                }
            }
        }
    }
    return true;
}

void DrMdoGrpObj::shadowCacheOnlyRender() {
    unsigned int mask = DrMan::s_pTop->m_mdlMan->m_shadowViewMask;
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            if ((1 << obj->m_groups) & mask) {
                obj->shadowCacheOnlyRender();
            }
        }
    }
}

void DrMdoGrpObj::occRender() {
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            if (static_cast<DrMdoCtlNom*>(obj)->m_stateFlags & 0x80) {
                obj->occRender();
            }
        }
    }
}

void DrMdoGrpObj::callShadowCacheUpdate(unsigned long value) {
    for (long i = 0; i < m_listNum; i++) {
        for (DrMdlBase* obj = m_ppList[i]->m_pTop; obj != nullptr; obj = obj->m_pNext) {
            obj->callShadowCacheUpdate(value);
        }
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

void DrMan::weatherFrmEnd() { m_weatherFrameReq[s_nDblStockIdx] = true; }

bool DrMan::isWeatherFrmEnd() { return m_weatherFrameReq[s_nDblIdx] != 0; }

void DrMan::setGlobalWind(const mm::Vec3& power) {
    mm::Vec3& wind = m_globalWind[s_nDblStockIdx];
    wind.x = power.x;
    wind.y = power.y;
    wind.z = power.z;
}

void DrMan::setAllMiddelTexStmChk(bool check) { m_allMiddelTexStmChk[s_nDblIdx] |= check; }

void DrMan::setSeamMapOn() { m_seamCalc[s_nDblIdx] = true; }

bool DrMan::isSeamMapOn() const { return m_seamCalc[s_nDblStockIdx]; }

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
