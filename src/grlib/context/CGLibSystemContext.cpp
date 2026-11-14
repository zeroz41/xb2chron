// grlib's own file: PtrSingleton's assertion cites grlib's path to singleton.h
#define MM_LIB_FROM_GRLIB
#include "grlib/CGLibMemHandle.h"
#include "classes/grlib/CGLibManager.h"
#include "nvn/nvn.h"
#include "nvn/nvn_FuncPtrInline.h"
#include "grlib/GrlTypes.h"
#include "grlib/CGLibShader.h"
#include "grlib/CGLibVtxFetch.h"
#include "grlib/CGLibDecShader.h"
#include "grlib/CGLibRenderTarget.h"
#include "grlib/CGLibPipeline.h"
#include "grlib/CGLibState.h"
#include "grlib/CGLibCtl.h"
#include "classes/grlib/context/CGLibSystemContext.h"
#include "grlib/CGLibVtxVertex.h"
#include "grlib/CGLibVtxOneInstans.h"
#include "grlib/CGLibVtxInstans.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibVtxStmOut.h"
#include "grlib/CGLibOneUniformBlock.h"
#include "mm/Col4.h"
#include "mtl/AllocHandle.h"
#include "mtl/MemManager.h"
#include "grlib/CGLibMemPoolAdder.h"
#include "grlib/CGLibDisplay.h"
#include <string.h>

namespace {
// GrlCompare to NVN's depth functions (NEVER 1 .. ALWAYS 8). Proposed name, not the original's: a file-local
// table the linker merged with other units' copies (lbl_71009B7BA8).
const NVNdepthFunc s_depthFuncTbl[] = {
    (NVNdepthFunc)1, (NVNdepthFunc)2, (NVNdepthFunc)3, (NVNdepthFunc)4,
    (NVNdepthFunc)5, (NVNdepthFunc)6, (NVNdepthFunc)7, (NVNdepthFunc)8,
};
}  // namespace

namespace grlib { namespace context {

unsigned int CGLibSystemContext::s_nvReportCounterSize;
unsigned int CGLibSystemContext::s_nvTextureSize;
unsigned int CGLibSystemContext::s_nvSamplerSize;
int CGLibSystemContext::s_nNnumReservedTextures;
int CGLibSystemContext::s_nNumReservedSamplers;
unsigned int CGLibSystemContext::s_nLinerTextureStride;

const ml::CriticalSection& CGLibSystemContext::getCriticalSection() {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71015E92B0, its guard lbl_71015E92D8)
    static ml::CriticalSection s_cs;
    return s_cs;
}

CGLibSystemContext::CGLibSystemContext() : pad_2448(0), pad_2450(0), m_isSetup(false) {}

CGLibSystemContext::~CGLibSystemContext() {}

}}  // namespace grlib::context

namespace grlib {

void CGLibDisplay::setup(NVNdevice* device) {
    m_init = true;
    nvnSyncInitialize(&m_sync, device);
    nvnSyncInitialize(&m_sync2, device);
    nvnWindowBuilderSetDefaults(&m_windowBuilder);
    nvnWindowBuilderSetDevice(&m_windowBuilder, device);
    nvnWindowBuilderSetNativeWindow(&m_windowBuilder, CGLibManager::sys()->m_vi.m_nativeWindow);
    NVNtextureBuilder builder;
    nvnTextureBuilderSetDevice(&builder, device);
    nvnTextureBuilderSetDefaults(&builder);
    nvnTextureBuilderSetTarget(&builder, NVN_TEXTURE_TARGET_2D);
    nvnTextureBuilderSetFormat(&builder, (NVNformat)0x25);
    nvnTextureBuilderSetSize2D(&builder, 1280, 720);
    m_storageSize[0] = nvnTextureBuilderGetStorageSize(&builder);
    m_storageAlign[0] = nvnTextureBuilderGetStorageAlignment(&builder);
    nvnTextureBuilderSetDevice(&builder, device);
    nvnTextureBuilderSetDefaults(&builder);
    nvnTextureBuilderSetTarget(&builder, NVN_TEXTURE_TARGET_2D);
    nvnTextureBuilderSetFormat(&builder, (NVNformat)0x35);
    nvnTextureBuilderSetSize2D(&builder, 1280, 720);
    m_storageSize[1] = nvnTextureBuilderGetStorageSize(&builder);
    m_storageAlign[1] = nvnTextureBuilderGetStorageAlignment(&builder);
    resize(1280, 720);
}

}  // namespace grlib

namespace grlib { namespace context {

bool CGLibSystemContext::cleanup() {
    if (m_isSetup) {
        m_utilObj.release();
        for (int i = 0; i < 2; i++) {
            m_cmdBuffers[i].release();
            m_subCmdBuffers[i].release();
        }
        m_gpuTimeStamp.release();
        m_samplerTbl.release();
        m_texDescriptor.release();
        m_samplerDescriptor.release();
        m_occlusion.release();
        m_textureAlloc.release();
        m_memPoolAdder.release();
        if (m_pPixelResArea != nullptr) {
            mtl::MemManager::deallocate(m_pPixelResArea, 0, false);
            m_pPixelResArea = nullptr;
        }
        for (int i = 0; i < 2; i++) {
            if (m_pPixelResAreaPrev[i] != nullptr) {
                mtl::MemManager::deallocate(m_pPixelResAreaPrev[i], 0, false);
                m_pPixelResAreaPrev[i] = nullptr;
            }
        }
        m_releaseTbl.release();
        for (int i = 0; i < 5; i++) {
            m_etcBuffer[i].release();
        }
        m_memPoolList0.release();
        m_memPoolList1.release();
        m_display.release();
        m_reportPool.release();
        m_pixelPool.release();
        m_extraPool0.release();
        m_extraPool1.release();
        m_memPoolTbl.release();
        m_isSetup = false;
    }
    return true;
}

bool CGLibSystemContext::isRelease() {
    return true;
}

}}  // namespace grlib::context

