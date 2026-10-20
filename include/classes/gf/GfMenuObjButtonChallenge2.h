#ifndef CLASSES_GF_GFMENUOBJBUTTONCHALLENGE2_H
#define CLASSES_GF_GFMENUOBJBUTTONCHALLENGE2_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B609E8
class GfMenuObjButtonChallenge2 : public ::gf::GfMenuObject {
public:
    class MainListener;
    class RingListener;
    virtual ~GfMenuObjButtonChallenge2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
