#ifndef GF_GFITEMUTIL_H
#define GF_GFITEMUTIL_H

namespace gf {

// an item's price, as GfItemUtil::getPrice reads it (inline constructor: its users zero it)
struct ItemPrice {
    ItemPrice() : pad_0(), m_price(0), m_sellPrice(0), pad_C() {}
    unsigned char pad_0[0x4];
    int m_price;      // GfMenuItemAdapter::update_Price shows it (the names are not the original's)
    unsigned int m_sellPrice;  // update_SellPrice (GfMenuItemList's sell price sorts compare it unsigned)
    unsigned char pad_C[0x8];
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
    unsigned char pad_65[0x3];
    // what GfMenuItemAdapter's Hana part callbacks show (the names are not the original's)
    int m_needEther;   // update_needEther
    int m_dustEther;   // update_dustEther
    unsigned char pad_70[0x6];
    unsigned char m_pArmor;  // update_PArmor
    unsigned char m_eArmor;  // update_EArmor
    unsigned char pad_78[0x8];
};

// the items' helpers (functions, by their symbols)
class GfItemUtil {
public:
    static unsigned int getItemBoxCount(unsigned int item);  // how many of the item the party has
    // count of the item into the party's box (1.0.0's name: 3.0.1's symbols spell it fn_71002FA93C)
    static void addItemBox(unsigned int item, int count);
    static void getProperty(ItemProperty& property, unsigned int item, unsigned int);
    static void getPrice(ItemPrice& price, unsigned int item, unsigned int shop);
};

}  // namespace gf

#endif