namespace grlib {
using context::CGLibSystemContext;

void CGLibState::setMainFrameBuffer() {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_display.m_renderTargets[ctx->m_display.m_index].setRenderTarget(*ctx->m_display.m_depthTarget.m_pDepthBuffer);
}

}  // namespace grlib

namespace grlib { namespace context {

void CGLibSystemContext::end() {
    m_gpuTimeStamp.end();
    m_subCmdBuffers[CGLibManager::s_nDblNowIdx].end();
    m_subCmdBuffers[CGLibManager::s_nDblNowIdx].call();
    m_cmdBuffers[CGLibManager::s_nDblNowIdx].end();
    m_pipeline.m_pCmdBuf = nullptr;
    m_pCmdBuf = nullptr;
    m_display.m_signaled = false;
}

void CGLibSystemContext::getUniformoGpuAddress(unsigned long& address, const CGLibMemType& mem) {
    if (mem.m_type == 6) {
        address = (static_cast<unsigned char*>(mem.m_pMem) - static_cast<unsigned char*>(m_extraPool1.m_pBuffer)) +
                  nvnMemoryPoolGetBufferAddress(m_extraPool1.m_pPool);
    } else {
        CGLibMemPool& etc = m_etcBuffer[mem.m_type].m_pool;
        address = (static_cast<unsigned char*>(mem.m_pMem) - static_cast<unsigned char*>(etc.m_pBuffer)) +
                  nvnMemoryPoolGetBufferAddress(etc.m_pPool);
    }
}

void CGLibSystemContext::getVertexGpuAddress(unsigned long& address, const CGLibMemType& mem) {
    if (mem.m_type == 6) {
        address = (static_cast<unsigned char*>(mem.m_pMem) - static_cast<unsigned char*>(m_extraPool0.m_pBuffer)) +
                  nvnMemoryPoolGetBufferAddress(m_extraPool0.m_pPool);
    } else {
        CGLibMemPool& etc = m_etcBuffer[mem.m_type].m_pool;
        address = (static_cast<unsigned char*>(mem.m_pMem) - static_cast<unsigned char*>(etc.m_pBuffer)) +
                  nvnMemoryPoolGetBufferAddress(etc.m_pPool);
    }
}

void CGLibSystemContext::getGlbUniformParam(unsigned char*& buffer, unsigned long& gpuAddress) {
    buffer = m_pGlbUniformBuffer + m_glbUniformOffset;
    gpuAddress = m_glbUniformGpuAddress + m_glbUniformOffset;
}

void CGLibSystemContext::nextGlbUniformOfs(unsigned int size) {
    unsigned int alignedSize = size + (-size & 0xFF);
    m_glbUniformOffset += alignedSize;
    m_glbUniformRest -= alignedSize;
}

unsigned int CGLibSystemContext::getPixelResAreaOffset(unsigned int offset) {
    return m_pixelResAreaOffset + offset;
}

void CGLibSystemContext::releaseDelayMempool(NVNmemoryPool* pool, void* buffer) {
    ml::CS lock(getCriticalSection());
    CGLibReleaseObj* obj = m_releaseTbl.createObj();
    obj->m_work.m_use = 1;
    obj->m_work.m_mempool = 1;
    obj->m_work.m_texture = 0;
    obj->m_work.m_pad = 0;
    obj->m_work.m_type = 0;
    obj->m_work.m_res.m_obj.m_pObj = pool;
    obj->m_work.m_res.m_obj.m_pBuff = buffer;
}

void CGLibSystemContext::releaseDelayTexture(NVNtexture* texture, void* mem, int textureId, int samplerId) {
    ml::CS lock(getCriticalSection());
    CGLibReleaseObj* obj = m_releaseTbl.createObj();
    obj->m_work.m_use = 1;
    obj->m_work.m_mempool = 0;
    obj->m_work.m_texture = 0;
    obj->m_work.m_pad = 0;
    obj->m_work.m_type = 1;
    if (texture != nullptr) {
        obj->m_work.m_texture = 1;
        obj->m_work.m_res.m_obj.m_pObj = texture;
    }
    obj->m_work.m_res.m_obj.m_pBuff = mem;
    obj->m_work.m_textureID = textureId;
    obj->m_work.m_samplerID = samplerId;
}

void CGLibSystemContext::releaseDelaySampler(CGLibBuffResSamObj* sampler) {
    ml::CS lock(getCriticalSection());
    CGLibReleaseObj* obj = m_releaseTbl.createObj();
    obj->m_work.m_res.m_obj.m_pObj = sampler;
    obj->m_work.m_use = 1;
    obj->m_work.m_mempool = 0;
    obj->m_work.m_texture = 0;
    obj->m_work.m_pad = 0;
    obj->m_work.m_type = 2;
}

void CGLibSystemContext::releaseDelayVertex(CGLibMemType& mem) {
    if (mem.m_type != 5) {
        ml::CS lock(getCriticalSection());
        CGLibReleaseObj* obj = m_releaseTbl.createObj();
        // a copy of the whole block, its padding too (an assignment copies 12 bytes)
        memcpy(&obj->m_work.m_res.m_mem, &mem, sizeof(CGLibMemType));
        obj->m_work.m_use = 1;
        obj->m_work.m_mempool = 0;
        obj->m_work.m_texture = 0;
        obj->m_work.m_pad = 0;
        obj->m_work.m_type = 3;
    }
    mem.m_pMem = nullptr;
    mem.m_type = 5;
}

}}  // namespace grlib::context

