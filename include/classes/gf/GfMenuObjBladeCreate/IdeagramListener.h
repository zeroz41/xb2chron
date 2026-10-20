#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_IDEAGRAMLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_IDEAGRAMLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60160
class GfMenuObjBladeCreate::IdeagramListener {
public:
    virtual ~IdeagramListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
