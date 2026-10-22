#ifndef GRLIB_CGLIBTEXTURE_H
#define GRLIB_CGLIBTEXTURE_H

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
};

}  // namespace grlib

#endif