namespace grlib {

void CGLibState::setViewport(const LibMainStateViewPort& viewport) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    nvnCommandBufferSetViewport(ctx->m_pipeline.m_pCmdBuf, viewport.x, viewport.y, viewport.width, viewport.height);
    nvnCommandBufferSetScissor(ctx->m_pipeline.m_pCmdBuf, viewport.x, viewport.y, viewport.width, viewport.height);
    ctx->m_viewport = viewport;
}

void CGLibState::setOnlyViewport(const LibMainStateViewPort& viewport) {
    nvnCommandBufferSetViewport(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf, viewport.x, viewport.y,
                                viewport.width, viewport.height);
}

void CGLibState::setOnlyScissor(const LibMainStateViewPort& viewport) {
    nvnCommandBufferSetScissor(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf, viewport.x, viewport.y,
                               viewport.width, viewport.height);
}

void CGLibState::beginRegisterRenderTarget() {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_renderTargetNum = 0;
    ctx->m_pDepthTarget = nullptr;
}

void CGLibState::setRegisterRenderTarget(CGLibColorBuffer& buffer, GrlMrtType mrt) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_renderTargetViews[mrt] = &buffer.m_view;
    ctx->m_renderTargets[mrt] = buffer.m_pNvnTexture;
    ctx->m_renderTargetNum++;
}

void CGLibState::setRegisterRenderTarget(CGLibRenderTarget& target, GrlMrtType mrt) {
    setRegisterRenderTarget(target.m_colorBuffer, mrt);
}

void CGLibState::setRegisterDepthTarget(CGLibDepthBuffer& buffer) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_pDepthTarget = buffer.m_pNvnTexture;
}

void CGLibState::endRegisterRenderTarget() {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    nvnCommandBufferSetRenderTargets(ctx->m_pipeline.m_pCmdBuf, ctx->m_renderTargetNum, ctx->m_renderTargets,
                                     ctx->m_renderTargetViews, ctx->m_pDepthTarget, nullptr);
}

CGLibRenderTarget* CGLibState::getMainRenderTarget() {
    return &CGLibSystemContext::get()->m_display.m_renderTargets[CGLibSystemContext::get()->m_display.m_index];
}

void CGLibState::setPixelResidentArea(bool enable, unsigned int size) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_pPixelResAreaPrev[CGLibManager::s_nStkNowIdx] = ctx->m_pPixelResArea;
    ctx->m_pPixelResArea = nullptr;
    ctx->m_pixelResAreaSize = size;
    if (enable) {
        ctx->m_pPixelResArea = mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, 0x10000, false, "no name", 0);
        ctx->m_pixelResAreaOffset = (unsigned char*)ctx->m_pPixelResArea - static_cast<unsigned char*>(ctx->m_pixelPool.m_pBuffer);
        ctx->m_pixelResAreaGpuAddress = nvnMemoryPoolGetBufferAddress(ctx->m_pixelPool.m_pPool) + ctx->m_pixelResAreaOffset;
    }
}

void CGLibColorCtl::setBlendControl(GrlBlendFunc src, GrlBlendFunc dst, GrlBlendCombine combine, GrlLogicType logic) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    nvnColorStateSetLogicOp(&ctx->m_pipeline.m_blendOnColorState, (NVNlogicOp)logic);
    nvnCommandBufferBindColorState(ctx->m_pipeline.m_pCmdBuf, &ctx->m_pipeline.m_blendOnColorState);
    NVNblendState* blend = &ctx->m_pipeline.m_blendState;
    nvnBlendStateSetBlendEquation(blend, (NVNblendEquation)combine, (NVNblendEquation)combine);
    nvnBlendStateSetBlendFunc(blend, (NVNblendFunc)src, (NVNblendFunc)dst, (NVNblendFunc)src, (NVNblendFunc)dst);
    for (int i = 0; i < 8; i++) {
        nvnBlendStateSetBlendTarget(blend, i);
        nvnCommandBufferBindBlendState(ctx->m_pipeline.m_pCmdBuf, blend);
    }
}

