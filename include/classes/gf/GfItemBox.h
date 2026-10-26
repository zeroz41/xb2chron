#ifndef CLASSES_GF_GFITEMBOX_H
#define CLASSES_GF_GFITEMBOX_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfMenuItemUtil.h"
#include "mm/mtl/Array.h"

namespace gf { class GfItemBox; }

namespace gf {
// a handle to one item box entry (1.0.0's symbols take it by value; 3.0.1's callers pass a copy by address, so it
// is not trivially copyable). The field name is not the original's.
struct GfItemHandle {
    GfItemHandle() : m_handle(0) {}
    GfItemHandle(const GfItemHandle& other) : m_handle(other.m_handle) {}
    unsigned int m_handle;
};

// one item box entry (1.0.0's symbols: GfItemInfo, 12 bytes: its constructor zeroes 8 bytes then 4). The id is the
// index in the type's BDAT range (getItemID adds getItemStartID - 1). Field names are not the original's.
struct GfItemInfo {
    ItemType::Type getType() const { return static_cast<ItemType::Type>(m_type); }
    GfItemHandle getHandle() const;
    unsigned short getItemID() const;
    void setType(ItemType::Type type);

    unsigned int m_id : 13;
    unsigned int m_type : 6;
    unsigned int m_count : 10;  // the stack count (GfItemBoxBase::fn_71002F9DD4 sums it)
    unsigned int pad_0_29 : 1;
    unsigned int m_equip : 1;  // setEquipFlag
    unsigned int pad_0_31 : 1;
    unsigned int m_time;  // getItemTime
    unsigned int m_serial;  // the handle's bits 6-31 (getHandle)
};

class GfItemBoxBase;

// walks a type's entries (1.0.0's symbols: item_iterator::operator++ returns a copy). Field names are not the
// original's; the step is the type's entry size, which 3.0.1's operator++ no longer reads (it walks pointers).
struct item_iterator {
    item_iterator(GfItemBoxBase* box, GfItemInfo** cur, unsigned int step, bool multi, ItemType::Type type)
        : m_box(box), m_cur(cur), m_step(step), m_multi(multi), m_type(type) {}
    item_iterator operator++();

    GfItemBoxBase* m_box;
    GfItemInfo** m_cur;
    unsigned int m_step;
    bool m_multi;
    ItemType::Type m_type;
};

// one item type's range of entries in the box (1.0.0's symbols: setItemTypeInfo, getItemTypeInfo; the struct's
// and its fields' names are not the original's)
struct ItemTypeInfo {
    ItemTypeInfo() : m_begin(nullptr), m_end(nullptr), m_multi(false), m_serial(nullptr), m_maxSlot(0), m_step(0),
                     m_maxStack(0) {}
    GfItemInfo** m_begin;
    GfItemInfo** m_end;
    bool m_multi;  // isMulti
    unsigned int* m_serial;  // updateSerialLocal counts it up
    unsigned short m_maxSlot;  // maxStockItem of a type whose entries do not stack
    unsigned short m_step;
    unsigned short m_maxStack;  // maxStockItem of a stacking type
};

// the item box's lists by item type (1.0.0's symbols: a virtual destructor; 3.0.1's frees 19 pointer arrays)
class GfItemBoxBase {
public:
    GfItemBoxBase();
    virtual ~GfItemBoxBase();  // slot 0
    // the index of a type's ItemTypeInfo (inline in 3.0.1; 1.0.0 had getItemTypeInfo out of line)
    static unsigned int getTypeIndex(ItemType::Type type) {
        switch (static_cast<int>(type)) {
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        case 5: return 4;
        case 6: return 5;
        case 7: return 8;
        case 8: return 9;
        case 9: return 10;
        case 10: return 11;
        case 11: return 12;
        case 12: return 13;
        case 14: return 6;
        case 15: return 7;
        case 16: return 14;
        case 17: return 15;
        case 18: return 16;
        case 19: return 17;
        case 20: return 18;
        default: return 0;
        }
    }
    ItemTypeInfo& getItemTypeInfo(ItemType::Type type) { return m_info[getTypeIndex(type)]; }
    const ItemTypeInfo& getItemTypeInfo(ItemType::Type type) const { return m_info[getTypeIndex(type)]; }
    item_iterator begin(ItemType::Type type);
    item_iterator end(ItemType::Type type);
    GfItemInfo* findItem(unsigned int item);
    GfItemInfo* findItemHandle(unsigned int item, GfItemHandle handle);
    bool addItem(unsigned int item, GfItemHandle& handle);
    bool decItem(unsigned int item, unsigned int count);
    unsigned int updateSerialLocal(ItemType::Type type);
    int countItem(unsigned int item);
    bool isMulti(ItemType::Type type);  // whether a type's items stack (else each entry is one item)
    int countItemWithoutEquip(unsigned int item);
    unsigned int maxStockItem(unsigned int item);
    unsigned int getItemTime(unsigned int item);
    unsigned int getItemTime(unsigned int item, GfItemHandle handle);
    void setEquipFlag(unsigned int item, GfItemHandle handle, bool equip);
    GfItemHandle getNoEquipItemHandle(unsigned int item);
    // 1.0.0's name: its canAddItem(unsigned int) sits at the same place (after setType, before decItem) and its
    // GfItemBox::addItem(unsigned, unsigned) calls it at the same site as 3.0.1's (fn_71002F9004 in the symbols)
    bool canAddItem(unsigned int item);
    // Placeholder name: new in 3.0.1 (between decItem and countItem; 1.0.0 had makeItem there, a different
    // signature). GfItemBox::fn_71002FA2B0 passes it an item and a handle copy and returns its bool.
    bool fn_71002F9634(unsigned int item, GfItemHandle handle);
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
    // Placeholder name: new in 3.0.1 (1.0.0 had setItemBox(ItemBox*, bool) instead). GfItemBox::fn_71002FA0F4 calls it
    // with SDataGame's favorite item types and item box; it sets up the 19 type lists from them.
    void fn_71002F3F98(unsigned char* favoriteItemType, unsigned char* itemBox);

    ItemTypeInfo m_info[19];
    unsigned char* m_favoriteItemType;  // GfDataItem::getFavoriteItemType
    unsigned char* m_itemBox;  // GfDataItem::getItemBox
    ::mm::mtl::Array<GfItemInfo*> m_lists[19];
};

// the item box singleton (1.0.0's symbols: GfItemBoxBase is its second base, at 8, by the _ZThn8_ thunks of its
// destructors)
class GfItemBox : public ::mm::mtl::PtrSingleton< ::gf::GfItemBox>, public GfItemBoxBase {
public:
    virtual ~GfItemBox();  // slot 0
    static bool addItem(unsigned int item, unsigned int count);
    static bool decItem(unsigned int item, unsigned int count);
    static bool decItemForNewGame(unsigned int item, unsigned int count);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among GfItemBox's
    // functions in gf_item_manager (between addItem and decItem's neighbours) and takes no object. What it does:
    // passes the item and a copy of the handle to the singleton's GfItemBoxBase fn_71002F9634 and returns its
    // bool; GfItemUtil::fn_71002FA968 calls it when its handle is non-zero.
    static bool fn_71002FA2B0(unsigned int item, GfItemHandle handle);
    // Placeholder name: the symbols call it GfItemInfo::getMaxStock() const, but it reads no object: it frees the
    // singleton's 19 lists and clears its two SDataGame pointers (1.0.0's getMaxStock reads a type's max stock).
    // GfItemManager::destroy calls it. Rename proposed.
    static void fn_71002FA134();
    // Placeholder name: new in 3.0.1. GfItemManager::initialize calls it with a type it passes on to
    // GfDataItem::getFavoriteItemType; it hands the two SDataGame pointers to the singleton's fn_71002F3F98.
    static void fn_71002FA0F4(unsigned int type);
};
}  // namespace gf

#endif
