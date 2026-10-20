#ifndef CLASSES_GF_GFMENUOBJDRKIZUNARING_RINGLISTENER_H
#define CLASSES_GF_GFMENUOBJDRKIZUNARING_RINGLISTENER_H

#include "classes/gf/GfMenuObjDrKizunaRing.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61BC0
class GfMenuObjDrKizunaRing::RingListener {
public:
    virtual ~RingListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
