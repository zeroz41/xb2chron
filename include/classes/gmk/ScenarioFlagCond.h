#ifndef CLASSES_GMK_SCENARIOFLAGCOND_H
#define CLASSES_GMK_SCENARIOFLAGCOND_H

class CBdatWrapper;

namespace gmk {
// a gimmick row's condition of 4 bytes (no table); GfFieldMapGimmick::BdatInfo holds one, built from the row's
// "OP_" columns by the (CBdatWrapper, row, prefix) constructor
class ScenarioFlagCond {
public:
    ScenarioFlagCond() : m_scenarioFlagMin(0), m_scenarioFlagMax(0) {}
    // the two values as they are (the gimmick sheets' BdatInfo::create read the row's ScenarioFlagMin/Max so)
    ScenarioFlagCond(unsigned short min, unsigned short max) : m_scenarioFlagMin(min), m_scenarioFlagMax(max) {}
    ScenarioFlagCond(const CBdatWrapper& bdat, int row, const char* prefix);
    bool isMatch() const;
    // the row's <prefix>ScenarioFlagMin and ScenarioFlagMax, kept when min <= max (the constructor reads those
    // columns; the names are not the original's)
    unsigned short m_scenarioFlagMin;
    unsigned short m_scenarioFlagMax;
};
}  // namespace gmk

#endif
