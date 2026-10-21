#ifndef CLASSES_FW_WINDFORCECALCULATOR_H
#define CLASSES_FW_WINDFORCECALCULATOR_H

#include "mm/mtl/RTTI.h"
namespace mm { class Vec3; }
namespace mm { namespace mtl { template <typename> class Vector; }}
namespace skd { class DynamicsSolver; }

namespace fw {
// a base of fw::WindForceCalculator no evidence names yet
class TUnk_B411E8 {
public:
    virtual ~TUnk_B411E8();
    virtual const mm::mtl::RTTI* getRTTI() const = 0;
    virtual void calcForce(float, skd::DynamicsSolver const&, mm::mtl::Vector<mm::Vec3>*) = 0;
    unsigned char pad_8[0x8];  // fields: size from where the next base starts
};
// a base of fw::WindForceCalculator no evidence names yet
class TUnk_B41218 {
public:
    virtual void calcForce(float, skd::DynamicsSolver const&, mm::mtl::Vector<mm::Vec3>*) = 0;
};
// table 0x7100B411E8; base at 0x0 unknown (TUnk_B411E8), base at 0x10 unknown (TUnk_B41218)
class WindForceCalculator : public TUnk_B411E8, public TUnk_B41218 {
public:
    virtual ~WindForceCalculator();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void calcForce(float, skd::DynamicsSolver const&, mm::mtl::Vector<mm::Vec3>*);  // slot 3
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif
