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
};

class CGLibCtlShader {
public:
    static void setShader(CGLibDecShader& shader, CGLibVtxFetch& fetch);
    static void setMemoryBarrierBit(unsigned int bits);
};

class CGLibCtlTexture {
public:
    static void setTexture(const CGLibTextureBuffer& texture, const CGLibSampler& sampler, unsigned int location);
};

class CGLibColorCtl {
public:
    static void setMrtBlend(unsigned char mask, GrlLogicType logic);
    static void setMrtBlendControl(GrlMrtType mrt, GrlBlendFunc src, GrlBlendFunc dst, GrlBlendCombine combine);
    static void setBlendOffControl(GrlLogicType logic);
};

}  // namespace grlib

#endif
