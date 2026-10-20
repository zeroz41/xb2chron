#ifndef CLASSES_GF_GFMENUOBJHANASUBMENU_SUBMENULISTENER_H
#define CLASSES_GF_GFMENUOBJHANASUBMENU_SUBMENULISTENER_H

#include "classes/gf/GfMenuObjHanaSubmenu.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62A08
class GfMenuObjHanaSubmenu::SubmenuListener {
public:
    virtual ~SubmenuListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
