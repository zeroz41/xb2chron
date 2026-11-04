#ifndef GF_SAVECHBTL_H
#define GF_SAVECHBTL_H

#include "gf/ChBtlInfo.h"
#include "mm/mtl/FixedArray.h"

namespace gf {

// 2.0.0's symbols name it (SaveChBtl::clear; GfArenaUtil's setupSaveData / applyChallengeStatus / setChallengeOK
// take one); the field name is not the original's. The challenge battle records of the save data (SDataGame's at
// 0x11A8CC; GfGameArena::getSaveInfo returns it): one ChBtlInfo per BTL_ChBtl row (setPlayEvent / isPlayEvent take
// m_rows, at its start).
class SaveChBtl {
public:
    // SDataGame's constructor and GfGameArena's run clear on their tables
    SaveChBtl() { clear(); }
    // 2.0.0's symbols name it. Its code is in title_main's unit range. What it does: clears each row's five
    // difficulties (copies of a zeroed array) and flags.
    void clear();
    ::mm::mtl::FixedArray<ChBtlInfo, 48> m_rows;
};

}  // namespace gf

#endif
