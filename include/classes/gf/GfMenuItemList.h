#ifndef CLASSES_GF_GFMENUITEMLIST_H
#define CLASSES_GF_GFMENUITEMLIST_H

#include "classes/ui/UIListInfo.h"
#include "gf/GfDataItem.h"

namespace gf {
// an item as the menus' item lists hold it (GfMenuItemList::setupFromBox fills one per item; the names are not the
// original's)
class MenuItemInfo {
public:
    // the item box entry's third word (setupFromBox copies it); a copy copies it apart from the rest, so its type
    // has a copy constructor of its own (GfMenuObjCylinderSelect's copy of a list item shows it)
    struct EntryValue {
        EntryValue() : m_value(0) {}
        EntryValue(const EntryValue& other) : m_value(other.m_value) {}
        unsigned int m_value;
    };
    MenuItemInfo() : m_type(0), m_id(0), m_count(0) {}
    unsigned int m_type;     // its ItemType::Type
    unsigned int m_id;       // the item's id
    unsigned short m_count;
    unsigned char pad_A[2];
    EntryValue m_entry;
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
        // one word of byte fields (stored as one): setupFromBox reads 0x29, and 0x2A-0x2B as a 16-bit pair
        unsigned int pad_28 : 8;
        unsigned int pad_29 : 8;
        unsigned int pad_2A : 8;
        unsigned int pad_2B : 8;
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
