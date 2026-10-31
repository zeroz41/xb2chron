#include "ui/EventData.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuObjStaffroll.h"
#include "classes/gf/GfMenuObjStaffroll/MainListener.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Pnt.h"

namespace gf {

void GfMenuObjStaffroll::start(float speed, int type) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x85));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0Float = speed;
        event.m_param1 = type;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjStaffroll::fadeout() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x85));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjStaffroll::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 0x21: {
        float time = event.m_param0Float;
        short x = event.m_param1;
        m_owner->m_scrollSpeed = m_owner->m_scrollLength / (time * 30.0f);
        m_owner->m_state = 2;
        mm::Pnt<short> pos(x, 0);
        acc.setPos(pos);
        acc.setDisp(true);
        bool disp = !GfMenuObjUtil::fn_710048FD30(3);
        ui::UIObjectAcc grade(acc.searchSibiling("LAY_grade"));
        grade.setDisp(disp);
        break;
    }
    case 0x22: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = 2.0f;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        ui::UIObjectAcc grade(acc.searchSibiling("LAY_grade"));
        grade.setDisp(false);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
