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
#include "ptlib/emitter/EmitterObj.h"
#include "mm/Col4.h"
#include "mm/MMStdBase.h"

#line 1 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/renderer/particle_renderer_obj.cpp"

namespace ptlib { namespace renderer {

void RenderGrObj::term() {
    m_backBuffer.release();
    m_shaderManager.term();
}

void RenderGrObj::fxcore_setup_target_update(int view) {
    if (view == 0) {
        int width = m_pDrInfo->m_pTarget->m_width;
        int height = m_pDrInfo->m_pTarget->m_height;
        if (m_backBuffer.m_pHalfDepth->m_width != width / 2 || m_backBuffer.m_pHalfDepth->m_height != height / 2) {
            m_backBuffer.resizeHalf(width, height, m_pDrInfo->m_effectBufOfs);
        }
    }
    if (m_backBuffer.m_isReleased) {
        m_backBuffer.m_pTiny->clearTexture(mm::Col4::black, static_cast<GrlClaerMask>(0xF));
        m_backBuffer.m_pTiny2->clearTexture(mm::Col4::white, static_cast<GrlClaerMask>(0xF));
        m_backBuffer.m_isReleased = false;
    }
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
    resizeHalf(width, height, offset);
}

RenderGrObj::~RenderGrObj() {
    term();
}

BackBuffer* RenderGrObj::getBackBuffer() {
    return &m_backBuffer;
}

void RenderGrObj::myGX2SetBlendControl(int mode) {
    // the blend factors and combines a mode of 0x80 and up packs (the table names are not the original's)
    static const GrlBlendFunc s_blendFunc[] = {
        static_cast<GrlBlendFunc>(1), static_cast<GrlBlendFunc>(2), static_cast<GrlBlendFunc>(3),
        static_cast<GrlBlendFunc>(4), static_cast<GrlBlendFunc>(5), static_cast<GrlBlendFunc>(6),
        static_cast<GrlBlendFunc>(7), static_cast<GrlBlendFunc>(8), static_cast<GrlBlendFunc>(9),
        static_cast<GrlBlendFunc>(10), static_cast<GrlBlendFunc>(11),
    };
    static const GrlBlendCombine s_blendCombine[] = {
        static_cast<GrlBlendCombine>(1), static_cast<GrlBlendCombine>(2), static_cast<GrlBlendCombine>(4),
        static_cast<GrlBlendCombine>(5), static_cast<GrlBlendCombine>(3),
    };
    if (mode >= 0x80) {
        GrlBlendFunc src = s_blendFunc[(mode >> 8) & 0xF];
        GrlBlendFunc dst = s_blendFunc[(mode >> 12) & 0xF];
        GrlBlendCombine combine = s_blendCombine[mode & 0xF];
        grlib::CGLibColorCtl::setBlendControl(src, dst, combine, src, dst, combine, static_cast<GrlLogicType>(3));
        return;
    }
    switch (mode) {
    case 0:
        grlib::CGLibColorCtl::setBlendOffControl(static_cast<GrlLogicType>(3));
        return;
    case 1:
    case 5:
        grlib::CGLibColorCtl::setBlendControl(static_cast<GrlBlendFunc>(5), static_cast<GrlBlendFunc>(6),
                                              static_cast<GrlBlendCombine>(1), static_cast<GrlBlendFunc>(1),
                                              static_cast<GrlBlendFunc>(6), static_cast<GrlBlendCombine>(1),
                                              static_cast<GrlLogicType>(3));
        return;
    case 2:
        grlib::CGLibColorCtl::setBlendControl(static_cast<GrlBlendFunc>(5), static_cast<GrlBlendFunc>(2),
                                              static_cast<GrlBlendCombine>(1), static_cast<GrlBlendFunc>(1),
                                              static_cast<GrlBlendFunc>(2), static_cast<GrlBlendCombine>(1),
                                              static_cast<GrlLogicType>(3));
        return;
    case 3:
        grlib::CGLibColorCtl::setBlendControl(static_cast<GrlBlendFunc>(5), static_cast<GrlBlendFunc>(2),
                                              static_cast<GrlBlendCombine>(3), static_cast<GrlBlendFunc>(1),
                                              static_cast<GrlBlendFunc>(2), static_cast<GrlBlendCombine>(3),
                                              static_cast<GrlLogicType>(3));
        return;
    case 4:
        grlib::CGLibColorCtl::setBlendControl(static_cast<GrlBlendFunc>(10), static_cast<GrlBlendFunc>(2),
                                              static_cast<GrlBlendCombine>(1), static_cast<GrlBlendFunc>(10),
                                              static_cast<GrlBlendFunc>(2), static_cast<GrlBlendCombine>(1),
                                              static_cast<GrlLogicType>(3));
        return;
    case 6:
        grlib::CGLibColorCtl::setBlendControl(static_cast<GrlBlendFunc>(5), static_cast<GrlBlendFunc>(2),
                                              static_cast<GrlBlendCombine>(1), static_cast<GrlBlendFunc>(2),
                                              static_cast<GrlBlendFunc>(2), static_cast<GrlBlendCombine>(1),
                                              static_cast<GrlLogicType>(3));
        return;
    case 7:
        grlib::CGLibColorCtl::setBlendControl(static_cast<GrlBlendFunc>(2), static_cast<GrlBlendFunc>(5),
                                              static_cast<GrlBlendCombine>(1), static_cast<GrlBlendFunc>(1),
                                              static_cast<GrlBlendFunc>(5), static_cast<GrlBlendCombine>(1),
                                              static_cast<GrlLogicType>(3));
        return;
    case 8:
        grlib::CGLibColorCtl::setBlendControl(static_cast<GrlBlendFunc>(2), static_cast<GrlBlendFunc>(5),
                                              static_cast<GrlBlendCombine>(3), static_cast<GrlBlendFunc>(1),
                                              static_cast<GrlBlendFunc>(5), static_cast<GrlBlendCombine>(3),
                                              static_cast<GrlLogicType>(3));
    default:
#line 1570
        MM_ASSERT(0);
        return;
    }
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

void RenderGrObj::setEffectRenderTarget(grlib::CGLibRenderTarget* pTarget, grlib::CGLibDepthBuffer* pDepth,
                                        grlib::CGLibRenderTarget* pTarget1, grlib::CGLibRenderTarget* pTarget2) {
    if (pTarget1 != nullptr) {
        if (pDepth != nullptr) {
            if (pTarget2 != nullptr) {
                pTarget->setRenderTarget(*pDepth, *pTarget1, *pTarget2);
            } else {
                pTarget->setRenderTarget(*pDepth, *pTarget1);
            }
        } else {
            if (pTarget2 != nullptr) {
                pTarget->setRenderTarget(*pTarget1, *pTarget2);
            } else {
                pTarget->setRenderTarget(*pTarget1);
            }
        }
    } else {
        if (pDepth != nullptr) {
            if (pTarget2 != nullptr) {
                pTarget->setRenderTarget(*pDepth, *pTarget2);
            } else {
                pTarget->setRenderTarget(*pDepth);
            }
        } else {
            if (pTarget2 != nullptr) {
                pTarget->setRenderTarget(*pTarget2);
            } else {
                pTarget->setRenderTarget();
            }
        }
    }
}

void RenderGrObj::draw_common_uconst(float* pOut, emitter::EmitterObj* pEmitter) {
    emitter::EmitterArg* pData = pEmitter->m_pData;
    if (pData != nullptr) {
        float param = pData->m_constParam;
        float depth = pData->m_drawDepth;
        if (pEmitter->m_drawLayer == 0xFF) {
            depth = -3.0f;
        }
        float value = pData->m_uconst14;
        float param2 = pData->m_constParam2;
        float fade = pEmitter->calc_fade();
        pOut[0] = m_screenParam[0];
        pOut[1] = m_screenParam[1];
        pOut[2] = m_screenParam[2];
        pOut[3] = param;
        pOut[4] = 0.0f;
        pOut[5] = 0.0f;
        pOut[6] = 0.0f;
        pOut[7] = 0.0f;
        pOut[8] = 0.0f;
        pOut[9] = 0.0f;
        pOut[10] = 0.0f;
        pOut[11] = 0.0f;
        pOut[12] = param2;
        pOut[13] = depth;
        pOut[14] = value;
        pOut[15] = fade;
    }
}

}}  // namespace ptlib::renderer
