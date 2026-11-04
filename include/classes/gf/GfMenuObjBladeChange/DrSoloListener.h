#ifndef CLASSES_GF_GFMENUOBJBLADECHANGE_DRSOLOLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECHANGE_DRSOLOLISTENER_H

#include "classes/gf/GfMenuObjBladeChange.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5FEE8 (no RTTI; 2.0.0's symbols name it): a listener new in 3.0.1. GfMenuObjBladeChange::initialize
// news it (0x28 bytes) for its "LAY_dr_solo" object; it fades LAY_btl_mode_solo in and out (events 0x21/0x22) and
// shows the solo battle mode's texts and push animation on event 0x105. Its D1 slot is the base's destructor.
class GfMenuObjBladeChange::DrSoloListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table, then stores the owner
    DrSoloListener(GfMenuObjBladeChange* owner) : m_ctrlSlot(0), pad_10(), m_owner(owner) {}
    virtual ~DrSoloListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    // LAY_btl_mode_solo's fade control: startPresetCtrl's slot, -1 after event 1 (the name is not the original's)
    int m_ctrlSlot;
    unsigned char pad_10[0xC];
    GfMenuObjBladeChange* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
