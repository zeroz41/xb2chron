#ifndef CLASSES_GF_GFMENUOBJENBOOK_GENUSSELLISTENER_H
#define CLASSES_GF_GFMENUOBJENBOOK_GENUSSELLISTENER_H

#include "classes/gf/GfMenuObjEnBook.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61EC0
class GfMenuObjEnBook::GenusSelListener {
public:
    virtual ~GenusSelListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
