#ifndef CLASSES_GF_GFBDATMAPLIST_H
#define CLASSES_GF_GFBDATMAPLIST_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatMaplist; }

namespace gf {
// a base of gf::GfBdatMaplist no evidence names yet
class TUnk_B47098 {
public:
    virtual ~TUnk_B47098();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B47070; base at 0x8 unknown (TUnk_B47098)
class GfBdatMaplist : public ::mm::mtl::PtrSingleton< ::gf::GfBdatMaplist>, public TUnk_B47098 {
public:
    virtual ~GfBdatMaplist();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
