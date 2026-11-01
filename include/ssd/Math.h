#ifndef SSD_MATH_H
#define SSD_MATH_H

#include <math.h>

// the sound library's own vector math (3D sound positions)
namespace ssd {

struct Vec3 {
    float x;
    float y;
    float z;
};

// a 4x3 transform: three axis rows and a translation row (Mat34LookAt fills the axes into the columns)
struct Mat34 {
    float m[4][3];
};

// v scaled to unit length; out is left as it is when v has no length (the name is not the original's)
inline void Vec3Normalize(Vec3* out, const Vec3* v) {
    float x = v->x;
    float y = v->y;
    float z = v->z;
    float lengthSq = x * x + y * y + z * z;
    if (lengthSq == 0.0f) {
        // nothing to scale (an empty branch: the original's block layout needs it)
    } else {
        float scale = 1.0f / sqrtf(lengthSq);
        out->x = x * scale;
        out->y = y * scale;
        out->z = z * scale;
    }
}

// a x b (the name is not the original's)
inline void Vec3Cross(Vec3* out, const Vec3* a, const Vec3* b) {
    float x = a->y * b->z - a->z * b->y;
    float y = a->z * b->x - a->x * b->z;
    float z = a->x * b->y - a->y * b->x;
    out->x = x;
    out->y = y;
    out->z = z;
}

// a . b (the name is not the original's)
inline float Vec3Dot(const Vec3* a, const Vec3* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

Mat34* Mat34LookAt(Mat34* out, const Vec3* eye, const Vec3* direction, const Vec3* up);
Vec3* Vec3Transform(const Mat34* m, const Vec3* v, Vec3* out);

}  // namespace ssd

#endif
