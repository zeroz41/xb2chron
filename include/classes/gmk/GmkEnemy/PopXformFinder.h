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
    // slot 1 (0x71005BC69C, emitted with the table)
    virtual bool isYSnap() const { return m_gmk->getData()->m_ySnap; }
    virtual bool onPopGob(gf::GF_OBJ_HANDLE*) const { return true; }  // slot 2 (0x71005BC6AC, emitted with the table)
    virtual void onCreateGobInsts(unsigned int) const {}  // slot 3 (0x71005BC6B4, emitted with the table)
    // 0x8 (the name is not the original's)
    const GmkEnemy* m_gmk;
};
}  // namespace gmk

#endif
