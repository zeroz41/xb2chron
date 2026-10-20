#ifndef CLASSES_GF_GFMENUOBJBALLOON_H
#define CLASSES_GF_GFMENUOBJBALLOON_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B5FBB0
class GfMenuObjBalloon : public ::gf::GfMenuObject {
public:
    class AutoTalkListener;
    class BoxListener;
    class EvSelectListener;
    class EvTalkListener;
    class GetItemListener;
    class SelMoneyListener;
    virtual ~GfMenuObjBalloon();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
