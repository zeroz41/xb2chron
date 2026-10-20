#ifndef CLASSES_GF_GFMENUOBJDAMAGEBUFF_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJDAMAGEBUFF_LISTLISTENER_H

#include "classes/gf/GfMenuObjDamageBuff.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B617A8
class GfMenuObjDamageBuff::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
