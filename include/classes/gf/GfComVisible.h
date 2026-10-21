#ifndef CLASSES_GF_GFCOMVISIBLE_H
#define CLASSES_GF_GFCOMVISIBLE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"

namespace gf {
// table 0x7100B66808
class GfComVisible : public ::gf::GfComponent {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComVisible();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
