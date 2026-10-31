#ifndef MM_MAT44_H
#define MM_MAT44_H

#include <stddef.h>
#include <string.h>
#include "mm/MMStdBase.h"
#include "mm/Math.h"
#include "mm/Vec3.h"
#include <math.h>

// mm_lib's mm_math/mm_mat44.h, as the including file's include path named it (see mm/Math.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MAT44_PATH "../../../mcl/mm_lib/source\\mm_math/mm_mat44.h"
#elif defined(MM_LIB_FROM_MONOLIB_MM)
// monolib_mm's (CacheDraw::setMatrix's command copy cites it so)
#define MM_MAT44_PATH \
    "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../../MCL/mm_lib/source\\mm_math/mm_mat44.h"
#elif defined(MM_LIB_FROM_XBRD)
// xbrd's (ScnObjModelDrSysStandard::apply's matrix copy cites it so)
#define MM_MAT44_PATH "D:/Monolithsoft/BF2/prog/libs/xbrd/proj/windows/../../../mcl/mm_lib/source\\mm_math/mm_mat44.h"
#else
#define MM_MAT44_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_math/mm_mat44.h"
#endif

// the alignment a matrix keeps (its copy asserts it of the source)
#define MM_MAT_ALIGN 16

namespace mm {

// a 4x4 matrix: 0x40 bytes, copied whole (Obb::setMat copies one with a 0x40-byte memcpy). Its rows are
// laid out as Sphere::getOBB builds one on its stack, the translation in the last. A copy made by
// construction first asserts the source's alignment (mm_mat44.h line 195; ColiMoveObject::postUpdate).
class Mat44 {
public:
    Mat44() {}
    Mat44(const Mat44& ma) {
#line 195 MM_MAT44_PATH
        MM_ASSERT((reinterpret_cast<size_t>(&ma) & size_t(MM_MAT_ALIGN - 1)) == 0);
        memcpy(this, &ma, sizeof(Mat44));
    }
    Mat44& operator=(const Mat44& ma) = default;

