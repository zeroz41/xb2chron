#include "gf/GfItemUtil.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfDataItem.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuItemUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/SCOM_ADD_ITEM.h"
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

void GfMenuItemList::addItem(const MenuItemInfo& item, bool request) {
    unsigned int type = item.m_type;
    unsigned int id = item.m_id;
    unsigned int index = 0xFFFFFFFF;
    for (unsigned int i = 0; i < getSize(); ++i) {
        const MenuItemInfo& contents = getContents(i);
        if (contents.m_type == type && contents.m_id == id) {
            index = i;
            break;
        }
    }
    if (index != 0xFFFFFFFF) {
        getContents(index).m_count += item.m_count;
    } else {
        addContents(item);
    }
    if (request) {
        SCOM_ADD_ITEM::create(item.m_id, item.m_count);
    }
}

void GfMenuItemList::decItem(const MenuItemInfo& item, bool request) {
    unsigned int type = item.m_type;
    unsigned int id = item.m_id;
    unsigned int index = 0xFFFFFFFF;
    for (unsigned int i = 0; i < getSize(); ++i) {
        const MenuItemInfo& contents = getContents(i);
        if (contents.m_type == type && contents.m_id == id) {
            index = i;
            break;
        }
    }
    if (index != 0xFFFFFFFF) {
        decItem(index, item.m_count, request);
    }
}

void GfMenuItemList::decItem(unsigned int index, unsigned int count, bool request) {
    if (index >= getSize()) {
        return;
    }
    MenuItemInfo& item = getContents(index);
    unsigned int id = item.m_id;
    int rest = item.m_count - count;
    if (rest <= 0) {
        m_list.erase(m_list.begin() + index);
        subSize(1);
        m_changed = true;
    } else {
        item.m_count = rest;
    }
    if (request) {
        SCOM_ADD_ITEM::create(id, -count);
    }
}

void GfMenuItemList::fn_7100375BF4(const MenuItemInfo& item, bool request) {
    unsigned int index = fn_7100375C50(item);
    if (index != 0xFFFFFFFF) {
        decItem(index, item.m_count, request);
    }
}

unsigned int GfMenuItemList::fn_7100375C50(const MenuItemInfo& item) {
    for (unsigned int i = 0; i < getSize(); ++i) {
        const MenuItemInfo& contents = getContents(i);
        if (contents.m_type == item.m_type && contents.m_id == item.m_id && contents.m_entry.m_handle == item.m_entry.m_handle) {
            return i;
        }
    }
    return 0xFFFFFFFF;
}

