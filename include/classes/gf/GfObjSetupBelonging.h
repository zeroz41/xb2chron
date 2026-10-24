#ifndef CLASSES_GF_GFOBJSETUPBELONGING_H
#define CLASSES_GF_GFOBJSETUPBELONGING_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A748
class GfObjSetupBelonging : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupBelonging() {}  // slot 1
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
