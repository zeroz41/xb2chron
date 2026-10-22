#ifndef CLASSES_GF_GFMENUOBJTUTORIAL_H
#define CLASSES_GF_GFMENUOBJTUTORIAL_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64E48
class GfMenuObjTutorial : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjTutorial();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static bool isWaiting();
};
}  // namespace gf

#endif
