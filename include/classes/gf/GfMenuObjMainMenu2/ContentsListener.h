#ifndef CLASSES_GF_GFMENUOBJMAINMENU2_CONTENTSLISTENER_H
#define CLASSES_GF_GFMENUOBJMAINMENU2_CONTENTSLISTENER_H

#include "classes/gf/GfMenuObjMainMenu2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63028
class GfMenuObjMainMenu2::ContentsListener {
public:
    virtual ~ContentsListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
