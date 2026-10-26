#include "classes/cloud/CloudObj.h"
#include "cloud/CloudUniform.h"
#include "cloud/CloudMdlParts.h"
#include "cloud/CloudMdlListMan.h"
#include "cloud/CloudObjMan.h"
#include "cloud/CloudObjReduction.h"
#include "cloud/CloudCalcParams.h"
#include "classes/cloud/CloudObjFlow.h"
#include "classes/cloud/CloudObjMdl.h"
#include "classes/cloud/CloudObjPlane.h"
#include "classes/cloud/CloudObjSky.h"
#include "classes/cloud/CloudObj.h"
#include "cloud/CloudObjMan.h"
#include "cloud/CloudObjReduction.h"
#include "cloud/CloudCalcParams.h"
#include "classes/cloud/CloudObjFlow.h"
#include "classes/cloud/CloudObjMdl.h"
#include "classes/cloud/CloudObjPlane.h"
#include "classes/cloud/CloudObjSky.h"
#include "classes/cloud/CloudMan.h"
#include "cloud/CloudShaderMan.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibDecShader.h"
#include "grlib/CGLibShader.h"
#include "grlib/CGLibRenderTarget.h"
#include "mm/Col4.h"
#include "mtl/MemManager.h"

namespace cloud {

float CloudObjFlow::FLOW_TEX_SIZE = 128.0f;

unsigned int CloudUniform::s_nUniformBlockSize[CLOUD_UNIFORM_NUM] = {
    0x150, 0x150, 0x70, 0x20, 0xE0, 0x20, 0x3000, 0x20, 0xD0, 0xA0, 0xF0, 0x60, 0xA0, 0xE0, 0x20, 0xA0, 0x140, 0x60,
};

void CloudUniform::createUniform(CloudUniformType type, unsigned int num) {
    releaseUniform();
    setup(s_nUniformBlockSize[type] * (num == 0 ? 1 : num));
}

void CloudUniform::updateData() {
    grlib::CGLibDblUniformBlock::updateData();
}

CloudObjFlow::~CloudObjFlow() {}

void CloudObjFlow::alphaRender() {}

CloudObjMan::~CloudObjMan() {
    m_mdlList.deleteAll();
    m_objList.deleteAll();
    if (m_pReduction != nullptr) {
        delete m_pReduction;
        m_pReduction = nullptr;
    }
    if (m_pCalcParams != nullptr) {
        delete m_pCalcParams;
        m_pCalcParams = nullptr;
    }
}

CloudObjFlow* CloudObjMan::createFlow() {
    m_pFlow = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) CloudObjFlow();
    m_objList.pushBack(m_pFlow);
    return m_pFlow;
}

CloudObjMdl* CloudObjMan::createMdl() {
    m_pMdl = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) CloudObjMdl();
    m_objList.pushBack(m_pMdl);
    return m_pMdl;
}

CloudMdlDataObj* CloudObjMan::createMdlData(const void* data) {
    CloudMdlDataObj* obj = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) CloudMdlDataObj();
    obj->create(data);
    m_mdlList.pushBack(obj);
    return obj;
}

bool CloudObjMan::isRender() const {
    return m_pCalcParams->m_pTarget != nullptr && m_isEnable;
}

void CloudObjMan::alphaRender(const ml::IDrDrawWorkInfo* info) {
    m_pReduction->alphaFastRender();
    for (CloudObj* obj = m_objList.m_pTop; obj != nullptr; obj = obj->m_pNext) {
        obj->alphaRender();
    }
    for (CloudObj* obj = m_objList.m_pTop; obj != nullptr; obj = obj->m_pNext) {
        obj->alphaRenderSec();
    }
    m_pCalcParams->m_pTarget->setRenderTarget(*m_pCalcParams->m_pDepth);
}

CloudObjMdl::~CloudObjMdl() {
    m_partsList.releaseAll();
}

void CloudObjMdl::alphaRender() {
    CloudObjMan* man = CloudMan::sys()->m_pObjMan;
    if (man->m_mdlOn && !man->m_mdlHide && m_partsList.m_pTop != nullptr) {
        man->m_pReduction->m_mdlTarget.clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
        renderBaseMdlPoli();
    }
}

void CloudObjMdl::alphaRenderSec() {
    CloudObjMan* man = CloudMan::sys()->m_pObjMan;
    if (man->m_mdlOn && !man->m_mdlHide && m_partsList.m_pTop != nullptr) {
        renderLastPoli();
    }
}

void CloudObjMdl::counterRender() {
    grlib::CGLibPolygon::setCullingBack();
    grlib::CGLibDecShader* shader = CloudMan::sys()->m_pShaderMan->setShader((CloudShaderType)13, 5, 1, 1);
    unsigned int location = shader->getCurrentShader().getUniformBlockOfs("U_MDL");
    m_mdlUniform.setUniformBlock(location);
    for (CloudMdlParts* parts = m_partsList.m_pTop; parts != nullptr; parts = parts->m_pNext) {
        if (parts->isDisp()) {
            parts->bindVertex();
            parts->render();
        }
    }
}

CloudObjPlane::~CloudObjPlane() {}

void CloudObjPlane::update() {
    CloudObjMan* man = CloudMan::sys()->m_pObjMan;
    if (man->m_planeOn) {
        updateSide();
        updateParams();
        if (!man->m_planeUniSkip || !man->m_planeUniSkip2) {
            updateUniform();
        }
    }
}

void CloudObjPlane::alphaRender() {
    CloudObjMan* man = CloudMan::sys()->m_pObjMan;
    if (man->m_planeOn && !man->m_planeHide) {
        if (!man->m_planeUniSkip || !man->m_planeUniSkip2) {
            renderPlaneDef();
        }
    }
}

CloudObjSky::~CloudObjSky() {}

void CloudObjSky::update() {
    if (CloudMan::sys()->m_pObjMan->m_skyOn) {
        updateParams();
        updateUniform();
    }
}

void CloudObjSky::alphaRender() {
    CloudObjMan* man = CloudMan::sys()->m_pObjMan;
    if (man->m_skyOn && !man->m_skyHide && !man->m_skyHideFrame) {
        renderDetailPoli();
        CloudMan::sys()->m_pObjMan->m_pReduction->m_skyTarget.clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f),
                                                                            (GrlClaerMask)0xF);
        renderSkyPoli();
        renderLastPoli();
    }
}

void CloudUniform::releaseUniform() {
    release();
}

CloudUniform::CloudUniform() {}

CloudUniform::~CloudUniform() {
    releaseUniform();
}

}  // namespace cloud
