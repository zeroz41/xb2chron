#ifndef GF_GFKIZUNARINGBLADE_H
#define GF_GFKIZUNARINGBLADE_H

namespace gf { class QuestCompleteParam; }

namespace gf {
// the affinity charts' achievements; its functions take no object
class GfKizunaringBlade {
public:
    static void orderAchievement(unsigned int id);
    static void qevCompleteQuest(const QuestCompleteParam& param);
};
}  // namespace gf

#endif
