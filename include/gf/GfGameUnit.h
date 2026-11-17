#ifndef GF_GFGAMEUNIT_H
#define GF_GFGAMEUNIT_H

#include "mm/Vec3.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GF_OBJ_HANDLE; class RQ_SETUP_PARTY; }

namespace gf {
// what GfGameUnit::createParty takes (the symbols name it; the field names are not the original's).
// SCOM_CREATE_PARTY_OBJ::exec sets the first two only; createParty gives the leader driver's init param pad_0
// (that parameter is 1.0f by default) and, with pad_4 set, the position at 0x10 and the word at 0x20
struct PartyLeaderInfo {
    float pad_0;
    bool pad_4;
    mm::Vec3 pad_10;
    float pad_20;
};

// the game's object units (by its symbols; 3.0.1's code for it lies in GfWeapon's unit)
class GfGameUnit {
public:
    // destroys a party's objects; handles receives the handles still being destroyed
    // (SCOM_DESTROY_PARTY_OBJ::exec waits for them)
    // creates the party's objects (SCOM_CREATE_PARTY_OBJ::exec)
    static void createParty(PartyLeaderInfo& leader);
    static void destroyParty(const RQ_SETUP_PARTY& party, mm::mtl::FixedVector<GF_OBJ_HANDLE*, 32>* handles);
};
}  // namespace gf

#endif
