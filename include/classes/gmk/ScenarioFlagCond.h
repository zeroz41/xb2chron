#ifndef CLASSES_GMK_SCENARIOFLAGCOND_H
#define CLASSES_GMK_SCENARIOFLAGCOND_H

class CBdatWrapper;

namespace gmk {
// a gimmick row's condition of 4 bytes (no table); GfFieldMapGimmick::BdatInfo holds one, built from the row's
// "OP_" columns by the (CBdatWrapper, row, prefix) constructor
class ScenarioFlagCond {
public:
    ScenarioFlagCond() : pad_0(0), pad_2(0) {}
    ScenarioFlagCond(const CBdatWrapper& bdat, int row, const char* prefix);
    bool isMatch() const;
    unsigned short pad_0;
    unsigned short pad_2;
};
}  // namespace gmk

#endif
