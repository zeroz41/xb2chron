#ifndef GF_GFKIZUNARINGBLADE_H
#define GF_GFKIZUNARINGBLADE_H

namespace gf { class AchievQuest; }
namespace gf { class QuestCompleteParam; }

namespace gf {
// the affinity charts' achievements; its functions take no object
class GfKizunaringBlade {
public:
    static unsigned int getReleaseAchievement(unsigned int blade, unsigned int line, unsigned int level);
    static unsigned int getAchievementCategory(unsigned int blade, unsigned int line, unsigned int level);
    static unsigned int getAchievementIcon(unsigned int blade, unsigned int line, unsigned int level);
    static unsigned int getAchievementVoiceCategory(unsigned int blade, unsigned int line, unsigned int level);
    static unsigned int getAchievementAfterVoice(unsigned int blade, unsigned int line, unsigned int level);
    static unsigned int getAchievementDifficulty(unsigned int blade, unsigned int line, unsigned int level);
    static unsigned int getAchievementQuest(unsigned int blade, unsigned int line, unsigned int level);
    // the chart achievement's result caption: the enhanced art's/skill's enhance caption or the field skill's caption
    static bool getAchievementResultMsg(unsigned char*& bdat, unsigned int& id, unsigned int blade, unsigned int line,
                                        unsigned int level);
    // the enhance value of the chart achievement's art or skill at that level (0 for other achievement types)
    static unsigned int getAchievementResultEnhance(unsigned int blade, unsigned int line, unsigned int level);
    static unsigned int getAchievementSetCategory(unsigned int blade, unsigned int line);
    static unsigned int getAchievementSetAbilityLevel(unsigned int blade, unsigned int line);
    // orders the quests of every chart line the player can take next
    static void refreshOrderQuestList();
    // whether a blade's chart line has reached a level: the blade is active and its line's earlier quests are done
    static bool isCompleteLevel(unsigned int blade, unsigned int line, unsigned int level);
    // whether a chart level's quest may be shown: its next quest's first task condition holds (or it has none)
    static bool isNetabareOK(unsigned int blade, unsigned int line, unsigned int level);
    static bool isCompleteLevel(const AchievQuest& quest);
    static void orderAchievement(unsigned int id);
    // resets the quests (GfQuestManager::resetQuest) of every chart line (0-9) of the blade that has a chart
    static void removeAchievement(unsigned int blade);
    // opens the quest of a chart level: line 9 (key line) when it is neither finished nor ordered, the other lines
    // up to the blade's key release level when it is not ordered (GfQuestInfo::isQuestNotOrder)
    static void orderAchievement(unsigned int blade, unsigned int line, unsigned int level);
    static void qevCompleteQuest(const QuestCompleteParam& param);
    // the levels of a blade's chart line up to level that are done
    static int getSkillLevel(unsigned int blade, unsigned int line, unsigned int level);
    // Placeholder name: nothing names it (1.0.0 has its counterpart, fn_7100364750, unnamed as well: a local
    // symbol, so the original's is not a member). Declared here because refreshOrderQuestList, its one caller,
    // calls it for each blade with an affinity chart and each line from 9 down to 0. What it does: for line 9 it
    // walks the line's 5 quests (GfDataBlade::getAchievInfo): an ordered quest with an achievement blade has its
    // next quest (GfDataQuest::getListNextQuestA) and itself entered with GfQuestManager::entryOrderAchievQuest;
    // the second quest, unordered and not finished, is opened (GfQuestManager::openOrder, flags cleared). For the
    // other lines it does the same for levels 1-5 up to GfDataBlade::getKeyReleaseLevel, opening the first level's
    // quest with GfDataBlade::setSkillLineLevel(blade, line, 0).
    static void fn_71002FF034(unsigned int blade, unsigned int line);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
    // GfItemUtil's unit (no this). What it does: for a nonzero blade, walks its GfDataBlade::getAchievInfo entries 0..9
    // (stops at one whose first short is 0) and runs GfQuestTask::refreshTaskParam on GfDataQuest::getListNextQuestA of
    // each of the entry's five quest IDs. GfArenaParty::addFieldBlade calls it after GfDataBlade::setActivateReserver.
    static void refreshAchievementCount(unsigned int blade);
};
}  // namespace gf

#endif
