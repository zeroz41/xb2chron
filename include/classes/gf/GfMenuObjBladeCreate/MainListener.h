#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_MAINLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60048
class GfMenuObjBladeCreate::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
