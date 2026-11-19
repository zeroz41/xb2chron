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
#include "cloud/CloudTextureMan.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibDecShader.h"
#include "grlib/CGLibShader.h"
#include "grlib/CGLibRenderTarget.h"
#include "mm/Col4.h"
#include "mtl/MemManager.h"
#include "cloud/CloudVertexMan.h"
#include "classes/ml/IDrDrawWorkInfo.h"
#include "classes/grlib/context/CGLibSystemContext.h"
#include "grlib/CGLibEtcUniformBlock.h"
#include "grlib/CGLibState.h"
#include "grlib/CGLibTexture.h"
#include "grlib/CGLibUniBaseUtility.h"
#include "nvn/nvn_FuncPtrInline.h"

namespace cloud {

float CloudObjFlow::FLOW_TEX_SIZE = 128.0f;

unsigned int CloudUniform::s_nUniformBlockSize[CLOUD_UNIFORM_NUM] = {
    0x150, 0x150, 0x70, 0x20, 0xE0, 0x20, 0x3000, 0x20, 0xD0, 0xA0, 0xF0, 0x60, 0xA0, 0xE0, 0x20, 0xA0, 0x140, 0x60,
};

unsigned int CloudObjReduction::s_nPixelOfs[8];

void CloudUniform::createUniform(CloudUniformType type, unsigned int num) {
    releaseUniform();
    setup(s_nUniformBlockSize[type] * (num == 0 ? 1 : num));
}

void CloudUniform::updateData() {
    grlib::CGLibDblUniformBlock::updateData();
}

CloudObjFlow::~CloudObjFlow() {}

void CloudObjFlow::update() {
    calcSamplingPos();
    float height = CloudMan::sys()->m_pObjMan->m_pCalcParams->m_height;
    float* buf = (float*)m_flowUniform.getBuff();
    CloudCalcParams* calc = CloudMan::sys()->m_pObjMan->m_pCalcParams;
    grlib::ShdMat44TransposeMat44(buf, calc->m_flowMat);
    grlib::ShdMat44TransposeMat44(buf + 0x10, calc->m_pInfo->m_flowMat[0]);
    grlib::ShdMat44TransposeMat44(buf + 0x20, calc->m_pInfo->m_flowMat[1]);
    grlib::ShdMat44TransposeMat44(buf + 0x30, calc->m_pInfo->m_flowMat[2]);
    buf[0x40] = height;
    buf[0x41] = 0.0f;
    buf[0x42] = 0.0f;
    buf[0x43] = height;
    buf[0x44] = calc->m_flowParam;
    buf[0x45] = 1.0f;
    buf[0x46] = calc->m_flowParam;
    buf[0x47] = 0.0f;
    buf[0x48] = calc->m_uvScale0;
    buf[0x49] = 0.0f;
    buf[0x4A] = calc->m_uvScale1;
    buf[0x4B] = 0.0f;
    m_flowUniform.updateData();
    buf = (float*)m_flowUniform2.getBuff();
    calc = CloudMan::sys()->m_pObjMan->m_pCalcParams;
    buf[0] = calc->m_pInfo->m_flowVec[0];
    buf[1] = calc->m_pInfo->m_flowVec[1];
    buf[2] = calc->m_pInfo->m_flowVec[2];
    buf[3] = 0.0f;
    buf[4] = calc->m_flowBlend;
    buf[5] = 1.0f - calc->m_flowBlend;
    buf[6] = 0.0f;
    buf[7] = 0.0f;
    m_flowUniform2.updateData();
}

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

void CloudObjMan::creataFastSetup() {
    createFlow();
    m_objList.pushBack(new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) CloudObjSky());
    [&] {
        m_pPlane = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) CloudObjPlane();
        m_objList.pushBack(m_pPlane);
    }();
    createMdl();
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

bool CloudObjMan::update(const ml::IDrDrawWorkInfo* info) {
    m_mdlOn = false;
    m_skyHideFrame = false;
    m_planeUniSkip = false;
    m_planeUniSkip2 = true;
    m_isHole = false;
    m_pCalcParams->apply(info);
    if (m_pCalcParams->m_pTarget == nullptr || !m_isEnable) {
        return false;
    }
    m_pReduction->imgUpdate();
    for (CloudMdlDataObj* obj = m_mdlList.m_pTop; obj != nullptr;) {
        bool alive = obj->update();
        CloudMdlDataObj* next = obj->m_pNext;
        if (!alive) {
            m_mdlList.remove(obj);
            delete obj;
        }
        obj = next;
    }
    for (CloudObj* obj = m_objList.m_pTop; obj != nullptr; obj = obj->m_pNext) {
        obj->update();
    }
    if (!m_mdlOn && m_skyHideFrame && m_planeUniSkip && m_planeUniSkip2) {
        return false;
    }
    CloudUniform& uniform = m_pCalcParams->m_uniform;
    CloudCalcParams* calc = CloudMan::sys()->m_pObjMan->m_pCalcParams;
    const float* planes = calc->m_pInfo->m_planes;
    float* buf = (float*)uniform.getBuff();
    grlib::ShdF32SetF32Array(buf, planes, 24);
    buf[0x18] = calc->m_height;
    buf[0x19] = 1.0f / calc->m_heightRange;
    buf[0x1A] = calc->m_heightParam;
    buf[0x1B] = 0.0f;
    uniform.updateData();
    m_pReduction->update();
    return true;
}

