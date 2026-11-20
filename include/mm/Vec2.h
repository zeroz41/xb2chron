#ifndef MM_VEC2_H
#define MM_VEC2_H

namespace mm {

// two floats in 16 bytes on a 16-byte boundary, as Vec3: UIObjectScrollBarPlugin's scale sits at 0x40 after a field
// ending at 0x34, and UIObjectFitPlugin's execute gives its scale a 16-byte slot. Its copies copy x and y.
class Vec2 {
public:
    Vec2() {}
    Vec2(float x, float y) : x(x), y(y) {}
    Vec2(const Vec2& v) : x(v.x), y(v.y) {}
    // trivial: an assignment copies the 8 data bytes at once (UICtrlMethodScale::setup, UICtrlMethodMotion::setup)
    Vec2& operator=(const Vec2& v) = default;
    static const Vec2 zero;  // AgentUtilField::calcFollowWallInput starts its input from it
    static const Vec2 unitY;  // StateUtilField::decideWallMoveMode measures the stick's angle from it
    float x;
    float y;
} __attribute__((aligned(16)));

}  // namespace mm

#endif
