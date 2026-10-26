#ifndef GF_GFPARTYSELECT_H
#define GF_GFPARTYSELECT_H

#include "mm/mtl/FixedVector.h"

namespace gf {
// 1.0.0's gf::GfPartySelect (statics only)
class GfPartySelect {
public:
    enum LIST_TYPE {};  // getDriverList switches on 0-8; the values' names are not known
    // fills the list with drivers. 3.0.1's copy (0x71002BCBE4) asserts size() < 0x20 and keeps the size at 0x40,
    // so its vector holds 32 (1.0.0's holds 16: size at 0x20, cmp #0x10); the symbols still spell 1.0.0's 16
    static void getDriverList(mm::mtl::FixedVector<unsigned short, 32>& list, LIST_TYPE type, unsigned int);
};
}  // namespace gf

#endif