bool CloudObjMan::isRender() const {
    return m_pCalcParams->m_pTarget != nullptr && m_isEnable;
}

void CloudObjReduction::update() {
    CloudCalcParams* calc = CloudMan::sys()->m_pObjMan->m_pCalcParams;
    const float* planes = calc->m_pInfo->m_planes;
    float* buf = (float*)m_uniform0.getBuff();
    grlib::ShdMat44TransposeMat44(buf, calc->m_invMat);
    grlib::ShdF32SetF32Array(buf + 16, planes, 24);
    m_uniform0.updateData();

    unsigned int width = m_width;
    unsigned int height = m_height;
    calc = CloudMan::sys()->m_pObjMan->m_pCalcParams;
    buf = (float*)m_uniform1.getBuff();
    buf[0] = calc->m_far - calc->m_near;
    buf[1] = calc->m_far * calc->m_near;
    buf[2] = calc->m_far;
    buf[3] = 0.0f;
    grlib::CGLibRenderTarget* target = calc->m_pTarget;
    float rateX = (float)target->m_width / (float)width;
    float rateY = (float)target->m_height / (float)height;
    buf[4] = -(rateX * 0.5f / (float)target->m_width);
    buf[5] = -(rateY * 0.5f / (float)target->m_height);
    float texelX = 1.0f / (float)width;
    buf[6] = texelX;
    buf[7] = 1.0f / (float)height;
    buf[8] = texelX * 0.0f;
    buf[9] = texelX * 0.0f;
    buf[10] = texelX * 0.0f;
    buf[11] = texelX * 1.0f;
    buf[12] = texelX * 1.0f;
    buf[13] = texelX * 0.0f;
    buf[14] = texelX * 1.0f;
    buf[15] = texelX * 1.0f;
    m_isUpdate = 1;
    m_uniform1.updateData();
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

void CloudObjMdl::update() {
    CloudMan* man = CloudMan::sys();
    CloudCalcParams* calc = man->m_pObjMan->m_pCalcParams;
    float time = man->m_frame * man->m_rate;
    float moveH = time * (calc->m_mdlRateH * calc->m_skySpeed);
    float moveV = time * (calc->m_skySpeed * calc->m_mdlRateV);
    m_scroll.x = 1.0f;
    m_scroll.y = 1.0f;
    m_scroll.z = 1.0f;
    m_scroll.normalize();
    m_scroll.x = moveH * m_scroll.x * 0.1f;
    m_scroll.y = moveV * m_scroll.y * 0.1f;
    m_scroll.z = moveH * m_scroll.z * 0.1f;
    m_partsList.update();
    m_partsList.calcZSort();
    updateUniform();
}

void CloudObjMdl::updateUniform() {
    bool isDisp = false;
    for (CloudMdlParts* parts = m_partsList.m_pTop; parts != nullptr; parts = parts->m_pNext) {
        if (parts->isDisp()) {
            parts->createUniform(m_scroll);
            isDisp = true;
        }
    }
    if (!isDisp) {
        return;
    }
    CloudMan::sys()->m_pObjMan->m_mdlOn = true;
    CloudCalcParams* calc = CloudMan::sys()->m_pObjMan->m_pCalcParams;
    float* buf = (float*)m_mdlUniform0.getBuff();
    buf[0x0] = calc->m_mdlCol0[0];
    buf[0x1] = calc->m_mdlCol0[1];
    buf[0x2] = calc->m_mdlCol0[2];
    buf[0x3] = 1.0f;
    buf[0x4] = calc->m_mdlCol1[0];
    buf[0x5] = calc->m_mdlCol1[1];
    buf[0x6] = calc->m_mdlCol1[2];
    buf[0x7] = 1.0f;
    buf[0x8] = calc->m_skyPos.x;
    buf[0x9] = calc->m_skyPos.y;
    buf[0xA] = calc->m_skyPos.z;
    buf[0xB] = 0.0f;
    buf[0xC] = calc->m_mdlVec[0];
    buf[0xD] = calc->m_mdlVec[1];
    buf[0xE] = calc->m_mdlVec[2];
    buf[0xF] = 0.0f;
    buf[0x10] = calc->m_lightVec0[0];
    buf[0x11] = calc->m_lightVec0[1];
    buf[0x12] = calc->m_lightVec0[2];
    buf[0x13] = 0.0f;
    buf[0x14] = calc->m_lightVec1[0];
    buf[0x15] = calc->m_lightVec1[1];
    buf[0x16] = calc->m_lightVec1[2];
    buf[0x17] = 0.0f;
    m_mdlUniform0.updateData();
    m_mdlUniform.createMdlPosUniform();
    m_mdlUniform.updateData();
}

void CloudObjMdl::renderLastPoli() {
    CloudObjMan* man = CloudMan::sys()->m_pObjMan;
    CloudCalcParams* calc = man->m_pCalcParams;
    if (calc->m_tiledCache[calc->m_tiledIdx][2].m_isEnable) {
        grlib::CGLibGPUCache::setTiledCacheSize(calc->m_tiledCache[calc->m_tiledIdx][2].m_width,
                                                calc->m_tiledCache[calc->m_tiledIdx][2].m_height);
        grlib::CGLibGPUCache::setTiledCacheAction((GrlTiledCacheAction)1);
    }
    grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)2, (GrlBlendFunc)6, (GrlBlendCombine)1, (GrlLogicType)3);
    calc->m_pTarget->setRenderTarget(*calc->m_pDepth);
    grlib::CGLibPolygon::setCullingBack();
    grlib::CGLibDepthCtl::setDepthStencilControl(1, 0, (GrlCompare)3, 1, (GrlCompare)5, 0x20, 0x20, 0x20, (GrlStencil)3,
                                                 (GrlStencil)1, (GrlStencil)1);
    CloudShaderMan* shd = CloudMan::sys()->m_pShaderMan;
    CloudObjReduction* reduction = man->m_pReduction;
    grlib::CGLibRenderTarget& target = man->m_planeCountSkip ? reduction->m_mdlTarget : reduction->m_upTarget;
    grlib::CGLibDecShader* shader = shd->setShader((CloudShaderType)10, 1, 2, 1);
    unsigned int mdl = shader->getCurrentShader().getUniformBlockOfs("U_MDL");
    unsigned int col = shader->getCurrentShader().getUniformBlockOfs("U_COL");
    unsigned int count = shader->getCurrentShader().getUniformBlockOfs("U_COUNT");
    unsigned int base = shader->getCurrentShader().getTextureLocation("base");
    unsigned int dwnDep = shader->getCurrentShader().getTextureLocation("dwnDep");
    unsigned int orgDep = shader->getCurrentShader().getTextureLocation("orgDep");
    shd->setTexture(base, *target.m_pTexture, (CloudSamplerType)2);
    shd->setTexture(dwnDep, *calc->m_pDepthTarget1->m_pSubTexture, (CloudSamplerType)1);
    shd->setTexture(orgDep, *calc->m_pDepthTarget0->m_pSubTexture, (CloudSamplerType)1);
    m_mdlUniform.setUniformBlock(mdl);
    reduction->m_counter[3].setUniformBlock(count);
    for (CloudMdlParts* parts = m_partsList.m_pTop; parts != nullptr; parts = parts->m_pNext) {
        if (parts->isDisp()) {
            parts->m_uniform.setUniformBlock(col);
            parts->bindVertex();
            parts->render();
        }
    }
    if (calc->m_tiledCache[calc->m_tiledIdx][2].m_isEnable) {
        grlib::CGLibGPUCache::setTiledCacheAction((GrlTiledCacheAction)3);
        grlib::CGLibGPUCache::setTiledCacheAction((GrlTiledCacheAction)2);
    }
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

void CloudObjReduction::renderUpScale(grlib::CGLibRenderTarget& target) {
    CloudCalcParams* calc = CloudMan::sys()->m_pObjMan->m_pCalcParams;
    float width = (float)target.m_width;
    float height = (float)target.m_height;
    grlib::CGLibEtcUniformBlock uniform;
    float* buf = (float*)uniform.getBuff();
    buf[0] = width;
    buf[1] = height;
    buf[2] = 1.0f / width;
    buf[3] = 1.0f / height;
    buf[4] = calc->m_far - calc->m_near;
    buf[5] = calc->m_far * calc->m_near;
    buf[6] = calc->m_far;
    buf[7] = 0.0f;
    uniform.updateData(0x20);
    grlib::CGLibColorCtl::setBlendOffControl((GrlLogicType)3);
    grlib::CGLibPolygon::setCullingOff();
    m_upTarget.setRenderTarget();
    CloudShaderMan* shd = CloudMan::sys()->m_pShaderMan;
    CloudVertexMan* vtx = CloudMan::sys()->m_pVertexMan;
    grlib::CGLibDecShader* shader = shd->setShader((CloudShaderType)15, 1, 1, 1);
    uniform.setUniformBlock(shader->getCurrentShader().getUniformBlockOfs("U_POST"));
    unsigned int depCol = shader->getCurrentShader().getTextureLocation("depCol");
    unsigned int dwnDep = shader->getCurrentShader().getTextureLocation("dwnDep");
    unsigned int orgDep = shader->getCurrentShader().getTextureLocation("orgDep");
    shd->setTexture(dwnDep, *m_depth1.m_pSubTexture, (CloudSamplerType)1);
    shd->setTexture(orgDep, *calc->m_pDepthTarget1->m_pSubTexture, (CloudSamplerType)1);
    shd->setTexture(depCol, *target.m_pTexture, (CloudSamplerType)2);
    vtx->bindVertexList((CloudVertexType)2);
    vtx->renderIndexList((CloudVertexType)2);
}

