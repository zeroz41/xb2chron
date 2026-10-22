#ifndef PTLIB_UTILITY_H
#define PTLIB_UTILITY_H

namespace mm { class Vec3; }

namespace ptlib {

// helpers the particle code shares (particle_intrusive_list.cpp)
class Utility {
public:
    // a colour (x, y, z = red, green, blue in [0, 1]) and an alpha in [0, 1], clamped, as bytes r | g << 8 |
    // b << 16 | a << 24
    static unsigned int conv_rgba(mm::Vec3* color, float alpha);
};

}  // namespace ptlib

#endif
