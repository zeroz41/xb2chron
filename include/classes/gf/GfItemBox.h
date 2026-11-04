#ifndef CLASSES_GF_GFITEMBOX_H
#define CLASSES_GF_GFITEMBOX_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfMenuItemUtil.h"
#include "gf/GfItemInfo.h"
#include "gf/SDataGame.h"
#include "mm/mtl/Array.h"
#include "mm/mtl/FixedArray.h"

namespace gf { class GfItemBox; }

namespace gf {
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
    // 2.0.0's symbols name it. What it does: true when an item of the type with an id has the serial (its handle's bits
    // 6-31); addItem calls it.
    bool findSerial(ItemType::Type type, unsigned int serial);
    // 1.0.0's name: its canAddItem(unsigned int) sits at the same place (after setType, before decItem) and its
    // GfItemBox::addItem(unsigned, unsigned) calls it at the same site as 3.0.1's (fn_71002F9004 in the symbols)
    bool canAddItem(unsigned int item);
    // 2.0.0's symbols name it. GfItemBox::decItem passes it an item and a handle copy and returns its bool.
    bool decItem(unsigned int item, GfItemHandle handle);
    // 2.0.0's symbols name it. What it does: walks the items of a type from begin(type) and sums the stack count (bits
    // 19-28 of each item's word) of those with an id (bits 0-12); GfItemUtil::isEnableAddItemBox, GfEquipUtil,
    // GfMenuItemUtil::canBuyItem and GfMenuGameAdapter's type 19 call it.
    int countItemCategory(ItemType::Type type);
    // 2.0.0's symbols name it. What it does: the number of a type's entries (from begin(type) to that type's list end);
    // GfMenuObjShop's StoreListListener and GfMenuGameAdapter's type 20 call it.
    int maxItemCategory(ItemType::Type type);
    // 2.0.0's symbols name it (1.0.0 had setItemBox(ItemBox*, bool) instead). GfItemBox::initialize calls it with
    // SDataGame's item box (ItemBox) and its second entry area (ItemBoxEx); it sets up the 19 type lists from them
    // (setupItemLists, one instance per item type).
    void setItemBox(ItemBox& favoriteItemType, ItemBoxEx& itemBox);

    ::mm::mtl::FixedArray<ItemTypeInfo, 19> m_info;
    ItemBox* m_favoriteItemType;  // GfDataItem::getFavoriteItemType
    ItemBoxEx* m_itemBox;  // GfDataItem::getItemBox
    ::mm::mtl::FixedArray< ::mm::mtl::Array<GfItemInfo*>, 19> m_lists;
};

// 2.0.0's symbols name it (one instance per item type, items and extra the type's FixedArrays of ItemBox and
// ItemBoxEx): GfItemBoxBase::setItemBox calls one instance per item type. It points list `index` at the type's
// ItemBox entries (and, when multi, its entries of the second area) and fills ItemTypeInfo `index` (1.0.0's
// GfItemBoxBase::setItemTypeInfo set the same fields).
template <typename Items, typename Extra>
void setupItemLists(ItemBox& box, unsigned int index, ::mm::mtl::FixedArray<ItemTypeInfo, 19>& infos,
                    ::mm::mtl::FixedArray< ::mm::mtl::Array<GfItemInfo*>, 19>& lists, Items& items, Extra& extra,
                    unsigned short maxStack, bool multi);

// the item box singleton (1.0.0's symbols: GfItemBoxBase is its second base, at 8, by the _ZThn8_ thunks of its
// destructors)
class GfItemBox : public ::mm::mtl::PtrSingleton< ::gf::GfItemBox>, public GfItemBoxBase {
public:
    virtual ~GfItemBox();  // slot 0
    static bool addItem(unsigned int item, unsigned int count);
    static bool decItem(unsigned int item, unsigned int count);
    static bool decItemForNewGame(unsigned int item, unsigned int count);
    // 2.0.0's symbols name it. What it does: passes the item and a copy of the handle to the singleton's GfItemBoxBase
    // decItem and returns its bool; GfItemUtil::fn_71002FA968 calls it when its handle is non-zero.
    static bool decItem(unsigned int item, GfItemHandle handle);
    // 2.0.0's symbols name it. GfItemManager's finalize (inlined in destroy) calls it on GfItemBox::get(); its body
    // reaches the object through get() again.
    void finalize();
    // 2.0.0's symbols name it. GfItemManager's initialize (inlined in its constructor) calls it on GfItemBox::get() and
    // passes nothing else. It hands GfDataItem::getFavoriteItemType() and getItemBox() (the two SDataGame pointers) to
    // the singleton's setItemBox.
    void initialize();
};
}  // namespace gf

#endif
