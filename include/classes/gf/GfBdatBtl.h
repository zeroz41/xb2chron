#ifndef CLASSES_GF_GFBDATBTL_H
#define CLASSES_GF_GFBDATBTL_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatBtl; }

namespace gf {
// a base of gf::GfBdatBtl no evidence names yet
class TUnk_B46320 {
public:
    virtual ~TUnk_B46320();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B462F8; base at 0x8 unknown (TUnk_B46320)
class GfBdatBtl : public ::mm::mtl::PtrSingleton< ::gf::GfBdatBtl>, public TUnk_B46320 {
public:
    virtual ~GfBdatBtl();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
