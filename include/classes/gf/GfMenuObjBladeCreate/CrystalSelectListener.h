#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_CRYSTALSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_CRYSTALSELECTLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60098
class GfMenuObjBladeCreate::CrystalSelectListener {
public:
    virtual ~CrystalSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
