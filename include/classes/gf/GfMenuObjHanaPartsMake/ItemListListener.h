#ifndef CLASSES_GF_GFMENUOBJHANAPARTSMAKE_ITEMLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJHANAPARTSMAKE_ITEMLISTLISTENER_H

#include "classes/gf/GfMenuObjHanaPartsMake.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62948
class GfMenuObjHanaPartsMake::ItemListListener {
public:
    virtual ~ItemListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
