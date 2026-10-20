#ifndef CLASSES_GF_GFMENUOBJHANAPARTSMAKE_NUMSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJHANAPARTSMAKE_NUMSELECTLISTENER_H

#include "classes/gf/GfMenuObjHanaPartsMake.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62970
class GfMenuObjHanaPartsMake::NumSelectListener {
public:
    virtual ~NumSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
