#ifndef CLASSES_GF_GFMENUOBJMAINMENU2_INDEXLISTENER_H
#define CLASSES_GF_GFMENUOBJMAINMENU2_INDEXLISTENER_H

#include "classes/gf/GfMenuObjMainMenu2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63050
class GfMenuObjMainMenu2::IndexListener {
public:
    virtual ~IndexListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
