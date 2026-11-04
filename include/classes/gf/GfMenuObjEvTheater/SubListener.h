#ifndef CLASSES_GF_GFMENUOBJEVTHEATER_SUBLISTENER_H
#define CLASSES_GF_GFMENUOBJEVTHEATER_SUBLISTENER_H

#include "classes/gf/GfMenuObjEvTheater.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B620D8
class GfMenuObjEvTheater::SubListener : public ::ui::UIObjectListener {
public:
    virtual ~SubListener() {}  // slot 0: its D1 slot is the base's destructor, its D0 (0x71004052F0) weak
    // slot 2: event 3 (1) sets up the input selection from the owner's m_msgList; 6 moves m_msgList's selection and
    // refreshes the owner (refreshSubList); 8 opens LAY_preview (m_title 4) or LAY_select on a decide (1) or goes back
    // to LAY_top on a cancel (2), then closes; 0x21 / 0x22 fade the object in / out
    virtual void reciveEvent(ui::EventData const&, unsigned int);
    // the layout of the other gf_menu_obj listeners (initialize, which constructs it, is not written yet)
    unsigned char pad_0C[0x10];
    GfMenuObjEvTheater* m_owner;
};
}  // namespace gf

#endif
