#ifndef CLASSES_GF_GFMENUOBJSALVAGE_RESULTLISTENER_H
#define CLASSES_GF_GFMENUOBJSALVAGE_RESULTLISTENER_H

#include "classes/gf/GfMenuObjSalvage.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64678
class GfMenuObjSalvage::ResultListener {
public:
    virtual ~ResultListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
