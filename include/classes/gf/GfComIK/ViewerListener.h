#ifndef CLASSES_GF_GFCOMIK_VIEWERLISTENER_H
#define CLASSES_GF_GFCOMIK_VIEWERLISTENER_H

#include "classes/gf/GfComIK.h"

namespace gf {
// table 0x7100B66338
class GfComIK::ViewerListener {
public:
    virtual void onWkStandbyLogout();  // slot 0
};
}  // namespace gf

#endif
