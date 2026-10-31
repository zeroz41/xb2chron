#include "mm/mtl/Vector.h"
#include "classes/ui/UIObjectList.h"
#include "classes/ui/UIGroup.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIInputLayer.h"
#include "classes/ui/UIInputManager.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIResource.h"
#include "ui/UIUtil.h"

namespace ui {

UIGroup::UIGroup() : m_objList(nullptr), m_flags(0) {}

UIGroup::~UIGroup() {
    clean();
}

void UIGroup::clean() {
    if (m_rootObjs.capacity() != 0) {
        for (RootObjInfo* it = m_rootObjs.begin(); it != m_rootObjs.end(); ++it) {
            if (it->m_resource != nullptr) {
                it->m_resource->release();
                it->m_resource = nullptr;
            }
            releaseInput(it->m_handle);
        }
        m_rootObjs.destroy();
    }
    if (m_inputs.capacity() != 0) {
        // the original's loop does not advance, and it destroys m_rootObjs again rather than m_inputs
        for (InputInfo* it = m_inputs.begin(); it != m_inputs.end();) {
            if (it->m_layer != nullptr) {
                it->m_layer->release();
                it->m_layer = nullptr;
            }
        }
        m_rootObjs.destroy();
    }
    if (m_objList != nullptr) {
        delete m_objList;
        m_objList = nullptr;
    }
    m_flags = 0;
}

void UIGroup::setup(unsigned int count) {
    if (count == 0) {
        return;
    }
    if (m_objList != nullptr) {
        delete m_objList;
        m_objList = nullptr;
    }
#line 60
    m_objList = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectList();
    m_rootObjs.setAllocator(UIUtil::getProgAllocator());
    m_rootObjs.reserve(count, 8);
    m_inputs.setAllocator(UIUtil::getProgAllocator());
    m_inputs.reserve(count, 8);
}

void UIGroup::releaseInput(unsigned int handle) {
    for (InputInfo* it = m_inputs.begin(); it != m_inputs.end();) {
        if (it->m_handle == handle) {
            if (it->m_input != 0) {
                UIInputManager::get()->releaseInputLayer(it->m_input);
            }
            if (it->m_layer != nullptr) {
                it->m_layer->release();
                it->m_layer = nullptr;
            }
            it = m_inputs.erase(it);
        } else {
            ++it;
        }
    }
}

void UIGroup::disp(bool disp) {
    if (disp) {
        m_flags &= ~4;
    } else {
        m_flags |= 4;
    }
}

void UIGroup::applyObject() {
    if (m_objList == nullptr || (m_flags & 2) != 0) {
        return;
    }
    if ((m_flags & 4) != 0) {
        for (RootObjInfo* it = m_rootObjs.begin(); it != m_rootObjs.end(); ++it) {
            UIObject* object = UIUtil::getObject(it->m_handle);
            it->m_disp = object->m_displayInfo.m_disp;
            object->m_displayInfo.setDisp(false);
        }
    }
    m_objList->apply();
    if ((m_flags & 4) != 0) {
        for (RootObjInfo* it = m_rootObjs.begin(); it != m_rootObjs.end(); ++it) {
            UIUtil::getObject(it->m_handle)->m_displayInfo.setDisp(it->m_disp);
        }
    }
}

unsigned int UIGroup::registObject(UIObject* object, const char* name, unsigned short layer, UIResource* resource) {
    if (m_objList == nullptr) {
        return 0;
    }
    RootObjInfo info;
    info.m_handle = m_objList->regist(object, name);
    if (info.m_handle == 0) {
        return 0;
    }
    info.m_name = name;
    info.m_layer = layer;
    info.m_resource = resource;
    info.m_terminate = false;
    info.m_release = false;
    info.m_releaseWait = 0;
    resource->addRef();
    m_rootObjs.push_back(info);
    return info.m_handle;
}

unsigned int UIGroup::searchObject(const char* name) {
    if (m_objList == nullptr) {
        return 0;
    }
    return m_objList->search(name);
}

void UIGroup::terminateObject(const char* name, bool release) {
    if (m_objList == nullptr) {
        return;
    }
    unsigned int handle = m_objList->search(name);
    if (handle == 0) {
        return;
    }
    RootObjInfo* it = getRootInfo(handle);
    if (it == nullptr) {
        return;
    }
    if (!it->m_terminate) {
        releaseInput(handle);
        readyTerminate(handle);
        it->m_terminate = true;
        it->m_release = release;
    }
}

void UIGroup::readyTerminate(unsigned int handle) {
    UIObject* object = UIUtil::getObject(handle);
    if (!object->m_flags.test(1)) {
        object->setTerm();
    } else {
        UIEventManager::EventInfo event;
        event.m_data.m_type = 2;
        event.m_handle = handle;
        UIEventManager::get()->pushObjectEvent(event);
    }
    if (object->m_type == 3) {
        UIObjectList* list = UIUtil::getLayoutObject(handle)->m_list;
        for (mm::mtl::IntrusiveList<UIObject>::iterator it = list->m_list.begin(), end = list->m_list.end(); it != end;
             ++it) {
            readyTerminate(it->m_handle);
        }
    }
}

void UIGroup::terminateObjectAll(bool release) {
    for (RootObjInfo* it = m_rootObjs.begin(); it != m_rootObjs.end(); ++it) {
        releaseInput(it->m_handle);
        readyTerminate(it->m_handle);
        it->m_terminate = true;
        it->m_release = release;
    }
}

void UIGroup::releaseObject(const char* name) {
    if (m_objList == nullptr) {
        return;
    }
    unsigned int handle = m_objList->search(name);
    if (handle == 0) {
        return;
    }
    RootObjInfo* it = getRootInfo(handle);
    if (it == nullptr) {
        return;
    }
    it->m_release = true;
}

bool UIGroup::isActiveLayer(unsigned short layer) {
    for (RootObjInfo* it = m_rootObjs.begin(); it != m_rootObjs.end(); ++it) {
        if (it->m_layer == layer) {
            return true;
        }
    }
    return false;
}

bool UIGroup::isAssignedLayer(const char* name, unsigned int layer) {
    if (m_objList == nullptr) {
        return false;
    }
    unsigned int handle = m_objList->search(name);
    if (handle == 0) {
        return false;
    }
    RootObjInfo* it = getRootInfo(handle);
    if (it == nullptr) {
        return false;
    }
    return it->m_layer == layer;
}

bool UIGroup::fn_710068DBAC(const char* name) {
    unsigned int handle = searchObject(name);
    for (RootObjInfo* it = m_rootObjs.begin(); it != m_rootObjs.end(); ++it) {
        if (it->m_terminate && it->m_handle == handle) {
            return true;
        }
    }
    return false;
}

void UIGroup::attachInput(const char* name, UIInputLayer* layer) {
    if (m_objList == nullptr) {
        return;
    }
    unsigned int handle = m_objList->search(name);
    if (handle == 0) {
        return;
    }
    UIObject* object = UIUtil::getObject(layer->m_id);
    mm::mtl::FixStr<64> layerName;
    layerName.format("%s_%s", name, object->m_name.m_str);
    unsigned int input = UIInputManager::get()->registInputLayer(layer, layerName.m_str);
    if (input == 0) {
        return;
    }
    layer->addRef();
    InputInfo info;
    info.m_layer = layer;
    info.m_input = input;
    info.m_handle = handle;
    m_inputs.push_back(info);
}

void UIGroup::suspend(bool stopApply) {
    m_flags = m_flags | (stopApply ? 3 : 1);
    for (InputInfo* it = m_inputs.begin(); it != m_inputs.end(); ++it) {
        if (it->m_input != 0) {
            UIInputManager::get()->releaseInputLayer(it->m_input);
            it->m_input = 0;
        }
    }
}

void UIGroup::resume() {
    m_flags &= ~3;
    for (InputInfo* it = m_inputs.begin(); it != m_inputs.end(); ++it) {
        if (it->m_input == 0) {
            it->m_input = UIInputManager::get()->registInputLayer(it->m_layer, getRootInfo(it->m_handle)->m_name.m_str);
        }
    }
}

void UIGroup::reloadText() {
    for (RootObjInfo* it = m_rootObjs.begin(); it != m_rootObjs.end(); ++it) {
        UIUtil::getLayoutObject(it->m_handle)->reloadText();
    }
}

bool UIGroup::hasObject() const {
    return m_rootObjs.size() != 0;
}

}  // namespace ui
