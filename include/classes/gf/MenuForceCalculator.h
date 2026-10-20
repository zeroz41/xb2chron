#ifndef CLASSES_GF_MENUFORCECALCULATOR_H
#define CLASSES_GF_MENUFORCECALCULATOR_H

namespace mm { class Vec3; }
namespace mm { namespace mtl { template <typename> class Vector; }}
namespace skd { class DynamicsSolver; }

namespace gf {
// a base of gf::MenuForceCalculator no evidence names yet
class TUnk_B5F888 {
public:
    virtual ~TUnk_B5F888();
    virtual void getRTTI() const = 0;
    virtual void calcForce(float, skd::DynamicsSolver const&, mm::mtl::Vector<mm::Vec3>*) = 0;
    unsigned char pad_8[0x8];  // fields: size from where the next base starts
};
// a base of gf::MenuForceCalculator no evidence names yet
class TUnk_B5F8B8 {
public:
    virtual void calcForce(float, skd::DynamicsSolver const&, mm::mtl::Vector<mm::Vec3>*) = 0;
};
// table 0x7100B5F888; base at 0x0 unknown (TUnk_B5F888), base at 0x10 unknown (TUnk_B5F8B8)
class MenuForceCalculator : public TUnk_B5F888, public TUnk_B5F8B8 {
public:
    virtual ~MenuForceCalculator();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void calcForce(float, skd::DynamicsSolver const&, mm::mtl::Vector<mm::Vec3>*);  // slot 3
};
}  // namespace gf

#endif
