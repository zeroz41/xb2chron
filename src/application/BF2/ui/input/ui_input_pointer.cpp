#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/mtl/FixedVector.h"
#include "ui/EventData.h"
#include "classes/ui/UIInputLayer.h"
#include "classes/ui/UIInputPad.h"
#include "classes/ui/UIInputPointer.h"
#include "classes/ui/UIObjectAcc.h"
#include "fw/PadData.h"
#include "ui/UIUtil.h"
#include "classes/ui/UIInputLayer.h"
#include "classes/ui/UIInputPad.h"
#include "classes/ui/UIInputPointer.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/mm/mtl/IAllocator.h"
#include "math.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "ui/UIUtil.h"

namespace ui {

UIInputPointer::~UIInputPointer() {
    if (m_selection.m_list != nullptr) {
        m_selection.m_list->release();
        m_selection.m_list = nullptr;
    }
}

UIInputPointer* UIInputPointer::create(unsigned int id, unsigned int handle, const PointerSetup& setup,
                                       mm::mtl::IAllocator* allocator) {
#line 56
    return new (allocator, 16, __FILE__, __LINE__) UIInputPointer(id, handle, setup);
}

void UIInputPointer::setupPointerSelection(const SelectionSetup& setup) {
    if (m_selection.m_list != nullptr) {
        m_selection.m_list->release();
        m_selection.m_list = nullptr;
    }
    m_selection = setup;
    if (m_selection.m_list != nullptr) {
        m_selection.m_list->addRef();
    }
    m_scale = 1.0f;
    m_pos = mm::Pnt<short>(0, 0);
}

void UIInputPointer::changePointerPos(const mm::Pnt<short>& pos) {
    if (m_pos.x != pos.x || m_pos.y != pos.y) {
        m_newPos = pos;
        m_posChanged = true;
    }
}

void UIInputPointer::changeRegionScale(float scale) {
    if (m_regionScale != scale) {
        m_regionScale = scale;
        m_scaleChanged = true;
    }
}

bool UIInputPointer::updateImpl() {
    const fw::PadData* pad = UIUtil::getPadData();
    float stickX = pad->m_rx;
    float stickY = pad->m_ry;
    mm::Pnt<short> pos = m_pos;
    if (m_rectChanged) {
        m_selection.m_rect = m_newRect;
        m_rectChanged = false;
    }
    bool result;
    if (m_posChanged) {
        result = setPointerPos(m_newPos, false, true);
        m_dir = mm::Vec2(0.0f, 0.0f);
        m_posChanged = false;
    } else if (m_scaleChanged) {
        float ratio = m_regionScale / m_scale;
        // the offset from the region's corner is stored first and the corner read again for the sum
        mm::Pnt<short> scaled;
        scaled.x = ratio * (pos.x - m_selection.m_rect.x);
        scaled.x += m_selection.m_rect.x;
        scaled.y = ratio * (pos.y - m_selection.m_rect.y);
        scaled.y += m_selection.m_rect.y;
        m_scale = m_regionScale;
        result = setPointerPos(scaled, false, false);
        m_scaleChanged = false;
    } else {
        float length = sqrtf(stickX * stickX + stickY * stickY);
        if (length == 0.0f) {
            if (m_selection.m_list == nullptr || !m_snap) {
                result = false;
            } else if (m_snapped) {
                result = false;
            } else if (m_select != -1 && sqrtf(m_dir.x * m_dir.x + m_dir.y * m_dir.y) != 0.0f) {
                UIObjectAcc acc(m_selection.m_list->getContents(m_select));
                if (acc.m_object != nullptr && acc.isDisp()) {
                    mm::Rect<short> rect;
                    acc.getRect(rect, 2);
                    pos.x = rect.x + rect.w / 2;
                    pos.y = rect.y + rect.h / 2;
                    result = setPointerPos(pos, true, true);
                    m_snapped = true;
                } else {
                    result = false;
                }
            } else {
                result = false;
            }
        } else {
            float speed = m_pointerSpeed * m_speedScale;
            if (speed <= 1.0f) {
                speed = 1.0f;
            }
            float inv = 1.0f / sqrtf(stickX * stickX + stickY * stickY);
            stickX *= inv;
            stickY *= inv;
            pos.x += (int)(speed * stickX);
            pos.y += (int)(-stickY * speed);
            result = setPointerPos(pos, false, true);
        }
    }
    return result;
}

// setPointerPos (0x710067AC88): not identical yet (register allocation in the nearest search)

EventData* UIInputPointer::getInputEventExt() {
    return &m_eventExt;
}

bool UIInputPointer::hasEventExt() const {
    return m_eventExt.m_type != 0;
}

void UIInputPointer::clearExt() {
    m_eventExt = EventData(0);
}

UIInputPointer* UIInputPointer::castUIInputPointer() {
    return this;
}

}  // namespace ui
