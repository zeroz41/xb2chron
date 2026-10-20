#ifndef CLASSES_GF_GFDATASTORE_H
#define CLASSES_GF_GFDATASTORE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfDataStore; }

namespace gf {
// table 0x7100B50B18
class GfDataStore : public ::mm::mtl::PtrSingleton< ::gf::GfDataStore> {
public:
    virtual ~GfDataStore();  // slot 0
};
}  // namespace gf

#endif
