#ifndef CLASSES_GF_GFMENUOBJENBOOK_INDEXLISTENER_H
#define CLASSES_GF_GFMENUOBJENBOOK_INDEXLISTENER_H

#include "classes/gf/GfMenuObjEnBook.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61E70
class GfMenuObjEnBook::IndexListener {
public:
    virtual ~IndexListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
