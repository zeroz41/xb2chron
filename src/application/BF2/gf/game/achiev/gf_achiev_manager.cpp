#include "classes/gf/GfAchievManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfQuestManager.h"
#include "gf/AchievQuest.h"
#include "gf/GfAchievStats.h"
#include "gf/GfDataAchievement.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataQuest.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfQuestTask.h"
#include "gf/QuestListAcc.h"
#include "gf/QuestTaskParam.h"
#include "gf/SDataGame.h"
#include "mm/mtl/FixStr.h"

namespace gf {

GfAchievManager::~GfAchievManager() {}

void GfAchievManager::build(const GfSetupParam& param) {
#line 78
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfAchievManager(param);
}

void GfAchievManager::destroy() {
    if (GfAchievManager* manager = get()) {
        delete manager;
    }
}

void GfAchievManager::update(const fw::UpdateInfo&) {
    for (int count = 60; !m_incQueue.empty() && count > 0; --count) {
        flushEventIncAchiev(m_incQueue.first());
        m_incQueue.pop();
    }
}

void GfAchievManager::flushEventIncAchiev(const IncQuest& inc) {
    AchievQuest* quest = GfDataQuest::getAchievQuest(inc.m_questId);
    if (quest == nullptr || quest->m_blade == 0 || quest->m_level == 0) {
        return;
    }
    ACHIEVEMENT_TYPE type;
    unsigned int index;
    mm::mtl::FixStr<128> name;
    GfDataAchievement::getAchievementType(type, index, quest->m_line);
    switch (static_cast<int>(type)) {
    case 0:
        name.format("アーツアチーブメント[%d]", index + 1);
        break;
    case 1:
        name.format("ブレイドスキルアチーブメント[%d]", index + 1);
        break;
    case 2:
        name.format("フィールドスキルアチーブメント[%d]", index + 1);
        break;
    case 3:
        name.format("キーアチーブメント");
        break;
    }
}

void fn_710028A448(unsigned int type, int value, unsigned int blade) {
    for (int line = 9; line >= 0; --line) {
        AchievInfo* info;
        int index;
        for (index = 0; index < 5; ++index) {
            info = GfDataBlade::getAchievInfo(blade, line);
            if (info->m_achievementId == 0 || info->m_quests[index].m_questId.empty()) {
                continue;
            }
            if (GfQuestInfo::isQuestFin(info->m_quests[index].m_questId)) {
                if (!(info->m_quests[index].m_flags & 1)) {
                    break;
                }
                continue;
            }
            // the original jumps out to the line's quest (a found flag or pointer test lays out the last check
            // differently)
            goto found;
        }
        continue;
    found:
        AchievQuest* quest = &info->m_quests[index];
        if (!GfQuestInfo::isQuestOrder(quest->m_questId) || info->m_quests[index].m_stats != type) {
            continue;
        }
        unsigned int add;
        unsigned int total;
        GfAchievStats::getAchievementAddCount(add, total, type, value, info->m_quests[index].m_count & 0x3FFFFFFF,
                                              info->m_quests[index].m_countMax & 0x3FFFFFFF);
        if (add == 0 && total != 0) {
            if ((info->m_quests[index].m_count & 0x3FFFFFFF) < total) {
                quest->setCount(total);
            }
        } else {
            quest->incleseCount(add);
            GfQuestManager::eventAchievementCount(quest->m_questId);
        }
    }
}

// counts value for a task achievement of the statistic type, completing the task when it fills (inline: the
// original keeps its locals above incAchiev's blade list and builds the task's quest per call; the name is not the
// original's)
static void incTaskAchiev(TaskAchieve& task, unsigned int type, int value) {
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int id = acc->getTaskTaskID(task.m_purposeId, task.m_task);
    if (id == 0 || acc->getAchievementStatsID(id) != type) {
        return;
    }
    unsigned int max = acc->getAchievementCount(id);
    unsigned int count = task.m_count;
    if (count >= max) {
        return;
    }
    unsigned int add;
    unsigned int total;
    GfAchievStats::getAchievementAddCount(add, total, type, value, count, acc->getAchievementCount(id));
    if (add != 0) {
        task.m_count += add;
        if (task.m_count >= max) {
            QuestTaskParam param(task.m_questId, task.m_task, TASK_STATE(1));
            GfQuestTask::setCompleteFlag(param, true);
        }
    }
}

void GfAchievManager::incAchiev(unsigned int type, int value) {
    mm::mtl::FixedVector<unsigned short, 422> blades;
    GfDataBlade::getListParty(blades, true, false);
    if (!blades.empty()) {
        for (unsigned short* it = blades.begin(); it != blades.end();) {
            unsigned int driver = GfDataBlade::getSetDriver(*it);
            if (driver != 0 && GfDataDriver::isActivateUnuse(driver)) {
                it = blades.erase(it);
            } else {
                ++it;
            }
        }
        for (unsigned short* it = blades.begin(); it != blades.end(); ++it) {
            fn_710028A448(type, value, *it);
        }
    }
    for (TaskAchieve* task = GfDataQuest::getTaskAchieve()->begin(); task != GfDataQuest::getTaskAchieve()->end();
         ++task) {
        incTaskAchiev(*task, type, value);
    }
}

void GfAchievManager::incAchievWithBlade(unsigned int type, int value,
                                         const mm::mtl::FixedVector<unsigned short, 422>& blades) {
    for (const unsigned short* it = blades.begin(); it != blades.end(); ++it) {
        fn_710028A448(type, value, *it);
    }
}

void GfAchievManager::checkAchievWithBlade(unsigned int type, int value,
                                    const mm::mtl::FixedVector<unsigned short, 422>& blades) {
    for (const unsigned short* it = blades.begin(); it != blades.end(); ++it) {
        fn_710028A448(type, value, *it);
    }
}

void GfAchievManager::incleaseAchievCount(QuestID id, unsigned int count, unsigned int add) {
    if (add == 0) {
        return;
    }
    IncQuest inc;
    inc.m_questId = id;
    inc.m_count = count;
    inc.m_add = add;
    if (m_incQueue.full()) {
        flushEventIncAchiev(inc);
    } else {
        m_incQueue.push_back(inc);
    }
}

void GfAchievManager::gevItemAdd(unsigned int item, int num) {
    GfAchievStats::checkItem(item, num);
}

void GfAchievManager::gevBladeActivate(unsigned int blade, ActivateType from, ActivateType to) {
    if (to != 0 && from != to) {
        GfAchievStats::checkBladeActivate(blade);
    }
}

void GfAchievManager::gevMercenariesMissionFlag(unsigned int, unsigned int flag, unsigned int) {
    if (flag == 4) {
        GfQuestManager::eventCheckTaskAll();
    }
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BACFC). The blades
// getBladeByAchievementSet checks after 1001-1041.
static const unsigned short s_extraBlades[] = {
    0x413, 0x414, 0x415, 0x416, 0x417, 0x418, 0x419, 0x41A, 0x450, 0x451, 0x452, 0x453, 0x454, 0x455, 0x457,
};

// Placeholder name: 1.0.0 has it unnamed too (a file-local function). What it does: whether the blade (not a
// dummy blade unless isIra holds) has an affinity chart line of the achievement.
static bool fn_710028AA4C(unsigned int blade, unsigned int achievement) {
    if (!GfDataBlade::isIra(blade) && GfDataBlade::isDummyBlade(blade)) {
        return false;
    }
    for (unsigned int line = 0; line < 10; ++line) {
        if (GfDataBlade::getAchievInfo(blade, line)->m_achievementId == achievement) {
            return true;
        }
    }
    return false;
}

bool GfAchievManager::getBladeByAchievementSet(mm::mtl::FixedVector<unsigned short, 422>& list,
                                               unsigned int achievement) const {
    if (achievement == 0) {
        return false;
    }
    if (GfGameManager::isGameTypeIra()) {
        for (unsigned int driver = 17; driver < 26; ++driver) {
            unsigned int blade = GfDataDriver::getIraBlade(driver, -1);
            if (fn_710028AA4C(blade, achievement)) {
                list.push_back(blade);
            }
        }
    } else {
        for (unsigned int blade = 1001; blade < 1042; ++blade) {
            if (fn_710028AA4C(blade, achievement)) {
                list.push_back(blade);
            }
        }
        for (unsigned long i = 0; i < sizeof(s_extraBlades) / sizeof(s_extraBlades[0]); ++i) {
            if (fn_710028AA4C(s_extraBlades[i], achievement)) {
                list.push_back(s_extraBlades[i]);
            }
        }
        for (unsigned int blade = GfDataBlade::getStartCommonBlade(); blade < GfDataBlade::fn_7100231754();
             ++blade) {
            if (!GfDataBlade::isActivateUnuse(blade) && fn_710028AA4C(blade, achievement)) {
                list.push_back(blade);
            }
        }
    }
    return !list.empty();
}

}  // namespace gf
