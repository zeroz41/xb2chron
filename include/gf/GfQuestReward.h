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
};
}  // namespace gf

#endif
