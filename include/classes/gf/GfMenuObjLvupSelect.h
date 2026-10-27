#ifndef CLASSES_GF_GFMENUOBJLVUPSELECT_H
#define CLASSES_GF_GFMENUOBJLVUPSELECT_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
class GfMenuCallContext;
// table 0x7100B62EF8
class GfMenuObjLvupSelect : public ::gf::GfMenuObject {
public:
    class DrImgListener;
    class MainListener;
    class SelectListener;
    virtual ~GfMenuObjLvupSelect();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // opens the level select for a driver row (GfMenuObjLvupMain's MainListener passes its context and the selection)
    static void openLevelSelect(GfMenuCallContext* context, unsigned int driver);
};
}  // namespace gf

#endif
