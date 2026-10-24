#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfDataItem.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuItemUtil.h"
#include "plugin/Bdat.h"

namespace gf {

GfMenuItemList::GfMenuItemList() {}

GfMenuItemList::~GfMenuItemList() {
    ;  // the original stores the table: its body had a statement the build compiles away
}

GfMenuItemList* GfMenuItemList::create() {
#line 67
    GfMenuItemList* list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuItemList;
    list->addRef();
    return list;
}

void GfMenuItemList::filterRarity(const FiltertInfo& filter) {
    for (unsigned int i = 0; i < getSize();) {
        MenuItemInfo item = getContents(i);
        unsigned int rarity = GfDataItem::getRarity(item.m_id);
        if (rarity == filter.m_rarity) {
            ++i;
        } else {
            decItem(item, false);
        }
    }
}

void GfMenuItemList::filterRarityMore(const FiltertInfo& filter) {
    for (unsigned int i = 0; i < getSize();) {
        MenuItemInfo item = getContents(i);
        unsigned int rarity = GfDataItem::getRarity(item.m_id);
        if (rarity < filter.m_rarity) {
            ++i;
        } else {
            decItem(item, false);
        }
    }
}

void GfMenuItemList::filterCollectionType(const FiltertInfo& filter) {
    for (unsigned int i = 0; i < getSize();) {
        MenuItemInfo item = getContents(i);
        ItemProperty property;
        GfItemUtil::getProperty(property, item.m_id, 0);
        if (property.m_type == 7 && property.m_collectionKey == filter.m_collectionKey) {
            ++i;
        } else {
            decItem(item, false);
        }
    }
}

void GfMenuItemList::filterFavoriteType(const FiltertInfo& filter) {
    for (unsigned int i = 0; i < getSize();) {
        MenuItemInfo item = getContents(i);
        ItemProperty property;
        GfItemUtil::getProperty(property, item.m_id, 0);
        if (property.m_type == 10 && property.m_favoriteKey == filter.m_favoriteKey) {
            ++i;
        } else {
            decItem(item, false);
        }
    }
}

void GfMenuItemList::updateCount() {
    for (unsigned int i = 0; i < getSize(); ++i) {
        MenuItemInfo& item = getContents(i);
        if (GfMenuItemUtil::canCountStack(item.m_type) && item.m_id != 0) {
            item.m_count = GfItemUtil::getItemBoxCount(item.m_id);
        }
    }
}

void GfMenuItemList::setupFromHanaParts(const HanaPartsSetup& setup) {
    ui::UIListInfoBase::SetupParam param = setup.m_setup;
    UIListInfo<MenuItemInfo>::setup(getAllocator(ALLOCATOR(0)), param);
    if (!isValid()) {
        return;
    }
    if (setup.m_type < 16 || setup.m_type > 20) {
        return;
    }
    unsigned char* fp = GfDataBdat::getFP(setup.m_type + 0x40);
    unsigned int top = Bdat::getIdTop(fp);
    unsigned int end = Bdat::getIdEnd(fp);
    for (unsigned int id = top; id <= end; ++id) {
        ItemProperty property;
        GfItemUtil::getProperty(property, id, 0);
        if (property.m_needEther != 0) {
            MenuItemInfo item;
            item.m_type = setup.m_type;
            item.m_id = id;
            item.m_count = GfItemUtil::getItemBoxCount(id);
            addContents(item);
        }
    }
}

bool GfMenuItemList::sortNameDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    const char* key = GfMenuBdat::getSortKeyName();
    unsigned int keyA;
    unsigned int keyB;
    if (key != nullptr) {
        keyA = (unsigned int)(unsigned long)Bdat::getVal(GfMenuBdat::getItemDataFP(a.m_type, a.m_id), key, a.m_id);
        keyB = (unsigned int)(unsigned long)Bdat::getVal(GfMenuBdat::getItemDataFP(b.m_type, b.m_id), key, b.m_id);
    } else {
        keyA = a.m_id;
        keyB = b.m_id;
    }
    if (keyA == keyB) {
        return a.m_id < b.m_id;
    }
    return keyA > keyB;
}

