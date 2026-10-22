#ifndef FW_HANDLEPTR_H
#define FW_HANDLEPTR_H

namespace fw { class PointerMap; }

namespace fw {
// a handle to a T: its index and the PointerMap that gave it out (UpdatableObject's constructor copies both;
// GfObjManager::createGfObj keeps a copy in the object's info; UpdatableGroup::tail and destroyAllObject hand the
// index back to the map, PointerMap::remove, once they delete the object). The names are not the original's.
template <typename T>
class HandlePtr {
public:
    unsigned int m_index;
    fw::PointerMap* m_map;
};
}  // namespace fw

#endif
