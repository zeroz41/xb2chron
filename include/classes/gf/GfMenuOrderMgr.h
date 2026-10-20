#ifndef CLASSES_GF_GFMENUORDERMGR_H
#define CLASSES_GF_GFMENUORDERMGR_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuOrderMgr; }

namespace gf {
// table 0x7100B5EE88
class GfMenuOrderMgr : public ::mm::mtl::PtrSingleton< ::gf::GfMenuOrderMgr> {
public:
    virtual ~GfMenuOrderMgr();  // slot 0
};
}  // namespace gf

#endif
