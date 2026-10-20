#ifndef CLASSES_GF_GFMENUOBJPARTYGAUGE_GAUGELISTENER_H
#define CLASSES_GF_GFMENUOBJPARTYGAUGE_GAUGELISTENER_H

#include "classes/gf/GfMenuObjPartyGauge.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63FA0
class GfMenuObjPartyGauge::GaugeListener {
public:
    virtual ~GaugeListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
