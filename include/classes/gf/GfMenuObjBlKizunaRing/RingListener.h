#ifndef CLASSES_GF_GFMENUOBJBLKIZUNARING_RINGLISTENER_H
#define CLASSES_GF_GFMENUOBJBLKIZUNARING_RINGLISTENER_H

#include "classes/gf/GfMenuObjBlKizunaRing.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60568
class GfMenuObjBlKizunaRing::RingListener {
public:
    virtual ~RingListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
