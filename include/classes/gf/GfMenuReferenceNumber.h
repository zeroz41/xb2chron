#ifndef CLASSES_GF_GFMENUREFERENCENUMBER_H
#define CLASSES_GF_GFMENUREFERENCENUMBER_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/gf/GfAllocator.h"

// gf_menu_reference_number.h as the object folder's files include it: create cites it
#define GF_MENU_REFERENCE_NUMBER_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2/gf/menu/object/../gf_menu_reference_number.h"

namespace gf {
// table 0x7100B5FB90; a counted number with its range a menu object shares with GfMenuReferenceAdapter
class GfMenuReferenceNumber : public ::mm::mtl::ReferenceObject {
public:
    GfMenuReferenceNumber() : m_value(0), m_min(0), m_max(9999) {}  // the symbols name no copy (inline in create)
    virtual ~GfMenuReferenceNumber();  // slot 0
    // a new one (GfMenuObjMercenaryReport's constructor holds it; inline: the name is not the original's)
    static GfMenuReferenceNumber* create() {
#line 46 GF_MENU_REFERENCE_NUMBER_PATH
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuReferenceNumber();
    }
    // GfMenuReferenceAdapter shows it (plus its offset) and its range; the names are not the original's
    int m_value;
    int m_min;  // the number plugin's setMin
    int m_max;  // the number plugin's setMax
    // whether the value is at an end of its range (GfMenuObjLvupSelect::SelectListener hides its arrows so: one
    // operator-> per test, the value and the bound loaded together); the names are not the original's
    bool isMin() const { return m_value == m_min; }
    bool isMax() const { return m_value == m_max; }
};
}  // namespace gf

#endif
