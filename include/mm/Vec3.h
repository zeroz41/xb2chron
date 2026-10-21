#ifndef MM_VEC3_H
#define MM_VEC3_H

#include "math.h"

namespace mm {

// three floats in 16 bytes (Vec3::zero is 0x10 long), on a 16-byte boundary: a packet puts one after a float
// at the next multiple of 16 (GfMoveRunControler::Packet, GfMoveJumpBackControler::Packet). Its copies are
// its own (a Vec3 returns through x8, as a class that is not trivially copyable does) and copy x, y and z.
// The operations are inline, so their names are not the original's (none survives in a symbol).
class Vec3 {
public:
    Vec3() {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
    Vec3& operator=(const Vec3& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
    friend Vec3 operator*(float s, const Vec3& v) { return Vec3(s * v.x, s * v.y, s * v.z); }

    float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3 cross(const Vec3& v) const { return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
    float length() const { return ::sqrtf(x * x + y * y + z * z); }
    bool isZero() const { return ::fabsf(x) <= 1e-6f && ::fabsf(y) <= 1e-6f && ::fabsf(z) <= 1e-6f; }
    // to length 1; one too short for that becomes zero
    void normalize() {
        if (!isZero()) {
            float length = this->length();
            if (length <= 1e-6f) {
                *this = zero;
            } else {
                float scale = 1.0f / length;
                x = scale * x;
                y = scale * y;
                z = scale * z;
            }
        }
    }

    float x;
    float y;
    float z;

    static const Vec3 zero;
    static const Vec3 unitY;
} __attribute__((aligned(16)));

}  // namespace mm

#endif
