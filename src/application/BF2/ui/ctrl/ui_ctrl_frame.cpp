#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UICtrlFrame.h"
#include <math.h>
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/Vec2.h"
#include "ui/UIUtil.h"
#include "classes/ui/UICtrlSimple.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UICtrlFrame.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/UpdateInfo.h"

namespace ui {

UICtrlFrame::~UICtrlFrame() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

UICtrlFrame* UICtrlFrame::create(unsigned int handle, const Setting& setting) {
#line 56
    UICtrlFrame* ctrl = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UICtrlFrame(handle);
    if (ctrl == nullptr) {
        return nullptr;
    }
    UIObjectAcc acc(handle);
    if (setting.m_viewName != nullptr) {
        ctrl->m_view = acc.searchChild(setting.m_viewName);
    }
    if (ctrl->m_view != 0) {
        mm::Rect<short> rect;
        UIObjectAcc(ctrl->m_view).getRect(rect, 2);
        acc.setLayoutViewport(rect);
    }
    if (setting.m_contentName != nullptr) {
        ctrl->m_content = acc.searchChild(setting.m_contentName);
        UIObjectAcc content(ctrl->m_content);
        content.getScale(ctrl->m_baseScale);
        content.getRect(ctrl->m_rect, 2);
    }
    if (setting.m_centerName != nullptr) {
        ctrl->m_centerObj = acc.searchChild(setting.m_centerName);
    }
    if (setting.m_offsName != nullptr) {
        ctrl->m_offsObj = acc.searchChild(setting.m_offsName);
        mm::Rect<short> rect;
        UIObjectAcc(ctrl->m_offsObj).getRect(rect, 2);
        ctrl->m_offsPos.x = rect.x - ctrl->m_rect.x;
        ctrl->m_offsPos.y = rect.y - ctrl->m_rect.y;
    }
    ctrl->m_moveTime = setting.m_moveTime;
    ctrl->m_scaleTime = setting.m_scaleTime;
    ctrl->m_list = setting.m_list;
    if (ctrl->m_list != nullptr) {
        unsigned int size = ctrl->m_list->getSize();
        ctrl->m_list->addRef();
        ctrl->m_objPos.setAllocator(UIUtil::getProgAllocator());
        ctrl->m_objPos.reserve(size == 0 ? 4 : size);
    }
    ctrl->m_distance = setting.m_distance;
    return ctrl;
}

void UICtrlFrame::setScale(float scale, bool anim) {
    if (anim && m_scaleTime != 0.0f) {
        if (m_scale == scale) {
            return;
        }
        UICtrlSimple<1>::Range range = {m_scale, scale};
        m_scaleMove.start(&range, m_scaleTime, m_scaleCurve);
        uiEventParam time;
        time.m_float = m_scaleTime;
        uiEventParam from;
        from.m_float = m_scale;
        uiEventParam to;
        to.m_float = scale;
        sendEvent(2, &time, &from, &to);
    } else {
        m_scale = scale;
    }
}

void UICtrlFrame::movePoint(mm::Pnt<short> pos, bool anim) {
    if (m_distance != -1) {
        short dx = pos.x - m_point.x;
        short dy = pos.y - m_point.y;
        if (sqrtf(dx * dx + dy * dy) > m_distance) {
            anim = true;
        }
    }
    if (anim && m_moveTime != 0.0f) {
        if (m_point.x == pos.x && m_point.y == pos.y) {
            return;
        }
        UICtrlSimple<2>::Range range[2] = {{(float)m_point.x, (float)pos.x}, {(float)m_point.y, (float)pos.y}};
        m_move.start(range, m_moveTime, m_moveCurve);
        uiEventParam time;
        time.m_float = m_scaleTime;
        uiEventParam from;
        from.m_half[0] = m_point.x;
        from.m_half[1] = m_point.y;
        uiEventParam to;
        to.m_half[0] = pos.x;
        to.m_half[1] = pos.y;
        sendEvent(2, &time, &from, &to);
    } else {
        m_point = pos;
    }
}

// update (0x710066E0B0) is not here yet: the best candidate is 4 words off (two registers swapped)

}  // namespace ui

// update (not identical yet) erases the finished object moves
template mm::mtl::Vector<ui::UICtrlFrame::ObjPosInfo>::iterator mm::mtl::Vector<ui::UICtrlFrame::ObjPosInfo>::erase(mm::mtl::Vector<ui::UICtrlFrame::ObjPosInfo>::iterator);
