#ifndef CLASSES_GF_GFCOMDYNAMICS_VIEWERLISTENER_H
#define CLASSES_GF_GFCOMDYNAMICS_VIEWERLISTENER_H

#include "classes/gf/GfComDynamics.h"

namespace gf {
// table 0x7100B662E8
class GfComDynamics::ViewerListener {
public:
    virtual void onWkStandbyLogout();  // slot 0
};
}  // namespace gf

#endif
