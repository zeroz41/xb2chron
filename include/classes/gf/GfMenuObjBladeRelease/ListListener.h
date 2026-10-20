#ifndef CLASSES_GF_GFMENUOBJBLADERELEASE_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADERELEASE_LISTLISTENER_H

#include "classes/gf/GfMenuObjBladeRelease.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B602C0
class GfMenuObjBladeRelease::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
