#ifndef CLASSES_GMK_TGMKFORMPCNPC_H
#define CLASSES_GMK_TGMKFORMPCNPC_H

#include "classes/gmk/AGmkBase.h"

namespace gmk { enum GmkType : int; }

namespace gmk {
// a template: 2 instances in the module
template <gmk::GmkType T0>
class TGmkFormPcnpc : public ::gmk::AGmkBase {
public:
    // its row of the list's BDAT table: nothing of it is kept (Vector<BdatInfo>::resize allocates a byte an element)
    class BdatInfo {};
    virtual ~TGmkFormPcnpc();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugUpdateMmf();  // slot 10
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = T0;
    unsigned char pad_48[0x8];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
