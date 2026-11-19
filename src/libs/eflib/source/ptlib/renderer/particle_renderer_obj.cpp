#define MM_LIB_FROM_EFLIB
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
#include "ptlib/emitter/EmitterManager.h"
#include "mm/mtl/FixedVector.h"
#include "mm/Col4.h"
#include "mm/MMStdBase.h"
#include "classes/effect/IEffectCallBack.h"
#include <algorithm>

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

void RenderGrObj::prioritySort(emitter::EmitterManager& manager, int view, FxParam&,
                               mm::mtl::FixedVector<sort::EmitterSort, 4000>& list) {
    CamParam* pCam = ParticleManager::get()->getCamParam();
    if (!ParticleManager::get()->m_initFlags[0]) {
        return;
    }
    for (emitter::EmitterObj* p = manager.m_pDrawTop[0]; p != nullptr; p = p->m_pDrawNext) {
        if (p->isRenderCheck() && p->m_viewNum == view && p->m_disp && p->m_alpha > 0.0f && p->m_pData != nullptr &&
            p->m_pData->m_shaderType != 5) {
            const mm::Mat44& viewMtx = pCam->m_viewMtx;
            sort::EmitterSort s;
            s.m_sortFirst = p->m_pData->m_sortType == 0;
            int priority = p->m_drawLayer + p->m_drawLayerOfs;
            if (priority < 0) {
                priority = 0;
            }
            if (priority > 255) {
                priority = 255;
            }
            s.m_priority = priority;
            s.m_depth = p->m_mtx.m[3][0] * viewMtx.m[0][2] + p->m_mtx.m[3][1] * viewMtx.m[1][2] +
                        p->m_mtx.m[3][2] * viewMtx.m[2][2] + viewMtx.m[3][2];
            s.m_border = false;
            s.m_pEmitter = p;
            list.push_back(s);
        }
    }
    std::stable_sort(list.begin(), list.end(), sort::Compare());
}

void RenderGrObj::draw_common_atr_wpn_tail(WpnTailShdVtxLayout* pVtx, mm::Vec3& pos, emitter::ParticleObj* pParticle,
                                           emitter::ParticleObj* pParticle2, float, unsigned int type,
                                           DrawTailWork* pWork) {
    pVtx->m_pos.x = pos.x;
    pVtx->m_pos.y = pos.y;
    pVtx->m_pos.z = pos.z;
    pVtx->m_drawIndex = pParticle->m_drawIndex;
    pVtx->m_rot = pParticle->m_rot;
    pVtx->m_drawParam = pParticle->m_drawParam;
    memcpy(pVtx->m_drawVec, pParticle->m_drawVec, sizeof(pVtx->m_drawVec));
    pVtx->m_keyVec = pParticle->m_keyVec;
    pVtx->m_size2 = 1.0f - (!pWork->m_useSizeZ ? pParticle2->m_size.y : pParticle2->m_size.z);
    switch (pWork->m_sizeType) {
    case 0:
        pVtx->m_size.x = pParticle->m_size.x;
        pVtx->m_size.y = pParticle->m_size.y;
        pVtx->m_size.z = pParticle->m_size.z;
        break;
    case 1:
        memset(&pVtx->m_size, 0, sizeof(pVtx->m_size));
        break;
    case 2:
        pVtx->m_size.x = pParticle->m_size.x;
        pVtx->m_size.y = 0.0f;
        pVtx->m_size.z = 0.0f;
        break;
    }
    pVtx->m_rgba = pParticle->m_pWork->m_rgba;
    pVtx->m_rgba2 = pParticle->m_pWork->m_rgba2;
    switch (type) {
    case 1:
    case 3:
    case 4:
    case 6: {
        float width = m_pDrInfo->m_screenWidth;
        pVtx->m_drawSize[0] = pParticle->m_pWork->m_drawSize / width;
        pVtx->m_drawSize[1] = -pParticle->m_pWork->m_drawSize / m_pDrInfo->m_screenHeight;
        break;
    }
    case 2:
    case 5:
        pVtx->m_drawSize[0] = pParticle->m_pWork->m_drawSize;
        pVtx->m_drawSize[1] = pParticle->m_pWork->m_drawSize2;
        break;
    }
}

