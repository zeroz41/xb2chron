#ifndef CLASSES_GF_GFCOMBEHAVIORMAPLODANIM_H
#define CLASSES_GF_GFCOMBEHAVIORMAPLODANIM_H

#include "classes/gf/GfComBehavior.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B664B8
class GfComBehaviorMapLodAnim : public ::gf::GfComBehavior {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComBehaviorMapLodAnim();  // slot 1
    virtual void update(fw::UpdateInfo const&);  // slot 5
};
}  // namespace gf

#endif
