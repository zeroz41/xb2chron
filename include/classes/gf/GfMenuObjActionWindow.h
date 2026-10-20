#ifndef CLASSES_GF_GFMENUOBJACTIONWINDOW_H
#define CLASSES_GF_GFMENUOBJACTIONWINDOW_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B5F978
class GfMenuObjActionWindow : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjActionWindow();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    virtual void eventHudSceneChange(unsigned int);  // slot 6
};
}  // namespace gf

#endif
