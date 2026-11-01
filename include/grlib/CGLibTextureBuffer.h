#ifndef GRLIB_CGLIBTEXTUREBUFFER_H
#define GRLIB_CGLIBTEXTUREBUFFER_H

#include "grlib/GrlTypes.h"
#include "grlib/CGLibVtlMemPool.h"
#include "nvn/nvn.h"

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
    unsigned short getMipmap() const;  // ml::DrAPCache::setMipMapOn tests only its low 16 bits
    // frees the texture, its memory and its descriptor ids now / once the GPU is done with them
    void release();
    void delayRelease();

    GrlSurfaceFormat m_format;     // 0x00
    unsigned short m_width;        // 0x04
    unsigned short m_height;       // 0x06
    unsigned short m_depth;        // 0x08: a 3D texture's depth (setupVolumeTextureBuff; the name is not the original's)
    unsigned short m_arrayNum;     // 0x0A: a cube map array's cubes (setupCubeMapTextureArrayBuff; the name is not the original's)
    unsigned short m_mipmap;       // 0x0C: getMipmap
    unsigned short m_type;         // 0x0E: 0 = 2D, 1 = 1D (isTexture1D), 3 = cube map, 4 = cube map array, 5 = 3D (isTexture3D)
    unsigned int m_flags;          // 0x10: 1 = initialized, 2 = owns m_pData, 0x20 = linear (not block-linear) layout
    unsigned char pad_14[0x4];
    NVNtexture* m_pNvnTexture;     // 0x18: from CGLibSystemContext::m_textureAlloc
    void* m_pStorage;              // 0x20: the texture's memory (pool memory + offset, setupTextureBuff)
    unsigned char* m_pData;        // 0x28
    unsigned int m_dataSize;       // 0x30
    int m_textureId;               // 0x34: CGLibSystemContext::m_texDescriptor ids, -1 = none
    int m_samplerId;               // 0x38
    unsigned char pad_3C[0x4];
    CGLibVtlMemPool m_memPool;     // 0x40
};

}  // namespace grlib

#endif
