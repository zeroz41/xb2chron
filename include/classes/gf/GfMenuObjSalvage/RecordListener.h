#ifndef CLASSES_GF_GFMENUOBJSALVAGE_TUNK_B646A0_H
#define CLASSES_GF_GFMENUOBJSALVAGE_TUNK_B646A0_H

#include "classes/gf/GfMenuObjSalvage.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B646A0: no RTTI or 1.0.0 symbol names it (new in 3.0.1). GfMenuObjSalvage::initialize registers it on
// LAY_record: a battle challenge record listener, by its layout (the suggestion is not a name).
class GfMenuObjSalvage::RecordListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes) with the menu object as its owner
    RecordListener(GfMenuObjSalvage* owner) : pad_0C(), m_owner(owner) {}
    virtual ~RecordListener() {}  // slot 0: the base's in the table (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjSalvage* m_owner;
};
}  // namespace gf

#endif
