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
    float lengthSq = v->x * v->x + v->y * v->y + v->z * v->z;
    if (lengthSq != 0.0f) {
        float scale = 1.0f / sqrtf(lengthSq);
        out->x = v->x * scale;
        out->y = v->y * scale;
        out->z = v->z * scale;
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
