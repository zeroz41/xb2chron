#ifndef CLASSES_GF_GFCOMPACKANIM_H
#define CLASSES_GF_GFCOMPACKANIM_H

#include "classes/gf/GfComAnimation.h"

namespace gf {
// table 0x7100B65610
class GfComPackAnim : public ::gf::GfComAnimation {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComPackAnim();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
};
}  // namespace gf

#endif
