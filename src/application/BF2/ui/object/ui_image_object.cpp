#include "layer/LayerAccObjBase.h"
#include "layer/LayerAccLayoutObj.h"
#include "layer/LayerAccManager.h"
#include "layer/LayerAccDefObj.h"
#include "layer/LayerAccDefTexture.h"
#include "layer/LayerAccAction.h"
#include "mm/Pnt.h"
#include "classes/ui/UIObjectBase.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UIImageObject.h"
#include "classes/ui/UIStreamManager.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UIImageObject.h"
#include "classes/ui/UIStreamManager.h"
#include "classes/mm/mtl/IAllocator.h"
#include "layer/LayerAccObjBase.h"
#include "layer/LayerAccLayoutObj.h"
#include "layer/LayerAccManager.h"
#include "ml/ScnRenderDrCapture.h"
#include "mm/mtl/FixStr.h"
#include "ui/UIUtil.h"

namespace ui {

// inline: 3.0.1 keeps no copy of it (the creates inline it)
inline UIImageObject::UIImageObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name)
    : UIObject(layer, name, 2) {
    m_contents = 0;
    m_index = 0;
    m_capture = nullptr;
}

// inline: 3.0.1 keeps no copy of it
inline UIImageObject::UIImageObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name, unsigned int type)
    : UIObject(layer, name, type) {
    m_contents = 0;
    m_index = 0;
    m_capture = nullptr;
}

UIImageObject::~UIImageObject() {
    ;  // stores the table: see CONTRIBUTING.md
}

UIImageObject* UIImageObject::create(UILayoutObject* parent, const void* resource, unsigned int contents,
                                     const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator, bool mask) {
    layer::LayerBase* layer;
    if (parent != nullptr) {
        layer::LayerAccLayoutObj layout(parent->m_layer);
        layer = mask ? layout.createMaskObj(resource) : layout.createObj(resource);
    } else {
        layer::LayerAccManager manager;
        layer = mask ? manager.createMaskObj(resource) : manager.createObj(resource);
    }
    UIImageObject* object;
    if (layer == nullptr) {
        object = nullptr;
    } else {
        layer::LayerAccDefObj def(layer);
        def.setIconNum(0);
#line 106
        object = new (allocator, 16, __FILE__, __LINE__) UIImageObject(layer, mm::mtl::FixStr<32>(name.m_str));
        if (object != nullptr && mask) {
            object->m_flags.set(14, true);  // a mask object
        }
    }
    object->m_contents = contents;
    return object;
}

UIImageObject* UIImageObject::create(UILayoutObject* parent, ml::ScnRenderDrCapture* capture,
                                     const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator) {
    layer::LayerBase* layer;
    if (parent != nullptr) {
        layer::LayerAccLayoutObj layout(parent->m_layer);
        layer = layout.createTexObj(*capture->m_texture);
    } else {
        layer::LayerAccManager manager;
        layer = manager.createTexObj(*capture->m_texture);
    }
    UIImageObject* object;
    if (layer == nullptr) {
        object = nullptr;
    } else {
#line 155
        object = new (allocator, 16, __FILE__, __LINE__) UIImageObject(layer, mm::mtl::FixStr<32>(name.m_str));
    }
    object->m_capture = capture;
    return object;
}

void UIImageObject::changeBin(const void* resource) {
    if (resource != nullptr && m_layer != nullptr) {
        layer::LayerAccDefTexture texture(m_layer);
        texture.setTexutre(resource);
    }
}

void UIImageObject::setMaskObject(UIImageObject* mask) {
    if (mask != nullptr && m_layer != nullptr && mask->m_layer != nullptr && mask->m_flags.test(14)) {
        layer::LayerAccDefObj def(m_layer);
        def.setMaskObj(mask->m_layer);
    }
}

void UIImageObject::setImageIndex(unsigned short index) {
    if (m_capture == nullptr && m_layer != nullptr) {
        if (index < getImageMax()) {
            if (m_contents == 0) {
                layer::LayerAccDefObj def(m_layer);
                def.setIconNum(index);
            } else {
                mm::mtl::PtrSingleton<UIStreamManager>::get()->start(m_contents, m_handle, index);
                m_index = index;
            }
        }
    }
}

unsigned short UIImageObject::getImageMax() {
    if (m_capture != nullptr) {
        return 1;
    }
    if (m_layer == nullptr) {
        return 1;
    }
    return m_contents != 0
               ? mm::mtl::PtrSingleton<UIStreamManager>::get()->getContentsNum(m_contents)
               : layer::LayerAccDefObj(m_layer).getIconMax() + 1;
}

unsigned short UIImageObject::getImageIndex() {
    if (m_capture != nullptr) {
        return 0;
    }
    if (m_layer == nullptr) {
        return 0;
    }
    if (m_contents != 0) {
        return m_index;
    }
    layer::LayerAccDefObj def(m_layer);
    return def.getIconNum();
}

