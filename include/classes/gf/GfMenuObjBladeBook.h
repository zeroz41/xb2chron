#ifndef CLASSES_GF_GFMENUOBJBLADEBOOK_H
#define CLASSES_GF_GFMENUOBJBLADEBOOK_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B5FDB8
class GfMenuObjBladeBook : public ::gf::GfMenuObject {
public:
    class ListListener;
    class MainListener;
    class PreviewListener;
    virtual ~GfMenuObjBladeBook();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
