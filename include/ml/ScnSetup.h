#ifndef ML_SCNSETUP_H
#define ML_SCNSETUP_H

#include "mm/mtl/FixStr.h"
#include "mtl/AllocHandle.h"

namespace ml {
// what ml::Scn::create makes a scene from (apps::FrameworkLauncher's build thread fills one from its
// SceneBuildInfo). The two 4-byte fields copied on their own (0x0C, 0x40) are ALLOC_HANDLEs: their user-written
// assignment keeps them out of the copy's memcpy runs, and they start at 0. Only the name has a name.
class ScnSetup {
public:
    ScnSetup() : pad_0(nullptr), pad_8(0x300000), pad_34(0x14000000), pad_38(0x80), pad_3c(0x1000), pad_44(true) {}

    void* pad_0;
    unsigned int pad_8;
    mtl::ALLOC_HANDLE pad_c;
    // 0x10 the build thread names the scene after its process (the name is not the original's)
    mm::mtl::FixStr<32> m_name;
    unsigned int pad_34;
    unsigned int pad_38;
    unsigned int pad_3c;
    mtl::ALLOC_HANDLE pad_40;
    bool pad_44;
};
}  // namespace ml

#endif
