#ifndef MM_VEC3_H
#define MM_VEC3_H

#include "math.h"

namespace mm {

// three floats in 16 bytes (Vec3::zero is 0x10 long), on a 16-byte boundary: a packet puts one after a float
// at the next multiple of 16 (GfMoveRunControler::Packet, GfMoveJumpBackControler::Packet). Its copies are
// its own (a Vec3 returns through x8, as a class that is not trivially copyable does) and copy x, y and z.
// By value it is passed indirectly too (btl::HateRingManager::UpdateRing(int, Vec3, Vec3) takes x2/x3 pointers).
// A copy whose loads come before its stores (a by-value argument's temporary, two fields of one object, a getter's
// value, a const global) reads x and y as ONE 64-bit load (`ldr x; lsr`: GVN widens the 16-aligned x load); the
// same copy from a float[3] or a 4-aligned pointer, or with a may-alias store in between, is three ldr w.
// The operations are inline, so their names are not the original's (none survives in a symbol).
class Vec3 {
public:
    Vec3() {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3(const Vec3& v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    Vec3& operator=(const Vec3& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    // each sum loads its own component first (ConpoundWind::calcWind's order), which `x += v.x` would not
    Vec3& operator+=(const Vec3& v) {
        x = x + v.x;
        y = y + v.y;
        z = z + v.z;
        return *this;
    }
    // likewise (CalcUtil::addForceSpring loads, subtracts and stores each component in turn)
    Vec3& operator-=(const Vec3& v) {
        x = x - v.x;
        y = y - v.y;
        z = z - v.z;
        return *this;
    }
    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
    friend Vec3 operator*(float s, const Vec3& v) { return Vec3(s * v.x, s * v.y, s * v.z); }

    // this = -v (the name is not the original's)
    void setV(Vec3 v) { *this = v; }
    void setNeg(Vec3 v) {
        x = -v.x;
        y = -v.y;
        z = -v.z;
    }

    float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3 cross(const Vec3& v) const { return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
    float length() const { return ::sqrtf(x * x + y * y + z * z); }
    // a component infinite or NaN, or the 0xCCCCCCCC of uninitialized memory (ptlib's "!outPos.isError()")
    bool isError() const { return !(isValid(x) && isValid(y) && isValid(z)); }
    static bool isValid(float f) {
        union {
            float f;
            unsigned int bits;
        } value;
        value.f = f;
        return value.bits != 0xCCCCCCCC && (value.bits & 0x7F800000) != 0x7F800000;
    }
    // each component within 1e-6 of other's (as Col3::isEqual; inline, so the name is not the original's)
    bool isEqual(const Vec3& other) const {
        return ::fabsf(other.x - x) <= 1e-6f && ::fabsf(other.y - y) <= 1e-6f && ::fabsf(other.z - z) <= 1e-6f;
    }
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
    static const Vec3 unit;  // (1, 1, 1)
    static const Vec3 unitX;
    static const Vec3 unitY;
    static const Vec3 unitZ;
} __attribute__((aligned(16)));

}  // namespace mm

#endif
