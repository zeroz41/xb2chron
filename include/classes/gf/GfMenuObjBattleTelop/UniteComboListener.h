#ifndef CLASSES_GF_GFMENUOBJBATTLETELOP_UNITECOMBOLISTENER_H
#define CLASSES_GF_GFMENUOBJBATTLETELOP_UNITECOMBOLISTENER_H

#include "classes/gf/GfMenuObjBattleTelop.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5FD90
class GfMenuObjBattleTelop::UniteComboListener : public ::ui::UIObjectListener {
public:
    UniteComboListener(GfMenuObjBattleTelop* owner) : pad_0C(), m_owner(owner) {}
    virtual ~UniteComboListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // initialize zeroes 0xC-0x1B only (0x1C-0x1F is the owner pointer's alignment)
    GfMenuObjBattleTelop* m_owner;  // 0x20
};
}  // namespace gf

#endif
