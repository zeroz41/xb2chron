#ifndef CLASSES_GF_GFMENUMAPINFO_H
#define CLASSES_GF_GFMENUMAPINFO_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuMapInfo; }

namespace gf {
// table 0x7100B5EDC0
class GfMenuMapInfo : public ::mm::mtl::PtrSingleton< ::gf::GfMenuMapInfo> {
public:
    virtual ~GfMenuMapInfo();  // slot 0
};
}  // namespace gf

#endif
