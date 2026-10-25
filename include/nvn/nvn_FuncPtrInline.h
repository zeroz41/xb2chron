#ifndef NVN_NVN_FUNCPTRINLINE_H
#define NVN_NVN_FUNCPTRINLINE_H

#include "nvn/nvn.h"

// NVN's entry points as the SDK's nvn_FuncPtrInline.h declares them: each a global function pointer
// (pfnc_<name>, loaded at start-up) and an inline wrapper calling through it. Only the entry points the
// decompiled code calls are listed; the signatures are the SDK's.

typedef NVNbufferAddress (*PFNNVNMEMORYPOOLGETBUFFERADDRESSPROC)(const NVNmemoryPool* pool);
extern PFNNVNMEMORYPOOLGETBUFFERADDRESSPROC pfnc_nvnMemoryPoolGetBufferAddress;
static inline NVNbufferAddress nvnMemoryPoolGetBufferAddress(const NVNmemoryPool* pool) { return pfnc_nvnMemoryPoolGetBufferAddress(pool); }

typedef void (*PFNNVNBLENDSTATESETBLENDTARGETPROC)(NVNblendState* blend, int target);
extern PFNNVNBLENDSTATESETBLENDTARGETPROC pfnc_nvnBlendStateSetBlendTarget;
static inline void nvnBlendStateSetBlendTarget(NVNblendState* blend, int target) { pfnc_nvnBlendStateSetBlendTarget(blend, target); }

typedef void (*PFNNVNBLENDSTATESETBLENDEQUATIONPROC)(NVNblendState* blend, NVNblendEquation modeRGB, NVNblendEquation modeAlpha);
extern PFNNVNBLENDSTATESETBLENDEQUATIONPROC pfnc_nvnBlendStateSetBlendEquation;
static inline void nvnBlendStateSetBlendEquation(NVNblendState* blend, NVNblendEquation modeRGB, NVNblendEquation modeAlpha) { pfnc_nvnBlendStateSetBlendEquation(blend, modeRGB, modeAlpha); }

typedef void (*PFNNVNBLENDSTATESETBLENDFUNCPROC)(NVNblendState* blend, NVNblendFunc srcFunc, NVNblendFunc dstFunc, NVNblendFunc srcFuncAlpha, NVNblendFunc dstFuncAlpha);
extern PFNNVNBLENDSTATESETBLENDFUNCPROC pfnc_nvnBlendStateSetBlendFunc;
static inline void nvnBlendStateSetBlendFunc(NVNblendState* blend, NVNblendFunc srcFunc, NVNblendFunc dstFunc, NVNblendFunc srcFuncAlpha, NVNblendFunc dstFuncAlpha) { pfnc_nvnBlendStateSetBlendFunc(blend, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha); }

typedef void (*PFNNVNCHANNELMASKSTATESETCHANNELMASKPROC)(NVNchannelMaskState* channelMask, int index, NVNboolean r, NVNboolean g, NVNboolean b, NVNboolean a);
extern PFNNVNCHANNELMASKSTATESETCHANNELMASKPROC pfnc_nvnChannelMaskStateSetChannelMask;
static inline void nvnChannelMaskStateSetChannelMask(NVNchannelMaskState* channelMask, int index, NVNboolean r, NVNboolean g, NVNboolean b, NVNboolean a) { pfnc_nvnChannelMaskStateSetChannelMask(channelMask, index, r, g, b, a); }

typedef void (*PFNNVNCOLORSTATESETLOGICOPPROC)(NVNcolorState* color, NVNlogicOp logicOp);
extern PFNNVNCOLORSTATESETLOGICOPPROC pfnc_nvnColorStateSetLogicOp;
static inline void nvnColorStateSetLogicOp(NVNcolorState* color, NVNlogicOp logicOp) { pfnc_nvnColorStateSetLogicOp(color, logicOp); }

