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
    // unlinks node (its m_pPrev/m_pNext at 0x0/0x8; DrMdoSmlShadowMan's lists). The name is not the original's.
    void remove(T* node) {
        T* prev = node->m_pPrev;
        T* next = node->m_pNext;
        if (prev != nullptr) {
            if (next != nullptr) {
                prev->m_pNext = next;
                node->m_pNext->m_pPrev = node->m_pPrev;
            } else {
                m_pTail = prev;
                prev->m_pNext = nullptr;
            }
        } else {
            if (next != nullptr) {
                m_pHead = next;
                next->m_pPrev = nullptr;
            } else {
                m_pHead = nullptr;
                m_pTail = nullptr;
            }
        }
        node->m_pPrev = nullptr;
        node->m_pNext = nullptr;
    }
    // links node at the end. The name is not the original's.
    void pushBack(T* node) {
        if (m_pTail == nullptr) {
            m_pHead = node;
            m_pTail = node;
            node->m_pPrev = nullptr;
        } else {
            m_pTail->m_pNext = node;
            node->m_pPrev = m_pTail;
            m_pTail = node;
        }
        node->m_pNext = nullptr;
    }

    T* m_pHead;  // 0x0
    T* m_pTail;  // 0x8
};
}  // namespace ml

#endif
