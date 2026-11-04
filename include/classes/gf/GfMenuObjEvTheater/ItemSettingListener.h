#ifndef CLASSES_GF_GFMENUOBJEVTHEATER_TUNK_B62178_H
#define CLASSES_GF_GFMENUOBJEVTHEATER_TUNK_B62178_H

#include "classes/gf/GfMenuObjEvTheater.h"
#include "classes/ui/UIObjectListener.h"

namespace gf {
// table 0x7100B62178. Unnamed class (TUnk_<table low address>): the symbols leave it unnamed (no RTTI in 3.0.1; 1.0.0's
// unit has MainListener, TopListener, SubListener, SelectListener, HeaderListener and ScreenListener, and 3.0.1 names the
// first five, so this is one of three listeners new in 3.0.1 or ScreenListener, which nothing proves).
class GfMenuObjEvTheater::ItemSettingListener : public ::ui::UIObjectListener {
public:
    virtual ~ItemSettingListener() {}  // slot 0: its D1 slot is the base's destructor, its D0 (0x7100405300) weak
    // slot 2: hides the object and disables its input on event 1; event 0x22 also removes its operation info and fades
    // it out, event 0x21 shows it, enables input, adds the operation info and fades it in
    virtual void reciveEvent(ui::EventData const&, unsigned int);
    // the layout of the other gf_menu_obj listeners (initialize, which constructs it, is not written yet)
    unsigned char pad_0C[0x10];
    GfMenuObjEvTheater* m_owner;
};
}  // namespace gf

#endif
