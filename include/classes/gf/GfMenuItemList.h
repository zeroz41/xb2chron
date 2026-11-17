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
    // signed: decItem subtracts from it and erases the item at 0 or below (ldrsh), and hands it on sign-extended
    short m_count;
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
        // more than 8 bytes: GfMenuObjPouch2::updateItemList keeps it below its ItemBoxSetup, not in the 8-byte hole
        // by its callee-saved register
        unsigned char m_armorTypeMode;  // filterIraAccWpn: 0 drops armor type 2, 1 keeps only armor type 2 of m_equipIcon
        unsigned char m_equipIcon;      // filterIraAccWpn keeps the items of this GfBdatItem::getPcEquipIcon
        unsigned char pad_09[3];
    };
    // what setupFromBox lists: the items of one type in the item box (the names are not the original's)
    struct ItemBoxSetup {
        // inline: its stores are its users' (GfMenuObjCylinderSelect's)
        ItemBoxSetup() : m_type(0), m_filter(nullptr), pad_20(), pad_28(1), pad_29(1), pad_2A(0), pad_2B(0), pad_2C(false) {}
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
    // what setupFromShopExcTask lists: the SetItem/SetNumber columns of a row of BDAT file 0xF2 (the names are not
    // the original's)
    struct ItemShopExcSetup {
        ItemShopExcSetup() : m_id(0) {}  // GfMenuObjShop::setupExcItem's clears the row
        ui::UIListInfoBase::SetupParam m_setup;  // the list's
        unsigned int m_id;                       // the row
    };
    // what setupFromQuestReward lists: a reward id's items (GfMenuObjShop::getExcTaskReward; the names are not the
    // original's)
    struct QuestRewardSetup {
        // GfMenuObjQuestReward::RewardListener's clears the reward id (stored before calls that set it)
        QuestRewardSetup() : m_reward(0) {}
        ui::UIListInfoBase::SetupParam m_setup;  // the list's
        unsigned int m_reward;                   // the reward id
    };
    // what setupFromMissionReward lists: GfMenuObjQuestReward::RewardListener fills one with its number
    // reference's value (the names are not the original's)
    struct MissionRewardSetup {
        MissionRewardSetup() : m_reward(0) {}
        ui::UIListInfoBase::SetupParam m_setup;  // the list's
        unsigned int m_reward;                   // the number reference's value
    };
    // what setupFromHanaParts lists (the field names are not the original's)
    struct HanaPartsSetup {
        // inline: GfMenuObjHanaPartsMake::updateItemList's stores zero 0x18-0x27
        HanaPartsSetup() : m_type(0), pad_18() {}
        ui::UIListInfoBase::SetupParam m_setup;  // the list's
        unsigned int m_type;  // the parts' ItemType::Type (16-20; their BDAT file is GfDataBdat's type + 0x40)
        unsigned char pad_18[0x10];
    };
    GfMenuItemList();
    virtual ~GfMenuItemList();  // slot 0
    static GfMenuItemList* create();  // with a reference for the caller
    // adds an item to the list (GfMenuObjDrArtsSet2::initialize adds items 0x633D-0x633F with false)
    void addItem(const MenuItemInfo& item, bool flag);
    void setupFromBox(const ItemBoxSetup& setup);
    void setupFromQuestReward(const QuestRewardSetup& setup);
    void setupFromMissionReward(const MissionRewardSetup& setup);
    void addListFromBox(const ItemBoxSetup& setup);  // setupFromBox's items added to the list
    void filterRarity(const FiltertInfo& filter);
    void filterRarityMore(const FiltertInfo& filter);
    void filterCollectionType(const FiltertInfo& filter);
    void filterFavoriteType(const FiltertInfo& filter);
    // 2.0.0's symbols name it. What it does: with expansion 3, keeps the type 2 items m_armorTypeMode/m_equipIcon pick
    void filterIraAccWpn(const FiltertInfo& filter);
    void updateCount();
    void setupFromHanaParts(const HanaPartsSetup& setup);  // every part of the type that needs ether  // the stackable items' counts from the item box
    void decItem(const MenuItemInfo& item, bool);
    // takes count off the item at index (erasing it at 0 or below); with the bool, a SCOM_ADD_ITEM request of -count
    void decItem(unsigned int index, unsigned int count, bool);
    // 2.0.0's symbols name them. decItemH: decItem of the item findItemH finds (GfMenuObjShop::NumSelectListener);
    // findItemH: the index of the item with the same type, id and box handle, -1 when none
    void decItemH(const MenuItemInfo& item, bool);
    unsigned int findItemH(const MenuItemInfo& item);
    void setupFromShop(const ItemShopSetup& setup);
    void setupFromShopExcTask(const ItemShopExcSetup& setup);
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
    // 2.0.0's symbols name them. What they do: sortTypeWpnAccesoryAscending / sortTypeWpnAccesoryDescending order by
    // the enhance key GfBdatItem::getPcEquipAddAtr reads, asc/desc, then the item id; sortTypeAccesoryAscending /
    // sortTypeAccesoryDescending the same for the other enhance key (see the bodies).
    static bool sortTypeWpnAccesoryAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeWpnAccesoryDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeAccesoryAscending(const MenuItemInfo& a, const MenuItemInfo& b);
    static bool sortTypeAccesoryDescending(const MenuItemInfo& a, const MenuItemInfo& b);
    // 2.0.0's symbols name them.
    void sortFromBuff(unsigned int order);
    void sortFromRole(unsigned int order);
    void sortFromEnhance(unsigned int order);
    // 2.0.0's symbols name it. What it does: the key sortFromEnhance sorts by: for items of types 2, 3, 18 and 20 (type
    // 9: of the item its ItemProperty::m_enhance names) whose m_enhance2 row has an effect, that effect's
    // GfBdatBtl::getBTL_EnhanceEffSortCat value (0 when it is s_PrioEnhanceSortCat); else 24.
    static unsigned int getEnhanceSortCat(const MenuItemInfo& item);
    // the key value sortFromBuff / sortFromRole / sortFromEnhance put first (their order argument). 2.0.0's symbols
    // name them
    static unsigned int s_PrioEnhanceSortCat;
    static unsigned int s_PrioRole;
    static unsigned int s_PrioBuff;
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
