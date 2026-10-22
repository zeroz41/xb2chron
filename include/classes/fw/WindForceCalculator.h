#ifndef CLASSES_FW_WINDFORCECALCULATOR_H
#define CLASSES_FW_WINDFORCECALCULATOR_H

#include "classes/fw/ForceCalculator.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/RTTI.h"
namespace fw { class WindProbe; }
namespace mm { class Vec3; }
namespace mm { namespace mtl { template <typename> class Vector; }}
namespace skd { class DynamicsSolver; }

namespace fw {
// table 0x7100B411E8; a fw::ForceCalculator (its m_rtti's base) that pushes with the wind a probe feels
class WindForceCalculator : public ForceCalculator {
public:
    virtual ~WindForceCalculator();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void calcForce(float, skd::DynamicsSolver const&, mm::mtl::Vector<mm::Vec3>*);  // slot 3
    static mm::mtl::IntrusivePtr<WindForceCalculator> create();
    void bindProbe(WindProbe& probe);
    void unbindProbe();
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif
