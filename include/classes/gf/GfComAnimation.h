#ifndef CLASSES_GF_GFCOMANIMATION_H
#define CLASSES_GF_GFCOMANIMATION_H

#include "classes/gf/GfComponent.h"

namespace gf {
// table 0x7100B65508
class GfComAnimation : public ::gf::GfComponent {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComAnimation();  // slot 1
};
}  // namespace gf

#endif
