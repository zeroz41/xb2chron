#ifndef MM_MAT34_H
#define MM_MAT34_H

namespace mm {

// a 3x4 matrix: three rows of four floats, 0x30 bytes (effect::SystemManager::updateCam copies Mat34::identity
// into one with a 0x30-byte memcpy)
class Mat34 {
public:
    float m[3][4];

    static const Mat34 identity;
} __attribute__((aligned(16)));

}  // namespace mm

#endif
