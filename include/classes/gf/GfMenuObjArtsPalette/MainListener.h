#ifndef CLASSES_GF_GFMENUOBJARTSPALETTE_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJARTSPALETTE_MAINLISTENER_H

#include "classes/gf/GfMenuObjArtsPalette.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5FB40
class GfMenuObjArtsPalette::MainListener : public ::ui::UIObjectListener {
public:
    // initialize zeroes 0xC-0x1B after storing its table: its own fields
    MainListener(GfMenuObjArtsPalette* owner) : pad_0C(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjArtsPalette* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
