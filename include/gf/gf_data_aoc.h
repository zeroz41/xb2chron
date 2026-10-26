#ifndef GF_GF_DATA_AOC_H
#define GF_GF_DATA_AOC_H

namespace gf { class GfSetupParam; }

namespace gf {
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because nothing in its unit
// (application/BF2/gf/data/gf_data_aoc) is a class member yet. What it does: returns the int at index*4+0xC of the
// object the global at 0x7100C294C0 points to, -1 while that is null (GfMenuManager::fn_710035A6C4 passes 4).
int fn_71002229C0(unsigned int index);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function for the same reason. What it
// does: allocates (gf_data_aoc.cpp line 0x2B) the 0x28-byte add-on data singleton the global at 0x7100C294C0 holds,
// sets its ints at 0xC-0x23 to -1 and fills them from the add-on contents; GfDataManager's constructor calls it with
// its setup parameter after GfDataStore::build.
void fn_7100222908(const GfSetupParam& param);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function for the same reason. What it
// does: deletes the add-on data singleton (0x7100C294C0) through its destructor slot; GfDataManager::destroy calls it
// after GfDataBdat::destroy.
void fn_710022299C();
}  // namespace gf

#endif
