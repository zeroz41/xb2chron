#ifndef NVN_NVN_FUNCPTRINLINE_H
#define NVN_NVN_FUNCPTRINLINE_H

#include "nvn/nvn.h"

// NVN's entry points as the SDK's nvn_FuncPtrInline.h declares them: each a global function pointer
// (pfnc_<name>, loaded at start-up) and an inline wrapper calling through it. Only the entry points the
// decompiled code calls are listed; the signatures are the SDK's.

typedef void (*PFNNVNTEXTUREFINALIZEPROC)(NVNtexture* texture);
extern PFNNVNTEXTUREFINALIZEPROC pfnc_nvnTextureFinalize;
static inline void nvnTextureFinalize(NVNtexture* texture) { pfnc_nvnTextureFinalize(texture); }

typedef void (*PFNNVNTEXTUREBUILDERSETDEFAULTSPROC)(NVNtextureBuilder* builder);
extern PFNNVNTEXTUREBUILDERSETDEFAULTSPROC pfnc_nvnTextureBuilderSetDefaults;
static inline void nvnTextureBuilderSetDefaults(NVNtextureBuilder* builder) { pfnc_nvnTextureBuilderSetDefaults(builder); }

typedef void (*PFNNVNTEXTUREBUILDERSETDEVICEPROC)(NVNtextureBuilder* builder, NVNdevice* device);
extern PFNNVNTEXTUREBUILDERSETDEVICEPROC pfnc_nvnTextureBuilderSetDevice;
static inline void nvnTextureBuilderSetDevice(NVNtextureBuilder* builder, NVNdevice* device) { pfnc_nvnTextureBuilderSetDevice(builder, device); }

typedef void (*PFNNVNTEXTUREBUILDERSETTARGETPROC)(NVNtextureBuilder* builder, NVNtextureTarget target);
extern PFNNVNTEXTUREBUILDERSETTARGETPROC pfnc_nvnTextureBuilderSetTarget;
static inline void nvnTextureBuilderSetTarget(NVNtextureBuilder* builder, NVNtextureTarget target) { pfnc_nvnTextureBuilderSetTarget(builder, target); }

typedef void (*PFNNVNTEXTUREBUILDERSETFORMATPROC)(NVNtextureBuilder* builder, NVNformat format);
extern PFNNVNTEXTUREBUILDERSETFORMATPROC pfnc_nvnTextureBuilderSetFormat;
static inline void nvnTextureBuilderSetFormat(NVNtextureBuilder* builder, NVNformat format) { pfnc_nvnTextureBuilderSetFormat(builder, format); }

typedef void (*PFNNVNTEXTUREBUILDERSETSIZE2DPROC)(NVNtextureBuilder* builder, int width, int height);
extern PFNNVNTEXTUREBUILDERSETSIZE2DPROC pfnc_nvnTextureBuilderSetSize2D;
static inline void nvnTextureBuilderSetSize2D(NVNtextureBuilder* builder, int width, int height) { pfnc_nvnTextureBuilderSetSize2D(builder, width, height); }

typedef void (*PFNNVNTEXTUREBUILDERSETDEPTHPROC)(NVNtextureBuilder* builder, int depth);
extern PFNNVNTEXTUREBUILDERSETDEPTHPROC pfnc_nvnTextureBuilderSetDepth;
static inline void nvnTextureBuilderSetDepth(NVNtextureBuilder* builder, int depth) { pfnc_nvnTextureBuilderSetDepth(builder, depth); }

typedef void (*PFNNVNTEXTUREBUILDERSETLEVELSPROC)(NVNtextureBuilder* builder, int numLevels);
extern PFNNVNTEXTUREBUILDERSETLEVELSPROC pfnc_nvnTextureBuilderSetLevels;
static inline void nvnTextureBuilderSetLevels(NVNtextureBuilder* builder, int numLevels) { pfnc_nvnTextureBuilderSetLevels(builder, numLevels); }

typedef void (*PFNNVNTEXTUREBUILDERSETFLAGSPROC)(NVNtextureBuilder* builder, NVNtextureFlags flags);
extern PFNNVNTEXTUREBUILDERSETFLAGSPROC pfnc_nvnTextureBuilderSetFlags;
static inline void nvnTextureBuilderSetFlags(NVNtextureBuilder* builder, NVNtextureFlags flags) { pfnc_nvnTextureBuilderSetFlags(builder, flags); }

typedef size_t (*PFNNVNTEXTUREBUILDERGETSTORAGESIZEPROC)(const NVNtextureBuilder* builder);
extern PFNNVNTEXTUREBUILDERGETSTORAGESIZEPROC pfnc_nvnTextureBuilderGetStorageSize;
static inline size_t nvnTextureBuilderGetStorageSize(const NVNtextureBuilder* builder) { return pfnc_nvnTextureBuilderGetStorageSize(builder); }

typedef size_t (*PFNNVNTEXTUREBUILDERGETSTORAGEALIGNMENTPROC)(const NVNtextureBuilder* builder);
extern PFNNVNTEXTUREBUILDERGETSTORAGEALIGNMENTPROC pfnc_nvnTextureBuilderGetStorageAlignment;
static inline size_t nvnTextureBuilderGetStorageAlignment(const NVNtextureBuilder* builder) { return pfnc_nvnTextureBuilderGetStorageAlignment(builder); }

typedef void (*PFNNVNTEXTUREBUILDERSETSIZE3DPROC)(NVNtextureBuilder* builder, int width, int height, int depth);
extern PFNNVNTEXTUREBUILDERSETSIZE3DPROC pfnc_nvnTextureBuilderSetSize3D;
static inline void nvnTextureBuilderSetSize3D(NVNtextureBuilder* builder, int width, int height, int depth) { pfnc_nvnTextureBuilderSetSize3D(builder, width, height, depth); }

typedef void (*PFNNVNTEXTUREBUILDERSETPACKAGEDTEXTUREDATAPROC)(NVNtextureBuilder* builder, const void* data);
extern PFNNVNTEXTUREBUILDERSETPACKAGEDTEXTUREDATAPROC pfnc_nvnTextureBuilderSetPackagedTextureData;
static inline void nvnTextureBuilderSetPackagedTextureData(NVNtextureBuilder* builder, const void* data) { pfnc_nvnTextureBuilderSetPackagedTextureData(builder, data); }

