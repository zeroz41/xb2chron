#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_LISTLISTENER_H

#include "classes/gf/GfMenuObjMercenaryForm.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63438
class GfMenuObjMercenaryForm::ListListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    ListListener(GfMenuObjMercenaryForm* owner) : m_index(0), pad_10(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // the blade list's selected index (inferred name): event 6 stores the new one, event 1 sets -1, event 0x21
    // restores the selection from it and the sort event (0x148) reselects it
    int m_index;
    unsigned char pad_10[0xC];
    GfMenuObjMercenaryForm* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
