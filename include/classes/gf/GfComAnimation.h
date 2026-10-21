#ifndef CLASSES_GF_GFCOMANIMATION_H
#define CLASSES_GF_GFCOMANIMATION_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"

namespace gf {
// table 0x7100B65508
class GfComAnimation : public ::gf::GfComponent {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComAnimation();  // slot 1
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
