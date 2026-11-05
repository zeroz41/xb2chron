#ifndef CLASSES_GMK_GMKENEMY_POPXFORMFINDER_H
#define CLASSES_GMK_GMKENEMY_POPXFORMFINDER_H

#include "classes/gmk/GmkEnemy.h"
#include "classes/gmk/GmkEnemyInsts/PopInfo.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace gmk {
// table 0x7100B6D7C8; GmkEnemy::update builds one on the stack
class GmkEnemy::PopXformFinder : public GmkEnemyInsts::IPopXformFinder {
public:
    explicit PopXformFinder(const GmkEnemy* gmk) : m_gmk(gmk) {}
    virtual bool findPosRot(mm::Vec3& pos, mm::Vec3& rot, gf::GF_OBJ_HANDLE* handle,
                            const GmkEnemyInsts::PopInfo::PopEnemyInfo& info) const;  // slot 0
    virtual bool isYSnap() const;  // slot 1
    virtual void onPopGob(gf::GF_OBJ_HANDLE* handle) const;  // slot 2
    virtual void onCreateGobInsts(unsigned int) const {}  // slot 3
    // 0x8 (the name is not the original's)
    const GmkEnemy* m_gmk;
};
}  // namespace gmk

#endif
