#ifndef CLASSES_WND_SPHERESHAPE_H
#define CLASSES_WND_SPHERESHAPE_H

namespace wnd { class AABB; }
namespace wnd { class Transform; }

namespace wnd {
// table 0x7100B817B8
class SphereShape {
public:
    virtual ~SphereShape();  // slot 0
    virtual void calcAABB(wnd::Transform const&, wnd::AABB*);  // slot 2
};
}  // namespace wnd

#endif
