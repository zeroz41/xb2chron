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

unsigned int GfEquipUtil::getEquipAcceResult(unsigned int driver, unsigned int slot, unsigned int accessory) {
    return getEquipAcceResult(*GfDataDriver::getSDataDriver(driver), slot, accessory);
}

unsigned int GfEquipUtil::getEquipOrbMax(unsigned int blade) {
    return GfDataBlade::getEquipOrbMax(blade);
}

unsigned int GfEquipUtil::getEquipBladeOrb(unsigned int blade, unsigned int slot) {
    return GfDataBlade::getEquipOrb(blade, slot);
}

unsigned int GfItemUtil::fn_71002FCD64(unsigned int driver) {
    return GfDataDriver::getEquipWpnAcce(driver);
}

unsigned int GfRecipeOrbUtil::getRecipeID(unsigned int item) {
    return GfBdatItem::get()->getEmptyOrbRecipe(item);
}

unsigned int GfRecipeOrbUtil::getEquipOrb(unsigned int item) {
    return GfBdatItem::get()->getEmptyOrbEquipItemID(item);
}

bool GfRecipeOrbUtil::isEnableRecipe(unsigned int recipe) {
    ::mm::mtl::FixedVector<OrbRecipe, 128> items;
    return getRecipeItemsByItemBox(items, recipe);
}

SDataPouch& GfPouchUtil::getPouch(unsigned int driver, unsigned int pouch) {
    if (GfGameManager::isGameTypeIra()) {
        driver = GfDataDriver::getIraFront(driver);
    }
    return *GfDataDriver::getPouchData(driver, pouch);
}

bool GfPouchUtil::isExistOpenItem() {
    return GfItemBox::get()->countItem(25305) != 0;
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
