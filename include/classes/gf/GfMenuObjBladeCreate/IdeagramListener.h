#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_IDEAGRAMLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_IDEAGRAMLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"
#include "classes/ui/UIObjectListener.h"
#include "gf/GfMenuObjUtil.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60160
class GfMenuObjBladeCreate::IdeagramListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): zeroes 0xC-0x1B after storing its table, then stores the owner (as
    // MainListener); its D1 slot is the base's destructor: an inline destructor
    IdeagramListener(GfMenuObjBladeCreate* owner) : m_shown(0), pad_10(), m_owner(owner) {}
    virtual ~IdeagramListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // inline helpers (the names are not the original's; their CtrlParams sit above reciveEvent's acc in the frame,
    // as an inlined callee's locals do): the fade of 0x21 (in) and 0x22 (out)
    static void fadeIn(unsigned int handle) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 1;
        param.m_time = 0.5f;
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(handle, param, nullptr);
    }
    static void fadeOut(unsigned int handle) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_startFlags = 2;
        param.m_time = 0.25f;
        param.m_eventId = 2;
        GfMenuObjUtil::startCtrl(handle, param, nullptr);
    }
    // 1 while faded in: 0x21 fades in only from 0, 0x22 fades out only from 1, 1 hides and resets it (the name is
    // not the original's)
    unsigned int m_shown;
    unsigned char pad_10[0xC];
    GfMenuObjBladeCreate* m_owner;  // (the name is not the original's)
};
}  // namespace gf

#endif
