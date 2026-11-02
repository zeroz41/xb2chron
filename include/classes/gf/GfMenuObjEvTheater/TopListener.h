#ifndef CLASSES_GF_GFMENUOBJEVTHEATER_TOPLISTENER_H
#define CLASSES_GF_GFMENUOBJEVTHEATER_TOPLISTENER_H

#include "classes/gf/GfMenuObjEvTheater.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// _ZTVN2gf18GfMenuObjEvTheater11TopListenerE
class GfMenuObjEvTheater::TopListener : public ::ui::UIObjectListener {
public:
    virtual ~TopListener() {}  // slot 0: its D1 slot is the base's destructor, its D0 weak
    // slot 2: event 6 moves the selection over the owner's m_topItems (and sets m_title), 8 opens LAY_sub /
    // LAY_select on a decide (1) or closes the layer on a cancel (2), 0x21 / 0x22 fade the object in / out
    virtual void reciveEvent(ui::EventData const&, unsigned int);
    // the layout of the other gf_menu_obj listeners (initialize, which constructs it, is not written yet)
    unsigned char pad_0C[0x14];
    GfMenuObjEvTheater* m_owner;  // 0x20
};
}  // namespace gf

#endif
