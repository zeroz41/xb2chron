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
    virtual unsigned int getEnArrangeID() const;  // slot 5
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_8[0x8];
    // the object's bdat row: the data objects' constructors read it (DataObjNpc, DataObjMap, DataObjMob,
    // DataObjGmk; the name is not the original's)
    unsigned int m_bdatId;
    unsigned char pad_14[0xC];
    // the object's initial position: setInitialTransform's (the name is not the original's)
    mm::Vec3 m_initialPos;
    unsigned char pad_30[0x10];
    // the object's scale: 1.0.0's setInitialScale(float) and setInitialScale(const mm::Vec3&) set it (the name is
    // not the original's)
    mm::Vec3 m_initialScale;
};
}  // namespace gf

#endif
