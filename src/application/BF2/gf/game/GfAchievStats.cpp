#include "gf/GfAchievStats.h"

#include "classes/gf/GfAchievManager.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "gf/AchievQuest.h"
#include "gf/GfDataAchievement.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataItem.h"
#include "gf/GfDataNpc.h"
#include "gf/GfDataUtil.h"
#include "gf/GfItemUtil.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"

namespace gf {

// the statistic of a collectible's category, from category 4, 0 for none (lbl_71009BAFE8; the name is not the
// original's)
static const mm::mtl::FixedArray<unsigned int, 12> s_collectionStats = {{6, 7, 8, 9, 10, 11, 12, 13, 0, 0, 0, 0}};
// the statistic of a treasure's category, from category 24, 0 for none (lbl_71009BB018; the name is not the
// original's)
static const mm::mtl::FixedArray<unsigned int, 12> s_treasureStats = {{18, 15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0}};

// the object of the last talk checkTalk counted, -1 at start (lbl_7100B52C30; the name is not the original's)
static GF_OBJ_HANDLE* s_talkHandle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);

void GfAchievStats::checkItem(unsigned int item, int num) {
    if (item == 0 || num < 1) {
        return;
    }
    GfBdatItem* bdat = GfBdatItem::sys();
    unsigned int type = GfDataItem::getItemType(item);
    GfAchievManager* manager = GfAchievManager::sys();
    if (manager == nullptr) {
        return;
    }
    switch (type) {
    case 7: {
        unsigned int category = bdat->getCollectionListCategory(item);
        if (category == 0) {
            return;
        }
        unsigned int stats = s_collectionStats[category - 4];
        if (stats == 0) {
            return;
        }
        SCOM_ACHIEV_INC::addTotalCount(5, num);
        manager->incAchiev(5, num);
        manager->incAchiev(stats, num);
        break;
    }
    case 8: {
        unsigned int category = bdat->getTresureCategory(item);
        if (category == 0) {
            return;
        }
        unsigned int stats = s_treasureStats[category - 24];
        if (stats == 0) {
            return;
        }
        SCOM_ACHIEV_INC::addTotalCount(14, num);
        manager->incAchiev(14, num);
        manager->incAchiev(stats, num);
        break;
    }
    case 11:
        SCOM_ACHIEV_INC::createCrystal();
        break;
    }
}

void GfAchievStats::checkTalk(unsigned int npc, GF_OBJ_HANDLE* handle) {
    if (s_talkHandle == handle) {
        return;
    }
    s_talkHandle = handle;
    SCOM_ACHIEV_INC::create(3, 1, 0);
    SCOM_ACHIEV_INC::addTotalCount(22, 1);
    SCOM_ACHIEV_INC::create(22, 1, 0);
    if (npc >= 2001) {
        switch (GfBdatRsc::sys()->getRscNpcListRoots(npc)) {
        case 1:
            SCOM_ACHIEV_INC::createParty(26, 1);
            break;
        case 2:
            SCOM_ACHIEV_INC::createParty(25, 1);
            break;
        case 3:
            SCOM_ACHIEV_INC::createParty(27, 1);
            break;
        case 4:
            SCOM_ACHIEV_INC::createParty(29, 1);
            break;
        case 5:
            SCOM_ACHIEV_INC::createParty(24, 1);
            break;
        case 6:
            SCOM_ACHIEV_INC::createParty(28, 1);
            break;
        }
    }
    switch (GfDataNpc::getGender(npc)) {
    case 1:
        SCOM_ACHIEV_INC::createParty(30, 1);
        break;
    case 2:
        SCOM_ACHIEV_INC::createParty(31, 1);
        break;
    }
}

void GfAchievStats::checkFallLength(GF_OBJ_HANDLE*, const MsgObjectNotifyDamage&) {
}

void GfAchievStats::checkBuyItemFromShop(unsigned int, unsigned int num, unsigned int, unsigned int price) {
    SCOM_ACHIEV_INC::addTotalCount(32, num);
    SCOM_ACHIEV_INC::create(32, num, 0);
    SCOM_ACHIEV_INC::addTotalCount(57, price);
    SCOM_ACHIEV_INC::create(57, price, 0);
}

