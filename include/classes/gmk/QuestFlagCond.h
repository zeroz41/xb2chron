#ifndef CLASSES_GMK_QUESTFLAGCOND_H
#define CLASSES_GMK_QUESTFLAGCOND_H

class CBdatWrapper;

namespace gmk {
// a gimmick row's condition of 4 bytes (no table); GfFieldMapGimmick::BdatInfo holds one, built from the row's
// "OP_" columns by the (CBdatWrapper, row, prefix) constructor
class QuestFlagCond {
public:
    QuestFlagCond() : pad_0(0), pad_2(0), pad_3(0) {}
    QuestFlagCond(const CBdatWrapper& bdat, int row, const char* prefix);
    bool isMatch() const;
    unsigned short pad_0;
    unsigned char pad_2;
    unsigned char pad_3;
};
}  // namespace gmk

#endif