// the planes to draw, back one first; a plane whose uniform update is skipped is left out (inferred helper, no
// symbol: inlined into renderPlaneDef; alphaRenderSec builds the same list)
static inline int getPlaneList(unsigned int* list) {
    CloudObjMan* man = CloudMan::sys()->m_pObjMan;
    int num = 0;
    if (!man->m_planeUniSkip) {
        if (!man->m_planeUniSkip2) {
            list[0] = 1;
            list[1] = 0;
            num = 2;
        } else {
            list[0] = 0;
            list[1] = 1;
            num = 1;
        }
    } else {
        list[0] = 1;
        list[1] = 0;
        num = 1;
    }
    return num;
}

CloudObjPlane::CloudObjPlane() {
    m_planeUniform2.createUniform(CLOUD_UNIFORM_BLUR, 0);
    m_planeUniform3.createUniform(CLOUD_UNIFORM_BLUR, 0);
    for (int i = 0; i < 2; i++) {
        m_planeUniform0[i].createUniform(CLOUD_UNIFORM_DEF, 0);
        m_planeUniform1[i].createUniform(CLOUD_UNIFORM_COLOR, 0);
        m_color0[i] = mm::Vec3(0.0f, 0.0f, 0.0f);
        m_color1[i] = mm::Vec3(0.0f, 0.0f, 0.0f);
        m_color2[i] = mm::Vec3(0.0f, 0.0f, 0.0f);
        m_color3[i] = mm::Vec3(0.0f, 0.0f, 0.0f);
        m_color4[i] = mm::Vec3(0.0f, 0.0f, 0.0f);
        m_scale0[i] = 1.0f;
        m_scale1[i] = 1.0f;
        m_scale2[i] = 1.0f;
        m_scale3[i] = 1.0f;
    }
    m_planeParam1 = 0.5f;
    m_planeParam0 = 0.0f;
    m_uniParam = 0;
    m_farDist = 0.0f;
    m_uniRate = 0.0f;
    m_planeFlag = true;
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

void CloudObjPlane::updateUniform() {
    // the three unnamed floats are never set by the original (createColorUniform's s0-s2 are left as they are)
    float unset0, unset1, unset2;
    for (unsigned int i = 0; i < 2; i++) {
        m_planeUniform0[i].createDefUniform(i, m_uniParam, (i == 0 && m_farDist != 0.0f) ? m_farDist : 20000.0f,
                                            m_uniRate);
        m_planeUniform0[i].updateData();
        m_planeUniform1[i].createColorUniform(m_color0[i], m_color1[i], m_color2[i], m_color3[i], m_color4[i], unset0,
                                              unset1, unset2, i, m_uniParam, m_uniRate);
        m_planeUniform1[i].updateData();
    }
    m_planeUniform2.createBlurUniform(false);
    m_planeUniform2.updateData();
    m_planeUniform3.createBlurUniform(true);
    m_planeUniform3.updateData();
}

void CloudObjPlane::renderLastPoli(unsigned int idx) {
    CloudObjMan* man = CloudMan::sys()->m_pObjMan;
    CloudCalcParams* calc = man->m_pCalcParams;
    grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)2, (GrlBlendFunc)6, (GrlBlendCombine)1, (GrlLogicType)3);
    grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 0);
    CloudShaderMan* shd = CloudMan::sys()->m_pShaderMan;
    CloudVertexMan* vtx = CloudMan::sys()->m_pVertexMan;
    grlib::CGLibPolygon::setCullingOff();
    if (idx == 0 && man->m_planeCountSkip && m_farDist == 0.0f) {
        grlib::CGLibDepthCtl::setDepthStencilControl(1, 1, (GrlCompare)3, 1, (GrlCompare)5, 0x20, 0x20, 0x20,
                                                     (GrlStencil)3, (GrlStencil)1, (GrlStencil)1);
    } else {
        grlib::CGLibDepthCtl::setDepthStencilControl(1, 1, (GrlCompare)3, 1, (GrlCompare)5, 0x20, 0x20, 0x20,
                                                     (GrlStencil)3, (GrlStencil)1, (GrlStencil)1);
    }
    if (idx == 1) {
        calc->m_pTarget->setRenderTarget(*calc->m_pDepth, *calc->m_pDeptTarget, *calc->m_pMrtTarget);
    } else {
        calc->m_pTarget->setRenderTarget(*calc->m_pDepth, *calc->m_pDeptTarget);
    }
    CloudObjReduction* reduction = CloudMan::sys()->m_pObjMan->m_pReduction;
    grlib::CGLibDecShader* shader = shd->setShader((CloudShaderType)10, idx == 0 ? 2 : 4, 1, 1);
    unsigned int mdl = shader->getCurrentShader().getUniformBlockOfs("U_MDL");
    unsigned int col = shader->getCurrentShader().getUniformBlockOfs("U_COL");
    unsigned int count = shader->getCurrentShader().getUniformBlockOfs("U_COUNT");
    unsigned int base = shader->getCurrentShader().getTextureLocation("base");
    unsigned int dept = shader->getCurrentShader().getTextureLocation("dept");
    unsigned int zmdl = shader->getCurrentShader().getTextureLocation("zmdl");
    unsigned int maskTex = shader->getCurrentShader().getTextureLocation("maskTex");
    shd->setTexture(base, *reduction->m_target0.m_pTexture, (CloudSamplerType)2);
    shd->setTexture(zmdl, *reduction->m_target1.m_pTexture, (CloudSamplerType)2);
    shd->setTexture(maskTex, *reduction->m_target3.m_pTexture, (CloudSamplerType)2);
    shd->setTexture(dept, *calc->m_pDeptTarget->m_pTexture, (CloudSamplerType)1);
    m_planeUniform0[idx].setUniformBlock(mdl);
    m_planeUniform1[idx].setUniformBlock(col);
    if (idx == 0) {
        if (man->m_planeCountSkip) {
            man->m_pReduction->m_counter[0].setUniformBlock(count);
            vtx->bindVertexList((CloudVertexType)3);
            vtx->renderIndexList((CloudVertexType)3);
        } else {
            man->m_pReduction->m_counter[1].setUniformBlock(count);
            vtx->bindVertexList((CloudVertexType)1);
            vtx->renderIndexList((CloudVertexType)1);
        }
    } else if (m_plane1CountSkip) {
        man->m_pReduction->m_counter[0].setUniformBlock(count);
        vtx->bindVertexList((CloudVertexType)3);
        vtx->renderIndexList((CloudVertexType)3);
    } else {
        man->m_pReduction->m_counter[2].setUniformBlock(count);
        vtx->bindVertexList((CloudVertexType)1);
        vtx->renderIndexList((CloudVertexType)1);
    }
    grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 1);
    grlib::CGLibCtlShader::setMemoryBarrierBit(4);
}

