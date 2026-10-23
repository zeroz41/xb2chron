#ifndef CLASSES_GF_GFFIELDCOLLECT_H
#define CLASSES_GF_GFFIELDCOLLECT_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldCollect; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B51488
class GfFieldCollect : public ::mm::mtl::PtrSingleton< ::gf::GfFieldCollect> {
public:
    virtual ~GfFieldCollect();  // slot 0
    void start(GF_OBJ_HANDLE* handle);  // GfPlayComCollect::start calls it
};
}  // namespace gf

#endif
