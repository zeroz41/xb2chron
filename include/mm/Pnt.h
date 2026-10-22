#ifndef MM_PNT_H
#define MM_PNT_H

namespace mm {

// a point (x, then y); UIObjectAcc::setPosCenter takes one. Its copies copy x and y one by one (UIObjectPosPlugin's
// execute reads its position's two halves apart), and its constructor stores them one by one.
template <typename T>
class Pnt {
public:
    Pnt() {}
    Pnt(T x, T y) : x(x), y(y) {}
    Pnt(const Pnt& p) : x(p.x), y(p.y) {}
    Pnt& operator=(const Pnt& p) {
        x = p.x;
        y = p.y;
        return *this;
    }
    T x;
    T y;
};

}  // namespace mm

#endif
