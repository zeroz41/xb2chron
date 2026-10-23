#ifndef GF_GFQUESTUTIL_H
#define GF_GFQUESTUTIL_H

namespace gmk { enum GmkType : int; }

namespace gf {
// the quests' helpers (functions, by their symbols)
class GfQuestUtil {
public:
    static bool getDispCount(unsigned int& count, unsigned int& max, const struct AchievQuest& quest);
    static bool getResultIdea(unsigned int& idea, unsigned int& count, unsigned int blade, unsigned int line,
                              unsigned int level);
    // whether a quest task ends at a gimmick: 1 when its items drop, 2 when its UI closes (GfFieldTbox's checks)
    static int getGimmickTaskEndCheck(gmk::GmkType type, unsigned int gimmickId);
};
}  // namespace gf

#endif
