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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in gf_menu_location's
    // unit and it writes the PtrSingleton<GfMenuLocation> instance. What it does: when the instance exists, stores value
    // in its u32 at 0x8 (GfMenuObjHitonowa's fn_710041D544, initialize and fn_7100423960 pass it).
    static void fn_7100356980(unsigned int value);
};
}  // namespace gf

#endif
