#include "classes/fw/UpdatableGroup.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/fw/PointerMap.h"

namespace fw {

UpdatableGroup::UpdatableGroup(mm::mtl::IAllocator* allocator, unsigned int index)
    : pad_48(), m_allocator(allocator), m_index(index) {
    m_objects.setAllocator(allocator);
    m_objects.reserve(0x1000);
}

UpdatableGroup::~UpdatableGroup() {
    m_objects.clear();
}

void UpdatableGroup::update(const UpdateInfo& info, unsigned int mask) {
    for (mm::mtl::List<UpdatableObject*>::iterator it = m_objects.begin(); it != m_objects.end();) {
        UpdatableObject* object = *it;
        ++it;
        if ((mask & (1 << object->m_updateBit)) && !object->isTerminate()) {
            object->update(info);
        }
    }
}

void UpdatableGroup::tail(const UpdateInfo& info) {
    mm::mtl::List<UpdatableObject*>::iterator it = m_objects.begin();
    while (it != m_objects.end()) {
        UpdatableObject* object = *it;
        if (object->isTerminate()) {
            it = m_objects.erase(it);
            destroyObject(object);
        } else {
            ++it;
        }
    }
}

// 1.0.0's: deletes the object and hands its handle back to its map (3.0.1 inlines it into tail and destroyAllObject)
void UpdatableGroup::destroyObject(UpdatableObject* object) {
    unsigned int index = object->m_handle.m_index;
    PointerMap* map = object->m_handle.m_map;
    delete object;
    if (index != 0 && map != nullptr) {
        map->remove(index);
    }
}

void UpdatableGroup::execEvent(const ObjectEvent& event, unsigned int mask) {
    for (mm::mtl::List<UpdatableObject*>::iterator it = m_objects.begin(); it != m_objects.end();) {
        UpdatableObject* object = *it;
        ++it;
        if ((mask & (1 << object->m_updateBit)) && !object->isTerminate()) {
            object->onEvent(event);
        }
    }
}

void UpdatableGroup::registObject(UpdatableObject* object) {
    m_objects.push_back(object);
}

void UpdatableGroup::destroyAllObject() {
    for (mm::mtl::List<UpdatableObject*>::iterator it = m_objects.begin(); it != m_objects.end();) {
        UpdatableObject* object = *it;
        it = m_objects.erase(it);
        destroyObject(object);
    }
}

}  // namespace fw
