// not proven yet: does not compile: no member named 'BdatInfo' in 'gmk::TGmkFormPcnpc<25>'
#ifndef CLASSES_GMK_TGMKFORMPCNPCLIST_H
#define CLASSES_GMK_TGMKFORMPCNPCLIST_H

#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkFormPcnpcGob; }
namespace gmk { enum GmkType : int; }

namespace gmk {
// a template: 2 instances in the module
template <typename T0, typename T1>
class TGmkFormPcnpcList : public ::gmk::TGmkList<T0, typename T0::BdatInfo, 1347310150u, 2u, gmk::GmkFormPcnpcGob> {
public:
    virtual ~TGmkFormPcnpcList();  // slot 0
    virtual void createGmk(void*);  // slot 16
};
}  // namespace gmk

#endif
