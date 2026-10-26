#ifndef GF_GF_DATA_AOC_H
#define GF_GF_DATA_AOC_H

namespace gf {
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because nothing in its unit
// (application/BF2/gf/data/gf_data_aoc) is a class member yet. What it does: returns the int at index*4+0xC of the
// object the global at 0x7100C294C0 points to, -1 while that is null (GfMenuManager::fn_710035A6C4 passes 4).
int fn_71002229C0(unsigned int index);
}  // namespace gf

#endif
