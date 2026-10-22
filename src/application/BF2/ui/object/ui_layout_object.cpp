#include "mm/Pnt.h"
#include "classes/ui/UIObjectBase.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIObjectList.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "layer/LayerAccLayoutObj.h"
#include "layer/LayerAccManager.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIObjectList.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UILayoutData.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/mm/mtl/IAllocator.h"
#include "layer/LayerAccLayoutObj.h"
#include "layer/LayerAccManager.h"
#include "mm/Rect.h"
#include "mm/Math.h"
#include "mm/mtl/FixStr.h"
#include "ui/UIUtil.h"

namespace ui {

// inline: 3.0.1 keeps no copy of it (create inlines it)
inline UILayoutObject::UILayoutObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name)
    : UIObject(layer, name, 3), m_list(nullptr), m_layoutData(nullptr), m_offset(0, 0) {
#line 41
    m_list = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectList();
}

UILayoutObject::~UILayoutObject() {
    if (m_layoutData != nullptr) {
        m_layoutData->release();
        m_layoutData = nullptr;
    }
    if (m_list != nullptr) {
        delete m_list;
        m_list = nullptr;
    }
}

UILayoutObject* UILayoutObject::create(UILayoutObject* parent, const mm::mtl::FixStr<32>& name, bool priorityTable,
                                       mm::mtl::IAllocator* allocator) {
    layer::LayerBase* layer;
    if (parent != nullptr) {
        layer::LayerAccLayoutObj layout(parent->m_layer);
        layer = layout.createLayoutObj();
    } else {
        layer::LayerAccManager manager;
        layer = manager.createLayoutObj();
    }
    if (layer == nullptr) {
        return nullptr;
    }
    layer::LayerAccLayoutObj layout(layer);
    if (priorityTable) {
        layout.createPriorityTbl(32);
    }
    layout.setAutoAnchorMode(static_cast<layer::LAYER_ANCHOR>(2));
#line 93
    return new (allocator, 16, __FILE__, __LINE__) UILayoutObject(layer, mm::mtl::FixStr<32>(name.m_str));
}

unsigned int UILayoutObject::addChild(unsigned int handle, UIObject* child) {
    unsigned int result = m_list->regist(child, child->m_name.m_str);
    if (result != 0) {
        child->setParent(handle);
    }
    return result;
}

unsigned int UILayoutObject::countChild(const char* name, unsigned int arg) const {
    unsigned int count = 0;
    if (m_list != nullptr && name != nullptr) {
        count = m_list->count(name, arg);
        for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list->m_list.begin(), end = m_list->m_list.end();
             it != end; ++it) {
            if (it->m_type == 3) {
                count += mm::mtl::rttiCast<UILayoutObject>(it.operator->())->countChild(name, arg);
            }
        }
    }
    return count;
}

unsigned int UILayoutObject::searchChild(const char* name) const {
    if (m_list == nullptr || name == nullptr) {
        return 0;
    }
    unsigned int handle = m_list->search(name);
    if (handle != 0) {
        return handle;
    }
    for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list->m_list.begin(), end = m_list->m_list.end();
         it != end; ++it) {
        if (it->m_type == 3) {
            handle = mm::mtl::rttiCast<UILayoutObject>(it.operator->())->searchChild(name);
            if (handle != 0) {
                return handle;
            }
        }
    }
    return 0;
}

unsigned int UILayoutObject::searchDuplicatedChild(const char* name, unsigned short index) const {
    if (m_list == nullptr || name == nullptr) {
        return 0;
    }
    unsigned int handle = m_list->searchDuplicate(name, index);
    if (handle != 0) {
        return handle;
    }
    for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list->m_list.begin(), end = m_list->m_list.end();
         it != end; ++it) {
        if (it->m_type == 3) {
            handle = mm::mtl::rttiCast<UILayoutObject>(it.operator->())->searchDuplicatedChild(name, index);
            if (handle != 0) {
                return handle;
            }
        }
    }
    return 0;
}

void UILayoutObject::setViewport(const mm::Rect<short>& rect) {
    layer::LayerAccLayoutObj layout(m_layer);
    layer::LayerAccManager manager;  // the original makes one it does not use
    layout.setViewPort(rect.x, rect.y, rect.w, rect.h);
    layout.setViewPortMode(true);
}

void UILayoutObject::setLayoutData(UILayoutData* data) {
    m_layoutData = data;
    data->addRef();
}

void UILayoutObject::setLayoutData(UILayoutObject* other) {
    m_layoutData = other->m_layoutData;
    m_layoutData->addRef();
}

void UILayoutObject::setInitialize() {
    UIObject::setInitialize();
    if (m_list != nullptr) {
        m_list->m_allTerm = false;
    }
}

