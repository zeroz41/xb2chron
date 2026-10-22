#include "ptlib/IntrusiveList.h"
#include "mm/MMStdBase.h"
#include "mm/Vec3.h"
#include "ptlib/Utility.h"

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

unsigned int Utility::conv_rgba(mm::Vec3* color, float alpha) {
    float r = color->x;
    float g = color->y;
    float b = color->z;
    r = r < 0.0f ? 0.0f : r;
    g = g < 0.0f ? 0.0f : g;
    b = b < 0.0f ? 0.0f : b;
    r = r > 1.0f ? 1.0f : r;
    g = g > 1.0f ? 1.0f : g;
    b = b > 1.0f ? 1.0f : b;
    r *= 255.0f;
    g *= 255.0f;
    float a = alpha * 255.0f;
    a = a < 0.0f ? 0.0f : a;
    a = a > 255.0f ? 255.0f : a;
    b *= 255.0f;
    unsigned char ir = (int)r;
    unsigned char ig = (int)g;
    unsigned char ib = (int)b;
    unsigned char ia = (int)a;
    return ir | (ig << 8) | (ib << 16) | (ia << 24);
}

}  // namespace ptlib
