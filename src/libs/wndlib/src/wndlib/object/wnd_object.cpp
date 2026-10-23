#include "classes/wnd/WindObject.h"
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
    m_pShape = info.pShape;
    m_pShape->addRef();
    m_releaseNode.m_pOwner = this;
}

WindObject::~WindObject() {
    if (m_pShape != nullptr) {
        m_pShape->release();
        m_pShape = nullptr;
    }
#line 42
    MM_ASSERT(m_pProxy == nullptr);
}

}  // namespace wnd
