#ifndef CLASSES_GF_GFMENUOBJENBOOK_ENLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJENBOOK_ENLISTLISTENER_H

#include "classes/gf/GfMenuObjEnBook.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61F10
class GfMenuObjEnBook::EnListListener {
public:
    virtual ~EnListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
