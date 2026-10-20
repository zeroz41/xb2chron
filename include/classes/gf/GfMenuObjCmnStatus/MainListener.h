#ifndef CLASSES_GF_GFMENUOBJCMNSTATUS_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJCMNSTATUS_MAINLISTENER_H

#include "classes/gf/GfMenuObjCmnStatus.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61310
class GfMenuObjCmnStatus::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
