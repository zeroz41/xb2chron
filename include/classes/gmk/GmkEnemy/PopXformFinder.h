#ifndef CLASSES_GMK_GMKENEMY_POPXFORMFINDER_H
#define CLASSES_GMK_GMKENEMY_POPXFORMFINDER_H

#include "classes/gmk/GmkEnemy.h"
#include "classes/gmk/GmkEnemyInsts/PopInfo.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace gmk {
// table 0x7100B6D7C8
class GmkEnemy::PopXformFinder {
public:
    virtual void findPosRot(mm::Vec3&, mm::Vec3&, gf::GF_OBJ_HANDLE*, gmk::GmkEnemyInsts::PopInfo::PopEnemyInfo const&) const;  // slot 0
    virtual void isYSnap() const;  // slot 1
    virtual void onPopGob(gf::GF_OBJ_HANDLE*) const;  // slot 2
    virtual void onCreateGobInsts(unsigned int) const;  // slot 3
};
}  // namespace gmk

#endif
