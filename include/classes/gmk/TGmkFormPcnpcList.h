// not proven yet: does not compile: no template named 'TGmkFormPcnpc' in namespace 'gmk'; did you mean 'TGmkFormPcnpcList'?
#ifndef CLASSES_GMK_TGMKFORMPCNPCLIST_H
#define CLASSES_GMK_TGMKFORMPCNPCLIST_H

#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkFormPcnpcGob; }
namespace gmk { enum GmkType : int; }

namespace gmk {
// a template: 2 instances in the module
template <typename T0, typename T1>
class TGmkFormPcnpcList : public ::gmk::TGmkList< ::gmk::TGmkFormPcnpc<(::gmk::GmkType)25>, ::gmk::TGmkFormPcnpc<(::gmk::GmkType)25>::BdatInfo, 1347310150u, 2u, ::gmk::GmkFormPcnpcGob> {
public:
    virtual ~TGmkFormPcnpcList();  // slot 0
    virtual void createGmk(void*);  // slot 16
};
}  // namespace gmk

#endif