typedef void (*PFNNVNTEXTUREBUILDERSETSWIZZLEPROC)(NVNtextureBuilder* builder, NVNtextureSwizzle r, NVNtextureSwizzle g, NVNtextureSwizzle b, NVNtextureSwizzle a);
extern PFNNVNTEXTUREBUILDERSETSWIZZLEPROC pfnc_nvnTextureBuilderSetSwizzle;
static inline void nvnTextureBuilderSetSwizzle(NVNtextureBuilder* builder, NVNtextureSwizzle r, NVNtextureSwizzle g, NVNtextureSwizzle b, NVNtextureSwizzle a) { pfnc_nvnTextureBuilderSetSwizzle(builder, r, g, b, a); }

typedef void (*PFNNVNTEXTUREBUILDERSETSTORAGEPROC)(NVNtextureBuilder* builder, const NVNmemoryPool* pool, ptrdiff_t offset);
extern PFNNVNTEXTUREBUILDERSETSTORAGEPROC pfnc_nvnTextureBuilderSetStorage;
static inline void nvnTextureBuilderSetStorage(NVNtextureBuilder* builder, const NVNmemoryPool* pool, ptrdiff_t offset) { pfnc_nvnTextureBuilderSetStorage(builder, pool, offset); }

typedef void (*PFNNVNTEXTUREBUILDERSETDEPTHSTENCILMODEPROC)(NVNtextureBuilder* builder, NVNtextureDepthStencilMode mode);
extern PFNNVNTEXTUREBUILDERSETDEPTHSTENCILMODEPROC pfnc_nvnTextureBuilderSetDepthStencilMode;
static inline void nvnTextureBuilderSetDepthStencilMode(NVNtextureBuilder* builder, NVNtextureDepthStencilMode mode) { pfnc_nvnTextureBuilderSetDepthStencilMode(builder, mode); }

typedef void (*PFNNVNTEXTUREBUILDERSETSTRIDEPROC)(NVNtextureBuilder* builder, ptrdiff_t stride);
extern PFNNVNTEXTUREBUILDERSETSTRIDEPROC pfnc_nvnTextureBuilderSetStride;
static inline void nvnTextureBuilderSetStride(NVNtextureBuilder* builder, ptrdiff_t stride) { pfnc_nvnTextureBuilderSetStride(builder, stride); }

typedef NVNboolean (*PFNNVNTEXTUREINITIALIZEPROC)(NVNtexture* texture, const NVNtextureBuilder* builder);
extern PFNNVNTEXTUREINITIALIZEPROC pfnc_nvnTextureInitialize;
static inline NVNboolean nvnTextureInitialize(NVNtexture* texture, const NVNtextureBuilder* builder) { return pfnc_nvnTextureInitialize(texture, builder); }

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

typedef void (*PFNNVNCOMMANDBUFFERSETSTENCILREFPROC)(NVNcommandBuffer* cmdBuf, NVNface faces, int ref);
extern PFNNVNCOMMANDBUFFERSETSTENCILREFPROC pfnc_nvnCommandBufferSetStencilRef;
static inline void nvnCommandBufferSetStencilRef(NVNcommandBuffer* cmdBuf, NVNface faces, int ref) { pfnc_nvnCommandBufferSetStencilRef(cmdBuf, faces, ref); }

typedef void (*PFNNVNCOMMANDBUFFERSETSTENCILVALUEMASKPROC)(NVNcommandBuffer* cmdBuf, NVNface faces, int mask);
extern PFNNVNCOMMANDBUFFERSETSTENCILVALUEMASKPROC pfnc_nvnCommandBufferSetStencilValueMask;
static inline void nvnCommandBufferSetStencilValueMask(NVNcommandBuffer* cmdBuf, NVNface faces, int mask) { pfnc_nvnCommandBufferSetStencilValueMask(cmdBuf, faces, mask); }

typedef void (*PFNNVNCOMMANDBUFFERSETSTENCILMASKPROC)(NVNcommandBuffer* cmdBuf, NVNface faces, int mask);
extern PFNNVNCOMMANDBUFFERSETSTENCILMASKPROC pfnc_nvnCommandBufferSetStencilMask;
static inline void nvnCommandBufferSetStencilMask(NVNcommandBuffer* cmdBuf, NVNface faces, int mask) { pfnc_nvnCommandBufferSetStencilMask(cmdBuf, faces, mask); }

typedef void (*PFNNVNDEPTHSTENCILSTATESETSTENCILOPPROC)(NVNdepthStencilState* depth, NVNface faces, NVNstencilOp fail, NVNstencilOp depthFail, NVNstencilOp depthPass);
extern PFNNVNDEPTHSTENCILSTATESETSTENCILOPPROC pfnc_nvnDepthStencilStateSetStencilOp;
static inline void nvnDepthStencilStateSetStencilOp(NVNdepthStencilState* depth, NVNface faces, NVNstencilOp fail, NVNstencilOp depthFail, NVNstencilOp depthPass) { pfnc_nvnDepthStencilStateSetStencilOp(depth, faces, fail, depthFail, depthPass); }

typedef void (*PFNNVNDEPTHSTENCILSTATESETSTENCILFUNCPROC)(NVNdepthStencilState* depth, NVNface faces, NVNstencilFunc func);
extern PFNNVNDEPTHSTENCILSTATESETSTENCILFUNCPROC pfnc_nvnDepthStencilStateSetStencilFunc;
static inline void nvnDepthStencilStateSetStencilFunc(NVNdepthStencilState* depth, NVNface faces, NVNstencilFunc func) { pfnc_nvnDepthStencilStateSetStencilFunc(depth, faces, func); }

typedef void (*PFNNVNVERTEXSTREAMSTATESETSTRIDEPROC)(NVNvertexStreamState* stream, ptrdiff_t stride);
extern PFNNVNVERTEXSTREAMSTATESETSTRIDEPROC pfnc_nvnVertexStreamStateSetStride;
static inline void nvnVertexStreamStateSetStride(NVNvertexStreamState* stream, ptrdiff_t stride) { pfnc_nvnVertexStreamStateSetStride(stream, stride); }

