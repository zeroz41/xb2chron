#ifndef CLASSES_GF_GFMENUOBJCHAPTERTELOP_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJCHAPTERTELOP_LISTLISTENER_H

#include "classes/gf/GfMenuObjChapterTelop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60E00
class GfMenuObjChapterTelop::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
