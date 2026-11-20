#ifndef CLASSES_GF_GFMENUOBJEVTHEATER_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJEVTHEATER_MAINLISTENER_H

#include "classes/gf/GfMenuObjEvTheater.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// _ZTVN2gf18GfMenuObjEvTheater12MainListenerE
class GfMenuObjEvTheater::MainListener : public ::ui::UIObjectListener {
public:
    virtual ~MainListener() {}  // slot 0: its D1 slot is the base's destructor, its D0 weak
    // slot 2: 1 / 0xC start IMG_bg's "start" / "loop", 3 sets up the input, 0x100 makes TitleMain's event request from
    // the selected event and the settings, 0x101 / 0x102 fade the object (0x102 also restores the option data)
    virtual void reciveEvent(ui::EventData const&, unsigned int);
    // the layout of the other gf_menu_obj listeners (initialize, which constructs it, is not written yet)
    unsigned char pad_0C[0x14];
    GfMenuObjEvTheater* m_owner;  // 0x20
};
}  // namespace gf

#endif