void CloudObjPlane::renderPlaneDef() {
    CloudObjReduction* reduction = CloudMan::sys()->m_pObjMan->m_pReduction;
    reduction->m_target1.clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
    reduction->m_target2.clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
    reduction->m_target3.clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
    unsigned int list[2];
    int num = getPlaneList(list);
    for (int i = 0; i < num; i++) {
        renderPlanePoli(list[i]);
        renderBlur(list[i]);
        renderDepth(list[i]);
    }
}

CloudObjSky::CloudObjSky() {
    m_skyUniform0.createUniform(CLOUD_UNIFORM_SKY_0, 0);
    m_skyUniform1.createUniform(CLOUD_UNIFORM_SKY_1, 0);
    m_skyUniform2.createUniform(CLOUD_UNIFORM_SKY_2, 0);
    m_targetSize = CloudMan::sys()->m_pObjMan->m_pCalcParams->m_skyTexSize;
    m_target.setTextureInfo((float)m_targetSize, (float)m_targetSize, (GrlSurfaceFormat)1, false, 0);
    m_scroll = mm::Vec3(0.0f, 0.0f, 0.0f);
    m_detailScroll = mm::Vec3(0.0f, 0.0f, 0.0f);
    m_detailParam = 1.0f;
    m_isFirst = true;
}

CloudObjSky::~CloudObjSky() {}

void CloudObjSky::update() {
    if (CloudMan::sys()->m_pObjMan->m_skyOn) {
        updateParams();
        updateUniform();
    }
}

void CloudObjSky::updateParams() {
    CloudMan* sys = CloudMan::sys();
    CloudCalcParams* calc = sys->m_pObjMan->m_pCalcParams;
    float frame = sys->m_frame;
    float rate = sys->m_rate;
    float rateH = calc->m_skyRateH;
    float speed0 = calc->m_skySpeed;
    float rateV = calc->m_skyRateV;
    const float sq2 = sqrtf(2.0f);
    float time = frame * rate;
    float speedH = rateH * speed0;
    float speedV = speed0 * rateV;
    mm::Vec3 dir(cosf(calc->m_skyWindAngle * 0.017453292f) * sq2, 1.0f,
                 sinf(calc->m_skyWindAngle * 0.017453292f) * sq2);
    float len = dir.length();
    float moveH = time * speedH;
    float moveV = time * speedV;
    if (len <= 1e-6f) {
        dir = mm::Vec3::zero;
    } else {
        float scale = 1.0f / len;
        dir = mm::Vec3(dir.x * scale, scale, dir.z * scale);
    }
    m_scroll += mm::Vec3(moveH * dir.x, moveV * dir.y, moveH * dir.z) * (calc->m_skyScale * calc->m_skyScale);
    float speed = calc->m_skySpeed * 0.5f;
    float move = time * speed * 0.01f;
    m_detailScroll.x += calc->m_detailDir[0] * move;
    m_detailScroll.y += calc->m_detailDir[1] * move;
    m_detailScroll.z += calc->m_detailDir[2] * move;
    if (m_isFirst) {
        m_detailParam = calc->m_skyParam[2];
        m_isFirst = false;
    } else if (m_detailParam != calc->m_skyParam[2]) {
        float diff = (m_detailParam - calc->m_skyParam[2]) * 0.5f;
        m_detailScroll.x = diff + m_detailScroll.x;
        m_detailScroll.y = diff + m_detailScroll.y;
        m_detailParam = calc->m_skyParam[2];
    }
    m_detailScroll.x = fmodf(m_detailScroll.x, 256.0f);
    m_detailScroll.y = fmodf(m_detailScroll.y, 256.0f);
    if (m_detailScroll.z >= 4352.0f) {
        m_detailScroll.z += -4352.0f;
    } else if (m_detailScroll.z <= -4352.0f) {
        m_detailScroll.z += 4352.0f;
    }
    m_scroll.x = fmodf(m_scroll.x, 256.0f);
    m_scroll.y = fmodf(m_scroll.y, 256.0f);
    if (m_scroll.z >= 4352.0f) {
        m_scroll.z += -4352.0f;
    } else if (m_scroll.z <= -4352.0f) {
        m_scroll.z += 4352.0f;
    }
    if (calc->m_skyTexSize != m_targetSize) {
        m_targetSize = calc->m_skyTexSize;
        m_target.setTextureInfo((float)m_targetSize, (float)m_targetSize, (GrlSurfaceFormat)1, false, 0);
        m_isTargetClear = true;
    }
}