bool UILayoutObject::isTermWithChild() const {
    if (m_list != nullptr) {
        return (m_flags & 8) != 0 && m_list->m_allTerm;  // bit 3: terminated
    }
    return (m_flags & 8) != 0;
}

void UILayoutObject::reloadText() {
    if (m_list != nullptr) {
        m_list->reloadText();
    }
}

void UILayoutObject::updateSize() {
    // the children's extent along x and along y, each as (least, greatest), from the screen's size (1280x720) down
    // (the names are not the original's)
    mm::Pnt<short> rangeX(1280, 0);
    mm::Pnt<short> rangeY(720, 0);
    bool found = false;
    mm::Rect<short> rect;
    for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list->m_list.begin(), end = m_list->m_list.end();
         it != end; ++it) {
        UIObjectAcc acc(it->m_handle);
        // the original tests the object twice, around isIgnoreSize (as a bool of its own: its code keeps the negation)
        bool use = acc.m_object != nullptr && !acc.isIgnoreSize() && acc.m_object != nullptr;
        if (use && (acc.isDisp() || acc.isAlwaysInLayout())) {
            acc.getRect(rect, 2);
            if (rect.x < rangeX.x) {
                rangeX.x = rect.x;
            }
            if (rect.y < rangeY.x) {
                rangeY.x = rect.y;
            }
            if (rect.x + rect.w > rangeX.y) {
                rangeX.y = rect.x + rect.w;
            }
            if (rect.y + rect.h > rangeY.y) {
                rangeY.y = rect.y + rect.h;
            }
            found = true;
        }
    }
    m_list->m_changed = false;
    if (!found) {
        rangeX.x = 0;
        rangeY.x = 0;
    }
    m_displayInfo.setPixelWidth(mm::abs(rangeX.x - rangeX.y));
    m_displayInfo.setPixelHeight(mm::abs(rangeY.x - rangeY.y));
    float w = m_displayInfo.m_pixelWidth;
    float h = m_displayInfo.m_pixelHeight;
    float sw = w * m_transform.m_scaleX;
    float sh = h * m_transform.m_scaleY;
    m_offset = mm::Pnt<short>((short)((w - sw) * 0.5f) + rangeX.x, (short)((h - sh) * 0.5f) + rangeY.x);
}

void UILayoutObject::update() {
    // terminated (bit 3) or following its parent's termination (bit 4); suspended (bit 15)
    unsigned int flags = m_flags;
    if ((flags & 0x10) && getParentPtr() != nullptr) {
        if (!(getParentPtr()->m_flags & 8) && (m_flags & 0x8000)) {
            return;
        }
    } else if (!(flags & 8) && (m_flags & 0x8000)) {
        return;
    }
    UIObject::update();
    if (m_list != nullptr && !m_list->m_allTerm) {
        m_list->update();
        if (m_parent != 0 && (m_transform.m_changed || m_list->m_changed)) {
            updateSize();
        }
    }
}

void UILayoutObject::apply() {
    UIObject::apply();
    if (!(m_flags & 0x8000) && m_list != nullptr) {
        for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list->m_list.begin(), end = m_list->m_list.end();
             it != end; ++it) {
            UIObject& child = *it;
            child.apply();
            child.resetDirty();
        }
    }
}

void UILayoutObject::getDisplayOffset(unsigned short mode, mm::Pnt<short>& offs) const {
    offs = m_offset;
    if (mode == 1) {
        offs.x += (short)(m_displayInfo.m_pixelWidth * m_transform.m_scaleX * 0.5f);
        offs.y += (short)(m_displayInfo.m_pixelHeight * m_transform.m_scaleY * 0.5f);
    }
}

unsigned int UILayoutObject::duplicateImpl(unsigned int handle) {
    UILayoutObject* parent = UIUtil::getLayoutObject(handle);
    if (parent == nullptr) {
        return 0;
    }
    UILayoutObject* object = create(parent, mm::mtl::FixStr<32>(m_name.m_str), true, UIUtil::getProgAllocator());
    if (object == nullptr) {
        return 0;
    }
    object->setLayoutData(this);
    object->addRef();
    unsigned int child = parent->addChild(handle, object);
    if (child != 0) {
        for (mm::mtl::IntrusiveList<UIObject>::iterator it = m_list->m_list.begin(), end = m_list->m_list.end();
             it != end; ++it) {
            if (it->duplicate(child) == 0) {
                parent->m_list->release(object);
                child = 0;
                break;
            }
        }
    }
    object->release();
    return child;
}

mm::mtl::RTTI UILayoutObject::m_rtti("UILayoutObject", &UIObject::m_rtti, nullptr);

}  // namespace ui
