#ifndef CLASSES_GF_GFMENUOBJLOCATIONTELOP_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJLOCATIONTELOP_MAINLISTENER_H

#include "classes/gf/GfMenuObjLocationTelop.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62E10
class GfMenuObjLocationTelop::MainListener : public ::ui::UIObjectListener {
public:
    MainListener(GfMenuObjLocationTelop* owner) : m_state(0), m_time(), pad_18(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // 0 hidden, 1 shown (the open event, 0x100), 3 closing (0x101) (the name is not the original's)
    int m_state;
    // cleared as one 8-byte value when the object is made (the names are not the original's)
    struct Time {
        int m_time;   // the open event's m_param1 (open passes 200); nothing here reads it
        int m_count;  // cleared when it closes; nothing here reads it
    };
    Time m_time;
    unsigned char pad_18[4];
    GfMenuObjLocationTelop* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
