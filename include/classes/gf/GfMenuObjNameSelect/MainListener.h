#ifndef CLASSES_GF_GFMENUOBJNAMESELECT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJNAMESELECT_MAINLISTENER_H

#include "classes/gf/GfMenuObjNameSelect.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63A20
class GfMenuObjNameSelect::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
