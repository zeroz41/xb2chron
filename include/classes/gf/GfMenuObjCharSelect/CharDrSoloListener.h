#ifndef CLASSES_GF_GFMENUOBJCHARSELECT_CHARDRSOLOLISTENER_H
#define CLASSES_GF_GFMENUOBJCHARSELECT_CHARDRSOLOLISTENER_H

#include "classes/gf/GfMenuObjCharSelect.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61150
class GfMenuObjCharSelect::CharDrSoloListener {
public:
    virtual ~CharDrSoloListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
