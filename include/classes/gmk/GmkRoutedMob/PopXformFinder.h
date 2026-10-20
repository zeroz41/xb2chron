#ifndef CLASSES_GMK_GMKROUTEDMOB_POPXFORMFINDER_H
#define CLASSES_GMK_GMKROUTEDMOB_POPXFORMFINDER_H

#include "classes/gmk/GmkRoutedMob.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace gmk {
// table 0x7100B6DE98
class GmkRoutedMob::PopXformFinder {
public:
    virtual void findPosRot(mm::Vec3&, mm::Vec3&) const;  // slot 0
    virtual void onPopGob(gf::GF_OBJ_HANDLE*) const;  // slot 1
    virtual void onCreateGobInsts(unsigned int) const;  // slot 2
};
}  // namespace gmk

#endif
