#ifndef CLASSES_GF_GFMENUOBJDRKIZUNARING_RINGPADLISTENER_H
#define CLASSES_GF_GFMENUOBJDRKIZUNARING_RINGPADLISTENER_H

#include "classes/gf/GfMenuObjDrKizunaRing.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61BE8
class GfMenuObjDrKizunaRing::RingPadListener {
public:
    virtual ~RingPadListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
