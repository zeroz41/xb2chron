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
    // whether an item (GfMenuItemAdapter::update_canStack) or an item type (GfMenuGameAdapter's type 19) counts its
    // stack
    static bool canCountStack(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among this
    // class's functions (between canEquipAcc and searchEquipOrb). What it does: whether an item is bound to a blade:
    // by GfDataItem::getItemType (2: GfBdatItem::fn_7100203610, 3: fn_7100200FE4, 20: fn_7100206788, else false)
    // the item row's blade/driver value, true when it is not 0 and equals blade. GfMenuHanaAdapter::isEquipParts
    // passes a Hana part and Hana.
    static bool fn_71003547CC(unsigned int item, unsigned int blade);
};

}  // namespace gf

#endif
