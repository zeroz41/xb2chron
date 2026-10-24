#ifndef GF_GFDATAITEM_H
#define GF_GFDATAITEM_H

#include "gf/GfMenuItemUtil.h"

namespace gf {
// the items' data, by their item id (functions, by its symbols)
class GfDataItem {
public:
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
    static bool isFavoriteCategoryFood(unsigned int category);
    static bool isMayItem(unsigned int item);
    static bool isTukiItem(unsigned int item);
};
}  // namespace gf

#endif