typedef void (*PFNNVNVERTEXSTREAMSTATESETDIVISORPROC)(NVNvertexStreamState* stream, int divisor);
extern PFNNVNVERTEXSTREAMSTATESETDIVISORPROC pfnc_nvnVertexStreamStateSetDivisor;
static inline void nvnVertexStreamStateSetDivisor(NVNvertexStreamState* stream, int divisor) { pfnc_nvnVertexStreamStateSetDivisor(stream, divisor); }

typedef NVNsyncWaitResult (*PFNNVNSYNCWAITPROC)(const NVNsync* sync, uint64_t timeoutNs);
extern PFNNVNSYNCWAITPROC pfnc_nvnSyncWait;
static inline NVNsyncWaitResult nvnSyncWait(const NVNsync* sync, uint64_t timeoutNs) { return pfnc_nvnSyncWait(sync, timeoutNs); }
typedef void (*PFNNVNSYNCFINALIZEPROC)(NVNsync* sync);
extern PFNNVNSYNCFINALIZEPROC pfnc_nvnSyncFinalize;
static inline void nvnSyncFinalize(NVNsync* sync) { pfnc_nvnSyncFinalize(sync); }
typedef void (*PFNNVNWINDOWFINALIZEPROC)(NVNwindow* window);
extern PFNNVNWINDOWFINALIZEPROC pfnc_nvnWindowFinalize;
static inline void nvnWindowFinalize(NVNwindow* window) { pfnc_nvnWindowFinalize(window); }

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

typedef void (*PFNNVNCOMMANDBUFFERCLEARCOLORIPROC)(NVNcommandBuffer* cmdBuf, int index, const int* color, int mask);
extern PFNNVNCOMMANDBUFFERCLEARCOLORIPROC pfnc_nvnCommandBufferClearColori;
static inline void nvnCommandBufferClearColori(NVNcommandBuffer* cmdBuf, int index, const int* color, int mask) { pfnc_nvnCommandBufferClearColori(cmdBuf, index, color, mask); }

typedef void (*PFNNVNCOMMANDBUFFERCLEARDEPTHSTENCILPROC)(NVNcommandBuffer* cmdBuf, float depthValue, NVNboolean depthMask, int stencilValue, int stencilMask);
extern PFNNVNCOMMANDBUFFERCLEARDEPTHSTENCILPROC pfnc_nvnCommandBufferClearDepthStencil;
static inline void nvnCommandBufferClearDepthStencil(NVNcommandBuffer* cmdBuf, float depthValue, NVNboolean depthMask, int stencilValue, int stencilMask) { pfnc_nvnCommandBufferClearDepthStencil(cmdBuf, depthValue, depthMask, stencilValue, stencilMask); }

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

typedef void (*PFNNVNMEMORYPOOLBUILDERSETDEFAULTSPROC)(NVNmemoryPoolBuilder* builder);
extern PFNNVNMEMORYPOOLBUILDERSETDEFAULTSPROC pfnc_nvnMemoryPoolBuilderSetDefaults;
static inline void nvnMemoryPoolBuilderSetDefaults(NVNmemoryPoolBuilder* builder) { pfnc_nvnMemoryPoolBuilderSetDefaults(builder); }

typedef void (*PFNNVNMEMORYPOOLBUILDERSETDEVICEPROC)(NVNmemoryPoolBuilder* builder, NVNdevice* device);
extern PFNNVNMEMORYPOOLBUILDERSETDEVICEPROC pfnc_nvnMemoryPoolBuilderSetDevice;
static inline void nvnMemoryPoolBuilderSetDevice(NVNmemoryPoolBuilder* builder, NVNdevice* device) { pfnc_nvnMemoryPoolBuilderSetDevice(builder, device); }

typedef void (*PFNNVNMEMORYPOOLBUILDERSETFLAGSPROC)(NVNmemoryPoolBuilder* builder, int flags);
extern PFNNVNMEMORYPOOLBUILDERSETFLAGSPROC pfnc_nvnMemoryPoolBuilderSetFlags;
static inline void nvnMemoryPoolBuilderSetFlags(NVNmemoryPoolBuilder* builder, int flags) { pfnc_nvnMemoryPoolBuilderSetFlags(builder, flags); }

typedef void (*PFNNVNMEMORYPOOLBUILDERSETSTORAGEPROC)(NVNmemoryPoolBuilder* builder, void* memory, size_t size);
extern PFNNVNMEMORYPOOLBUILDERSETSTORAGEPROC pfnc_nvnMemoryPoolBuilderSetStorage;
static inline void nvnMemoryPoolBuilderSetStorage(NVNmemoryPoolBuilder* builder, void* memory, size_t size) { pfnc_nvnMemoryPoolBuilderSetStorage(builder, memory, size); }

typedef NVNboolean (*PFNNVNMEMORYPOOLINITIALIZEPROC)(NVNmemoryPool* pool, const NVNmemoryPoolBuilder* builder);
extern PFNNVNMEMORYPOOLINITIALIZEPROC pfnc_nvnMemoryPoolInitialize;
static inline NVNboolean nvnMemoryPoolInitialize(NVNmemoryPool* pool, const NVNmemoryPoolBuilder* builder) { return pfnc_nvnMemoryPoolInitialize(pool, builder); }

typedef void (*PFNNVNCOMMANDBUFFERMEMORYCALLBACKPROC)(NVNcommandBuffer* cmdBuf, NVNcommandBufferMemoryEvent event,
                                                     size_t minSize, void* callbackData);
