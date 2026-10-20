#ifndef CLASSES_GF_GFMENUOBJELEMENTEFF_H
#define CLASSES_GF_GFMENUOBJELEMENTEFF_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61C60
class GfMenuObjElementEff : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjElementEff();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
