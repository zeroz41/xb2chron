#ifndef CLASSES_GF_GFITEMBOX_H
#define CLASSES_GF_GFITEMBOX_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfMenuItemUtil.h"

namespace gf { class GfItemBox; }

namespace gf {
// a handle to one item box entry (1.0.0's symbols take it by value; 3.0.1's callers pass a copy by address, so it
// is not trivially copyable). The field name is not the original's.
struct GfItemHandle {
    GfItemHandle() : m_handle(0) {}
    GfItemHandle(const GfItemHandle& other) : m_handle(other.m_handle) {}
    unsigned int m_handle;
};

// the item box's lists by item type (1.0.0's symbols: a virtual destructor that does nothing)
class GfItemBoxBase {
public:
    virtual ~GfItemBoxBase();  // slot 0
    int countItem(unsigned int item);
    bool isMulti(ItemType::Type type);  // whether a type's items stack (else each entry is one item)
    int countItemWithoutEquip(unsigned int item);
    unsigned int getItemTime(unsigned int item, GfItemHandle handle);
    void setEquipFlag(unsigned int item, GfItemHandle handle, bool equip);
    GfItemHandle getNoEquipItemHandle(unsigned int item);
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
    static bool addItem(unsigned int item, unsigned int count);
    static bool decItem(unsigned int item, unsigned int count);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among GfItemBox's
    // functions in gf_item_manager (between addItem and decItem's neighbours) and takes no object. What it does:
    // passes the item and a copy of the handle to the singleton's GfItemBoxBase fn_71002F9634 and returns its
    // bool; GfItemUtil::fn_71002FA968 calls it when its handle is non-zero.
    static bool fn_71002FA2B0(unsigned int item, GfItemHandle handle);
};
}  // namespace gf

#endif