typedef NVNboolean (*PFNNVNCOMMANDBUFFERINITIALIZEPROC)(NVNcommandBuffer* cmdBuf, NVNdevice* device);
extern PFNNVNCOMMANDBUFFERINITIALIZEPROC pfnc_nvnCommandBufferInitialize;
static inline NVNboolean nvnCommandBufferInitialize(NVNcommandBuffer* cmdBuf, NVNdevice* device) { return pfnc_nvnCommandBufferInitialize(cmdBuf, device); }
typedef void (*PFNNVNCOMMANDBUFFERFINALIZEPROC)(NVNcommandBuffer* cmdBuf);
extern PFNNVNCOMMANDBUFFERFINALIZEPROC pfnc_nvnCommandBufferFinalize;
static inline void nvnCommandBufferFinalize(NVNcommandBuffer* cmdBuf) { pfnc_nvnCommandBufferFinalize(cmdBuf); }
typedef void (*PFNNVNCOMMANDBUFFERSETMEMORYCALLBACKPROC)(NVNcommandBuffer* cmdBuf, PFNNVNCOMMANDBUFFERMEMORYCALLBACKPROC callback);
extern PFNNVNCOMMANDBUFFERSETMEMORYCALLBACKPROC pfnc_nvnCommandBufferSetMemoryCallback;
static inline void nvnCommandBufferSetMemoryCallback(NVNcommandBuffer* cmdBuf, PFNNVNCOMMANDBUFFERMEMORYCALLBACKPROC callback) { pfnc_nvnCommandBufferSetMemoryCallback(cmdBuf, callback); }
typedef void (*PFNNVNCOMMANDBUFFERSETMEMORYCALLBACKDATAPROC)(NVNcommandBuffer* cmdBuf, void* callbackData);
extern PFNNVNCOMMANDBUFFERSETMEMORYCALLBACKDATAPROC pfnc_nvnCommandBufferSetMemoryCallbackData;
static inline void nvnCommandBufferSetMemoryCallbackData(NVNcommandBuffer* cmdBuf, void* callbackData) { pfnc_nvnCommandBufferSetMemoryCallbackData(cmdBuf, callbackData); }
typedef void (*PFNNVNCOMMANDBUFFERADDCOMMANDMEMORYPROC)(NVNcommandBuffer* cmdBuf, const NVNmemoryPool* pool, ptrdiff_t offset, size_t size);
extern PFNNVNCOMMANDBUFFERADDCOMMANDMEMORYPROC pfnc_nvnCommandBufferAddCommandMemory;
static inline void nvnCommandBufferAddCommandMemory(NVNcommandBuffer* cmdBuf, const NVNmemoryPool* pool, ptrdiff_t offset, size_t size) { pfnc_nvnCommandBufferAddCommandMemory(cmdBuf, pool, offset, size); }
typedef void (*PFNNVNCOMMANDBUFFERADDCONTROLMEMORYPROC)(NVNcommandBuffer* cmdBuf, void* memory, size_t size);
extern PFNNVNCOMMANDBUFFERADDCONTROLMEMORYPROC pfnc_nvnCommandBufferAddControlMemory;
static inline void nvnCommandBufferAddControlMemory(NVNcommandBuffer* cmdBuf, void* memory, size_t size) { pfnc_nvnCommandBufferAddControlMemory(cmdBuf, memory, size); }
typedef void (*PFNNVNCOMMANDBUFFERBEGINRECORDINGPROC)(NVNcommandBuffer* cmdBuf);
extern PFNNVNCOMMANDBUFFERBEGINRECORDINGPROC pfnc_nvnCommandBufferBeginRecording;
static inline void nvnCommandBufferBeginRecording(NVNcommandBuffer* cmdBuf) { pfnc_nvnCommandBufferBeginRecording(cmdBuf); }
typedef NVNcommandHandle (*PFNNVNCOMMANDBUFFERENDRECORDINGPROC)(NVNcommandBuffer* cmdBuf);
extern PFNNVNCOMMANDBUFFERENDRECORDINGPROC pfnc_nvnCommandBufferEndRecording;
static inline NVNcommandHandle nvnCommandBufferEndRecording(NVNcommandBuffer* cmdBuf) { return pfnc_nvnCommandBufferEndRecording(cmdBuf); }
typedef size_t (*PFNNVNCOMMANDBUFFERGETCOMMANDMEMORYUSEDPROC)(const NVNcommandBuffer* cmdBuf);
extern PFNNVNCOMMANDBUFFERGETCOMMANDMEMORYUSEDPROC pfnc_nvnCommandBufferGetCommandMemoryUsed;
static inline size_t nvnCommandBufferGetCommandMemoryUsed(const NVNcommandBuffer* cmdBuf) { return pfnc_nvnCommandBufferGetCommandMemoryUsed(cmdBuf); }
typedef size_t (*PFNNVNCOMMANDBUFFERGETCONTROLMEMORYUSEDPROC)(const NVNcommandBuffer* cmdBuf);
extern PFNNVNCOMMANDBUFFERGETCONTROLMEMORYUSEDPROC pfnc_nvnCommandBufferGetControlMemoryUsed;
static inline size_t nvnCommandBufferGetControlMemoryUsed(const NVNcommandBuffer* cmdBuf) { return pfnc_nvnCommandBufferGetControlMemoryUsed(cmdBuf); }
typedef void (*PFNNVNCOMMANDBUFFERCALLCOMMANDSPROC)(NVNcommandBuffer* cmdBuf, int numCommands, const NVNcommandHandle* handles);
extern PFNNVNCOMMANDBUFFERCALLCOMMANDSPROC pfnc_nvnCommandBufferCallCommands;
static inline void nvnCommandBufferCallCommands(NVNcommandBuffer* cmdBuf, int numCommands, const NVNcommandHandle* handles) { pfnc_nvnCommandBufferCallCommands(cmdBuf, numCommands, handles); }
typedef void (*PFNNVNCOMMANDBUFFERBINDTRANSFORMFEEDBACKBUFFERPROC)(NVNcommandBuffer* cmdBuf, int index, NVNbufferAddress buffer, size_t size);
extern PFNNVNCOMMANDBUFFERBINDTRANSFORMFEEDBACKBUFFERPROC pfnc_nvnCommandBufferBindTransformFeedbackBuffer;
static inline void nvnCommandBufferBindTransformFeedbackBuffer(NVNcommandBuffer* cmdBuf, int index, NVNbufferAddress buffer, size_t size) { pfnc_nvnCommandBufferBindTransformFeedbackBuffer(cmdBuf, index, buffer, size); }
typedef void (*PFNNVNCOMMANDBUFFERBEGINTRANSFORMFEEDBACKPROC)(NVNcommandBuffer* cmdBuf, NVNbufferAddress buffer);
extern PFNNVNCOMMANDBUFFERBEGINTRANSFORMFEEDBACKPROC pfnc_nvnCommandBufferBeginTransformFeedback;
static inline void nvnCommandBufferBeginTransformFeedback(NVNcommandBuffer* cmdBuf, NVNbufferAddress buffer) { pfnc_nvnCommandBufferBeginTransformFeedback(cmdBuf, buffer); }
typedef void (*PFNNVNCOMMANDBUFFERENDTRANSFORMFEEDBACKPROC)(NVNcommandBuffer* cmdBuf, NVNbufferAddress buffer);
extern PFNNVNCOMMANDBUFFERENDTRANSFORMFEEDBACKPROC pfnc_nvnCommandBufferEndTransformFeedback;
static inline void nvnCommandBufferEndTransformFeedback(NVNcommandBuffer* cmdBuf, NVNbufferAddress buffer) { pfnc_nvnCommandBufferEndTransformFeedback(cmdBuf, buffer); }
typedef void (*PFNNVNMEMORYPOOLFINALIZEPROC)(NVNmemoryPool* pool);
extern PFNNVNMEMORYPOOLFINALIZEPROC pfnc_nvnMemoryPoolFinalize;
static inline void nvnMemoryPoolFinalize(NVNmemoryPool* pool) { pfnc_nvnMemoryPoolFinalize(pool); }


