// not proven yet: does not compile: no template named 'TGmkFormPc' in namespace 'gmk'; did you mean 'TGmkFormPcnpc'?
#ifndef CLASSES_GMK_TGMKFORMPCLIST_H
#define CLASSES_GMK_TGMKFORMPCLIST_H

#include "classes/gmk/IGmkList.h"
#include "classes/gmk/TGmkFormPcnpc.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkFormPcGob; }
namespace gmk { enum GmkType : int; }

namespace gmk {
// a template: 2 instances in the module
template <typename T0, typename T1>
class TGmkFormPcList : public ::gmk::TGmkList< ::gmk::TGmkFormPc<(::gmk::GmkType)24, ::gmk::TGmkFormPcnpc<(::gmk::GmkType)25>>, ::gmk::TGmkFormPc<(::gmk::GmkType)24, ::gmk::TGmkFormPcnpc<(::gmk::GmkType)25>>::BdatInfo, 1129337414u, 3u, ::gmk::GmkFormPcGob> {
public:
    virtual ~TGmkFormPcList();  // slot 0
    virtual void create(gmk::IGmkList::CreateInfo const&);  // slot 9
    virtual void createGmk(void*);  // slot 16
};
}  // namespace gmk

#endif
