#ifndef CLASSES_GF_GFOBJSETUP_H
#define CLASSES_GF_GFOBJSETUP_H

#include "mm/mtl/RTTI.h"
namespace gf {
// table 0x7100B6A4C8
class GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetup();  // slot 1
    virtual void getFootStep() const;  // slot 3
    virtual void getFootStepEffect() const;  // slot 4
    virtual void getEnArrangeID() const;  // slot 5
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
