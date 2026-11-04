#include "ui/EventData.h"
#include "classes/ui/UIInputManager.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIInputPad.h"
#include "ui/UIUtil.h"
#include "mm/mtl/Hash.h"

namespace ui {

UIInputManager::UIInputManager() : m_minimumLayerHandle(0), m_enabled(true) {}

UIInputManager::~UIInputManager() {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end();) {
        if (it->m_layer != nullptr) {
            it->m_layer->release();
            it->m_layer = nullptr;
        }
        InputLayerInfo* info = it.operator->();
        it = m_layers.erase(it);
        delete info;
    }
    // The list's own emptying follows the release of its elements.
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end();) {
        it = m_layers.erase(it);
    }
}

void UIInputManager::sendEvent(InputLayerInfo& layer) {
    UIEventManager::EventInfo info;
    info.m_data.m_type = 0;
    info.m_data.m_param01 = 0;
    info.m_handle = layer.m_layer->m_id;
    if (layer.m_target != 0 && UIUtil::isValid(layer.m_target)) {
        info.m_handle = layer.m_target;
    }
    if (layer.m_layer->m_event.m_type != 0 || layer.m_layer->m_actionEvent.m_type != 0 || layer.m_layer->hasEventExt()) {
        info.m_data.copyFrom(layer.m_layer->m_event);
        UIEventManager::get()->pushObjectEvent(info);
    }
    if (layer.m_layer->m_actionEvent.m_type != 0) {
        info.m_data.copyFrom(layer.m_layer->m_actionEvent);
        UIEventManager::get()->pushObjectEvent(info);
    }
    if (layer.m_layer->hasEventExt()) {
        info.m_data.copyFrom(*layer.m_layer->getInputEventExt());
        UIEventManager::get()->pushObjectEvent(info);
    }
    layer.m_layer->clear();
}

void UIInputManager::enable() { m_enabled = true; }

void UIInputManager::disable() { m_enabled = false; }

unsigned int UIInputManager::registInputLayer(UIInputLayer* layer, const char* name) {
#line 128
    InputLayerInfo* info = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) InputLayerInfo();
    if (info == nullptr) {
        return 0;
    }
    info->m_layer = layer;
    layer->addRef();
    info->m_target = 0;
    info->m_enabled = true;
    info->m_handle = mm::mtl::hashStrCrc(name);
    InputList::iterator it = m_layers.begin();
    for (; it != m_layers.end(); ++it) {
        if (layer->m_handle >= (*it).m_layer->m_handle) {
            break;
        }
    }
    m_layers.insert(it, info);
    if (UIUtil::isValid(info->m_layer->m_id)) {
        UIUtil::getObject(layer->m_id)->m_flags.set(2, true);
    }
    return info->m_handle;
}

void UIInputManager::releaseInputLayer(unsigned int handle) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        if (it->m_handle == handle) {
            if (UIUtil::isValid(it->m_layer->m_id)) {
                UIUtil::getObject(it->m_layer->m_id)->m_flags.reset(2);
            }
            if (it->m_layer != nullptr) {
                it->m_layer->release();
                it->m_layer = nullptr;
            }
            InputLayerInfo* info = it.operator->();
            m_layers.erase(it);
            operator delete(info);
            return;
        }
    }
}

void UIInputManager::setupInputSelection(unsigned int handle, int select, unsigned int max) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            info.m_layer->setupSelection(select, max);
            sendEvent(info);
            return;
        }
    }
}

void UIInputManager::resetInputSelection(unsigned int handle) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            info.m_layer->resetSelection();
            sendEvent(info);
            return;
        }
    }
}

void UIInputManager::setSelectionChecker(unsigned int handle, IUIInputSelectionChecker* checker) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            info.m_layer->m_checker = checker;
            return;
        }
    }
}

void UIInputManager::setInputActionEnable(unsigned int handle, unsigned int action, bool enable) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            info.m_layer->setActionEnable(action, enable);
            return;
        }
    }
}

