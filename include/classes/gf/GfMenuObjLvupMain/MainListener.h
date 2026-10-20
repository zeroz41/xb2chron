#ifndef CLASSES_GF_GFMENUOBJLVUPMAIN_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJLVUPMAIN_MAINLISTENER_H

#include "classes/gf/GfMenuObjLvupMain.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62E80
class GfMenuObjLvupMain::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
