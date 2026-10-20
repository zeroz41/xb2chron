#ifndef CLASSES_GF_GFMENUOBJHANAPARTSMAKE_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJHANAPARTSMAKE_MAINLISTENER_H

#include "classes/gf/GfMenuObjHanaPartsMake.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B628F8
class GfMenuObjHanaPartsMake::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
