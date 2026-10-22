#ifndef CLASSES_WND_BOXSHAPE_H
#define CLASSES_WND_BOXSHAPE_H

#include "classes/wnd/Shape.h"
#include "mm/Vec3.h"

namespace wnd { class AABB; }
namespace wnd { class Transform; }

namespace wnd {
// table 0x7100B81768
class BoxShape : public Shape {
public:
    BoxShape(mm::Vec3 const& halfExtents);
    virtual ~BoxShape() {}  // slot 0 (inline: the table holds Shape's)
    virtual void calcAABB(wnd::Transform const&, wnd::AABB*);  // slot 2

    // the constructor's; SphereBoxAgent takes the box as reaching this far each way along its own axes
    mm::Vec3 m_halfExtents;
};
}  // namespace wnd

#endif
