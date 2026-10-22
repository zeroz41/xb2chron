#ifndef GRLIB_CGLIBACC2DTEXTURE_H
#define GRLIB_CGLIBACC2DTEXTURE_H

namespace grlib { class CGLibTextureBuffer; }

namespace grlib {

// write access to a 2D texture's texels while locked (0xA8 bytes: FontSys::construct keeps one on its stack)
class CGLibAcc2DTexture {
public:
    CGLibAcc2DTexture();
    ~CGLibAcc2DTexture();
    void lock(CGLibTextureBuffer& buffer);
    void unlock();
    // the texel at x, y set to value
    void setInt(int value, unsigned int x, unsigned int y);

    alignas(8) unsigned char pad_0[0xA8];
};

}  // namespace grlib

#endif
