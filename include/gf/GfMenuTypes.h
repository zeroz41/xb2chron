#ifndef GF_GFMENUTYPES_H
#define GF_GFMENUTYPES_H

namespace gf { namespace GfMenuTypes {

// what a full-screen layer is opened with (GfMenuFullScreen::registLayerParam copies its 0x20 bytes, 8 at a time)
struct Param {
    // its users' code zeroes the first 0x10 bytes as one 8-aligned block, and no more
    Param() : m_menuId(0), pad_4() {}
    union {
        unsigned int m_menuId;  // the menu: GfMenuObject::getMenuLayerID's argument
        // the same word as two halves (GfMenuObjBlWeapon2::openForShop stores each, its initialize reads the word):
        // the open type and its parameter (the names are not the original's)
        struct {
            unsigned short m_type;
            unsigned short m_param;
        } m_halves;
    };
    unsigned char pad_4[0xC];
    alignas(8) unsigned char pad_10[0x10];
};

}}  // namespace gf::GfMenuTypes

#endif
