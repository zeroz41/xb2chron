#ifndef CLASSES_GF_GFMENUOBJOTHERCURSOR_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJOTHERCURSOR_MAINLISTENER_H

#include "classes/gf/GfMenuObjOtherCursor.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63E20
class GfMenuObjOtherCursor::MainListener : public ::ui::UIObjectListener {
public:
    MainListener(GfMenuObjOtherCursor* owner) : pad_C(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_C[0x10];  // the constructor zeroes it; no code here reads it
    GfMenuObjOtherCursor* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
