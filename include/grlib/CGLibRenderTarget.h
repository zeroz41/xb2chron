#ifndef GRLIB_CGLIBRENDERTARGET_H
#define GRLIB_CGLIBRENDERTARGET_H

#include "nvn/nvn.h"

#include "grlib/GrlTypes.h"
#include "grlib/CGLibTextureBuffer.h"

namespace mm { struct Col4; }

namespace grlib {

// a colour buffer: the NVN texture drawing writes and the view CGLibState::setRegisterRenderTarget binds (the field
// names are not the original's; the size is not known, 0x40 is what its users prove)
class CGLibColorBuffer {
public:
    // the render targets' constructors and destructors inline these (the name of release is not the original's)
    CGLibColorBuffer() : m_flags(0) {}
    ~CGLibColorBuffer() { release(); }
    void release() { m_flags &= ~1; }
    unsigned int getWidth() const;
    unsigned int getHeight() const;

    unsigned char pad_0[0x4];
    unsigned short m_width;   // 0x04
    unsigned short m_height;  // 0x06
    unsigned char pad_8[0x4];
    unsigned int m_flags;     // 0x0C: 1 = set up (cleared by release)
    NVNtextureView m_view;  // 0x10
    const NVNtexture* m_pNvnTexture;  // 0x38
};

// a depth buffer (the field name is not the original's; the size is not known)
class CGLibDepthBuffer {
public:
    void invalidate();
    unsigned int getWidth() const;
    unsigned int getHeight() const;

    unsigned char pad_0[0x4];
    unsigned short m_width;   // 0x04
    unsigned short m_height;  // 0x06
    unsigned char pad_8[0x8];
    const NVNtexture* m_pNvnTexture;  // 0x10
};

// the render targets' base: DrPixlMan calls its setColorInvalidate on its CGLibRenderTarget objects (that
// CGLibRenderTarget derives from it is inferred from those calls); every render target's constructor starts with
// a texture and a pointer to it (the field names are not the original's)
class CGLibRenderTargetBase {
public:
    CGLibRenderTargetBase() : m_pTexture(&m_texture) {}
    void setColorInvalidate();

    CGLibTextureBuffer m_texture;    // 0x00
    CGLibTextureBuffer* m_pTexture;  // 0x70: &m_texture
};

// a cube map array's render target: 6 faces x (m_arrayNum + 1) x m_mipNum colour buffers (the field names are
// not the original's)
class CGLibRenderArrayCubeMap : public CGLibRenderTargetBase {
public:
    CGLibRenderArrayCubeMap();
    ~CGLibRenderArrayCubeMap();
    void releaseWork();
    void setMipmapRenderTarget(GrlCubeMapFace face, unsigned int mip, unsigned int index);

    CGLibColorBuffer* m_pColorBuffers;  // 0x78
    bool m_isSetup;                     // 0x80: cleared by releaseWork
    unsigned int m_width;               // 0x84
    unsigned int m_height;              // 0x88
    unsigned int m_mipNum;              // 0x8C
    unsigned int m_arrayNum;            // 0x90
};

// a render target: the colour buffers drawing goes to (the field names are not the original's)
class CGLibRenderTarget : public CGLibRenderTargetBase {
public:
    CGLibRenderTarget();
    ~CGLibRenderTarget();
    // frees the textures once the GPU is done with them; releaseTexture also forgets the size
    void releaseWork();
    void release();
    void releaseTexture();
    // the texture's size and format, its pixels at offset in the pool (the parameter names are not the original's)
    void setTextureInfo(float width, float height, GrlSurfaceFormat format, bool flag, unsigned int offset);
    // makes this target current, with up to two more (the other colour buffers)
    void setRenderTarget();
    void setRenderTarget(CGLibRenderTarget& target1);
    void setRenderTarget(CGLibRenderTarget& target1, CGLibRenderTarget& target2);
    // makes this target current with the depth buffer
    void setRenderTarget(CGLibDepthBuffer& depth);
    void setRenderTarget(CGLibDepthBuffer& depth, CGLibRenderTarget& target1);
    void setRenderTarget(CGLibDepthBuffer& depth, CGLibRenderTarget& target1, CGLibRenderTarget& target2);
    // makes this target current with count more targets (MRT 1..count) and an optional depth buffer
    void setRenderTargetImpl(CGLibRenderTarget** targets, unsigned long count, CGLibDepthBuffer* depth);
    // clears the colour buffer's masked channels to color
    void clearTexture(const mm::Col4& color, GrlClaerMask mask);
    // clears the colour buffer's masked channels to the integer values
    void clearIntTexture(const int* values, GrlClaerMask mask);

