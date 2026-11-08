#include "gf/SDataPouch.h"
#include "gf/GfDataBladeArts.h"
#include "gf/GfKizunaringBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfEquipUtil.h"
#include "classes/gf/GfQuestManager.h"
#include "gf/GfPouchUtil.h"
#include "gf/GfRecipeOrbUtil.h"
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
#include "gf/GfKizunaringBlade.h"
#include "gf/GfQuestInfo.h"
#include "gf/QuestListAcc.h"
#include "gf/AchievQuest.h"
#include "classes/gf/GfQuestManager.h"
#include "gf/GfPouchUtil.h"
#include "gf/GfRecipeOrbUtil.h"
#include "gf/SDataPouch.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfDataAchievement.h"
#include "gf/GfDataBladeSkill.h"
#include "gf/GfDataBladeArts.h"
#include "gf/GfDataFieldSkill.h"
#include "gf/GfDataUtil.h"
#include "gf/OwnerBonus.h"
#include "classes/gf/GfBdatBtl.h"
#include "gf/GfDataDriverArts.h"
#include "classes/gf/SCOM_ADD_MONEY.h"
#include "classes/gf/SCOM_POPUP.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/SCOM_ITEM_USE.h"
#include "classes/gf/SCOM_ADD_TRUST.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "fw/UpdateInfo.h"
#include "gf/GfShopUtil.h"
#include "classes/gf/GfItemManager.h"
#include "gf/GfUtil.h"
#include "mm/mtl/FixStr.h"
#include "gf/GfDataShop.h"
#include "gf/GfAchievStats.h"
#include "classes/gf/SCOM_ADD_DEVELOP.h"

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