typedef void (*PFNNVNDEPTHSTENCILSTATESETDEPTHTESTENABLEPROC)(NVNdepthStencilState* depth, NVNboolean enable);
extern PFNNVNDEPTHSTENCILSTATESETDEPTHTESTENABLEPROC pfnc_nvnDepthStencilStateSetDepthTestEnable;
static inline void nvnDepthStencilStateSetDepthTestEnable(NVNdepthStencilState* depth, NVNboolean enable) { pfnc_nvnDepthStencilStateSetDepthTestEnable(depth, enable); }

typedef void (*PFNNVNDEPTHSTENCILSTATESETDEPTHWRITEENABLEPROC)(NVNdepthStencilState* depth, NVNboolean enable);
extern PFNNVNDEPTHSTENCILSTATESETDEPTHWRITEENABLEPROC pfnc_nvnDepthStencilStateSetDepthWriteEnable;
static inline void nvnDepthStencilStateSetDepthWriteEnable(NVNdepthStencilState* depth, NVNboolean enable) { pfnc_nvnDepthStencilStateSetDepthWriteEnable(depth, enable); }

typedef void (*PFNNVNDEPTHSTENCILSTATESETDEPTHFUNCPROC)(NVNdepthStencilState* depth, NVNdepthFunc func);
extern PFNNVNDEPTHSTENCILSTATESETDEPTHFUNCPROC pfnc_nvnDepthStencilStateSetDepthFunc;
static inline void nvnDepthStencilStateSetDepthFunc(NVNdepthStencilState* depth, NVNdepthFunc func) { pfnc_nvnDepthStencilStateSetDepthFunc(depth, func); }

typedef void (*PFNNVNDEPTHSTENCILSTATESETSTENCILTESTENABLEPROC)(NVNdepthStencilState* depth, NVNboolean enable);
extern PFNNVNDEPTHSTENCILSTATESETSTENCILTESTENABLEPROC pfnc_nvnDepthStencilStateSetStencilTestEnable;
static inline void nvnDepthStencilStateSetStencilTestEnable(NVNdepthStencilState* depth, NVNboolean enable) { pfnc_nvnDepthStencilStateSetStencilTestEnable(depth, enable); }

typedef void (*PFNNVNVERTEXSTREAMSTATESETSTRIDEPROC)(NVNvertexStreamState* stream, ptrdiff_t stride);
extern PFNNVNVERTEXSTREAMSTATESETSTRIDEPROC pfnc_nvnVertexStreamStateSetStride;
static inline void nvnVertexStreamStateSetStride(NVNvertexStreamState* stream, ptrdiff_t stride) { pfnc_nvnVertexStreamStateSetStride(stream, stride); }

typedef void (*PFNNVNVERTEXSTREAMSTATESETDIVISORPROC)(NVNvertexStreamState* stream, int divisor);
extern PFNNVNVERTEXSTREAMSTATESETDIVISORPROC pfnc_nvnVertexStreamStateSetDivisor;
static inline void nvnVertexStreamStateSetDivisor(NVNvertexStreamState* stream, int divisor) { pfnc_nvnVertexStreamStateSetDivisor(stream, divisor); }

typedef NVNsyncWaitResult (*PFNNVNSYNCWAITPROC)(const NVNsync* sync, uint64_t timeoutNs);
extern PFNNVNSYNCWAITPROC pfnc_nvnSyncWait;
static inline NVNsyncWaitResult nvnSyncWait(const NVNsync* sync, uint64_t timeoutNs) { return pfnc_nvnSyncWait(sync, timeoutNs); }

typedef void (*PFNNVNCOMMANDBUFFERBINDBLENDSTATEPROC)(NVNcommandBuffer* cmdBuf, const NVNblendState* blend);
extern PFNNVNCOMMANDBUFFERBINDBLENDSTATEPROC pfnc_nvnCommandBufferBindBlendState;
static inline void nvnCommandBufferBindBlendState(NVNcommandBuffer* cmdBuf, const NVNblendState* blend) { pfnc_nvnCommandBufferBindBlendState(cmdBuf, blend); }

