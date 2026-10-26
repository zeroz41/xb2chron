// the cloud system's top (cloud::CloudMan) and CloudObj's constructor; xbrd's library (its singleton assertion cites
// xbrd's mcl path)
#define MM_LIB_FROM_XBRD
#include "classes/cloud/CloudMan.h"
#include "classes/cloud/CloudObj.h"
#include "classes/cloud/CloudDataMan.h"
#include "cloud/CloudShaderMan.h"
#include "cloud/CloudCalcParams.h"
#include "cloud/CloudObjMan.h"
#include "cloud/CloudObjReduction.h"
#include "cloud/CloudVertexMan.h"
#include "cloud/CloudTextureMan.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrResMdoSortCloud.h"
#include "classes/ml/IDrDrawWorkInfo.h"
#include "ml/DrMdoZSortMan.h"
#include "mm/Col3.h"
#include "mtl/MemManager.h"

namespace cloud {

int CloudMan::s_nDblStIdx = 1;
int CloudMan::s_nDblDfIdx;

CloudMan::CloudMan(ml::Scn* scn, mtl::ALLOC_HANDLE handle, unsigned int size)
    : m_pScn(scn), m_pReserved(nullptr) {
    s_nDblDfIdx = 0;
    s_nDblStIdx = 1;
    m_hTop = mtl::ALLOC_HANDLE();
    m_hData = mtl::ALLOC_HANDLE();
    m_hWork = mtl::ALLOC_HANDLE();
    m_hTop = mtl::MemManager::create(handle, size + 0x1000, "CloudTop", false, "no name", 0);
    m_hData = mtl::MemManager::create(m_hTop, 0x380000, "CloudData", false, "no name", 0);
    unsigned int workSize = size - 0x380000;
    m_hWork = mtl::MemManager::create(m_hTop, workSize, "CloudWork", false, "no name", 0);
    m_isSetupWait = true;
    m_pSortObj = nullptr;
    m_pTextureMan = nullptr;
    m_pShaderMan = nullptr;
    m_pVertexMan = nullptr;
    m_frame = 1.0f;
    m_rate = 1.0f;
    m_pDataMan = new (m_hWork, nullptr, 0, 4, false) CloudDataMan();
    m_pObjMan = new (m_hWork, nullptr, 0, 4, false) CloudObjMan();
    m_pSortObj = new (m_hWork, nullptr, 0, 4, false) ml::DrResMdoSortCloud(this);
}

CloudMan::~CloudMan() {
    if (m_pSortObj) {
        delete m_pSortObj;
        m_pSortObj = nullptr;
    }
    if (m_pObjMan) {
        delete m_pObjMan;
        m_pObjMan = nullptr;
    }
    if (m_pVertexMan) {
        delete m_pVertexMan;
        m_pVertexMan = nullptr;
    }
    if (m_pTextureMan) {
        delete m_pTextureMan;
        m_pTextureMan = nullptr;
    }
    if (m_pShaderMan) {
        delete m_pShaderMan;
        m_pShaderMan = nullptr;
    }
    if (m_pDataMan) {
        delete m_pDataMan;
        m_pDataMan = nullptr;
    }
    if (m_hData.m_handle) {
        mtl::MemManager::erase(m_hData);
        m_hData.m_handle = 0;
    }
    if (m_hWork.m_handle) {
        mtl::MemManager::erase(m_hWork);
        m_hWork.m_handle = 0;
    }
    if (m_hTop.m_handle) {
        mtl::MemManager::erase(m_hTop);
        m_hTop.m_handle = 0;
    }
}

void CloudMan::planeOn(bool on) { m_pObjMan->m_planeOn = on; }

void CloudMan::planeSideOn(bool on) { m_pObjMan->m_planeSideOn = on; }

void CloudMan::skyOn(bool on) { m_pObjMan->m_skyOn = on; }

void CloudMan::mdlOn(bool on) { m_pObjMan->m_mdlOn = on; }

void CloudMan::setHeight(float height) { m_pObjMan->m_pCalcParams->m_height = height; }

float CloudMan::getHeight() const { return m_pObjMan->m_pCalcParams->m_height; }

bool CloudMan::isHole() const { return m_pObjMan->m_isHole; }

void CloudMan::setCldNum(unsigned int num) {
    if (num <= 1) {
        m_pObjMan->m_pCalcParams->m_cldNum = num;
    }
}

unsigned int CloudMan::getCldNum() const { return m_pObjMan->m_pCalcParams->m_cldNum; }

void CloudMan::beginSetup() {
    if (m_pDataMan->isReadOk()) {
        m_isSetupWait = false;
        m_pVertexMan = new (m_hWork, nullptr, 0, 4, false) CloudVertexMan();
        m_pTextureMan = new (m_hWork, nullptr, 0, 4, false) CloudTextureMan();
        m_pShaderMan = new (m_hWork, nullptr, 0, 4, false) CloudShaderMan();
        m_pShaderMan->createShader();
        m_pTextureMan->createTexture();
        m_pObjMan->creataFastSetup();
    }
}

void CloudMan::begin(float frame) {
    m_frame = frame;
    if (m_isSetupWait) {
        beginSetup();
    } else {
        m_pShaderMan->update();
    }
}

void CloudMan::end() {}

void CloudMan::apply(const ml::IDrDrawWorkInfo* info, ml::DrMdoZSortMan* zsort) {
    if (!m_isSetupWait && info->m_subPass == 0 && m_pObjMan->update(info) && m_pObjMan->isRender()) {
        zsort->setViewCloud(m_pSortObj);
    }
}

void CloudMan::alphaRender(const ml::IDrDrawWorkInfo* info) {
    m_pObjMan->alphaRender(info);
    ml::DrMan::getIns()->setAlphaRenderTarget();
}

void CloudMan::finalRender(const ml::IDrDrawWorkInfo* info) {
    if (!m_isSetupWait) {
        m_pObjMan->isRender();
    }
}

void CloudMan::tail() {
    s_nDblDfIdx = 1 - s_nDblDfIdx;
    s_nDblStIdx = 1 - s_nDblStIdx;
}

unsigned int CloudMan::getPixelMem(unsigned int& mem, unsigned int width, unsigned int height) {
    return CloudObjReduction::getPixelMem(mem, width, height);
}

const mm::Col3& CloudMan::getPlaneCol(unsigned int idx) const {
    CloudCalcParams* params = m_pObjMan->m_pCalcParams;
    return idx == 0 ? params->m_planeCol[0] : params->m_planeCol[1];
}

CloudObj::CloudObj() {}

}  // namespace cloud
