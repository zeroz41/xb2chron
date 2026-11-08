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
#include "classes/effect/IEffectCallBack.h"

#line 1 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/renderer/particle_renderer_obj.cpp"

namespace ptlib { namespace renderer {

void RenderGrObj::term() {
    m_backBuffer.release();
    m_shaderManager.term();
}

void RenderManager::setEmitterDraw(emitter::EmitterObj* pObj, emitter::EmitterArg* pArg) {
    // lbl_71009D5624: the blend mode of the shaders below 0x30 (the name is not the original's)
    static const int s_blendModeTbl[0x30] = {
        2, 3, 6, 2, 10, 2, 12, 2, 9, 8, 14, 2, 11, 2, 2, 1, 2, 2, 2, 2, 2, 7, 4, 2,
        13, 5, 2, 2, 15, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    };
    // lbl_71009D56E4: shaders 0x30 and 0x40's blend mode by the emitter's shader number (the name is not the original's)
    static const int s_shaderBlendTbl[0x30] = {
        6, 1, 2, 2, 6, 6, 3, 6, 4, 5, 1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 5, 1, 6,
        6, 2, 6, 6, 6, 6, 6, 6, 6, 4, 6, 4, 4, 6, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    int shader = -1;
    switch (pArg->m_type) {
    case 0:
    case 12:
        switch (pArg->m_shaderType) {
        case 5:
        case 29:
        case 30:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
            shader = 0;
            break;
        case 3:
            shader = 2;
            break;
        default:
            shader = pArg->m_shaderType;
            break;
        }
        break;
    case 1:
        shader = 0x30;
        break;
    case 2:
        shader = 0x53;
        break;
    case 4:
        shader = 0x50;
        break;
    case 5:
        shader = 0x51;
        break;
    case 9:
        shader = 0x40;
        break;
    }
    if (pArg->m_type == 13 || pArg->m_type == 14) {
        pObj->m_shaderGroup = 0;
        pObj->m_blendMode = 0;
        return;
    }
    if (shader == -1) {
        efMsg("SHADER ERROR!!!");
        return;
    }
    if (m_pGrObj != nullptr) {
        int blend = shader < 0x30 ? s_blendModeTbl[shader] : 2;
        int group = 0;
        switch (shader) {
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x54:
        case 0x55:
        case 0x56:
        case 0x57:
        case 0x58:
        case 0x59:
        case 0x5B:
        case 0x5D:
            group = 0;
            blend = -1;
            break;
        case 0x30:
            group = 1;
            blend = s_shaderBlendTbl[pArg->m_shaderType];
            break;
        case 0x31:
            group = 1;
            blend = 1;
            break;
        case 0x32:
            group = 1;
            blend = 2;
            break;
        case 0x36:
            group = 1;
            blend = 3;
            break;
        case 0x38:
            group = 1;
            blend = 4;
            break;
        case 0x39:
            group = 1;
            blend = 5;
            break;
        case 0x40:
            group = 9;
            blend = s_shaderBlendTbl[pArg->m_shaderType];
            break;
        case 0x41:
            group = 2;
            blend = 6;
            break;
        case 0x46:
            group = 2;
            blend = 3;
            break;
        case 0x48:
            group = 2;
            blend = 4;
            break;
        case 0x49:
            group = 2;
            blend = 5;
            break;
        case 0x53:
            group = 4;
            blend = 1;
            break;
        case 0x42:
            group = 2;
            blend = 2;
            break;
        }
        pObj->m_blendMode = blend;
        pObj->m_shaderGroup = group;
    }
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

bool getFramePos(mm::Vec3& pos0, mm::Vec3& pos1, float frame, effect::IEffectCallBack* pCallBack, short type) {
    unsigned int size;
    const unsigned int* pData = static_cast<const unsigned int*>(pCallBack->getBindData(size));
    if (pData != nullptr) {
        SwtPackData pack(pData, size);
        const char* pName = pCallBack->getStateName() + 2;
        SwtData swt = [&]() {
            for (unsigned int i = 0; i < pack.m_num; i++) {
                if (strstr(reinterpret_cast<const char*>(pData + 1) + i * 0x80, pName) != nullptr) {
                    return pack.getAddr(frame, i, type);
                }
            }
            return SwtData(nullptr);
        }();
        if (swt.m_pData != nullptr) {
            return calcFrame(swt, frame, pos0, pos1, type);
        }
    }
    return false;
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

SwtData SwtPackData::getAddr(float& frame, unsigned int index, short type) {
    if (index < m_num) {
        // after the names: one offset per state to its SwtData block (u32 key count, block number, block count)
        const unsigned int* pOffset = m_pData + m_num * 32 + 1;
        const unsigned int* p = reinterpret_cast<const unsigned int*>(reinterpret_cast<const char*>(m_pData) + pOffset[index]);
        unsigned int block = p[1];
        unsigned int blockNum = p[2];
        float size = calcFrameSize(p, type);
        if (size <= frame) {
            if (block + 1 >= blockNum) {
                return SwtData(nullptr);
            }
            frame -= size;
            index++;
        } else if (frame < 0.0f) {
            if (block == 0) {
                return SwtData(nullptr);
            }
            index--;
            const unsigned int* pPrev = reinterpret_cast<const unsigned int*>(reinterpret_cast<const char*>(m_pData) + pOffset[index]);
            frame = calcFrameSize(pPrev, type) + frame - 1.0f;
        }
        return SwtData(reinterpret_cast<const unsigned int*>(reinterpret_cast<const char*>(m_pData) + pOffset[index]));
    }
    return SwtData(nullptr);
}

}}  // namespace ptlib::renderer
