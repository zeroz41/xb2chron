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
    // the message table and row of the item's caption (GfItemUtil::getProperty; returns true once it set them)
    static bool getCaption(unsigned char*& bdat, unsigned int& id, unsigned int item);
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
    // items 108-113: local 8-bit flags 2166-2171 count up, capped at 255 (GfGameUtilShop::execChangeItem)
    static void addCraftFlag(unsigned int item);
    // items 739-853 (nine groups): sets the item's 1-bit local flag from 56736 on, then stores each group's count
    // of set flags (capped at 255) in the 8-bit local flags 4275-4283
    static void setCraftFlag(unsigned int item, bool set);
    static unsigned int getItemStartID(ItemType::Type type);  // the type's first BDAT row, 0 for none
    static float getFavoriteItemTime(unsigned int item);  // GfBdatItem::getFavoriteTime in seconds (x 60)
    // the item type of an item category: 11 below 4, 7 below 12, 10 below 24, 8 below 28, 6 below 30, else 0
    static unsigned int getTypeByItemCategory(unsigned int category);
    // SDataGame::m_itemBox and m_itemBoxExtend. 2.0.0's symbols name both (carried as getFavoriteItemType and
    // getItemBox before; 1.0.0's getItemBox returns the same field, see ItemBox).
    static ItemBox* getItemBox();
    static ItemBoxEx* getItemBoxExtend();  // SDataGame::m_itemBoxExtend
    // 2.0.0's symbols name it. What it does: whether id is in 25501-25999 (GfItemUtil::getCountByItemCategory,
    // getEnableStock, getProperty pass an item id).
    static bool isValidPreciousIra(unsigned int id);
    // 2.0.0's symbols name it. What it does: whether id is 40260-40268 or 40312.
    static bool isHomuraCookItem(unsigned int id);
};
}  // namespace gf

#endif
