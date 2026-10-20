#ifndef CLASSES_GF_GFMENUOBJBUTTONCHALLENGE_H
#define CLASSES_GF_GFMENUOBJBUTTONCHALLENGE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B60928
class GfMenuObjButtonChallenge : public ::gf::GfMenuObject {
public:
    virtual ~GfMenuObjButtonChallenge();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