void GfMenuItemList::sort(unsigned int order, bool ascending) {
    if (getSize() == 0) {
        return;
    }
    std::function<bool(const MenuItemInfo&, const MenuItemInfo&)> compare;
    switch (order) {
    case 1: {
        unsigned int* times = new (getAllocator(ALLOCATOR(0)), nullptr, 0, 8) unsigned int[static_cast<unsigned int>(getSize())];
        for (unsigned int i = 0; i < getSize(); i++) {
            times[i] = GfItemUtil::getItemTime(getContents(i).m_id, getContents(i).m_entry);
            getContents(i).m_sortIndex = i;
        }
        if (ascending) {
            UIListInfo<MenuItemInfo>::sort([times](const MenuItemInfo& a, const MenuItemInfo& b) {
                unsigned int timeA = times[a.m_sortIndex];
                unsigned int timeB = times[b.m_sortIndex];
                if (timeA == timeB) {
                    return a.m_id < b.m_id;
                }
                return timeA < timeB;
            });
        } else {
            UIListInfo<MenuItemInfo>::sort([times](const MenuItemInfo& a, const MenuItemInfo& b) {
                unsigned int timeA = times[a.m_sortIndex];
                unsigned int timeB = times[b.m_sortIndex];
                if (timeA == timeB) {
                    return a.m_id < b.m_id;
                }
                return timeA > timeB;
            });
        }
        delete[] times;
        return;
    }
    case 2:
        compare = ascending ? sortNameDescending : sortNameAscending;
        break;
    case 3:
        compare = ascending ? sortRareAscending : sortRareDescending;
        break;
    case 5:
        if (GfItemUtil::getType((m_list.size() != 0 ? m_list[0] : m_dummy).m_id) == 2 && GfMenuObjUtil::fn_710048FD30(3)) {
            unsigned int i = 0;
            for (; i < getSize(); i++) {
                if (GfBdatItem::sys()->getPcEquipArmorType(getContents(i).m_id) != 2) {
                    break;
                }
            }
            if (i == getSize()) {
                compare = ascending ? fn_710037749C : fn_7100377614;
            }
        }
        break;
    case 7:
        compare = ascending ? sortSellPriceAscending : sortSellPriceDescending;
        break;
    case 8:
        compare = ascending ? sortFavoriteTimeAscending : sortFavoriteTimeDescending;
        break;
    case 9:
        switch (GfItemUtil::getType((m_list.size() != 0 ? m_list[0] : m_dummy).m_id)) {
        case 2:
            if (!GfMenuObjUtil::fn_710048FD30(3)) {
                compare = ascending ? fn_710037777C : fn_71003778C0;
            } else {
                unsigned int i = 0;
                for (; i < getSize(); i++) {
                    if (GfBdatItem::sys()->getPcEquipArmorType(getContents(i).m_id) != 2) {
                        break;
                    }
                }
                if (i == getSize()) {
                    compare = ascending ? fn_710037749C : fn_7100377614;
                } else {
                    compare = ascending ? fn_710037777C : fn_71003778C0;
                }
            }
            break;
        case 3:
            compare = ascending ? sortTypeAsCoreEquipAscending : sortTypeAsCoreEquipDescending;
            break;
        case 7:
            compare = ascending ? sortTypeCollectionAscending : sortTypeCollectionDescending;
            break;
        case 8:
            compare = ascending ? sortTypeTreasureAscending : sortTypeTreasureDescending;
            break;
        case 9:
            compare = ascending ? sortTypeAsCoreAscending : sortTypeAsCoreDescending;
            break;
        case 10:
            compare = ascending ? sortTypeFavoriteAscending : sortTypeFavoriteDescending;
            break;
        case 12:
            compare = ascending ? sortTypeBoosterAscending : sortTypeBoosterDescending;
            break;
        }
        break;
    case 10:
        compare = ascending ? sortWpnRankAscending : sortWpnRankDescending;
        break;
    case 12:
        compare = ascending ? sortGetAreaAscending : sortGetAreaDescending;
        break;
    case 13:
        compare = ascending ? sortIdAscending : sortIdDescending;
        break;
    default:
        if (order > 0x50) {
            fn_7100377F28(order - 0x50);
        } else if (order > 0x40) {
            fn_7100378144(order - 0x40);
        } else if (order > 0x20) {
            fn_710037835C(order - 0x20);
        }
        return;
    }
    UIListInfo<MenuItemInfo>::sort(compare);
}

bool GfMenuItemList::fn_710037749C(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 2) {
        return false;
    }
    if (propB.m_type != 2) {
        return true;
    }
    unsigned int keyA = GfBdatItem::sys()->fn_7100202C3C(a.m_id);
    unsigned int keyB = GfBdatItem::sys()->fn_7100202C3C(b.m_id);
    if (keyA == keyB) {
        GfBdatBtl* btl = GfBdatBtl::sys();
        unsigned int effectA = btl->getBTL_EnhanceEnhanceEffect(propA.m_enhance2);
        unsigned int effectB = btl->getBTL_EnhanceEnhanceEffect(propB.m_enhance2);
        if (effectA == 0) {
            return false;
        }
        if (effectB == 0) {
            return true;
        }
        if (effectA == effectB) {
            float paramA = btl->getBTL_EnhanceParam1(propA.m_enhance2);
            float paramB = btl->getBTL_EnhanceParam1(propB.m_enhance2);
            if (paramA == paramB) {
                float param2A = btl->getBTL_EnhanceParam2(propA.m_enhance2);
                float param2B = btl->getBTL_EnhanceParam2(propB.m_enhance2);
                if (param2A == param2B) {
                    return a.m_id < b.m_id;
                }
                return param2A > param2B;
            }
            return paramA > paramB;
        }
        return effectA > effectB;
    }
    return keyA > keyB;
}

