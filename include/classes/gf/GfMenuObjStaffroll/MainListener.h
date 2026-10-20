#ifndef CLASSES_GF_GFMENUOBJSTAFFROLL_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJSTAFFROLL_MAINLISTENER_H

#include "classes/gf/GfMenuObjStaffroll.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64B40
class GfMenuObjStaffroll::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
