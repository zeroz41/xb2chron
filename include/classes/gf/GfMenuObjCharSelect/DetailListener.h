#ifndef CLASSES_GF_GFMENUOBJCHARSELECT_DETAILLISTENER_H
#define CLASSES_GF_GFMENUOBJCHARSELECT_DETAILLISTENER_H

#include "classes/gf/GfMenuObjCharSelect.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61088
class GfMenuObjCharSelect::DetailListener {
public:
    virtual ~DetailListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
