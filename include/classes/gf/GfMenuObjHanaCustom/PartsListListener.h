#ifndef CLASSES_GF_GFMENUOBJHANACUSTOM_PARTSLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJHANACUSTOM_PARTSLISTLISTENER_H

#include "classes/gf/GfMenuObjHanaCustom.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62710
class GfMenuObjHanaCustom::PartsListListener {
public:
    virtual ~PartsListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