typedef void (*PFNNVNCOMMANDBUFFERBINDCHANNELMASKSTATEPROC)(NVNcommandBuffer* cmdBuf, const NVNchannelMaskState* channelMask);
extern PFNNVNCOMMANDBUFFERBINDCHANNELMASKSTATEPROC pfnc_nvnCommandBufferBindChannelMaskState;
static inline void nvnCommandBufferBindChannelMaskState(NVNcommandBuffer* cmdBuf, const NVNchannelMaskState* channelMask) { pfnc_nvnCommandBufferBindChannelMaskState(cmdBuf, channelMask); }

typedef void (*PFNNVNCOMMANDBUFFERBINDCOLORSTATEPROC)(NVNcommandBuffer* cmdBuf, const NVNcolorState* color);
extern PFNNVNCOMMANDBUFFERBINDCOLORSTATEPROC pfnc_nvnCommandBufferBindColorState;
static inline void nvnCommandBufferBindColorState(NVNcommandBuffer* cmdBuf, const NVNcolorState* color) { pfnc_nvnCommandBufferBindColorState(cmdBuf, color); }

typedef void (*PFNNVNCOMMANDBUFFERBINDDEPTHSTENCILSTATEPROC)(NVNcommandBuffer* cmdBuf, const NVNdepthStencilState* depthStencil);
extern PFNNVNCOMMANDBUFFERBINDDEPTHSTENCILSTATEPROC pfnc_nvnCommandBufferBindDepthStencilState;
static inline void nvnCommandBufferBindDepthStencilState(NVNcommandBuffer* cmdBuf, const NVNdepthStencilState* depthStencil) { pfnc_nvnCommandBufferBindDepthStencilState(cmdBuf, depthStencil); }

typedef void (*PFNNVNCOMMANDBUFFERBINDPOLYGONSTATEPROC)(NVNcommandBuffer* cmdBuf, const NVNpolygonState* polygon);
extern PFNNVNCOMMANDBUFFERBINDPOLYGONSTATEPROC pfnc_nvnCommandBufferBindPolygonState;
static inline void nvnCommandBufferBindPolygonState(NVNcommandBuffer* cmdBuf, const NVNpolygonState* polygon) { pfnc_nvnCommandBufferBindPolygonState(cmdBuf, polygon); }

typedef void (*PFNNVNCOMMANDBUFFERBINDVERTEXATTRIBSTATEPROC)(NVNcommandBuffer* cmdBuf, int numAttribs, const NVNvertexAttribState* attribs);
extern PFNNVNCOMMANDBUFFERBINDVERTEXATTRIBSTATEPROC pfnc_nvnCommandBufferBindVertexAttribState;
static inline void nvnCommandBufferBindVertexAttribState(NVNcommandBuffer* cmdBuf, int numAttribs, const NVNvertexAttribState* attribs) { pfnc_nvnCommandBufferBindVertexAttribState(cmdBuf, numAttribs, attribs); }

typedef void (*PFNNVNCOMMANDBUFFERBINDVERTEXSTREAMSTATEPROC)(NVNcommandBuffer* cmdBuf, int numStreams, const NVNvertexStreamState* streams);
extern PFNNVNCOMMANDBUFFERBINDVERTEXSTREAMSTATEPROC pfnc_nvnCommandBufferBindVertexStreamState;
static inline void nvnCommandBufferBindVertexStreamState(NVNcommandBuffer* cmdBuf, int numStreams, const NVNvertexStreamState* streams) { pfnc_nvnCommandBufferBindVertexStreamState(cmdBuf, numStreams, streams); }

typedef void (*PFNNVNCOMMANDBUFFERBINDPROGRAMPROC)(NVNcommandBuffer* cmdBuf, const NVNprogram* program, int stages);
extern PFNNVNCOMMANDBUFFERBINDPROGRAMPROC pfnc_nvnCommandBufferBindProgram;
static inline void nvnCommandBufferBindProgram(NVNcommandBuffer* cmdBuf, const NVNprogram* program, int stages) { pfnc_nvnCommandBufferBindProgram(cmdBuf, program, stages); }

