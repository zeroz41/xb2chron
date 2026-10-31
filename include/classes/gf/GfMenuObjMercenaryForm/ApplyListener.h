#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_APPLYLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_APPLYLISTENER_H

#include "classes/gf/GfMenuObjMercenaryForm.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63410
class GfMenuObjMercenaryForm::ApplyListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    ApplyListener(GfMenuObjMercenaryForm* owner) : m_open(), pad_10(), m_owner(owner) {}
    virtual ~ApplyListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_open;  // 1 once its open (0x21) ran, 0 after open (1) and close (0x22) (the name is not the original's)
    unsigned char pad_10[0xC];
    GfMenuObjMercenaryForm* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
