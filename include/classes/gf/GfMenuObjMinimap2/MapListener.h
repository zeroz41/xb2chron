#ifndef CLASSES_GF_GFMENUOBJMINIMAP2_MAPLISTENER_H
#define CLASSES_GF_GFMENUOBJMINIMAP2_MAPLISTENER_H

#include "classes/gf/GfMenuObjMinimap2.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B637F0
class GfMenuObjMinimap2::MapListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table
    MapListener(GfMenuObjMinimap2* owner) : pad_0C(), m_owner(owner) {}
    virtual ~MapListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjMinimap2* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
