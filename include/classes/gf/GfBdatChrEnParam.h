#ifndef CLASSES_GF_GFBDATCHRENPARAM_H
#define CLASSES_GF_GFBDATCHRENPARAM_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatChrEnParam; }

namespace gf {
// a base of gf::GfBdatChrEnParam no evidence names yet
class TUnk_B46A80 {
public:
    virtual ~TUnk_B46A80();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B46A58; base at 0x8 unknown (TUnk_B46A80)
class GfBdatChrEnParam : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrEnParam>, public TUnk_B46A80 {
public:
    virtual ~GfBdatChrEnParam();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