void CloudObjSky::updateUniform() {
    CloudCalcParams* calc = CloudMan::sys()->m_pObjMan->m_pCalcParams;
    float* buf = (float*)m_skyUniform0.getBuff();
    grlib::ShdMat44TransposeMat44(buf, calc->m_skyMat[0]);
    grlib::ShdMat44TransposeMat44(buf + 0x10, calc->m_skyMat[1]);
    grlib::ShdMat44TransposeMat44(buf + 0x20, calc->m_skyMat[1]);
    buf[0x30] = calc->m_skyPos.x;
    buf[0x31] = calc->m_skyPos.y;
    buf[0x32] = calc->m_skyPos.z;
    buf[0x33] = calc->m_far * 0.9f;
    m_skyUniform0.updateData();
    m_skyUniform1.createSkyUniform(m_scroll);
    m_skyUniform1.updateData();
    CloudMan* sys = CloudMan::sys();
    calc = sys->m_pObjMan->m_pCalcParams;
    float time = sys->m_frame * sys->m_rate;
    buf = (float*)m_skyUniform2.getBuff();
    buf[0] = m_detailScroll.x;
    buf[1] = m_detailScroll.y;
    buf[2] = m_detailScroll.z;
    buf[3] = 0.0f;
    buf[4] = calc->m_skyParam[2];
    buf[5] = calc->m_skyParam[1];
    buf[6] = calc->m_skyParam[0];
    buf[7] = time;
    m_skyUniform2.updateData();
}

void CloudUniform::createSkyUniform(const mm::Vec3& scroll) {
    float* buf = (float*)getBuff();
    CloudCalcParams* calc = CloudMan::sys()->m_pObjMan->m_pCalcParams;
    buf[0x0] = calc->m_skyCol0[0];
    buf[0x1] = calc->m_skyCol0[1];
    buf[0x2] = calc->m_skyCol0[2];
    buf[0x3] = 1.0f;
    buf[0x4] = calc->m_skyCol1[0];
    buf[0x5] = calc->m_skyCol1[1];
    buf[0x6] = calc->m_skyCol1[2];
    buf[0x7] = 1.0f;
    grlib::ShdF32SetF32Array(buf + 0x8, &calc->m_skyPos.x, 4);
    float scale = calc->m_skyScale * 10.0f;
    buf[0xC] = calc->m_skyFactor * 10.0f;
    buf[0xD] = scale;
    buf[0xE] = calc->m_skyParam2[0];
    buf[0xF] = calc->m_skyParam2[1];
    buf[0x10] = calc->m_uvScale0;
    buf[0x11] = 0.0f;
    buf[0x12] = calc->m_uvScale1;
    buf[0x13] = 0.0f;
    buf[0x14] = scroll.x;
    buf[0x15] = scroll.y;
    buf[0x16] = scroll.z;
    buf[0x17] = 0.0f;
    buf[0x18] = 0.0f;
    buf[0x19] = calc->m_skyRadius;
    buf[0x1A] = 0.0f;
    buf[0x1B] = 1.0f;
    float radius2 = calc->m_skyRadius * calc->m_skyRadius;
    float outer = calc->m_skyRadius + calc->m_skyAtmHeight;
    float horizon = sqrtf(outer * outer - radius2);
    mm::Vec3 dir(horizon, calc->m_skyRadius, 0.0f);
    float length = dir.length();
    if (length <= 1e-6f) {
        dir = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        dir.x = scale * dir.x;
        dir.y = scale * dir.y;
        dir.z = scale * dir.z;
    }
    float x = dir.x;
    buf[0x1C] = calc->m_skyRadius + calc->m_skyAtmHeight;
    buf[0x1D] = calc->m_skyRadius + 1.0f;
    buf[0x1E] = 1.0f / x;
    buf[0x1F] = 1.0f / horizon;
    buf[0x20] = calc->m_lightVec0[0];
    buf[0x21] = calc->m_lightVec0[1];
    buf[0x22] = calc->m_lightVec0[2];
    buf[0x23] = 1.0f;
    buf[0x24] = calc->m_lightVec1[0];
    buf[0x25] = calc->m_lightVec1[1];
    buf[0x26] = calc->m_lightVec1[2];
    buf[0x27] = 1.0f;
}

