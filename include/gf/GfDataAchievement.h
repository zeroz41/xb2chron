#ifndef GF_GFDATAACHIEVEMENT_H
#define GF_GFDATAACHIEVEMENT_H

namespace gf { class AchievQuest; }

namespace gf {
enum ACHIEVEMENT_TYPE : int;
class GfDataAchievement {
public:
    // Maps affinity chart lines 0-2, 3-5, 6-8 and 9 to types 0, 1, 2 and 3 and the index within each group.
    static bool getAchievementType(ACHIEVEMENT_TYPE& type, unsigned int& index, unsigned int line);
    static void setupTotalCount(AchievQuest& quest);
    static bool isWaitControllFreeStats(unsigned int stats);
    // SCOM_ACHIEV_INC::addTotalCount forwards here
    static void addTotalCount(unsigned int type, unsigned int value);
    static void clearTotalCount(unsigned int type);  // GfGameScene::gevBattleStart clears type 146
    // the total count of a statistic: from its 8-bit local flag (getAchievementTotalFlgIndex8), else its 32-bit one
    // (getAchievementTotalFlgIndex32), else 0
    static unsigned int getTotalCount(unsigned int stats);
    // the 32-bit local flag holding a statistic's total: 258 + its place in the unit's 64-entry table, -1 for none
    static int getAchievementTotalFlgIndex32(unsigned short stats);
    // 2.0.0's symbols name it. What it does: the 8-bit local flag holding the total of statistics 184-213 (stats +
    // 3834), -1 for others; GfAchievStats::getAchievementAddCount and getAchievementTotalCount call it.
    static int getAchievementTotalFlgIndex8(unsigned short stats);
    // whether an affinity chart quest earns the achievement bonus count (GfGameMercenaries::
    // execMissionRewardAchievementBonusForBlade asks): its statistic is one of a fixed 67, or the task of the quest
    // after it is of type 1, 4, 6 or 11
    static bool isAddAchievementBonusCount(const AchievQuest& quest);
    // 2.0.0's symbols name it. What it does: stores value as a statistic's total: in its 8-bit local flag
    // (getAchievementTotalFlgIndex8) capped at 255, else in its 32-bit one (getAchievementTotalFlgIndex32); the only
    // caller is createKizunaTalk.
    static void setTotalCount(unsigned int type, unsigned int value);
};
}  // namespace gf

#endif