int GfItemUtil::getCountByItemCategory(unsigned int category) {
    GfBdatItem* bdat = GfBdatItem::get();
    unsigned int begin, end;
    int count = 0;
    switch (GfDataItem::getTypeByItemCategory(category)) {
    case 6:
        if (GfDataItem::getItemBdatCount(begin, end, static_cast<ItemType::Type>(6))) {
            for (unsigned int item = begin; item < end; item++) {
                unsigned int itemCategory = GfDataItem::isValidPreciousIra(item) ? bdat->getPreciousIraCategory(item)
                                                                                 : bdat->getPreciousCategory(item);
                if (itemCategory == category) {
                    count += GfItemBox::get()->countItem(item);
                }
            }
        }
        break;
    case 7:
        if (GfDataItem::getItemBdatCount(begin, end, static_cast<ItemType::Type>(7))) {
            for (unsigned int item = begin; item < end; item++) {
                if (bdat->getCollectionListCategory(item) == category) {
                    count += GfItemBox::get()->countItem(item);
                }
            }
        }
        break;
    case 8:
        if (GfDataItem::getItemBdatCount(begin, end, static_cast<ItemType::Type>(8))) {
            for (unsigned int item = begin; item < end; item++) {
                if (bdat->getTresureCategory(item) == category) {
                    count += GfItemBox::get()->countItem(item);
                }
            }
        }
        break;
    case 10:
        if (GfDataItem::getItemBdatCount(begin, end, static_cast<ItemType::Type>(10))) {
            for (unsigned int item = begin; item < end; item++) {
                if (bdat->getFavoriteCategory(item) == category) {
                    count += GfItemBox::get()->countItem(item);
                }
            }
        }
        break;
    }
    return count;
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
        result = GfItemBox::decItem(item, handle);
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
            have = GfItemBox::get()->countItemCategory(type);
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

int GfItemUtil::getEnableStock(unsigned int item) {
    GfBdatItem* bdat = GfBdatItem::get();
    int max;
    switch (GfDataItem::getItemType(item)) {
    case 6:
        max = GfDataItem::isValidPreciousIra(item) ? bdat->getPreciousIraValueMax(item) : bdat->getPreciousValueMax(item);
        if (item == 25305 && GfDataUtil::isIra()) {
            max = 3;
        }
        break;
    case 10: {
        const OwnerBonus& bonus = GfGameManager::getOwnerBonus();
        max = bdat->getFavoriteValueMax(item) + bonus.m_values[3];
        break;
    }
    case 11:
        max = bdat->getCrystalListValueMax(item);
        break;
    case 12: {
        const OwnerBonus& bonus = GfGameManager::getOwnerBonus();
        int value = bdat->getBoosterValueMax(item);
        max = (value == 0 ? 5 : value) + bonus.m_values[13];
        break;
    }
    default:
        max = GfItemBox::get()->maxStockItem(item);
        break;
    }
    return max == 0 ? 1 : max;
}

void GfItemUtil::getPropertyAcce(ItemProperty& property) {
    GfBdatItem* bdat = GfBdatItem::get();
    property.m_debugName = bdat->getPcEquipDebugName(property.m_item);
    property.m_enhance2 = bdat->getPcEquipEnhance1(property.m_item);
    property.m_coreKey = 0;
    if (bdat->isPcEquipFlagEqPC01(property.m_item)) {
        property.m_flags |= 0x10000;
    } else {
        property.m_flags &= ~0x10000;
    }
    if (bdat->isPcEquipFlagEqPC02(property.m_item)) {
        property.m_flags |= 0x20000;
    } else {
        property.m_flags &= ~0x20000;
    }
    if (bdat->isPcEquipFlagEqPC03(property.m_item)) {
        property.m_flags |= 0x40000;
    } else {
        property.m_flags &= ~0x40000;
    }
    if (bdat->isPcEquipFlagEqPC04(property.m_item)) {
        property.m_flags |= 0x80000;
    } else {
        property.m_flags &= ~0x80000;
    }
    if (bdat->isPcEquipFlagEqPC05(property.m_item)) {
        property.m_flags |= 0x100000;
    } else {
        property.m_flags &= ~0x100000;
    }
    if (bdat->isPcEquipFlagEqPC06(property.m_item)) {
        property.m_flags |= 0x200000;
    } else {
        property.m_flags &= ~0x200000;
    }
    if (bdat->isPcEquipFlagEqPC07(property.m_item)) {
        property.m_flags |= 0x400000;
    } else {
        property.m_flags &= ~0x400000;
    }
    if (bdat->isPcEquipFlagEqPC08(property.m_item)) {
        property.m_flags |= 0x800000;
    } else {
        property.m_flags &= ~0x800000;
    }
    if (bdat->isPcEquipFlagEqPC09(property.m_item)) {
        property.m_flags |= 0x1000000;
    } else {
        property.m_flags &= ~0x1000000;
    }
    property.m_iconIndex = bdat->getPcEquipIcon(property.m_item);
}

void GfItemUtil::getPropertyHanaRole(ItemProperty& property) {
    GfBdatItem* bdat = GfBdatItem::get();
    property.m_condition = bdat->getITM_HanaRoleCondition(property.m_item);
    property.m_needEther = bdat->getITM_HanaRoleNeedEther(property.m_item);
    property.m_dustEther = bdat->getITM_HanaRoleDustEther(property.m_item);
    property.m_role = bdat->getITM_HanaRoleRole(property.m_item);
    property.m_pArmor = bdat->getITM_HanaRolePArmor(property.m_item);
    property.m_eArmor = bdat->getITM_HanaRoleEArmor(property.m_item);
    property.m_revise[0] = bdat->getITM_HanaRoleHpMaxRev(property.m_item);
    property.m_revise[1] = bdat->getITM_HanaRoleStrengthRev(property.m_item);
    property.m_revise[2] = bdat->getITM_HanaRolePowEtherRev(property.m_item);
    property.m_revise[3] = bdat->getITM_HanaRoleDexRev(property.m_item);
    property.m_revise[4] = bdat->getITM_HanaRoleAgilityRev(property.m_item);
    property.m_revise[5] = bdat->getITM_HanaRoleLuckRev(property.m_item);
}

bool GfItemUtil::getProperty(ItemProperty& property, unsigned int item, unsigned int shop) {
    property.clear();
    ItemType::Type type;
    unsigned int index;
    if (!GfDataItem::getItemType(type, index, item)) {
        return property.m_flags & 1;
    }
    property.m_flags |= 1;
    property.m_item = item;
    property.m_index = index;
    property.m_type = type;
    property.m_count = GfItemBox::get()->countItem(item);
    property.m_stock = getEnableStock(item);
    property.m_time = GfItemBox::get()->getItemTime(item);
    GfDataItem::getName(property.m_bdat, property.m_name, item);
    GfDataItem::getCaption(property.m_bdat, property.m_caption, item);
    getPrice(property.m_price, item, shop);
    property.m_rarity = GfDataItem::getRarity(item);
    unsigned int& flags = property.m_flags;
    flags = GfDataItem::isEnableSell(item) ? flags & ~4 : flags | 4;
    switch (static_cast<int>(type)) {
    case 1: {
        GfBdatItem* bdat = GfBdatItem::get();
        property.m_debugName = bdat->getPcWpnChipDebugName(property.m_item);
        property.m_weaponRank = bdat->getPcWpnChipRank(property.m_item);
        break;
    }
    case 2:
        getPropertyAcce(property);
        break;
    case 3: {
        GfBdatItem* bdat = GfBdatItem::get();
        property.m_debugName = bdat->getEmptyOrbDebugName(property.m_item);
        property.m_enhance2 = bdat->getEquipOrbEnhance(property.m_item);
        property.m_coreKey = bdat->getEquipOrbEnhanceCategory(property.m_item);
        break;
    }
    case 5:
        property.m_flags = GfBdatItem::get()->getSalvageQuest(property.m_item) == 0 ? property.m_flags & ~0x10
                                                                                     : property.m_flags | 0x10;
        break;
    case 7: {
        GfBdatItem* bdat = GfBdatItem::get();
        property.m_collectionKey = bdat->getCollectionListCategory(property.m_item);
        property.m_zone = bdat->getCollectionListZone(property.m_item);
        break;
    }
    case 8: {
        GfBdatItem* bdat = GfBdatItem::get();
        property.m_treasureKey = bdat->getTresureCategory(property.m_item);
        property.m_treasureGraphic = bdat->getTresureGraphic(property.m_item);
        property.m_zone = bdat->getTresureZone(property.m_item);
        property.m_treasureFlag = bdat->getTresureFlag(property.m_item);
        property.m_flags = bdat->getTresureNoMultiple(property.m_item) == 0 ? property.m_flags & ~8 : property.m_flags | 8;
        break;
    }
    case 9: {
        GfBdatItem* bdat = GfBdatItem::get();
        property.m_debugName = bdat->getEmptyOrbDebugName(property.m_item);
        property.m_recipe = bdat->getEmptyOrbRecipe(property.m_item);
        property.m_enhance = bdat->getEmptyOrbEquipItemID(property.m_item);
        break;
    }
    case 10: {
        GfBdatItem* bdat = GfBdatItem::get();
        property.m_favoriteKey = bdat->getFavoriteCategory(property.m_item);
        property.m_zone = bdat->getFavoriteZone(property.m_item);
        property.m_favoriteType = bdat->getFavoriteType(property.m_item);
        property.m_favoriteTime = bdat->getFavoriteTime(property.m_item);
        break;
    }
    case 11:
    case 14:
    case 15:
        break;
    case 12: {
        GfBdatItem* bdat = GfBdatItem::get();
        property.m_boosterKey = bdat->getBoosterCategory(property.m_item);
        property.m_boosterIdea = bdat->getBoosterIdea(property.m_item);
        break;
    }
    case 16:
        getPropertyHanaRole(property);
        break;
    case 17: {
        GfBdatItem* bdat = GfBdatItem::get();
        property.m_attribute = bdat->getITM_HanaAtrAtr(property.m_item);
        property.m_condition = bdat->getITM_HanaAtrCondition(property.m_item);
        property.m_needEther = bdat->getITM_HanaAtrNeedEther(property.m_item);
        property.m_dustEther = bdat->getITM_HanaAtrDustEther(property.m_item);
        break;
    }
    case 18: {
        GfBdatItem* bdat = GfBdatItem::get();
        property.m_enhance2 = bdat->getITM_HanaArtsEnhEnhance(property.m_item);
        property.m_condition = bdat->getITM_HanaArtsEnhCondition(property.m_item);
        property.m_needEther = bdat->getITM_HanaArtsEnhNeedEther(property.m_item);
        property.m_dustEther = bdat->getITM_HanaArtsEnhDustEther(property.m_item);
        break;
    }
    case 19: {
        GfBdatItem* bdat = GfBdatItem::get();
        property.m_partsSortKey = bdat->getITM_HanaNArtsSetNArts(property.m_item);
        property.m_condition = bdat->getITM_HanaNArtsSetCondition(property.m_item);
        property.m_needEther = bdat->getITM_HanaNArtsSetNeedEther(property.m_item);
        property.m_dustEther = bdat->getITM_HanaNArtsSetDustEther(property.m_item);
        break;
    }
    case 20: {
        GfBdatItem* bdat = GfBdatItem::get();
        property.m_enhance2 = bdat->getITM_HanaAssistEnhance(property.m_item);
        property.m_condition = bdat->getITM_HanaAssistCondition(property.m_item);
        property.m_needEther = bdat->getITM_HanaAssistNeedEther(property.m_item);
        property.m_dustEther = bdat->getITM_HanaAssistDustEther(property.m_item);
        break;
    }
    case 6: {
        GfBdatItem* bdat = GfBdatItem::get();
        if (GfDataItem::isValidPreciousIra(property.m_item)) {
            property.m_preciousCategory = bdat->getPreciousIraCategory(property.m_item);
            property.m_preciousType = bdat->getPreciousIraType(property.m_item);
        } else {
            property.m_preciousCategory = bdat->getPreciousCategory(property.m_item);
            property.m_preciousType = bdat->getPreciousType(property.m_item);
        }
        break;
    }
    default:
        return false;
    }
    return property.m_flags & 1;
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

void GfItemUtil::setEquipFlag(unsigned int item, GfItemHandle handle, bool equip) {
    // the copy comes first: the original reads the handle before the box singleton
    GfItemHandle h(handle);
    GfItemBox::get()->setEquipFlag(item, h, equip);
}

GfItemHandle GfItemUtil::getNoEquipItemHandle(unsigned int item) {
    return GfItemBox::get()->getNoEquipItemHandle(item);
}

void GfItemUtil::setupNewGameParam() {
    GfBdatItem* bdat = GfBdatItem::get();
    unsigned int start = bdat->getEventStart();
    unsigned int end = bdat->getEventEnd();
    for (unsigned int id = start; id < end; id++) {
        int count = GfItemBox::get()->countItem(id);
        if (count != 0) {
            GfItemBox::decItemForNewGame(id, count);
        }
    }
    start = bdat->getInfoStart();
    end = bdat->getInfoEnd();
    for (unsigned int id = start; id < end; id++) {
        if (bdat->getInfoClearNewGame(id) != 0) {
            int count = GfItemBox::get()->countItem(id);
            if (count != 0) {
                GfItemBox::decItemForNewGame(id, count);
            }
        }
    }
    start = bdat->getPreciousStart();
    end = bdat->getPreciousIraEnd();
    for (unsigned int id = start; id < end; id++) {
        if (GfDataItem::isValidPreciousIra(id) ? bdat->getPreciousIraClearNewGame(id) != 0
                                               : bdat->getPreciousClearNewGame(id) != 0) {
            int count = GfItemBox::get()->countItem(id);
            if (count != 0) {
                GfItemBox::decItemForNewGame(id, count);
            }
        }
    }
    start = bdat->getTresureStart();
    end = bdat->getTresureEnd();
    for (unsigned int id = start; id < end; id++) {
        if (bdat->getTresureClearNewGame(id) != 0) {
            int count = GfItemBox::get()->countItem(id);
            if (count != 0) {
                GfItemBox::decItemForNewGame(id, count);
            }
        }
    }
    GfDataItem::setNoMultiple(45005, false);
    GfDataItem::setNoMultiple(45009, false);
    GfDataItem::setNoMultiple(45010, false);
    if (GfItemBox::get()->countItem(45005) != 0) {
        GfItemBox::decItemForNewGame(45005, 1);
    }
    if (GfItemBox::get()->countItem(45009) != 0) {
        GfItemBox::decItemForNewGame(45009, 1);
    }
}

void GfEquipUtil::equipBladeChip(unsigned int blade, unsigned int chip) {
    GfDataBlade::getBladeWeapon(blade);  // its result is not used
    if (GfItemBox::get()->countItem(chip) != 0 && GfItemBox::decItem(chip, 1)) {
        GfEvent::callItemAdd(chip, -1);
    }
    GfDataBlade::setBladeWeapon(blade, GfDataBlade::getBladeWeaponByRank(blade, chip));
    GfReqCommand::reqRebuildPartyWeapon(blade);
}

bool GfEquipUtil::isEnableExtendDriverAcce(unsigned int driver) {
    return GfDataDriver::isEnableExtendEquipAcce(driver);
}

void GfEquipUtil::setEnableExtendDriverAcce(unsigned int driver, bool flag) {
    GfDataDriver::setEnableExtendEquipAcce(driver, flag);
}

unsigned int GfEquipUtil::getEquipDriverAcce(unsigned int driver, unsigned int slot) {
    return GfDataDriver::getEquipAcce(driver, slot);
}

bool GfEquipUtil::equipDriverAcce(unsigned int driver, unsigned int slot, unsigned int accessory, GfItemHandle handle) {
    GfDataItem::getItemType(accessory);  // its result is not used
    unsigned int old = GfDataDriver::getEquipAcce(driver, slot);
    if (old != 0) {
        GfItemHandle oldHandle = GfDataDriver::getEquipAcceHandle(driver, slot);
        GfDataDriver::setEquipAcce(driver, slot, 0);
        GfDataDriver::setEquipAcceHandle(driver, slot, GfItemHandle());
        if (oldHandle.m_handle == 0) {
            if (GfItemUtil::isEnableAddItemBox(old, 1)) {
                GfItemUtil::addItemBox(old, 1);
            } else if (GfDataItem::isEnableSell(old)) {
                SCOM_ADD_MONEY::create(GfDataItem::getPrice(old));
            }
        } else {
            GfItemUtil::setEquipFlag(old, oldHandle, false);
        }
    }
    if (handle.m_handle == 0) {
        handle = GfItemBox::get()->getNoEquipItemHandle(accessory);
    }
    GfItemUtil::setEquipFlag(accessory, handle, true);
    GfDataDriver::setEquipAcce(driver, slot, accessory);
    GfDataDriver::setEquipAcceHandle(driver, slot, handle);
    GfEvent::callAcceParam(driver, slot);
    return true;
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

bool GfEquipUtil::equipBladeOrb(unsigned int blade, unsigned int orb, unsigned int slot, GfItemHandle handle) {
    unsigned short old = GfDataBlade::getEquipOrb(blade, slot);
    if (old != 0) {
        GfItemHandle oldHandle = GfDataBlade::getEquipOrbHandle(blade, slot);
        if (oldHandle.m_handle == 0) {
            GfDataBlade::setEquipOrb(blade, 0, slot);
            if (GfItemUtil::isEnableAddItemBox(old, 1)) {
                GfItemUtil::addItemBox(old, 1);
            } else if (GfDataItem::isEnableSell(old)) {
                SCOM_ADD_MONEY::create(GfDataItem::getPrice(old));
            }
        } else {
            GfItemUtil::setEquipFlag(old, oldHandle, false);
        }
    }
    if (handle.m_handle == 0) {
        handle = GfItemBox::get()->getNoEquipItemHandle(orb);
    } else {
        unsigned int owner = GfItemUtil::getEquipChar(handle);
        if (owner != 0 && owner != blade) {
            handle = GfItemBox::get()->getNoEquipItemHandle(orb);
        }
    }
    GfItemUtil::setEquipFlag(orb, handle, true);
    GfDataBlade::setEquipOrb(blade, orb, slot);
    GfDataBlade::setEquipOrbHandle(blade, handle, slot);
    GfEvent::callOrbParam(blade, slot);
    return true;
}

unsigned int GfEquipUtil::getEquipOrbResult(unsigned int blade, unsigned int orb, unsigned int slot) {
    if (GfDataItem::getItemType(orb) != 3) {
        return 1;
    }
    if (GfItemBox::get()->countItem(orb) == 0) {
        return 6;
    }
    GfBdatItem* bdat = GfBdatItem::get();
    GfBdatBtl* btl = GfBdatBtl::get();
    unsigned int category = bdat->getEquipOrbEnhanceCategory(orb);
    unsigned int max = GfDataBlade::getEquipOrbMax(blade);
    for (unsigned int i = 0; i < max; i++) {
        unsigned short other = GfDataBlade::getEquipOrb(blade, i);
        if (slot != i && other != 0 && bdat->getEquipOrbEnhanceCategory(other) == category) {
            return 3;
        }
    }
    unsigned int effect = btl->getBTL_EnhanceEnhanceEffect(bdat->getEquipOrbEnhance(orb));
    max = GfDataBlade::getEquipOrbMax(blade);
    for (unsigned int i = 0; i < max; i++) {
        unsigned short other = GfDataBlade::getEquipOrb(blade, i);
        if (slot != i && other != 0 && effect == btl->getBTL_EnhanceEnhanceEffect(bdat->getEquipOrbEnhance(other))) {
            return 4;
        }
    }
    if (slot == 0xFFFFFFFF && GfDataBlade::isEquipOrbFull(blade)) {
        return 2;
    }
    return 0;
}

unsigned int GfEquipUtil::execWpUpItem(unsigned int driver, unsigned int item, unsigned int wpnType) {
    if (item - 0x633D < 3) {
        if (GfItemBox::get()->countItem(item) == 0) {
            return 6;
        }
        GfBdatItem* bdat = GfBdatItem::get();
        GfDataDriverArts::addWp(driver, wpnType,
                                GfDataItem::isValidPreciousIra(item) ? bdat->getPreciousIraType(item) : bdat->getPreciousType(item));
        if (GfItemBox::decItem(item, 1)) {
            GfEvent::callItemAdd(item, -1);
        }
        return 0;
    }
    return 1;
}

unsigned int GfEquipUtil::getEquipIraWpnAcce(unsigned int driver) {
    return GfDataDriver::getEquipWpnAcce(driver);
}

bool GfEquipUtil::equipIraWpnAcce(unsigned int driver, unsigned int item, GfItemHandle handle) {
    GfDataItem::getItemType(item);  // its result is not used
    unsigned int old = GfDataDriver::getEquipWpnAcce(driver);
    if (old != 0) {
        GfItemHandle oldHandle = GfDataDriver::getEquipWpnAcceHandle(driver);
        GfDataDriver::setEquipWpnAcce(driver, 0);
        GfDataDriver::setEquipWpnAcceHandle(driver, GfItemHandle());
        if (oldHandle.m_handle == 0) {
            if (GfItemUtil::isEnableAddItemBox(old, 1)) {
                GfItemUtil::addItemBox(old, 1);
            } else if (GfDataItem::isEnableSell(old)) {
                SCOM_ADD_MONEY::create(GfDataItem::getPrice(old));
            }
        } else {
            GfItemUtil::setEquipFlag(old, oldHandle, false);
        }
    }
    if (handle.m_handle == 0) {
        handle = GfItemBox::get()->getNoEquipItemHandle(item);
    }
    GfItemUtil::setEquipFlag(item, handle, true);
    GfDataDriver::setEquipWpnAcce(driver, item);
    GfDataDriver::setEquipWpnAcceHandle(driver, handle);
    return true;
}

int GfShopUtil::execBuy(unsigned int item, unsigned int num, unsigned int shop) {
    if (!GfItemUtil::isEnableAddItemBox(item, num)) {
        return 1;
    }
    ItemPrice price;
    GfItemUtil::getPrice(price, item, shop);
    unsigned int total = price.m_price * num;
    if (GfDataUtil::getMoney() < total) {
        return 3;
    }
    GfItemUtil::addItemBox(item, num);
    SCOM_ADD_MONEY::create(-total);
    SCOM_ADD_DEVELOP::create(GfGameManager::getMapZoneID(), price.m_hundredth * num);
    GfDataShop::setBuyItem(shop, item);
    GfAchievStats::checkBuyItemFromShop(item, num, shop, total);
    GfEvent::callExecBuy(item, num, shop);
    return 0;
}

int GfShopUtil::execSell(unsigned int item, unsigned int num, unsigned int shop, GfItemHandle handle) {
    if (!GfDataItem::isEnableSell(item)) {
        return 4;
    }
    if (GfItemBox::get()->countItem(item) < num) {
        return 2;
    }
    ItemPrice price;
    GfItemUtil::getPrice(price, item, shop);
    if (handle.m_handle != 0) {
        GfItemUtil::fn_71002FA968(item, 1, false, handle);
    } else {
        GfItemUtil::addItemBox(item, -num);
    }
    unsigned int total = price.m_sellPrice * num;
    SCOM_ADD_MONEY::create(total);
    SCOM_ADD_DEVELOP::create(GfGameManager::getMapZoneID(), price.m_eightHundredth * num);
    GfAchievStats::checkSellItemFromShop(item, num, shop, total);
    return 0;
}

void GfRecipeOrbUtil::execOrbRecipe(unsigned int item, const ::mm::mtl::FixedVector<OrbRecipe, 128>* items) {
    GfBdatItem* bdat = GfBdatItem::get();
    unsigned int recipe = bdat->getEmptyOrbRecipe(item);
    // a debug copy of the item's name the function never reads (the original builds it too)
    ::mm::mtl::FixStr<128> name;
    name = util::debugUTF8ToSJIS(GfDataItem::getName(item));
    ::mm::mtl::FixedVector<OrbRecipe, 128> list;
    if (items == nullptr) {
        getRecipeItemsByItemBox(list, recipe);
        items = &list;
    }
    isEnabaleOrbRecipe(recipe, *items);
    unsigned int orb = bdat->getEmptyOrbEquipItemID(item);
    // the original reads the singleton again and asks the item's type (unused) before the recipe test
    bdat = GfBdatItem::get();
    GfDataItem::getItemType(item);
    if (bdat->getEmptyOrbRecipe(item) != 0) {
        for (const OrbRecipe* it = items->begin(); it != items->end(); ++it) {
            if (it->m_item != 0 && it->m_number != 0) {
                GfItemUtil::addItemBox(it->m_item, -it->m_number);
            }
        }
    }
    GfItemUtil::addItemBox(item, -1);
    GfItemUtil::addItemBox(orb, 1);
}

unsigned int GfRecipeOrbUtil::getRecipeID(unsigned int item) {
    return GfBdatItem::get()->getEmptyOrbRecipe(item);
}

unsigned int GfRecipeOrbUtil::getEquipOrb(unsigned int item) {
    return GfBdatItem::get()->getEmptyOrbEquipItemID(item);
}

bool GfRecipeOrbUtil::getRecipeInfo(RecipeInfo& info, unsigned int recipe) {
    if (recipe == 0) {
        return false;
    }
    GfBdatItem* bdat = GfBdatItem::get();
    info.m_recipe = 0;
    info.m_recipeType = 0;
    info.m_resultRarity = RecipeInfo::Result();
    info.m_resultColleCategory = RecipeInfo::Result();
    info.m_resultItems.clear();
    info.m_recipe = recipe;
    info.m_recipeType = bdat->getOrbRecipeRecipeType(recipe);
    switch (info.m_recipeType) {
    case 0:
        info.m_resultRarity.m_value = bdat->getOrbRecipeRarity(recipe);
        info.m_resultRarity.m_number = bdat->getOrbRecipeAssortNumber(recipe);
        break;
    case 1:
        info.m_resultColleCategory.m_value = bdat->getOrbRecipeRscCat(recipe);
        info.m_resultColleCategory.m_number = bdat->getOrbRecipeAssortNumber(recipe);
        break;
    case 2:
        for (unsigned int i = 0; i < 8; i++) {
            unsigned int id = bdat->getOrbRecipeItemID(recipe, i);
            if (id != 0) {
                RecipeInfo::Item entry;
                entry.m_item = id;
                entry.m_number = bdat->getOrbRecipeItemNumber(recipe, i);
                info.m_resultItems.push_back(entry);
            }
        }
        break;
    default:
        return false;
    }
    return true;
}

bool GfRecipeOrbUtil::isEnableRecipe(unsigned int recipe) {
    ::mm::mtl::FixedVector<OrbRecipe, 128> items;
    return getRecipeItemsByItemBox(items, recipe);
}

void GfPouchUtil::updatePouch(unsigned int driver, unsigned int pouch, const SDataPouch& data, const ::fw::UpdateInfo& info) {
    GfGameManager::isGameTypeIra();  // the original calls it and drops the answer
    unsigned int item = data.itemId;
    if (item == 0) {
        return;
    }
    SDataPouch work = data;
    work.remainTime -= info.m_deltaTime;
    if (work.remainTime <= 0.0f) {
        if (fn_71002FDB88(driver, pouch, work)) {
            SCOM_POPUP::createPouch(driver, data.itemId, 1);
            SCOM_FIELD_VOICE::createPouchAutoAdd(data.itemId, driver);
        } else {
            SCOM_FIELD_VOICE::createPouchAutoAddFailed(item, driver);
        }
    }
    GfDataDriver::setPouchData(driver, pouch, work);
}

bool GfPouchUtil::fn_71002FDB88(unsigned int driver, unsigned int pouch, SDataPouch& data) {
    if (GfItemBox::get()->countItem(data.itemId) == 0) {
        SCOM_POPUP::createPouch(driver, data.itemId, 0);
        data.itemId = 0;
        data.remainTime = 0.0f;
        GfDataDriver::setPouchData(driver, pouch, data);
        return false;
    }
    GfItemUtil::addItemBox(data.itemId, -1);
    SCOM_ITEM_USE::create(data.itemId, driver);
    float time = GfDataItem::getFavoriteItemTime(data.itemId);
    if (time <= 0.0f) {
        time = 180.0f;
    }
    data.remainTime = time;
    unsigned int trust = GfBdatItem::get()->getFavoriteTrustPoint(data.itemId);
    if (trust != 0) {
        if (GfDataDriver::isIra(driver)) {
            ::mm::mtl::FixedVector<unsigned short, 32> list;
            GfDataDriver::getIraBack(list, driver);
            for (const unsigned short& id : list) {
                if (!GfDataDriver::isActivateUnuse(id)) {
                    SCOM_ADD_TRUST::create(id, trust);
                }
            }
        } else {
            for (int i = 0; i < GfDataDriver::getMaxSetBladeNum(driver); i++) {
                unsigned int blade = GfDataDriver::getBlade(driver, i);
                if (blade != 0) {
                    SCOM_ADD_TRUST::create(blade, trust);
                }
            }
        }
    }
    GfDataDriver::setPouchData(driver, pouch, data);
    return true;
}

SDataPouch& GfPouchUtil::getPouch(unsigned int driver, unsigned int pouch) {
    if (GfGameManager::isGameTypeIra()) {
        driver = GfDataDriver::getIraFront(driver);
    }
    return *GfDataDriver::getPouchData(driver, pouch);
}

void GfPouchUtil::setPouch(unsigned int driver, unsigned int pouch, const SDataPouch& data) {
    if (GfGameManager::isGameTypeIra()) {
        driver = GfDataDriver::getIraFront(driver);
    }
    SDataPouch work = data;
    unsigned int item = data.itemId;
    if (item != 0) {
        GfDataDriver::setUsedFavoriteItemForPouch(driver, work.itemId);
        if (GfDataDriver::isIra(driver)) {
            ::mm::mtl::FixedVector<unsigned short, 32> list;
            GfDataDriver::getIraBack(list, driver);
            for (const unsigned short& id : list) {
                GfDataDriver::setUsedFavoriteItemForPouch(id, work.itemId);
            }
        } else {
            int num = GfDataDriver::getMaxSetBladeNum(driver);
            for (int i = 0; i < num; i++) {
                GfDataBlade::setUsedFavoriteItemForPouch(GfDataDriver::getBlade(driver, i), work.itemId);
            }
        }
        SCOM_ACHIEV_INC::addTotalCount(19, 1);
        SCOM_ACHIEV_INC::create(19, 1, 0);
    }
    work.remainTime = 0.0f;
    if (item != 0) {
        fn_71002FDB88(driver, pouch, work);
    }
}

bool GfPouchUtil::isEnableSetItem(unsigned int driver, unsigned int pouch, unsigned int item) {
    if (GfGameManager::isGameTypeIra()) {
        driver = GfDataDriver::getIraFront(driver);
    }
    if (driver == 0 || !GfDataDriver::getPouchData(driver, pouch)->m_open) {
        return false;
    }
    for (unsigned int i = 0; i < 3; i++) {
        SDataPouch* data = GfDataDriver::getPouchData(driver, i);
        if (data->itemId == 0 || i == pouch) {
            continue;
        }
        if (data->itemId == item) {
            return false;
        }
    }
    return true;
}

bool GfPouchUtil::isExistOpenItem() {
    return GfItemBox::get()->countItem(25305) != 0;
}

void GfPouchUtil::execOpen(unsigned int driver) {
    if (!isExistOpenItem()) {
        return;
    }
    if (GfGameManager::isGameTypeIra()) {
        driver = GfDataDriver::getIraFront(driver);
    }
    for (unsigned int i = 0; i < 3; i++) {
        SDataPouch data = *GfDataDriver::getPouchData(driver, i);
        if (!data.m_open) {
            data.m_open = 1;
            GfDataDriver::setPouchData(driver, i, data);
            GfItemUtil::addItemBox(25305, -1);
            return;
        }
    }
}

unsigned int GfPouchUtil::getOpenCount(unsigned int driver) {
    if (GfGameManager::isGameTypeIra()) {
        driver = GfDataDriver::getIraFront(driver);
    }
    unsigned int count = 0;
    for (unsigned int i = 0; i < 3; i++) {
        if (GfDataDriver::getPouchData(driver, i)->m_open) {
            count++;
        }
    }
    return count;
}

// The helper is inferred (no symbol names it): the quests' resets come out as the original's only from an inlined
// function (its argument copies start fresh each line). The name is not the original's.
static inline void resetAchievQuests(AchievInfo* info) {
    for (int i = 0; i < 5; i++) {
        GfQuestManager::resetQuest(info->m_quests[i].m_questId);
    }
}

void GfKizunaringBlade::removeAchievement(unsigned int blade) {
    if (blade == 0) {
        return;
    }
    for (unsigned int line = 0; line < 10; line++) {
        AchievInfo* info = GfDataBlade::getAchievInfo(blade, line);
        if (info->m_achievementId != 0) {
            resetAchievQuests(info);
        }
    }
}

unsigned int GfKizunaringBlade::getAchievementCategory(unsigned int blade, unsigned int line, unsigned int level) {
    if (blade != 0) {
        unsigned int set = GfDataBlade::getAchievInfo(blade, line)->m_achievementId;
        if (set != 0) {
            unsigned int id = QuestListAcc::get()->getFLD_AchievementSetAchievementID(set, level - 1);
            if (id != 0) {
                return QuestListAcc::get()->getFLD_AchievementListCategory(id);
            }
        }
    }
    return 0;
}

bool GfKizunaringBlade::getAchievementResultMsg(unsigned char*& bdat, unsigned int& id, unsigned int blade,
                                                unsigned int line, unsigned int level) {
    DataParamAcc acc(4, blade, GimmickType(0));
    ACHIEVEMENT_TYPE type;
    unsigned int index;
    GfDataAchievement::getAchievementType(type, index, line);
    if (type == 0) {
        return GfDataBladeArts::getEnhanceCaption(bdat, id, acc.getBladeArts(index, false), level);
    } else if (type == 1) {
        return GfDataBladeSkill::getEnhanceCaption(bdat, id, acc.getBladeSkill(index, false), level);
    } else if (type == 2) {
        return GfDataFieldSkill::getCaption(bdat, id, acc.getFieldSkill(index, false));
    }
    return false;
}

unsigned int GfKizunaringBlade::getAchievementResultEnhance(unsigned int blade, unsigned int line, unsigned int level) {
    DataParamAcc acc(4, blade, GimmickType(0));
    ACHIEVEMENT_TYPE type;
    unsigned int index;
    GfDataAchievement::getAchievementType(type, index, line);
    if (type == 0) {
        return GfDataBladeArts::getEnhance(acc.getBladeArts(index, false), level);
    } else if (type == 1) {
        return GfDataBladeSkill::getEnhance(acc.getBladeSkill(index, false), level);
    }
    return 0;
}

unsigned int GfKizunaringBlade::getAchievementIcon(unsigned int blade, unsigned int line, unsigned int level) {
    if (blade != 0) {
        unsigned int set = GfDataBlade::getAchievInfo(blade, line)->m_achievementId;
        if (set != 0) {
            unsigned int id = QuestListAcc::get()->getFLD_AchievementSetAchievementID(set, level - 1);
            if (id != 0) {
                return QuestListAcc::get()->getFLD_AchievementListIcon(id);
            }
        }
    }
    return 0;
}

unsigned int GfKizunaringBlade::getAchievementVoiceCategory(unsigned int blade, unsigned int line, unsigned int level) {
    if (blade != 0) {
        unsigned int set = GfDataBlade::getAchievInfo(blade, line)->m_achievementId;
        if (set != 0) {
            unsigned int id = QuestListAcc::get()->getFLD_AchievementSetAchievementID(set, level - 1);
            if (id != 0) {
                return QuestListAcc::get()->getFLD_AchievementListVoiceCategory(id);
            }
        }
    }
    return 0;
}

unsigned int GfKizunaringBlade::getAchievementAfterVoice(unsigned int blade, unsigned int line, unsigned int level) {
    if (blade != 0) {
        unsigned int set = GfDataBlade::getAchievInfo(blade, line)->m_achievementId;
        if (set != 0) {
            unsigned int id = QuestListAcc::get()->getFLD_AchievementSetAchievementID(set, level - 1);
            if (id != 0) {
                return QuestListAcc::get()->getFLD_AchievementListAfterVoice(id);
            }
        }
    }
    return 0;
}

unsigned int GfKizunaringBlade::getAchievementDifficulty(unsigned int blade, unsigned int line, unsigned int level) {
    if (blade != 0) {
        unsigned int set = GfDataBlade::getAchievInfo(blade, line)->m_achievementId;
        if (set != 0) {
            unsigned int id = QuestListAcc::get()->getFLD_AchievementSetAchievementID(set, level - 1);
            if (id != 0) {
                return QuestListAcc::get()->getFLD_AchievementListDifficulty(id);
            }
        }
    }
    return 0;
}

unsigned int GfKizunaringBlade::getAchievementQuest(unsigned int blade, unsigned int line, unsigned int level) {
    if (blade != 0) {
        unsigned int set = GfDataBlade::getAchievInfo(blade, line)->m_achievementId;
        if (set != 0) {
            unsigned int id = QuestListAcc::get()->getFLD_AchievementSetAchievementID(set, level - 1);
            if (id != 0) {
                return QuestListAcc::get()->getFLD_AchievementListTask(id);
            }
        }
    }
    return 0;
}

unsigned int GfKizunaringBlade::getAchievementSetCategory(unsigned int blade, unsigned int line) {
    if (blade != 0) {
        unsigned int set = GfDataBlade::getAchievInfo(blade, line)->m_achievementId;
        if (set != 0) {
            return QuestListAcc::get()->getFLD_AchievementSetCategory(set);
        }
    }
    return 0;
}

unsigned int GfKizunaringBlade::getAchievementSetAbilityLevel(unsigned int blade, unsigned int line) {
    if (blade != 0) {
        unsigned int set = GfDataBlade::getAchievInfo(blade, line)->m_achievementId;
        if (set != 0) {
            return QuestListAcc::get()->getFLD_AchievementSetAbilityLevel(set);
        }
    }
    return 0;
}

}  // namespace gf
