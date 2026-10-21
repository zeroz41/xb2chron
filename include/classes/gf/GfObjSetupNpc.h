#ifndef CLASSES_GF_GFOBJSETUPNPC_H
#define CLASSES_GF_GFOBJSETUPNPC_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A5C8
class GfObjSetupNpc : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupNpc();  // slot 1
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
