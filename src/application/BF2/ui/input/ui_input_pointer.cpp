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

// UIInputPad's: ui_input_pad.cpp's code ends before them in the original's order
EventData* UIInputPad::getInputEventExt() {
    return &m_eventExt;
}

bool UIInputPad::hasEventExt() const {
    return m_eventExt.m_type != 0;
}

void UIInputPad::clearExt() {
    m_eventExt = EventData(0);
}

UIInputPad* UIInputPad::castUIInputPad() {
    return this;
}

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