void CGLibColorCtl::setBlendControl(GrlBlendFunc colorSrc, GrlBlendFunc colorDst, GrlBlendCombine colorCombine,
                                    GrlBlendFunc alphaSrc, GrlBlendFunc alphaDst, GrlBlendCombine alphaCombine,
                                    GrlLogicType logic) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    nvnColorStateSetLogicOp(&ctx->m_pipeline.m_blendOnColorState, (NVNlogicOp)logic);
    nvnCommandBufferBindColorState(ctx->m_pipeline.m_pCmdBuf, &ctx->m_pipeline.m_blendOnColorState);
    NVNblendState* blend = &ctx->m_pipeline.m_blendState;
    nvnBlendStateSetBlendEquation(blend, (NVNblendEquation)colorCombine, (NVNblendEquation)alphaCombine);
    nvnBlendStateSetBlendFunc(blend, (NVNblendFunc)colorSrc, (NVNblendFunc)colorDst, (NVNblendFunc)alphaSrc,
                              (NVNblendFunc)alphaDst);
    for (int i = 0; i < 8; i++) {
        nvnBlendStateSetBlendTarget(blend, i);
        nvnCommandBufferBindBlendState(ctx->m_pipeline.m_pCmdBuf, blend);
    }
}

void CGLibColorCtl::setBlendOffControl(GrlLogicType logic) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNcolorState* color = &ctx->m_pipeline.m_blendOffColorState;
    nvnColorStateSetLogicOp(color, (NVNlogicOp)logic);
    nvnCommandBufferBindColorState(ctx->m_pipeline.m_pCmdBuf, color);
}

void CGLibColorCtl::setMrtBlend(unsigned char mask, GrlLogicType logic) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNcolorState* color = &ctx->m_pipeline.m_mrtColorState;
    for (int i = 0; i < 8; i++) {
        if (mask & (1 << i)) {
            nvnColorStateSetBlendEnable(color, i, true);
        } else {
            nvnColorStateSetBlendEnable(color, i, false);
        }
    }
    nvnColorStateSetLogicOp(color, (NVNlogicOp)logic);
    nvnCommandBufferBindColorState(ctx->m_pipeline.m_pCmdBuf, color);
}

void CGLibColorCtl::setMrtBlendControl(GrlMrtType mrt, GrlBlendFunc src, GrlBlendFunc dst, GrlBlendCombine combine) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNblendState* blend = &ctx->m_pipeline.m_blendState;
    nvnBlendStateSetBlendTarget(blend, mrt);
    nvnBlendStateSetBlendEquation(blend, (NVNblendEquation)combine, (NVNblendEquation)combine);
    nvnBlendStateSetBlendFunc(blend, (NVNblendFunc)src, (NVNblendFunc)dst, (NVNblendFunc)src, (NVNblendFunc)dst);
    nvnCommandBufferBindBlendState(ctx->m_pipeline.m_pCmdBuf, blend);
}

void CGLibColorCtl::setMrtBlendControl(GrlMrtType mrt, GrlBlendFunc colorSrc, GrlBlendFunc colorDst,
                                       GrlBlendCombine colorCombine, GrlBlendFunc alphaSrc, GrlBlendFunc alphaDst,
                                       GrlBlendCombine alphaCombine) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNblendState* blend = &ctx->m_pipeline.m_blendState;
    nvnBlendStateSetBlendTarget(blend, mrt);
    nvnBlendStateSetBlendEquation(blend, (NVNblendEquation)colorCombine, (NVNblendEquation)alphaCombine);
    nvnBlendStateSetBlendFunc(blend, (NVNblendFunc)colorSrc, (NVNblendFunc)colorDst, (NVNblendFunc)alphaSrc,
                              (NVNblendFunc)alphaDst);
    nvnCommandBufferBindBlendState(ctx->m_pipeline.m_pCmdBuf, blend);
}

void CGLibColorCtl::setColorBufferOn() {
    nvnCommandBufferBindChannelMaskState(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf,
                                         &CGLibSystemContext::get()->m_pipeline.m_channelMaskOn);
}

void CGLibColorCtl::setColorBufferOff() {
    nvnCommandBufferBindChannelMaskState(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf,
                                         &CGLibSystemContext::get()->m_pipeline.m_channelMaskOff);
}

void CGLibColorCtl::setColorChannelMask(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNchannelMaskState* mask = &ctx->m_pipeline.m_channelMask;
    for (int i = 0; i < 8; i++) {
        nvnChannelMaskStateSetChannelMask(mask, i, r, g, b, a);
    }
    nvnCommandBufferBindChannelMaskState(ctx->m_pipeline.m_pCmdBuf, mask);
}

void CGLibColorCtl::setColorChannelMask(GrlMrtType mrt, unsigned char r, unsigned char g, unsigned char b,
                                        unsigned char a) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNchannelMaskState* mask = &ctx->m_pipeline.m_channelMask;
    nvnChannelMaskStateSetChannelMask(mask, mrt, r, g, b, a);
    nvnCommandBufferBindChannelMaskState(ctx->m_pipeline.m_pCmdBuf, mask);
}

void CGLibColorCtl::clearMainFrameBuffer(const mm::Col4& color) {
    // all four channels
    CGLibState::getMainRenderTarget()->clearTexture(color, (GrlClaerMask)0xF);
}

void CGLibPolygon::setCullingOff() {
    nvnCommandBufferBindPolygonState(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf,
                                     &CGLibSystemContext::get()->m_pipeline.m_polygonCullOff);
}