bool GfMenuItemList::fn_7100377614(const MenuItemInfo& a, const MenuItemInfo& b) {
    ItemProperty propA;
    ItemProperty propB;
    GfItemUtil::getProperty(propA, a.m_id, 0);
    GfItemUtil::getProperty(propB, b.m_id, 0);
    if (propA.m_type != 2) {
        return false;
    }
    if (propB.m_type != 2) {
        return true;
    }
    unsigned int keyA = GfBdatItem::sys()->fn_7100202C3C(a.m_id);
    unsigned int keyB = GfBdatItem::sys()->fn_7100202C3C(b.m_id);
    if (keyA == keyB) {
        GfBdatBtl* btl = GfBdatBtl::sys();
        unsigned int effectA = btl->getBTL_EnhanceEnhanceEffect(propA.m_enhance2);
        unsigned int effectB = btl->getBTL_EnhanceEnhanceEffect(propB.m_enhance2);
        if (effectA == 0) {
            return false;
        }
        if (effectB == 0) {
            return true;
        }
        if (effectA == effectB) {
            float paramA = btl->getBTL_EnhanceParam1(propA.m_enhance2);
            float paramB = btl->getBTL_EnhanceParam1(propB.m_enhance2);
            if (paramA == paramB) {
                float param2A = btl->getBTL_EnhanceParam2(propA.m_enhance2);
                float param2B = btl->getBTL_EnhanceParam2(propB.m_enhance2);
                if (param2A == param2B) {
                    return a.m_id < b.m_id;
                }
                return param2A > param2B;
            }
            return paramA > paramB;
        }
        return effectA < effectB;
    }
    return keyA < keyB;
}

bool GfMenuItemList::fn_710037777C(const MenuItemInfo& a, const MenuItemInfo& b) {
    GfBdatItem* item = GfBdatItem::sys();
    if (GfItemUtil::getItemCategory(a.m_id) != 2) {
        return false;
    }
    if (GfItemUtil::getItemCategory(b.m_id) != 2) {
        return true;
    }
    GfBdatBtl* btl = GfBdatBtl::sys();
    unsigned int enhanceA = item->getPcEquipEnhance1(a.m_id);
    unsigned int enhanceB = item->getPcEquipEnhance1(b.m_id);
    unsigned int effectA = btl->getBTL_EnhanceEnhanceEffect(enhanceA);
    unsigned int effectB = btl->getBTL_EnhanceEnhanceEffect(enhanceB);
    if (effectA == 0) {
        return false;
    }
    if (effectB == 0) {
        return true;
    }
    if (effectA == effectB) {
        float paramA = btl->getBTL_EnhanceParam1(enhanceA);
        float paramB = btl->getBTL_EnhanceParam1(enhanceB);
        if (paramA == paramB) {
            float param2A = btl->getBTL_EnhanceParam2(enhanceA);
            float param2B = btl->getBTL_EnhanceParam2(enhanceB);
            if (param2A == param2B) {
                return a.m_id < b.m_id;
            }
            return param2A > param2B;
        }
        return paramA > paramB;
    }
    return effectA > effectB;
}

bool GfMenuItemList::fn_71003778C0(const MenuItemInfo& a, const MenuItemInfo& b) {
    GfBdatItem* item = GfBdatItem::sys();
    if (a.m_type != 2) {
        return false;
    }
    if (b.m_type != 2) {
        return true;
    }
    GfBdatBtl* btl = GfBdatBtl::sys();
    unsigned int enhanceA = item->getPcEquipEnhance1(a.m_id);
    unsigned int enhanceB = item->getPcEquipEnhance1(b.m_id);
    unsigned int effectA = btl->getBTL_EnhanceEnhanceEffect(enhanceA);
    unsigned int effectB = btl->getBTL_EnhanceEnhanceEffect(enhanceB);
    if (effectA == 0) {
        return false;
    }
    if (effectB == 0) {
        return true;
    }
    if (effectA == effectB) {
        float paramA = btl->getBTL_EnhanceParam1(enhanceA);
        float paramB = btl->getBTL_EnhanceParam1(enhanceB);
        if (paramA == paramB) {
            float param2A = btl->getBTL_EnhanceParam2(enhanceA);
            float param2B = btl->getBTL_EnhanceParam2(enhanceB);
            if (param2A == param2B) {
                return a.m_id < b.m_id;
            }
            return param2A > param2B;
        }
        return paramA > paramB;
    }
    return effectA < effectB;
}

