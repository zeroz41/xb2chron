#ifndef CLASSES_GF_GFMENUOBJHANAPARTSCRYSTAL_H
#define CLASSES_GF_GFMENUOBJHANAPARTSCRYSTAL_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B627C8
class GfMenuObjHanaPartsCrystal : public ::gf::GfMenuObject {
public:
    class ItemListListener;
    class MainListener;
    class NumSelectListener;
    class PartsListListener;
    virtual ~GfMenuObjHanaPartsCrystal();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
