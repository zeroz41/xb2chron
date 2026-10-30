#ifndef MM_COL4_H
#define MM_COL4_H

namespace mm {

// a colour, four floats; mm_lib names the common ones (white, gray, black, red, green, ...)
struct Col4 {
    Col4() {}
    Col4(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

    float r;
    float g;
    float b;
    float a;

    static const Col4 zero;
    static const Col4 white;
    static const Col4 black;
    static const Col4 gray;  // GmkRoutedNpc::debugDraw passes it while its pop condition fails
    static const Col4 yellow;  // GmkRoute/GmkRoutedFootPrint::debugDraw pass it to debugDrawRoute
};

}  // namespace mm

#endif
