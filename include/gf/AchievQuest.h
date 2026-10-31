#ifndef GF_ACHIEVQUEST_H
#define GF_ACHIEVQUEST_H

#include "gf/QuestID.h"

namespace gf {

// one quest of an affinity chart line (0x1C bytes; 1.0.0's AchievQuest functions name the class). The field names
// are not the original's.
class AchievQuest {
public:
    QuestID m_questId;
    // the count and the count to reach, 30 bits each (1.0.0's isCountComplete; GfQuestInfo masks them)
    unsigned int m_count;
    unsigned int m_countMax;
    // bit 0: GfKizunaringBlade's checks count the quest as done; bits 2 and 3: 1.0.0's setTaskComplete
    unsigned short m_flags;
    // the statistic the quest counts (GfAchievStats::getAchievementTotalCount reads its total for it)
    unsigned short m_stats;
    unsigned char pad_10[0x2];
    unsigned short m_line;      // the blade's skill line (isCompleteLevel(AchievQuest&) passes the three on)
    unsigned short m_level;     // the line's level (getSkillLevel counts one done at 1 even without its quest)
    unsigned short m_blade;
    unsigned char pad_18[0x4];

    // whether the count changed (GfQuestInfo::incCollectUseCount and decCollectUseCount answer it)
    bool incleseCount(unsigned int count);
    bool decleseCount(unsigned int count);
    // sets the count (up to the count to reach); whether it rose
    bool setCount(unsigned int count);
    bool isCountComplete() const;
    // sets (set) or clears flag bit 2 (task true) or bit 3 (task false); GfQuestTask::isCompleteFlag tests bit 2 for
    // a quest with no PRT quest, else bit 3
    void setTaskComplete(bool task, bool set);
    // raises the count to the count to reach and tells the achievement manager what it added
    void setCountComplete();
};

}  // namespace gf

#endif
