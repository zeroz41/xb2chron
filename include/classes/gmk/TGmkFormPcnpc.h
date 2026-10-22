#ifndef CLASSES_GMK_TGMKFORMPCNPC_H
#define CLASSES_GMK_TGMKFORMPCNPC_H

#include "classes/gmk/AGmkBase.h"

namespace gmk { enum GmkType : int; }

namespace gmk {
// a template: 2 instances in the module
template <gmk::GmkType T0>
class TGmkFormPcnpc : public ::gmk::AGmkBase {
public:
    virtual ~TGmkFormPcnpc();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugUpdateMmf();  // slot 10
};
}  // namespace gmk

#endif
