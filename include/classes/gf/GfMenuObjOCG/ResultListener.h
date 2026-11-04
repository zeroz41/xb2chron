#ifndef CLASSES_GF_TUNK_B63AE0_TUNK_B63B50_H
#define CLASSES_GF_TUNK_B63AE0_TUNK_B63B50_H

#include "classes/gf/GfMenuObjOCG.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63B50: LAY_result's listener (initialize registers it on LAY_result); nothing names it (no 1.0.0 class, no symbol)
class GfMenuObjOCG::ResultListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    ResultListener(GfMenuObjOCG* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ResultListener() {}  // slot 0: its D1 slot is the base's destructor; its D0 is in the unit's tail
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjOCG* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
