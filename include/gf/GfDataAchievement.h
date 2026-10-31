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
    // the total count of a statistic: from its 8-bit local flag (fn_710024B4D0), else its 32-bit one
    // (getAchievementTotalFlgIndex), else 0
    static unsigned int getTotalCount(unsigned int stats);
    // the 32-bit local flag holding a statistic's total: 258 + its place in the unit's 64-entry table, -1 for none
    static int getAchievementTotalFlgIndex(unsigned short stats);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataAchievement's functions and getTotalCount, addTotalCount and clearTotalCount
    // inline it before getAchievementTotalFlgIndex. What it does: the 8-bit local flag holding the total of statistics
    // 184-213 (stats + 3834), -1 for others; GfAchievStats::getAchievementAddCount and getAchievementTotalCount call it.
    static int fn_710024B4D0(unsigned short stats);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataAchievement's functions, between addTotalCount and setupTotalCount. What it does:
    // stores value as a statistic's total: in its 8-bit local flag (fn_710024B4D0) capped at 255, else in its 32-bit
    // one (getAchievementTotalFlgIndex); the only caller is fn_71005663BC.
    static void fn_710024B71C(unsigned int type, unsigned int value);
};
}  // namespace gf

#endif
