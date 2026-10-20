#ifndef CLASSES_GF_GFCOMTRANSFORM_LISTENER_H
#define CLASSES_GF_GFCOMTRANSFORM_LISTENER_H

#include "classes/gf/GfComTransform.h"

namespace gf {
// table 0x7100B66420
class GfComTransform::Listener {
public:
    virtual void onWkStandbyLogout();  // slot 0
};
}  // namespace gf

#endif
