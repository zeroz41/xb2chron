#ifndef CLASSES_GF_GFMENUOBJDRARTSSET2_ARTSLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJDRARTSSET2_ARTSLISTLISTENER_H

#include "classes/gf/GfMenuObjDrArtsSet2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61A10
class GfMenuObjDrArtsSet2::ArtsListListener {
public:
    virtual ~ArtsListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
