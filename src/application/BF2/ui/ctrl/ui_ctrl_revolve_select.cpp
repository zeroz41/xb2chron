#include "mm/Pnt.h"
#include "ui/UIUtil.h"
#include "classes/ui/UICtrlSimple.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UICtrlRevolveSelect.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/UpdateInfo.h"
#include "mm/Col3.h"
#include "mm/Math.h"
#include "mm/Vec2.h"

namespace ui {

UICtrlRevolveSelect::~UICtrlRevolveSelect() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

UICtrlRevolveSelect* UICtrlRevolveSelect::create(unsigned int handle, const RevolveSetting& setting,
                                                 UISelectObjList* list) {
    if (list == nullptr) {
        return nullptr;
    }
#line 52
    UICtrlRevolveSelect* ctrl = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UICtrlRevolveSelect(handle);
    if (ctrl == nullptr) {
        return nullptr;
    }
    list->addRef();
    ctrl->m_setting = setting;
    ctrl->m_list = list;
    ctrl->reset();
    if (setting.m_type == 1 || setting.m_type == 2) {
        ctrl->m_startAngle = 90;
    } else if (setting.m_type == 0) {
        ctrl->m_startAngle = setting.m_startAngle;
    }
    return ctrl;
}

void UICtrlRevolveSelect::reset() {
    int index = m_list->getIndex(false);
    if (m_list->getSize() == 0) {
        return;
    }
    float step = getAngleStep();
    if (index >= 0) {
        m_targetAngle = m_angle = -(index * step);
    }
    m_index = index;
}

void UICtrlRevolveSelect::setIndex(int index, bool anim) {
    if (m_list->getSize() == 0) {
        return;
    }
    float step = getAngleStep();
    if (index >= 0) {
        if (anim && m_setting.m_rollTime > 0.0f) {
            float angle = m_angle;
            float target;
            if (m_setting.m_angleRange == 360) {
                // all round: the shorter way, straight there (move steps) or across the end of the list (around)
                int last = m_index;
                unsigned int move = mm::abs(index - last);
                int count = m_list->getSize();
                unsigned int around;
                if (last > index) {
                    around = mm::abs(index - m_index + count);
                } else {
                    around = mm::abs(m_index - index + count);
                }
                if (move > around) {
                    float d;
                    if (m_setting.m_direction != 0) {
                        d = step * around;
                        if (m_index > index) {
                            d = -d;
                        }
                    } else {
                        d = step * around;
                        if (m_index >= index) {
                            d = -d;
                        }
                    }
                    target = m_targetAngle + d;
                } else {
                    target = m_index != -1 ? m_targetAngle - step * (index - m_index) : -(index * step);
                }
            } else {
                target = -(index * step);
            }
            UICtrlSimple<1>::Range range = {angle, target};
            m_targetAngle = target;
            m_roll.start(&range, m_setting.m_rollTime, m_setting.m_rollCurve);
            uiEventParam time;
            time.m_float = m_setting.m_rollTime;
            uiEventParam to;
            to.m_float = target;
            uiEventParam turn;
            turn.m_float = target - m_angle;
            sendEvent(0, &time, &to, &turn);
        } else {
            m_targetAngle = m_angle = -(index * step);
        }
    }
    m_index = index;
}

void UICtrlRevolveSelect::moveCenterOffset(const mm::Pnt<short>& offset, bool anim) {
    if (anim) {
        UICtrlSimple<2>::Range range[2] = {{(float)m_centerOffset.x, (float)offset.x},
                                           {(float)m_centerOffset.y, (float)offset.y}};
        m_move.start(range, m_setting.m_moveTime, m_setting.m_moveCurve);
        uiEventParam time;
        time.m_float = m_setting.m_moveTime;
        uiEventParam from;
        from.m_half[0] = m_setting.m_center.x + m_centerOffset.x;
        from.m_half[1] = m_setting.m_center.y + m_centerOffset.y;
        uiEventParam to;
        to.m_half[0] = m_setting.m_center.x + offset.x;
        to.m_half[1] = m_setting.m_center.y + offset.y;
        sendEvent(2, &time, &from, &to);
    } else {
        m_centerOffset = offset;
    }
}

bool UICtrlRevolveSelect::isMoving() const {
    return m_move.isBusy();
}

void UICtrlRevolveSelect::update(const fw::UpdateInfo& info) {
    if (m_list == nullptr) {
        return;
    }
    int index = m_list->getIndex(false);
    if (index != m_index) {
        setIndex(index, true);
    } else if (m_roll.isBusy()) {
        m_roll.update(info.m_deltaTime);
        if (!m_roll.isBusy()) {
            sendEvent(1, nullptr, nullptr, nullptr);
        }
        m_angle = m_roll.m_value[0];
    }
    if (m_move.isBusy()) {
        m_move.update(info.m_deltaTime);
        if (!m_move.isBusy()) {
            sendEvent(3, nullptr, nullptr, nullptr);
        }
        m_centerOffset.x = m_move.m_value[0];
        m_centerOffset.y = m_move.m_value[1];
    }
    updateObject(m_angle, m_centerOffset);
    if (m_setting.m_type == 0) {
        UIObjectAcc pointer(m_pointer);
        if (pointer.m_object != nullptr) {
            mm::Pnt<short> pos;
            getCenterPos(pos);
            pointer.setRot(m_angle * 0.0174532924f);
            pointer.setPosCenter(pos);
        }
    }
}

void UICtrlRevolveSelect::updateObject(float angle, const mm::Pnt<short>& offset) {
    if (m_list->getSize() == 0) {
        return;
    }
    float start = m_startAngle;
    float step = getAngleStep();
    angle = start + angle;
    for (unsigned int i = 0; i < m_list->getSize(); i++) {
        UIObjectAcc acc(m_list->getObject(i));
        if (acc.m_object != nullptr) {
            mm::Vec2 scale;
            acc.getScale(scale);
            float x = m_setting.m_center.x + offset.x;
            float y = m_setting.m_center.y + offset.y;
            if (m_setting.m_type == 1 || m_setting.m_type == 2) {
                float rad = angle * 0.0174532924f;
                float s = sinf(rad);
                if (m_setting.m_type == 2) {
                    x -= cosf(rad) * m_setting.m_radius;
                    y += s * m_setting.m_radiusY;
                } else {
                    y -= cosf(rad) * m_setting.m_radius;
                    x += s * m_setting.m_radiusY;
                }
                float range = m_setting.m_angleRange / 360.0f;
                unsigned int count = m_list->getSize();
                float priority = count / (range + range) + m_setting.m_priorityBase;
                acc.setDispPriority(priority + s * priority);
                // the objects at the back (sin -1) are the smallest and darkest
                scale.x = scale.y = 1.0f - m_setting.m_scaleRate * ((1.0f - s) * 0.5f);
                float color = 1.0f - m_setting.m_colorRate * ((1.0f - s) * 0.5f);
                acc.setMulColor(mm::Col3(color, color, color));
            } else if (m_setting.m_type == 0) {
                float rad = angle * 0.0174532924f;
                x += cosf(rad) * m_setting.m_radius;
                y -= sinf(rad) * m_setting.m_radius;
                if (acc.m_handle == m_list->getSelectObject()) {
                    acc.setMulColor(mm::Col3(1.0f, 1.0f, 1.0f));
                } else {
                    float color = 1.0f - m_setting.m_colorRate;
                    acc.setMulColor(mm::Col3(color, color, color));
                }
            }
            acc.setPosCenter(mm::Pnt<short>(x, y));
            acc.setScale(scale);
            acc.setDisp(true);
            angle += step;
        }
    }
}

}  // namespace ui