bool GfMenuItemList::sortNameAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    const char* key = GfMenuBdat::getSortKeyName();
    unsigned int keyA;
    unsigned int keyB;
    if (key != nullptr) {
        keyA = (unsigned int)(unsigned long)Bdat::getVal(GfMenuBdat::getItemDataFP(a.m_type, a.m_id), key, a.m_id);
        keyB = (unsigned int)(unsigned long)Bdat::getVal(GfMenuBdat::getItemDataFP(b.m_type, b.m_id), key, b.m_id);
    } else {
        keyA = a.m_id;
        keyB = b.m_id;
    }
    if (keyA == keyB) {
        return a.m_id < b.m_id;
    }
    return keyA < keyB;
}

bool GfMenuItemList::sortRareAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    unsigned int rarityA = getSortRarity(a);
    unsigned int rarityB = getSortRarity(b);
    if (rarityA == rarityB) {
        return a.m_id < b.m_id;
    }
    return rarityA < rarityB;
}

bool GfMenuItemList::sortRareDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    unsigned int rarityA = getSortRarity(a);
    unsigned int rarityB = getSortRarity(b);
    if (rarityA == rarityB) {
        return a.m_id < b.m_id;
    }
    return rarityA > rarityB;
}

bool GfMenuItemList::sortSellPriceAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemPrice priceA;
    ItemPrice priceB;
    GfItemUtil::getPrice(priceA, a.m_id, 0);
    GfItemUtil::getPrice(priceB, b.m_id, 0);
    if (priceA.m_sellPrice == priceB.m_sellPrice) {
        return a.m_id < b.m_id;
    }
    return priceA.m_sellPrice < priceB.m_sellPrice;
}

bool GfMenuItemList::sortSellPriceDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemPrice priceA;
    ItemPrice priceB;
    GfItemUtil::getPrice(priceA, a.m_id, 0);
    GfItemUtil::getPrice(priceB, b.m_id, 0);
    if (priceA.m_sellPrice == priceB.m_sellPrice) {
        return a.m_id < b.m_id;
    }
    return priceA.m_sellPrice > priceB.m_sellPrice;
}

bool GfMenuItemList::sortTypeBoosterAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 12) {
        return false;
    }
    if (propB.m_type != 12) {
        return true;
    }
    if (propA.m_boosterKey == propB.m_boosterKey) {
        return a.m_id < b.m_id;
    }
    return propA.m_boosterKey < propB.m_boosterKey;
}

bool GfMenuItemList::sortTypeBoosterDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 12) {
        return false;
    }
    if (propB.m_type != 12) {
        return true;
    }
    if (propA.m_boosterKey == propB.m_boosterKey) {
        return a.m_id < b.m_id;
    }
    return propA.m_boosterKey > propB.m_boosterKey;
}

bool GfMenuItemList::sortTypeCollectionAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 7) {
        return false;
    }
    if (propB.m_type != 7) {
        return true;
    }
    if (propA.m_collectionKey == propB.m_collectionKey) {
        return a.m_id < b.m_id;
    }
    return propA.m_collectionKey < propB.m_collectionKey;
}

bool GfMenuItemList::sortTypeCollectionDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 7) {
        return false;
    }
    if (propB.m_type != 7) {
        return true;
    }
    if (propA.m_collectionKey == propB.m_collectionKey) {
        return a.m_id < b.m_id;
    }
    return propA.m_collectionKey > propB.m_collectionKey;
}

bool GfMenuItemList::sortTypeFavoriteAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 10) {
        return false;
    }
    if (propB.m_type != 10) {
        return true;
    }
    if (propA.m_favoriteKey == propB.m_favoriteKey) {
        return a.m_id < b.m_id;
    }
    return propA.m_favoriteKey < propB.m_favoriteKey;
}

bool GfMenuItemList::sortTypeFavoriteDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 10) {
        return false;
    }
    if (propB.m_type != 10) {
        return true;
    }
    if (propA.m_favoriteKey == propB.m_favoriteKey) {
        return a.m_id < b.m_id;
    }
    return propA.m_favoriteKey > propB.m_favoriteKey;
}

bool GfMenuItemList::sortTypeAsCoreAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 9) {
        return false;
    }
    if (propB.m_type != 9) {
        return true;
    }
    GfItemUtil::getProperty(propA, propA.m_enhance, 0);
    GfItemUtil::getProperty(propB, propB.m_enhance, 0);
    if (propA.m_coreKey == propB.m_coreKey) {
        return a.m_id < b.m_id;
    }
    return propA.m_coreKey < propB.m_coreKey;
}

