#ifndef CLASSES_GF_GFMENUOBJCHARSELECT_CHARBLMOVELISTENER_H
#define CLASSES_GF_GFMENUOBJCHARSELECT_CHARBLMOVELISTENER_H

#include "classes/gf/GfMenuObjCharSelect.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61100
class GfMenuObjCharSelect::CharBlMoveListener {
public:
    virtual ~CharBlMoveListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
