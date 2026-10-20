#ifndef CLASSES_GF_GFMENUOBJARTSPALETTE_REVERSELISTENER_H
#define CLASSES_GF_GFMENUOBJARTSPALETTE_REVERSELISTENER_H

#include "classes/gf/GfMenuObjArtsPalette.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B5FB68
class GfMenuObjArtsPalette::ReverseListener {
public:
    virtual ~ReverseListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
