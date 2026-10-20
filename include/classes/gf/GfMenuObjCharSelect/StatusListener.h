#ifndef CLASSES_GF_GFMENUOBJCHARSELECT_STATUSLISTENER_H
#define CLASSES_GF_GFMENUOBJCHARSELECT_STATUSLISTENER_H

#include "classes/gf/GfMenuObjCharSelect.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B610B0
class GfMenuObjCharSelect::StatusListener {
public:
    virtual ~StatusListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
