#ifndef CLASSES_GF_GFCOMASM_VIEWERLISTENER_H
#define CLASSES_GF_GFCOMASM_VIEWERLISTENER_H

#include "classes/gf/GfComAsm.h"

namespace gf {
// table 0x7100B65590
class GfComAsm::ViewerListener {
public:
    virtual void onWkStandbyLogout();  // slot 0
};
}  // namespace gf

#endif