typedef void (*PFNNVNCOMMANDBUFFERBINDVERTEXBUFFERPROC)(NVNcommandBuffer* cmdBuf, int index, NVNbufferAddress buffer, size_t size);
extern PFNNVNCOMMANDBUFFERBINDVERTEXBUFFERPROC pfnc_nvnCommandBufferBindVertexBuffer;
static inline void nvnCommandBufferBindVertexBuffer(NVNcommandBuffer* cmdBuf, int index, NVNbufferAddress buffer, size_t size) { pfnc_nvnCommandBufferBindVertexBuffer(cmdBuf, index, buffer, size); }

typedef void (*PFNNVNCOMMANDBUFFERSETVIEWPORTPROC)(NVNcommandBuffer* cmdBuf, int x, int y, int w, int h);
extern PFNNVNCOMMANDBUFFERSETVIEWPORTPROC pfnc_nvnCommandBufferSetViewport;
static inline void nvnCommandBufferSetViewport(NVNcommandBuffer* cmdBuf, int x, int y, int w, int h) { pfnc_nvnCommandBufferSetViewport(cmdBuf, x, y, w, h); }

typedef void (*PFNNVNCOMMANDBUFFERSETSCISSORPROC)(NVNcommandBuffer* cmdBuf, int x, int y, int w, int h);
extern PFNNVNCOMMANDBUFFERSETSCISSORPROC pfnc_nvnCommandBufferSetScissor;
static inline void nvnCommandBufferSetScissor(NVNcommandBuffer* cmdBuf, int x, int y, int w, int h) { pfnc_nvnCommandBufferSetScissor(cmdBuf, x, y, w, h); }

typedef void (*PFNNVNCOMMANDBUFFERCLEARCOLORPROC)(NVNcommandBuffer* cmdBuf, int index, const float* color, int mask);
extern PFNNVNCOMMANDBUFFERCLEARCOLORPROC pfnc_nvnCommandBufferClearColor;
static inline void nvnCommandBufferClearColor(NVNcommandBuffer* cmdBuf, int index, const float* color, int mask) { pfnc_nvnCommandBufferClearColor(cmdBuf, index, color, mask); }

typedef void (*PFNNVNCOMMANDBUFFERDRAWARRAYSPROC)(NVNcommandBuffer* cmdBuf, NVNdrawPrimitive mode, int first, int count);
extern PFNNVNCOMMANDBUFFERDRAWARRAYSPROC pfnc_nvnCommandBufferDrawArrays;
static inline void nvnCommandBufferDrawArrays(NVNcommandBuffer* cmdBuf, NVNdrawPrimitive mode, int first, int count) { pfnc_nvnCommandBufferDrawArrays(cmdBuf, mode, first, count); }

typedef void (*PFNNVNCOMMANDBUFFERDRAWARRAYSINSTANCEDPROC)(NVNcommandBuffer* cmdBuf, NVNdrawPrimitive mode, int first, int count, int baseInstance, int instanceCount);
extern PFNNVNCOMMANDBUFFERDRAWARRAYSINSTANCEDPROC pfnc_nvnCommandBufferDrawArraysInstanced;
static inline void nvnCommandBufferDrawArraysInstanced(NVNcommandBuffer* cmdBuf, NVNdrawPrimitive mode, int first, int count, int baseInstance, int instanceCount) { pfnc_nvnCommandBufferDrawArraysInstanced(cmdBuf, mode, first, count, baseInstance, instanceCount); }