unsigned int UIInputManager::searchInputHandle(unsigned int object) {
    if (object == 0) {
        return 0;
    }
    UIObject* obj = UIUtil::getObject(object);
    if (obj == nullptr) {
        return 0;
    }
    if (obj->m_flags.test(2)) {
        for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
            // the layer's own object test is taken before the second *it (the original branches on it after
            // each path of that check)
            bool found = (*it).m_layer->m_id == object;
            InputLayerInfo& info = *it;
            if (found || info.m_target == object) {
                return info.m_handle;
            }
        }
    }
    return 0;
}

UIInputLayer* UIInputManager::getInputLayer(unsigned int handle) {
    if (handle != 0) {
        for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
            InputLayerInfo& info = *it;
            if (info.m_handle == handle) {
                return info.m_layer;
            }
        }
    }
    return nullptr;
}

bool UIInputManager::migrateInput(unsigned int handle, unsigned int target) {
    if (handle == 0) {
        return false;
    }
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            info.m_target = target;
            if (target != 0) {
                UIUtil::getObject(target)->m_flags.set(2, true);
            }
            return true;
        }
    }
    return false;
}

void UIInputManager::enableInput(unsigned int handle) {
    if (handle == 0) {
        return;
    }
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            info.m_enabled = true;
            return;
        }
    }
}

void UIInputManager::disableInput(unsigned int handle) {
    if (handle == 0) {
        return;
    }
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            info.m_enabled = false;
            return;
        }
    }
}

bool UIInputManager::isEnableInput(unsigned int handle) {
    if (handle != 0) {
        for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
            InputLayerInfo& info = *it;
            if (info.m_handle == handle) {
                return info.m_enabled != 0;
            }
        }
    }
    return false;
}

void UIInputManager::setPadLineSelection(unsigned int handle, unsigned int max) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            UIInputPad* pad = info.m_layer->castUIInputPad();
            if (pad != nullptr) {
                pad->setLineSelectionMax(max);
            }
            return;
        }
    }
}

void UIInputManager::setPadLineSelectionLoop(unsigned int handle, bool loop) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            UIInputPad* pad = info.m_layer->castUIInputPad();
            if (pad != nullptr) {
                pad->setLineSelectLoop(loop);
            }
            return;
        }
    }
}

void UIInputManager::setPadPageSize(unsigned int handle, unsigned int size) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            UIInputPad* pad = info.m_layer->castUIInputPad();
            if (pad != nullptr) {
                pad->setPageSize(size);
            }
            return;
        }
    }
}

void UIInputManager::setPadLoopSetting(unsigned int handle, bool loop) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            UIInputPad* pad = info.m_layer->castUIInputPad();
            if (pad != nullptr) {
                pad->setLoop(loop);
            }
            return;
        }
    }
}

void UIInputManager::setupPointerSelection(unsigned int handle, const UIInputPointer::SelectionSetup& setup) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            UIInputPointer* pointer = info.m_layer->castUIInputPointer();
            if (pointer != nullptr) {
                pointer->setupPointerSelection(setup);
            }
            return;
        }
    }
}

void UIInputManager::changePointerPos(unsigned int handle, const mm::Pnt<short>& pos) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            UIInputPointer* pointer = info.m_layer->castUIInputPointer();
            if (pointer != nullptr) {
                pointer->changePointerPos(pos);
            }
            return;
        }
    }
}

void UIInputManager::changeRegionScale(unsigned int handle, float scale) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            UIInputPointer* pointer = info.m_layer->castUIInputPointer();
            if (pointer != nullptr) {
                pointer->changeRegionScale(scale);
            }
            return;
        }
    }
}

void UIInputManager::setPadLineSelectionForce(unsigned int handle, unsigned int value) {
    for (InputList::iterator it = m_layers.begin(); it != m_layers.end(); ++it) {
        InputLayerInfo& info = *it;
        if (info.m_handle == handle) {
            UIInputPad* pad = info.m_layer->castUIInputPad();
            if (pad != nullptr) {
                pad->setLineSelectionMaxForce(value);
            }
            return;
        }
    }
}

}  // namespace ui
