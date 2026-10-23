#ifndef CLASSES_GF_GFQUESTMANAGER_H
#define CLASSES_GF_GFQUESTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/QuestID.h"
#include "gf/QuestListAcc.h"
#include "mm/mtl/FixStr.h"

namespace gf { class GfQuestManager; }

namespace gf {
// a quest's rewards, as GfQuestManager::getRewardItem fills them: twelve texts with their numbers (the names are not
// the original's)
struct GfQuestReward {
    struct Item {
        Item() : m_value(0) {}
        mm::mtl::FixStr<64> m_text;
        unsigned int m_value;
    };
    Item m_items[12];
};
}  // namespace gf

namespace gf {
// table 0x7100B56DB0
class GfQuestManager : public ::mm::mtl::PtrSingleton< ::gf::GfQuestManager> {
public:
    virtual ~GfQuestManager();  // slot 0
    static void entryOrderAchievQuest(gf::QuestID id);
    // whether the quest's order opened (GfQuestEvent::setQuestEntry tests it)
    static bool openOrder(gf::QuestID id, bool notify);
    static bool getRewardItem(GfQuestReward& reward, gf::QuestID id, bool);
    static gf::QuestID getCurrentQuest(QTYPE type);
};
}  // namespace gf

#endif
