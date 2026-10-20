#ifndef CLASSES_GF_GFMENUOBJMOVIELAYER_H
#define CLASSES_GF_GFMENUOBJMOVIELAYER_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63818
class GfMenuObjMovieLayer : public ::gf::GfMenuObject {
public:
    virtual ~GfMenuObjMovieLayer();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
