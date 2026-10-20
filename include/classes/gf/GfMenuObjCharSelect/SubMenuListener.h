#ifndef CLASSES_GF_GFMENUOBJCHARSELECT_SUBMENULISTENER_H
#define CLASSES_GF_GFMENUOBJCHARSELECT_SUBMENULISTENER_H

#include "classes/gf/GfMenuObjCharSelect.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61060
class GfMenuObjCharSelect::SubMenuListener {
public:
    virtual ~SubMenuListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
