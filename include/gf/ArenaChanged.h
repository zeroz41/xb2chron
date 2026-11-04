#ifndef GF_ARENACHANGED_H
#define GF_ARENACHANGED_H

#include "mm/mtl/FixedVector.h"

namespace gf {

// 2.0.0's symbols name it (ArenaChanged::operator=; GfArenaUtil::setupLevelForBattleStart / setupRankForBattleStart
// take one); the field names are not the original's. The two lists GfGameArena::getMenuInfo fills (ArenaMenuInfo
// keeps one at 0x38, GfArenaParty one of its own).
struct ArenaChanged {
    // the elements of the two lists: three shorts each (the copies divide by 6; room for 26 and 422). No symbol
    // names them.
    // Entry38 is a party driver's id, its level and the level the challenge sets (setupLevelForBattleStart fills
    // them; GfArenaParty::setupLevelForBattleStart sets m_challengeLevel, setupLevelForBattleEnd puts m_level back).
    // The names are not the original's.
    struct Entry38 {
        unsigned short m_driver;
        unsigned short m_level;
        unsigned short m_challengeLevel;
    };
    // filled by setupRankForBattleStart; what the shorts hold is not recovered
    struct EntryE0 {
        unsigned short pad_0;
        unsigned short pad_2;
        unsigned short pad_4;
    };
    mm::mtl::FixedVector<Entry38, 26> m_list38;
    mm::mtl::FixedVector<EntryE0, 422> m_listE0;
};

}  // namespace gf

#endif
