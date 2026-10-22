#ifndef GF_GFITEMUTIL_H
#define GF_GFITEMUTIL_H

namespace gf {

// an item's price, as GfItemUtil::getPrice reads it (inline constructor: its users zero it)
struct ItemPrice {
    ItemPrice() : pad_0() {}
    unsigned char pad_0[0x14];
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
    unsigned char pad_44[0x3C];
};

// the items' helpers (functions, by their symbols)
class GfItemUtil {
public:
    static unsigned int getItemBoxCount(unsigned int item);  // how many of the item the party has
    static void getProperty(ItemProperty& property, unsigned int item, unsigned int);
};

}  // namespace gf

#endif
