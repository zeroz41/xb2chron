#ifndef CLASSES_GF_GFMENUOBJMINIGAME_H
#define CLASSES_GF_GFMENUOBJMINIGAME_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B636F0
class GfMenuObjMiniGame : public ::gf::GfMenuObject {
public:
    virtual ~GfMenuObjMiniGame();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
