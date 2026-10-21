#ifndef CLASSES_GF_GFCOMBEHAVIORMAPLODANIM_H
#define CLASSES_GF_GFCOMBEHAVIORMAPLODANIM_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComBehavior.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B664B8
class GfComBehaviorMapLodAnim : public ::gf::GfComBehavior {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorMapLodAnim();  // slot 1
    virtual void update(fw::UpdateInfo const&);  // slot 5
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
