#ifndef FW_HANDLEPTR_H
#define FW_HANDLEPTR_H

#include "classes/fw/PointerMap.h"

namespace fw {
// a handle to a T: its index and the PointerMap that gave it out (UpdatableObject's constructor copies both;
// GfObjManager::createGfObj keeps a copy in the object's info; UpdatableGroup::tail and destroyAllObject hand the
// index back to the map, PointerMap::remove, once they delete the object). The names are not the original's.
// Its copies are its own (UpdatableObjectManager::registPointer returns one through memory; UpdatableObject's
// constructor and addChild copy it field by field), and none is index 0 and no map (removeChild clears a
// child's parent to that).
template <typename T>
class HandlePtr {
public:
    HandlePtr() : m_index(0), m_map(nullptr) {}
    HandlePtr(unsigned int index, fw::PointerMap* map) : m_index(index), m_map(map) {}
    HandlePtr(const HandlePtr& other) : m_index(other.m_index), m_map(other.m_map) {}
    HandlePtr& operator=(const HandlePtr& other) {
        m_index = other.m_index;
        m_map = other.m_map;
        return *this;
    }
    // the T it points at, none for index 0 (UpdatableObject's destructor finds its parent and itself through
    // them; the name is not the original's)
    T* get() const { return m_index != 0 ? static_cast<T*>(m_map->getPtr(m_index)) : nullptr; }

    unsigned int m_index;
    fw::PointerMap* m_map;
};
}  // namespace fw

#endif
