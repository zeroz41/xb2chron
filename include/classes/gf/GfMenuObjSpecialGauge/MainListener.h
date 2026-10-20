#ifndef CLASSES_GF_GFMENUOBJSPECIALGAUGE_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJSPECIALGAUGE_MAINLISTENER_H

#include "classes/gf/GfMenuObjSpecialGauge.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64AB0
class GfMenuObjSpecialGauge::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
