#ifndef CLASSES_WND_SPHERESHAPE_H
#define CLASSES_WND_SPHERESHAPE_H

#include "classes/wnd/Shape.h"

namespace wnd { class AABB; }
namespace wnd { class Transform; }

namespace wnd {
// table 0x7100B817B8
class SphereShape : public Shape {
public:
    SphereShape(float radius);
    virtual ~SphereShape();  // slot 0
    virtual void calcAABB(wnd::Transform const&, wnd::AABB*);  // slot 2

    float m_radius;  // the constructor's; calcAABB spans the position plus and minus it
};
}  // namespace wnd

#endif
