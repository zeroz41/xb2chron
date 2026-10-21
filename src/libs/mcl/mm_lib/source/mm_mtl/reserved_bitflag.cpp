#include "mm/mtl/ReservedBitflag.h"
#include <string.h>
#include "classes/mm/mtl/IAllocator.h"
#include "mm/MMStdBase.h"

namespace mm { namespace mtl {

void ReservedBitflag::setLocal(unsigned int index, bool flag) {
#line 16
    MM_ASSERT(m_element != 0);
    MM_ASSERT(index < m_size);
    const unsigned int word = index / 32;
    const unsigned int bit = 1ul << (index & 31ul);
    if (flag) {
        m_element[word] |= bit;
    } else {
        m_element[word] &= ~bit;
    }
}

bool ReservedBitflag::getLocal(unsigned int index) const {
#line 34
    MM_ASSERT(m_element != 0);
    const unsigned int word = index / 32;
    const unsigned int bit = 1ul << (index & 31ul);
    return (m_element[word] & bit) != 0;
}

void ReservedBitflag::clrLocal(unsigned int index) {
    const unsigned int word = index / 32;
    const unsigned int bit = 1ul << (index & 31ul);
    m_element[word] &= ~bit;
}

void ReservedBitflag::clrLocal() {
    if (m_element != nullptr) {
        memset(m_element, 0, m_elementNum * sizeof(unsigned int));
    }
}

ReservedBitflag::ReservedBitflag() : m_element(nullptr), m_size(0), m_elementNum(0), m_allocator(nullptr) {}

ReservedBitflag::~ReservedBitflag() {
    destroy();
}

void ReservedBitflag::destroy() {
    if (m_element != nullptr) {
#line 128
        MM_ASSERT(m_allocator != 0);
        m_allocator->deallocate(m_element);
        m_element = nullptr;
        m_size = 0;
        m_elementNum = 0;
        m_allocator = nullptr;
    }
}

void ReservedBitflag::initialize(IAllocator* allocator, unsigned int size) {
#line 105
    MM_ASSERT(size != 0);
    MM_ASSERT(m_element == 0);
    MM_ASSERT(allocator != 0);
    unsigned int elementNum = (size + sizeof(unsigned int) * 8 - 1) / (sizeof(unsigned int) * 8);
    m_element = static_cast<unsigned int*>(allocator->allocate(elementNum * sizeof(unsigned int), sizeof(unsigned int)));
#line 112
    MM_ASSERT(m_element != 0);
    m_allocator = allocator;
    m_size = size;
    m_elementNum = elementNum;
    clrLocal();
}

void ReservedBitflag::set(unsigned int start, unsigned int last, bool flag) {
#line 169
    MM_ASSERT(start <= last);
    for (unsigned int i = start; i < last; i++) {
        setLocal(i, flag);
    }
}

}}  // namespace mm::mtl
