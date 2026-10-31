#ifndef CLASSES_GMK_GMKMOB_POPXFORMFINDER_H
#define CLASSES_GMK_GMKMOB_POPXFORMFINDER_H

#include "classes/gmk/GmkMob.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace gmk {
// table 0x7100B6DD60; GmkMob::update builds one on the stack (the only user of the table)
class GmkMob::PopXformFinder : public GmkMobInsts::IPopXformFinder {
public:
    explicit PopXformFinder(const GmkMob* gmk) : m_gmk(gmk) {}
    virtual bool findPosRot(mm::Vec3& pos, mm::Vec3& rot) const;  // slot 0
    virtual void onPopGob(gf::GF_OBJ_HANDLE*) const {}  // slot 1
    virtual void onCreateGobInsts(unsigned int) const {}  // slot 2
    const GmkMob* m_gmk;  // 0x8 (the name is not the original's)
};
}  // namespace gmk

#endif
