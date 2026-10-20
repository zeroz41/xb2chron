#ifndef CLASSES_GF_GFMENUOBJMAINSUBMENU_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJMAINSUBMENU_MAINLISTENER_H

#include "classes/gf/GfMenuObjMainSubmenu.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63300
class GfMenuObjMainSubmenu::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
