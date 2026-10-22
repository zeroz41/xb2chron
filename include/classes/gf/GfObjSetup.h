#ifndef CLASSES_GF_GFOBJSETUP_H
#define CLASSES_GF_GFOBJSETUP_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
namespace gf {
// table 0x7100B6A4C8
class GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetup() {}  // slot 1
    virtual void getFootStep() const;  // slot 3
    virtual void getFootStepEffect() const;  // slot 4
    virtual void getEnArrangeID() const;  // slot 5
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_8[0x38];
    // the object's scale: 1.0.0's setInitialScale(float) and setInitialScale(const mm::Vec3&) set it (the name is
    // not the original's)
    mm::Vec3 m_initialScale;
};
}  // namespace gf

#endif
