#ifndef CLASSES_GF_GFMENUOBJPOUCH2_FILTERLISTENER2_H
#define CLASSES_GF_GFMENUOBJPOUCH2_FILTERLISTENER2_H

#include "classes/gf/GfMenuObjPouch2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B642A0
class GfMenuObjPouch2::FilterListener2 {
public:
    virtual ~FilterListener2();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
