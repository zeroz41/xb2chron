#ifndef CLASSES_GF_GFMENUOBJOPTION_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJOPTION_MAINLISTENER_H

#include "classes/gf/GfMenuObjOption.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63CF0
class GfMenuObjOption::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
