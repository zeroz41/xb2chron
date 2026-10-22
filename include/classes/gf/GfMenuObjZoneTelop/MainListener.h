#ifndef CLASSES_GF_GFMENUOBJZONETELOP_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJZONETELOP_MAINLISTENER_H

#include "classes/gf/GfMenuObjZoneTelop.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B651E0
class GfMenuObjZoneTelop::MainListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    MainListener(GfMenuObjZoneTelop* owner) : pad_0C(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjZoneTelop* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
