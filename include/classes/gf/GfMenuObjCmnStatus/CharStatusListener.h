#ifndef CLASSES_GF_GFMENUOBJCMNSTATUS_CHARSTATUSLISTENER_H
#define CLASSES_GF_GFMENUOBJCMNSTATUS_CHARSTATUSLISTENER_H

#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B61338; initialize makes one for LAY_status_dr and one for LAY_status_bl
class GfMenuObjCmnStatus::CharStatusListener : public ::ui::UIObjectListener {
public:
    // initialize zeroes 0xC-0x1B after storing its table: its own fields
    CharStatusListener(GfMenuObjCmnStatus* owner) : pad_0C(), m_owner(owner) {}
    virtual ~CharStatusListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjCmnStatus* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
