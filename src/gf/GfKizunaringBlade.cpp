#include "gf/GfKizunaringBlade.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataQuest.h"
#include "gf/GfQuestInfo.h"
#include "classes/gf/GfQuestManager.h"
#include "gf/QuestListAcc.h"
#include "gf/QuestTaskParam.h"
#include "gf/QuestCompleteParam.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/SCOM_POPUP.h"

namespace gf {

// refreshOrderQuestList (0x71002FECC4) is not written yet: a range-for over the FixedVector<unsigned short, 422>
// tests the byte count for the empty list where the original tests the element count (12 words apart); its callee
// fn_71002FF034 (0x71002FF034, 0x270 bytes) is not written either.

bool GfKizunaringBlade::isCompleteLevel(unsigned int blade, unsigned int line, unsigned int level) {
    if (blade == 0 || GfDataBlade::isActivateUnuse(blade)) {
        return false;
    }
    if (GfDataBlade::isUnselect(blade)) {
        return false;
    }
    unsigned int driver = GfDataBlade::getSetDriver(blade);
    if (driver != 0 && GfDataDriver::isActivateUnuse(driver)) {
        return false;
    }
    AchievInfo* info = GfDataBlade::getAchievInfo(blade, line);
    if (info->m_achievementId == 0) {
        return false;
    }
    if (!isNetabareOK(blade, line, level)) {
        return false;
    }
    for (unsigned int i = 1; i < level; ++i) {
        AchievQuest& quest = info->m_quests[i - 1];
        if (!quest.m_questId.empty() && !(quest.m_flags & 1)) {
            if (GfQuestInfo::isQuestOrder(quest.m_questId)) {
                return false;
            }
            if (GfQuestInfo::isQuestNotOrder(quest.m_questId)) {
                return false;
            }
        }
    }
    return true;
}

bool GfKizunaringBlade::isNetabareOK(unsigned int blade, unsigned int line, unsigned int level) {
    AchievInfo* info = GfDataBlade::getAchievInfo(blade, line);
    AchievQuest& quest = info->m_quests[level - 1];
    if (quest.m_questId.empty()) {
        return true;
    }
    QuestID next = GfDataQuest::getListNextQuestA(quest.m_questId);
    QuestListAcc* acc = QuestListAcc::get();
    QuestTaskParam param(next, 0, TASK_STATE(0));
    unsigned int condition = acc->getTaskTaskCondition1(param.m_purposeId);
    if (condition == 0) {
        return true;
    }
    return GfGameCond::isGameCond(condition);
}

bool GfKizunaringBlade::isCompleteLevel(const AchievQuest& quest) {
    return isCompleteLevel(quest.m_blade, quest.m_line, quest.m_level);
}

void GfKizunaringBlade::qevCompleteQuest(const QuestCompleteParam& param) {
    if (param.m_questId.m_achieveId == 0) {
        return;
    }
    const AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
    if (quest != nullptr) {
        SCOM_POPUP::createAchievement(quest->m_blade, quest->m_line, quest->m_level);
    }
}

int GfKizunaringBlade::getSkillLevel(unsigned int blade, unsigned int line, unsigned int level) {
    AchievInfo* info = GfDataBlade::getAchievInfo(blade, line);
    int count = 0;
    for (unsigned int i = 1; i <= level; ++i) {
        AchievQuest& quest = info->m_quests[i - 1];
        if (!quest.m_questId.empty() || (quest.m_level == 1 && (quest.m_flags & 1))) {
            ++count;
        }
    }
    return count;
}

}  // namespace gf
