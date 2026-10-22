#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UICtrlManager.h"
#include "classes/ui/UIEventManager.h"
#include "ui/UIUtil.h"

namespace ui {

UICtrlObject::UICtrlObject(unsigned int handle) : m_handle(handle), m_eventHandle(0) {
    addRef();
    UICtrlManager::get()->addCtrlObject(this);
}

UICtrlObject::~UICtrlObject() {
    ;  // stores the table (a statement the build compiles away)
}

bool UICtrlObject::isTerm() {
    if (m_RefCount == 1) {
        return true;
    }
    return !UIUtil::isValid(m_handle);
}

void UICtrlObject::setupEventHanding(unsigned int handle, unsigned short id) {
    m_eventHandle = handle;
    m_eventId = id;
}

unsigned short UICtrlObject::getEventCtrlObjID(const EventData& event) {
    return event.m_param0Short;
}

unsigned short UICtrlObject::getEventType(const EventData& event) {
    return event.m_paramShort[1];
}

void UICtrlObject::sendEvent(unsigned short type, const uiEventParam* param0, const uiEventParam* param1,
                             const uiEventParam* param2) {
    UIEventManager* manager = UIEventManager::get();
    if (manager == nullptr || m_eventHandle == 0) {
        return;
    }
    EventData data;
    data.m_type = 0xE;
    data.m_paramShort[0] = m_eventId;
    data.m_paramShort[1] = type;
    data.m_param1 = param0 != nullptr ? param0->m_value : 0;
    data.m_param2 = param1 != nullptr ? param1->m_value : 0;
    data.m_param3 = param2 != nullptr ? param2->m_value : 0;
    UIEventManager::EventInfo info;
    info.m_handle = m_eventHandle;
    info.m_data = data;
    manager->pushObjectEvent(info);
}

}  // namespace ui
