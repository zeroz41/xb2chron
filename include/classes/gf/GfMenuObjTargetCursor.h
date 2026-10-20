#ifndef CLASSES_GF_GFMENUOBJTARGETCURSOR_H
#define CLASSES_GF_GFMENUOBJTARGETCURSOR_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64B68
class GfMenuObjTargetCursor : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjTargetCursor();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
