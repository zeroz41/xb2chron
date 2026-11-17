#ifndef CLASSES_GF_GFMENUOBJBATTLETELOP_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJBATTLETELOP_MAINLISTENER_H

#include "classes/gf/GfMenuObjBattleTelop.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5FD68
// the field names below are not the original's (from reciveEvent)
class GfMenuObjBattleTelop::MainListener : public ::ui::UIObjectListener {
public:
    MainListener(GfMenuObjBattleTelop* owner) : m_ctrl(0), m_state(), pad_18(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // inline (no copy in the original), reciveEvent's: the telop fade (PresetCtrlParam preset 1, m_startFlag4, slot
    // m_ctrl) in (0) or out (1) with that event id, and the close event (0x22) to the LAY_telop child of the object
    // GfMenuObject::getAttachedObject gives for that id (when there is one). The names are not the original's
    static int startFade(unsigned int handle, int slot, unsigned int out, int eventId);
    static void closeAttachedTelop(unsigned int id);
    int m_ctrl;       // 0xC: the fade-in control (-1: none); its slot for the fade-out
    // reset as one (event 1 zeroes both with one 8-byte store, apart from m_ctrl's)
    struct State {
        int m_active;  // 1 while a telop is open (0x21 to 0x22)
        int m_shown;   // 1 after the fade-in started, until the fade-out
    };
    State m_state;    // 0x10
    unsigned char pad_18[4];  // initialize zeroes 0xC-0x1B only (0x1C-0x1F is the owner pointer's alignment)
    GfMenuObjBattleTelop* m_owner;  // 0x20
};
}  // namespace gf

#endif
