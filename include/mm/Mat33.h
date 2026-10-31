#ifndef MM_MAT33_H
#define MM_MAT33_H

#include "math.h"

namespace mm {

// mm_lib's 3x3 matrix: nine floats in 0x30 bytes (mm::Mat33::identity's size), a 2D transform applied to row vectors
// (x, y, 1). Its inline members are known only by what UIParticleEmitter::update inlines; their names are not the
// original's.
class Mat33 {
public:
    // this times the rotation by angle about z
    void rotateZ(float angle) {
        float s = ::sinf(angle);
        float c = ::cosf(angle);
        for (int i = 0; i < 3; ++i) {
            float x = m[i][0];
            float y = m[i][1];
            float z = m[i][2];
            m[i][0] = x * c - y * s + z * 0.0f;
            m[i][1] = x * s + y * c + z * 0.0f;
            m[i][2] = x * 0.0f + y * 0.0f + z;
        }
    }
    // the point (x, y) through this
    void transform(float& x, float& y) const {
        float tx = x * m[0][0] + y * m[1][0] + m[2][0];
        float ty = x * m[0][1] + y * m[1][1] + m[2][1];
        x = tx;
        y = ty;
    }

    float m[3][3];

    static const Mat33 identity;
} __attribute__((aligned(16)));

}  // namespace mm

#endif
