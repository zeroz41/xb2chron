#ifndef CLASSES_GF_GFMENUOBJOPTION_SUBMENULISTENER_H
#define CLASSES_GF_GFMENUOBJOPTION_SUBMENULISTENER_H

#include "classes/gf/GfMenuObjOption.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63D18
class GfMenuObjOption::SubMenuListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes) with the menu object as its owner
    SubMenuListener(GfMenuObjOption* owner) : pad_0C(), m_owner(owner) {}
    virtual ~SubMenuListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjOption* m_owner;
};
}  // namespace gf

#endif
