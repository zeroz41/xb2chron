#ifndef CLASSES_GF_GFMENUOBJCHARSELECT_DETAILLISTENER_H
#define CLASSES_GF_GFMENUOBJCHARSELECT_DETAILLISTENER_H

#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B61088
class GfMenuObjCharSelect::DetailListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    DetailListener(GfMenuObjCharSelect* owner) : m_detailMode(0), pad_10(), m_owner(owner) {}
    virtual ~DetailListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // event 0x21's first parameter: which detail page is shown (sub index text 19 when set, 18 when not; event 8
    // with parameter 2 shows text 3 or 2 by it; event 1 clears it). The name is not the original's
    int m_detailMode;
    unsigned char pad_10[0xC];
    GfMenuObjCharSelect* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
