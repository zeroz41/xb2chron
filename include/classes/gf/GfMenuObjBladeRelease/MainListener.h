#ifndef CLASSES_GF_GFMENUOBJBLADERELEASE_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADERELEASE_MAINLISTENER_H

#include "classes/gf/GfMenuObjBladeRelease.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60298
class GfMenuObjBladeRelease::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
