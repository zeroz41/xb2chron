#include "classes/gf/GfItemBox.h"
#include "gf/GfDataItem.h"
#include "gf/GfItemUtil.h"
#include "gf/GfDataBlade.h"
#include "gf/GfEquipUtil.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfGameCond.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataDevelop.h"
#include "classes/gf/GfBdatShop.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfReqCommand.h"

namespace gf {

int GfItemUtil::getCountByType(ItemType::Type type) {
    unsigned int begin, end;
    int count = 0;
    if (GfDataItem::getItemBdatCount(begin, end, type)) {
        for (unsigned int item = begin; item < end; item++) {
            count += GfItemBox::get()->countItem(item);
        }
    }
    return count;
}

int GfItemUtil::getItemBoxCount(unsigned int item) {
    return GfItemBox::get()->countItem(item);
}

bool GfItemUtil::addItemBox(unsigned int item, int count) {
    return fn_71002FA968(item, count, false, GfItemHandle());
}

bool GfItemUtil::fn_71002FA968(unsigned int item, int count, bool silent, GfItemHandle handle) {
    if (count > 0 && GfDataItem::isNoMultiple(item)) {
        return false;
    }
    bool result;
    if (handle.m_handle != 0) {
        result = GfItemBox::fn_71002FA2B0(item, handle);
    } else if (count < 0) {
        result = GfItemBox::decItem(item, -count);
    } else {
        result = GfItemBox::addItem(item, count);
    }
    if (result && count > 0) {
        GfDataItem::setNoMultiple(item, true);
    }
    if (!silent && result) {
        GfEvent::callItemAdd(item, count);
    }
    return result;
}

bool GfItemUtil::addItemBoxWithSilent(unsigned int item, int count) {
    if (count > 0) {
        if (!GfDataItem::isNoMultiple(item) && GfItemBox::addItem(item, count)) {
            GfDataItem::setNoMultiple(item, true);
            return true;
        }
        return false;
    }
    if (count >= 0) {
        return GfItemBox::addItem(item, count);
    }
    return GfItemBox::decItem(item, -count);
}

int GfItemUtil::getItemBoxCountWithoutEquip(unsigned int item) {
    return GfItemBox::get()->countItemWithoutEquip(item);
}

bool GfItemUtil::isEnableAddItemBox(unsigned int item, int count) {
    ItemType::Type type = static_cast<ItemType::Type>(GfDataItem::getItemType(item));
    if (count > 0) {
        int have;
        if (GfItemBox::get()->isMulti(type)) {
            have = GfItemBox::get()->countItem(item);
        } else {
            have = GfItemBox::get()->fn_71002F9DD4(type);
        }
        int stock = getEnableStock(item);
        return stock > have && stock - have >= count;
    }
    if (count < 0) {
        return GfItemBox::get()->countItem(item) >= -count;
    }
    return false;
}

unsigned int GfItemUtil::getType(unsigned int item) {
    return GfDataItem::getItemType(item);
}

void GfItemUtil::getPrice(ItemPrice& price, unsigned int item, unsigned int shop) {
    unsigned int base = GfDataItem::getPrice(item);
    price.m_basePrice = base;
    price.m_price = base;
    price.m_sellPrice = base >> 1;
    price.m_hundredth = 0;
    price.m_eightHundredth = 0;
    if (base == 0) {
        return;
    }
    GfBdatShop* bdat = GfBdatShop::get();
    int level = GfDataDevelop::getLevel(GfGameManager::getMapZoneID());
    float value = price.m_basePrice;
    if (shop != 0 && level != 0) {
        value = value + value * bdat->getShopListDiscount(shop, level - 1) * -0.01f;
    }
    unsigned int result = value;
    price.m_price = result == 0 ? 1 : result;
    float basePrice = price.m_basePrice;
    result = basePrice * 0.01f;
    price.m_hundredth = result == 0 ? 1 : result;
    result = basePrice * 0.00125f;
    price.m_eightHundredth = result == 0 ? 1 : result;
}

GfItem GfItemUtil::getInfo(unsigned int item) {
    GfItem info;
    info.m_count = GfItemBox::get()->countItem(item);
    info.m_item = item;
    return info;
}

bool GfItemUtil::isPrecious(unsigned int item) {
    return GfDataItem::getItemType(item) == 6;
}

unsigned int GfItemUtil::getItemTime(unsigned int item, GfItemHandle handle) {
    return GfItemBox::get()->getItemTime(item, handle);
}

unsigned int GfItemUtil::getItemCategory(unsigned int item) {
    ItemType::Type type;
    unsigned int index;
    if (!GfDataItem::getItemType(type, index, item)) {
        return 0;
    }
    return index == 0 ? type : 0;
}

int GfItemUtil::getCrystalNum() {
    return getCountByType(static_cast<ItemType::Type>(11));
}

bool GfItemUtil::isValidCrystal(unsigned int item) {
    ItemType::Type type;
    unsigned int index;
    if (GfDataItem::getItemType(type, index, item) && type == 11) {
        unsigned int condition = GfBdatItem::get()->getCrystalListCondition(item);
        if (condition != 0) {
            return GfGameCond::isGameCond(condition);
        }
    }
    return true;
}

GfItemHandle GfItemUtil::getNoEquipItemHandle(unsigned int item) {
    return GfItemBox::get()->getNoEquipItemHandle(item);
}

void GfEquipUtil::equipBladeChip(unsigned int blade, unsigned int chip) {
    GfDataBlade::getBladeWeapon(blade);  // its result is not used
    if (GfItemBox::get()->countItem(chip) != 0 && GfItemBox::decItem(chip, 1)) {
        GfEvent::callItemAdd(chip, -1);
    }
    GfDataBlade::setBladeWeapon(blade, GfDataBlade::getBladeWeaponByRank(blade, chip));
    GfReqCommand::reqRebuildPartyWeapon(blade);
}

unsigned int GfEquipUtil::getEquipAcceResult(unsigned int driver, unsigned int slot, unsigned int accessory) {
    return getEquipAcceResult(*GfDataDriver::getSDataDriver(driver), slot, accessory);
}

unsigned int GfEquipUtil::getEquipOrbMax(unsigned int blade) {
    return GfDataBlade::getEquipOrbMax(blade);
}

unsigned int GfEquipUtil::getEquipBladeOrb(unsigned int blade, unsigned int slot) {
    return GfDataBlade::getEquipOrb(blade, slot);
}

}  // namespace gf
