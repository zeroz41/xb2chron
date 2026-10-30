#ifndef FW_TRANSFORM_H
#define FW_TRANSFORM_H

#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace fw {
// a place and a turn: ReferenceFrame keeps its local one and the world one it composes from its parent's
class Transform {
public:
    // rhs placed in lhs's frame: lhs's position plus rhs's turned by lhs's rotation, rhs's rotation then lhs's
    static void mul(const Transform& lhs, const Transform& rhs, Transform* pOut);
    // the opposite transform: the inverse rotation, and the negated position turned by it
    static void invert(const Transform& transform, Transform* pOut);
    // rhs placed in lhs's inverse frame (inline: ReferenceFrame::syncLocalTransform; the name is not the original's)
    static void mulInverse(const Transform& lhs, const Transform& rhs, Transform* pOut) {
        Transform inverse;
        invert(lhs, &inverse);
        mul(inverse, rhs, pOut);
    }

    mm::Vec3 position;
    mm::Quat rotation;
};
}  // namespace fw

#endif
