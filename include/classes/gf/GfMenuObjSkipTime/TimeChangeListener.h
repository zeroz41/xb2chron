#ifndef CLASSES_GF_GFMENUOBJSKIPTIME_TIMECHANGELISTENER_H
#define CLASSES_GF_GFMENUOBJSKIPTIME_TIMECHANGELISTENER_H

#include "classes/gf/GfMenuObjSkipTime.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B649D0
class GfMenuObjSkipTime::TimeChangeListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    TimeChangeListener(GfMenuObjSkipTime* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TimeChangeListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjSkipTime* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
