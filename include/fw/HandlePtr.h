#ifndef FW_HANDLEPTR_H
#define FW_HANDLEPTR_H

namespace fw {
// a handle to a T: its index and the object (UpdatableObject's constructor copies both; GfObjManager::createGfObj
// keeps a copy in the object's info). The names are not the original's.
template <typename T>
class HandlePtr {
public:
    unsigned int m_index;
    T* m_ptr;
};
}  // namespace fw

#endif
