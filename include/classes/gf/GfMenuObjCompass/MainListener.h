#ifndef CLASSES_GF_GFMENUOBJCOMPASS_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJCOMPASS_MAINLISTENER_H

#include "classes/gf/GfMenuObjCompass.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B616C8
class GfMenuObjCompass::MainListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table
    MainListener(GfMenuObjCompass* owner) : m_ctrl(0), m_state(), pad_18(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // the field names are not the original's
    int m_ctrl;       // the open (0x21) or close (0x22) fade's control slot; -1 after the init event (1)
    // an 8-byte aggregate: the init event (1) resets both with one 8-byte store before its FixStr's stores
    struct State {
        int m_frameCtrl;  // LAY_frame's colour control (event 0x101), -1 for none
        int m_open;       // 1 while open
    };
    State m_state;
    unsigned char pad_18[4];
    GfMenuObjCompass* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
