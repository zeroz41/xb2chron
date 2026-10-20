#ifndef CLASSES_GF_GFMENUOBJBLADEBOOK_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADEBOOK_LISTLISTENER_H

#include "classes/gf/GfMenuObjBladeBook.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B5FE28
class GfMenuObjBladeBook::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
