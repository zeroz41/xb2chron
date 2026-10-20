#ifndef CLASSES_BTL_SHAKECAMERAELEMENTRANDOM_H
#define CLASSES_BTL_SHAKECAMERAELEMENTRANDOM_H

namespace mm { class Vec3; }

namespace btl {
// table 0x7100B3BCC0
class ShakeCameraElementRandom {
public:
    virtual ~ShakeCameraElementRandom();  // slot 0
    virtual void StopEternalShake();  // slot 2
    virtual void Update(float);  // slot 3
    virtual void CalcShift(mm::Vec3 const&, mm::Vec3 const&, mm::Vec3&, mm::Vec3&);  // slot 4
};
}  // namespace btl

#endif
