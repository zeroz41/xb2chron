#ifndef CLASSES_GF_GFOBJSETUPBLADE_H
#define CLASSES_GF_GFOBJSETUPBLADE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A488
class GfObjSetupBlade : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupBlade();  // slot 1
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
