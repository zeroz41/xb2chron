#ifndef CLASSES_GF_GFOBJSETUPMAP_H
#define CLASSES_GF_GFOBJSETUPMAP_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A548
class GfObjSetupMap : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupMap();  // slot 1
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
