#ifndef CLASSES_GF_GFMENUOBJBLADESET2_BLADELISTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADESET2_BLADELISTLISTENER_H

#include "classes/gf/GfMenuObjBladeSet2.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60398
class GfMenuObjBladeSet2::BladeListListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    BladeListListener(GfMenuObjBladeSet2* owner) : pad_0C(), m_owner(owner) {}
    virtual ~BladeListListener() {}  // slot 0: weak; its D0 folds into MainListener's
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjBladeSet2* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
