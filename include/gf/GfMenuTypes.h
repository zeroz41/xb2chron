#ifndef GF_GFMENUTYPES_H
#define GF_GFMENUTYPES_H

namespace gf { namespace GfMenuTypes {

// what a full-screen layer is opened with (GfMenuFullScreen::registLayerParam copies its 0x20 bytes, 8 at a time)
struct Param {
    // its users' code zeroes the first 0x10 bytes as one 8-aligned block, and no more
    Param() : m_menuId(0), m_value(0), pad_8() {}
    union {
        unsigned int m_menuId;  // the menu: GfMenuObject::getMenuLayerID's argument
        // the same word as two halves (GfMenuObjBlWeapon2::openForShop stores each, its initialize reads the word):
        // the open type and its parameter (the names are not the original's)
        struct {
            unsigned short m_type;
            unsigned short m_param;
        } m_halves;
    };
    // a value for the menu: GfMenuObjBlKizunaRing::openForMercenary stores its second argument, its initialize
    // reads it back (the name is not the original's)
    unsigned int m_value;
    unsigned char pad_8[8];
    // 8-byte words: GfMenuFullScreen::registLayerParam's temporary keeps its copy of the Param 8-aligned (a byte
    // array with alignas(8) put it 4 bytes lower)
    unsigned long pad_10[2];
};

}}  // namespace gf::GfMenuTypes

#endif
