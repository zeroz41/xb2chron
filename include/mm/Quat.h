#ifndef MM_QUAT_H
#define MM_QUAT_H

#include "math.h"
#include "mm/MMStdBase.h"
#include "mm/Vec3.h"

// mm_lib's mm_math/mm_quat_impl_nx.h, as the including file's include path named it (see mm/Math.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_QUAT_IMPL_PATH "../../../mcl/mm_lib/source\\mm_math/mm_quat_impl_nx.h"
#else
#define MM_QUAT_IMPL_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_math/mm_quat_impl_nx.h"
#endif

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
        // the second product's terms in the original's order (GfComPropertyEvent::procMsgObjectGetVelocity)
        return Vec3((-(z * ty) + y * tz - x * tw) + w * tx, (-(x * tz) + z * tx - y * tw) + w * ty,
                    (-(y * tx) + x * ty - z * tw) + w * tz);
    }

    // rotate(v) written into out a component at a time: fw::WindForceCalculator::calcForce's node positions store
    // x alone, then y and z, and schedule the products so (the name is not the original's: every mm::Quat member is
    // inlined)
    void rotate(Vec3& out, const Vec3& v) const {
        float tx = (y * v.z - z * v.y) + w * v.x;
        float ty = (z * v.x - x * v.z) + w * v.y;
        float tz = (x * v.y - y * v.x) + w * v.z;
        float tw = -x * v.x - y * v.y - z * v.z;
        out.x = (-(z * ty) + y * tz - x * tw) + w * tx;
        out.y = (-(x * tz) + z * tx - y * tw) + w * ty;
        out.z = (-(y * tx) + x * ty - z * tw) + w * tz;
    }

    // the opposite rotation: qa's conjugate over its squared length (mm_quat_impl_nx.h asserts `!qa.isZero()`)
    static __attribute__((always_inline)) Quat inverse(const Quat& qa) {
#line 86 MM_QUAT_IMPL_PATH
        MM_ASSERT(!qa.isZero());
        float scale = 1.0f / (qa.x * qa.x + qa.y * qa.y + qa.z * qa.z + qa.w * qa.w);
        return Quat(-qa.x * scale, -qa.y * scale, -qa.z * scale, qa.w * scale);
    }

    // every component a number: none infinite or NaN, none the 0xCCCCCCCC of uninitialized memory
    bool isValid() const { return isValid(x) && isValid(y) && isValid(z) && isValid(w); }
    static bool isValid(float f) {
        union {
            float f;
            unsigned int bits;
        } value;
        value.f = f;
        return value.bits != 0xCCCCCCCC && (value.bits & 0x7F800000) != 0x7F800000;
    }

    // qb's rotation, then qa's; an invalid operand is printed (BlowRotateIkSolver::calcIK inlines it)
    friend __attribute__((always_inline)) Quat operator*(const Quat& qa, const Quat& qb) {
        if (!qa.isValid()) {
            ::mm::MMStdBase::mmPrint("qa[%f %f %f %f]\n", qa.x, qa.y, qa.z, qa.w);
        }
        if (!qb.isValid()) {
            ::mm::MMStdBase::mmPrint("qb[%f %f %f %f]\n", qb.x, qb.y, qb.z, qb.w);
        }
        return Quat(qb.y * qa.z - qb.z * qa.y + qa.x * qb.w + qb.x * qa.w,
                    qb.z * qa.x - qb.x * qa.z + qa.y * qb.w + qb.y * qa.w,
                    qb.x * qa.y - qb.y * qa.x + qa.z * qb.w + qb.z * qa.w,
                    qb.w * qa.w - qb.x * qa.x - qb.y * qa.y - qb.z * qa.z);
    }

    // anm::BlendUtil's blends: each component scaled, and summed (not rotations)
    Quat operator+(const Quat& q) const { return Quat(x + q.x, y + q.y, z + q.z, w + q.w); }
    Quat operator*(float s) const { return Quat(x * s, y * s, z * s, w * s); }
    friend Quat operator*(float s, const Quat& q) { return Quat(s * q.x, s * q.y, s * q.z, s * q.w); }

    float x;
    float y;
    float z;
    float w;

    static const Quat zero;
    static const Quat identity;
} __attribute__((aligned(16)));

}  // namespace mm

#endif