void UIImageObject::setHFlip(bool flip) {
    if (m_layer != nullptr) {
        layer::LayerAccDefObj def(m_layer);
        def.setFlip(static_cast<layer::LayerFlipType>(0), flip);
    }
}

void UIImageObject::setVFlip(bool flip) {
    if (m_layer != nullptr) {
        layer::LayerAccDefObj def(m_layer);
        def.setFlip(static_cast<layer::LayerFlipType>(1), flip);
    }
}

void UIImageObject::setExtType(unsigned int type) {
    if (m_capture == nullptr && m_layer != nullptr) {
        layer::LayerAccDefObj def(m_layer);
        switch (type) {
        case 1:
            def.setGauge(static_cast<layer::LAYER_GAUGE>(3));
            break;
        case 2:
            def.setGauge(static_cast<layer::LAYER_GAUGE>(1));
            break;
        case 3:
            def.setGauge(static_cast<layer::LAYER_GAUGE>(4));
            break;
        case 4:
            def.setGauge(static_cast<layer::LAYER_GAUGE>(2));
            break;
        }
    }
}

unsigned int UIImageObject::getExtType() {
    if (m_capture != nullptr) {
        return 0;
    }
    if (m_layer == nullptr) {
        return 0;
    }
    layer::LayerAccDefObj def(m_layer);
    if (def.getGauge() != 0) {
        if (def.getGauge() == static_cast<layer::LAYER_GAUGE>(3)) {
            return 1;
        }
        if (def.getGauge() == static_cast<layer::LAYER_GAUGE>(1)) {
            return 2;
        }
        if (def.getGauge() == static_cast<layer::LAYER_GAUGE>(4)) {
            return 3;
        }
        if (def.getGauge() == static_cast<layer::LAYER_GAUGE>(2)) {
            return 4;
        }
    }
    return 0;
}

void UIImageObject::setExtParam(float param) {
    if (m_capture == nullptr && m_layer != nullptr) {
        layer::LayerAccDefObj def(m_layer);
        if (def.getGauge() != 0) {
            def.setParm(param);
        }
    }
}

bool UIImageObject::hasAnimation() {
    if (m_capture != nullptr) {
        return false;
    }
    if (m_layer == nullptr) {
        return false;
    }
    if (m_flags.test(14)) {  // a mask object
        return false;
    }
    layer::LayerAccAction action(m_layer);
    return action.isActionData();
}

void UIImageObject::startAnimation(const char* name, bool loop) {
    if (hasAnimation()) {
        layer::LayerAccAction action(m_layer);
        action.actionName(name);
        m_loop = loop;
    }
}

void UIImageObject::startAnimationFromID(unsigned int id, bool loop) {
    if (hasAnimation()) {
        layer::LayerAccAction action(m_layer);
        action.actionID(id);
        m_loop = loop;
    }
}

void UIImageObject::startAnimationFromIndex(unsigned int index, bool loop) {
    if (hasAnimation()) {
        layer::LayerAccAction action(m_layer);
        if (index < action.getActionMax()) {
            action.actionIdx(index);
            m_loop = loop;
        }
    }
}

void UIImageObject::stopAnimation() {
    if (hasAnimation()) {
        layer::LayerAccAction action(m_layer);
        if (action.isRunning()) {
            action.actionEnd();
        }
    }
}

bool UIImageObject::isPlayingAnimation() {
    if (hasAnimation()) {
        layer::LayerAccAction action(m_layer);
        return action.isRunning();
    }
    return false;
}

float UIImageObject::getAnimationPlaybackLength() {
    if (m_capture == nullptr && m_layer != nullptr) {
        layer::LayerAccAction action(m_layer);
        return action.getActionSec(action.getRunningActIdx());
    }
    return 0.0f;
}

void UIImageObject::setAnimationPlaybackTime(float time) {
    if (m_capture == nullptr && m_layer != nullptr) {
        layer::LayerAccAction action(m_layer);
        action.setRunningActSec(time);
    }
}

unsigned int UIImageObject::duplicateImpl(unsigned int handle) {
    UILayoutObject* parent = UIUtil::getLayoutObject(handle);
    if (parent == nullptr) {
        return 0;
    }
    layer::LayerAccObjBase base(m_layer);
    UIImageObject* object;
    if (m_capture != nullptr) {
        object = create(parent, m_capture, mm::mtl::FixStr<32>(m_name.m_str), UIUtil::getProgAllocator());
    } else {
        object = create(parent, base.getResData(), m_contents, mm::mtl::FixStr<32>(m_name.m_str),
                        UIUtil::getProgAllocator(), m_flags.test(14));
    }
    if (object == nullptr) {
        return 0;
    }
    object->addRef();
    object->setImageIndex(getImageIndex());
    unsigned int child = parent->addChild(handle, object);
    object->release();
    return child;
}

mm::mtl::RTTI UIImageObject::m_rtti("UIImageObject", &UIObject::m_rtti, nullptr);

}  // namespace ui
