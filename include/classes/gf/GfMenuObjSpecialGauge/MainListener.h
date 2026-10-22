#ifndef CLASSES_GF_GFMENUOBJSPECIALGAUGE_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJSPECIALGAUGE_MAINLISTENER_H

#include "classes/gf/GfMenuObjSpecialGauge.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B64AB0
class GfMenuObjSpecialGauge::MainListener : public ::ui::UIObjectListener {
public:
    // its state: a 4-aligned aggregate at 0xC (event 1 stores 0x10-0x17 as one 8-byte store, which fields of the
    // listener itself, 8-aligned at 0x10, would merge with 0xC instead); the names are not the original's
    struct State {
        int m_ctrl;     // the slot of its last fade (-1 for none)
        int m_open;     // open (0x100) in battle sets it, close (0x101) clears it
        int m_shown;    // 1 while faded in
        int m_enabled;  // event 1 sets it: open fades in only with it
    };
    MainListener(GfMenuObjSpecialGauge* owner) : m_state(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    State m_state;
    GfMenuObjSpecialGauge* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
