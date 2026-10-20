#ifndef CLASSES_WND_SHAPE_H
#define CLASSES_WND_SHAPE_H

namespace wnd {
// table 0x7100B81790
class Shape {
public:
    virtual ~Shape();  // slot 0
    virtual void vf2() = 0;  // slot 2
};
}  // namespace wnd

#endif
