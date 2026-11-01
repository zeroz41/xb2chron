#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_FORMLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_FORMLISTENER_H

#include "classes/gf/GfMenuObjMercenaryForm.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B633C0
class GfMenuObjMercenaryForm::FormListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    FormListener(GfMenuObjMercenaryForm* owner) : pad_0C(), pad_10(), pad_14(), m_owner(owner) {}
    virtual ~FormListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int pad_0C;  // zeroed with pad_10 when it opens (event 1)
    int pad_10;
    unsigned char pad_14[8];
    GfMenuObjMercenaryForm* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
