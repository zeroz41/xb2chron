#ifndef CLASSES_GF_GFMENUOBJSALVAGE_H
#define CLASSES_GF_GFMENUOBJSALVAGE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B645F8
class GfMenuObjSalvage : public ::gf::GfMenuObject {
public:
    class ResultListener;
    virtual ~GfMenuObjSalvage();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
