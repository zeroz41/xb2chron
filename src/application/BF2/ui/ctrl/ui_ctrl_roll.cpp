#include "mm/Pnt.h"
#include "mm/Math.h"
#include "ui/UIUtil.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UICtrlRoll.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/UpdateInfo.h"

namespace ui {

UICtrlRoll::~UICtrlRoll() {
    if (m_entries.capacity() != 0) {
        m_entries.destroy();
    }
}

UICtrlRoll* UICtrlRoll::create(unsigned int handle, const RollSetup& setting) {
#line 46
    UICtrlRoll* ctrl = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UICtrlRoll(handle);
    if (ctrl == nullptr) {
        return nullptr;
    }
    ctrl->m_setting = setting;
    ctrl->m_entries.setAllocator(setting.m_allocator);
    ctrl->m_entries.reserve(setting.m_count);
    ctrl->reset();
    return ctrl;
}

void UICtrlRoll::reset() {
    m_entries.clear();
}

void UICtrlRoll::delObject(unsigned int handle) {
    if (m_entries.size() == m_entries.capacity()) {
        return;
    }
    for (RollObjInfo* it = m_entries.begin(); it != m_entries.end(); ++it) {
        if (it->m_handle == handle) {
            m_entries.erase(it);
            return;
        }
    }
}

void UICtrlRoll::pause(bool paused) {
    m_paused = paused;
}

void UICtrlRoll::update(const fw::UpdateInfo&) {
    if (m_entries.size() == 0 || m_paused) {
        return;
    }
    mm::Pnt<short> centerPos;
    UIObjectAcc center(m_handle);
    center.getPosCenter(centerPos);
    for (unsigned long i = 0; i < m_entries.size(); i++) {
        RollObjInfo& entry = m_entries[i];
        UIObjectAcc object(entry.m_handle);
        float angle;
        if (entry.m_param.m_reverse) {
            angle = entry.m_angle + entry.m_param.m_speed;
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
        } else {
            angle = entry.m_angle - entry.m_param.m_speed;
            if (angle < 0.0f) {
                angle += 360.0f;
            }
        }
        float rad = angle * 0.0174532924f;
        mm::Pnt<short> pos;
        pos = centerPos;
        pos.x += (short)(cosf(rad) * entry.m_param.m_radius);
        pos.y += (short)-(sinf(rad) * entry.m_param.m_radius);
        object.setPosCenter(pos);
        entry.m_angle = angle;
    }
}

}  // namespace ui
