#ifndef CLASSES_GF_GFMENUREFERENCEITEM_H
#define CLASSES_GF_GFMENUREFERENCEITEM_H

#include "classes/gf/GfMenuItemList.h"
#include "classes/mm/mtl/ReferenceObject.h"

namespace gf {
// table 0x7100B5FCE8; a counted item a menu object shares with GfMenuItemAdapter (GfMenuObjBalloon's get-item rows)
class GfMenuReferenceItem : public ::mm::mtl::ReferenceObject {
public:
    virtual ~GfMenuReferenceItem() {}  // slot 0
    virtual void getItem(gf::MenuItemInfo& item) const { item = m_item; }  // slot 2
    MenuItemInfo m_item;  // 0xC
};
}  // namespace gf

#endif
