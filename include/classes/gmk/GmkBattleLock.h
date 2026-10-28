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
    virtual ~GmkBattleLock();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // its kind (getGmkType's; GfGameInsideBattleLock walks the battle locks by it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(11);

    unsigned char pad_48[0x8];
    // its collision (1.0.0's GmkBattleLock::createGmkCollision creates it; the name is not the original's)
    GmkCollision m_collision;
    unsigned char pad_b0[0x10];
    unsigned int m_effectHandle;  // dispose removes the effect it names (the name is not the original's)
    unsigned char pad_c4[0xc];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
