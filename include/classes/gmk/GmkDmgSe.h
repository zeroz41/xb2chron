#ifndef CLASSES_GMK_GMKDMGSE_H
#define CLASSES_GMK_GMKDMGSE_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6E240
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkDmgSe : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    virtual ~GmkDmgSe();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void dispose();  // slot 5
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x33);
    unsigned char pad_48[0xa8];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
