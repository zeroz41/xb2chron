#ifndef MM_PNT_H
#define MM_PNT_H

namespace mm {

// a point on screen (UIObjectAcc::getPos/setPos take a Pnt<short>)
template <typename T>
class Pnt {
public:
    T x;
    T y;
};

}  // namespace mm

#endif
