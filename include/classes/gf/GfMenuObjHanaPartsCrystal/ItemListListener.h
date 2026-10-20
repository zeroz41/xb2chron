#ifndef CLASSES_GF_GFMENUOBJHANAPARTSCRYSTAL_ITEMLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJHANAPARTSCRYSTAL_ITEMLISTLISTENER_H

#include "classes/gf/GfMenuObjHanaPartsCrystal.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62860
class GfMenuObjHanaPartsCrystal::ItemListListener {
public:
    virtual ~ItemListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
