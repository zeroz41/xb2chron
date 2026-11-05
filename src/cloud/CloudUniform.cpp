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
