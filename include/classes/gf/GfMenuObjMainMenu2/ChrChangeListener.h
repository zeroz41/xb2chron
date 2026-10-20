#ifndef CLASSES_GF_GFMENUOBJMAINMENU2_CHRCHANGELISTENER_H
#define CLASSES_GF_GFMENUOBJMAINMENU2_CHRCHANGELISTENER_H

#include "classes/gf/GfMenuObjMainMenu2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63078
class GfMenuObjMainMenu2::ChrChangeListener {
public:
    virtual ~ChrChangeListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
