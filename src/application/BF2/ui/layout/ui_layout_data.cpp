#include "mm/Pnt.h"
#include "classes/ui/UITransform.h"
#include "classes/ui/UIDisplayInfo.h"
#include "classes/ui/UIObjectBase.h"
#include "classes/ui/UIObject.h"
#include "classes/layer/LayerObj.h"
#include "classes/ui/UILayoutData.h"
#include "layer/LayerAccLayoutBinary.h"
#include "mm/Rect.h"
#include "classes/mm/mtl/IAllocator.h"

namespace ui {

UILayoutData::~UILayoutData() {
    ;  // the original stores the table and returns; clang drops the store for an empty body
}

UILayoutData* UILayoutData::create(void* binary, mm::mtl::IAllocator* allocator, const UILayoutData* parent) {
#line 47
    UILayoutData* data = new (allocator, 16, __FILE__, __LINE__) UILayoutData(binary, parent);
    return data;
}

bool UILayoutData::attachLayout(const char* name, UIObject* object) const {
    layer::LayerAccLayoutBinary acc(m_binary);
    if (acc.getPosIdx(name) == -1) {
        if (m_parent == nullptr) {
            return false;
        }
        return m_parent->attachLayout(name, object);
    }
    if (object->m_type == 3) {
        float pos[2];
        float size[2];
        acc.setLayoutPosData(pos[0], pos[1], size[0], size[1], name);
        if (object->m_displayInfo.m_pixelWidth == 1 || object->m_displayInfo.m_pixelHeight == 1) {
            object->setPos(mm::Pnt<short>(pos[0], pos[1]));
        } else {
            object->setPosCenter(mm::Pnt<short>(pos[0] + size[0] * 0.5f, pos[1] + size[1] * 0.5f));
            object->m_transform.setScale(size[0] / object->m_displayInfo.m_pixelWidth,
                                         size[1] / object->m_displayInfo.m_pixelHeight);
        }
    } else {
        acc.setLayoutObj(static_cast<layer::LayerObj*>(object->m_layer), name, true);
        UIObject::importTransform(object->m_transform, object->m_layer);
        if (object->m_displayInfo.m_center == 1) {
            mm::Pnt<short> pos = object->m_transform.m_pos;
            object->setPosCenter(pos);
        }
    }
    return true;
}

bool UILayoutData::getLayoutRect(const char* name, mm::Rect<short>& rect) const {
    if (m_binary == nullptr) {
        return false;
    }
    layer::LayerAccLayoutBinary acc(m_binary);
    int index = acc.getPosIdx(name);
    if (index == -1 && m_parent != nullptr) {
        return m_parent->getLayoutRect(name, rect);
    }
    float pos[2];
    float size[2];
    acc.setLayoutPosData(pos[0], pos[1], size[0], size[1], index);
    rect.x = pos[0];
    rect.y = pos[1];
    rect.w = size[0];
    rect.h = size[1];
    return true;
}

}  // namespace ui
