#ifndef CLASSES_GMK_GMKROUTEDENEMY_POPXFORMFINDER_H
#define CLASSES_GMK_GMKROUTEDENEMY_POPXFORMFINDER_H

#include "classes/gmk/GmkEnemyInsts/PopInfo.h"
#include "classes/gmk/GmkRoutedEnemy.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace gmk {
// table 0x7100B6D860; GmkRoutedEnemy::update builds one on the stack
class GmkRoutedEnemy::PopXformFinder : public GmkEnemyInsts::IPopXformFinder {
public:
    explicit PopXformFinder(GmkRoutedEnemy* gmk) : m_gmk(gmk) {}
    virtual bool findPosRot(mm::Vec3& pos, mm::Vec3& rot, gf::GF_OBJ_HANDLE* handle,
                            const GmkEnemyInsts::PopInfo::PopEnemyInfo& info) const;  // slot 0
    virtual bool isYSnap() const { return false; }  // slot 1
    virtual void onPopGob(gf::GF_OBJ_HANDLE* handle) const;  // slot 2
    virtual void onCreateGobInsts(unsigned int num) const { m_gmk->createRouteNavis(num); }  // slot 3
    // 0x8 (the name is not the original's); not const: onCreateGobInsts calls createRouteNavis
    GmkRoutedEnemy* m_gmk;
};
}  // namespace gmk

#endif
