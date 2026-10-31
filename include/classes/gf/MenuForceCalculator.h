#ifndef CLASSES_GF_MENUFORCECALCULATOR_H
#define CLASSES_GF_MENUFORCECALCULATOR_H

#include "classes/fw/ForceCalculator.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/RTTI.h"
namespace mm { class Vec3; }
namespace mm { namespace mtl { template <typename> class Vector; }}
namespace skd { class DynamicsSolver; }

namespace gf {
// table 0x7100B5F888; a fw::ForceCalculator (its m_rtti's base) whose force swings along z for a while
class MenuForceCalculator : public fw::ForceCalculator {
public:
    // inline here: 1.0.0 has an out-of-line copy, 3.0.1 none (create inlines it)
    MenuForceCalculator() : m_time(0.0f) {}
    virtual ~MenuForceCalculator();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void calcForce(float, skd::DynamicsSolver const&, mm::mtl::Vector<mm::Vec3>*);  // slot 3
    static mm::mtl::IntrusivePtr<MenuForceCalculator> create();
    static mm::mtl::RTTI m_rtti;

    float m_time;  // seconds summed by calcForce for solver 0 (the name is not the original's)
};
}  // namespace gf

#endif
