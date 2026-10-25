#ifndef GRLIB_CGLIBRENDERTARGET_H
#define GRLIB_CGLIBRENDERTARGET_H

#include "nvn/nvn.h"

#include "grlib/GrlTypes.h"

namespace grlib { class CGLibTextureBuffer; }
namespace mm { struct Col4; }

namespace grlib {

// a colour buffer: the NVN texture drawing writes and the view CGLibState::setRegisterRenderTarget binds (the field
// names are not the original's; the size is not known, 0x40 is what its users prove)
class CGLibColorBuffer {
public:
    unsigned int getWidth() const;
    unsigned int getHeight() const;

    unsigned char pad_0[0x10];
    NVNtextureView m_view;  // 0x10
    const NVNtexture* m_pNvnTexture;  // 0x38
};

// a depth buffer (the field name is not the original's; the size is not known)
class CGLibDepthBuffer {
public:
    void invalidate();

    unsigned char pad_0[0x10];
    const NVNtexture* m_pNvnTexture;  // 0x10
};

// the render targets' base: DrPixlMan calls its setColorInvalidate on its CGLibRenderTarget objects (no fields
// known; that CGLibRenderTarget derives from it is inferred from those calls)
class CGLibRenderTargetBase {
public:
    void setColorInvalidate();
};

// a render target: the colour buffers drawing goes to (the field names are not the original's)
class CGLibRenderTarget : public CGLibRenderTargetBase {
public:
    // makes this target current, with up to two more (the other colour buffers)
    void setRenderTarget();
    void setRenderTarget(CGLibRenderTarget& target1);
    void setRenderTarget(CGLibRenderTarget& target1, CGLibRenderTarget& target2);
    // makes this target current with the depth buffer
    void setRenderTarget(CGLibDepthBuffer& depth);
    // clears the colour buffer's masked channels to color
    void clearTexture(const mm::Col4& color, GrlClaerMask mask);

    unsigned char pad_0[0x70];
    CGLibTextureBuffer* m_pTexture;  // its colour texture
    CGLibColorBuffer m_colorBuffer;  // 0x78
    unsigned char pad_B8[0x4];
    unsigned int m_width;  // 0xBC
    unsigned int m_height;  // 0xC0
    unsigned char pad_C4[0x304];  // 0x3C8 bytes: CGLibSystemContext holds an array of two
};

}  // namespace grlib

#endif
