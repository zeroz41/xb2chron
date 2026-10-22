#include "classes/ui/UITimer.h"
#include "classes/ui/UITimerManager.h"
#include "classes/ui/UIEventManager.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/UpdateInfo.h"
#include "ui/UIUtil.h"

namespace ui {

UITimerManager::UITimerManager() : m_suspend(false) {
    m_timers.reserve(UIUtil::getProgAllocator(), 0x40);
}

UITimerManager::~UITimerManager() {
    for (mm::mtl::IntrusiveList<TimerNode>::iterator it = m_list.begin(); it != m_list.end();) {
        UITimer* timer = static_cast<UITimer*>(m_timers.getPtr(it->m_handle));
        m_timers.remove(it->m_handle);
        if (timer != nullptr) {
            delete timer;
        }
        TimerNode* node = it.operator->();
        it = m_list.erase(it);
        delete node;
    }
    // the list's own emptying (nothing is left in it by now)
    for (mm::mtl::IntrusiveList<TimerNode>::iterator it = m_list.begin(); it != m_list.end();) {
        it = m_list.erase(it);
    }
    m_timers.destroy();
}

void UITimerManager::update(const fw::UpdateInfo& info) {
    if (m_suspend) {
        return;
    }
    for (mm::mtl::IntrusiveList<TimerNode>::iterator it = m_list.begin(); it != m_list.end();) {
        TimerNode& node = *it;
        UITimer* timer = static_cast<UITimer*>(m_timers.getPtr(node.m_handle));
        if (timer != nullptr) {
            if (!UIUtil::isTerm(node.m_objHandle)) {
                if (node.m_suspend) {
                    ++it;
                    continue;
                }
                timer->update(info.m_deltaTime);
                if (!timer->isOver()) {
                    ++it;
                    continue;
                }
                node.m_count++;
                UIEventManager::EventInfo event;
                event.m_handle = node.m_objHandle;
                event.m_data.m_type = 0xB;
                event.m_data.m_param0 = node.m_eventId;
                event.m_data.m_param1 = node.m_count;
                UIEventManager::get()->pushObjectEvent(event);
                if (node.m_repeat) {
                    timer->restart();
                    ++it;
                    continue;
                }
                timer->stop();
            }
            m_timers.remove(node.m_handle);
            delete timer;
        }
        it = m_list.erase(it);
        delete &node;
    }
}

unsigned int UITimerManager::registTimer(unsigned int handle, unsigned short id, unsigned long end, bool repeat) {
#line 172
    UITimer* timer = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UITimer();
    if (timer == nullptr) {
        return 0;
    }
#line 177
    TimerNode* node = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) TimerNode;
    if (node == nullptr) {
        delete timer;
        timer = nullptr;
    }
    unsigned int timerHandle = m_timers.regist(timer);
    if (timerHandle == 0) {
        if (timer != nullptr) {
            delete timer;
        }
        return 0;
    }
    timer->start(end);
    node->m_handle = timerHandle;
    node->m_objHandle = handle;
    node->m_eventId = id;
    node->m_count = 0;
    node->m_repeat = repeat;
    node->m_suspend = false;
    m_list.push_back(node);
    return timerHandle;
}

void UITimerManager::releaseTimer(unsigned int handle) {
    if (handle == 0) {
        return;
    }
    for (mm::mtl::IntrusiveList<TimerNode>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if (it->m_handle == handle) {
            UITimer* timer = static_cast<UITimer*>(m_timers.getPtr(it->m_handle));
            m_timers.remove(it->m_handle);
            if (timer != nullptr) {
                delete timer;
            }
            TimerNode* node = it.operator->();
            m_list.erase(it);
            // freed without the null check a delete expression makes (its destructor does nothing)
            operator delete(node);
            return;
        }
    }
}

void UITimerManager::setTimerSpeedFactor(unsigned int handle, float factor) {
    if (handle == 0) {
        return;
    }
    for (mm::mtl::IntrusiveList<TimerNode>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if (it->m_handle == handle) {
            static_cast<UITimer*>(m_timers.getPtr(handle))->m_speedFactor = factor;
        }
    }
}

unsigned int UITimerManager::getTimerHandle(unsigned int objHandle) {
    if (objHandle == 0) {
        return 0;
    }
    for (mm::mtl::IntrusiveList<TimerNode>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if ((*it).m_objHandle == objHandle) {
            return it->m_handle;
        }
    }
    return 0;
}

}  // namespace ui
