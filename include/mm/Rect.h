#ifndef MM_RECT_H
#define MM_RECT_H

namespace mm {

// a rectangle on screen: its corner and its size (UIObjectOffsetPlugin::execute centers with x + w / 2)
template <typename T>
class Rect {
public:
    T x;
    T y;
    T w;
    T h;
};

}  // namespace mm

#endif
