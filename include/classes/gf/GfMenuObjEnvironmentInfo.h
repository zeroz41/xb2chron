#ifndef CLASSES_GF_GFMENUOBJENVIRONMENTINFO_H
#define CLASSES_GF_GFMENUOBJENVIRONMENTINFO_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61D68
class GfMenuObjEnvironmentInfo : public ::gf::GfMenuObject {
public:
    class ListListener;
    virtual ~GfMenuObjEnvironmentInfo();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
