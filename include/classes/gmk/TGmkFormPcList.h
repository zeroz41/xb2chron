#ifndef CLASSES_GMK_TGMKFORMPCLIST_H
#define CLASSES_GMK_TGMKFORMPCLIST_H

#include "classes/gmk/IGmkList.h"
#include "classes/gmk/TGmkFormPc.h"
#include "classes/gmk/TGmkFormPcnpc.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkFormPcGob; }
namespace gmk { enum GmkType : int; }

namespace gmk {
// a template: 2 instances in the module; T0 its gimmicks, T1 the TGmkList of them it extends
template <typename T0, typename T1>
class TGmkFormPcList : public T1 {
public:
    virtual ~TGmkFormPcList();  // slot 0
    virtual void create(gmk::IGmkList::CreateInfo const&);  // slot 9
    virtual void createGmk(void*);  // slot 16
};
}  // namespace gmk

#endif
