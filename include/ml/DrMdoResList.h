#ifndef ML_DRMDORESLIST_H
#define ML_DRMDORESLIST_H

namespace ml {
// A head/tail list of resources linked through their m_pNext (0x8), owned by the DrMdo*Man managers: their
// destructors delete every node and clear the list. The type and member names are not the original's.
template <class T>
struct DrMdoResList {
    void deleteAll() {
        T* node = m_pHead;
        while (node != nullptr) {
            T* next = node->m_pNext;
            delete node;
            node = next;
        }
        m_pHead = nullptr;
        m_pTail = nullptr;
    }

    T* m_pHead;  // 0x0
    T* m_pTail;  // 0x8
};
}  // namespace ml

#endif