void GfAchievStats::checkSellItemFromShop(unsigned int, unsigned int num, unsigned int, unsigned int price) {
    SCOM_ACHIEV_INC::addTotalCount(33, num);
    SCOM_ACHIEV_INC::create(33, num, 0);
    SCOM_ACHIEV_INC::addTotalCount(59, price);
    SCOM_ACHIEV_INC::create(59, price, 0);
}

void GfAchievStats::checkBladeActivate(unsigned int blade) {
    BladeCounts counts = {};
    fn_710028AF64(counts, blade);
    SCOM_ACHIEV_INC::createParty(38, counts.m_num);
    SCOM_ACHIEV_INC::createParty(39, counts.m_gender1);
    SCOM_ACHIEV_INC::createParty(40, counts.m_gender2);
    SCOM_ACHIEV_INC::createParty(41, counts.m_race2);
    SCOM_ACHIEV_INC::createParty(42, counts.m_weaponType[0]);
    SCOM_ACHIEV_INC::createParty(43, counts.m_weaponType[1]);
    SCOM_ACHIEV_INC::createParty(44, counts.m_weaponType[2]);
    SCOM_ACHIEV_INC::createParty(45, counts.m_weaponType[3]);
    SCOM_ACHIEV_INC::createParty(46, counts.m_weaponType[4]);
    SCOM_ACHIEV_INC::createParty(47, counts.m_weaponType[5]);
    SCOM_ACHIEV_INC::createParty(48, counts.m_weaponType[6]);
}

void GfAchievStats::fn_710028AF64(BladeCounts& counts, unsigned int blade) {
    mm::mtl::FixedVector<unsigned short, 422> blades;
    GfDataBlade::fn_71002376E8(blades);
    GfDataBlade::getListReserver(blades);
    GfDataBlade::removeSameBlade(blades);
    unsigned long i = 0;
    for (; i != blades.size(); i++) {
        if (*(blades.begin() + i) == (unsigned short)blade) {
            break;
        }
    }
    mm::mtl::FixedVector<unsigned short, 422>::iterator it = blades.begin() + i;
    if (it != blades.end()) {
        blades.erase(it);
    }
    counts.m_num = blades.size();
    for (mm::mtl::FixedVector<unsigned short, 422>::iterator b = blades.begin(), e = blades.end(); b != e; ++b) {
        unsigned int id = *b;
        switch (GfDataBlade::fn_710023982C(id)) {
        case 1:
            counts.m_gender1++;
            break;
        case 2:
            counts.m_gender2++;
            break;
        }
        if (GfDataBlade::getRace(id) == 2) {
            counts.m_race2++;
        }
        switch (GfDataBlade::getBladeWpnType(id)) {
        case 10:
            counts.m_weaponType[0]++;
            break;
        case 11:
            counts.m_weaponType[1]++;
            break;
        case 12:
            counts.m_weaponType[2]++;
            break;
        case 13:
            counts.m_weaponType[3]++;
            break;
        case 14:
            counts.m_weaponType[4]++;
            break;
        case 15:
            counts.m_weaponType[5]++;
            break;
        case 16:
            counts.m_weaponType[6]++;
            break;
        }
    }
}

// getAchievementAddCount 0x710028B15C: 4 words off, see the worker notes (wip/GfAchievStats_full_addcount4words.cpp)

int GfAchievStats::getAchievementTotalCount(const AchievQuest& quest) {
    BladeCounts counts = {};
    fn_710028AF64(counts, quest.m_blade);
    if (GfDataAchievement::fn_710024B4D0(quest.m_stats) >= 0 ||
        GfDataAchievement::getAchievementTotalFlgIndex(quest.m_stats) >= 0) {
        return GfDataAchievement::getTotalCount(quest.m_stats);
    }
    switch (quest.m_stats) {
    case 38:
        return counts.m_num;
    case 39:
        return counts.m_gender1;
    case 40:
        return counts.m_gender2;
    case 41:
        return counts.m_race2;
    case 42:
        return counts.m_weaponType[0];
    case 43:
        return counts.m_weaponType[1];
    case 44:
        return counts.m_weaponType[2];
    case 45:
        return counts.m_weaponType[3];
    case 46:
        return counts.m_weaponType[4];
    case 47:
        return counts.m_weaponType[5];
    case 48:
        return counts.m_weaponType[6];
    case 56:
        return GfDataUtil::getMoney();
    case 67:
        return GfItemUtil::getCrystalNum();
    }
    return -1;
}

}  // namespace gf
