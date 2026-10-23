#ifndef CLASSES_GMK_TGMKFORMPCNPCLIST_H
#define CLASSES_GMK_TGMKFORMPCNPCLIST_H

#include "classes/gmk/TGmkFormPcnpc.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkFormPcnpcGob; }
namespace gmk { enum GmkType : int; }

namespace gmk {
// a template: 2 instances in the module; T0 its gimmicks, T1 the TGmkList of them it extends
template <typename T0, typename T1>
class TGmkFormPcnpcList : public T1 {
public:
    virtual ~TGmkFormPcnpcList();  // slot 0
    virtual void createGmk(void*);  // slot 16
};
}  // namespace gmk

#endif
