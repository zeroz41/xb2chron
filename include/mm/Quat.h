#ifndef MM_QUAT_H
#define MM_QUAT_H

#include "math.h"
#include "mm/Vec3.h"

namespace mm {

// a rotation as a quaternion: four floats in 16 bytes (Quat::zero is 0x10 long). The operations are inline, so
// their names are not the original's (none survives in a symbol).
class Quat {
public:
    Quat() {}
    Quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    // each component within 1e-6 of zero's
    bool isZero() const {
        return ::fabsf(zero.x - x) <= 1e-6f && ::fabsf(zero.y - y) <= 1e-6f && ::fabsf(zero.z - z) <= 1e-6f &&
               ::fabsf(zero.w - w) <= 1e-6f;
    }

    // v turned by this rotation: this * v * this's conjugate, v a quaternion with no real part
    Vec3 rotate(const Vec3& v) const {
        float tx = (y * v.z - z * v.y) + w * v.x;
        float ty = (z * v.x - x * v.z) + w * v.y;
        float tz = (x * v.y - y * v.x) + w * v.z;
        float tw = -x * v.x - y * v.y - z * v.z;
        return Vec3(((y * tz - z * ty) - x * tw) + w * tx, ((z * tx - x * tz) - y * tw) + w * ty,
                    ((x * ty - y * tx) - z * tw) + w * tz);
    }

    float x;
    float y;
    float z;
    float w;

    static const Quat zero;
} __attribute__((aligned(16)));

}  // namespace mm

#endif
