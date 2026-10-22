#ifndef CLASSES_GF_GFMENUOBJEVENTSKIP_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJEVENTSKIP_LISTLISTENER_H

#include "classes/gf/GfMenuObjEventSkip.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B61FA8
class GfMenuObjEventSkip::ListListener : public ::ui::UIObjectListener {
public:
    ListListener(GfMenuObjEventSkip* owner) : m_pauseShown(0), pad_10(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0: weak, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // 1 while LAY_pause is shown: each end of its fade (event 3) fades it the other way and flips this
    // (the name is not the original's)
    int m_pauseShown;
    unsigned char pad_10[0xC];
    GfMenuObjEventSkip* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
