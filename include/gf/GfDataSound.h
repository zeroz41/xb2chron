#ifndef GF_GFDATASOUND_H
#define GF_GFDATASOUND_H

#include "mm/mtl/FixedVector.h"

namespace mm { namespace mtl { template <int> class FixStr; }}

namespace gf {
class GfDataSound {
public:
    // "sound/se/<name>.xsp"
    static void getFullPath(mm::mtl::FixStr<128>& path, const char* name);
    static const char* getSeFileByWeaponType(unsigned int type);
    // the foot step's sound pack files, false when it has none (the symbol names it; GfAssetSetup::
    // requestFootStepSePackFile tests bit 0 of the result)
    static bool getFootStepSePackFile(mm::mtl::FixedVector<const char*, 2>& files, unsigned int footStep);
};
}  // namespace gf

#endif
