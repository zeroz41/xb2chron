#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_RESULTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_RESULTLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60138
class GfMenuObjBladeCreate::ResultListener {
public:
    virtual ~ResultListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
