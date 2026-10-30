#ifndef CLASSES_GF_GFMENUOBJPARTYFORM3_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJPARTYFORM3_MAINLISTENER_H

#include "classes/gf/GfMenuObjPartyForm3.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63EC8
class GfMenuObjPartyForm3::MainListener : public ::ui::UIObjectListener {
public:
    MainListener(GfMenuObjPartyForm3* owner) : pad_C(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2

    unsigned int pad_C[4];  // zeroed by the constructor
    GfMenuObjPartyForm3* m_owner;
};
}  // namespace gf

#endif
