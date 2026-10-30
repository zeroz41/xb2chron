#ifndef GF_GFGAMEUNIT_H
#define GF_GFGAMEUNIT_H

#include "mm/mtl/FixedVector.h"

namespace gf { class GF_OBJ_HANDLE; class RQ_SETUP_PARTY; }

namespace gf {
// the game's object units (by its symbols; 3.0.1's code for it lies in GfWeapon's unit)
class GfGameUnit {
public:
    // destroys a party's objects; handles receives the handles still being destroyed
    // (SCOM_DESTROY_PARTY_OBJ::exec waits for them)
    static void destroyParty(const RQ_SETUP_PARTY& party, mm::mtl::FixedVector<GF_OBJ_HANDLE*, 32>* handles);
};
}  // namespace gf

#endif
