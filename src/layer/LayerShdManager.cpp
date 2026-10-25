#include "grlib/GrlTypes.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibState.h"
#include "classes/grlib/CGLibShdListBase.h"
#include "classes/grlib/CGLibShdListData.h"
#include "classes/layer/LayerShdManager.h"
#include "classes/layer/LayerHandleAllocator.h"
#include "layer/LayerRceManager.h"
#include "layer/LayerVertexObj.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibVtxInstans.h"
#include "grlib/CGLibVtxOneInstans.h"
#include "mtl/MemManager.h"

namespace layer {

LayerRceManager::~LayerRceManager() {}

void LayerShdManager::setupMainRenderTarget() {
    grlib::CGLibState::setMainFrameBuffer();
}

void LayerShdManager::setShaderMaskOff() {
    m_pMaskWork = nullptr;
    m_pMaskObj = nullptr;
    m_select.m_maskObjType = 1;
}

void LayerShdManager::setDepthBufferCheckOn() {
    if (!m_depthCheck) {
        grlib::CGLibDepthCtl::setDepthControl(1, 0, GrlCompare(3));
        m_depthCheck = true;
    }
    m_select.m_worldType = 1;
    m_p3DSpaceBlock = nullptr;
}

void LayerShdManager::setDepthBufferCheckOff() {
    if (m_depthCheck) {
        grlib::CGLibDepthCtl::setDepthControl(0, 0, GrlCompare(1));
        m_depthCheck = false;
    }
    m_select.m_worldType = 1;
    m_p3DSpaceBlock = nullptr;
}

void LayerShdManager::set3DSpaceMode(grlib::CGLibDblUniformBlock* block) {
    if (!m_depthCheck) {
        grlib::CGLibDepthCtl::setDepthControl(1, 0, GrlCompare(3));
        m_depthCheck = true;
    }
    m_select.m_worldType = 2;
    m_p3DSpaceBlock = block;
}

void LayerShdManager::setupTexture(const grlib::CGLibTextureBuffer& texture, LayerSamplerType sampler,
                                   unsigned int location) {
    grlib::CGLibCtlTexture::setTexture(texture, m_samplers[sampler], location);
}

grlib::CGLibDecShader* LayerShdManager::setupShader() {
    return (this->*s_CallSelect[m_select.m_shaderType])();
}

grlib::CGLibRenderTarget* LayerShdManager::getDefRenderTarget() {
    if (m_pRenderTarget != nullptr) {
        return m_pRenderTarget;
    }
    return grlib::CGLibState::getMainRenderTarget();
}

void LayerShdManager::setupVertex(LayerVertexObj* obj, unsigned int index) {
    obj->setVertex(index);
}

void LayerShdManager::setupVertex(LayerDefVertType type) {
    grlib::CGLibCtlVertex::setVertex(m_defVertices[type]);
}

void LayerShdManager::setupInstaceVertex(grlib::CGLibVtxInstans& vertex, unsigned int first, unsigned int count) {
    grlib::CGLibCtlVertex::setInstanceVertex(vertex, first, count, 1, 1);
}

void LayerShdManager::setupInstaceVertex(grlib::CGLibVtxOneInstans& vertex, unsigned int first, unsigned int count) {
    grlib::CGLibCtlVertex::setInstanceVertex(vertex, first, count, 1, 1);
}

void LayerShdManager::renderQuadsIndex() {
    m_quadIndices[0].drawIndex();
}

void LayerShdManager::renderInstaceQuadsIndex(unsigned int instances) {
    m_quadIndices[0].drawInsIndex(instances);
}

void LayerShdManager::setupBlendDef() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(5), GrlBlendFunc(6), GrlBlendCombine(1), GrlBlendFunc(2), GrlBlendFunc(6), GrlBlendCombine(1), GrlLogicType(3));
}

void LayerShdManager::setupBlendSwf() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(2), GrlBlendFunc(6), GrlBlendCombine(1), GrlBlendFunc(2), GrlBlendFunc(6), GrlBlendCombine(1), GrlLogicType(3));
}

void LayerShdManager::setupBlendNo() {
    grlib::CGLibColorCtl::setBlendOffControl(GrlLogicType(3));
}

void LayerShdManager::setupBlendAdd() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(5), GrlBlendFunc(2), GrlBlendCombine(1), GrlBlendFunc(2), GrlBlendFunc(2), GrlBlendCombine(1), GrlLogicType(3));
}

void LayerShdManager::setupBlendAddSwf() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(2), GrlBlendFunc(2), GrlBlendCombine(1), GrlBlendFunc(2), GrlBlendFunc(2), GrlBlendCombine(1), GrlLogicType(3));
}

