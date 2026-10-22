#ifndef FW_TRANSFORM_H
#define FW_TRANSFORM_H

#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace fw {
// a place and a turn: ReferenceFrame keeps its local one and the world one it composes from its parent's
class Transform {
public:
    static void mul(const Transform& lhs, const Transform& rhs, Transform* pOut);

    mm::Vec3 position;
    mm::Quat rotation;
};
}  // namespace fw

#endif
