#ifndef CLASSES_GF_GFMENUOBJPARTYSTATUS2_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJPARTYSTATUS2_MAINLISTENER_H

#include "classes/gf/GfMenuObjPartyStatus2.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B640D0: initialize makes it for "LAY_main"
class GfMenuObjPartyStatus2::MainListener : public ::ui::UIObjectListener {
public:
    MainListener(GfMenuObjPartyStatus2* owner) : pad_C(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2

    unsigned int pad_C[4];  // zeroed by the constructor; nothing in the unit reads it
    GfMenuObjPartyStatus2* m_owner;
};
}  // namespace gf

#endif
