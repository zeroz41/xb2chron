#ifndef CLASSES_GMK_GMKBATTLELOCK_H
#define CLASSES_GMK_GMKBATTLELOCK_H

#include "classes/gmk/AGmkBase.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gmk {
// table 0x7100B6C480
class GmkBattleLock : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkBattleLock();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // its kind (getGmkType's; GfGameInsideBattleLock walks the battle locks by it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(11);

    unsigned char pad_48[0x60];
    // what the lock holds while it is engaged, none otherwise: dispose clears three of its fields and releases it
    // (its class is not known yet; the name is not the original's)
    mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> m_lockObject;
};
}  // namespace gmk

#endif
