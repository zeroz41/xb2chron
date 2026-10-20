#ifndef CLASSES_GF_GFMENUOBJHANAPARTSMAKE_H
#define CLASSES_GF_GFMENUOBJHANAPARTSMAKE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B628B0
class GfMenuObjHanaPartsMake : public ::gf::GfMenuObject {
public:
    class ItemListListener;
    class MainListener;
    class NumSelectListener;
    class PartsListListener;
    virtual ~GfMenuObjHanaPartsMake();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
