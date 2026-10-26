#ifndef CLOUD_CLOUDLIST_H
#define CLOUD_CLOUDLIST_H

namespace cloud {

// a list of the cloud objects CloudObjMan keeps (its objects, its model data): first, last and count; each element
// carries m_pPrev, m_pNext and m_pList (the list holding it). The names are not the original's.
template <typename T>
class CloudList {
public:
    void pushBack(T* obj) {
        if (m_pEnd != nullptr) {
            m_pEnd->m_pNext = obj;
            obj->m_pPrev = m_pEnd;
            m_pEnd = obj;
        } else {
            m_pTop = obj;
            m_pEnd = obj;
            obj->m_pPrev = nullptr;
        }
        obj->m_pNext = nullptr;
        obj->m_pList = this;
        ++m_num;
    }

    void remove(T* obj) {
        T* prev = obj->m_pPrev;
        T* next = obj->m_pNext;
        if (prev == nullptr) {
            if (next == nullptr) {
                m_pTop = nullptr;
                m_pEnd = nullptr;
            } else {
                m_pTop = next;
                next->m_pPrev = nullptr;
            }
        } else if (next == nullptr) {
            m_pEnd = prev;
            prev->m_pNext = nullptr;
        } else {
            obj->m_pPrev->m_pNext = obj->m_pNext;
            obj->m_pNext->m_pPrev = obj->m_pPrev;
        }
        obj->m_pNext = nullptr;
        obj->m_pList = nullptr;
        obj->m_pPrev = nullptr;
        --m_num;
    }

    // deletes every element
    void deleteAll() {
        for (T* obj = m_pTop; obj != nullptr;) {
            T* next = obj->m_pNext;
            delete obj;
            obj = next;
        }
        m_num = 0;
        m_pTop = nullptr;
        m_pEnd = nullptr;
    }

    T* m_pTop;  // 0x0
    T* m_pEnd;  // 0x8
    int m_num;  // 0x10
};

}  // namespace cloud

#endif
