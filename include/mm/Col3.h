#ifndef MM_COL3_H
#define MM_COL3_H

#include "math.h"

namespace mm {

// a colour without alpha, three floats. The operations are inline, so their names are not the original's (none
// survives in a symbol).
class Col3 {
public:
    Col3() {}
    Col3(float r, float g, float b) : r(r), g(g), b(b) {}

    // each component within 1e-6 of other's
    bool isEqual(const Col3& other) const {
        return ::fabsf(other.r - r) <= 1e-6f && ::fabsf(other.g - g) <= 1e-6f && ::fabsf(other.b - b) <= 1e-6f;
    }

    // the named colours (mm_lib's; their symbols name them)
    static const Col3 yellow;
    static const Col3 salmon;

    float r;
    float g;
    float b;
};

}  // namespace mm

#endif
