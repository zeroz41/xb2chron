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

    T* m_head;
    T* m_tail;
};
}  // namespace idcoli

#endif
