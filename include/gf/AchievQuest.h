#ifndef GF_ACHIEVQUEST_H
#define GF_ACHIEVQUEST_H

#include "gf/QuestID.h"

namespace gf {

// one quest of an affinity chart line (0x1C bytes; 1.0.0's AchievQuest functions name the class). The field names
// are not the original's.
class AchievQuest {
public:
    QuestID m_questId;
    unsigned char pad_4[0x8];   // the count and the count to reach (30 bits each: 1.0.0's isCountComplete)
    // bit 0: GfKizunaringBlade's checks count the quest as done; bits 2 and 3: 1.0.0's setTaskComplete
    unsigned short m_flags;
    unsigned char pad_e[0x4];
    unsigned short m_line;      // the blade's skill line (isCompleteLevel(AchievQuest&) passes the three on)
    unsigned short m_level;     // the line's level (getSkillLevel counts one done at 1 even without its quest)
    unsigned short m_blade;
    unsigned char pad_18[0x4];
};

}  // namespace gf

#endif
