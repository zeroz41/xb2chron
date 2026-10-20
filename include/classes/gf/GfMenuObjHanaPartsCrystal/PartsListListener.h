#ifndef CLASSES_GF_GFMENUOBJHANAPARTSCRYSTAL_PARTSLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJHANAPARTSCRYSTAL_PARTSLISTLISTENER_H

#include "classes/gf/GfMenuObjHanaPartsCrystal.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62838
class GfMenuObjHanaPartsCrystal::PartsListListener {
public:
    virtual ~PartsListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
