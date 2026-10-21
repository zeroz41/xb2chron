#ifndef CLASSES_GF_GFBDATCHRBL_H
#define CLASSES_GF_GFBDATCHRBL_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatChrBl; }

namespace gf {
// a base of gf::GfBdatChrBl no evidence names yet
class TUnk_B46778 {
public:
    virtual ~TUnk_B46778();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B46750; base at 0x8 unknown (TUnk_B46778)
class GfBdatChrBl : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrBl>, public TUnk_B46778 {
public:
    virtual ~GfBdatChrBl();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
