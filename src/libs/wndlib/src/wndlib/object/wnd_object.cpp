#include "classes/wnd/Shape.h"
#include "classes/wnd/WindObject.h"
#include "mm/MMStdBase.h"

namespace wnd {

WindObject::WindObject(ObjectType type, const WindObjectCreateInfo& info)
    : m_type(type), m_filter(info.filter), m_pProxy(nullptr), m_flags(0) {
#line 25
    MM_ASSERT(info.pTransform);
    MM_ASSERT(info.pShape);
    m_transform = *info.pTransform;
    m_shape = info.pShape;
    m_shape->addRef();
    m_releaseNode.m_pOwner = this;
}

WindObject::~WindObject() {
    if (m_shape != nullptr) {
        m_shape->release();
        m_shape = nullptr;
    }
#line 42
    MM_ASSERT(m_pProxy == nullptr);
}

}  // namespace wnd
