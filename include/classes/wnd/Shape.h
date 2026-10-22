#ifndef CLASSES_WND_SHAPE_H
#define CLASSES_WND_SHAPE_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace wnd { class AABB; }
namespace wnd { class Transform; }

namespace wnd {
// a shape's kind, which each shape's constructor gives Shape's: SphereShape's 0, BoxShape's 1
enum ShapeType {
    SHAPE_TYPE_SPHERE = 0,
    SHAPE_TYPE_BOX = 1,
};

// table 0x7100B81790; counted (its constructor clears the count at 8, WindObject's adds a reference)
class Shape : public mm::mtl::ReferenceObject {
public:
    Shape(ShapeType type);
    virtual ~Shape();  // slot 0
    virtual void calcAABB(wnd::Transform const&, wnd::AABB*) = 0;  // slot 2

    ShapeType m_type;  // the constructor's; the collision agents check it before taking a shape as theirs
};
}  // namespace wnd

#endif