void CloudObjSky::renderDetailPoli() {
    if (m_isTargetClear) {
        m_isTargetClear = false;
        m_target.clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), (GrlClaerMask)0xF);
    }
    m_target.setRenderTarget();
    grlib::CGLibPolygon::setCullingOff();
    grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)5, (GrlBlendFunc)6, (GrlBlendCombine)1, (GrlLogicType)3);
    grlib::CGLibColorCtl::setColorBufferOn();
    grlib::CGLibDepthCtl::setDepthControl(0, 0, (GrlCompare)7);
    CloudVertexMan* vtx = CloudMan::sys()->m_pVertexMan;
    CloudShaderMan* shd = CloudMan::sys()->m_pShaderMan;
    CloudTextureMan* tex = CloudMan::sys()->m_pTextureMan;
    vtx->bindVertexList((CloudVertexType)2);
    grlib::CGLibDecShader* shader = shd->setShader((CloudShaderType)8, 0, 1, 1);
    unsigned int det = shader->getCurrentShader().getUniformBlockOfs("U_DET");
    unsigned int t3d = shader->getCurrentShader().getTextureLocation("t3d");
    unsigned int texNoise = shader->getCurrentShader().getTextureLocation("texNoise");
    shd->setTexture(t3d, *tex->m_pTextures[1], (CloudSamplerType)0);
    shd->setTexture(texNoise, *tex->m_pTextures[2], (CloudSamplerType)0);
    m_skyUniform2.setUniformBlock(det);
    vtx->renderIndexList((CloudVertexType)2);
}

void CloudObjSky::renderSkyPoli() {
    CloudCalcParams* calc = CloudMan::sys()->m_pObjMan->m_pCalcParams;
    grlib::CGLibColorCtl::setBlendOffControl((GrlLogicType)3);
    grlib::CGLibDepthCtl::setDepthControl(1, 0, (GrlCompare)3);
    CloudObjReduction* reduction = CloudMan::sys()->m_pObjMan->m_pReduction;
    reduction->m_skyTarget.setRenderTarget(*reduction->m_depth0.m_pDepthBuffer);
    grlib::CGLibPolygon::setCullingOff();
    CloudVertexMan* vtx = CloudMan::sys()->m_pVertexMan;
    CloudShaderMan* shd = CloudMan::sys()->m_pShaderMan;
    CloudTextureMan* tex = CloudMan::sys()->m_pTextureMan;
    vtx->bindVertexList((CloudVertexType)5);
    grlib::CGLibDecShader* shader = shd->setShader((CloudShaderType)6, calc->m_skyShader, 2, 1);
    unsigned int col = shader->getCurrentShader().getUniformBlockOfs("U_COL");
    unsigned int mdl = shader->getCurrentShader().getUniformBlockOfs("U_MDL");
    unsigned int fog = shader->getCurrentShader().getUniformBlockOfs("U_FOG");
    unsigned int count = shader->getCurrentShader().getUniformBlockOfs("U_COUNT");
    unsigned int noisetex = shader->getCurrentShader().getTextureLocation("noisetex");
    unsigned int texNoise = shader->getCurrentShader().getTextureLocation("texNoise");
    unsigned int detail = shader->getCurrentShader().getTextureLocation("detail");
    shd->setTexture(noisetex, *tex->m_pTextures[1], (CloudSamplerType)0);
    shd->setTexture(texNoise, *tex->m_pTextures[2], (CloudSamplerType)0);
    shd->setTexture(detail, *m_target.m_pTexture, (CloudSamplerType)2);
    m_skyUniform0.setUniformBlock(mdl);
    m_skyUniform1.setUniformBlock(col);
    calc->m_uniform.setUniformBlock(fog);
    CloudMan::sys()->m_pObjMan->m_pReduction->m_counter[0].setUniformBlock(count);
    vtx->renderIndexList((CloudVertexType)5);
}

void CloudObjSky::renderLastPoli() {
    grlib::CGLibCtlShader::setMemoryBarrierBit(4);
    CloudObjMan* man = CloudMan::sys()->m_pObjMan;
    CloudCalcParams* calc = man->m_pCalcParams;
    calc->m_pTarget->setRenderTarget(*calc->m_pDepth);
    grlib::CGLibPolygon::setCullingOff();
    grlib::CGLibDepthCtl::setDepthControl(1, 0, (GrlCompare)3);
    grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)2, (GrlBlendFunc)6, (GrlBlendCombine)1, (GrlLogicType)3);
    CloudVertexMan* vtx = CloudMan::sys()->m_pVertexMan;
    CloudShaderMan* shd = CloudMan::sys()->m_pShaderMan;
    vtx->bindVertexList((CloudVertexType)5);
    CloudObjReduction* reduction = man->m_pReduction;
    grlib::CGLibDecShader* shader = shd->setShader((CloudShaderType)10, 3, 2, 1);
    unsigned int mdl = shader->getCurrentShader().getUniformBlockOfs("U_MDL");
    unsigned int count = shader->getCurrentShader().getUniformBlockOfs("U_COUNT");
    unsigned int base = shader->getCurrentShader().getTextureLocation("base");
    shd->setTexture(base, *reduction->m_skyTarget.m_pTexture, (CloudSamplerType)2);
    m_skyUniform0.setUniformBlock(mdl);
    man->m_pReduction->m_counter[0].setUniformBlock(count);
    vtx->renderIndexList((CloudVertexType)5);
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

