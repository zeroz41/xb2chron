#ifndef CLASSES_GF_GFCOMIK_GROUND_H
#define CLASSES_GF_GFCOMIK_GROUND_H

#include "classes/gf/GfComIK.h"

namespace fw { class IKFootIndex; }

namespace gf {
// table 0x7100B66350
class GfComIK::Ground {
public:
    virtual void getFootGround(fw::IKFootIndex);  // slot 0
    virtual void getPlane() const;  // slot 1
    virtual void getHitPos() const;  // slot 2
    virtual void getPlaneSub() const;  // slot 3
    virtual void getHitPosSub() const;  // slot 4
    virtual ~Ground();  // slot 5
};
}  // namespace gf

#endif
