#ifndef CLASSES_GF_GFMENUOBJCOMBOROUTE_H
#define CLASSES_GF_GFMENUOBJCOMBOROUTE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61360
class GfMenuObjComboRoute : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjComboRoute();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
