#ifndef MM_RECT_H
#define MM_RECT_H

#include "mm/Pnt.h"

namespace mm {

// a rectangle as its corner and its size: UIObjectPosPlugin centers on x + w / 2, y + h / 2. A copy made copies the
// four one by one (UIObjectPosPlugin's execute stores each half of the words it loads); an assignment copies the
// whole (ui::UIInputPointer::updateImpl copies its region as one doubleword).
template <typename T>
class Rect {
public:
    Rect() {}
    // inline: ml::DesktopIcon's constructor sets its rectangle from one
    Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
    Rect(const Rect& r) : x(r.x), y(r.y), w(r.w), h(r.h) {}
    // whether a point lies within it, its far edges included (inline: ui::UIInputPointer::setPointerPos compares
    // the point with each edge, the size halved apart from the test); the name is not the original's
    bool isInside(const Pnt<T>& p) const { return p.x >= x && p.x <= x + w && p.y >= y && p.y <= y + h; }
    T x;
    T y;
    T w;
    T h;
};

}  // namespace mm

#endif
