#ifndef GF_GFITEMUTIL_H
#define GF_GFITEMUTIL_H

#include "classes/gf/GfItemBox.h"

namespace gf {

// an item and how many the party has, as GfItemUtil::getInfo fills it (the field names are not the original's)
struct GfItem {
    // leaves the item and its count to its users (GfItemUtil::getInfo stores them after it)
    GfItem() : pad_4(0), m_handle() {}
    unsigned short m_item;
    unsigned short m_count;
    unsigned short pad_4;
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
    // bit 0: the item exists; bit 2: it cannot be sold; bit 4: a salvage quest needs it (a type 5 item whose
    // salvage quest is set)
    unsigned int m_flags;
    unsigned char pad_4[0x4];
    // the item's kind, as GfMenuItemList's sorts test it (1 weapon rank, 2 enhance, 3 and 9 core, 7 collection,
    // 8 treasure, 10 favorite, 12 booster); the name is not the original's
    int m_type;
    unsigned char pad_C[0x24];
    ItemPrice m_price;  // GfItemUtil::getPrice's
    // what GfMenuItemList's type sorts order the items of one kind by (after which their ids); the names are not the
    // original's, each named for the sort that reads it
    unsigned char pad_44[0x1];
    unsigned char m_boosterKey;     // type 12 (sortTypeBooster*)
    unsigned char pad_46[0x6];
    unsigned char m_coreKey;        // types 3 and 9 (sortTypeAsCoreEquip*, sortTypeAsCore* of the item m_enhance names)
    unsigned char m_collectionKey;  // type 7 (sortTypeCollection*)
    unsigned char m_favoriteKey;    // type 10 (sortTypeFavorite*)
    unsigned char pad_4F[0x3];
    unsigned short m_favoriteTime;  // type 10 (sortFavoriteTime*)
    unsigned char pad_54[0x2];
    // type 2: the BTL_Enhance row the item's effect is (GfMenuItemList's enhance sorts); type 9: an item id
    // (sortTypeAsCore* reads that item's m_coreKey)
    unsigned short m_enhance;
    unsigned char pad_58[0x5];
    unsigned char m_treasureKey;    // type 8 (sortTypeTreasure*)
    unsigned char pad_5E[0x6];
    unsigned char m_weaponRank;     // type 1 (sortWpnRank*)
    // type 2: update_IconAll shows it + 1 (the name is not the original's)
    unsigned char m_iconIndex;
    unsigned char pad_66[0x2];
    // what GfMenuItemAdapter's Hana part callbacks show (the names are not the original's)
    int m_needEther;   // update_needEther
    int m_dustEther;   // update_dustEther
    unsigned char pad_70[0x5];
    unsigned char m_role;    // update_roleText: the FP text row (0: none)
    unsigned char m_pArmor;  // update_PArmor
    unsigned char m_eArmor;  // update_EArmor
    unsigned char m_revise[6];  // update_revise shows the first that is not 0
    unsigned char pad_7E[0x2];
};

// the items' helpers (functions, by their symbols)
class GfItemUtil {
public:
    // the items of a type the party has (each item id of the type counted in the box)
    static int getCountByType(ItemType::Type type);
    static int getItemBoxCount(unsigned int item);  // how many of the item the party has
    // count of the item into the party's box (an event call follows); false when it could not be added
    static bool addItemBox(unsigned int item, int count);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's addItemBox, 168 bytes, did this
    // inline). A member because addItemBox and addItemBoxWithSilent of this unit call it. What it does: refuses a
    // positive count of an item GfDataItem::isNoMultiple marks; adds (GfItemBox::addItem) or removes
    // (GfItemBox::decItem) the count, or with a non-zero handle sets that entry (fn_71002FA2B0); marks a gained
    // item with GfDataItem::setNoMultiple; unless silent, calls GfEvent::callItemAdd.
    static bool fn_71002FA968(unsigned int item, int count, bool silent, GfItemHandle handle);
    // count of the item into the party's box without the event call
    static bool addItemBoxWithSilent(unsigned int item, int count);
    static int getItemBoxCountWithoutEquip(unsigned int item);
    // whether count of the item fits in (count > 0) or can be taken from (count < 0) the box
    static bool isEnableAddItemBox(unsigned int item, int count);
    static unsigned int getType(unsigned int item);
    static int getEnableStock(unsigned int item);  // how many of the item the box may hold
    static void getProperty(ItemProperty& property, unsigned int item, unsigned int);
    static void getPrice(ItemPrice& price, unsigned int item, unsigned int shop);
    static GfItem getInfo(unsigned int item);
    static bool isPrecious(unsigned int item);  // an item of type 6
    static unsigned int getItemTime(unsigned int item, GfItemHandle handle);
    // the item's type, when its index in the type's table is 0 (else 0)
    static unsigned int getItemCategory(unsigned int item);
    static int getCrystalNum();  // the crystals (type 11 items) the party has
    // false for a crystal whose BDAT condition (GfBdatItem::getCrystalListCondition) does not hold
    static bool isValidCrystal(unsigned int item);
    static void setEquipFlag(unsigned int item, GfItemHandle handle, bool equip);
    static GfItemHandle getNoEquipItemHandle(unsigned int item);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lies among GfItemUtil's
    // functions (its unit). What it does: forwards to fn_7100247474, which for a DLC driver (0x11-0x19) gives the
    // 16-bit item id at +0x5A4 of its row of GfDataManager::fn_7100224A10's driver table, else 0.
    // GfMenuItemAdapter::ReferenceDriverEquipConverter shows it as slot 0's accessory of such a driver on menu layer 3.
    static unsigned int fn_71002FCD64(unsigned int driver);
};

}  // namespace gf

#endif
