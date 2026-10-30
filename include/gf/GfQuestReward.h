#ifndef GF_GFQUESTREWARD_H
#define GF_GFQUESTREWARD_H

#include "mm/mtl/FixStr.h"

namespace gf {
// a quest's rewards, as GfQuestManager::getRewardItem fills them: twelve texts with their numbers (the names are not
// the original's)
struct GfQuestReward {
    struct Item {
        Item() : m_value(0) {}
        mm::mtl::FixStr<64> m_text;
        unsigned int m_value;
    };
    // one reward's parameters (the field names are not the original's)
    class Param {
    public:
        // the map getDevelopZone's development zone is on
        unsigned int getDevelopZone() const;

        unsigned char pad_0[0x46];
        unsigned short m_developZone;  // getDevelopZone's
    };

    Item m_items[12];
    // 0x360: the blade item 5's trust goes to (GfQuestUtil::execReward passes it to SCOM_ADD_TRUST::create; the
    // original's stack copies are 0x368 bytes). The name is not the original's.
    unsigned short m_trustBlade;
};
}  // namespace gf

#endif
