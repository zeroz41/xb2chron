#ifndef CLASSES_GF_GFBDATCHRDR_H
#define CLASSES_GF_GFBDATCHRDR_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatChrDr; }

namespace gf {
// a base of gf::GfBdatChrDr no evidence names yet
class TUnk_B46920 {
public:
    virtual ~TUnk_B46920();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B468F8; base at 0x8 unknown (TUnk_B46920)
class GfBdatChrDr : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrDr>, public TUnk_B46920 {
public:
    virtual ~GfBdatChrDr();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
