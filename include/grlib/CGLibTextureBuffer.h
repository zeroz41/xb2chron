#ifndef GRLIB_CGLIBTEXTUREBUFFER_H
#define GRLIB_CGLIBTEXTUREBUFFER_H

#include "grlib/GrlTypes.h"

namespace grlib {

// a texture in GPU memory (0x70 bytes: ptlib::material::MaterialTexture keeps one from 0x40 to its end at 0xB0)
// Field names are not the original's: CGLibAccUtilTexture::setup2DTexutreInfo reads the format, the size of the
// level 0 image, the block-linear flag and the texel memory; CGLibAcc2DTexture::unlock flushes m_pData/m_dataSize.
class CGLibTextureBuffer {
public:
    CGLibTextureBuffer();
    ~CGLibTextureBuffer();
    bool isTexture1D() const;
    bool isTexture3D() const;
    bool isInitialized() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    GrlSurfaceFormat getFormat() const;
    // the texture's first texel (CGLibTexture::get1PixelTextureInfo)
    float get1PixelTextureInfo();
    unsigned int getMipmap() const;

    GrlSurfaceFormat m_format;     // 0x00
    unsigned short m_width;        // 0x04
    unsigned short m_height;       // 0x06
    unsigned char pad_8[0x4];
    unsigned short m_mipmap;       // 0x0C: getMipmap
    unsigned short m_type;         // 0x0E: 1 = 1D (isTexture1D), 5 = 3D (isTexture3D)
    unsigned int m_flags;          // 0x10: 1 = initialized, 0x20 = linear (not block-linear) layout
    unsigned char pad_14[0x14];
    unsigned char* m_pData;        // 0x28
    unsigned int m_dataSize;       // 0x30
    unsigned char pad_34[0x3C];
};

}  // namespace grlib

#endif
