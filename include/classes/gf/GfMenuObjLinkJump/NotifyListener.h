#ifndef CLASSES_GF_GFMENUOBJLINKJUMP_NOTIFYLISTENER_H
#define CLASSES_GF_GFMENUOBJLINKJUMP_NOTIFYLISTENER_H

#include "classes/gf/GfMenuObjLinkJump.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62D08
class GfMenuObjLinkJump::NotifyListener {
public:
    virtual ~NotifyListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
