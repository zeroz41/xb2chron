#ifndef CLASSES_GMK_GAMEFLAGCOND_H
#define CLASSES_GMK_GAMEFLAGCOND_H

namespace gmk {
// table 0x7100B6F398
class GameFlagCond {
public:
    // GmkMapGimmick::isNotSolved builds one on the stack: both fields stored together after the table
    GameFlagCond(int flagType, int flagIndex) : m_flagType(flagType), m_flagIndex(flagIndex) {}
    virtual ~GameFlagCond() {}  // slot 0
    // the local game flag of type 1 << (m_flagType - 1) at m_flagIndex equals value (false for a type outside 1..6)
    bool isMatch(unsigned int value) const;
    // the names are not the original's
    int m_flagType;   // 0x8: 1..6
    int m_flagIndex;  // 0xC
};
}  // namespace gmk

#endif
