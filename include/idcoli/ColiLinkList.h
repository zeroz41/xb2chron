#ifndef IDCOLI_COLILINKLIST_H
#define IDCOLI_COLILINKLIST_H

namespace idcoli {
// a list of T linked through T's own m_prev/m_next (IDColiManager's object lists). The member names are not the
// original's.
template <typename T>
class ColiLinkList {
public:
    ColiLinkList() : m_head(nullptr), m_tail(nullptr) {}
    // appends obj (IDColiManager's createColi* functions)
    void pushBack(T* obj) {
        if (m_tail != nullptr) {
            m_tail->m_next = obj;
            obj->m_prev = m_tail;
            m_tail = obj;
        } else {
            m_head = obj;
            m_tail = obj;
            obj->m_prev = nullptr;
        }
        obj->m_next = nullptr;
    }
    // unlinks obj (IDColiManager's addList and delList; the name is not the original's)
    void remove(T* obj) {
        T* prev = obj->m_prev;
        T* next = obj->m_next;
        if (prev == nullptr) {
            if (next == nullptr) {
                m_head = nullptr;
                m_tail = nullptr;
            } else {
                m_head = next;
                next->m_prev = nullptr;
            }
        } else if (next == nullptr) {
            m_tail = prev;
            prev->m_next = nullptr;
        } else {
            prev->m_next = next;
            obj->m_next->m_prev = obj->m_prev;
        }
        obj->m_prev = nullptr;
        obj->m_next = nullptr;
    }

    T* m_head;
    T* m_tail;
};
}  // namespace idcoli

#endif
