#ifndef CLASSES_GF_GFMENUOBJEXPGET_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJEXPGET_LISTLISTENER_H

#include "classes/gf/GfMenuObjExpGet.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62258
class GfMenuObjExpGet::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
