#ifndef CLASSES_GF_GFMENUOBJMAINMENU2_CLOSELISTENER_H
#define CLASSES_GF_GFMENUOBJMAINMENU2_CLOSELISTENER_H

#include "classes/gf/GfMenuObjMainMenu2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B630A0
class GfMenuObjMainMenu2::CloseListener {
public:
    virtual ~CloseListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
