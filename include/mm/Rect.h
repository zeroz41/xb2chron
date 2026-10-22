#ifndef MM_RECT_H
#define MM_RECT_H

namespace mm {

// a rectangle as its corner and its size: UIObjectPosPlugin centers on x + w / 2, y + h / 2. Its copies copy the
// four one by one (UIObjectPosPlugin's execute stores each half of the words it loads).
template <typename T>
class Rect {
public:
    Rect() {}
    Rect(const Rect& r) : x(r.x), y(r.y), w(r.w), h(r.h) {}
    Rect& operator=(const Rect& r) {
        x = r.x;
        y = r.y;
        w = r.w;
        h = r.h;
        return *this;
    }
    T x;
    T y;
    T w;
    T h;
};

}  // namespace mm

#endif
