#ifndef CLASSES_FW_FORCECALCULATOR_H
#define CLASSES_FW_FORCECALCULATOR_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/RTTI.h"

namespace mm { class Vec3; }
namespace mm { namespace mtl { template <typename> class Vector; }}
namespace skd { class DynamicsSolver; }

namespace skd {
// what a dynamics asks for its external force (skd::Factory::createDynamics takes one)
class ForceInterface {
public:
    virtual void calcForce(float, skd::DynamicsSolver const&, mm::mtl::Vector<mm::Vec3>*) = 0;
};
}  // namespace skd

namespace fw {
// the force calculators' common base. 1.0.0 names its type fw::ForceCalculator::m_rtti ("ForceCalculator", no
// bases; here lbl_7100C23480, constructed by DebugCommander's initializer), the base WindForceCalculator's and
// MenuForceCalculator's m_rtti name. Counted (GfComDynamics holds one by IntrusivePtr: the count at 8, released
// through slot 1), its RTTI in slot 2, its skd::ForceInterface at 0x10 (what GfComDynamics::setup hands
// createDynamics); the derived tables (TUnk_B411E8 / TUnk_B5F888 in their headers) have this shape.
class ForceCalculator : public mm::mtl::ReferenceObject, public skd::ForceInterface {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;  // slot 2
    virtual void calcForce(float, skd::DynamicsSolver const&, mm::mtl::Vector<mm::Vec3>*) = 0;  // slot 3
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif
