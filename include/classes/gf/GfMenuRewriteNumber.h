#ifndef CLASSES_GF_GFMENUREWRITENUMBER_H
#define CLASSES_GF_GFMENUREWRITENUMBER_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/gf/GfAllocator.h"

namespace gf {
// table 0x7100B640F8; counted (GfMenuAdapter references the one it is given). The table is weak: no key function
// (its D1 slot is ReferenceObject's destructor), GfMenuObjPartyStatus2's unit makes one and emits it.
class GfMenuRewriteNumber : public ::mm::mtl::ReferenceObject {
public:
    GfMenuRewriteNumber() : m_number(0), m_enabled(true) {}
    // a new one holding a reference (inline: GfMenuObjPartyStatus2::MainListener's open event inlines it, citing
    // gf_menu_adapter.h line 39; the name is not the original's)
    static GfMenuRewriteNumber* create() {
#line 39 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/menu/adapter/gf_menu_adapter.h"
        GfMenuRewriteNumber* number = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuRewriteNumber;
        if (number != nullptr) {
            number->addRef();
        }
        return number;
    }
    virtual ~GfMenuRewriteNumber() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    // what GfMenuAdapter::setNumber shows while m_enabled is set (the names are not the original's)
    int m_number;
    bool m_enabled;
};
}  // namespace gf

#endif
