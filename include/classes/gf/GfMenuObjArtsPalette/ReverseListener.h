#ifndef CLASSES_GF_GFMENUOBJARTSPALETTE_REVERSELISTENER_H
#define CLASSES_GF_GFMENUOBJARTSPALETTE_REVERSELISTENER_H

#include "classes/gf/GfMenuObjArtsPalette.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5FB68
class GfMenuObjArtsPalette::ReverseListener : public ::ui::UIObjectListener {
public:
    // initialize zeroes 0xC-0x1B after storing its table: its own fields
    ReverseListener(GfMenuObjArtsPalette* owner) : m_count(0), pad_10(), m_owner(owner) {}
    virtual ~ReverseListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_count;  // its reverse icons (LAY_reverse_icon@NN), counted at its event 1 (the name is not the original's)
    unsigned char pad_10[0xC];
    GfMenuObjArtsPalette* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
