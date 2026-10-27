#ifndef CLASSES_GF_GFMENUOBJTARGETCURSOR_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJTARGETCURSOR_MAINLISTENER_H

#include "classes/gf/GfMenuObjTargetCursor.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B64BB0
class GfMenuObjTargetCursor::MainListener : public ::ui::UIObjectListener {
public:
    // its state: a 4-aligned aggregate at 0xC the constructor zeroes (the names are not the original's)
    struct State {
        int m_open;  // 1 while open (event 0x100 sets it, 0x101 and 1 clear it)
        unsigned char pad_10[0xC];
    };
    MainListener(GfMenuObjTargetCursor* owner) : m_state(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    State m_state;
    GfMenuObjTargetCursor* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
