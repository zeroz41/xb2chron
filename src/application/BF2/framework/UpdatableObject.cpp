#include "classes/fw/PointerMap.h"
#include "fw/HandlePtr.h"
#include "mm/mtl/UniquePtr.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/fw/UpdatableObjectFactory.h"
#include "classes/fw/UpdatableObjectManager.h"
#include "classes/fw/UpdatableGroup.h"
#include "classes/mm/mtl/IAllocator.h"
#include "string.h"

namespace fw {

mm::mtl::RTTI UpdatableObject::m_rtti("UpdatableObject", nullptr, nullptr);

UpdatableObject::UpdatableObject(unsigned int type, const HandlePtr<UpdatableObject>& handle, unsigned int arg)
    : m_handle(handle), m_type(type), m_updateBit(arg), m_flags(0) {
    for (int i = 0; i < 16; i++) {
        m_components[i] = nullptr;
    }
}

UpdatableObject::~UpdatableObject() {
    UpdatableObject* parent = m_parent.get();
    if (parent != nullptr) {
        parent->removeChild(m_handle.get());
    }
}

void UpdatableObject::setTerminate() {
    m_flags |= 1;
}

bool UpdatableObject::isTerminate() const {
    return m_flags & 1;
}

void UpdatableObject::addChild(UpdatableObject* child) {
    m_children.push_back(child);
    child->m_parent = m_handle;
}

void UpdatableObject::removeChild(UpdatableObject* child) {
    m_children.remove(child);
    child->m_parent = HandlePtr<UpdatableObject>();
}

void UpdatableObject::registComponentLocal(unsigned int slot, ComponentObject* component) {
    m_components[slot] = component;
    component->m_owner = this;
}

void UpdatableObject::removeComponentLocal(unsigned int slot) {
    if (m_components[slot] != nullptr) {
        delete m_components[slot];
        m_components[slot] = nullptr;
    }
}

void UpdatableObject::initialize() {}

void UpdatableObject::onEvent(const ObjectEvent& event) {}

}  // namespace fw
