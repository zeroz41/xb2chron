#ifndef CLASSES_GMK_GMKDMGPHANTOM_H
#define CLASSES_GMK_GMKDMGPHANTOM_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkPhantomSimple.h"

namespace gmk {
// table 0x7100B6E170
// 16-aligned through its GmkPhantomSimple (TGmkList::createGmk reserves its Vector with alignment 16)
class GmkDmgPhantom : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    GmkDmgPhantom() {}  // inline: Vector<GmkDmgPhantom>::resize constructs in place with these stores
    virtual ~GmkDmgPhantom();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void dispose();  // slot 5
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x31);
    // 0x48..0x50: padding (neither stored nor copied by the Vector instances)
    GmkPhantomSimple m_phantom;  // 0x50 (the name is not the original's); size 0xb0 from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
