#ifndef CLASSES_GF_GFMENUOBJFADE_H
#define CLASSES_GF_GFMENUOBJFADE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62298
class GfMenuObjFade : public ::gf::GfMenuObject {
public:
    class FadeListener;
    class LoadingListener;
    virtual ~GfMenuObjFade();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
