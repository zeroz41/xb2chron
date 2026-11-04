#ifndef GF_ARENABATTLEINFO_H
#define GF_ARENABATTLEINFO_H

namespace gf {

// 2.0.0's symbols name it (GfArenaReward's functions take one); the field names are not the original's. What
// StateArenaResultBattle's steps pass to GfArenaReward's getTresureBoxNum / createTresureBox / createMoney /
// playVoice / dropClearReward: m_id is a BTL_ChBtl row (GfBdatBtl's getBTL_ChBtlTresureNeed / getBTL_ChBtlClearReward
// take it), m_value is compared with that row's TresureNeed1..3 values. 16 bytes: GfArenaBattle::execBattleSequence
// copies it whole (two 8-byte moves) into m_resultScore.
struct ArenaBattleInfo {
    unsigned int m_id;
    unsigned int pad_4;
    unsigned int m_value;
    unsigned int pad_C;
};

}  // namespace gf

#endif