void CGLibPolygon::setCullingFront() {
    nvnCommandBufferBindPolygonState(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf,
                                     &CGLibSystemContext::get()->m_pipeline.m_polygonCullFront);
}

void CGLibPolygon::setCullingBack() {
    nvnCommandBufferBindPolygonState(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf,
                                     &CGLibSystemContext::get()->m_pipeline.m_polygonCullBack);
}

void CGLibPolygon::setCullingDispOff() {
    nvnCommandBufferBindPolygonState(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf,
                                     &CGLibSystemContext::get()->m_pipeline.m_polygonDispOff);
}

void CGLibPolygon::setLineWidth(float width) {
    nvnCommandBufferSetLineWidth(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf, width);
}

void CGLibPolygon::setRasterizer(unsigned char discard) {
    nvnCommandBufferSetRasterizerDiscard(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf, discard);
}

void CGLibDepthCtl::setDepthControl(unsigned char test, unsigned char write, GrlCompare compare) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNdepthStencilState* depth = &ctx->m_pipeline.m_depthStencilState;
    nvnDepthStencilStateSetDepthTestEnable(depth, test);
    nvnDepthStencilStateSetDepthFunc(depth, s_depthFuncTbl[compare]);
    nvnDepthStencilStateSetDepthWriteEnable(depth, write);
    nvnDepthStencilStateSetStencilTestEnable(depth, false);
    nvnCommandBufferBindDepthStencilState(ctx->m_pipeline.m_pCmdBuf, depth);
}

void CGLibDepthCtl::setDepthStencilControl(unsigned char depthTest, unsigned char depthWrite, GrlCompare depthCompare,
                                           unsigned char stencilTest, GrlCompare stencilCompare, unsigned int ref,
                                           unsigned int mask, unsigned int writeMask, GrlStencil pass,
                                           GrlStencil depthFail, GrlStencil fail) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    if (stencilTest) {
        // both faces (NVN_FACE_FRONT_AND_BACK)
        nvnCommandBufferSetStencilRef(ctx->m_pipeline.m_pCmdBuf, (NVNface)3, ref);
        nvnCommandBufferSetStencilValueMask(ctx->m_pipeline.m_pCmdBuf, (NVNface)3, mask);
        nvnCommandBufferSetStencilMask(ctx->m_pipeline.m_pCmdBuf, (NVNface)3, writeMask);
        nvnDepthStencilStateSetStencilTestEnable(&ctx->m_pipeline.m_depthStencilState, true);
        nvnDepthStencilStateSetStencilOp(&ctx->m_pipeline.m_depthStencilState, (NVNface)3, (NVNstencilOp)fail, (NVNstencilOp)depthFail,
                                         (NVNstencilOp)pass);
        nvnDepthStencilStateSetStencilFunc(&ctx->m_pipeline.m_depthStencilState, (NVNface)3, (NVNstencilFunc)s_depthFuncTbl[stencilCompare]);
    } else {
        nvnDepthStencilStateSetStencilTestEnable(&ctx->m_pipeline.m_depthStencilState, false);
    }
    nvnDepthStencilStateSetDepthTestEnable(&ctx->m_pipeline.m_depthStencilState, depthTest);
    nvnDepthStencilStateSetDepthFunc(&ctx->m_pipeline.m_depthStencilState, s_depthFuncTbl[depthCompare]);
    nvnDepthStencilStateSetDepthWriteEnable(&ctx->m_pipeline.m_depthStencilState, depthWrite);
    nvnCommandBufferBindDepthStencilState(ctx->m_pipeline.m_pCmdBuf, &ctx->m_pipeline.m_depthStencilState);
}

void CGLibDepthCtl::clearColorBuffer(CGLibColorBuffer& buffer, const mm::Col4& color, GrlClaerMask mask) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    const NVNtextureView* view = &buffer.m_view;
    nvnCommandBufferSetViewport(ctx->m_pipeline.m_pCmdBuf, 0, 0, buffer.getWidth(), buffer.getHeight());
    nvnCommandBufferSetScissor(ctx->m_pipeline.m_pCmdBuf, 0, 0, buffer.getWidth(), buffer.getHeight());
    nvnCommandBufferSetRenderTargets(ctx->m_pipeline.m_pCmdBuf, 1, &buffer.m_pNvnTexture, &view, nullptr, nullptr);
    nvnCommandBufferClearColor(ctx->m_pipeline.m_pCmdBuf, 0, &color.r, mask);
    nvnCommandBufferSetRenderTargets(ctx->m_pipeline.m_pCmdBuf, ctx->m_renderTargetNum, ctx->m_renderTargets,
                                     ctx->m_renderTargetViews, ctx->m_pDepthTarget, nullptr);
    nvnCommandBufferSetViewport(ctx->m_pipeline.m_pCmdBuf, 0, 0, ctx->m_viewport.width, ctx->m_viewport.height);
    nvnCommandBufferSetScissor(ctx->m_pipeline.m_pCmdBuf, 0, 0, ctx->m_viewport.width, ctx->m_viewport.height);
}

