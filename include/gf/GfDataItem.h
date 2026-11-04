#ifndef GF_GFDATAITEM_H
#define GF_GFDATAITEM_H

#include "gf/GfMenuItemUtil.h"
#include "gf/SDataGame.h"

namespace gf {
// the items' data, by their item id (functions, by its symbols)
class GfDataItem {
public:
    // the item's category (fn_710030EB68 matches collect tasks by it)
    static unsigned int getCategory(unsigned int item);
    static const char* getName(unsigned int item);
    static int getRarity(unsigned int item);  // GfMenuItemAdapter::update_RareIcon's icon
    // the message table and row of the item's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int item);
    static unsigned int getItemType(unsigned int item);  // 2: an accessory (DataObjDriver::setVirtualEquipAcc)
    // an item id's type and its index in that type's table (GfItemBox entries hold both: bits 13-18, 0-12)
    static bool getItemType(ItemType::Type& type, unsigned int& index, unsigned int item);
    // the first and the end item id of a type
    static bool getItemBdatCount(unsigned int& begin, unsigned int& end, ItemType::Type type);
    static bool isNoMultiple(unsigned int item);  // an item the party may hold once, already gained
    static void setNoMultiple(unsigned int item, bool set);
    static unsigned int getPrice(unsigned int item);  // the item's BDAT price
    static bool isEnableSell(unsigned int item);  // false for types 4 and 6, else the type's BDAT no-sell flag
    static bool isFavoriteCategoryFood(unsigned int category);
    static bool isMayItem(unsigned int item);
    static bool isTukiItem(unsigned int item);
    static bool isMusubiCookItem(unsigned int item);
    static bool isYuohCookItem(unsigned int item);
    static unsigned int getItemStartID(ItemType::Type type);  // the type's first BDAT row, 0 for none
    static float getFavoriteItemTime(unsigned int item);  // GfBdatItem::getFavoriteTime in seconds (x 60)
    // the item type of an item category: 11 below 4, 7 below 12, 10 below 24, 8 below 28, 6 below 30, else 0
    static unsigned int getTypeByItemCategory(unsigned int category);
    // SDataGame::m_favoriteItemType. No parameter: its body reads none and its one caller (GfItemBox::initialize)
    // passes none (1.0.0's getFavoriteItemType(unsigned int) is a different function: a GfBdatItem lookup).
    static ItemBox* getFavoriteItemType();
    static SDataGame::ItemBoxEx* getItemBox();  // SDataGame::m_itemBox
};
}  // namespace gf

#endif
