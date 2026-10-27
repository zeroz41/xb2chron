#ifndef CLASSES_GF_GFMENUOBJPARTYSTATUS_COMBOREQLISTENER_H
#define CLASSES_GF_GFMENUOBJPARTYSTATUS_COMBOREQLISTENER_H

#include "classes/gf/GfMenuObjPartyStatus.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {

// table 0x7100B64060: initialize makes it for "LAY_combo_req2"
class GfMenuObjPartyStatus::ComboReqListener : public ::ui::UIObjectListener {
public:
    // its state: a 4-aligned aggregate at 0xC that initialize zeroes after storing the table (the names are not the
    // original's)
    struct State {
        int m_value;            // event 1 sets it to -1
        unsigned int m_open;    // a bit per request slot that is open
        unsigned char pad_8[0x8];
    };
    ComboReqListener(GfMenuObjPartyStatus* owner) : m_state(), m_owner(owner) {}
    virtual ~ComboReqListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2

    State m_state;
    GfMenuObjPartyStatus* m_owner;
};

}  // namespace gf

#endif