void CGLibDepthCtl::clearIntColorBuffer(CGLibColorBuffer& buffer, const int* values, GrlClaerMask mask) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    const NVNtextureView* view = &buffer.m_view;
    nvnCommandBufferSetViewport(ctx->m_pipeline.m_pCmdBuf, 0, 0, buffer.getWidth(), buffer.getHeight());
    nvnCommandBufferSetScissor(ctx->m_pipeline.m_pCmdBuf, 0, 0, buffer.getWidth(), buffer.getHeight());
    nvnCommandBufferSetRenderTargets(ctx->m_pipeline.m_pCmdBuf, 1, &buffer.m_pNvnTexture, &view, nullptr, nullptr);
    nvnCommandBufferClearColori(ctx->m_pipeline.m_pCmdBuf, 0, values, mask);
    nvnCommandBufferSetRenderTargets(ctx->m_pipeline.m_pCmdBuf, ctx->m_renderTargetNum, ctx->m_renderTargets,
                                     ctx->m_renderTargetViews, ctx->m_pDepthTarget, nullptr);
    nvnCommandBufferSetViewport(ctx->m_pipeline.m_pCmdBuf, 0, 0, ctx->m_viewport.width, ctx->m_viewport.height);
    nvnCommandBufferSetScissor(ctx->m_pipeline.m_pCmdBuf, 0, 0, ctx->m_viewport.width, ctx->m_viewport.height);
}

// stencilOnly (the name is not the original's): the depth is left as it is
void CGLibDepthCtl::clearDepthBuffer(CGLibDepthBuffer& buffer, bool stencilOnly) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    nvnCommandBufferSetViewport(ctx->m_pipeline.m_pCmdBuf, 0, 0, buffer.getWidth(), buffer.getHeight());
    nvnCommandBufferSetScissor(ctx->m_pipeline.m_pCmdBuf, 0, 0, buffer.getWidth(), buffer.getHeight());
    nvnCommandBufferSetRenderTargets(ctx->m_pipeline.m_pCmdBuf, 0, nullptr, nullptr, buffer.m_pNvnTexture, nullptr);
    if (stencilOnly) {
        nvnCommandBufferClearDepthStencil(ctx->m_pipeline.m_pCmdBuf, 1.0f, false, 0, 0xFFFF);
    } else {
        nvnCommandBufferClearDepthStencil(ctx->m_pipeline.m_pCmdBuf, 1.0f, true, 0, 0xFFFF);
    }
    nvnCommandBufferSetRenderTargets(ctx->m_pipeline.m_pCmdBuf, ctx->m_renderTargetNum, ctx->m_renderTargets,
                                     ctx->m_renderTargetViews, ctx->m_pDepthTarget, nullptr);
    nvnCommandBufferSetViewport(ctx->m_pipeline.m_pCmdBuf, 0, 0, ctx->m_viewport.width, ctx->m_viewport.height);
    nvnCommandBufferSetScissor(ctx->m_pipeline.m_pCmdBuf, 0, 0, ctx->m_viewport.width, ctx->m_viewport.height);
}

void CGLibCtlVertex::setVertex(CGLibVtxVertex& vertex) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    nvnVertexStreamStateSetStride(&ctx->m_pipeline.m_vertexStreams[0], vertex.m_stride);
    nvnVertexStreamStateSetDivisor(&ctx->m_pipeline.m_vertexStreams[0], 0);
    ctx->m_pipeline.m_lastVertexStream = 0;
    ctx->m_pipeline.m_vertexStreamDirty = true;
    nvnCommandBufferBindVertexBuffer(ctx->m_pipeline.m_pCmdBuf, 0, vertex.m_gpuAddress, vertex.m_size);
}

void CGLibCtlVertex::setVertex(CGLibVtxVertex& vertex, unsigned int offset) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    nvnVertexStreamStateSetStride(&ctx->m_pipeline.m_vertexStreams[0], vertex.m_stride);
    nvnVertexStreamStateSetDivisor(&ctx->m_pipeline.m_vertexStreams[0], 0);
    ctx->m_pipeline.m_lastVertexStream = 0;
    ctx->m_pipeline.m_vertexStreamDirty = true;
    nvnCommandBufferBindVertexBuffer(ctx->m_pipeline.m_pCmdBuf, 0, vertex.m_gpuAddress + offset, vertex.m_size);
}

void CGLibCtlVertex::setAddVertex(CGLibVtxVertex& vertex, int offset, int slot, unsigned int divisor) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNvertexStreamState* stream = &ctx->m_pipeline.m_vertexStreams[slot];
    nvnVertexStreamStateSetStride(stream, vertex.m_stride);
    nvnVertexStreamStateSetDivisor(stream, divisor);
    ctx->m_pipeline.m_lastVertexStream = slot;
    ctx->m_pipeline.m_vertexStreamDirty = true;
    nvnCommandBufferBindVertexBuffer(ctx->m_pipeline.m_pCmdBuf, slot, vertex.m_gpuAddress + offset, vertex.m_size);
}

void CGLibCtlVertex::setUniformVertex(CGLibOneUniformBlock& block, int stride, int offset, int slot,
                                      unsigned int divisor) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNvertexStreamState* stream = &ctx->m_pipeline.m_vertexStreams[slot];
    nvnVertexStreamStateSetStride(stream, stride);
    nvnVertexStreamStateSetDivisor(stream, divisor);
    ctx->m_pipeline.m_lastVertexStream = slot;
    ctx->m_pipeline.m_vertexStreamDirty = true;
    nvnCommandBufferBindVertexBuffer(ctx->m_pipeline.m_pCmdBuf, slot, block.m_gpuAddress + offset, block.m_size);
}

