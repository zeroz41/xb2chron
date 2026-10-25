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
#include "grlib/CGLibVtxStmOut.h"
#include "grlib/CGLibOneUniformBlock.h"
#include "mm/Col4.h"
#include "mtl/AllocHandle.h"
#include "mtl/MemManager.h"
#include "grlib/CGLibMemPoolAdder.h"
#include "grlib/CGLibDisplay.h"

namespace {
// GrlCompare to NVN's depth functions (NEVER 1 .. ALWAYS 8). Proposed name, not the original's: a file-local
// table the linker merged with other units' copies (lbl_71009B7BA8).
const NVNdepthFunc s_depthFuncTbl[] = {
    (NVNdepthFunc)1, (NVNdepthFunc)2, (NVNdepthFunc)3, (NVNdepthFunc)4,
    (NVNdepthFunc)5, (NVNdepthFunc)6, (NVNdepthFunc)7, (NVNdepthFunc)8,
};
}  // namespace

namespace grlib { namespace context {

bool CGLibSystemContext::isRelease() {
    return true;
}

}}  // namespace grlib::context

namespace grlib {
using context::CGLibSystemContext;

void CGLibState::setMainFrameBuffer() {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_mainRenderTargets[ctx->m_mainIndex].setRenderTarget(*ctx->m_pMainDepthBuffer);
}

}  // namespace grlib

namespace grlib { namespace context {

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
    return &CGLibSystemContext::get()->m_mainRenderTargets[CGLibSystemContext::get()->m_mainIndex];
}

void CGLibState::setPixelResidentArea(bool enable, unsigned int size) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_pPixelResAreaPrev[CGLibManager::s_nStkNowIdx] = ctx->m_pPixelResArea;
    ctx->m_pPixelResArea = nullptr;
    ctx->m_pixelResAreaSize = size;
    if (enable) {
        ctx->m_pPixelResArea = mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, 0x10000, false, "no name", 0);
        ctx->m_pixelResAreaOffset = (unsigned char*)ctx->m_pPixelResArea - ctx->m_pPixelPoolMem;
        ctx->m_pixelResAreaGpuAddress = nvnMemoryPoolGetBufferAddress(ctx->m_pPixelPool) + ctx->m_pixelResAreaOffset;
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
    return &CGLibSystemContext::get()->m_decShader;
}

CGLibVtxFetch* CGLibCtlShader::getVtxFetch(GrlUtilVertFetch fetch) {
    return &CGLibSystemContext::get()->m_vtxFetches[fetch];
}

CGLibSampler* CGLibCtlShader::getSampler(GrlUtilSampler sampler) {
    return &CGLibSystemContext::get()->m_samplers[sampler];
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

void CGLibDisplay::updateSignaled() {
    m_needWait = !m_signaled;
}

void CGLibDisplay::swapChain(NVNqueue* queue) {
    if (m_needWait) {
        // NVN_WAIT_TIMEOUT_MAXIMUM
        nvnSyncWait(&m_sync, ~0UL);
    }
}

}  // namespace grlib
