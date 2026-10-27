#ifndef CLASSES_GF_GFMENUOBJPARTYSTATUS_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJPARTYSTATUS_MAINLISTENER_H

#include "classes/gf/GfMenuObjPartyStatus.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {

// table 0x7100B64038: initialize makes it for "LAY_main"
class GfMenuObjPartyStatus::MainListener : public ::ui::UIObjectListener {
public:
    // its state: a 4-aligned aggregate at 0xC that initialize zeroes after storing the table (the names are not the
    // original's)
    struct State {
        int m_value;            // what openPartyStatus is given and returns (event 1 sets it to -1)
        unsigned int m_flags;   // open (0x21) sets bit 0 (and bit 1 with parameter 1), close (0x22) bit 2
        int m_open;             // 1 while the party status is open
        unsigned int m_members; // a bit per member (1 << member) that keeps it open
    };
    MainListener(GfMenuObjPartyStatus* owner) : m_state(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2

    State m_state;
    GfMenuObjPartyStatus* m_owner;
};

}  // namespace gf

#endif