typedef void (*PFNNVNCOMMANDBUFFERSETRENDERTARGETSPROC)(NVNcommandBuffer* cmdBuf, int numColors, const NVNtexture* const* colors, const NVNtextureView* const* colorViews, const NVNtexture* depthStencil, const NVNtextureView* depthStencilView);
extern PFNNVNCOMMANDBUFFERSETRENDERTARGETSPROC pfnc_nvnCommandBufferSetRenderTargets;
static inline void nvnCommandBufferSetRenderTargets(NVNcommandBuffer* cmdBuf, int numColors, const NVNtexture* const* colors, const NVNtextureView* const* colorViews, const NVNtexture* depthStencil, const NVNtextureView* depthStencilView) { pfnc_nvnCommandBufferSetRenderTargets(cmdBuf, numColors, colors, colorViews, depthStencil, depthStencilView); }

typedef void (*PFNNVNCOMMANDBUFFERSETLINEWIDTHPROC)(NVNcommandBuffer* cmdBuf, float width);
extern PFNNVNCOMMANDBUFFERSETLINEWIDTHPROC pfnc_nvnCommandBufferSetLineWidth;
static inline void nvnCommandBufferSetLineWidth(NVNcommandBuffer* cmdBuf, float width) { pfnc_nvnCommandBufferSetLineWidth(cmdBuf, width); }

typedef void (*PFNNVNCOMMANDBUFFERSETRASTERIZERDISCARDPROC)(NVNcommandBuffer* cmdBuf, NVNboolean discard);
extern PFNNVNCOMMANDBUFFERSETRASTERIZERDISCARDPROC pfnc_nvnCommandBufferSetRasterizerDiscard;
static inline void nvnCommandBufferSetRasterizerDiscard(NVNcommandBuffer* cmdBuf, NVNboolean discard) { pfnc_nvnCommandBufferSetRasterizerDiscard(cmdBuf, discard); }

typedef void (*PFNNVNCOMMANDBUFFERDISPATCHCOMPUTEPROC)(NVNcommandBuffer* cmdBuf, int groupsX, int groupsY, int groupsZ);
extern PFNNVNCOMMANDBUFFERDISPATCHCOMPUTEPROC pfnc_nvnCommandBufferDispatchCompute;
static inline void nvnCommandBufferDispatchCompute(NVNcommandBuffer* cmdBuf, int groupsX, int groupsY, int groupsZ) { pfnc_nvnCommandBufferDispatchCompute(cmdBuf, groupsX, groupsY, groupsZ); }

typedef void (*PFNNVNCOMMANDBUFFERBARRIERPROC)(NVNcommandBuffer* cmdBuf, int barrierBits);
extern PFNNVNCOMMANDBUFFERBARRIERPROC pfnc_nvnCommandBufferBarrier;
static inline void nvnCommandBufferBarrier(NVNcommandBuffer* cmdBuf, int barrierBits) { pfnc_nvnCommandBufferBarrier(cmdBuf, barrierBits); }

typedef void (*PFNNVNCOMMANDBUFFERSETTILEDCACHEACTIONPROC)(NVNcommandBuffer* cmdBuf, NVNtiledCacheAction action);
extern PFNNVNCOMMANDBUFFERSETTILEDCACHEACTIONPROC pfnc_nvnCommandBufferSetTiledCacheAction;
static inline void nvnCommandBufferSetTiledCacheAction(NVNcommandBuffer* cmdBuf, NVNtiledCacheAction action) { pfnc_nvnCommandBufferSetTiledCacheAction(cmdBuf, action); }

typedef void (*PFNNVNCOMMANDBUFFERSETTILEDCACHETILESIZEPROC)(NVNcommandBuffer* cmdBuf, int tileWidth, int tileHeight);
extern PFNNVNCOMMANDBUFFERSETTILEDCACHETILESIZEPROC pfnc_nvnCommandBufferSetTiledCacheTileSize;
static inline void nvnCommandBufferSetTiledCacheTileSize(NVNcommandBuffer* cmdBuf, int tileWidth, int tileHeight) { pfnc_nvnCommandBufferSetTiledCacheTileSize(cmdBuf, tileWidth, tileHeight); }

