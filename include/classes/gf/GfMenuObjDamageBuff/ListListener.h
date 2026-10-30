#ifndef CLASSES_GF_GFMENUOBJDAMAGEBUFF_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJDAMAGEBUFF_LISTLISTENER_H

#include "classes/gf/GfMenuObjDamageBuff.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B617A8
class GfMenuObjDamageBuff::ListListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    ListListener(GfMenuObjDamageBuff* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjDamageBuff* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
