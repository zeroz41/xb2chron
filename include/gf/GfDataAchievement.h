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
};
}  // namespace gf

#endif
