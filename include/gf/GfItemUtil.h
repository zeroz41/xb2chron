#ifndef GF_GFITEMUTIL_H
#define GF_GFITEMUTIL_H

namespace gf {

// an item's price, as GfItemUtil::getPrice reads it (inline constructor: its users zero it)
struct ItemPrice {
    ItemPrice() : pad_0(), m_price(0), m_sellPrice(0), pad_C() {}
    unsigned char pad_0[0x4];
    int m_price;      // GfMenuItemAdapter::update_Price shows it (the names are not the original's)
    int m_sellPrice;  // update_SellPrice
    unsigned char pad_C[0x8];
};

// what GfItemUtil::getProperty reads about an item (the field names are not the original's)
struct ItemProperty {
    // inline: its stores are its users' (GfMenuObjCylinderSelect's)
    ItemProperty() : m_flags(0) {}
    // bit 0: the item exists; bit 2: it cannot be sold; bit 4: a salvage quest needs it (a type 5 item whose
    // salvage quest is set)
    unsigned int m_flags;
    unsigned char pad_4[0x2C];
    ItemPrice m_price;  // GfItemUtil::getPrice's
    unsigned char pad_44[0x24];
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
    static void getProperty(ItemProperty& property, unsigned int item, unsigned int);
    static void getPrice(ItemPrice& price, unsigned int item, unsigned int shop);
};

}  // namespace gf

#endif
