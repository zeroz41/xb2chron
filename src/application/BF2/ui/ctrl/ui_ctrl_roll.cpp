#include "mm/Pnt.h"
#include "mm/Math.h"
#include "ui/UIUtil.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UICtrlObject.h"
#include "classes/ui/TUnk_B74610.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/UpdateInfo.h"

namespace ui {

TUnk_B74610::~TUnk_B74610() {
    if (m_entries.capacity() != 0) {
        m_entries.destroy();
    }
}

TUnk_B74610* TUnk_B74610::fn_7100672020(unsigned int handle, const Setting& setting) {
#line 46
    TUnk_B74610* ctrl = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) TUnk_B74610(handle);
    if (ctrl == nullptr) {
        return nullptr;
    }
    ctrl->m_setting = setting;
    ctrl->m_entries.setAllocator(setting.m_allocator);
    ctrl->m_entries.reserve(setting.m_count);
    ctrl->fn_7100672160();
    return ctrl;
}

void TUnk_B74610::fn_7100672160() {
    m_entries.clear();
}

void TUnk_B74610::fn_710067237C(unsigned int handle) {
    if (m_entries.size() == m_entries.capacity()) {
        return;
    }
    for (Entry* it = m_entries.begin(); it != m_entries.end(); ++it) {
        if (it->m_handle == handle) {
            m_entries.erase(it);
            return;
        }
    }
}

void TUnk_B74610::fn_710067256C(bool paused) {
    m_paused = paused;
}

void TUnk_B74610::update(const fw::UpdateInfo&) {
    if (m_entries.size() == 0 || m_paused) {
        return;
    }
    mm::Pnt<short> centerPos;
    UIObjectAcc center(m_handle);
    center.getPosCenter(centerPos);
    for (unsigned long i = 0; i < m_entries.size(); i++) {
        Entry& entry = m_entries[i];
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
