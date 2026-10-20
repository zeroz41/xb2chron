#ifndef CLASSES_GF_GFMENUOBJMAINSUBMENU_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJMAINSUBMENU_LISTLISTENER_H

#include "classes/gf/GfMenuObjMainSubmenu.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63328
class GfMenuObjMainSubmenu::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
