#ifndef MM_MAT44_H
#define MM_MAT44_H

namespace mm {

// a 4x4 matrix: 0x40 bytes, copied whole (Obb::setMat copies one with a 0x40-byte memcpy). Its rows are
// laid out as Sphere::getOBB builds one on its stack, the translation in the last.
class Mat44 {
public:
    float m[4][4];
} __attribute__((aligned(16)));

}  // namespace mm

#endif
