#ifndef CLASSES_GF_GFMENUOBJBLKIZUNARING_RINGPADLISTENER_H
#define CLASSES_GF_GFMENUOBJBLKIZUNARING_RINGPADLISTENER_H

#include "classes/gf/GfMenuObjBlKizunaRing.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60590
class GfMenuObjBlKizunaRing::RingPadListener {
public:
    virtual ~RingPadListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
