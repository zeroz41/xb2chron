#ifndef MM_VEC3_H
#define MM_VEC3_H

namespace mm {

// a 3D vector. Only its components are declared: mm_lib's constants (zero, unitX, ...) are 16 bytes apart,
// yet copies move 12 bytes, so how its fourth word is declared is still open.
class Vec3 {
public:
    float x;
    float y;
    float z;
};

}  // namespace mm

#endif
