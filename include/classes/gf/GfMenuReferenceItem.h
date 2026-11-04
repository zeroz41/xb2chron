#ifndef CLASSES_GF_GFMENUREFERENCEITEM_H
#define CLASSES_GF_GFMENUREFERENCEITEM_H

#include "classes/gf/GfMenuItemList.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/gf/GfAllocator.h"

// gf_menu_reference_item.h as the menu folder's files include it (backslash included): create cites it
#define GF_MENU_REFERENCE_ITEM_PATH "D:/Monolithsoft/BF2/prog/application/BF2\\gf/menu/gf_menu_reference_item.h"

namespace gf {
// table 0x7100B5FCE8; a counted item a menu object shares with GfMenuItemAdapter (GfMenuObjBalloon's get-item rows)
class GfMenuReferenceItem : public ::mm::mtl::ReferenceObject {
public:
    virtual ~GfMenuReferenceItem() {}  // slot 0
    // a new one (GfMenuObjGiftBox's constructor holds it; inline: the name is not the original's)
    static GfMenuReferenceItem* create() {
#line 57 GF_MENU_REFERENCE_ITEM_PATH
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuReferenceItem;
    }
    virtual void getItem(gf::MenuItemInfo& item) const { item = m_item; }  // slot 2
    MenuItemInfo m_item;  // 0xC
};
}  // namespace gf

#endif
