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
    MainListener(GfMenuObjArtsPalette* owner)
        : m_ctrlSlot(0), m_state(), pad_18(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // the field names are not the original's (reciveEvent's use of them)
    int m_ctrlSlot;   // the slot of the palette's fade control: event 1 sets -1, 0x100/0x101 the preset's
    struct State { int open; int infoDisp; } m_state;
    unsigned char pad_18[0x4];
    GfMenuObjArtsPalette* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
