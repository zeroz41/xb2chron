#ifndef CLASSES_GF_GFMENUCALLMANAGER_H
#define CLASSES_GF_GFMENUCALLMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuCallManager; }

namespace gf {
// table 0x7100B5E418
class GfMenuCallManager : public ::mm::mtl::PtrSingleton< ::gf::GfMenuCallManager> {
public:
    virtual ~GfMenuCallManager();  // slot 0
};
}  // namespace gf

#endif