void RenderGrObj::draw_common_atr_normal(float* pOut, emitter::ParticleObj* pParticle, float, unsigned int type, float,
                                         float) {
    pOut[0] = pParticle->m_pos.x + pParticle->m_drawOfs.x;
    pOut[1] = pParticle->m_pos.y + pParticle->m_drawOfs.y;
    pOut[2] = pParticle->m_pos.z + pParticle->m_drawOfs.z;
    reinterpret_cast<unsigned int*>(pOut)[3] = pParticle->m_drawIndex;
    pOut[4] = pParticle->m_rot.x;
    pOut[5] = pParticle->m_rot.y;
    pOut[6] = pParticle->m_rot.z + pParticle->m_drawRotOfs;
    pOut[7] = pParticle->m_drawParam;
    memcpy(&pOut[8], pParticle->m_drawVec, sizeof(pParticle->m_drawVec));
    memcpy(&pOut[12], &pParticle->m_keyVec, sizeof(mm::Vec3NA));
    pOut[15] = pParticle->m_pWork->m_drawAttr[4];
    memcpy(&pOut[16], &pParticle->m_size, sizeof(mm::Vec3NA));
    pOut[19] = pParticle->m_pWork->m_drawAttr[13];
    memcpy(&pOut[20], &pParticle->m_pWork->m_drawAttr[0], sizeof(float) * 2);
    memcpy(&pOut[22], &pParticle->m_pWork->m_drawAttr[2], sizeof(float) * 2);
    memcpy(&pOut[24], &pParticle->m_pWork->m_drawAttr[9], sizeof(float) * 2);
    memcpy(&pOut[26], &pParticle->m_pWork->m_drawAttr[11], sizeof(float) * 2);
    reinterpret_cast<unsigned int*>(pOut)[28] = pParticle->m_pWork->m_rgba;
    reinterpret_cast<unsigned int*>(pOut)[29] = pParticle->m_pWork->m_rgba2;
    switch (type) {
    case 1:
    case 9:
    case 11:
    case 12:
        pOut[30] = 0.0f;
        pOut[31] = 0.0f;
        break;
    case 4:
    case 5:
    case 7:
        pOut[30] = pParticle->m_pWork->m_drawSize;
        pOut[31] = pParticle->m_pWork->m_drawSize2;
        break;
    case 6:
    case 8:
        pOut[30] = pParticle->m_pWork->m_drawSize;
        pOut[31] = 1.0f;
        break;
    case 10:
    case 15:
        pOut[30] = 0.0f;
        pOut[31] = 0.0f;
        pOut[32] = pParticle->m_pWork->m_drawAttr2[0];
        pOut[33] = pParticle->m_pWork->m_drawAttr2[1];
        pOut[34] = pParticle->m_pWork->m_drawAttr2[2];
        pOut[35] = pParticle->m_pWork->m_drawAttr2[6];
        pOut[36] = pParticle->m_pWork->m_drawAttr2[3];
        pOut[37] = pParticle->m_pWork->m_drawAttr2[4];
        pOut[38] = pParticle->m_pWork->m_drawSize;
        pOut[39] = 1.0f;
        break;
    default:
        pOut[30] = pParticle->m_pWork->m_drawSize;
        pOut[31] = 0.0f;
        break;
    case 14:
        pOut[30] = pParticle->m_pWork->m_drawSize;
        pOut[31] = 0.0f;
        pOut[32] = pParticle->m_pWork->m_drawAttr[5];
        pOut[33] = pParticle->m_pWork->m_drawAttr[6];
        pOut[34] = pParticle->m_pWork->m_drawAttr[7];
        pOut[35] = pParticle->m_pWork->m_drawAttr[8];
        break;
    }
}

void RenderGrObj::draw_common_atr_strip(float* pOut, emitter::ParticleObj* pParticle, emitter::ParticleObj* pParticle2,
                                        float, unsigned int, DrawTailWork* pWork, mm::Vec3 vec0, mm::Vec3 vec1, float,
                                        float) {
    memcpy(pOut, &pParticle->m_pos, sizeof(mm::Vec3NA));
    reinterpret_cast<unsigned int*>(pOut)[3] = pParticle->m_drawIndex;
    if (pParticle->m_drawParam < -2.5f) {
        memcpy(&pOut[4], &vec0, sizeof(mm::Vec3NA));
        pOut[7] = pParticle->m_drawParam;
        memcpy(&pOut[8], &vec1, sizeof(mm::Vec3NA));
    } else {
        memcpy(&pOut[4], &pParticle->m_rot, sizeof(mm::Vec3NA));
        pOut[7] = pParticle->m_drawParam;
        memcpy(&pOut[8], pParticle->m_drawVec, sizeof(pParticle->m_drawVec));
    }
    memcpy(&pOut[12], &pParticle->m_keyVec, sizeof(mm::Vec3NA));
    switch (pWork->m_sizeType) {
    case 0:
        pOut[16] = pParticle->m_size.x;
        pOut[17] = pParticle->m_size.y;
        pOut[18] = pParticle->m_size.z;
        break;
    case 1:
        memset(&pOut[16], 0, sizeof(mm::Vec3NA));
        break;
    case 2:
        pOut[16] = pParticle->m_size.x;
        pOut[17] = 0.0f;
        pOut[18] = 0.0f;
        break;
    case 3:
        pOut[16] = pOut[17] = pOut[18] = pParticle->m_pWork->m_pEmParent->m_pData->m_drawDist;
        break;
    }
    if (pWork->m_useSizeZ) {
        pOut[15] = pParticle2->m_size.z;
    } else {
        pOut[15] = pParticle2->m_size.y;
    }
    pOut[19] = pWork->m_index * pParticle2->m_sizeRate;
    reinterpret_cast<unsigned int*>(pOut)[20] = pParticle->m_pWork->m_rgba;
    reinterpret_cast<unsigned int*>(pOut)[21] = pParticle->m_pWork->m_rgba2;
    pOut[22] = pParticle->m_pWork->m_drawSize / m_pDrInfo->m_screenWidth;
    pOut[23] = -pParticle->m_pWork->m_drawSize / m_pDrInfo->m_screenHeight;
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
