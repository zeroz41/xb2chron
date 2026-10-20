#ifndef CLASSES_GF_GFMENUOBJCHARSELECT_CHARLISTENER_H
#define CLASSES_GF_GFMENUOBJCHARSELECT_CHARLISTENER_H

#include "classes/gf/GfMenuObjCharSelect.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61038
class GfMenuObjCharSelect::CharListener {
public:
    virtual ~CharListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
