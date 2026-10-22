#include "classes/ui/UIObject.h"
#include "classes/ml/Scn.h"
#include "classes/fw/ModelObject.h"
#include "layer/LayerAccLayoutObj.h"
#include "layer/LayerAccMemObj.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "ml/ScnRenderDrViewCtrl.h"
#include "classes/ui/UIScreenObject.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ui {

UIScreenObject::~UIScreenObject() {
    if (m_onMemory == 0 && m_model != nullptr) {
        m_model->release();
        m_model = nullptr;
    }
    if (m_onMemory == 1) {
        switch (m_onMemoryInfo.m_modelTexture) {
        case 1:
        case 2:
        case 3:
        case 4: {
            ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<ml::Scn>::get()->m_renderDrSys, 0);
            unsigned char slot = m_onMemoryInfo.m_modelTexture - 1;  // the original truncates it to a byte
            acc.resetModelTexture(slot);
            break;
        }
        }
    }
}

UIScreenObject* UIScreenObject::create(UILayoutObject* parent, ml::ScnRenderDrViewCtrl* view, fw::ModelObject* model,
                                       const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator) {
    layer::LayerAccLayoutObj layout(parent->m_layer);
    layer::LayerBase* layer = layout.createTexObj(*view->m_texture);
    if (layer == nullptr) {
        return nullptr;
    }
#line 79
    UIScreenObject* object = new (allocator, 16, __FILE__, __LINE__) UIScreenObject(layer, mm::mtl::FixStr<32>(name.m_str));
    if (object != nullptr) {
        object->m_onMemory = 0;
        object->m_viewIndex = view->m_viewIndex;
        object->m_model = model;
        if (model != nullptr) {
            model->addRef();
        }
    }
    return object;
}

UIScreenObject* UIScreenObject::createOnMemory(UILayoutObject* parent, unsigned int width, unsigned int height,
                                               const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator,
                                               const OnMemoryInfo& info) {
    layer::LayerAccLayoutObj layout(parent->m_layer);
    layer::LayerBase* layer = layout.createMemObj(width, height, (layer::LayerMemType)info.m_memType);
    if (layer == nullptr) {
        return nullptr;
    }
#line 116
    UIScreenObject* object = new (allocator, 16, __FILE__, __LINE__) UIScreenObject(layer, mm::mtl::FixStr<32>(name.m_str));
    if (object != nullptr) {
        object->m_onMemory = 1;
    }
    switch (info.m_modelTexture) {
    case 1:
    case 2:
    case 3:
    case 4: {
        ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<ml::Scn>::get()->m_renderDrSys, 0);
        layer::LayerAccMemObj memObj(layer);
        unsigned char slot = info.m_modelTexture - 1;  // the original truncates it to a byte
        ml::ScnRenderDrMdlTexture texture;
        texture.m_texture = memObj.getTexture();
        texture.m_slot = slot;
        texture.m_enable = true;
        acc.setModelTexture(texture);
        memObj.setRender(false);
        break;
    }
    }
    object->m_onMemoryInfo = info;
    return object;
}

unsigned int UIScreenObject::getOnMemoryPixelSize() const {
    if (m_onMemory == 1) {
        switch (m_onMemoryInfo.m_memType) {
        case 1:
            return 3;
        case 2:
            return 2;
        case 3:
            return 1;
        }
    }
    return 0;
}

void* UIScreenObject::getOnMemoryBuffer() const {
    if (m_onMemory == 1) {
        layer::LayerAccMemObj memObj(m_layer);
        return memObj.getMemBufer();
    }
    return nullptr;
}

void UIScreenObject::swapOnMemoryBuffer() {
    if (m_onMemory == 1) {
        layer::LayerAccMemObj memObj(m_layer);
        memObj.updateMemBufer();
    }
}

unsigned int UIScreenObject::duplicateImpl(unsigned int) {
    return 0;
}

mm::mtl::RTTI UIScreenObject::m_rtti("UIScreenObject", &UIObject::m_rtti, nullptr);

}  // namespace ui
