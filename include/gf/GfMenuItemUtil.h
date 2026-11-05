#ifndef GF_GFMENUITEMUTIL_H
#define GF_GFMENUITEMUTIL_H

namespace ui { class UIStr; }
namespace gf { struct GfItemHandle; }

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
    static int getItemNum(unsigned char type, unsigned int id);  // GfItemUtil::getItemBoxCount(id)
    // the party driver that has the accessory (item and handle) equipped, 0 for none; slot gets its slot (one more
    // when GfMenuObjUtil::isValidExpansion(3) holds; 0 for a DLC driver's own accessory). The name is 1.0.0's: its
    // searchEquipAcc has the same callers (canEquipAcc, GfMenuObjDrEquip2); 2.0.0's symbols name it too
    static unsigned short searchEquipAcc(unsigned int item, GfItemHandle handle, unsigned int* slot);
    // the blade that has the Hana part (item and handle) of that parts slot equipped, 0 for none (its callers:
    // GfMenuObjHanaCustom::refreshItemList shows that blade's name; parameter names inferred)
    static unsigned int searchEquipHanaParts(unsigned int partsId, unsigned int item, GfItemHandle handle);
    // whether the party has the money for the item at the shop and room for it in its box
    static bool canBuyItem(unsigned int item, unsigned int shop);
    // false when the party's money is at its maximum, else GfDataItem::isEnableSell
    static bool canSellItem(unsigned int item, unsigned int);
    static bool canSellItemType(unsigned int type);  // false for types 4 and 6 and outside 1-12
    // 0 when the orb can be made, 1 when the orb box is full, 2 when the recipe is not enabled, 3 without a recipe
    static int canCreateOrb(unsigned int item);
    // a common window id for an equip error (1-4)
    static unsigned int getEquipErrorCmnWindowID(unsigned int error);
    static bool getIconNumber(ItemType::Type type, unsigned int id, unsigned int& number, bool);
    // whether an item (GfMenuItemAdapter::update_canStack) or an item type (GfMenuGameAdapter's type 19) counts its
    // stack
    static bool canCountStack(unsigned int id);
    // 2.0.0's symbols name it. What it does: whether an item is bound to a blade: by GfDataItem::getItemType (2:
    // GfBdatItem::getPcEquipDriver, 3: getEquipOrbBlade, 20: getITM_HanaAssistBlade, else false) the item row's
    // blade/driver value, true when it is not 0 and equals blade. GfMenuHanaAdapter::isEquipParts passes a Hana part
    // and Hana.
    static bool isModelChangeItem(unsigned int item, unsigned int blade);
};

}  // namespace gf

#endif
