#ifndef CLASSES_GF_GFBDATQUEST_H
#define CLASSES_GF_GFBDATQUEST_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatQuest; }

namespace gf {
// a base of gf::GfBdatQuest no evidence names yet
class TUnk_B47240 {
public:
    virtual ~TUnk_B47240();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B47218; base at 0x8 unknown (TUnk_B47240)
class GfBdatQuest : public ::mm::mtl::PtrSingleton< ::gf::GfBdatQuest>, public TUnk_B47240 {
public:
    virtual ~GfBdatQuest();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
