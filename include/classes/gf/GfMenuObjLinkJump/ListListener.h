#ifndef CLASSES_GF_GFMENUOBJLINKJUMP_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJLINKJUMP_LISTLISTENER_H

#include "classes/gf/GfMenuObjLinkJump.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62D30
class GfMenuObjLinkJump::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
