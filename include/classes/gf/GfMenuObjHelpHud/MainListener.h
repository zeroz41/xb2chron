#ifndef CLASSES_GF_GFMENUOBJHELPHUD_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJHELPHUD_MAINLISTENER_H

#include "classes/gf/GfMenuObjHelpHud.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62A78
class GfMenuObjHelpHud::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
