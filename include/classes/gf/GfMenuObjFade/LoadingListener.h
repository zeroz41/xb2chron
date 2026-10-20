#ifndef CLASSES_GF_GFMENUOBJFADE_LOADINGLISTENER_H
#define CLASSES_GF_GFMENUOBJFADE_LOADINGLISTENER_H

#include "classes/gf/GfMenuObjFade.h"

namespace gf {
// table 0x7100B62308
class GfMenuObjFade::LoadingListener {
public:
    virtual ~LoadingListener();  // slot 0
    virtual void vf2();  // slot 2
};
}  // namespace gf

#endif
