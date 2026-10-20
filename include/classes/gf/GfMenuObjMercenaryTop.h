#ifndef CLASSES_GF_GFMENUOBJMERCENARYTOP_H
#define CLASSES_GF_GFMENUOBJMERCENARYTOP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63608
class GfMenuObjMercenaryTop : public ::gf::GfMenuObject {
public:
    class MainListener;
    class MissionListener;
    class ZoneListener;
    virtual ~GfMenuObjMercenaryTop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
