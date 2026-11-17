#ifndef CLASSES_GF_GFMENUOBJCOMMONTEXT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJCOMMONTEXT_MAINLISTENER_H

#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B614C0
class GfMenuObjCommonText::MainListener : public ::ui::UIObjectListener {
public:
    MainListener(GfMenuObjCommonText* owner) : m_savedLayer(0), m_kind(0), pad_14(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    // ui::UIInputManager's m_minimumLayerHandle while no dialog was open: the open event (0x21) saves it before raising
    // it to group 4's priority, the close event (0x22) puts it back (the name is not the original's)
    unsigned int m_savedLayer;
    // the open dialog's kind (the open event's m_paramShort[7]: 0 LAY_dialog .. 8 LAY_num_select), 0xFF for none
    // (the name is not the original's)
    unsigned int m_kind;
    unsigned char pad_14[0x8];
    unsigned char pad_1C[0x4];  // the constructor leaves it as it is
    GfMenuObjCommonText* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif
