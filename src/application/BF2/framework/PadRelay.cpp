#include "fw/PadData.h"
#include "fw/PadRelay.h"
#include "classes/fw/PadResEvent.h"
#include "classes/fw/PadResEventManager.h"
#include "classes/fw/PadManager.h"
#include "bin/BinaryResolver.h"
#include <string.h>

namespace fw {

PadRelay::PadRelay() : m_padNo(-1), m_eventNo(-1) {}

PadRelay::~PadRelay() {}

void PadRelay::bind(int padNo, int eventNo, mm::mtl::IAllocator* allocator) {
    m_padNo = padNo;
    m_eventNo = eventNo;
    m_actions.setAllocator(allocator);
    m_axes.setAllocator(allocator);
}

void PadRelay::unbind() {
    m_axes.clear();
    m_actions.clear();
    m_axes.setAllocator(nullptr);
    m_actions.setAllocator(nullptr);
    m_padNo = -1;
    m_eventNo = -1;
}

void PadRelay::update() {
    if (const PadResEventManager* manager = PadResEventManager::get()) {
        if (const PadResEvent* event = manager->getResource(m_eventNo)) {
            for (unsigned int i = 0; i < event->m_actionCount; i++) {
                const ResActionInfo& info = event->m_actions[i];
                for (unsigned int j = 0; j < info.m_actionCount; j++) {
                    if (checkAction(info.m_actions[j])) {
                        invokeAction(info);
                        break;
                    }
                }
            }
            for (unsigned int i = 0; i < event->m_axisCount; i++) {
                invokeAxis(event->m_axes[i]);
            }
        }
    }
}

bool PadRelay::checkAction(const ResAction& action) {
    if (action.m_keyCount == 0) {
        return false;
    }
    const PadData& pad = PadManager::getControlPadData(m_padNo);
    for (unsigned long i = 0; i < action.m_keyCount; i++) {
        const ResKey& key = action.m_keys[i];
        unsigned int bit = getPadKey(static_cast<PadActKey>(key.m_key));
        switch (key.m_kind) {
        case 0:
            if ((bit & pad.m_btn) == 0) {
                return false;
            }
            break;
        case 1:
            if ((bit & pad.m_btn) != 0) {
                return false;
            }
            break;
        case 2:
            if ((bit & pad.m_down) == 0) {
                return false;
            }
            break;
        case 3:
            if ((bit & pad.m_up) == 0) {
                return false;
            }
            break;
        case 4:
            if ((bit & pad.m_repeat) == 0) {
                return false;
            }
            break;
        case 5:
            if ((bit & pad.m_dbl) == 0) {
                return false;
            }
            break;
        case 6:
            if ((bit & pad.pad_18) == 0) {
                return false;
            }
            break;
        case 7:
            if ((bit & pad.pad_14) == 0) {
                return false;
            }
            break;
        default:
            return false;
        }
    }
    return true;
}

void PadRelay::invokeAction(const ResActionInfo& info) {
    mm::mtl::FixStr<32> key(info.m_name);
    if (ActionMap::node* n = m_actions.find(key)) {
        if (n->value.second.isValid()) {
            n->value.second();
        }
    }
}

void PadRelay::invokeAxis(const ResAxisInfo& info) {
    mm::mtl::FixStr<32> key(info.m_name);
    if (AxisMap::node* n = m_axes.find(key)) {
        if (n->value.second.isValid()) {
            const PadData& pad = PadManager::getControlPadData(m_padNo);
            float value;
            switch (info.m_axis) {
            case 0:
                value = pad.m_lx;
                break;
            case 1:
                value = pad.m_ly;
                break;
            case 2:
                value = pad.m_rx;
                break;
            case 3:
                value = pad.m_ry;
                break;
            default:
                value = 0.0f;
                break;
            }
            n->value.second(value * info.m_scale);
        }
    }
}

bool PadRelayUtil::getFwPadKey(unsigned int pad, const char* name, unsigned int action, unsigned int key,
                               unsigned int* pKey) {
    if (const PadResEventManager* manager = PadResEventManager::get()) {
        if (const PadResEvent* event = manager->getResource(pad)) {
            const ResActionInfo* info = nullptr;
            for (unsigned long i = 0; i < event->m_actionCount; i++) {
                if (strcmp(event->m_actions[i].m_name, name) == 0) {
                    info = &event->m_actions[i];
                    break;
                }
            }
            if (info != nullptr && action < info->m_actionCount && key < info->m_actions[action].m_keyCount) {
                *pKey = getPadKey(static_cast<PadActKey>(info->m_actions[action].m_keys[key].m_key));
                return true;
            }
        }
    }
    return false;
}

void PadResEventManager::setup(unsigned int count, mm::mtl::IAllocator* allocator) {
    m_resources.setAllocator(allocator);
    m_resources.resize(count, mm::mtl::IntrusivePtr<const PadResEvent>());
}

void PadResEventManager::cleanup() {
    m_resources.clear();
    m_resources.setAllocator(nullptr);
}

void PadResEventManager::setResource(unsigned int index, const PadResEvent* resource) {
    if (PadResEventManager* manager = get()) {
        manager->m_resources[index] = resource;
    }
}

PadResEventManager::PadResEventManager() {}

PadResEventManager::~PadResEventManager() {}

}  // namespace fw
