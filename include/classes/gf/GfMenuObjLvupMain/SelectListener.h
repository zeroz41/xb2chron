#ifndef CLASSES_GF_GFMENUOBJLVUPMAIN_SELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJLVUPMAIN_SELECTLISTENER_H

#include "classes/gf/GfMenuObjLvupMain.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62ED0
class GfMenuObjLvupMain::SelectListener {
public:
    virtual ~SelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
