#ifndef GRLIB_CGLIBCTL_H
#define GRLIB_CGLIBCTL_H

#include "grlib/GrlTypes.h"

namespace grlib { class CGLibDecShader; class CGLibSampler; class CGLibTextureBuffer; class CGLibVtxFetch; }
namespace grlib { class CGLibVtxVertex; }

namespace grlib {

// the current drawing state's setters
class CGLibCtlVertex {
public:
    static void setVertex(CGLibVtxVertex& vertex);
    // draws count vertices of the bound vertex buffer as the primitive type (once per instance)
    static void renderVertex(GrlPrimitiveType type, int count);
    static void renderInstanceVertex(GrlPrimitiveType type, int count, int instances);
};

class CGLibCtlShader {
public:
    static void setShader(CGLibDecShader& shader, CGLibVtxFetch& fetch);
    static void setComputeShader(CGLibDecShader& shader);
    static void setMemoryBarrierBit(unsigned int bits);
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
    static void setMrtBlend(unsigned char mask, GrlLogicType logic);
    static void setMrtBlendControl(GrlMrtType mrt, GrlBlendFunc src, GrlBlendFunc dst, GrlBlendCombine combine);
    static void setBlendOffControl(GrlLogicType logic);
};

class CGLibPolygon {
public:
    static void setCullingOff();
    static void setCullingFront();
    static void setCullingBack();
};

}  // namespace grlib

#endif
