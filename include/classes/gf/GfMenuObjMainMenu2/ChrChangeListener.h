#ifndef CLASSES_GF_GFMENUOBJMAINMENU2_CHRCHANGELISTENER_H
#define CLASSES_GF_GFMENUOBJMAINMENU2_CHRCHANGELISTENER_H

#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63078
class GfMenuObjMainMenu2::ChrChangeListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): zeroes m_chr, stores the owner
    ChrChangeListener(GfMenuObjMainMenu2* owner) : m_chr(), m_owner(owner) {}
    virtual ~ChrChangeListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    GfMenuObjMainMenu2::ChrChangeState m_chr;  // 0xC (the name is not the original's)
    GfMenuObjMainMenu2* m_owner;  // 0x20
};
}  // namespace gf

#endif
