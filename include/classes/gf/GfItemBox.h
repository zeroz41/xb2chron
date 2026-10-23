#ifndef CLASSES_GF_GFITEMBOX_H
#define CLASSES_GF_GFITEMBOX_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfMenuItemUtil.h"

namespace gf { class GfItemBox; }

namespace gf {
// the item box's lists by item type (1.0.0's symbols: a virtual destructor that does nothing)
class GfItemBoxBase {
public:
    virtual ~GfItemBoxBase();  // slot 0
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among
    // GfItemBoxBase's functions in gf_item_manager and is called on the GfItemBox singleton's GfItemBoxBase. What it
    // does: walks the items of a type from begin(type) and sums the stack count (bits 19-28 of each item's word) of
    // those with an id (bits 0-12); GfItemUtil::isEnableAddItemBox, GfEquipUtil, GfMenuItemUtil::canBuyItem and
    // GfMenuGameAdapter's type 19 call it.
    int fn_71002F9DD4(ItemType::Type type);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reasons. What it
    // does: the number of a type's entries (from begin(type) to that type's list end); GfMenuObjShop's
    // StoreListListener and GfMenuGameAdapter's type 20 call it.
    int fn_71002F9F6C(ItemType::Type type);
};

// the item box singleton (1.0.0's symbols: GfItemBoxBase is its second base, at 8, by the _ZThn8_ thunks of its
// destructors)
class GfItemBox : public ::mm::mtl::PtrSingleton< ::gf::GfItemBox>, public GfItemBoxBase {
public:
    virtual ~GfItemBox();  // slot 0
};
}  // namespace gf

#endif
