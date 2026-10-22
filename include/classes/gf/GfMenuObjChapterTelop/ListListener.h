#ifndef CLASSES_GF_GFMENUOBJCHAPTERTELOP_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJCHAPTERTELOP_LISTLISTENER_H

#include "classes/gf/GfMenuObjChapterTelop.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60E00
class GfMenuObjChapterTelop::ListListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table
    ListListener(GfMenuObjChapterTelop* owner) : m_chapter(0), m_phase(0), pad_14(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_chapter;  // the open event's (0x21) chapter (the name is not the original's)
    // 1: the next animation end (0xC) fades IMG_end_telop out, 0: an animation or control end (3) closes the telop.
    // Nothing in 3.0.1 sets 1 (the name is not the original's)
    int m_phase;
    unsigned char pad_14[8];
    GfMenuObjChapterTelop* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
