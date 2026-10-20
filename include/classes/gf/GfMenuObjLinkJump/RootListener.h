#ifndef CLASSES_GF_GFMENUOBJLINKJUMP_ROOTLISTENER_H
#define CLASSES_GF_GFMENUOBJLINKJUMP_ROOTLISTENER_H

#include "classes/gf/GfMenuObjLinkJump.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62CB8
class GfMenuObjLinkJump::RootListener {
public:
    virtual ~RootListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