typedef void (*PFNNVNCOMMANDBUFFERDRAWELEMENTSPROC)(NVNcommandBuffer* cmdBuf, NVNdrawPrimitive mode, NVNindexType type, int count, NVNbufferAddress indexBuffer);
extern PFNNVNCOMMANDBUFFERDRAWELEMENTSPROC pfnc_nvnCommandBufferDrawElements;
static inline void nvnCommandBufferDrawElements(NVNcommandBuffer* cmdBuf, NVNdrawPrimitive mode, NVNindexType type, int count, NVNbufferAddress indexBuffer) { pfnc_nvnCommandBufferDrawElements(cmdBuf, mode, type, count, indexBuffer); }

typedef void (*PFNNVNCOMMANDBUFFERDRAWELEMENTSINSTANCEDPROC)(NVNcommandBuffer* cmdBuf, NVNdrawPrimitive mode, NVNindexType type, int count, NVNbufferAddress indexBuffer, int baseVertex, int baseInstance, int instanceCount);
extern PFNNVNCOMMANDBUFFERDRAWELEMENTSINSTANCEDPROC pfnc_nvnCommandBufferDrawElementsInstanced;
static inline void nvnCommandBufferDrawElementsInstanced(NVNcommandBuffer* cmdBuf, NVNdrawPrimitive mode, NVNindexType type, int count, NVNbufferAddress indexBuffer, int baseVertex, int baseInstance, int instanceCount) { pfnc_nvnCommandBufferDrawElementsInstanced(cmdBuf, mode, type, count, indexBuffer, baseVertex, baseInstance, instanceCount); }

typedef void (*PFNNVNVERTEXATTRIBSTATESETDEFAULTSPROC)(NVNvertexAttribState* attrib);
extern PFNNVNVERTEXATTRIBSTATESETDEFAULTSPROC pfnc_nvnVertexAttribStateSetDefaults;
static inline void nvnVertexAttribStateSetDefaults(NVNvertexAttribState* attrib) { pfnc_nvnVertexAttribStateSetDefaults(attrib); }

typedef void (*PFNNVNVERTEXATTRIBSTATESETFORMATPROC)(NVNvertexAttribState* attrib, NVNformat format, ptrdiff_t relativeOffset);
extern PFNNVNVERTEXATTRIBSTATESETFORMATPROC pfnc_nvnVertexAttribStateSetFormat;
static inline void nvnVertexAttribStateSetFormat(NVNvertexAttribState* attrib, NVNformat format, ptrdiff_t relativeOffset) { pfnc_nvnVertexAttribStateSetFormat(attrib, format, relativeOffset); }

typedef void (*PFNNVNVERTEXATTRIBSTATESETSTREAMINDEXPROC)(NVNvertexAttribState* attrib, int streamIndex);
extern PFNNVNVERTEXATTRIBSTATESETSTREAMINDEXPROC pfnc_nvnVertexAttribStateSetStreamIndex;
static inline void nvnVertexAttribStateSetStreamIndex(NVNvertexAttribState* attrib, int streamIndex) { pfnc_nvnVertexAttribStateSetStreamIndex(attrib, streamIndex); }

typedef uint64_t (*PFNNVNDEVICEGETTIMESTAMPINNANOSECONDSPROC)(const NVNdevice* device, const NVNcounterData* counterData);
extern PFNNVNDEVICEGETTIMESTAMPINNANOSECONDSPROC pfnc_nvnDeviceGetTimestampInNanoseconds;
static inline uint64_t nvnDeviceGetTimestampInNanoseconds(const NVNdevice* device, const NVNcounterData* counterData) { return pfnc_nvnDeviceGetTimestampInNanoseconds(device, counterData); }

typedef NVNtextureHandle (*PFNNVNDEVICEGETTEXTUREHANDLEPROC)(const NVNdevice* device, int textureID, int samplerID);
extern PFNNVNDEVICEGETTEXTUREHANDLEPROC pfnc_nvnDeviceGetTextureHandle;
static inline NVNtextureHandle nvnDeviceGetTextureHandle(const NVNdevice* device, int textureID, int samplerID) { return pfnc_nvnDeviceGetTextureHandle(device, textureID, samplerID); }

typedef NVNimageHandle (*PFNNVNDEVICEGETIMAGEHANDLEPROC)(const NVNdevice* device, int imageID);
extern PFNNVNDEVICEGETIMAGEHANDLEPROC pfnc_nvnDeviceGetImageHandle;
static inline NVNimageHandle nvnDeviceGetImageHandle(const NVNdevice* device, int imageID) { return pfnc_nvnDeviceGetImageHandle(device, imageID); }

typedef void (*PFNNVNDEVICEBUILDERSETDEFAULTSPROC)(NVNdeviceBuilder* builder);
extern PFNNVNDEVICEBUILDERSETDEFAULTSPROC pfnc_nvnDeviceBuilderSetDefaults;
static inline void nvnDeviceBuilderSetDefaults(NVNdeviceBuilder* builder) { pfnc_nvnDeviceBuilderSetDefaults(builder); }

