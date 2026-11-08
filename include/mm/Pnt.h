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
    // ScnCamMan::update compares a camera's size with a view's this way: the halves are read one by one, through
    // the 4-aligned Pnt, where a 16-aligned owner's two ints would be read as one word
    bool operator!=(const Pnt& p) const { return x != p.x || y != p.y; }
    T x;
    T y;
};

}  // namespace mm

#endif
