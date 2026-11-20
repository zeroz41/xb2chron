#ifndef CLASSES_GF_GFMENUOBJCOMMONTEXT_DIALOGLISTENER_H
#define CLASSES_GF_GFMENUOBJCOMMONTEXT_DIALOGLISTENER_H

#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B614E8
class GfMenuObjCommonText::DialogListener : public ::ui::UIObjectListener {
public:
    DialogListener(GfMenuObjCommonText* owner) : m_state(0), pad_10(), m_shown(0), m_owner(owner) {}
    virtual ~DialogListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    // the dialog's kind from the open event (0x21): 0 ok only, 1 ok/cancel, 2 the long ok/ok/cancel (the name is
    // not the original's)
    int m_state;
    unsigned char pad_10[0x8];
    int m_shown;  // 1 from the open event (0x21) until the close (0x22) or suspend (1) event (the name is not the original's)
    unsigned char pad_1C[0x4];
    GfMenuObjCommonText* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif
