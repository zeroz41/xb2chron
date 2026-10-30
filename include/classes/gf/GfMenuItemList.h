#ifndef CLASSES_GF_GFMENUITEMLIST_H
#define CLASSES_GF_GFMENUITEMLIST_H

#include "classes/gf/GfItemBox.h"
#include "classes/ui/UIListInfo.h"
#include "gf/GfDataItem.h"

namespace gf {
// an item as the menus' item lists hold it (GfMenuItemList::setupFromBox fills one per item; the names are not the
// original's)
class MenuItemInfo {
public:
    MenuItemInfo() : m_type(0), m_id(0), m_count(0) {}
    unsigned int m_type;     // its ItemType::Type
    unsigned int m_id;       // the item's id
    unsigned short m_count;
    // the list position sort(1) stores, its time table's index (the name is not the original's)
    unsigned short m_sortIndex;
    // the item's handle in the box (setupFromBox copies the entry's third word; sort(1) passes it to
    // GfItemUtil::getItemTime; a copy copies it apart from the rest: GfMenuObjCylinderSelect's copy of a list item)
    GfItemHandle m_entry;
};

// table 0x7100B5F488
class GfMenuItemList : public ::ui::UIListInfo< ::gf::MenuItemInfo> {
public:
    // what the filters keep (ItemBoxSetup's m_filter; the field names are not the original's)
    struct FiltertInfo {
        unsigned int m_flags;           // which filters setupFromBox applies
        unsigned char m_rarity;         // filterRarity keeps this rarity, filterRarityMore the ones below it
        unsigned char m_collectionKey;  // filterCollectionType keeps type 7 items of this ItemProperty key
        unsigned char m_favoriteKey;    // filterFavoriteType keeps type 10 items of this ItemProperty key
    };
    // what setupFromBox lists: the items of one type in the item box (the names are not the original's)
    struct ItemBoxSetup {
        // inline: its stores are its users' (GfMenuObjCylinderSelect's)
        ItemBoxSetup() : m_filter(nullptr), pad_20(), pad_28(1), pad_29(1), pad_2A(0), pad_2B(0), pad_2C(false) {}
        ui::UIListInfoBase::SetupParam m_setup;  // the list's
        unsigned int m_type;                     // the items' ItemType::Type
        const FiltertInfo* m_filter;             // its first word's bits pick the filters setupFromBox applies
        unsigned char pad_20[8];
        // byte fields (plain bytes: GfMenuObjHanaPartsCrystal::makeCategoryItemList zeroes 0x28-0x29 as one halfword
        // apart from 0x2A-0x2B); setupFromBox reads 0x29, and 0x2A-0x2B as a 16-bit pair
        unsigned char pad_28;
        unsigned char pad_29;
        unsigned char pad_2A;
        unsigned char pad_2B;
        bool pad_2C;
    };
    // what setupFromShop lists: a shop's goods (GfMenuObjBlWeapon2::seqSrcAppear fills one; the names are not the
    // original's)
    struct ItemShopSetup {
        ui::UIListInfoBase::SetupParam m_setup;  // the list's
        unsigned int m_shop;                     // the shop
    };
    struct ItemShopExcSetup;
    struct QuestRewardSetup;
    struct MissionRewardSetup;
    // what setupFromHanaParts lists (the field names are not the original's)
    struct HanaPartsSetup {
        ui::UIListInfoBase::SetupParam m_setup;  // the list's
        unsigned int m_type;  // the parts' ItemType::Type (16-20; their BDAT file is GfDataBdat's type + 0x40)
    };
    GfMenuItemList();
    virtual ~GfMenuItemList();  // slot 0
    static GfMenuItemList* create();  // with a reference for the caller
    // adds an item to the list (GfMenuObjDrArtsSet2::initialize adds items 0x633D-0x633F with false)
    void addItem(const MenuItemInfo& item, bool flag);
    void setupFromBox(const ItemBoxSetup& setup);
    void addListFromBox(const ItemBoxSetup& setup);  // setupFromBox's items added to the list
    void filterRarity(const FiltertInfo& filter);
    void filterRarityMore(const FiltertInfo& filter);
    void filterCollectionType(const FiltertInfo& filter);
    void filterFavoriteType(const FiltertInfo& filter);
    void updateCount();
    void setupFromHanaParts(const HanaPartsSetup& setup);  // every part of the type that needs ether  // the stackable items' counts from the item box
    void decItem(const MenuItemInfo& item, bool);
    void setupFromShop(const ItemShopSetup& setup);
    void sort(unsigned int order, bool);
    // the sort orders (comparators for UIListInfo::sort): each orders by its key, then by item id
    static bool sortNameDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortNameAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortRareAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortRareDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortSellPriceAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortSellPriceDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeBoosterAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeBoosterDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeCollectionAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeCollectionDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeFavoriteAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeFavoriteDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeAsCoreAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeAsCoreDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeAsCoreEquipAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeAsCoreEquipDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeTreasureAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeTreasureDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortWpnRankAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortWpnRankDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortFavoriteTimeAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortFavoriteTimeDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortGetAreaAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortGetAreaDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortIdAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortIdDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because sort(5/9) picks them as
    // comparators for type 2 items (this class's sort orders). What they do: fn_710037749C / fn_7100377614 order
    // by the enhance key GfBdatItem::fn_7100202C3C reads, asc/desc, then the item id; fn_710037777C /
    // fn_71003778C0 the same for the other enhance key (see the bodies).
    static bool fn_710037749C(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool fn_7100377614(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool fn_710037777C(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool fn_71003778C0(const MenuItemInfo& a, const MenuItemInfo& b);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because sort(order) calls them
    // with this and order - 0x50 (fn_7100377F28), order - 0x40 (fn_7100378144), order - 0x20 (fn_710037835C);
    // each sorts the list with a comparator lambda of its own (tables 0x7100B5F660, 0x7100B5F618, 0x7100B5F5D0).
    void fn_7100377F28(unsigned int order);
    void fn_7100378144(unsigned int order);
    void fn_710037835C(unsigned int order);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because only fn_710037835C calls
    // it, once per item. What it does: the key fn_710037835C sorts by: for items of types 2, 3, 18 and 20 (type 9:
    // of the item its ItemProperty::m_enhance names) whose m_enhance2 row has an effect, that effect's
    // GfBdatBtl::fn_71001E80D0 value (0 when it is s_firstEnhanceSortKey); else 24.
    static unsigned int fn_7100378524(const MenuItemInfo& item);
    // the key value fn_7100377F28 / fn_7100378144 / fn_710037835C put first (their order argument). Proposed names,
    // not the original's: the symbols leave them unnamed (lbl_7100EA70C0, lbl_7100EA70BC, lbl_7100EA70B8)
    static unsigned int s_firstEnhanceSortKey;
    static unsigned int s_firstRole;
    static unsigned int s_firstPartsSortKey;
    // the rarity the rarity sorts read: none for types 6, 14 and 15 (1.0.0 has it out of line; 3.0.1 inlines it)
    static unsigned int getSortRarity(const MenuItemInfo& item) {
        switch (item.m_type) {
        case 6:
        case 14:
        case 15:
            return 0;
        default:
            return GfDataItem::getRarity(item.m_id);
        }
    }
};
}  // namespace gf

#endif
