#ifndef CLASSES_GF_GFMENUOBJSALVAGE_RESULTLISTENER_H
#define CLASSES_GF_GFMENUOBJSALVAGE_RESULTLISTENER_H

#include "classes/gf/GfMenuObjSalvage.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B64678
class GfMenuObjSalvage::ResultListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes) with the menu object as its owner
    ResultListener(GfMenuObjSalvage* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ResultListener() {}  // slot 0: the base's in the table (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    union {
        int m_ctrlSlot;  // 0x0C: set to -1 by event 1 (the name is not the original's)
        unsigned char pad_0C[0x10];
    };
    GfMenuObjSalvage* m_owner;
};
}  // namespace gf

#endif
