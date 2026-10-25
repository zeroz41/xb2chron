#ifndef CLASSES_GF_GFMENUOBJMINIMAP2_H
#define CLASSES_GF_GFMENUOBJMINIMAP2_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63738
class GfMenuObjMinimap2 : public ::gf::GfMenuObject {
public:
    class MainListener;
    class MapListener;
    static void enable();
    static void disable();
    virtual ~GfMenuObjMinimap2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
