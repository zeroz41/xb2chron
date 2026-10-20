#ifndef CLASSES_GF_GFMENUOBJOPTION_SUBMENULISTENER_H
#define CLASSES_GF_GFMENUOBJOPTION_SUBMENULISTENER_H

#include "classes/gf/GfMenuObjOption.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63D18
class GfMenuObjOption::SubMenuListener {
public:
    virtual ~SubMenuListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
