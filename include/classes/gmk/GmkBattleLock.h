#ifndef CLASSES_GMK_GMKBATTLELOCK_H
#define CLASSES_GMK_GMKBATTLELOCK_H

#include "classes/gmk/AGmkBase.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/gmk/GmkCollision.h"
namespace gmk { class GmkBattleLockGob; }

namespace gmk {
// table 0x7100B6C480
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkBattleLock : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    // user-provided: Vector<GmkBattleLock>::resize stores the defaults below only (no zero fill of the element first)
    GmkBattleLock() {}
    virtual ~GmkBattleLock();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // 2.0.0's symbols name them (update calls createEffect, which tail-calls applyEffectParam)
    void createEffect();
    void applyEffectParam() const;
    // its collision from its shape (out of line; its update calls it)
    void createGmkCollision();
    // its kind (getGmkType's; GfGameInsideBattleLock walks the battle locks by it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(11);

    // its collision (1.0.0's GmkBattleLock::createGmkCollision creates it; the name is not the original's); at 0x50,
    // 16-aligned (0x48..0x4f: a hole, not stored or copied)
    GmkCollision m_collision;
    unsigned int m_effectHandle = 0;  // 0xc0: dispose removes the effect it names (the name is not the original's)
    // the enemies counted inside it (GfComBehaviorEnemy's update counts in and out; signed: update makes its
    // collision while it is 1 or more and drops it below)
    int pad_c4 = 0;  // (0xc8..0xcf: tail padding; the size: TGmkList::getInst's stride)
};
}  // namespace gmk

#endif
