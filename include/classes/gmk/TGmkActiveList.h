#ifndef CLASSES_GMK_TGMKACTIVELIST_H
#define CLASSES_GMK_TGMKACTIVELIST_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gmk {
// a template: 5 instances in the module
template <typename T0>
class TGmkActiveList : public ::mm::mtl::PtrSingleton< ::gmk::TGmkActiveList< T0>> {
public:
    virtual ~TGmkActiveList();  // slot 0
};
}  // namespace gmk

#endif
