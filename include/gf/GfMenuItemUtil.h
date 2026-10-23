#ifndef GF_GFMENUITEMUTIL_H
#define GF_GFMENUITEMUTIL_H

namespace ui { class UIStr; }

namespace gf {

// an item's kind (gf::ItemType::Type in the symbols)
struct ItemType {
    enum Type {};
};

// the menus' item helpers (functions, by their symbols; getIconNumber by 1.0.0's)
class GfMenuItemUtil {
public:
    // the item type and id a shop icon (GfDataBdat 0xED's ShopIcon) shows; false when it shows none
    static bool convShopIcon(unsigned int icon, ItemType::Type& type, unsigned int& id);
    // the icon image index of an item; false when it has none
    // the item's name (an empty text when it has none)
    static void getItemName(unsigned char type, unsigned int id, ui::UIStr& name);
    static int canEquipAcc(unsigned int item, unsigned int, unsigned int);  // 0 when the accessory can be equipped
    static bool getIconNumber(ItemType::Type type, unsigned int id, unsigned int& number, bool);
};

}  // namespace gf

#endif
