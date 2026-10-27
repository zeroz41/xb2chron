#ifndef CLASSES_GMK_QUESTFLAGCOND_H
#define CLASSES_GMK_QUESTFLAGCOND_H

class CBdatWrapper;

namespace gmk {
// a gimmick row's condition of 4 bytes (no table); GfFieldMapGimmick::BdatInfo holds one, built from the row's
// "OP_" columns by the (CBdatWrapper, row, prefix) constructor
class QuestFlagCond {
public:
    QuestFlagCond() : m_questFlag(0), m_questFlagMin(0), m_questFlagMax(0) {}
    // the three values as they are (the gimmick sheets' BdatInfo::create read the row's QuestFlag/Min/Max so)
    QuestFlagCond(unsigned short flag, unsigned char min, unsigned char max)
        : m_questFlag(flag), m_questFlagMin(min), m_questFlagMax(max) {}
    QuestFlagCond(const CBdatWrapper& bdat, int row, const char* prefix);
    bool isMatch() const;
    // a quest is named and min <= max (GmkEnemyInsts::BdatInfo tests this before isMatch; an inline member: its
    // loads keep the class's 2-byte alignment, the two bytes read as one halfword; the name is not the original's)
    bool isSet() const { return m_questFlag != 0 && m_questFlagMin <= m_questFlagMax; }
    // the row's <prefix>QuestFlag, QuestFlagMin and QuestFlagMax (the constructor reads those columns; the names
    // are not the original's)
    unsigned short m_questFlag;
    unsigned char m_questFlagMin;
    unsigned char m_questFlagMax;
};
}  // namespace gmk

#endif
