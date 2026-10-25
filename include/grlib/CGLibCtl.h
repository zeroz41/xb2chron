#ifndef GRLIB_CGLIBCTL_H
#define GRLIB_CGLIBCTL_H

#include "grlib/GrlTypes.h"

namespace grlib { class CGLibDecShader; class CGLibSampler; class CGLibTextureBuffer; class CGLibVtxFetch; }
namespace grlib { class CGLibVtxVertex; class CGLibVtxInstans; class CGLibVtxOneInstans; class CGLibVtxStmOut; class CGLibOneUniformBlock; }
namespace grlib { class CGLibColorBuffer; class CGLibDecShader; class CGLibDecShdExtTbl; class CGLibDepthBuffer; }
namespace mtl { class ALLOC_HANDLE; }
namespace mm { struct Col4; }

namespace grlib {

// the current drawing state's setters
class CGLibCtlVertex {
public:
    static void setVertex(CGLibVtxVertex& vertex);
    // binds the vertex buffer from offset bytes on
    static void setVertex(CGLibVtxVertex& vertex, unsigned int offset);
    // binds the vertex buffer (from offset bytes on) as stream slot, divisor its instance step (the parameter
    // names are not the original's)
    static void setAddVertex(CGLibVtxVertex& vertex, int offset, int slot, unsigned int divisor);
    static void setUniformVertex(CGLibOneUniformBlock& block, int stride, int offset, int slot, unsigned int divisor);
    static void setStreamOutVertex(CGLibVtxStmOut& vertex, int stride, int offset, int slot, unsigned int divisor);
    // draws count vertices of the bound vertex buffer as the primitive type (once per instance)
    static void renderVertex(GrlPrimitiveType type, int count);
    static void renderInstanceVertex(GrlPrimitiveType type, int count, int instances);
    // binds an instance vertex buffer (layer::LayerShdManager::setupInstaceVertex passes 1, 1 for the last two;
    // the parameter names are not the original's)
    static void setInstanceVertex(CGLibVtxInstans& vertex, int first, int count, int step, unsigned int slot);
    static void setInstanceVertex(CGLibVtxOneInstans& vertex, int first, int count, int step, unsigned int slot);
};

class CGLibCtlShader {
public:
    static void setShader(CGLibDecShader& shader, CGLibVtxFetch& fetch);
    static void setShader(CGLibDecShdExtTbl& table, CGLibVtxFetch& fetch);
    static void setComputeShader(CGLibDecShader& shader);
    static void setDispatchCompute(unsigned int x, unsigned int y, unsigned int z);
    static void setMemoryBarrier();
    static void setMemoryBarrierBit(unsigned int bits);
    // the system context's shared shader, vertex fetch objects and samplers
    static CGLibDecShader* getDecShader();
    static CGLibVtxFetch* getVtxFetch(GrlUtilVertFetch fetch);
    static CGLibSampler* getSampler(GrlUtilSampler sampler);
};

class CGLibCtlTexture {
public:
    static void setTexture(const CGLibTextureBuffer& texture, const CGLibSampler& sampler, unsigned int location);
    static void setUAVTexture(const CGLibTextureBuffer& texture, unsigned int location, unsigned int, unsigned int);
};

class CGLibColorCtl {
public:
    static void setColorBufferOn();
    static void setColorBufferOff();
    static void setColorChannelMask(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    // blending on for the colour targets whose bit is set in mask
    static void setMrtBlend(unsigned char mask, GrlLogicType logic);
    static void setMrtBlendControl(GrlMrtType mrt, GrlBlendFunc src, GrlBlendFunc dst, GrlBlendCombine combine);
    static void setMrtBlendControl(GrlMrtType mrt, GrlBlendFunc colorSrc, GrlBlendFunc colorDst,
                                   GrlBlendCombine colorCombine, GrlBlendFunc alphaSrc, GrlBlendFunc alphaDst,
                                   GrlBlendCombine alphaCombine);
    static void setColorChannelMask(GrlMrtType mrt, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    // clears the current main render target's colour buffer
    static void clearMainFrameBuffer(const mm::Col4& color);
    static void setBlendOffControl(GrlLogicType logic);
    static void setBlendControl(GrlBlendFunc src, GrlBlendFunc dst, GrlBlendCombine combine, GrlLogicType logic);
    // the colour then the alpha source, destination and combine (layer::LayerShdManager's setupBlend functions)
    static void setBlendControl(GrlBlendFunc colorSrc, GrlBlendFunc colorDst, GrlBlendCombine colorCombine,
                                GrlBlendFunc alphaSrc, GrlBlendFunc alphaDst, GrlBlendCombine alphaCombine,
                                GrlLogicType logic);
};

class CGLibDepthCtl {
public:
    // depth test on/off, depth write on/off, the comparison (layer::LayerShdManager::setDepthBufferCheckOn/Off;
    // the parameter names are not the original's)
    static void setDepthControl(unsigned char test, unsigned char write, GrlCompare compare);
    static void clearColorBuffer(CGLibColorBuffer& buffer, const mm::Col4& color, GrlClaerMask mask);
    static void clearIntColorBuffer(CGLibColorBuffer& buffer, const int* values, GrlClaerMask mask);
    // clears the depth buffer (what the flag selects is not known)
    static void clearDepthBuffer(CGLibDepthBuffer& buffer, bool);
};
class CGLibPolygon {
public:
    static void setCullingOff();
    static void setCullingFront();
    static void setCullingBack();
    static void setCullingDispOff();
    static void setLineWidth(float width);
    // discards the rasterizer's output while set
    static void setRasterizer(unsigned char discard);
};

class CGLibGPUCache {
public:
    static void setTiledCacheSize(unsigned int width, unsigned int height);
    static void setTiledCacheAction(GrlTiledCacheAction action);
    static void depthInvalidate(CGLibDepthBuffer& buffer);
    // the system context's CGLibMemPoolAdder adds or releases a pool
    static void setMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
    static void setMemPoolBuffer(void* buffer, unsigned int size);
    static void releaseMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
    static void releaseMemPoolBuffer(void* buffer);
};

}  // namespace grlib

#endif
