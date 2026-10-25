#ifndef GRLIB_CGLIBCTL_H
#define GRLIB_CGLIBCTL_H

#include "grlib/GrlTypes.h"

namespace grlib { class CGLibDecShader; class CGLibSampler; class CGLibTextureBuffer; class CGLibVtxFetch; }
namespace grlib { class CGLibVtxVertex; class CGLibVtxInstans; class CGLibVtxOneInstans; }

namespace grlib {

// the current drawing state's setters
class CGLibCtlVertex {
public:
    static void setVertex(CGLibVtxVertex& vertex);
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
};
class CGLibPolygon {
public:
    static void setCullingOff();
    static void setCullingFront();
    static void setCullingBack();
};

}  // namespace grlib

#endif