void CGLibCtlVertex::setUniformVertex(CGLibDblUniformBlock& block, int stride, int offset, int slot,
                                      unsigned int divisor) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNvertexStreamState* stream = &ctx->m_pipeline.m_vertexStreams[slot];
    nvnVertexStreamStateSetStride(stream, stride);
    nvnVertexStreamStateSetDivisor(stream, divisor);
    ctx->m_pipeline.m_lastVertexStream = slot;
    ctx->m_pipeline.m_vertexStreamDirty = true;
    nvnCommandBufferBindVertexBuffer(ctx->m_pipeline.m_pCmdBuf, slot, block.getGPUAdress() + offset, block.m_size);
}

void CGLibCtlVertex::setInstanceVertex(CGLibVtxInstans& vertex, int stride, int offset, int slot,
                                       unsigned int divisor) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNvertexStreamState* stream = &ctx->m_pipeline.m_vertexStreams[slot];
    nvnVertexStreamStateSetStride(stream, stride);
    nvnVertexStreamStateSetDivisor(stream, divisor);
    ctx->m_pipeline.m_lastVertexStream = slot;
    ctx->m_pipeline.m_vertexStreamDirty = true;
    nvnCommandBufferBindVertexBuffer(ctx->m_pipeline.m_pCmdBuf, slot, vertex.getGPUAdress() + offset, vertex.m_offset);
}

void CGLibCtlVertex::setInstanceVertex(CGLibVtxOneInstans& vertex, int stride, int offset, int slot,
                                       unsigned int divisor) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNvertexStreamState* stream = &ctx->m_pipeline.m_vertexStreams[slot];
    nvnVertexStreamStateSetStride(stream, stride);
    nvnVertexStreamStateSetDivisor(stream, divisor);
    ctx->m_pipeline.m_lastVertexStream = slot;
    ctx->m_pipeline.m_vertexStreamDirty = true;
    nvnCommandBufferBindVertexBuffer(ctx->m_pipeline.m_pCmdBuf, slot, vertex.m_gpuAddress + offset, vertex.m_offset);
}

void CGLibCtlVertex::setStreamOutVertex(CGLibVtxStmOut& vertex, int stride, int offset, int slot,
                                        unsigned int divisor) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    NVNvertexStreamState* stream = &ctx->m_pipeline.m_vertexStreams[slot];
    nvnVertexStreamStateSetStride(stream, stride);
    nvnVertexStreamStateSetDivisor(stream, divisor);
    ctx->m_pipeline.m_lastVertexStream = slot;
    ctx->m_pipeline.m_vertexStreamDirty = true;
    nvnCommandBufferBindVertexBuffer(ctx->m_pipeline.m_pCmdBuf, slot, vertex.m_gpuAddress + offset, vertex.getSize());
}

void CGLibCtlVertex::renderVertex(GrlPrimitiveType type, int count) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_pipeline.updateVertex();
    nvnCommandBufferDrawArrays(ctx->m_pipeline.m_pCmdBuf, (NVNdrawPrimitive)type, 0, count);
}

void CGLibPipeline::updateVertex() {
    if (m_vertexStreamDirty) {
        nvnCommandBufferBindVertexStreamState(m_pCmdBuf, m_lastVertexStream + 1, m_vertexStreams);
        m_vertexStreamDirty = false;
    }
}

void CGLibCtlVertex::renderInstanceVertex(GrlPrimitiveType type, int count, int instances) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_pipeline.updateVertex();
    nvnCommandBufferDrawArraysInstanced(ctx->m_pipeline.m_pCmdBuf, (NVNdrawPrimitive)type, 0, count, 0, instances);
}

void CGLibCtlTexture::setTexture(const CGLibTextureBuffer& texture, const CGLibSampler& sampler,
                                 unsigned int location) {
    if (location != 0xFFFFFFFF) {
        CGLibSystemContext* ctx = CGLibSystemContext::get();
        int textureId = ctx->m_texDescriptor.setTexture(texture);
        int samplerId = ctx->m_samplerDescriptor.setSampler(sampler);
        NVNtextureHandle handle = nvnDeviceGetTextureHandle(&CGLibManager::sys()->m_device, textureId, samplerId);
        ctx->m_pipeline.m_pShader->setTextureHandle(location, ctx->m_pipeline.m_pCmdBuf, handle);
    }
}

void CGLibCtlTexture::setUAVTexture(const CGLibTextureBuffer& texture, unsigned int location, unsigned int,
                                    unsigned int) {
    if (location != 0xFFFFFFFF) {
        CGLibSystemContext* ctx = CGLibSystemContext::get();
        int imageId = ctx->m_texDescriptor.setImage(texture);
        NVNimageHandle handle = nvnDeviceGetImageHandle(&CGLibManager::sys()->m_device, imageId);
        ctx->m_pipeline.m_pShader->setImageHandle(location, ctx->m_pipeline.m_pCmdBuf, handle);
    }
}

