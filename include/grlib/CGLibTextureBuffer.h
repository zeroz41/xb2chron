#ifndef GRLIB_CGLIBTEXTUREBUFFER_H
#define GRLIB_CGLIBTEXTUREBUFFER_H

namespace grlib {

// a texture in GPU memory (0x70 bytes: ptlib::material::MaterialTexture keeps one from 0x40 to its end at 0xB0)
class CGLibTextureBuffer {
public:
    CGLibTextureBuffer();
    ~CGLibTextureBuffer();
    bool isTexture3D() const;

    alignas(8) unsigned char pad_0[0x70];
};

}  // namespace grlib

#endif
