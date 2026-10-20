#ifndef CLASSES_GF_GFMENUOBJZONETELOP_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJZONETELOP_MAINLISTENER_H

#include "classes/gf/GfMenuObjZoneTelop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B651E0
class GfMenuObjZoneTelop::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
