#include "classes/ui/UIInputLayer.h"
#include "classes/ui/IUIInputSelectionChecker.h"
#include "fw/PadData.h"
#include "ui/UIUtil.h"

namespace ui {

UIInputLayer::UIInputLayer(unsigned int id, unsigned int handle, const InputSetup& setup)
    : m_handle(handle), m_event(0), m_actionEvent(0), m_id(id), m_selectMax(0), m_select(-1),
      m_selectEnable(true), m_checker(nullptr) {
    m_setup = setup;
}

UIInputLayer::~UIInputLayer() {}

bool UIInputLayer::update() {
    const fw::PadData* pad = UIUtil::getPadData();
    EventData event;
    for (ActionInfo* action = m_setup.m_actions.begin(); action != m_setup.m_actions.end(); ++action) {
        unsigned int bits = UIUtil::convUIPadToFWPad(action->m_pad, false);
        if (!action->m_enable) {
            continue;
        }
        if ((pad->m_down & bits) || ((pad->m_repeat & bits) && action->m_repeat)) {
            switch (action->m_pad) {
            case 2:
                event.m_type = 5;
                event.m_param1 = 0;
                break;
            case 1:
                event.m_type = 4;
                event.m_param1 = 0;
                break;
            default:
                event.m_type = 7;
                event.m_param1 = action->m_pad;
                break;
            }
            event.m_param0 = m_select;
            m_event = event;
            if (action->m_enable) {
                event.m_type = 8;
                event.m_param1 = action->m_action;
                m_actionEvent = event;
            }
            return true;
        }
    }
    return updateImpl();
}

void UIInputLayer::setupSelection(int select, unsigned int max) {
    m_selectMax = max;
    int old = m_select;
    m_select = select < (int)max ? select : 0;
    m_event.m_type = 6;
    m_event.m_param0 = m_select;
    m_event.m_param1 = old;
    m_event.m_param2 = 0;
    m_event.m_param3 = 0;
}

void UIInputLayer::resetSelection() {
    m_select = -1;
}

bool UIInputLayer::changeSelect(int select, unsigned char param) {
    if (m_select == select || !m_selectEnable) {
        return false;
    }
    m_event.m_type = 6;
    m_event.m_param2 = param;
    m_event.m_param3 = 0;
    m_event.m_param0 = select;
    m_event.m_param1 = m_select;
    m_select = select;
    return true;
}

bool UIInputLayer::isEnableSelect(int select) {
    if (m_checker != nullptr) {
        return m_checker->isEnableSelect(m_id, select);
    }
    return true;
}

void UIInputLayer::setActionEnable(unsigned short action, bool enable) {
    for (ActionInfo* it = m_setup.m_actions.begin(); it != m_setup.m_actions.end(); ++it) {
        if (it->m_action == action) {
            it->m_enable = enable;
            return;
        }
    }
}

bool UIInputLayer::hasEventExt() const {
    return false;
}

void UIInputLayer::clear() {
    m_event.m_type = 0;
    m_event.m_param2 = 0;
    m_event.m_param3 = 0;
    m_event.m_param0 = 0;
    m_event.m_param1 = 0;
    m_actionEvent.m_type = 0;
    m_actionEvent.m_param2 = 0;
    m_actionEvent.m_param3 = 0;
    m_actionEvent.m_param0 = 0;
    m_actionEvent.m_param1 = 0;
    clearExt();
}

void UIInputLayer::clearExt() {}

UIInputPad* UIInputLayer::castUIInputPad() {
    return nullptr;
}

UIInputWheel* UIInputLayer::castUIInputWheel() {
    return nullptr;
}

UIInputPointer* UIInputLayer::castUIInputPointer() {
    return nullptr;
}

}  // namespace ui
