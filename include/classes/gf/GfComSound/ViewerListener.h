#ifndef CLASSES_GF_GFCOMSOUND_VIEWERLISTENER_H
#define CLASSES_GF_GFCOMSOUND_VIEWERLISTENER_H

#include "classes/gf/GfComSound.h"

namespace gf {
// table 0x7100B69CF8
class GfComSound::ViewerListener {
public:
    virtual void onWkStandbyLogout();  // slot 0
};
}  // namespace gf

#endif