void CGLibCtlShader::setShader(CGLibDecShader& shader, CGLibVtxFetch& fetch) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    CGLibShader* current = &shader.getCurrentShader();
    ctx->m_pipeline.m_pShader = current;
    nvnCommandBufferBindProgram(ctx->m_pipeline.m_pCmdBuf, &current->m_program, current->m_stages);
    nvnCommandBufferBindVertexAttribState(ctx->m_pipeline.m_pCmdBuf, fetch.m_attribNum, fetch.m_pAttribs);
}

void CGLibCtlShader::setShader(CGLibDecShdExtTbl& table, CGLibVtxFetch& fetch) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    CGLibShader* current = table.m_pDecShader->m_pShaders + table.m_current;
    ctx->m_pipeline.m_pShader = current;
    nvnCommandBufferBindProgram(ctx->m_pipeline.m_pCmdBuf, &current->m_program, current->m_stages);
    nvnCommandBufferBindVertexAttribState(ctx->m_pipeline.m_pCmdBuf, fetch.m_attribNum, fetch.m_pAttribs);
}

void CGLibCtlShader::setComputeShader(CGLibDecShader& shader) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    CGLibShader* current = &shader.getCurrentShader();
    ctx->m_pipeline.m_pShader = current;
    nvnCommandBufferBindProgram(ctx->m_pipeline.m_pCmdBuf, &current->m_program, current->m_stages);
}

void CGLibCtlShader::setDispatchCompute(unsigned int x, unsigned int y, unsigned int z) {
    nvnCommandBufferDispatchCompute(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf, x, y, z);
}

void CGLibCtlShader::setMemoryBarrier() {
    // the barrier bits 1 | 8
    nvnCommandBufferBarrier(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf, 9);
}

void CGLibCtlShader::setMemoryBarrierBit(unsigned int bits) {
    nvnCommandBufferBarrier(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf, bits);
}

CGLibDecShader* CGLibCtlShader::getDecShader() {
    return &CGLibSystemContext::get()->m_utilObj.m_decShader;
}

CGLibVtxFetch* CGLibCtlShader::getVtxFetch(GrlUtilVertFetch fetch) {
    return &CGLibSystemContext::get()->m_utilObj.m_vtxFetches[fetch];
}

CGLibSampler* CGLibCtlShader::getSampler(GrlUtilSampler sampler) {
    return &CGLibSystemContext::get()->m_utilObj.m_samplers[sampler];
}

void CGLibGPUCache::setTiledCacheSize(unsigned int width, unsigned int height) {
    nvnCommandBufferSetTiledCacheTileSize(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf, width, height);
}

void CGLibGPUCache::setTiledCacheAction(GrlTiledCacheAction action) {
    nvnCommandBufferSetTiledCacheAction(CGLibSystemContext::get()->m_pipeline.m_pCmdBuf,
                                        (NVNtiledCacheAction)action);
}

void CGLibGPUCache::depthInvalidate(CGLibDepthBuffer& buffer) {
    buffer.invalidate();
}

void CGLibGPUCache::setMemPoolMemHandle(mtl::ALLOC_HANDLE handle) {
    CGLibSystemContext::get()->m_memPoolAdder.addAdder(handle);
}

void CGLibGPUCache::setMemPoolBuffer(void* buffer, unsigned int size) {
    CGLibSystemContext::get()->m_memPoolAdder.addAdder(buffer, size);
}

void CGLibGPUCache::releaseMemPoolMemHandle(mtl::ALLOC_HANDLE handle) {
    CGLibSystemContext::get()->m_memPoolAdder.releaseAdder(handle);
}

void CGLibGPUCache::releaseMemPoolBuffer(void* buffer) {
    CGLibSystemContext::get()->m_memPoolAdder.releaseAdder(buffer);
}

void CGLibDisplay::resize(unsigned int width, unsigned int height) {
    if (m_windowInit) {
        nvnWindowFinalize(&m_window);
    }
    m_windowInit = true;
    m_renderTargets[0].m_pTexture->m_flags |= 4;
    m_renderTargets[1].m_pTexture->m_flags |= 4;
    m_renderTargets[0].setTextureInfo(width, height, (GrlSurfaceFormat)0x25, false, 0);
    m_renderTargets[1].setTextureInfo(width, height, (GrlSurfaceFormat)0x25, false, 0);
    m_depthTarget.setTextureInfo(width, height, (GrlDepthFormat)0x35, false, 0);
    memset(m_renderTargets[0].m_pTexture->m_pData, 0, m_renderTargets[0].m_pTexture->m_dataSize);
    memset(m_renderTargets[1].m_pTexture->m_pData, 0, m_renderTargets[1].m_pTexture->m_dataSize);
    NVNtexture* textures[2] = {m_renderTargets[0].m_pTexture->m_pNvnTexture, m_renderTargets[1].m_pTexture->m_pNvnTexture};
    nvnWindowBuilderSetTextures(&m_windowBuilder, 2, textures);
    nvnWindowInitialize(&m_window, &m_windowBuilder);
}

void CGLibDisplay::updateSignaled() {
    m_needWait = !m_signaled;
}

void CGLibDisplay::swapChain(NVNqueue* queue) {
    if (m_needWait) {
        // NVN_WAIT_TIMEOUT_MAXIMUM
        nvnSyncWait(&m_sync, ~0UL);
    }
}

CGLibDisplay::~CGLibDisplay() {
    release();
}

}  // namespace grlib
