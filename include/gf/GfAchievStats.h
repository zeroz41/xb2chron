#ifndef GF_GFACHIEVSTATS_H
#define GF_GFACHIEVSTATS_H

namespace gf { class AchievQuest; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// the affinity chart quests' counts kept in the game's stats (functions, by their symbols)
class GfAchievStats {
public:
    // the quest's count from the stats; negative when the stats keep none for it
    static int getAchievementTotalCount(const AchievQuest& quest);
    // counts a talk with an NPC (GfPlayComTalk::start: the talk's NPC id and object)
    static void checkTalk(unsigned int npc, GF_OBJ_HANDLE* handle);
};
}  // namespace gf

#endif
