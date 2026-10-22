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

// 1.0.0's fw::UpdatableObjectManager::Impl (0x140 bytes): 32 groups and the map of the objects' handles; its
// constructor and destructor have no out-of-line copy in 1.0.0
class UpdatableObjectManager::Impl {
public:
    enum { GROUP_MAX = 32 };  // the name is not the original's

    Impl(mm::mtl::IAllocator* allocator, unsigned long count) : m_allocator(allocator) {
        for (int i = 0; i < GROUP_MAX; i++) {
            m_groups[i] = nullptr;
        }
        m_pointerMap.reserve(allocator, count);
        m_pointerMap.setRange(1, 0x7FFFFFF, 0x7FFFFFF);
    }
    ~Impl() {
        destroy();
        m_pointerMap.destroy();
    }
    HandlePtr<UpdatableObject> registPointer(unsigned int type, const void* ptr);
    void registGroup(unsigned int index, UpdatableGroup* group);
    void removeGroup(unsigned int index);
    void destroy();
    void destroyObject(unsigned int mask);
    void update(const UpdateInfo& info, unsigned int mask);
    void tail(const UpdateInfo& info);
    void execEvent(const ObjectEvent& event, unsigned int mask);
    UpdatableGroup* getGroup(unsigned int index);
    void registObject(unsigned int index, UpdatableObject* object);

    // the names are not the original's
    mm::mtl::IAllocator* m_allocator;  // the constructor's: the groups and the factory come from it
    UpdatableGroup* m_groups[GROUP_MAX];  // initialize makes them
    PointerMap m_pointerMap;  // the objects' handles (registPointer)
};

HandlePtr<UpdatableObject> UpdatableObjectManager::Impl::registPointer(unsigned int type, const void* ptr) {
    return HandlePtr<UpdatableObject>(m_pointerMap.regist(ptr), &m_pointerMap);
}

void UpdatableObjectManager::Impl::registGroup(unsigned int index, UpdatableGroup* group) {
    removeGroup(index);
    m_groups[index] = group;
}

void UpdatableObjectManager::Impl::removeGroup(unsigned int index) {
    if (m_groups[index] != nullptr) {
        delete m_groups[index];
        m_groups[index] = nullptr;
    }
}

void UpdatableObjectManager::Impl::destroy() {
    for (int i = GROUP_MAX - 1; i >= 0; i--) {
        if (m_groups[i] != nullptr) {
            m_groups[i]->destroyAllObject();
        }
    }
    for (int i = GROUP_MAX - 1; i >= 0; i--) {
        removeGroup(i);
    }
}

void UpdatableObjectManager::Impl::destroyObject(unsigned int mask) {
    for (int i = GROUP_MAX - 1; i >= 0; i--) {
        if (m_groups[i] != nullptr && (mask & (1 << i))) {
            m_groups[i]->destroyAllObject();
        }
    }
}

void UpdatableObjectManager::Impl::update(const UpdateInfo& info, unsigned int mask) {
    for (int i = 0; i < GROUP_MAX; i++) {
        if (m_groups[i] != nullptr) {
            m_groups[i]->update(info, mask);
        }
    }
}

void UpdatableObjectManager::Impl::tail(const UpdateInfo& info) {
    for (int i = GROUP_MAX - 1; i >= 0; i--) {
        if (m_groups[i] != nullptr) {
            m_groups[i]->tail(info);
        }
    }
}

void UpdatableObjectManager::Impl::execEvent(const ObjectEvent& event, unsigned int mask) {
    for (int i = 0; i < GROUP_MAX; i++) {
        if (m_groups[i] != nullptr) {
            m_groups[i]->execEvent(event, mask);
        }
    }
}

UpdatableGroup* UpdatableObjectManager::Impl::getGroup(unsigned int index) {
    return m_groups[index];
}

void UpdatableObjectManager::Impl::registObject(unsigned int index, UpdatableObject* object) {
    getGroup(index)->registObject(object);
}

UpdatableObjectManager::UpdatableObjectManager(mm::mtl::IAllocator* allocator, unsigned long count)
#line 234
    : m_impl(new (allocator, 8, __FILE__, __LINE__) Impl(allocator, count)) {}

UpdatableObjectManager::~UpdatableObjectManager() {}

bool UpdatableObjectManager::initialize() {
    mm::mtl::IAllocator* allocator = m_impl->m_allocator;
    for (unsigned int i = 0; i < Impl::GROUP_MAX; i++) {
#line 256
        UpdatableGroup* group = new (allocator, 8, __FILE__, __LINE__) UpdatableGroup(allocator, i);
        m_impl->registGroup(i, group);
    }
#line 262
    new (allocator, 8, __FILE__, __LINE__) UpdatableObjectFactory(allocator, this);
    return true;
}

bool UpdatableObjectManager::finalize() {
    delete UpdatableObjectFactory::get();
    m_impl.reset();
    return true;
}

void UpdatableObjectManager::update(const UpdateInfo& info, unsigned int mask) {
    if (isFinalized()) {
        return;
    }
    m_impl->update(info, mask);
}

void UpdatableObjectManager::execEvent(const ObjectEvent& event, unsigned int mask) {
    if (isFinalized()) {
        return;
    }
    m_impl->execEvent(event, mask);
}

void UpdatableObjectManager::tail(const UpdateInfo& info) {
    if (isFinalized()) {
        return;
    }
    m_impl->tail(info);
}

HandlePtr<UpdatableObject> UpdatableObjectManager::registPointer(unsigned int type, const void* ptr) {
    return m_impl->registPointer(type, ptr);
}

void UpdatableObjectManager::registObject(unsigned int group, UpdatableObject* object) {
    m_impl->registObject(group, object);
}

const char* UpdatableObjectManager::getName() const {
    return "UpdatableObjectManager";
}

UpdatableObjectFactory::~UpdatableObjectFactory() {}

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
