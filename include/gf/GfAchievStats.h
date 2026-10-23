#ifndef GF_GFACHIEVSTATS_H
#define GF_GFACHIEVSTATS_H

namespace gf { class AchievQuest; }

namespace gf {
// the affinity chart quests' counts kept in the game's stats (functions, by their symbols)
class GfAchievStats {
public:
    // the quest's count from the stats; negative when the stats keep none for it
    static int getAchievementTotalCount(const AchievQuest& quest);
};
}  // namespace gf

#endif