typedef void (*PFNNVNDEVICEBUILDERSETFLAGSPROC)(NVNdeviceBuilder* builder, int flags);
extern PFNNVNDEVICEBUILDERSETFLAGSPROC pfnc_nvnDeviceBuilderSetFlags;
static inline void nvnDeviceBuilderSetFlags(NVNdeviceBuilder* builder, int flags) { pfnc_nvnDeviceBuilderSetFlags(builder, flags); }

typedef NVNboolean (*PFNNVNDEVICEINITIALIZEPROC)(NVNdevice* device, const NVNdeviceBuilder* builder);
extern PFNNVNDEVICEINITIALIZEPROC pfnc_nvnDeviceInitialize;
static inline NVNboolean nvnDeviceInitialize(NVNdevice* device, const NVNdeviceBuilder* builder) { return pfnc_nvnDeviceInitialize(device, builder); }

typedef void (*PFNNVNDEVICEFINALIZEPROC)(NVNdevice* device);
extern PFNNVNDEVICEFINALIZEPROC pfnc_nvnDeviceFinalize;
static inline void nvnDeviceFinalize(NVNdevice* device) { pfnc_nvnDeviceFinalize(device); }

typedef void (*PFNNVNDEVICEGETINTEGERPROC)(const NVNdevice* device, NVNdeviceInfo pname, int* v);
extern PFNNVNDEVICEGETINTEGERPROC pfnc_nvnDeviceGetInteger;
static inline void nvnDeviceGetInteger(const NVNdevice* device, NVNdeviceInfo pname, int* v) { pfnc_nvnDeviceGetInteger(device, pname, v); }

typedef void (*PFNNVNDEVICESETWINDOWORIGINMODEPROC)(NVNdevice* device, NVNwindowOriginMode windowOriginMode);
extern PFNNVNDEVICESETWINDOWORIGINMODEPROC pfnc_nvnDeviceSetWindowOriginMode;
static inline void nvnDeviceSetWindowOriginMode(NVNdevice* device, NVNwindowOriginMode windowOriginMode) { pfnc_nvnDeviceSetWindowOriginMode(device, windowOriginMode); }

typedef void (*PFNNVNDEVICESETDEPTHMODEPROC)(NVNdevice* device, NVNdepthMode depthMode);
extern PFNNVNDEVICESETDEPTHMODEPROC pfnc_nvnDeviceSetDepthMode;
static inline void nvnDeviceSetDepthMode(NVNdevice* device, NVNdepthMode depthMode) { pfnc_nvnDeviceSetDepthMode(device, depthMode); }

typedef void (*PFNNVNQUEUEBUILDERSETDEVICEPROC)(NVNqueueBuilder* builder, NVNdevice* device);
extern PFNNVNQUEUEBUILDERSETDEVICEPROC pfnc_nvnQueueBuilderSetDevice;
static inline void nvnQueueBuilderSetDevice(NVNqueueBuilder* builder, NVNdevice* device) { pfnc_nvnQueueBuilderSetDevice(builder, device); }

typedef void (*PFNNVNQUEUEBUILDERSETDEFAULTSPROC)(NVNqueueBuilder* builder);
extern PFNNVNQUEUEBUILDERSETDEFAULTSPROC pfnc_nvnQueueBuilderSetDefaults;
static inline void nvnQueueBuilderSetDefaults(NVNqueueBuilder* builder) { pfnc_nvnQueueBuilderSetDefaults(builder); }

typedef void (*PFNNVNQUEUEBUILDERSETCOMMANDMEMORYSIZEPROC)(NVNqueueBuilder* builder, size_t size);
extern PFNNVNQUEUEBUILDERSETCOMMANDMEMORYSIZEPROC pfnc_nvnQueueBuilderSetCommandMemorySize;
static inline void nvnQueueBuilderSetCommandMemorySize(NVNqueueBuilder* builder, size_t size) { pfnc_nvnQueueBuilderSetCommandMemorySize(builder, size); }

typedef void (*PFNNVNQUEUEBUILDERSETCOMMANDFLUSHTHRESHOLDPROC)(NVNqueueBuilder* builder, size_t threshold);
extern PFNNVNQUEUEBUILDERSETCOMMANDFLUSHTHRESHOLDPROC pfnc_nvnQueueBuilderSetCommandFlushThreshold;
static inline void nvnQueueBuilderSetCommandFlushThreshold(NVNqueueBuilder* builder, size_t threshold) { pfnc_nvnQueueBuilderSetCommandFlushThreshold(builder, threshold); }

typedef NVNboolean (*PFNNVNQUEUEINITIALIZEPROC)(NVNqueue* queue, const NVNqueueBuilder* builder);
extern PFNNVNQUEUEINITIALIZEPROC pfnc_nvnQueueInitialize;
static inline NVNboolean nvnQueueInitialize(NVNqueue* queue, const NVNqueueBuilder* builder) { return pfnc_nvnQueueInitialize(queue, builder); }

typedef void (*PFNNVNQUEUEFINALIZEPROC)(NVNqueue* queue);
extern PFNNVNQUEUEFINALIZEPROC pfnc_nvnQueueFinalize;
static inline void nvnQueueFinalize(NVNqueue* queue) { pfnc_nvnQueueFinalize(queue); }

typedef NVNboolean (*PFNNVNTEXTUREPOOLINITIALIZEPROC)(NVNtexturePool* pool, const NVNmemoryPool* memoryPool, ptrdiff_t offset, int numDescriptors);
extern PFNNVNTEXTUREPOOLINITIALIZEPROC pfnc_nvnTexturePoolInitialize;
static inline NVNboolean nvnTexturePoolInitialize(NVNtexturePool* pool, const NVNmemoryPool* memoryPool, ptrdiff_t offset, int numDescriptors) { return pfnc_nvnTexturePoolInitialize(pool, memoryPool, offset, numDescriptors); }

typedef void (*PFNNVNTEXTUREPOOLFINALIZEPROC)(NVNtexturePool* pool);
extern PFNNVNTEXTUREPOOLFINALIZEPROC pfnc_nvnTexturePoolFinalize;
static inline void nvnTexturePoolFinalize(NVNtexturePool* pool) { pfnc_nvnTexturePoolFinalize(pool); }

