#ifndef GF_GFQUESTREWARD_H
#define GF_GFQUESTREWARD_H

#include "mm/mtl/FixStr.h"

namespace gf {
// a quest's rewards, as GfQuestManager::getRewardItem fills them: twelve texts with their numbers (the names are not
// the original's)
struct GfQuestReward {
    // one reward: its text and number. Param is the original's name (the symbols name Param::getDevelopZone, which
    // reads the high half of the development reward's m_value); the field names are not the original's
    class Param {
    public:
        Param() : m_value(0) {}
        // the map of the development zone in m_value's high half
        unsigned int getDevelopZone() const;

        mm::mtl::FixStr<64> m_text;
        unsigned int m_value;
    };

    Param m_items[12];
    // 0x360: the blade item 5's trust goes to (GfQuestUtil::execReward passes it to SCOM_ADD_TRUST::create; the
    // original's stack copies are 0x368 bytes). The name is not the original's.
    unsigned short m_trustBlade;
};
}  // namespace gf

#endif
