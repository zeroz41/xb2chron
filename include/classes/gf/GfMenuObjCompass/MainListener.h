#ifndef CLASSES_GF_GFMENUOBJCOMPASS_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJCOMPASS_MAINLISTENER_H

#include "classes/gf/GfMenuObjCompass.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B616C8
class GfMenuObjCompass::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
