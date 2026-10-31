#include "classes/ui/UIObject.h"
#include "classes/ui/UIPolygonObject.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UIShape.h"
#include "classes/ui/UIShapeSimpleFace.h"
#include "classes/ui/UIShapeRing.h"
#include "classes/ui/UIShapeParticle.h"
#include "classes/mm/mtl/IAllocator.h"
#include "layer/LayerAccFormat.h"
#include "layer/LayerAccLayoutObj.h"
#include "layer/LayerAccManager.h"
#include "layer/LayerAccObjBase.h"
#include "layer/LayerAccPolyObj.h"
#include "layer/LayerPolyVertex.h"
#include "mm/mtl/FixStr.h"
#include "ml/ScnRenderDrCapture.h"
#include "ui/UIUtil.h"
#include "mm/mtl/IntrusivePtr.h"

namespace ui {

UIPolygonObject::~UIPolygonObject() {
    if (m_shape != nullptr) {
        delete m_shape;
        m_shape = nullptr;
    }
}

UIPolygonObject* UIPolygonObject::create(UILayoutObject* parent, const PolygonInfo& info, const void* texture,
                                         unsigned int textureSize, const mm::mtl::FixStr<32>& name,
                                         mm::mtl::IAllocator* allocator) {
    if (texture != nullptr) {
        layer::LayerAccFormat format(texture);
        if (format.m_flag) {
            return nullptr;
        }
    }
    UIPolygonObject* object = createObject(parent, info, name, allocator);
    if (object != nullptr) {
        if (object->m_info.m_shapeType == 3) {
            object->m_flags.set(10, true);
        }
        object->m_textureSize = textureSize;
        object->m_capture = nullptr;
        if (texture != nullptr) {
            layer::LayerAccPolyObj poly(object->m_layer);
            poly.setTexutre(texture);
        }
    }
    return object;
}

UIPolygonObject* UIPolygonObject::create(UILayoutObject* parent, const PolygonInfo& info, ml::ScnRenderDrCapture* capture,
                                         const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator) {
    UIPolygonObject* object = createObject(parent, info, name, allocator);
    if (object != nullptr) {
        object->m_textureSize = 0;
        object->m_capture = capture;
        layer::LayerAccPolyObj poly(object->m_layer);
        poly.setTexutre(*capture->m_texture);
    }
    return object;
}

UIPolygonObject* UIPolygonObject::createObject(UILayoutObject* parent, const PolygonInfo& info,
                                               const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator) {
    UIShape* shape = createShape(info, allocator);
    if (shape == nullptr) {
        return nullptr;
    }
    layer::LayerBase* layer;
    if (parent == nullptr) {
        layer::LayerAccManager manager;
        layer = manager.createPolyObj(info.m_width, info.m_height, shape->m_vertices.size(),
                                      shape->m_indices.size(), static_cast<layer::LayerPrimitiveType>(0));
    } else {
        layer::LayerAccLayoutObj layout(parent->m_layer);
        layer = layout.createPolyObj(info.m_width, info.m_height, shape->m_vertices.size(),
                                     shape->m_indices.size(), static_cast<layer::LayerPrimitiveType>(0));
    }
    if (layer == nullptr) {
        return nullptr;
    }
#line 222
    UIPolygonObject* object = new (allocator, 16, __FILE__, __LINE__) UIPolygonObject(layer, mm::mtl::FixStr<32>(name.m_str));
    if (object == nullptr) {
        return nullptr;
    }
    object->m_info = info;
    object->m_shape = shape;
    return object;
}

void UIPolygonObject::apply() {
    UIObject::apply();
    if (m_shape != nullptr) {
        m_shape->update(m_handle);
        if (m_shape->m_dirty && m_shape->m_indexRange != 0) {
            layer::LayerAccPolyObj poly(m_layer);
            poly.LockVertex();
            for (unsigned int i = 0; i < static_cast<unsigned int>(m_shape->m_vertices.size()); i++) {
                layer::LayerPolyVertex vertex = m_shape->m_vertices[i];
                vertex.x = vertex.x * 0.5f + 0.5f;
                vertex.y = vertex.y * 0.5f + 0.5f;
                poly.setVertex(i, vertex);
            }
            poly.UnlockVertex();
            poly.LockIndex();
            for (unsigned int i = 0; i < static_cast<unsigned int>(m_shape->m_indices.size()); i++) {
                poly.setIndex(i, m_shape->m_indices[i]);
            }
            poly.UnlockIndex();
            poly.setIndexInfo(0, m_shape->m_indexRange);
            m_shape->m_dirty = false;
        }
    }
}

unsigned int UIPolygonObject::duplicateImpl(unsigned int handle) {
    UILayoutObject* parent = UIUtil::getLayoutObject(handle);
    if (parent == nullptr) {
        return 0;
    }
    layer::LayerAccObjBase base(m_layer);
    UIPolygonObject* object;
    if (m_capture != nullptr) {
        object = create(parent, m_info, m_capture, mm::mtl::FixStr<32>(m_name.m_str), UIUtil::getProgAllocator());
    } else {
        object = create(parent, m_info, base.getResData(), m_textureSize, mm::mtl::FixStr<32>(m_name.m_str),
                        UIUtil::getProgAllocator());
    }
    if (object == nullptr) {
        return 0;
    }
    object->addRef();
    unsigned int child = parent->addChild(handle, object);
    object->release();
    return child;
}

UIShape* UIPolygonObject::createShape(const PolygonInfo& info, mm::mtl::IAllocator* allocator) {
    switch (info.m_shapeType) {
    case 1:
#line 239
        return new (allocator, 16, __FILE__, __LINE__) UIShapeSimpleFace(info.m_count);
    case 2:
#line 242
        return new (allocator, 16, __FILE__, __LINE__) UIShapeRing(info.m_division, info.m_weight);
    case 3:
#line 245
        return new (allocator, 16, __FILE__, __LINE__) UIShapeParticle(info.m_data, info.m_dataSize, info.m_width, info.m_height);
    }
    return nullptr;
}

mm::mtl::RTTI UIPolygonObject::m_rtti("UIPolygonObject", &UIObject::m_rtti, nullptr);

}  // namespace ui