bool GfMenuItemList::sortTypeAsCoreDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 9) {
        return false;
    }
    if (propB.m_type != 9) {
        return true;
    }
    GfItemUtil::getProperty(propA, propA.m_enhance, 0);
    GfItemUtil::getProperty(propB, propB.m_enhance, 0);
    if (propA.m_coreKey == propB.m_coreKey) {
        return a.m_id < b.m_id;
    }
    return propA.m_coreKey > propB.m_coreKey;
}

bool GfMenuItemList::sortTypeAsCoreEquipAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 3) {
        return false;
    }
    if (propB.m_type != 3) {
        return true;
    }
    if (propA.m_coreKey == propB.m_coreKey) {
        return a.m_id < b.m_id;
    }
    return propA.m_coreKey < propB.m_coreKey;
}

bool GfMenuItemList::sortTypeAsCoreEquipDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 3) {
        return false;
    }
    if (propB.m_type != 3) {
        return true;
    }
    if (propA.m_coreKey == propB.m_coreKey) {
        return a.m_id < b.m_id;
    }
    return propA.m_coreKey > propB.m_coreKey;
}

bool GfMenuItemList::sortTypeTreasureAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 8) {
        return false;
    }
    if (propB.m_type != 8) {
        return true;
    }
    if (propA.m_treasureKey == propB.m_treasureKey) {
        return a.m_id < b.m_id;
    }
    return propA.m_treasureKey < propB.m_treasureKey;
}

bool GfMenuItemList::sortTypeTreasureDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 8) {
        return false;
    }
    if (propB.m_type != 8) {
        return true;
    }
    if (propA.m_treasureKey == propB.m_treasureKey) {
        return a.m_id < b.m_id;
    }
    return propA.m_treasureKey > propB.m_treasureKey;
}

bool GfMenuItemList::sortWpnRankAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 1) {
        return false;
    }
    if (propB.m_type != 1) {
        return true;
    }
    if (propA.m_weaponRank == propB.m_weaponRank) {
        return a.m_id < b.m_id;
    }
    return propA.m_weaponRank < propB.m_weaponRank;
}

bool GfMenuItemList::sortWpnRankDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 1) {
        return false;
    }
    if (propB.m_type != 1) {
        return true;
    }
    if (propA.m_weaponRank == propB.m_weaponRank) {
        return a.m_id < b.m_id;
    }
    return propA.m_weaponRank > propB.m_weaponRank;
}

bool GfMenuItemList::sortFavoriteTimeAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 10) {
        return false;
    }
    if (propB.m_type != 10) {
        return true;
    }
    if (propA.m_favoriteTime == propB.m_favoriteTime) {
        return a.m_id < b.m_id;
    }
    return propA.m_favoriteTime < propB.m_favoriteTime;
}

bool GfMenuItemList::sortFavoriteTimeDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 10) {
        return false;
    }
    if (propB.m_type != 10) {
        return true;
    }
    if (propA.m_favoriteTime == propB.m_favoriteTime) {
        return a.m_id < b.m_id;
    }
    return propA.m_favoriteTime > propB.m_favoriteTime;
}

bool GfMenuItemList::sortGetAreaAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    unsigned int areaA;
    unsigned int areaB;
    if (a.m_type == 8) {
        unsigned char* fp = GfDataBdat::getFP(0x94);
        areaA = (unsigned short)(unsigned long)Bdat::getVal(fp, "Zone", a.m_id);
        areaB = (unsigned short)(unsigned long)Bdat::getVal(fp, "Zone", b.m_id);
    } else {
        areaA = a.m_id;
        areaB = b.m_id;
    }
    if (areaA == areaB) {
        return a.m_id < b.m_id;
    }
    return areaA < areaB;
}

bool GfMenuItemList::sortGetAreaDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    unsigned int areaA;
    unsigned int areaB;
    if (a.m_type == 8) {
        unsigned char* fp = GfDataBdat::getFP(0x94);
        areaA = (unsigned short)(unsigned long)Bdat::getVal(fp, "Zone", a.m_id);
        areaB = (unsigned short)(unsigned long)Bdat::getVal(fp, "Zone", b.m_id);
    } else {
        areaA = a.m_id;
        areaB = b.m_id;
    }
    if (areaA == areaB) {
        return a.m_id < b.m_id;
    }
    return areaA > areaB;
}

bool GfMenuItemList::sortIdAscending(const MenuItemInfo& a, const MenuItemInfo& b) {
    return a.m_id < b.m_id;
}

bool GfMenuItemList::sortIdDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    return a.m_id > b.m_id;
}

}  // namespace gf
