#ifndef CLASSES_GF_GFMENUOBJARTSPALETTE_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJARTSPALETTE_MAINLISTENER_H

#include "classes/gf/GfMenuObjArtsPalette.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B5FB40
class GfMenuObjArtsPalette::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