typedef void (*PFNNVNCOLORSTATESETBLENDENABLEPROC)(NVNcolorState* color, int index, NVNboolean enable);
extern PFNNVNCOLORSTATESETBLENDENABLEPROC pfnc_nvnColorStateSetBlendEnable;
static inline void nvnColorStateSetBlendEnable(NVNcolorState* color, int index, NVNboolean enable) { pfnc_nvnColorStateSetBlendEnable(color, index, enable); }

typedef void (*PFNNVNCOMMANDBUFFERRESETCOUNTERPROC)(NVNcommandBuffer* cmdBuf, NVNcounterType counter);
extern PFNNVNCOMMANDBUFFERRESETCOUNTERPROC pfnc_nvnCommandBufferResetCounter;
static inline void nvnCommandBufferResetCounter(NVNcommandBuffer* cmdBuf, NVNcounterType counter) { pfnc_nvnCommandBufferResetCounter(cmdBuf, counter); }
typedef void (*PFNNVNCOMMANDBUFFERREPORTCOUNTERPROC)(NVNcommandBuffer* cmdBuf, NVNcounterType counter, NVNbufferAddress buffer);
extern PFNNVNCOMMANDBUFFERREPORTCOUNTERPROC pfnc_nvnCommandBufferReportCounter;
static inline void nvnCommandBufferReportCounter(NVNcommandBuffer* cmdBuf, NVNcounterType counter, NVNbufferAddress buffer) { pfnc_nvnCommandBufferReportCounter(cmdBuf, counter, buffer); }
typedef void (*PFNNVNCOMMANDBUFFERBINDUNIFORMBUFFERPROC)(NVNcommandBuffer* cmdBuf, NVNshaderStage stage, int index, NVNbufferAddress buffer, size_t size);
extern PFNNVNCOMMANDBUFFERBINDUNIFORMBUFFERPROC pfnc_nvnCommandBufferBindUniformBuffer;
static inline void nvnCommandBufferBindUniformBuffer(NVNcommandBuffer* cmdBuf, NVNshaderStage stage, int index, NVNbufferAddress buffer, size_t size) { pfnc_nvnCommandBufferBindUniformBuffer(cmdBuf, stage, index, buffer, size); }

typedef void (*PFNNVNCOMMANDBUFFERBINDSTORAGEBUFFERPROC)(NVNcommandBuffer* cmdBuf, NVNshaderStage stage, int index, NVNbufferAddress buffer, size_t size);
extern PFNNVNCOMMANDBUFFERBINDSTORAGEBUFFERPROC pfnc_nvnCommandBufferBindStorageBuffer;
static inline void nvnCommandBufferBindStorageBuffer(NVNcommandBuffer* cmdBuf, NVNshaderStage stage, int index, NVNbufferAddress buffer, size_t size) { pfnc_nvnCommandBufferBindStorageBuffer(cmdBuf, stage, index, buffer, size); }

typedef void (*PFNNVNCOMMANDBUFFERBINDTEXTUREPROC)(NVNcommandBuffer* cmdBuf, NVNshaderStage stage, int index, NVNtextureHandle texture);
extern PFNNVNCOMMANDBUFFERBINDTEXTUREPROC pfnc_nvnCommandBufferBindTexture;
static inline void nvnCommandBufferBindTexture(NVNcommandBuffer* cmdBuf, NVNshaderStage stage, int index, NVNtextureHandle texture) { pfnc_nvnCommandBufferBindTexture(cmdBuf, stage, index, texture); }

typedef void (*PFNNVNCOMMANDBUFFERBINDIMAGEPROC)(NVNcommandBuffer* cmdBuf, NVNshaderStage stage, int index, NVNimageHandle image);
extern PFNNVNCOMMANDBUFFERBINDIMAGEPROC pfnc_nvnCommandBufferBindImage;
static inline void nvnCommandBufferBindImage(NVNcommandBuffer* cmdBuf, NVNshaderStage stage, int index, NVNimageHandle image) { pfnc_nvnCommandBufferBindImage(cmdBuf, stage, index, image); }

#endif
