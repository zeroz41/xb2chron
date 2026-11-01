#ifndef GRLIB_CGLIBTEXTURE_H
#define GRLIB_CGLIBTEXTURE_H

#include "grlib/GrlTypes.h"

namespace grlib { class CGLibTextureBuffer; }
namespace grlib { class CGLibVtlMemPool; }
namespace grlib { class CGLibMemPool; }
namespace grlib { class CGLibDepthBuffer; }

namespace grlib {

// where a texture's channels come from (the field names are not the original's; ptlib's material manager uses
// 0 and 1 for the constants and 2 to 5 for the image's red to alpha)
struct CGLibTexSwizzle {
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
};

// the end of an image file, its last 0x38 bytes: the image's size, target, format and levels are its last 0x20
// (the struct and field names are not the original's; the code reaches the fields from the struct's start)
struct CGLibTexImageFooter {
    unsigned char pad_0[0x18];
    unsigned int m_width;     // 0x18
    unsigned int m_height;    // 0x1C
    unsigned int m_depth;     // 0x20
    unsigned int m_target;    // 0x24: NVNtextureTarget
    unsigned int m_format;    // 0x28: NVNformat
    unsigned int m_levels;    // 0x2C
    unsigned char pad_30[0x8];
};

// the platform part: the NVN texture of a buffer, its storage at offset of pool, and its descriptor ids (the
// parameter names are not the original's)
class CGLibTexture_plf {
public:
    // a 2D texture of mip + 1 levels; flags 8/0x10 of the buffer make it depth/stencil, 0x20 linear, 4 adds the
    // display flag
    static void setupTextureBuff(CGLibTextureBuffer& buffer, unsigned int width, unsigned int height,
                                 unsigned int mip, GrlSurfaceFormat format, CGLibMemPool& pool, unsigned int offset);
    static void setupCubemapTextureBuff(CGLibTextureBuffer& buffer, unsigned int width, unsigned int height,
                                        unsigned int mip, GrlSurfaceFormat format, CGLibMemPool& pool,
                                        unsigned int offset);
    static void setupVolumeTextureBuff(CGLibTextureBuffer& buffer, unsigned int width, unsigned int height,
                                       unsigned int depth, GrlSurfaceFormat format, CGLibMemPool& pool,
                                       unsigned int offset);
    static void setupCubeMapTextureArrayBuff(CGLibTextureBuffer& buffer, unsigned int width, unsigned int height,
                                             unsigned int arrayNum, unsigned int mip, GrlSurfaceFormat format,
                                             CGLibMemPool& pool, unsigned int offset);
    // a depth texture at offset of pool (1.0.0 names it; 3.0.1's callers inline it)
    static void setupDepthBuff(CGLibDepthBuffer& buffer, unsigned int width, unsigned int height,
                               GrlDepthFormat format, CGLibMemPool& pool, unsigned int offset);
    // frees the buffer's descriptor ids, takes a texture id (and an image id when image is set) and binds the
    // texture to them (1.0.0 names it; 3.0.1's callers inline it)
    static void allocTextureID(CGLibTextureBuffer& buffer, bool image);
};

class CGLibTexture {
public:
    // buffer made from an image file's size bytes
    static void createTextureImagePtrs(CGLibTextureBuffer& buffer, const void* image, unsigned int size, bool flag,
                                       const CGLibTexSwizzle* swizzle, bool flag2);
    // buffer made from an image of two parts (DrResMdoSeamTexture::createHeightTexture; the parameter names are not
    // the original's)
    static void createMixTextureImagePtrs(CGLibTextureBuffer& buffer, const void* image, unsigned int size,
                                          unsigned int size2, bool flag, const CGLibTexSwizzle* swizzle, bool flag2);
    // buffer made from the size bytes at offset of pool's memory (DrResMdoTexList; the parameter names are not the
    // original's)
    static void createTextureImagePtrs(CGLibTextureBuffer& buffer, unsigned int size, CGLibVtlMemPool& pool,
                                       unsigned int offset, bool flag, const CGLibTexSwizzle* swizzle, bool flag2);
    // the buffer's image moved to offset of pool's memory (DrResMdoTexList)
    static void changeTextureImagePtrs(CGLibTextureBuffer& buffer, unsigned int size, CGLibVtlMemPool& pool,
                                       unsigned int offset);
    // the buffer's image moved to new memory holding the same size bytes (DrResMdoSeamTexture::changeMemTexture)
    static void changeTextureImagePtrs(CGLibTextureBuffer& buffer, const void* image, unsigned int size);
    // as changeTextureImagePtrs for an image of two parts (the parameter names are not the original's)
    static void changeMixTextureImagePtrs(CGLibTextureBuffer& buffer, const void* image, unsigned int size,
                                          unsigned int size2);
    // buffer made empty, width by height texels of the format
    static void createTextureBuff(CGLibTextureBuffer& buffer, unsigned int width, unsigned int height,
                                  GrlSurfaceFormat format);
    // the mip levels down to a 4x4 block for a width by height texture (0 below 2, at most 17)
    static unsigned int getMipMapCnt(unsigned int width, unsigned int height);
    // the texture's first texel, into pValue (the return type is not known)
    static void get1PixelTextureInfo(float* pValue, CGLibTextureBuffer& buffer);
    // the bytes and the alignment a width by height texture of the format takes (the parameter names are not the
    // original's)
    static void getDefPixelSize(unsigned int& size, unsigned int& align, unsigned int width, unsigned int height,
                                unsigned int mip, GrlSurfaceFormat format);
    // the same for a cube map array of arrayNum cubes (the parameter names are not the original's)
    static void getArrayCubePixelSize(unsigned int& size, unsigned int& align, unsigned int width, unsigned int height,
                                      unsigned int arrayNum, unsigned int mip, GrlSurfaceFormat format);
    // the same for a depth texture without mips (the parameter names are not the original's)
    static void getDepthPixelSize(unsigned int& size, unsigned int& align, unsigned int width, unsigned int height,
                                  GrlDepthFormat format);
    // depth buffers of width by height texels: pixel memory of their own / the pixel pool's resident area at offset
    // (the parameter names are not the original's)
    static void createDepthBuff(CGLibDepthBuffer& buffer, unsigned int width, unsigned int height,
                                GrlDepthFormat format);
    static void createDepthBuff(CGLibDepthBuffer& buffer, unsigned int width, unsigned int height,
                                GrlDepthFormat format, unsigned int offset);
};

}  // namespace grlib

#endif
