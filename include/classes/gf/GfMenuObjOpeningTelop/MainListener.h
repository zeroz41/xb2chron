#ifndef CLASSES_GF_GFMENUOBJOPENINGTELOP_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJOPENINGTELOP_MAINLISTENER_H

#include "classes/gf/GfMenuObjOpeningTelop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63C10
class GfMenuObjOpeningTelop::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
