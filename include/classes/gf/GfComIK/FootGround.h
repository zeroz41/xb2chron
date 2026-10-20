#ifndef CLASSES_GF_GFCOMIK_FOOTGROUND_H
#define CLASSES_GF_GFCOMIK_FOOTGROUND_H

#include "classes/gf/GfComIK.h"

namespace gf {
// table 0x7100B66398
class GfComIK::FootGround {
public:
    virtual void getPlane() const;  // slot 0
    virtual void getHitPos() const;  // slot 1
    virtual ~FootGround();  // slot 2
};
}  // namespace gf

#endif
