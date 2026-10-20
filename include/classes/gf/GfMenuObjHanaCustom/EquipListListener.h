#ifndef CLASSES_GF_GFMENUOBJHANACUSTOM_EQUIPLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJHANACUSTOM_EQUIPLISTLISTENER_H

#include "classes/gf/GfMenuObjHanaCustom.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62788
class GfMenuObjHanaCustom::EquipListListener {
public:
    virtual ~EquipListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