CloudObjReduction::CloudObjReduction() {
    m_uniform0.createUniform(CLOUD_UNIFORM_15, 0);
    m_uniform1.createUniform(CLOUD_UNIFORM_16, 0);
    m_height = -1;
    m_width = -1;
    m_isReady = false;
}

CloudObjReduction::~CloudObjReduction() {
    m_counter[0].release();
    m_counter[1].release();
    m_counter[2].release();
    m_counter[3].release();
    m_skyTarget.release();
    m_upTarget.release();
    m_target0.release();
    m_target1.release();
    m_target2.release();
    m_target3.release();
    m_mdlTarget.release();
    m_depth0.release();
    m_depth1.release();
    m_uniform0.releaseUniform();
    m_uniform1.releaseUniform();
}

void CloudUniform::releaseUniform() {
    release();
}

unsigned int CloudObjReduction::getPixelMem(unsigned int& mem, unsigned int width, unsigned int height) {
    unsigned int size;
    unsigned int align;
    unsigned int ofs;
    grlib::CGLibTexture::getDepthPixelSize(size, align, width / 4, height / 2, (GrlDepthFormat)0x34);
    ofs = (align - mem % align) % align + mem;
    mem = size + ofs;
    s_nPixelOfs[0] = ofs;
    grlib::CGLibTexture::getDepthPixelSize(size, align, width / 4, height / 2, (GrlDepthFormat)0x34);
    ofs = (align - mem % align) % align + mem;
    mem = size + ofs;
    s_nPixelOfs[1] = ofs;
    grlib::CGLibTexture::getDefPixelSize(size, align, width / 4, height / 2, 0, (GrlSurfaceFormat)0x29);
    ofs = (align - mem % align) % align + mem;
    mem = size + ofs;
    s_nPixelOfs[2] = ofs;
    grlib::CGLibTexture::getDefPixelSize(size, align, width / 4, height / 2, 0, (GrlSurfaceFormat)0x29);
    ofs = (align - mem % align) % align + mem;
    mem = size + ofs;
    s_nPixelOfs[3] = ofs;
    grlib::CGLibTexture::getDefPixelSize(size, align, width / 4, height / 2, 0, (GrlSurfaceFormat)0x11);
    ofs = (align - mem % align) % align + mem;
    mem = size + ofs;
    s_nPixelOfs[4] = ofs;
    grlib::CGLibTexture::getDefPixelSize(size, align, width / 4, height / 2, 0, (GrlSurfaceFormat)0x29);
    ofs = (align - mem % align) % align + mem;
    mem = size + ofs;
    s_nPixelOfs[5] = ofs;
    grlib::CGLibTexture::getDefPixelSize(size, align, width / 4, height / 2, 0, (GrlSurfaceFormat)0xD);
    ofs = (align - mem % align) % align + mem;
    mem = size + ofs;
    s_nPixelOfs[6] = ofs;
    grlib::CGLibTexture::getDefPixelSize(size, align, width / 2, height / 2, 0, (GrlSurfaceFormat)0x29);
    ofs = (align - mem % align) % align + mem;
    mem = size + ofs;
    s_nPixelOfs[7] = ofs;
    return s_nPixelOfs[0];
}

void CloudObjReduction::stencilRender() {
    CloudMan::sys()->m_pObjMan->m_pCalcParams->m_pDepthTarget0->setRenderTarget();
    grlib::CGLibColorCtl::setColorBufferOff();
    grlib::CGLibColorCtl::setBlendOffControl((GrlLogicType)3);
    grlib::CGLibPolygon::setCullingOff();
    grlib::CGLibDepthCtl::setDepthStencilControl(0, 0, (GrlCompare)7, 1, (GrlCompare)7, 0, 0x20, 0x20, (GrlStencil)3,
                                                 (GrlStencil)1, (GrlStencil)1);
    CloudVertexMan* vtx = CloudMan::sys()->m_pVertexMan;
    CloudShaderMan* shd = CloudMan::sys()->m_pShaderMan;
    vtx->bindVertexList((CloudVertexType)2);
    grlib::CGLibDecShader* shader = shd->setShader((CloudShaderType)13, 4, 1, 1);
    unsigned int count1 = shader->getCurrentShader().getUniformBlockOfs("U_COUNT1");
    unsigned int count2 = shader->getCurrentShader().getUniformBlockOfs("U_COUNT2");
    unsigned int count3 = shader->getCurrentShader().getUniformBlockOfs("U_COUNT3");
    unsigned int count4 = shader->getCurrentShader().getUniformBlockOfs("U_COUNT4");
    m_counter[0].setUniformBlock(count1);
    m_counter[1].setUniformBlock(count2);
    m_counter[2].setUniformBlock(count3);
    m_counter[3].setUniformBlock(count4);
    vtx->renderIndexList((CloudVertexType)2);
    grlib::CGLibColorCtl::setColorBufferOn();
}

CloudUniform::CloudUniform() {}

CloudUniform::~CloudUniform() {
    releaseUniform();
}

}  // namespace cloud
