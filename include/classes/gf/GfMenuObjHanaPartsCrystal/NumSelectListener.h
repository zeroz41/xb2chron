#ifndef CLASSES_GF_GFMENUOBJHANAPARTSCRYSTAL_NUMSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJHANAPARTSCRYSTAL_NUMSELECTLISTENER_H

#include "classes/gf/GfMenuObjHanaPartsCrystal.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62888
class GfMenuObjHanaPartsCrystal::NumSelectListener {
public:
    virtual ~NumSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
