#ifndef GF_GFQUESTUTIL_H
#define GF_GFQUESTUTIL_H

namespace gmk { enum GmkType : int; }

namespace gf {
// the quests' helpers (functions, by their symbols)
class GfQuestUtil {
public:
    // whether a quest task ends at a gimmick: 1 when its items drop, 2 when its UI closes (GfFieldTbox's checks)
    static int getGimmickTaskEndCheck(gmk::GmkType type, unsigned int gimmickId);
};
}  // namespace gf

#endif
