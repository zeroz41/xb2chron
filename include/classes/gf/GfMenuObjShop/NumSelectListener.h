#ifndef CLASSES_GF_GFMENUOBJSHOP_NUMSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_NUMSELECTLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B648C0
class GfMenuObjShop::NumSelectListener {
public:
    virtual ~NumSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
