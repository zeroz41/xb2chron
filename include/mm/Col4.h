#ifndef MM_COL4_H
#define MM_COL4_H

#include "mm/Col3.h"

namespace mm {

// a colour, four floats; mm_lib names the common ones (white, gray, black, red, green, ...)
// derives from Col3: UICtrlMethodMulColor::setup and UICtrlManager::addUndoMethod copy (and pass) a colour's
// r, g, b as one Col3 lvalue (12 bytes: b, then r and g in one 8-byte copy)
struct Col4 : public Col3 {
    Col4() {}
    Col4(float r, float g, float b, float a) : Col3(r, g, b), a(a) {}

    float a;

    static const Col4 zero;
    static const Col4 white;
    static const Col4 black;
    static const Col4 gray;  // GmkRoutedNpc::debugDraw passes it while its pop condition fails
    static const Col4 yellow;  // GmkRoute/GmkRoutedFootPrint::debugDraw pass it to debugDrawRoute
    static const Col4 red;
    static const Col4 green;
    static const Col4 blue;
};

}  // namespace mm

#endif
