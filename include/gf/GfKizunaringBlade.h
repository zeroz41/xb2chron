#ifndef GF_GFKIZUNARINGBLADE_H
#define GF_GFKIZUNARINGBLADE_H

namespace gf { class AchievQuest; }
namespace gf { class QuestCompleteParam; }

namespace gf {
// the affinity charts' achievements; its functions take no object
class GfKizunaringBlade {
public:
    // orders the quests of every chart line the player can take next
    static void refreshOrderQuestList();
    // whether a blade's chart line has reached a level: the blade is active and its line's earlier quests are done
    static bool isCompleteLevel(unsigned int blade, unsigned int line, unsigned int level);
    // whether a chart level's quest may be shown: its next quest's first task condition holds (or it has none)
    static bool isNetabareOK(unsigned int blade, unsigned int line, unsigned int level);
    static bool isCompleteLevel(const AchievQuest& quest);
    static void orderAchievement(unsigned int id);
    static void qevCompleteQuest(const QuestCompleteParam& param);
    // the levels of a blade's chart line up to level that are done
    static int getSkillLevel(unsigned int blade, unsigned int line, unsigned int level);
};
}  // namespace gf

#endif