typedef void (*PFNNVNTEXTUREPOOLREGISTERTEXTUREPROC)(const NVNtexturePool* pool, int id, const NVNtexture* texture, const NVNtextureView* view);
extern PFNNVNTEXTUREPOOLREGISTERTEXTUREPROC pfnc_nvnTexturePoolRegisterTexture;
static inline void nvnTexturePoolRegisterTexture(const NVNtexturePool* pool, int id, const NVNtexture* texture, const NVNtextureView* view) { pfnc_nvnTexturePoolRegisterTexture(pool, id, texture, view); }

typedef void (*PFNNVNTEXTUREPOOLREGISTERIMAGEPROC)(const NVNtexturePool* pool, int id, const NVNtexture* texture, const NVNtextureView* view);
extern PFNNVNTEXTUREPOOLREGISTERIMAGEPROC pfnc_nvnTexturePoolRegisterImage;
static inline void nvnTexturePoolRegisterImage(const NVNtexturePool* pool, int id, const NVNtexture* texture, const NVNtextureView* view) { pfnc_nvnTexturePoolRegisterImage(pool, id, texture, view); }

typedef void (*PFNNVNTEXTUREVIEWSETDEFAULTSPROC)(NVNtextureView* view);
extern PFNNVNTEXTUREVIEWSETDEFAULTSPROC pfnc_nvnTextureViewSetDefaults;
static inline void nvnTextureViewSetDefaults(NVNtextureView* view) { pfnc_nvnTextureViewSetDefaults(view); }

typedef void (*PFNNVNTEXTUREVIEWSETLEVELSPROC)(NVNtextureView* view, int baseLevel, int numLevels);
extern PFNNVNTEXTUREVIEWSETLEVELSPROC pfnc_nvnTextureViewSetLevels;
static inline void nvnTextureViewSetLevels(NVNtextureView* view, int baseLevel, int numLevels) { pfnc_nvnTextureViewSetLevels(view, baseLevel, numLevels); }

typedef void (*PFNNVNTEXTUREVIEWSETLAYERSPROC)(NVNtextureView* view, int minLayer, int numLayers);
extern PFNNVNTEXTUREVIEWSETLAYERSPROC pfnc_nvnTextureViewSetLayers;
static inline void nvnTextureViewSetLayers(NVNtextureView* view, int minLayer, int numLayers) { pfnc_nvnTextureViewSetLayers(view, minLayer, numLayers); }

typedef void (*PFNNVNTEXTUREVIEWSETFORMATPROC)(NVNtextureView* view, NVNformat format);
extern PFNNVNTEXTUREVIEWSETFORMATPROC pfnc_nvnTextureViewSetFormat;
static inline void nvnTextureViewSetFormat(NVNtextureView* view, NVNformat format) { pfnc_nvnTextureViewSetFormat(view, format); }

typedef void (*PFNNVNTEXTUREVIEWSETTARGETPROC)(NVNtextureView* view, NVNtextureTarget target);
extern PFNNVNTEXTUREVIEWSETTARGETPROC pfnc_nvnTextureViewSetTarget;
static inline void nvnTextureViewSetTarget(NVNtextureView* view, NVNtextureTarget target) { pfnc_nvnTextureViewSetTarget(view, target); }

typedef void (*PFNNVNPROGRAMFINALIZEPROC)(NVNprogram* program);
extern PFNNVNPROGRAMFINALIZEPROC pfnc_nvnProgramFinalize;
static inline void nvnProgramFinalize(NVNprogram* program) { pfnc_nvnProgramFinalize(program); }

typedef NVNboolean (*PFNNVNPROGRAMINITIALIZEPROC)(NVNprogram* program, NVNdevice* device);
extern PFNNVNPROGRAMINITIALIZEPROC pfnc_nvnProgramInitialize;
static inline NVNboolean nvnProgramInitialize(NVNprogram* program, NVNdevice* device) { return pfnc_nvnProgramInitialize(program, device); }

typedef NVNboolean (*PFNNVNPROGRAMSETSHADERSPROC)(NVNprogram* program, int count, const NVNshaderData* stageData);
extern PFNNVNPROGRAMSETSHADERSPROC pfnc_nvnProgramSetShaders;
static inline NVNboolean nvnProgramSetShaders(NVNprogram* program, int count, const NVNshaderData* stageData) { return pfnc_nvnProgramSetShaders(program, count, stageData); }

typedef void (*PFNNVNSAMPLERBUILDERSETDEFAULTSPROC)(NVNsamplerBuilder* builder);
extern PFNNVNSAMPLERBUILDERSETDEFAULTSPROC pfnc_nvnSamplerBuilderSetDefaults;
static inline void nvnSamplerBuilderSetDefaults(NVNsamplerBuilder* builder) { pfnc_nvnSamplerBuilderSetDefaults(builder); }

typedef void (*PFNNVNSAMPLERBUILDERSETDEVICEPROC)(NVNsamplerBuilder* builder, NVNdevice* device);
extern PFNNVNSAMPLERBUILDERSETDEVICEPROC pfnc_nvnSamplerBuilderSetDevice;
static inline void nvnSamplerBuilderSetDevice(NVNsamplerBuilder* builder, NVNdevice* device) { pfnc_nvnSamplerBuilderSetDevice(builder, device); }

typedef void (*PFNNVNSAMPLERBUILDERSETWRAPMODEPROC)(NVNsamplerBuilder* builder, NVNwrapMode s, NVNwrapMode t, NVNwrapMode r);
extern PFNNVNSAMPLERBUILDERSETWRAPMODEPROC pfnc_nvnSamplerBuilderSetWrapMode;
static inline void nvnSamplerBuilderSetWrapMode(NVNsamplerBuilder* builder, NVNwrapMode s, NVNwrapMode t, NVNwrapMode r) { pfnc_nvnSamplerBuilderSetWrapMode(builder, s, t, r); }

typedef void (*PFNNVNSAMPLERBUILDERSETMINMAGFILTERPROC)(NVNsamplerBuilder* builder, NVNminFilter min, NVNmagFilter mag);
extern PFNNVNSAMPLERBUILDERSETMINMAGFILTERPROC pfnc_nvnSamplerBuilderSetMinMagFilter;
static inline void nvnSamplerBuilderSetMinMagFilter(NVNsamplerBuilder* builder, NVNminFilter min, NVNmagFilter mag) { pfnc_nvnSamplerBuilderSetMinMagFilter(builder, min, mag); }

