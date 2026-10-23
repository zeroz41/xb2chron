#ifndef GF_GFDATASALVAGE_H
#define GF_GFDATASALVAGE_H

#include "mm/mtl/FixedVector.h"

namespace gf {
// the salvage game's data lookups (functions, by its symbols)
class GfDataSalvage {
public:
    // the blades whose field skills help a salvage; false when there are none
    static bool getSalvageSkillBlade(mm::mtl::FixedVector<unsigned short, 422>& blades);
    // the level of a blade's salvage skill
    static unsigned int getSalvageSkillLevel(unsigned int blade);
};
}  // namespace gf

#endif
