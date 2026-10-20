#ifndef CLASSES_GF_GFMENUOBJELEMENTEFF_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJELEMENTEFF_MAINLISTENER_H

#include "classes/gf/GfMenuObjElementEff.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61CA8
class GfMenuObjElementEff::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
