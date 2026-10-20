#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_BOOSTERSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_BOOSTERSELECTLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B600C0
class GfMenuObjBladeCreate::BoosterSelectListener {
public:
    virtual ~BoosterSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
