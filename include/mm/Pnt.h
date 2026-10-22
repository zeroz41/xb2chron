#ifndef MM_PNT_H
#define MM_PNT_H

namespace mm {

// a point (x, then y); UIObjectAcc::setPosCenter takes one. Its copy constructor copies x and y one by one
// (UIObjectPosPlugin's execute reads its position's two halves apart, UILayoutData::attachLayout copies a transform's
// position so), and its constructor stores them one by one. Its assignment is the implicit one: UILayoutObject's
// getDisplayOffset copies its offset as one word, and updateSize stores a new one as one word.
template <typename T>
class Pnt {
public:
    Pnt() {}
    Pnt(T x, T y) : x(x), y(y) {}
    Pnt(const Pnt& p) : x(p.x), y(p.y) {}
    T x;
    T y;
};

}  // namespace mm

#endif
