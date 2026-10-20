#ifndef CLASSES_GF_GFMENUOBJFIELDICON_H
#define CLASSES_GF_GFMENUOBJFIELDICON_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62330
class GfMenuObjFieldIcon : public ::gf::GfMenuObject {
public:
    virtual ~GfMenuObjFieldIcon();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
