#ifndef GF_CHBTLINFO_H
#define GF_CHBTLINFO_H

namespace gf {

// 2.0.0's symbols name it and its nested ChBtlDiff (GfArenaUtil::setPlayEvent / isPlayEvent take a
// FixedArray<ChBtlInfo, 48>, setupMenuInfoForCube / Score / ClearTime a ChBtlInfo::ChBtlDiff); the field names are not
// the original's. One challenge battle's saved record: SaveChBtl keeps 48 (SDataGame's at 0x11A8CC); its ChBtlDiff
// per difficulty (GfGameArena::getSaveInfo(id, GFDIFF) returns one), setupGame sets the flags.
struct ChBtlInfo {
    // 12 bytes the arena copies from SDataGame's table (row * 0x40 + difficulty * 12 at 0x11A8CC)
    struct ChBtlDiff {
        ChBtlDiff() : m_value0(0), m_value4(0), m_value8(0), m_flag8(0) {}
        unsigned int m_value0;
        unsigned int m_value4;
        unsigned int m_value8 : 17;  // also stored at 0x2C
        unsigned int m_flag8 : 7;
    };
    ChBtlInfo() : m_flag3C(0), m_isChecked(false), m_flag3E(false) {}
    ChBtlDiff m_rules[5];
    // setupGame: !GfBdatBtl::isBTL_ChBtlFlagHide(id) the first time; applyChallengeStatus sets 1,
    // GfArenaUtil::setChallengeOK 2 (a state, not a bool)
    unsigned char m_flag3C;
    bool m_isChecked;  // setupGame sets it once it has set m_flag3C
    bool m_flag3E;
};

}  // namespace gf

#endif
