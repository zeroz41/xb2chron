#include "ptlib/renderer/RendererManager.h"
#include "ptlib/renderer/RendererObj.h"
#include "ptlib/renderer/ShaderManager.h"
#include "ptlib/renderer/ScreenRenderManager.h"
#include "ptlib/material/MaterialManager.h"
#include "ptlib/material/MaterialBase.h"
#include "ptlib/DrDrawWorkInfoEF.h"
#include "ptlib/ParticleSystem.h"
#include "ptlib/StackAllocater.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibRenderTarget.h"
#include "grlib/CGLibTexture.h"

#line 1 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/renderer/particle_renderer_obj.cpp"

namespace ptlib { namespace renderer {

void RenderGrObj::term() {
    m_backBuffer.release();
    m_shaderManager.term();
}

void RenderManager::draw(emitter::EmitterManager& manager, FxParam& param, int view, int pass) {
    if (m_pGrObj != nullptr) {
        m_pGrObj->fxcore_setup_target_update(view);
    }
    if (m_pGrObj != nullptr) {
        m_pGrObj->draw(manager, param, view, pass);
    }
}

void* RenderManager::tex_loadmem(int key, void* data, int size, int format, unsigned char* param, bool permanent,
                                 void* owner) {
    if (m_pGrObj == nullptr) {
        return nullptr;
    }
    material::MaterialBase* pMaterial = material::MaterialManager::getPtr()->create(
        key, static_cast<material::eMaterialType>(0), data, size, false, param, owner, format);
    if (pMaterial != nullptr && permanent) {
        pMaterial->m_permanent = true;
    }
    return pMaterial;
}

void RenderManager::tex_freemem(int key, void* owner) {
    if (m_pGrObj != nullptr) {
        const int materialKey = key;
        material::MaterialManager::getPtr()->destroyMateriaByKey(materialKey, owner);
    }
}

RenderGrObj* RenderManager::getRenderGrObj() {
    return m_pGrObj;
}

const DrDrawWorkInfoEF* RenderManager::getDrInfo() {
    if (m_pGrObj != nullptr) {
        return m_pGrObj->m_pDrInfo;
    }
    return nullptr;
}

void ShaderManager::init() {
    int size = 0;
    m_pFile = ParticleManager::readFileBlock("/effect/shader/shd_effect.wishp", size);
    m_shdList.createPacShader(m_pFile, 1011, true);
    for (int i = 0; i < 16; i++) {
        grlib::CGLibDecShader* pShader = &m_shdList.m_pList[i];
        m_declOfs[i].m_veriationMode = pShader->getDeclarationOfs("VERIATION_MODE");
        m_declOfs[i].m_softMode = pShader->getDeclarationOfs("SOFT_MODE");
        m_declOfs[i].m_shadowMode = pShader->getDeclarationOfs("SHADOW_MODE");
        m_declOfs[i].m_clipMode = pShader->getDeclarationOfs("CLIP_MODE");
        m_declOfs[i].m_usingTemporalAA = pShader->getDeclarationOfs("USING_TEMPORAL_AA");
    }
}

grlib::CGLibDecShader* ShaderManager::getShaderByIndex(EffShdType type) {
    return &m_shdList.get(type);
}

void BackBuffer::createAll(StaticAllocObj* pAlloc, float width, float height, float, float, unsigned int offset) {
    m_pHalfDepth = static_cast<grlib::CGLibRenderTarget*>(pAlloc->sysAlloc(sizeof(grlib::CGLibRenderTarget), 16, nullptr, 0));
    m_pHalfColor = static_cast<grlib::CGLibRenderTarget*>(pAlloc->sysAlloc(sizeof(grlib::CGLibRenderTarget), 16, nullptr, 0));
    m_pTiny = static_cast<grlib::CGLibRenderTarget*>(pAlloc->sysAlloc(sizeof(grlib::CGLibRenderTarget), 16, nullptr, 0));
    m_pTiny2 = static_cast<grlib::CGLibRenderTarget*>(pAlloc->sysAlloc(sizeof(grlib::CGLibRenderTarget), 16, nullptr, 0));
    new (m_pHalfDepth) grlib::CGLibRenderTarget();
    new (m_pHalfColor) grlib::CGLibRenderTarget();
    new (m_pTiny) grlib::CGLibRenderTarget();
    new (m_pTiny2) grlib::CGLibRenderTarget();
    m_pTiny->setTextureInfo(8.0f, 8.0f, static_cast<GrlSurfaceFormat>(1), false, 0);
    m_pTiny2->setTextureInfo(8.0f, 8.0f, static_cast<GrlSurfaceFormat>(0x26), false, 0);
    width *= 0.5f;
    height *= 0.5f;
    unsigned int size;
    unsigned int align;
    grlib::CGLibTexture::getDefPixelSize(size, align, width, height, 0, static_cast<GrlSurfaceFormat>(0x3F));
    unsigned int depthOffset = offset + (align - offset % align) % align;
    offset = size + depthOffset;
    m_pHalfDepth->setTextureInfo(width, height, static_cast<GrlSurfaceFormat>(0x3F), true, depthOffset);
    grlib::CGLibTexture::getDefPixelSize(size, align, width, height, 0, static_cast<GrlSurfaceFormat>(5));
    offset += (align - offset % align) % align;
    m_pHalfColor->setTextureInfo(width, height, static_cast<GrlSurfaceFormat>(5), true, offset);
}

RenderGrObj::~RenderGrObj() {
    term();
}

BackBuffer* RenderGrObj::getBackBuffer() {
    return &m_backBuffer;
}

void RenderGrObj::draw_capture() {
    if (m_pDrInfo->m_pCapture != nullptr && screen::ScreenRenderManager::isValid()) {
        screen::ScreenRenderManager* pScreen = screen::ScreenRenderManager::getPtr();
        grlib::CGLibDepthCtl::setDepthControl(0, 0, static_cast<GrlCompare>(7));
        grlib::CGLibColorCtl::setBlendOffControl(static_cast<GrlLogicType>(3));
        m_pDrInfo->m_pCapture->setRenderTarget();
        pScreen->RenderCapScreen(m_pDrInfo, m_pDrInfo->m_pTarget->m_pTexture, m_pDrInfo->m_pDepthColor->m_pTexture);
        *m_pDrInfo->m_pCaptured = true;
        grlib::CGLibColorCtl::setBlendControl(static_cast<GrlBlendFunc>(5), static_cast<GrlBlendFunc>(6),
                                              static_cast<GrlBlendCombine>(1), static_cast<GrlLogicType>(3));
        m_blendState = 0;
    }
}

}}  // namespace ptlib::renderer
