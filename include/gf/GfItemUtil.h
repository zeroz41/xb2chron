#ifndef GF_GFITEMUTIL_H
#define GF_GFITEMUTIL_H

#include "classes/gf/GfItemBox.h"
#include "mm/mtl/FixedVector.h"

namespace gf {

// an item and how many the party has, as GfItemUtil::getInfo fills it (the field names are not the original's)
struct GfItem {
    // leaves the item and its count to its users (GfItemUtil::getInfo stores them after it)
    GfItem() : m_equipChar(0), m_handle() {}
    unsigned short m_item;
    unsigned short m_count;
    // the driver or blade that has the entry equipped (getInfo(FixedVector&, ...): getEquipChar of an equipped entry,
    // else 0; the name is not the original's)
    unsigned short m_equipChar;
    GfItemHandle m_handle;  // zeroed as GfItemHandle's constructor does (and it makes GfItem returned by address)
};

// an item's price, as GfItemUtil::getPrice reads it (inline constructor: its users zero it)
struct ItemPrice {
    ItemPrice() : m_basePrice(0), m_price(0), m_sellPrice(0), m_hundredth(0), m_eightHundredth(0) {}
    // GfItemUtil::getPrice's: the item's BDAT price, then the shop's (discounted by the zone's development level) and
    // the sell price, half the BDAT price; the last two are a 100th and an 800th of it, at least 1 (what reads them is
    // not known). The names are not the original's.
    unsigned int m_basePrice;
    int m_price;      // GfMenuItemAdapter::update_Price shows it (the names are not the original's)
    unsigned int m_sellPrice;  // update_SellPrice (GfMenuItemList's sell price sorts compare it unsigned)
    unsigned int m_hundredth;
    unsigned int m_eightHundredth;
};

// what GfItemUtil::getProperty reads about an item (the field names are not the original's)
struct ItemProperty {
    // inline: its stores are its users' (GfMenuObjCylinderSelect's)
    ItemProperty() : m_flags(0) {}
    // getProperty's first step (the symbol of its static, _ZZN2gf12ItemProperty5clearEvE6szNull, names it): every
    // field but m_time zeroed, the debug name pointed at an empty string
    void clear() {
        static const char* szNull = "";
        m_flags = 0;
        m_item = 0;
        m_index = 0;
        m_type = 0;
        m_count = 0;
        pad_E = 0;
        m_stock = 0;
        m_zone = 0;
        m_debugName = szNull;
        m_bdat = nullptr;
        m_name = 0;
        m_caption = 0;
        m_price.m_basePrice = 0;
        m_price.m_price = 0;
        m_price.m_sellPrice = 0;
        m_price.m_hundredth = 0;
        m_price.m_eightHundredth = 0;
        m_rarity = 0;
        m_boosterKey = 0;
        m_boosterIdea = 0;
        pad_48 = 0;
        m_enhance2 = 0;
        m_coreKey = 0;
        m_collectionKey = 0;
        m_favoriteKey = 0;
        m_favoriteType = 0;
        m_favoriteTime = 0;
        m_recipe = 0;
        m_enhance = 0;
        m_preciousCategory = 0;
        m_preciousType = 0;
        pad_5C = 0;
        m_treasureKey = 0;
        m_treasureGraphic = 0;
        m_treasureFlag = 0;
        pad_62 = 0;
        m_weaponRank = 0;
        m_iconIndex = 0;
        m_needEther = 0;
        m_dustEther = 0;
        m_condition = 0;
        m_partsSortKey = 0;
        m_attribute = 0;
        m_role = 0;
        m_pArmor = 0;
        m_eArmor = 0;
        for (int i = 0; i < 6; i++) {
            m_revise[i] = 0;
        }
        pad_7E = 0;
    }
    // bit 0: the item exists; bit 2: it cannot be sold; bit 4: a salvage quest needs it (a type 5 item whose
    // salvage quest is set)
    unsigned int m_flags;
    // the item id getProperty was asked for (getPropertyAcce and getPropertyHanaRole read their BDAT rows by it); the
    // name is not the original's
    unsigned short m_item;
    unsigned short m_index;  // the item's index in its type's BDAT range (GfDataItem::getItemType)
    // the item's kind, as GfMenuItemList's sorts test it (1 weapon rank, 2 enhance, 3 and 9 core, 7 collection,
    // 8 treasure, 10 favorite, 12 booster); the name is not the original's
    int m_type;
    unsigned short m_count;  // how many the party has (GfItemBoxBase::countItem)
    unsigned short pad_E;
    unsigned short m_stock;  // getEnableStock
    unsigned short m_zone;   // types 7, 8 and 10: the BDAT row's zone
    unsigned int m_time;     // GfItemBoxBase::getItemTime (clear leaves it)
    // the item's BDAT debug name (getPropertyAcce: the PcEquip row's); the name is not the original's
    const char* m_debugName;
    // the item's name and caption (GfDataItem::getName / getCaption: the BDAT and its row ids)
    unsigned char* m_bdat;
    unsigned int m_name;
    unsigned int m_caption;
    ItemPrice m_price;  // GfItemUtil::getPrice's
    // what GfMenuItemList's type sorts order the items of one kind by (after which their ids); the names are not the
    // original's, each named for the sort that reads it
    unsigned char m_rarity;  // GfDataItem::getRarity
    unsigned char m_boosterKey;     // type 12 (sortTypeBooster*): the booster category
    unsigned char m_boosterIdea;    // type 12: GfBdatItem::getBoosterIdea
    unsigned short pad_48;
    // type 2: a second BTL_Enhance row (the enhance sorts GfMenuItemList::sortTypeWpnAccesoryAscending / sortTypeWpnAccesoryDescending order by
    // its effect and params); the name is not the original's
    unsigned short m_enhance2;
    unsigned char m_coreKey;        // types 3 and 9 (sortTypeAsCoreEquip*, sortTypeAsCore* of the item m_enhance names)
    unsigned char m_collectionKey;  // type 7 (sortTypeCollection*)
    unsigned char m_favoriteKey;    // type 10 (sortTypeFavorite*)
    unsigned short m_favoriteType;  // type 10
    unsigned short m_favoriteTime;  // type 10 (sortFavoriteTime*)
    unsigned short m_recipe;        // type 9: GfBdatItem::getEmptyOrbRecipe
    // type 2: the BTL_Enhance row the item's effect is (GfMenuItemList's enhance sorts); type 9: an item id
    // (sortTypeAsCore* reads that item's m_coreKey)
    unsigned short m_enhance;
    // type 6: the precious (or PreciousIra) row's category and type
    unsigned short m_preciousCategory;
    unsigned short m_preciousType;
    unsigned char pad_5C;
    unsigned char m_treasureKey;    // type 8 (sortTypeTreasure*)
    // type 8: the Tresure row's graphic and flag
    unsigned short m_treasureGraphic;
    unsigned short m_treasureFlag;
    unsigned short pad_62;
    unsigned char m_weaponRank;     // type 1 (sortWpnRank*)
    // type 2: update_IconAll shows it + 1 (the name is not the original's)
    unsigned char m_iconIndex;
    // what GfMenuItemAdapter's Hana part callbacks show (the names are not the original's)
    int m_needEther;   // update_needEther
    int m_dustEther;   // update_dustEther
    // the game condition (GfGameCond::isGameCond) the item needs; 0: none (GfMenuHanaAdapter::isMakeParts; the name
    // is not the original's)
    unsigned short m_condition;
    // type 19: what GfMenuItemList::sortFromBuff sorts by (the name is not the original's)
    unsigned short m_partsSortKey;
    unsigned char m_attribute;  // type 17: GfBdatItem::getITM_HanaAtrAtr
    unsigned char m_role;    // update_roleText: the FP text row (0: none)
    unsigned char m_pArmor;  // update_PArmor
    unsigned char m_eArmor;  // update_EArmor
    unsigned char m_revise[6];  // update_revise shows the first that is not 0
    unsigned short pad_7E;
};

// the items' helpers (functions, by their symbols)
class GfItemUtil {
public:
    // the items of a type the party has (each item id of the type counted in the box)
    static int getCountByType(ItemType::Type type);
    static int getItemBoxCount(unsigned int item);  // how many of the item the party has
    // how many items of the category the party has (GfQuestTask::refreshTaskParam counts a collect task's category
    // with it)
    static int getCountByItemCategory(unsigned int category);
    // count of the item into the party's box (an event call follows); false when it could not be added
    static bool addItemBox(unsigned int item, int count);
    // GfGameManager::setupGame calls it (symbol _ZN2gf10GfItemUtil19setupItemDataFollowEv)
    static void setupItemDataFollow();
    // empties the box of the event, info, precious and treasure items whose BDAT row clears them on a new game and
    // of items 45005 and 45009; clears the no-multiple mark of 45005, 45009 and 45010 (symbol
    // _ZN2gf10GfItemUtil17setupNewGameParamEv)
    static void setupNewGameParam();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's addItemBox, 168 bytes, did this
    // inline). A member because addItemBox and addItemBoxWithSilent of this unit call it. What it does: refuses a
    // positive count of an item GfDataItem::isNoMultiple marks; adds (GfItemBox::addItem) or removes
    // (GfItemBox::decItem) the count, or with a non-zero handle sets that entry (decItem); marks a gained
    // item with GfDataItem::setNoMultiple; unless silent, calls GfEvent::callItemAdd.
    static bool fn_71002FA968(unsigned int item, int count, bool silent, GfItemHandle handle);
    // count of the item into the party's box without the event call
    static bool addItemBoxWithSilent(unsigned int item, int count);
    static int getItemBoxCountWithoutEquip(unsigned int item);
    // whether count of the item fits in (count > 0) or can be taken from (count < 0) the box
    static bool isEnableAddItemBox(unsigned int item, int count);
    static unsigned int getType(unsigned int item);
    static int getEnableStock(unsigned int item);  // how many of the item the box may hold
    // fills property for the item (shop: the shop whose price getPrice reads); false when the item does not exist
    // or its type has no property part
    static bool getProperty(ItemProperty& property, unsigned int item, unsigned int shop);
    // getProperty's part for an accessory (type 2): the PcEquip row's debug name, enhance, which drivers may equip it
    // (m_flags bits 16-24) and its icon
    static void getPropertyAcce(ItemProperty& property);
    // getProperty's part for a Hana role part (type 16): the ITM_HanaRole row's condition, ether, role and armor
    static void getPropertyHanaRole(ItemProperty& property);
    static void getPrice(ItemPrice& price, unsigned int item, unsigned int shop);
    static GfItem getInfo(unsigned int item);
    // the items of a type the party has
    static void getInfo(::mm::mtl::FixedVector<GfItem, 1024>& items, ItemType::Type type, bool);
    // the driver or blade (an id) that has the item box entry equipped (an accessory, an orb or a Hana part), 0 for none
    static unsigned int getEquipChar(GfItemHandle handle);
    static bool isPrecious(unsigned int item);  // an item of type 6
    static unsigned int getItemTime(unsigned int item, GfItemHandle handle);
    // the item's type, when its index in the type's table is 0 (else 0)
    static unsigned int getItemCategory(unsigned int item);
    static int getCrystalNum();  // the crystals (type 11 items) the party has
    // false for a crystal whose BDAT condition (GfBdatItem::getCrystalListCondition) does not hold
    static bool isValidCrystal(unsigned int item);
    static void setEquipFlag(unsigned int item, GfItemHandle handle, bool equip);
    static GfItemHandle getNoEquipItemHandle(unsigned int item);
};


}  // namespace gf

#endif
