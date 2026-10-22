#include "mm/Pnt.h"
#include "ui/UIUtil.h"
#include "classes/ui/UICtrlSimple.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/UpdateInfo.h"

namespace ui {

UICtrlCursorSelect::~UICtrlCursorSelect() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

void UICtrlCursorSelect::CursorSetting::setType(int type) {
    switch (type) {
    case 0:
        m_moveTime = 0.0f;
        break;
    case 1:
        m_moveTime = 0.15f;
        m_moveCurve = CURVE_LINEAR;
        break;
    case 2:
        m_moveTime = 0.15f;
        m_moveCurve = CURVE_SIN90;
        break;
    }
}

UICtrlCursorSelect* UICtrlCursorSelect::create(unsigned int handle, const CursorSetting& setting,
                                               UISelectObjList* list) {
    if (handle == 0 || list == nullptr) {
        return nullptr;
    }
    list->addRef();
#line 78
    UICtrlCursorSelect* ctrl = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UICtrlCursorSelect(handle);
    if (ctrl == nullptr) {
        return nullptr;
    }
    ctrl->m_setting = setting;
    ctrl->m_list = list;
    ctrl->m_cursor = handle;
    ctrl->m_index = list->getIndex(false);
    ctrl->setSelIndex(list->getIndex(false), false);
    UIObjectAcc cursor(handle);
    if (setting.m_waitAnim != nullptr) {
        cursor.startAnimation(setting.m_waitAnim, false);
    }
    return ctrl;
}

void UICtrlCursorSelect::setSelIndex(unsigned int index, bool anim) {
    if (m_cursor == 0 || m_list->getSize() == 0) {
        return;
    }
    UIObjectAcc cursor(m_cursor);
    unsigned int selected = m_list->getIndex(false);
    UIObjectAcc target(m_list->getObject(selected));
    mm::Pnt<short> from;
    cursor.getPos(from);
    mm::Pnt<short> to;
    switch (m_setting.m_dockType) {
    case 6: {
        target.getPosCenter(to);
        mm::Rect<short> rect;
        cursor.getRect(rect, 2);
        if (!m_setting.m_fixX) {
            to.x -= rect.w / 2;
        }
        if (!m_setting.m_fixY) {
            to.y -= rect.h / 2;
        }
        if (!m_setting.m_fixX) {
            to.x += m_setting.m_offsetX;
        }
        if (!m_setting.m_fixY) {
            to.y += m_setting.m_offsetY;
        }
        break;
    }
    case 5:
        calcFit(cursor, target);
        UIUtil::setDockPos(cursor.m_handle, target.m_handle, 0, m_setting.m_outer);
        cursor.getPos(to);
        break;
    default:
        UIUtil::setDockPos(cursor.m_handle, target.m_handle, m_setting.m_dockType, m_setting.m_outer);
        cursor.getPos(to);
        to.x += m_setting.m_offsetX;
        to.y += m_setting.m_offsetY;
        break;
    }
    cursor.setPos(from);
    to.x = m_setting.m_fixX ? from.x : to.x;
    to.y = m_setting.m_fixY ? from.y : to.y;
    if (anim && m_setting.m_moveTime != 0.0f) {
        UICtrlSimple<2>::Range range[2] = {{(float)from.x, (float)to.x}, {(float)from.y, (float)to.y}};
        m_move.start(range, m_setting.m_moveTime, m_setting.m_moveCurve);
    } else {
        m_pos = to;
    }
}

void UICtrlCursorSelect::open(int index) {
    if (m_list != nullptr) {
        m_index = index;
        m_list->setIndex(index);
        setSelIndex(index, false);
    }
}

void UICtrlCursorSelect::setIndex(unsigned int index) {
    if (m_list != nullptr) {
        m_list->setIndex(index);
    }
}

bool UICtrlCursorSelect::inputChange(unsigned int index) {
    if (m_list == nullptr) {
        return false;
    }
    UIObjectAcc cursor(m_cursor);
    if (cursor.m_object == nullptr) {
        return false;
    }
    if (index == 0xFFFFFFFF || m_list->getSize() == 0) {
        cursor.setDisp(false);
        return false;
    }
    setIndex(index);
    if (m_disp) {
        cursor.setDisp(true);
    }
    return true;
}

void UICtrlCursorSelect::setDisp(bool disp) {
    UIObjectAcc cursor(m_cursor);
    if (cursor.m_object != nullptr) {
        cursor.setDisp(disp);
        m_disp = disp;
    }
}

void UICtrlCursorSelect::setAlpha(float alpha) {
    UIObjectAcc cursor(m_cursor);
    if (cursor.m_object != nullptr) {
        cursor.setAlpha(alpha);
    }
}

void UICtrlCursorSelect::update(const fw::UpdateInfo& info) {
    if (m_list == nullptr || m_list->getSize() == 0) {
        return;
    }
    UIObjectAcc cursor(m_cursor);
    unsigned int index = m_list->getIndex(false);
    if (index != m_index) {
        setSelIndex(index, true);
        uiEventParam change;
        change.m_half[0] = index;
        change.m_half[1] = m_index;
        sendEvent(0, &change, nullptr, nullptr);
        m_index = index;
        if (m_setting.m_moveTime == 0.0f) {
            uiEventParam end;
            end.m_half[0] = index;
            sendEvent(1, &end, nullptr, nullptr);
        } else if (m_setting.m_moveAnim != nullptr) {
            cursor.startAnimation(m_setting.m_moveAnim, false);
        }
    }
    if (m_move.isBusy()) {
        m_move.update(info.m_deltaTime);
        m_pos.x = m_move.m_value[0];
        m_pos.y = m_move.m_value[1];
        if (!m_move.isBusy()) {
            uiEventParam end;
            end.m_half[0] = index;
            sendEvent(1, &end, nullptr, nullptr);
            if (m_setting.m_waitAnim != nullptr) {
                cursor.startAnimation(m_setting.m_waitAnim, false);
            }
        }
    }
    updateObjectPos(m_pos);
}

void UICtrlCursorSelect::updateObjectPos(mm::Pnt<short> pos) {
    if (m_cursor == 0) {
        return;
    }
    UIObjectAcc cursor(m_cursor);
    cursor.setPos(pos);
    if (m_list != nullptr && m_list->getSize() != 0) {
        unsigned int selected = m_list->getIndex(false);
        UIObjectAcc target(m_list->getObject(selected));
        if (target.m_object != nullptr) {
            setSelIndex(m_index, false);
            if (m_setting.m_dockType == 5) {
                calcFit(cursor, target);
            }
        }
    }
}

}  // namespace ui
