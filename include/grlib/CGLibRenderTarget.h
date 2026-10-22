#ifndef GRLIB_CGLIBRENDERTARGET_H
#define GRLIB_CGLIBRENDERTARGET_H

namespace grlib { class CGLibTextureBuffer; }

namespace grlib {

// a render target: the colour buffers drawing goes to (the field names are not the original's)
class CGLibRenderTarget {
public:
    // makes this target current, with up to two more (the other colour buffers)
    void setRenderTarget();
    void setRenderTarget(CGLibRenderTarget& target1);
    void setRenderTarget(CGLibRenderTarget& target1, CGLibRenderTarget& target2);

    unsigned char pad_0[0x70];
    CGLibTextureBuffer* m_pTexture;  // its colour texture
    unsigned char pad_78[0x44];
    unsigned int m_width;
    unsigned int m_height;
};

}  // namespace grlib

#endif
