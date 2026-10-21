#ifndef CLASSES_GF_GFCOMPACKANIM_H
#define CLASSES_GF_GFCOMPACKANIM_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComAnimation.h"

namespace gf {
// table 0x7100B65610
class GfComPackAnim : public ::gf::GfComAnimation {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComPackAnim();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
