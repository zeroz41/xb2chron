#ifndef CLASSES_GF_GFMENUHUD_H
#define CLASSES_GF_GFMENUHUD_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuHUD; }

namespace gf {
// table 0x7100B5E890
class GfMenuHUD : public ::mm::mtl::PtrSingleton< ::gf::GfMenuHUD> {
public:
    virtual ~GfMenuHUD();  // slot 0
};
}  // namespace gf

#endif
