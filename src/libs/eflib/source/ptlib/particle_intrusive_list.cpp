#include "ptlib/IntrusiveList.h"
#include "mm/MMStdBase.h"

namespace ptlib {

IntrusiveListBase::IntrusiveListBase() : m_size(0) {}

void IntrusiveListBase::linkNode(IntrusiveListNode* node, IntrusiveListNode* next) {
#line 34 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/particle_intrusive_list.cpp"
    MM_ASSERT(!node->intoNode());
    IntrusiveListNode* prev = next->m_prev;
    node->m_prev = prev;
    prev->m_next = node;
    next->m_prev = node;
    node->m_next = next;
}

void IntrusiveListBase::unlinkNode(IntrusiveListNode* node) {
#line 43
    MM_ASSERT(node->intoNode());
    node->m_prev->m_next = node->m_next;
    node->m_next->m_prev = node->m_prev;
    node->m_next = node;
    node->m_prev = node;
}

}  // namespace ptlib
