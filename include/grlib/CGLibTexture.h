#ifndef GRLIB_CGLIBTEXTURE_H
#define GRLIB_CGLIBTEXTURE_H

#include "grlib/GrlTypes.h"

namespace grlib { class CGLibTextureBuffer; }

namespace grlib {

// where a texture's channels come from (the field names are not the original's; ptlib's material manager uses
// 0 and 1 for the constants and 2 to 5 for the image's red to alpha)
struct CGLibTexSwizzle {
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
};

class CGLibTexture {
public:
    // buffer made from an image file's size bytes
    static void createTextureImagePtrs(CGLibTextureBuffer& buffer, const void* image, unsigned int size, bool flag,
                                       const CGLibTexSwizzle* swizzle, bool flag2);
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
};

}  // namespace grlib

#endif
