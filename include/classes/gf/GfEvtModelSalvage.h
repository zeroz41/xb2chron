#ifndef CLASSES_GF_GFEVTMODELSALVAGE_H
#define CLASSES_GF_GFEVTMODELSALVAGE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfEvtModelDriver.h"

namespace gf {
// table 0x7100B53D28
class GfEvtModelSalvage : public ::gf::GfEvtModelDriver {
public:
    virtual ~GfEvtModelSalvage();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
