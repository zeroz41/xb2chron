#ifndef MM_VEC4_H
#define MM_VEC4_H

#include "mm/Vec3.h"

namespace mm {

// four floats in 16 bytes, on a 16-byte boundary. Its copies are its own: they copy x, y, z and w one by one
// (anm::QsTransform's copies do). The operations are inline, so their names are not the original's.
class Vec4 {
public:
    Vec4() {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vec4(const Vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    Vec4& operator=(const Vec4& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }
    // anm::BlendUtil's blends: each component scaled, and summed
    Vec4 operator+(const Vec4& v) const { return Vec4(x + v.x, y + v.y, z + v.z, w + v.w); }
    friend Vec4 operator*(float s, const Vec4& v) { return Vec4(s * v.x, s * v.y, s * v.z, s * v.w); }

    float x;
    float y;
    float z;
    float w;

    static const Vec4 zero;
    static const Vec4 unit;  // (1, 1, 1, 1): anm's samplers give a QsTransform it as its scale
} __attribute__((aligned(16)));

}  // namespace mm

#endif
