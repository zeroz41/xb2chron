#ifndef CLASSES_GMK_GMKDMGPHANTOM_H
#define CLASSES_GMK_GMKDMGPHANTOM_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6E170
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkDmgPhantom : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    virtual ~GmkDmgPhantom();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void dispose();  // slot 5
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x31);
    unsigned char pad_48[0x68];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
