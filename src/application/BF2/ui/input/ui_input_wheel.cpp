#include "mm/mtl/FixedVector.h"
#include "ui/EventData.h"
#include "classes/ui/UIInputLayer.h"
#include "classes/ui/UIInputManager.h"
#include "classes/ui/UIInputSwitcher.h"
#include "classes/ui/UIInputWheel.h"
#include "fw/PadData.h"
#include "ui/UIUtil.h"
#include "classes/ui/UIInputLayer.h"
#include "classes/ui/UIInputManager.h"
#include "classes/ui/UIInputSwitcher.h"
#include "classes/ui/UIInputWheel.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/mm/mtl/IAllocator.h"
#include "math.h"
#include "mm/Math.h"
#include "ui/UIUtil.h"

namespace ui {

// whether the handle is a live UI object's (the name is not the original's)
static inline bool isObject(unsigned int handle) {
    if (handle == 0) {
        return false;
    }
    UIObjectAcc acc(handle);
    return acc.m_object != nullptr;
}

UIInputSwitcher::UIInputSwitcher(unsigned int num) : m_objects(), m_active(-1) {
    m_objects.setAllocator(UIUtil::getProgAllocator());
    m_objects.reserve(num);
}

UIInputSwitcher::~UIInputSwitcher() {
    if (m_objects.size() != 0) {
        m_objects.clear();
    }
}

void UIInputSwitcher::clearInputObject() {
    for (unsigned int i = 0; i < m_objects.size(); i++) {
        m_objects[i] = 0;
    }
}

// setInputObject (0x710067B43C): not identical yet (wip/ui_input_wheel.cpp: the build tests the handle before
// the index)

unsigned int UIInputSwitcher::getInputObject(unsigned int index) {
    if (UIInputManager::get() == nullptr || index >= m_objects.size()) {
        return 0;
    }
    return m_objects[index];
}

void UIInputSwitcher::disable() {
    if (UIInputManager::get() == nullptr) {
        return;
    }
    for (unsigned int i = 0; i < m_objects.size(); i++) {
        unsigned int handle = m_objects[i];
        if (isObject(handle)) {
            unsigned int input = UIInputManager::get()->searchInputHandle(handle);
            if (input != 0) {
                UIInputManager::get()->disableInput(input);
            }
        }
    }
    m_active = -1;
}

void UIInputSwitcher::enable(unsigned int index) {
    if (UIInputManager::get() == nullptr || index >= m_objects.size() || m_objects[index] == 0) {
        return;
    }
    if (m_active != -1) {
        unsigned int handle = m_objects[m_active];
        if (isObject(handle)) {
            unsigned int input = UIInputManager::get()->searchInputHandle(handle);
            if (input != 0) {
                UIInputManager::get()->disableInput(input);
            }
        }
    }
    unsigned int handle = m_objects[index];
    if (isObject(handle)) {
        unsigned int input = UIInputManager::get()->searchInputHandle(handle);
        if (input != 0) {
            UIInputManager::get()->enableInput(input);
            m_active = index;
        }
    }
}

UIInputWheel::~UIInputWheel() {
    ;  // stores the table (a statement the build compiles away)
}

UIInputWheel* UIInputWheel::create(unsigned int id, unsigned int handle, const WheelSetup& setup,
                                   mm::mtl::IAllocator* allocator) {
#line 40
    return new (allocator, 16, __FILE__, __LINE__) UIInputWheel(id, handle, setup);
}

// updateImpl (0x710067B890): not identical yet (wip/ui_input_wheel.cpp: float registers)

EventData* UIInputWheel::getInputEventExt() {
    return &m_event;
}

UIInputWheel* UIInputWheel::castUIInputWheel() {
    return this;
}

}  // namespace ui
