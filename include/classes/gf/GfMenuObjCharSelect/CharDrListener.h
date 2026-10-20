#ifndef CLASSES_GF_GFMENUOBJCHARSELECT_CHARDRLISTENER_H
#define CLASSES_GF_GFMENUOBJCHARSELECT_CHARDRLISTENER_H

#include "classes/gf/GfMenuObjCharSelect.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B610D8
class GfMenuObjCharSelect::CharDrListener {
public:
    virtual ~CharDrListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
