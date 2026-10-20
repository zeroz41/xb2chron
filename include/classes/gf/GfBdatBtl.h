#ifndef CLASSES_GF_GFBDATBTL_H
#define CLASSES_GF_GFBDATBTL_H

#include "classes/gf/_gfbbt.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatBtl; }

namespace gf {
// table 0x7100B462F8
class GfBdatBtl : public ::mm::mtl::PtrSingleton< ::gf::GfBdatBtl>, public ::gf::_gfbbt {
public:
    virtual ~GfBdatBtl();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
