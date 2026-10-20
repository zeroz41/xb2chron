#ifndef CLASSES_GF_GFMENUOBJEVTHEATER_H
#define CLASSES_GF_GFMENUOBJEVTHEATER_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62040
class GfMenuObjEvTheater : public ::gf::GfMenuObject {
public:
    class HeaderListener;
    virtual ~GfMenuObjEvTheater();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
