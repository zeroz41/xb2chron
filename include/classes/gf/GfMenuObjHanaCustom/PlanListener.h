#ifndef CLASSES_GF_GFMENUOBJHANACUSTOM_PLANLISTENER_H
#define CLASSES_GF_GFMENUOBJHANACUSTOM_PLANLISTENER_H

#include "classes/gf/GfMenuObjHanaCustom.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62760
class GfMenuObjHanaCustom::PlanListener {
public:
    virtual ~PlanListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
