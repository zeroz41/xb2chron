#ifndef CLASSES_GF_GFMENUOBJTARGETCURSOR_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJTARGETCURSOR_MAINLISTENER_H

#include "classes/gf/GfMenuObjTargetCursor.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64BB0
class GfMenuObjTargetCursor::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
