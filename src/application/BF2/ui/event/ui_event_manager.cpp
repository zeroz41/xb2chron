#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIGameListener.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIEventCondition.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIObjectListener.h"
#include "fw/UpdateInfo.h"
#include "ui/UIUtil.h"

namespace ui {

UIEventManager::UIEventManager() : m_gameListener(nullptr) {}

UIEventManager::~UIEventManager() {
    m_gameListener = nullptr;
    for (mm::mtl::IntrusiveList<ListenerNode>::iterator it = m_listeners.begin(); it != m_listeners.end();) {
        if (it->m_listener != nullptr) {
            it->m_listener->release();
            it->m_listener = nullptr;
        }
        UIEventCondition* condition = it->m_conditions;
        while (condition != nullptr) {
            UIEventCondition* next = condition->m_next;
            condition->release();
            condition = next;
        }
        ListenerNode* node = it.operator->();
        it = m_listeners.erase(it);
        delete node;
    }
    // the list's own emptying (nothing is left in it by now)
    for (mm::mtl::IntrusiveList<ListenerNode>::iterator it = m_listeners.begin(); it != m_listeners.end();) {
        it = m_listeners.erase(it);
    }
    m_objectEvents.clear();
    m_gameEvents.clear();
}

void UIEventManager::update(const fw::UpdateInfo& info) {
    if (m_listeners.m_size != 0) {
        for (mm::mtl::IntrusiveList<ListenerNode>::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it) {
            for (UIEventCondition* condition = (*it).m_conditions; condition != nullptr;
                 condition = condition->m_next) {
                int event = condition->update();
                if (event != 0) {
                    // event 0xD: a condition of the object raised an event
                    EventInfo eventInfo;
                    eventInfo.m_handle = (*it).m_handle;
                    eventInfo.m_delay = 0.0f;
                    eventInfo.m_data.m_type = 0xD;
                    eventInfo.m_data.m_param0 = event;
                    eventInfo.m_data.m_param1 = condition->m_userValue0;
                    eventInfo.m_data.m_param2 = condition->m_userValue1;
                    eventInfo.m_data.m_param3 = condition->getArg();
                    pushObjectEvent(eventInfo);
                }
            }
        }
        if (m_objectEvents.size() != 0) {
            for (EventInfo* event = m_objectEvents.begin(); event != m_objectEvents.end();) {
                if (stepEventInfo(*event, info.m_deltaTime)) {
                    for (mm::mtl::IntrusiveList<ListenerNode>::iterator it = m_listeners.begin();
                         it != m_listeners.end(); ++it) {
                        if (event->m_handle == (*it).m_handle) {
                            if (!UIUtil::isTerm((*it).m_handle)) {
                                (*it).m_listener->reciveEvent(event->m_data, event->m_handle);
                            }
                            break;
                        }
                    }
                    event = m_objectEvents.erase(event);
                } else {
                    ++event;
                }
            }
        }
    }
    if (m_gameListener != nullptr && m_gameEvents.size() != 0) {
        for (EventInfo* event = m_gameEvents.begin(); event != m_gameEvents.end();) {
            if (stepEventInfo(*event, info.m_deltaTime)) {
                m_gameListener->reciveEvent(event->m_data, event->m_handle);
                event = m_gameEvents.erase(event);
            } else {
                ++event;
            }
        }
    }
}

void UIEventManager::pushObjectEvent(const EventInfo& info) {
    m_objectEvents.push_back(info);
}

bool UIEventManager::stepEventInfo(EventInfo& info, float time) {
    if (info.m_delay == 0.0f) {
        return true;
    }
    float delay = info.m_delay - time;
    info.m_delay = delay < 0.0f ? 0.0f : delay;
    return false;
}

void UIEventManager::registObjectListener(unsigned int handle, UIObjectListener* listener) {
    if (!UIUtil::isValid(handle)) {
        return;
    }
    for (mm::mtl::IntrusiveList<ListenerNode>::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it) {
        if ((*it).m_handle == handle) {
            return;
        }
    }
    listener->addRef();
#line 198
    ListenerNode* node = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) ListenerNode;
    node->m_handle = handle;
    node->m_listener = listener;
    node->m_conditions = nullptr;
    m_listeners.push_back(node);
    UIUtil::getObject(handle)->m_flags |= 2;  // bit 1: the object has a listener (removeObjectListener clears it)
    // event 1 tells the new listener it is registered; the parameters are stored again although EventData's
    // constructor zeroes them (without the stores the copy into the queue goes through the stack)
    EventInfo info;
    info.m_handle = handle;
    info.m_delay = 0.0f;
    info.m_data.m_type = 1;
    info.m_data.m_param0 = 0;
    info.m_data.m_param1 = 0;
    info.m_data.m_param2 = 0;
    info.m_data.m_param3 = 0;
    UIEventManager::get()->pushObjectEvent(info);
}

void UIEventManager::removeObjectListener(unsigned int handle) {
    if (!UIUtil::isValid(handle)) {
        return;
    }
    for (mm::mtl::IntrusiveList<ListenerNode>::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it) {
        if (it->m_handle == handle) {
            if (it->m_listener != nullptr) {
                it->m_listener->release();
                it->m_listener = nullptr;
            }
            UIEventCondition* condition = it->m_conditions;
            while (condition != nullptr) {
                UIEventCondition* next = condition->m_next;
                condition->release();
                condition = next;
            }
            UIUtil::getObject(handle)->m_flags &= ~2;
            ListenerNode* node = it.operator->();
            m_listeners.erase(it);
            operator delete(node);  // freed without the null check a delete expression makes
            return;
        }
    }
}

void UIEventManager::addCondition(unsigned int handle, UIEventCondition* condition) {
    if (!UIUtil::isValid(handle)) {
        return;
    }
    for (mm::mtl::IntrusiveList<ListenerNode>::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it) {
        if ((*it).m_handle == handle) {
            condition->addRef();
            condition->m_next = (*it).m_conditions;
            (*it).m_conditions = condition;
        }
    }
}

void UIEventManager::pushGameEvent(const EventInfo& info) {
    if (m_gameListener != nullptr) {
        m_gameEvents.push_back(info);
    }
}

void UIEventManager::setGameListener(UIGameListener* listener) {
    m_gameListener = listener;
}

bool UIEventManager::isObjectListenerFull() {
    return false;
}

}  // namespace ui
