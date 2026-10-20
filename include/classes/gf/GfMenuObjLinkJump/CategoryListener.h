#ifndef CLASSES_GF_GFMENUOBJLINKJUMP_CATEGORYLISTENER_H
#define CLASSES_GF_GFMENUOBJLINKJUMP_CATEGORYLISTENER_H

#include "classes/gf/GfMenuObjLinkJump.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62CE0
class GfMenuObjLinkJump::CategoryListener {
public:
    virtual ~CategoryListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
