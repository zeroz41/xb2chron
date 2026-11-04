#ifndef GF_ARENABATTLESTART_H
#define GF_ARENABATTLESTART_H

namespace gf {

// 2.0.0's symbols name it (GfSequentialPlay::addStartChallengeBattle, GfPlayComStartChallengeBattle::create and
// GfArenaParty / GfArenaUtil take one); the field names are not the original's. The challenge a battle starts with:
// its BTL_ChBtl row id and its difficulty (GfGameArena::getMenuInfo builds one on the stack from its id and GFDIFF,
// GfArenaBattle keeps one at +0x20, GfPlayComStartChallengeBattle one at +0x20; 12 bytes). The constructor zeroes it
// (GfArenaBattle's constructor, MsgGameBtlArena's); having one makes assignments copy 9 bytes (8 + 1:
// GfPlayComStartChallengeBattle::start).
struct ArenaBattleStart {
    ArenaBattleStart() : m_id(0), m_mode(0), m_flag8(false) {}
    unsigned int m_id;
    unsigned int m_mode;
    bool m_flag8;  // getMenuInfo clears it
};

}  // namespace gf

#endif
