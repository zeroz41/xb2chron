#ifndef CLASSES_GF_GFBDATBGM_H
#define CLASSES_GF_GFBDATBGM_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatBgm; }

namespace gf {
// a base of gf::GfBdatBgm no evidence names yet
class TUnk_B45FB8 {
public:
    virtual ~TUnk_B45FB8();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B45F90; base at 0x8 unknown (TUnk_B45FB8)
class GfBdatBgm : public ::mm::mtl::PtrSingleton< ::gf::GfBdatBgm>, public TUnk_B45FB8 {
public:
    virtual ~GfBdatBgm();  // slot 0
    virtual void bdatRefresh();  // slot 2
    const char* getBgmListfilename(unsigned int id) const;  // a BGM list row's file name
};
}  // namespace gf

#endif