void LayerShdManager::setupBlendSub() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(5), GrlBlendFunc(2), GrlBlendCombine(2), GrlBlendFunc(2), GrlBlendFunc(2), GrlBlendCombine(2), GrlLogicType(3));
}

void LayerShdManager::setupBlendSubSwf() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(2), GrlBlendFunc(2), GrlBlendCombine(2), GrlBlendFunc(2), GrlBlendFunc(2), GrlBlendCombine(2), GrlLogicType(3));
}

void LayerShdManager::setupBlendMul() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(1), GrlBlendFunc(3), GrlBlendCombine(1), GrlBlendFunc(1), GrlBlendFunc(5), GrlBlendCombine(1), GrlLogicType(3));
}

void LayerShdManager::initColor(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_gaugeType = shader.getDeclarationOfs("MENU_GAUGE_TYPE");
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_maskObjType = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
    ofs.m_option = shader.getDeclarationOfs("MENU_FILBLEND_TYPE");
    ofs.m_secTexType = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initTex(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_gaugeType = shader.getDeclarationOfs("MENU_GAUGE_TYPE");
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_maskObjType = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
    ofs.m_option = shader.getDeclarationOfs("MENU_FILBLEND_TYPE");
    ofs.m_secTexType = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initFont(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_iconType = shader.getDeclarationOfs("MENU_ICON_TYPE");
    ofs.m_maskObjType = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
}

void LayerShdManager::initWin(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_gaugeType = shader.getDeclarationOfs("MENU_GAUGE_TYPE");
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_maskObjType = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
    ofs.m_secTexType = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initNumber(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_maskObjType = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
    ofs.m_secTexType = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initPoly(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_option = shader.getDeclarationOfs("MENU_USE_TEX");
    ofs.m_maskObjType = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
    ofs.m_secTexType = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initGsBlur(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_option = shader.getDeclarationOfs("MENU_USE_TEX");
}

void LayerShdManager::initFlowMap(unsigned int) {}

void LayerShdManager::initMemWrite(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_option = shader.getDeclarationOfs("MENU_DECODE_TYPE");
}

void LayerShdManager::initGamma(unsigned int) {}

void LayerShdManager::initDebug(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_option = shader.getDeclarationOfs("MENU_USE_TEX");
}

void LayerShdManager::initTest(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_option = shader.getDeclarationOfs("MENU_USE_TEX");
}

void (LayerShdManager::*LayerShdManager::s_CallSetup[13])(unsigned int) = {
    &LayerShdManager::initColor,  &LayerShdManager::initTex,      &LayerShdManager::initFont,
    &LayerShdManager::initWin,    &LayerShdManager::initTex,      &LayerShdManager::initNumber,
    &LayerShdManager::initPoly,   &LayerShdManager::initGsBlur,   &LayerShdManager::initFlowMap,
    &LayerShdManager::initMemWrite, &LayerShdManager::initGamma,  &LayerShdManager::initDebug,
    &LayerShdManager::initTest,
};
grlib::CGLibDecShader* (LayerShdManager::*LayerShdManager::s_CallSelect[13])() = {
    &LayerShdManager::selectColor,    &LayerShdManager::selectTex,      &LayerShdManager::selectFont,
    &LayerShdManager::selectWin,      &LayerShdManager::selectIcon,     &LayerShdManager::selectNumber,
    &LayerShdManager::selectPoly,     &LayerShdManager::selectGsBlur,   &LayerShdManager::selectFlowMap,
    &LayerShdManager::selectMemWrite, &LayerShdManager::selectGamma,    &LayerShdManager::selectDebug,
    &LayerShdManager::selectTest,
};
void (*LayerShdManager::s_CallBlend[8])() = {
    &LayerShdManager::setupBlendDef, &LayerShdManager::setupBlendSwf,    &LayerShdManager::setupBlendNo,
    &LayerShdManager::setupBlendAdd, &LayerShdManager::setupBlendAddSwf, &LayerShdManager::setupBlendSub,
    &LayerShdManager::setupBlendSubSwf, &LayerShdManager::setupBlendMul,
};

LayerHandleAllocator::LayerHandleAllocator() {}

void LayerHandleAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) {
    m_memHandle = handle;
}

void* LayerHandleAllocator::allocate(unsigned long size, unsigned long alignment) {
    return mtl::MemManager::allocate(m_memHandle, size, alignment, false, "no name", 0);
}

void LayerHandleAllocator::deallocate(void* memory) {
    if (memory != nullptr) {
        mtl::MemManager::deallocate(memory, 0, false);
    }
}

}  // namespace layer
