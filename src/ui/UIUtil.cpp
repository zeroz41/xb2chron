#include "ui/UIUtil.h"
#include "layer/LayerAccManager.h"
#include "classes/fw/MemHandlebaseAllocator.h"
#include "classes/fw/PointerMap.h"
#include "classes/ui/UIImageObject.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UIObject.h"

namespace ui { namespace UIUtil {

fw::PointerMap s_ObjPtrMap;
unsigned int s_ObjPtrMax;
fw::MemHandlebaseAllocator s_ProgAllocator;
fw::MemHandlebaseAllocator s_ResAllocator;
unsigned char* s_BdatFPs[17];
unsigned int s_SafeMarginW;
unsigned int s_SafeMarginH;

void initLayerLib() {
    layer::LayerAccManager manager;
    manager.setCoordinate(layer::LayerCoordinate(0));
}

void termLayerLib() {}

void initObjectMap(unsigned int count) {
    s_ObjPtrMap.reserve(&s_ProgAllocator, count);
    s_ObjPtrMax = count;
}

mm::mtl::IAllocator* getProgAllocator() {
    return &s_ProgAllocator;
}

void termObjectMap() {
    s_ObjPtrMap.destroy();
    s_ObjPtrMax = 0;
}

unsigned int registObject(UIObject* object) {
    return s_ObjPtrMap.regist(object);
}

UIObject* getObject(unsigned int handle) {
    return static_cast<UIObject*>(s_ObjPtrMap.getPtr(handle));
}

UILayoutObject* getLayoutObject(unsigned int handle) {
    UIObject* object = getObject(handle);
    if (object == nullptr) {
        return nullptr;
    }
    return object->getRTTI()->isKindOf(&UILayoutObject::m_rtti) ? static_cast<UILayoutObject*>(object) : nullptr;
}

UIImageObject* getImageObject(unsigned int handle) {
    UIObject* object = getObject(handle);
    if (object == nullptr) {
        return nullptr;
    }
    return object->getRTTI()->isKindOf(&UIImageObject::m_rtti) ? static_cast<UIImageObject*>(object) : nullptr;
}

bool isValid(unsigned int handle) {
    return s_ObjPtrMap.isValid(handle);
}

bool isTerm(unsigned int handle) {
    if (!isValid(handle)) {
        return false;
    }
    return (getObject(handle)->m_flags & 8) != 0;
}

unsigned char* getBdatFP(unsigned char index) {
    if (index < 17) {
        return s_BdatFPs[index];
    }
    return nullptr;
}

mm::mtl::IAllocator* getResourceAllocator() {
    return &s_ResAllocator;
}

unsigned int getGroupPriority(unsigned int group) {
    return (group << 5) | 1;
}

void setSafeMergin(unsigned int width, unsigned int height) {
    s_SafeMarginW = width;
    s_SafeMarginH = height;
}

}}  // namespace ui::UIUtil
