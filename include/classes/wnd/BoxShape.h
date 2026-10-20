#ifndef CLASSES_WND_BOXSHAPE_H
#define CLASSES_WND_BOXSHAPE_H

namespace wnd { class AABB; }
namespace wnd { class Transform; }

namespace wnd {
// table 0x7100B81768
class BoxShape {
public:
    virtual ~BoxShape();  // slot 0
    virtual void calcAABB(wnd::Transform const&, wnd::AABB*);  // slot 2
};
}  // namespace wnd

#endif
