#ifndef CLASSES_GMK_GMKROUTEDMOB_POPXFORMFINDER_H
#define CLASSES_GMK_GMKROUTEDMOB_POPXFORMFINDER_H

#include "classes/gmk/GmkRoutedMob.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace gmk {
// table 0x7100B6DE98
// GmkRoutedMob::update builds one on the stack
class GmkRoutedMob::PopXformFinder : public GmkMobInsts::IPopXformFinder {
public:
    explicit PopXformFinder(GmkRoutedMob* gmk) : m_gmk(gmk), m_navi(nullptr) {}
    virtual bool findPosRot(mm::Vec3& pos, mm::Vec3& rot) const;  // slot 0
    virtual void onPopGob(gf::GF_OBJ_HANDLE* handle) const;  // slot 1
    virtual void onCreateGobInsts(unsigned int num) const { m_gmk->createRouteNavis(num); }  // slot 2
    // 0x8 (the name is not the original's); not const: onCreateGobInsts calls createRouteNavis
    GmkRoutedMob* m_gmk;
    // 0x10: the free route navigator findPosRot picked (none when it found none); onPopGob binds the popped object
    // to it (the name is not the original's)
    mutable GmkRouteNavi* m_navi;
};
}  // namespace gmk

#endif
