#include "classes/ui/UIObjectList.h"
#include "classes/ui/UIObjectBase.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIObjectParam.h"
#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UITextObject.h"
#include "ui/UIUtil.h"
#include "mm/mtl/RTTI.h"
#include "mm/mtl/Hash.h"

namespace ui {

UIObjectBase::UIObjectBase(const mm::mtl::FixStr<32>& name)
    : m_flags(0), m_duplicateIndex(0), m_name(name) {
    m_flags = 0;
}

UIObjectBase::~UIObjectBase() {}

void UIObjectBase::update() {
    m_transform.syncParent();
    m_displayInfo.syncParent();
}

void UIObjectBase::setInitialize() {
    m_flags &= ~0x8;
}

void UIObjectBase::setTerm() {
    m_flags &= ~0x8000;
    m_flags |= 0x8;
}

UIObjectList::UIObjectList() : m_allTerm(false), m_changed(false) {}

UIObjectList::~UIObjectList() {
    clear();
}

void UIObjectList::update() {
    if (m_list.m_size == 0) {
        return;
    }
    int termCount = 0;
    bool changed = false;
    for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list.begin(); it != m_list.end();) {
        UIObject* object = it.m_node;
        if (object == nullptr) {
            continue;
        }
        if ((object->m_flags & 0x8) &&
            (object->m_type != 3 || UIUtil::getLayoutObject(object->m_handle)->isTermWithChild())) {
            if (object->m_flags & 0x10) {
                it = m_list.erase(it);
                UIUtil::releaseObject(object->m_handle);
                object->release();
                changed = true;
                continue;
            }
            ++termCount;
        } else {
            object->update();
            object->updatePlugin();
            if (object->m_transform.m_changed || object->m_displayInfo.m_changed) {
                changed = true;
            }
        }
        ++it;
    }
    if (m_list.m_size == termCount) {
        m_allTerm = true;
    }
    if (!m_changed) {
        m_changed = changed;
    }
}

void UIObjectList::apply() {
    for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        UIObject& object = *it;
        object.apply();
        object.resetDirty();
    }
}

unsigned int UIObjectList::regist(UIObject* object, const char* name) {
    if (object == nullptr) {
        return 0;
    }
    for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if (it.m_node == object) {
            return 0;
        }
    }
    object->addRef();
    m_list.push_back(object);
    return object->m_handle;
}

void UIObjectList::release(UIObject* object) {
    for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if (it.m_node == object) {
            m_list.erase(it);
            UIUtil::releaseObject(object->m_handle);
            if (object != nullptr) {
                object->release();
            }
            return;
        }
    }
}

void UIObjectList::release(const char* name) {
    if (name == nullptr) {
        return;
    }
    unsigned int hash = mm::mtl::hashStrCrc(name);
    for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        UIObject& object = *it;
        if (object.m_nameHash == hash) {
            m_list.erase(it);
            UIUtil::releaseObject(object.m_handle);
            object.release();
            return;
        }
    }
}

unsigned int UIObjectList::count(const char* name, unsigned int start) {
    mm::mtl::FixStr<32> str;
    str.format(name, start);
    unsigned int hash = mm::mtl::hashStrCrc(str.m_str);
    unsigned int n = 0;
    for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list.begin(); it != m_list.end();) {
        if (it->m_nameHash == hash) {
            ++n;
            str.format(name, n + start);
            hash = mm::mtl::hashStrCrc(str.m_str);
            it = m_list.begin();
        } else {
            ++it;
        }
    }
    return n;
}

unsigned int UIObjectList::search(const char* name) {
    if (name == nullptr) {
        return 0;
    }
    unsigned int hash = mm::mtl::hashStrCrc(name);
    for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if (it->m_nameHash == hash) {
            return it->m_handle;
        }
    }
    return 0;
}

void UIObjectList::reloadText() {
    for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        UIObject& object = *it;
        if (object.m_type == 1) {
            mm::mtl::rttiCast<UITextObject>(&object)->reloadText();
        } else if (object.m_type == 3) {
            mm::mtl::rttiCast<UILayoutObject>(&object)->reloadText();
        }
    }
}

UIObjectParam::UIObjectParam(unsigned int handle) : m_handle(handle) {
    UIUtil::getObject(handle)->registAdditionalParam(this);
}

UIObjectParam::~UIObjectParam() {
    if (m_handle != 0) {
        UIObject* object = UIUtil::getObject(m_handle);
        if (object != nullptr) {
            object->registAdditionalParam(this);
        }
    }
}

UIObjectPlugin::UIObjectPlugin() : m_next(nullptr), m_updateFlags(1) {}

void UIObjectPlugin::execute(UIObjectAcc&) {
    m_updateFlags = 0;
}

bool UIObjectPlugin::isNeedUpdate(UIObjectAcc& acc) {
    if (acc.isDisp()) {
        return m_updateFlags & 1;
    }
    return false;
}

mm::mtl::RTTI UIObjectPlugin::m_rtti("UIObjectPlugin", nullptr, nullptr);

}  // namespace ui
