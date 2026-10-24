#ifndef CLASSES_GF_GFOBJSETUPEXTRA_H
#define CLASSES_GF_GFOBJSETUPEXTRA_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A788
class GfObjSetupExtra : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupExtra() {}  // slot 1
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
