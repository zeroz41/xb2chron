#ifndef CLASSES_FW_FORCECALCULATOR_H
#define CLASSES_FW_FORCECALCULATOR_H

#include "mm/mtl/RTTI.h"

namespace fw {
// the force calculators' common base. 1.0.0 names its type fw::ForceCalculator::m_rtti ("ForceCalculator", no
// bases; here lbl_7100C23480, constructed by DebugCommander's initializer), the base WindForceCalculator's and
// MenuForceCalculator's m_rtti name. Its table and members are not identified yet (the derived headers' base
// TUnk_B411E8 / TUnk_B5F888 has its shape).
class ForceCalculator {
public:
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif
