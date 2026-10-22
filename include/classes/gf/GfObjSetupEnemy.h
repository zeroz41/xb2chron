#ifndef CLASSES_GF_GFOBJSETUPENEMY_H
#define CLASSES_GF_GFOBJSETUPENEMY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
namespace gf {
// table 0x7100B6A448; its m_rtti names GfObjSetup's as its base (gf_obj_setup.cpp's static initializer)
class GfObjSetupEnemy : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupEnemy();  // slot 1
    virtual void getFootStep() const;  // slot 3
    virtual void getFootStepEffect() const;  // slot 4
    virtual void getEnArrangeID() const;  // slot 5
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
