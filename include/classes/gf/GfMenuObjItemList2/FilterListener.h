#ifndef CLASSES_GF_GFMENUOBJITEMLIST2_FILTERLISTENER_H
#define CLASSES_GF_GFMENUOBJITEMLIST2_FILTERLISTENER_H

#include "classes/gf/GfMenuObjItemList2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62C48
class GfMenuObjItemList2::FilterListener {
public:
    virtual ~FilterListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