    // the rotation by euler angles r (radians): x first, then y, then z, rows as AGmkBase::getMatrix and
    // gmk::Xform::toMatrix store them (the name is not the original's)
    void setRotXYZ(Vec3 r) {
        float sx = ::sinf(r.x);
        float cx = ::cosf(r.x);
        float sy = ::sinf(r.y);
        float cy = ::cosf(r.y);
        float sz = ::sinf(r.z);
        float cz = ::cosf(r.z);
        m[0][0] = cy * cz;
        m[0][1] = cy * sz;
        m[0][2] = -sy;
        m[0][3] = 0.0f;
        m[1][0] = sx * sy * cz - cx * sz;
        m[1][1] = sx * sy * sz + cx * cz;
        m[1][2] = sx * cy;
        m[1][3] = 0.0f;
        m[2][0] = cx * sy * cz + sx * sz;
        m[2][1] = cx * sy * sz - sx * cz;
        m[2][2] = cx * cy;
        m[2][3] = 0.0f;
        m[3][0] = 0.0f;
        m[3][1] = 0.0f;
        m[3][2] = 0.0f;
        m[3][3] = 1.0f;
    }
    // the rotation by angle about y (TGmkList::createGmk's placement; the name is not the original's)
    void setRotY(float angle) {
        float s = ::sinf(angle);
        float c = ::cosf(angle);
        m[0][0] = c;
        m[0][1] = 0.0f;
        m[0][2] = -s;
        m[0][3] = 0.0f;
        m[1][0] = 0.0f;
        m[1][1] = 1.0f;
        m[1][2] = 0.0f;
        m[1][3] = 0.0f;
        m[2][0] = s;
        m[2][1] = 0.0f;
        m[2][2] = c;
        m[2][3] = 0.0f;
        m[3][0] = 0.0f;
        m[3][1] = 0.0f;
        m[3][2] = 0.0f;
        m[3][3] = 1.0f;
    }
    // the translation by v (the name is not the original's)
    void setTrans(Vec3 v) {
        m[0][0] = 1.0f;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;
        m[0][3] = 0.0f;
        m[1][0] = 0.0f;
        m[1][1] = 1.0f;
        m[1][2] = 0.0f;
        m[1][3] = 0.0f;
        m[2][0] = 0.0f;
        m[2][1] = 0.0f;
        m[2][2] = 1.0f;
        m[2][3] = 0.0f;
        m[3][0] = v.x;
        m[3][1] = v.y;
        m[3][2] = v.z;
        m[3][3] = 1.0f;
    }
    // the scale by v (the name is not the original's)
    void setScale(Vec3 v) {
        m[0][0] = v.x;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;
        m[0][3] = 0.0f;
        m[1][0] = 0.0f;
        m[1][1] = v.y;
        m[1][2] = 0.0f;
        m[1][3] = 0.0f;
        m[2][0] = 0.0f;
        m[2][1] = 0.0f;
        m[2][2] = v.z;
        m[2][3] = 0.0f;
        m[3][0] = 0.0f;
        m[3][1] = 0.0f;
        m[3][2] = 0.0f;
        m[3][3] = 1.0f;
    }
    // moves the translation by (x, y, z) (the name is not the original's)
    // the translation moved by v (the name is not the original's)
    void addTrans(Vec3 v) {
        m[3][0] += v.x;
        m[3][1] += v.y;
        m[3][2] += v.z;
    }
    // its translation row (the name is not the original's)
    Vec3 getTrans() const { return Vec3(m[3][0], m[3][1], m[3][2]); }
    // this = ma * mb (the name is not the original's)
    __attribute__((always_inline)) void mul(const Mat44& ma, const Mat44& mb) { *this = ma * mb; }
    void addTrans(float x, float y, float z) {
        m[3][0] += x;
        m[3][1] += y;
        m[3][2] += z;
    }
    // this times mb, every element a full four-term sum (the 0 and 1 terms are not folded away in its users)
    friend __attribute__((always_inline)) Mat44 operator*(const Mat44& ma, const Mat44& mb) {
        Mat44 r;
        r.m[0][0] = ma.m[0][0] * mb.m[0][0] + ma.m[0][1] * mb.m[1][0] + ma.m[0][2] * mb.m[2][0] + ma.m[0][3] * mb.m[3][0];
        r.m[0][1] = ma.m[0][0] * mb.m[0][1] + ma.m[0][1] * mb.m[1][1] + ma.m[0][2] * mb.m[2][1] + ma.m[0][3] * mb.m[3][1];
        r.m[0][2] = ma.m[0][0] * mb.m[0][2] + ma.m[0][1] * mb.m[1][2] + ma.m[0][2] * mb.m[2][2] + ma.m[0][3] * mb.m[3][2];
        r.m[0][3] = ma.m[0][0] * mb.m[0][3] + ma.m[0][1] * mb.m[1][3] + ma.m[0][2] * mb.m[2][3] + ma.m[0][3] * mb.m[3][3];
        r.m[1][0] = ma.m[1][0] * mb.m[0][0] + ma.m[1][1] * mb.m[1][0] + ma.m[1][2] * mb.m[2][0] + ma.m[1][3] * mb.m[3][0];
        r.m[1][1] = ma.m[1][0] * mb.m[0][1] + ma.m[1][1] * mb.m[1][1] + ma.m[1][2] * mb.m[2][1] + ma.m[1][3] * mb.m[3][1];
        r.m[1][2] = ma.m[1][0] * mb.m[0][2] + ma.m[1][1] * mb.m[1][2] + ma.m[1][2] * mb.m[2][2] + ma.m[1][3] * mb.m[3][2];
        r.m[1][3] = ma.m[1][0] * mb.m[0][3] + ma.m[1][1] * mb.m[1][3] + ma.m[1][2] * mb.m[2][3] + ma.m[1][3] * mb.m[3][3];
        r.m[2][0] = ma.m[2][0] * mb.m[0][0] + ma.m[2][1] * mb.m[1][0] + ma.m[2][2] * mb.m[2][0] + ma.m[2][3] * mb.m[3][0];
        r.m[2][1] = ma.m[2][0] * mb.m[0][1] + ma.m[2][1] * mb.m[1][1] + ma.m[2][2] * mb.m[2][1] + ma.m[2][3] * mb.m[3][1];
        r.m[2][2] = ma.m[2][0] * mb.m[0][2] + ma.m[2][1] * mb.m[1][2] + ma.m[2][2] * mb.m[2][2] + ma.m[2][3] * mb.m[3][2];
        r.m[2][3] = ma.m[2][0] * mb.m[0][3] + ma.m[2][1] * mb.m[1][3] + ma.m[2][2] * mb.m[2][3] + ma.m[2][3] * mb.m[3][3];
        r.m[3][0] = ma.m[3][0] * mb.m[0][0] + ma.m[3][1] * mb.m[1][0] + ma.m[3][2] * mb.m[2][0] + ma.m[3][3] * mb.m[3][0];
        r.m[3][1] = ma.m[3][0] * mb.m[0][1] + ma.m[3][1] * mb.m[1][1] + ma.m[3][2] * mb.m[2][1] + ma.m[3][3] * mb.m[3][1];
        r.m[3][2] = ma.m[3][0] * mb.m[0][2] + ma.m[3][1] * mb.m[1][2] + ma.m[3][2] * mb.m[2][2] + ma.m[3][3] * mb.m[3][2];
        r.m[3][3] = ma.m[3][0] * mb.m[0][3] + ma.m[3][1] * mb.m[1][3] + ma.m[3][2] * mb.m[2][3] + ma.m[3][3] * mb.m[3][3];
        return r;
    }
    // the euler angles of the rotation part, setRotXYZ's inverse up to their sign (the name is not the original's)
    __attribute__((always_inline)) void getRotXYZ(Vec3& r) const {
        r.y = mm::asin(m[0][2]);
        if (r.y < 1.57079637f) {
            if (r.y > -1.57079637f) {
                r.z = ::atan2f(-m[0][1], m[0][0]);
                r.x = ::atan2f(-m[1][2], m[2][2]);
            } else {
                r.z = -::atan2f(-m[1][0], m[2][0]);
                r.x = 0.0f;
            }
        } else {
            r.z = ::atan2f(m[1][0], -m[2][0]);
            r.x = 0.0f;
        }
    }

    float m[4][4];

    static const Mat44 identity;
} __attribute__((aligned(16)));

}  // namespace mm

#endif
