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
    virtual ~MainListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_ctrl;       // 0xC: the fade-in control (-1: none); its slot for the fade-out
    int m_active;     // 0x10: 1 while a telop is open (0x21 to 0x22)
    int m_shown;      // 0x14: 1 after the fade-in started, until the fade-out
    unsigned char pad_18[8];
    GfMenuObjBattleTelop* m_owner;  // 0x20
};
}  // namespace gf

#endif
