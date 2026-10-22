#include "classes/ui/UIAnimationManager.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/UpdateInfo.h"
#include "ui/UIUtil.h"

namespace ui {

UIAnimationManager::UIAnimationManager() {}

// the destructor (0x710066AD8C, 0x710066AEB4) is not written yet: the candidate differs in register allocation
// only (see the worker report)

void UIAnimationManager::update(const fw::UpdateInfo& info) {
    for (mm::mtl::IntrusiveList<ObjectNode>::iterator it = m_list.begin(); it != m_list.end();) {
        ObjectNode& node = *it;
        UIObjectAcc acc(node.m_handle);
        if (acc.isTerm()) {
            it = m_list.erase(it);
            delete &node;
            continue;
        }
        bool playing = acc.isPlayingAnimation();
        if (node.m_playing != playing) {
            if (node.m_playing && !playing) {
                UIEventManager::EventInfo event;
                event.m_handle = node.m_eventHandle;
                event.m_data.m_type = 0xC;
                event.m_data.m_param0 = node.m_eventParam;
                UIEventManager::get()->pushObjectEvent(event);
            }
            node.m_playing = playing;
        }
        ++it;
    }
}

bool UIAnimationManager::registObject(unsigned int handle) {
    UIObjectAcc acc(handle);
    if (!acc.isImage() || !acc.hasAnimation()) {
        return false;
    }
#line 105
    ObjectNode* node = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) ObjectNode;
    node->m_handle = handle;
    node->m_eventHandle = handle;
    node->m_eventParam = 0;
    node->m_playing = false;
    m_list.push_back(node);
    return true;
}

void UIAnimationManager::fn_710066B148(unsigned int handle, unsigned int eventHandle, unsigned int eventParam) {
    for (mm::mtl::IntrusiveList<ObjectNode>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        ObjectNode& node = *it;
        if (node.m_handle == handle) {
            node.m_eventHandle = eventHandle;
            node.m_eventParam = eventParam;
        }
    }
}

}  // namespace ui
