#ifndef CLASSES_GF_GFMENUOBJLVUPMAIN_MENULISTENER_H
#define CLASSES_GF_GFMENUOBJLVUPMAIN_MENULISTENER_H

#include "classes/gf/GfMenuObjLvupMain.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62EA8
class GfMenuObjLvupMain::MenuListener {
public:
    virtual ~MenuListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
