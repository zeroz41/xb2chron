#ifndef CLASSES_GF_GFMENUOBJMINIMAP2_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJMINIMAP2_MAINLISTENER_H

#include "classes/gf/GfMenuObjMinimap2.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B637C8
class GfMenuObjMinimap2::MainListener : public ::ui::UIObjectListener {
public:
    // its state: a 4-aligned aggregate at 0xC (event 1 stores 0x10-0x17 as one 8-byte store, which fields of the
    // listener itself would merge with 0xC instead, as GfMenuObjEnvironmentInfo::ListListener's); the names are not
    // the original's
    struct State {
        int m_open;      // 1 while faded in: open (0x21) fades in, close (0x22) out
        int m_ctrlSlot;  // the slot of its last fade
        int m_zoomMode;  // the zoom step event 8 (input 9) cycles through (0-3)
        int pad_0C;
    };
    MainListener(GfMenuObjMinimap2* owner) : m_state(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    State m_state;
    GfMenuObjMinimap2* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