typedef void (*PFNNVNSAMPLERBUILDERSETMAXANISOTROPYPROC)(NVNsamplerBuilder* builder, float maxAniso);
extern PFNNVNSAMPLERBUILDERSETMAXANISOTROPYPROC pfnc_nvnSamplerBuilderSetMaxAnisotropy;
static inline void nvnSamplerBuilderSetMaxAnisotropy(NVNsamplerBuilder* builder, float maxAniso) { pfnc_nvnSamplerBuilderSetMaxAnisotropy(builder, maxAniso); }

typedef void (*PFNNVNSAMPLERBUILDERSETLODCLAMPPROC)(NVNsamplerBuilder* builder, float min, float max);
extern PFNNVNSAMPLERBUILDERSETLODCLAMPPROC pfnc_nvnSamplerBuilderSetLodClamp;
static inline void nvnSamplerBuilderSetLodClamp(NVNsamplerBuilder* builder, float min, float max) { pfnc_nvnSamplerBuilderSetLodClamp(builder, min, max); }

typedef void (*PFNNVNSAMPLERBUILDERSETLODBIASPROC)(NVNsamplerBuilder* builder, float bias);
extern PFNNVNSAMPLERBUILDERSETLODBIASPROC pfnc_nvnSamplerBuilderSetLodBias;
static inline void nvnSamplerBuilderSetLodBias(NVNsamplerBuilder* builder, float bias) { pfnc_nvnSamplerBuilderSetLodBias(builder, bias); }

typedef void (*PFNNVNSAMPLERBUILDERSETBORDERCOLORPROC)(NVNsamplerBuilder* builder, const float* borderColor);
extern PFNNVNSAMPLERBUILDERSETBORDERCOLORPROC pfnc_nvnSamplerBuilderSetBorderColor;
static inline void nvnSamplerBuilderSetBorderColor(NVNsamplerBuilder* builder, const float* borderColor) { pfnc_nvnSamplerBuilderSetBorderColor(builder, borderColor); }

typedef void (*PFNNVNSAMPLERBUILDERSETCOMPAREPROC)(NVNsamplerBuilder* builder, NVNcompareMode mode, NVNcompareFunc func);
extern PFNNVNSAMPLERBUILDERSETCOMPAREPROC pfnc_nvnSamplerBuilderSetCompare;
static inline void nvnSamplerBuilderSetCompare(NVNsamplerBuilder* builder, NVNcompareMode mode, NVNcompareFunc func) { pfnc_nvnSamplerBuilderSetCompare(builder, mode, func); }

typedef NVNboolean (*PFNNVNSAMPLERINITIALIZEPROC)(NVNsampler* sampler, const NVNsamplerBuilder* builder);
extern PFNNVNSAMPLERINITIALIZEPROC pfnc_nvnSamplerInitialize;
static inline NVNboolean nvnSamplerInitialize(NVNsampler* sampler, const NVNsamplerBuilder* builder) { return pfnc_nvnSamplerInitialize(sampler, builder); }

typedef void (*PFNNVNSAMPLERFINALIZEPROC)(NVNsampler* sampler);
extern PFNNVNSAMPLERFINALIZEPROC pfnc_nvnSamplerFinalize;
static inline void nvnSamplerFinalize(NVNsampler* sampler) { pfnc_nvnSamplerFinalize(sampler); }

typedef NVNboolean (*PFNNVNSAMPLERPOOLINITIALIZEPROC)(NVNsamplerPool* pool, const NVNmemoryPool* memoryPool, ptrdiff_t offset, int numDescriptors);
extern PFNNVNSAMPLERPOOLINITIALIZEPROC pfnc_nvnSamplerPoolInitialize;
static inline NVNboolean nvnSamplerPoolInitialize(NVNsamplerPool* pool, const NVNmemoryPool* memoryPool, ptrdiff_t offset, int numDescriptors) { return pfnc_nvnSamplerPoolInitialize(pool, memoryPool, offset, numDescriptors); }

typedef void (*PFNNVNSAMPLERPOOLFINALIZEPROC)(NVNsamplerPool* pool);
extern PFNNVNSAMPLERPOOLFINALIZEPROC pfnc_nvnSamplerPoolFinalize;
static inline void nvnSamplerPoolFinalize(NVNsamplerPool* pool) { pfnc_nvnSamplerPoolFinalize(pool); }

typedef void (*PFNNVNSAMPLERPOOLREGISTERSAMPLERPROC)(const NVNsamplerPool* pool, int id, const NVNsampler* sampler);
extern PFNNVNSAMPLERPOOLREGISTERSAMPLERPROC pfnc_nvnSamplerPoolRegisterSampler;
static inline void nvnSamplerPoolRegisterSampler(const NVNsamplerPool* pool, int id, const NVNsampler* sampler) { pfnc_nvnSamplerPoolRegisterSampler(pool, id, sampler); }

typedef void (*PFNNVNCOMMANDBUFFERSETTEXTUREPOOLPROC)(NVNcommandBuffer* cmdBuf, const NVNtexturePool* texturePool);
extern PFNNVNCOMMANDBUFFERSETTEXTUREPOOLPROC pfnc_nvnCommandBufferSetTexturePool;
static inline void nvnCommandBufferSetTexturePool(NVNcommandBuffer* cmdBuf, const NVNtexturePool* texturePool) { pfnc_nvnCommandBufferSetTexturePool(cmdBuf, texturePool); }

typedef void (*PFNNVNCOMMANDBUFFERSETSAMPLERPOOLPROC)(NVNcommandBuffer* cmdBuf, const NVNsamplerPool* samplerPool);
extern PFNNVNCOMMANDBUFFERSETSAMPLERPOOLPROC pfnc_nvnCommandBufferSetSamplerPool;
static inline void nvnCommandBufferSetSamplerPool(NVNcommandBuffer* cmdBuf, const NVNsamplerPool* samplerPool) { pfnc_nvnCommandBufferSetSamplerPool(cmdBuf, samplerPool); }

#endif
