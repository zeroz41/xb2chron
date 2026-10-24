#ifndef CLASSES_GF_GFMENULOCATION_H
#define CLASSES_GF_GFMENULOCATION_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuLocation; }

namespace gf {
// table 0x7100B5E910
class GfMenuLocation : public ::mm::mtl::PtrSingleton< ::gf::GfMenuLocation> {
public:
    virtual ~GfMenuLocation();  // slot 0
    // GfMenuManager's quest events refresh locators 0, 1 and 3
    static void refreshLocator(unsigned int kind);
};
}  // namespace gf

#endif