    CGLibColorBuffer m_colorBuffer;  // 0x78
    bool m_isSetup;                  // 0xB8: cleared by releaseWork
    unsigned int m_width;  // 0xBC
    unsigned int m_height;  // 0xC0
    unsigned short m_mipNum;          // 0xC4: cleared by the destructor
    unsigned char m_mipWork[0x60];    // 0xC8: zeroed by the constructor (contents unknown)
    CGLibTextureBuffer m_mipTextures[6];  // 0x128 (0x3C8 bytes: CGLibDisplay holds an array of two)
};

// a volume texture's render target: one colour buffer per slice (the field names are not the original's)
class CGLibRenderVolume : public CGLibRenderTargetBase {
public:
    CGLibRenderVolume();
    ~CGLibRenderVolume();
    void releaseWork();
    // makes the slice current, with the same slice of other as the second colour buffer
    void setRenderTarget(unsigned int slice, CGLibRenderVolume& other);

    CGLibColorBuffer* m_pColorBuffers;  // 0x78
    bool m_isSetup;                     // 0x80
    unsigned int m_width;               // 0x84
    unsigned int m_height;              // 0x88
    unsigned int m_depth;               // 0x8C
};

// a cube map's render target with mip levels: a colour buffer per face and level (the field names are not the
// original's)
class CGLibRenderCubeMapMipMap : public CGLibRenderTargetBase {
public:
    CGLibRenderCubeMapMipMap();
    ~CGLibRenderCubeMapMipMap();
    // the faces' size and format, the pixels at offset in the pool (the parameter names are not the original's)
    void setTextureInfo(float width, float height, GrlSurfaceFormat format, bool flag, unsigned int offset);
    void releaseWork();
    void setRenderTarget(GrlCubeMapFace face, unsigned int mip);

    CGLibColorBuffer m_colorBuffers[6][16];  // 0x78
    bool m_isSetup;                          // 0x1878
    unsigned int m_mipNum;                   // 0x187C
};

// a depth render target (the field names are not the original's; the fields from 0x8 to 0x120, among them
// textures, are not known yet)
class CGLibDepthTarget {
public:
    // out of line (CGLibUniBaseUtility's unit); CGLibDisplay's constructor and destructor call them
    CGLibDepthTarget();
    ~CGLibDepthTarget();
    void releaseWork();
    void release();
    // clears the depth buffer (CGLibDepthCtl::clearDepthBuffer)
    void clearDepth(bool);
    // makes the depth buffer current, with no colour buffer
    void setRenderTarget();

    unsigned int m_width;   // 0x00
    unsigned int m_height;  // 0x04
    unsigned char pad_8[0x118];
    CGLibDepthBuffer* m_pDepthBuffer;  // 0x120
    unsigned char pad_128[0x8];
    // 0x130: the texture DrMdoSetup::fn_710077C23C binds (DrPixlMan::getDepthObj's); the name is not the original's
    CGLibTextureBuffer* m_pTexture;
    // 0x138..0x800: the constructor builds CGLibVtlMemPools up to 0x7D8 (0x800 bytes: CGLibDisplay's memory pool
    // follows it at 0x800, SHCACHE_WORK_TBL ends 0x800 after its one)
    unsigned char pad_138[0x6C8];
};

}  // namespace grlib

#endif
