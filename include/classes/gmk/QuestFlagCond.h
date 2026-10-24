#ifndef CLASSES_GMK_QUESTFLAGCOND_H
#define CLASSES_GMK_QUESTFLAGCOND_H

class CBdatWrapper;

namespace gmk {
// a gimmick row's condition of 4 bytes (no table); GfFieldMapGimmick::BdatInfo holds one, built from the row's
// "OP_" columns by the (CBdatWrapper, row, prefix) constructor
class QuestFlagCond {
public:
    QuestFlagCond() : m_questFlag(0), m_questFlagMin(0), m_questFlagMax(0) {}
    QuestFlagCond(const CBdatWrapper& bdat, int row, const char* prefix);
    bool isMatch() const;
    // the row's <prefix>QuestFlag, QuestFlagMin and QuestFlagMax (the constructor reads those columns; the names
    // are not the original's)
    unsigned short m_questFlag;
    unsigned char m_questFlagMin;
    unsigned char m_questFlagMax;
};
}  // namespace gmk

#endif