bool GfMenuItemList::sortNameDescending(const MenuItemInfo& a, const MenuItemInfo& b) {
    const char* key = GfMenuBdat::getSortKeyName();
    unsigned int keyA;
    unsigned int keyB;
    if (key != nullptr) {
        keyA = (unsigned int)Bdat::getVal(GfMenuBdat::getItemDataFP(a.m_type, a.m_id), key, a.m_id);
        keyB = (unsigned int)Bdat::getVal(GfMenuBdat::getItemDataFP(b.m_type, b.m_id), key, b.m_id);
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
        keyA = (unsigned int)Bdat::getVal(GfMenuBdat::getItemDataFP(a.m_type, a.m_id), key, a.m_id);
        keyB = (unsigned int)Bdat::getVal(GfMenuBdat::getItemDataFP(b.m_type, b.m_id), key, b.m_id);
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
        areaA = (unsigned short)Bdat::getVal(fp, "Zone", a.m_id);
        areaB = (unsigned short)Bdat::getVal(fp, "Zone", b.m_id);
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
        areaA = (unsigned short)Bdat::getVal(fp, "Zone", a.m_id);
        areaB = (unsigned short)Bdat::getVal(fp, "Zone", b.m_id);
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

// Proposed names, not the original's: the symbols leave them unnamed (lbl_7100EA70B8, lbl_7100EA70BC, lbl_7100EA70C0)
unsigned int GfMenuItemList::s_firstEnhanceSortKey;
unsigned int GfMenuItemList::s_firstRole;
unsigned int GfMenuItemList::s_firstPartsSortKey;

void GfMenuItemList::fn_7100378144(unsigned int order) {
    s_firstRole = order;
    unsigned int* keys = new (getAllocator(ALLOCATOR(0)), nullptr, 0, 8) unsigned int[static_cast<unsigned int>(getSize())];
    for (unsigned int i = 0; i < getSize(); i++) {
        const MenuItemInfo& item = getContents(i);
        ItemProperty prop;
        GfItemUtil::getProperty(prop, item.m_id, 0);
        unsigned int key = 4;
        if (item.m_type == 16 && prop.m_role != 0) {
            key = prop.m_role == s_firstRole ? 0 : prop.m_role;
        }
        keys[i] = key;
        getContents(i).m_sortIndex = i;
    }
    UIListInfo<MenuItemInfo>::sort([keys](const MenuItemInfo& a, const MenuItemInfo& b) {
        unsigned int keyA = keys[a.m_sortIndex];
        unsigned int keyB = keys[b.m_sortIndex];
        if (keyA == keyB) {
            return sortNameAscending(a, b);
        }
        return keyA < keyB;
    });
    delete[] keys;
}

void GfMenuItemList::fn_710037835C(unsigned int order) {
    s_firstEnhanceSortKey = order;
    unsigned int* keys = new (getAllocator(ALLOCATOR(0)), nullptr, 0, 8) unsigned int[static_cast<unsigned int>(getSize())];
    for (unsigned int i = 0; i < getSize(); i++) {
        keys[i] = fn_7100378524(getContents(i));
        getContents(i).m_sortIndex = i;
    }
    UIListInfo<MenuItemInfo>::sort([keys](const MenuItemInfo& a, const MenuItemInfo& b) {
        unsigned int keyA = keys[a.m_sortIndex];
        unsigned int keyB = keys[b.m_sortIndex];
        if (keyA == keyB) {
            return sortNameAscending(a, b);
        }
        return keyA < keyB;
    });
    delete[] keys;
}

}  // namespace gf
