#include "mm/Vec3.h"
#include "classes/wnd/BoxShape.h"

namespace wnd {

BoxShape::BoxShape(const mm::Vec3& halfExtents) : Shape(SHAPE_TYPE_BOX), m_halfExtents(halfExtents) {}

// calcAABB (0x7100892E70) is not matched yet: each unit axis turned by the rotation (mm::Quat::rotate), the extent
// along each world axis the sum of its components' sizes times the half extents, the box the position less and
// plus it. The closest candidate differs in 122 instruction lines (scheduling).

}  // namespace wnd
