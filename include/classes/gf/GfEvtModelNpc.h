#ifndef CLASSES_GF_GFEVTMODELNPC_H
#define CLASSES_GF_GFEVTMODELNPC_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfEvtModel.h"

namespace gf {
// table 0x7100B53E68
class GfEvtModelNpc : public ::gf::GfEvtModel {
public:
    virtual ~GfEvtModelNpc();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
